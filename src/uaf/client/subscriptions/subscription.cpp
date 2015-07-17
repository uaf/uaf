/* This file is part of the UAF (Unified Architecture Framework) project.
 *
 * Copyright (C) 2012 Wim Pessemier (Institute of Astronomy, KULeuven)
 *
 * Project website: http://www.ster.kuleuven.be/uaf
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "uaf/client/subscriptions/subscription.h"

namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;
    using std::vector;
    using std::map;
    using std::size_t;


    // Constructor
    // =============================================================================================
    Subscription::Subscription(
            LoggerFactory*                          loggerFactory,
            const SubscriptionSettings&             subscriptionSettings,
            ClientSubscriptionHandle                clientSubscriptionHandle,
            ClientConnectionId                      clientConnectionId,
            UaClientSdk::UaSession*                 uaSession,
            UaClientSdk::UaSubscriptionCallback*    uaSubscriptionCallback,
            uaf::ClientInterface*                  clientInterface,
            Database*                               database)
    : uaSession_(uaSession),
      uaSubscriptionCallback_(uaSubscriptionCallback),
      subscriptionSettings_(subscriptionSettings),
      clientSubscriptionHandle_(clientSubscriptionHandle),
      clientConnectionId_(clientConnectionId),
      database_(database),
      clientInterface_(clientInterface),
      clientHandle_(0)
    {
        // build the logger name:
        stringstream loggerName;
        loggerName << "Subscription-" << int(clientSubscriptionHandle);
        logger_ = new Logger(loggerFactory, loggerName.str());

        subscriptionState_ = uaf::subscriptionstates::Deleted;

        uaSubscription_ = 0;

        logger_->debug("Subscription %d has been constructed", clientSubscriptionHandle);
        logger_->debug("Subscription settings:");
        logger_->debug(subscriptionSettings.toString());
    }


    // Destructor
    // =============================================================================================
    Subscription::~Subscription()
    {
        logger_->debug("Now destructing the subscription");

        // try to delete the subscription
        Status status = deleteSubscription();

        // Don't delete the uaSubscription_, it is owned by uaSession_!
        // And also don't delete the uaSession_ here, it is owned by uaf::Session!

        // delete the logger
        delete logger_;
        logger_ = 0;
    }


    Status Subscription::createSubscription()
    {

        logger_->debug("Creating the subscription to the server");

        Status ret;

        UaClientSdk::ServiceSettings serviceSettings;

        UaClientSdk::SubscriptionSettings subscriptionSettings;
        subscriptionSettings = toSdk(subscriptionSettings_);

        SdkStatus sdkStatus = uaSession_->createSubscription(
                serviceSettings,
                uaSubscriptionCallback_,
                clientSubscriptionHandle_,
                subscriptionSettings,
                OpcUa_True,
                &uaSubscription_);


        if (sdkStatus.isGood())
            ret = statuscodes::Good;
        else
            ret = CreateSubscriptionError(sdkStatus);

        if (ret.isGood())
        {
            setSubscriptionState(uaf::subscriptionstates::Created);
            logger_->debug("The subscription has been successfully created to the server");
        }
        else
        {
            setSubscriptionState(uaf::subscriptionstates::Deleted);
            logger_->error(ret);
        }

        return ret;
    }


    Status Subscription::deleteSubscription()
    {
        Status ret;

        if (uaSession_->isConnected())
        {

            if (isCreated())
            {
                logger_->debug("Now deleting subscription %d and thereby deleting all monitored items",
                               clientSubscriptionHandle_);
                UaClientSdk::ServiceSettings serviceSettings;
                SdkStatus sdkStatus = uaSession_->deleteSubscription(serviceSettings, &uaSubscription_);

                if (sdkStatus.isGood())
                    ret = statuscodes::Good;
                else
                    ret = DeleteSubscriptionError(sdkStatus);
            }
            else
            {
                logger_->debug("No need to delete subscription %d on the server side, as it was " \
                               "already deleted", clientSubscriptionHandle_);
                ret = statuscodes::Good;
            }
        }
        else
        {
            ret = SessionNotConnectedError();
        }

        // now update the persistent requests
        MonitoredItemsMap::iterator it = monitoredItemsMap_.begin();
        while (it != monitoredItemsMap_.end())
        {
            // remove the notification buffer according to the kind
            if (it->second.settings.kind() == MonitoredItemSettings::Data)
            {
                database_->createMonitoredDataRequestStore.updateTargetStatus(
                        it->second.requestHandle,
                        it->second.targetRank,
                        SubscriptionHasBeenDeletedError());
            }
            else
            {
                database_->createMonitoredEventsRequestStore.updateTargetStatus(
                        it->second.requestHandle,
                        it->second.targetRank,
                        SubscriptionHasBeenDeletedError());
            }

            // remove the monitoredItemsMap_ entry
            monitoredItemsMap_.erase(it++);
        }

        // log the result
        if (ret.isGood())
        {
            logger_->debug("The subscription has been deleted successfully");
            setSubscriptionState(uaf::subscriptionstates::Deleted);
        } else
        {
            logger_->error(ret);
        }

        return ret;
    }


    bool Subscription::isCreated() const
    {
        return subscriptionState_ == uaf::subscriptionstates::Created;
    }


    // Set the monitoring mode
    // =============================================================================================
    Status Subscription::setPublishingMode(
            bool                   publishingEnabled,
            const ServiceSettings& serviceSettings)
    {
        OpcUa_Boolean uaPublishingEnabled = publishingEnabled ? OpcUa_True : OpcUa_False;
        UaClientSdk::ServiceSettings uaServiceSettings;
        serviceSettings.toSdk(uaServiceSettings);
        SdkStatus sdkStatus = uaSubscription_->setPublishingMode(uaServiceSettings,
                                                                 uaPublishingEnabled);

        if (sdkStatus.isGood())
            return statuscodes::Good;
        else
            return SetPublishingModeInvocationError(sdkStatus);
    }


    // Set the publishing mode for the given client handles.
    // =============================================================================================
    Status Subscription::setMonitoringModeIfNeeded(
            vector<ClientHandle>            clientHandles,
            monitoringmodes::MonitoringMode monitoringMode,
            const ServiceSettings&          serviceSettings,
            vector<Status>&                 results)
    {
        logger_->debug("Setting the monitored item mode to %s",
                       uaf::monitoringmodes::toString(monitoringMode).c_str());

        Status ret;

        UaMutexLocker locker(&monitoredItemsMapMutex_); // unlocks when locker goes out of scope

        // Create an array of affected MonitoredItemIds, and their rank number.
        // To increase efficiency, we first make these arrays the same size as the ClientHandles,
        // then fill the arrays from the front towards the end, and finally we resize them again
        // to the correct size.
        uint32_t maxSize = clientHandles.size();
        uint32_t realSize = 0; // to be updated
        UaUInt32Array ranks;
        UaUInt32Array ids;
        ranks.resize(maxSize);
        ids.resize(maxSize);
        MonitoredItemsMap::const_iterator it;
        for (uint32_t i = 0; i < maxSize; i++)
        {
            it = monitoredItemsMap_.find(clientHandles[i]);

            if (it != monitoredItemsMap_.end())
            {
                realSize++;

                ranks[realSize-1] = i;
                ids[realSize-1]   = it->second.monitoredItemId;
            }
        }

        // don't forget to resize the ranks and ids now to their real size:
        ranks.resize(realSize);
        ids.resize(realSize);

        // now invoke the service
        OpcUa_MonitoringMode opcUaMonitoringMode = fromUafToSdk(monitoringMode);
        UaClientSdk::ServiceSettings uaServiceSettings;
        serviceSettings.toSdk(uaServiceSettings);
        UaStatusCodeArray uaStatusCodes;

        SdkStatus sdkStatus = uaSubscription_->setMonitoringMode(
                uaServiceSettings,
                opcUaMonitoringMode,
                ids,
                uaStatusCodes);

        if (sdkStatus.isGood())
            return statuscodes::Good;
        else
            return SetMonitoringModeInvocationError(sdkStatus);


        logger_->debug("Result of OPC UA service call: %s", ret.toString().c_str());

        if (ret.isGood())
        {
            for (uint32_t i = 0; i < realSize; i++)
            {
                if (OpcUa_IsGood(uaStatusCodes[i]))
                    results[ranks[i]] = statuscodes::Good;
                else
                    results[ranks[i]] = ServerCouldNotSetMonitoringModeError(
                            clientHandles[ranks[i]],
                            SdkStatus(uaStatusCodes[i]));
            }
        }

        return ret;
    }



    // Change the subscription status
    // =============================================================================================
    void Subscription::setSubscriptionState(
            uaf::subscriptionstates::SubscriptionState subscriptionState)
    {
        logger_->debug("The subscription status has changed to %s",
                       uaf::subscriptionstates::toString(subscriptionState).c_str());
        Subscription::subscriptionState_ = subscriptionState;

        // call the callback interface
        clientInterface_->subscriptionStatusChanged(subscriptionInformation());
    }


    // Get information about the session
    // =============================================================================================
    uaf::SubscriptionInformation Subscription::subscriptionInformation() const
    {
        uaf::SubscriptionInformation info;
        info.clientConnectionId = clientConnectionId_;
        info.clientSubscriptionHandle = clientSubscriptionHandle_;
        info.subscriptionState = subscriptionState_;
        info.subscriptionSettings = subscriptionSettings_;
        return info;
    }


    // Get information about the monitored item
    // =============================================================================================
    bool Subscription::monitoredItemInformation(
            ClientHandle                clientHandle,
            MonitoredItemInformation&   monitoredItemInformation)
    {
        UaMutexLocker locker(&monitoredItemsMapMutex_); // unlocks when locker goes out of scope

        MonitoredItemsMap::const_iterator it = monitoredItemsMap_.find(clientHandle);

        bool monitoredItemFound = (it != monitoredItemsMap_.end());

        if (monitoredItemFound)
        {
            monitoredItemInformation.monitoredItemState = monitoreditemstates::Created;
            monitoredItemInformation.clientConnectionId = clientConnectionId_;
            monitoredItemInformation.clientSubscriptionHandle = clientSubscriptionHandle_;
            monitoredItemInformation.clientHandle = it->first;
            monitoredItemInformation.settings = it->second.settings;
        }

        return monitoredItemFound;
    }


    // keep the subscription alive
    // =============================================================================================
    void Subscription::keepAlive()
    {
        logger_->debug("The subscription is still alive");

        // create the notification
        KeepAliveNotification notification;

        notification.clientConnectionId         = clientConnectionId_;
        notification.clientSubscriptionHandle   = clientSubscriptionHandle_;
        notification.subscriptionState          = subscriptionState_;

        UaMutexLocker locker(&monitoredItemsMapMutex_); // unlocks when locker goes out of scope

        // now add the monitored item handles

        for (MonitoredItemsMap::iterator it = monitoredItemsMap_.begin();
                it != monitoredItemsMap_.end(); ++it)
            notification.clientHandles.push_back(it->first);

        // call the callback interface
        clientInterface_->keepAliveReceived(notification);
    }


    // implemented from callback interface
    // =============================================================================================
    void Subscription::dataChange(
            const UaDataNotifications&  dataNotifications,
            const UaDiagnosticInfos &   diagnosticInfos)
    {
        // get the number of notifications
        uint32_t noOfNotifications = dataNotifications.length();

        // create the notifications
        vector<DataChangeNotification> notifications;

        logger_->debug("A total of %d data notifications were received", noOfNotifications);

        // fill the notifications
        for (uint32_t i=0; i < noOfNotifications; i++)
        {
            ClientHandle clientHandle = dataNotifications[i].ClientHandle;

            MonitoredItemsMap::const_iterator it = monitoredItemsMap_.find(clientHandle);

            // update the contents of the notification
            if (it != monitoredItemsMap_.end())
            {
                DataChangeNotification notification;

                notification.clientHandle       = clientHandle;
                notification.data               = dataNotifications[i].Value.Value;

                if (OpcUa_IsGood(dataNotifications[i].Value.StatusCode))
                    notification.status = statuscodes::Good;
                else
                    notification.status = BadDataReceivedError(SdkStatus(dataNotifications[i].Value.StatusCode));

                // add it to the vector of notifications for the callback
                notifications.push_back(notification);

                // log the notification
                logger_->debug(" - Notification %d:", int(i));
                logger_->debug(notification.toString("   ", 25));
            }
        }

        // call the callback interface
        clientInterface_->dataChangesReceived(notifications);
    }


    // implemented from callback interface
    // =============================================================================================
    void Subscription::newEvents(UaEventFieldLists& uaEventFieldList)
    {
        // get the number of notifications
        uint32_t noOfNotifications = uaEventFieldList.length();

        logger_->debug("A total of %d notifications were received", noOfNotifications);

        // create the notifications
        vector<EventNotification> notifications;

        // fill the notifications
        for (uint32_t i=0; i < noOfNotifications; i++)
        {
            ClientHandle clientHandle = uaEventFieldList[i].ClientHandle;

            MonitoredItemsMap::const_iterator it = monitoredItemsMap_.find(clientHandle);

            // update the contents of the notification
            if (it != monitoredItemsMap_.end())
            {
                EventNotification notification;

                notification.clientHandle       = clientHandle;

                // update the event fields
                for (int32_t j=0; j < uaEventFieldList[i].NoOfEventFields; j++)
                    notification.fields.push_back(Variant(uaEventFieldList[i].EventFields[j]));

                // add it to the vector of notifications for the callback
                notifications.push_back(notification);

                // log the notification
                logger_->debug(" - Notification %d:", int(i));
                logger_->debug(notification.toString("   ", 25));
            }
        }

        // call the callback interface
        clientInterface_->eventsReceived(notifications);
    }

}

