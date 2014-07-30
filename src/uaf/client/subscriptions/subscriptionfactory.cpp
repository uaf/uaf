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

#include "uaf/client/subscriptions/subscriptionfactory.h"

namespace uafc
{
    using namespace uaf;
    using namespace uafc;
    using std::string;
    using std::stringstream;
    using std::vector;


    // Constructor
    // =============================================================================================
    SubscriptionFactory::SubscriptionFactory(
            LoggerFactory*              loggerFactory,
            uafc::ClientConnectionId    clientConnectionId,
            UaClientSdk::UaSession*     uaSession,
            ClientInterface*            clientInterface,
            Database*                   database)
    : uaSession_(uaSession),
      clientConnectionId_(clientConnectionId),
      database_(database),
      clientInterface_(clientInterface),
      transactionId_(0)
    {
        // build the logger name:
        stringstream loggerName;
        loggerName << "SubFactory-" << clientConnectionId;
        logger_ = new Logger(loggerFactory, loggerName.str());

        logger_->debug("SubscriptionFactory for session %d has been constructed",
                       clientConnectionId);
    }


    // Destructor
    // =============================================================================================
    SubscriptionFactory::~SubscriptionFactory()
    {
        logger_->debug("Destructing the subscription factory");

        // delete the logger
        delete logger_;
        logger_ = 0;
    }





    // Get a new transaction id
    // =============================================================================================
    uafc::TransactionId SubscriptionFactory::getNewTransactionId_()
    {
        UaMutexLocker locker(&transactionIdMutex_);

        uint32_t delta = 1;
        TransactionId newTransactionId;
        while (delta < OpcUa_UInt32_Max)
        {
            newTransactionId = transactionId_ + delta;

            if (transactionMap_.find(newTransactionId) == transactionMap_.end())
            {
                transactionId_ = newTransactionId;
                return transactionId_;
            }
            else
            {
                delta++;
            }
        }

        return 0;
    }



    // Manual subscription
    //==============================================================================================
    Status SubscriptionFactory::manuallySubscribe(
            const SubscriptionSettings& settings,
            ClientSubscriptionHandle&   clientSubscriptionHandle)
    {
        Status ret;
        Subscription* subscription = 0;

        ret = acquireSubscription(settings, subscription);

        if (ret.isGood())
        {
            clientSubscriptionHandle = subscription->clientSubscriptionHandle();

            ret = releaseSubscription(subscription);
        }
        else
        {
            ret.addDiagnostic("Could not manually subscribe");
            logger_->error(ret);
        }

        return ret;
    }

    // Manual unsubscription
    //==============================================================================================
    Status SubscriptionFactory::manuallyUnsubscribe(
            ClientSubscriptionHandle clientSubscriptionHandle)
    {
        Status ret;
        Subscription* subscription = 0;

        ret = acquireExistingSubscription(clientSubscriptionHandle, subscription);

        if (ret.isGood())
        {
            ret = subscription->deleteSubscription();
            releaseSubscription(subscription);
        }
        else
        {
            ret.addDiagnostic("Could not manually unsubscribe");
            logger_->error(ret);
        }

        return ret;
    }




    // Get information about the subscription
    // =============================================================================================
    Status SubscriptionFactory::subscriptionInformation(
            ClientSubscriptionHandle    clientSubscriptionHandle,
            SubscriptionInformation&    subscriptionInformation)
    {
        Status ret;

        Subscription* subscription = 0;
        ret = acquireExistingSubscription(clientSubscriptionHandle, subscription);

        if (ret.isGood())
        {
            subscriptionInformation = subscription->subscriptionInformation();
            releaseSubscription(subscription);
        }

        return ret;
    }



    // Get information about the subscriptions
    // =============================================================================================
    vector<SubscriptionInformation> SubscriptionFactory::allSubscriptionInformations()
    {
        logger_->debug("Getting the subscription information for all subscription");

        vector<SubscriptionInformation> ret;

        // lock the mutex to make sure the subscriptionMap_ is not being manipulated
        UaMutexLocker locker(&subscriptionMapMutex_);

        // loop trough the sessions
        for (SubscriptionMap::const_iterator it = subscriptionMap_.begin();
                it != subscriptionMap_.end();
                ++it)
        {
            ret.push_back(it->second->subscriptionInformation());
        }

        return ret;
    }


    // Get information about the monitored item
    // =============================================================================================
    bool SubscriptionFactory::monitoredItemInformation(
            ClientHandle                clientHandle,
            MonitoredItemInformation&   monitoredItemInformation)
    {
        // lock the mutex to make sure the subscriptionMap_ is not being manipulated
        UaMutexLocker locker(&subscriptionMapMutex_);

        bool monitoredItemFound = false;

        // loop trough the sessions
        for (SubscriptionMap::const_iterator it = subscriptionMap_.begin();
                it != subscriptionMap_.end() && (!monitoredItemFound);
                ++it)
        {
            monitoredItemFound = it->second->monitoredItemInformation(
                    clientHandle,
                    monitoredItemInformation);
        }

        return monitoredItemFound;
    }


    // Set the publishing mode.
    // =============================================================================================
    Status SubscriptionFactory::setPublishingMode(
            ClientSubscriptionHandle    clientSubscriptionHandle,
            bool                        publishingEnabled,
            const ServiceSettings&      serviceSettings,
            bool&                       subscriptionFound)
    {
        // lock the mutex to make sure the sessionMap_ is not being manipulated
        UaMutexLocker locker(&subscriptionMapMutex_);

        // loop trough the subscriptions
        for (SubscriptionMap::iterator it = subscriptionMap_.begin();
                it != subscriptionMap_.end();
                ++it)
        {
            subscriptionFound = clientSubscriptionHandle == it->second->clientSubscriptionHandle();

            if (subscriptionFound)
                return it->second->setPublishingMode(publishingEnabled, serviceSettings);
        }

        return Status(uaf::statuscodes::InvalidRequestError,
                      "Could not set the publishing mode since clientSubscriptionHandle %d was " \
                      "not found",
                      clientSubscriptionHandle);
    }



    // Set the monitoring mode for the given client handles.
    // =============================================================================================
    Status SubscriptionFactory::setMonitoringModeIfNeeded(
            vector<ClientHandle>            clientHandles,
            monitoringmodes::MonitoringMode monitoringMode,
            const ServiceSettings&          serviceSettings,
            vector<Status>&                 results)
    {
        Status ret;

        // lock the mutex to make sure the sessionMap_ is not being manipulated
        UaMutexLocker locker(&subscriptionMapMutex_);

        // loop trough the subscriptions
        for (SubscriptionMap::iterator it = subscriptionMap_.begin();
                it != subscriptionMap_.end() && ret.isNotBad();
                ++it)
        {
            ret = it->second->setMonitoringModeIfNeeded(
                    clientHandles,
                    monitoringMode,
                    serviceSettings,
                    results);
        }

        return ret;
    }


    // Construct a subscription if needed
    // =============================================================================================
    Status SubscriptionFactory::acquireSubscription(
            const SubscriptionSettings& subscriptionSettings,
            Subscription*&              subscription)
    {
        logger_->debug("Acquiring subscription with the following settings:");
        logger_->debug(subscriptionSettings.toString());

        Status ret;

        subscription = 0;

        // lock the mutex to make sure the subscriptionMap_ is not being manipulated
        UaMutexLocker locker(&subscriptionMapMutex_);

        // we'll try to find a similar subscription that can be re-used,
        // unless we're creating an "unique" subscription
        // (one that is only created for -and used by- the current request)
        if (subscriptionSettings.unique)
        {
            logger_->debug("The requested subscription must be unique");
        }
        else
        {
            // loop trough the subscriptions ...
            for (SubscriptionMap::const_iterator it = subscriptionMap_.begin();
                 it != subscriptionMap_.end();
                 ++it)
            {
                // ... until a suitable one is found
                if (it->second->subscriptionSettings() == subscriptionSettings)
                {
                    subscription = it->second;
                    logger_->debug("A suitable subscription (ClientSubscriptionHandle=%d) already exists",
                                   subscription->clientSubscriptionHandle());

                    // get the ClientSubscriptionHandle of the subscription
                    ClientSubscriptionHandle handle = subscription->clientSubscriptionHandle();

                    // now increment the activity count of the subscription
                    activityMapMutex_.lock();
                    activityMap_[handle] = activityMap_[handle] + 1;
                    activityMapMutex_.unlock();

                    ret.setGood();

                    break;
                }
            }
        }

        // if no subscription exists yet, we create one
        if (subscription == 0)
        {
            ClientSubscriptionHandle clientSubscriptionHandle;
            clientSubscriptionHandle = database_->createUniqueClientSubscriptionHandle();

            logger_->debug("We create a new subscription with clientSubscriptionHandle %d",
                           clientSubscriptionHandle);

            // create a new subscription instance
            subscription = new Subscription(
                    logger_->loggerFactory(),
                    subscriptionSettings,
                    clientSubscriptionHandle,
                    clientConnectionId_,
                    uaSession_,
                    this,
                    clientInterface_,
                    database_);

            // store the new subscription instance in the subscriptionMap
            subscriptionMap_[clientSubscriptionHandle] = subscription;

            logger_->debug("The new subscription has been created");

            // create an activity count for the subscription
            activityMapMutex_.lock();
            activityMap_[clientSubscriptionHandle] = 1;
            activityMapMutex_.unlock();

            // create the subscription on the server
            ret = subscription->createSubscription();
        }

        // 'subscription' now points to an existing Subscription instance
        // (i.e. a valid memory location)

        ret.setGood();


        // add some diagnostics
        if (ret.isGood())
        {
            activityMapMutex_.lock();
            logger_->debug("The requested subscription is acquired (#activities: %d)",
                           activityMap_[subscription->clientSubscriptionHandle()]);
            activityMapMutex_.unlock();
        }
        else
        {
            logger_->error("The requested subscription could not be acquired");
            ret.addDiagnostic("The requested subscription could not be acquired");
        }
        return ret;
    }




    // Acquire an existing session, if one is available.
    // =============================================================================================
    Status SubscriptionFactory::acquireExistingSubscription(
            ClientSubscriptionHandle    clientSubscriptionHandle,
            Subscription*&              subscription)
    {
        logger_->debug("Acquiring existing subscription %d if available", clientSubscriptionHandle);

        Status ret;

        subscription = 0;

        // lock the mutex to make sure the sessionMap is nog being manipulated
        UaMutexLocker locker(&subscriptionMapMutex_);

        SubscriptionMap::const_iterator iter = subscriptionMap_.find(clientSubscriptionHandle);

        if (iter == subscriptionMap_.end())
        {
            ret.setStatus(statuscodes::InvalidRequestError,
                          "No subscription with ClientSubscriptionHandle %d is known",
                          clientSubscriptionHandle);

            logger_->error(ret);
        }
        else
        {
            // update the subscription argument
            subscription = iter->second;

            // increment the activity count of the session
            activityMapMutex_.lock();
            Activity newActivityCount = activityMap_[clientSubscriptionHandle] + 1;
            activityMap_[clientSubscriptionHandle] = newActivityCount;
            activityMapMutex_.unlock();

            // an existing session was acquired, so set the status to Good
            ret.setGood();

            logger_->debug("Subscription %d was acquired (#activities: %d)",
                           clientSubscriptionHandle, newActivityCount);
        }

        return ret;
    }




    // Release a subscription
    // =============================================================================================
    Status SubscriptionFactory::releaseSubscription(
            Subscription*&  subscription,
            bool            allowGarbageCollection)
    {
        Status ret;


        // lock the mutex to make sure the subscriptionMap is not being manipulated
        UaMutexLocker subscriptionMapLocker(&subscriptionMapMutex_);

        // also lock the mutex to make sure the activity cannot change anymore
        UaMutexLocker activityMapLocker(&activityMapMutex_);

        if (subscription == 0)
        {
            ret.setStatus(statuscodes::UnexpectedError,
                          "releaseSubscription() got a null pointer!");
            logger_->error(ret);
        }
        else if (activityMap_[subscription->clientSubscriptionHandle()] == 0)
        {
            ret.setStatus(statuscodes::UnexpectedError,
                          "Trying to release a fully released subscription!");
            logger_->error(ret);
        }
        else
        {
            ClientSubscriptionHandle handle = subscription->clientSubscriptionHandle();

            activityMap_[handle] = activityMap_[handle] - 1;
            ret.setGood();

            logger_->debug("Subscription %d is now released (#activities: %d)",
                           handle, activityMap_[handle]);

            // check if the subscription is closed
            if (!subscription->isCreated() && allowGarbageCollection)
            {
                // if there is no ongoing activity of the session (in other words: if there is no
                // pointer to this session being used), we may delete it!
                if (activityMap_[handle] == 0)
                {
                    logger_->debug("There's no ongoing activity of this deleted subscription, so "
                                   "we may delete it");
                    delete subscription;
                    subscription = 0;
                    activityMap_.erase(handle);
                    subscriptionMap_.erase(handle);

                    logger_->debug("The subscription has been deleted");
                }
            }
        }

        return ret;
    }


    // implemented from callback interface
    // =============================================================================================
    void SubscriptionFactory::subscriptionStatusChanged(
                    OpcUa_UInt32    clientSubscriptionHandle,
                    const UaStatus& uaStatus)
    {
        logger_->debug("Subscription status for clientSubscriptionHandle %d has changed: %s",
                clientSubscriptionHandle, uaStatus.toString().toUtf8());

        // acquire the subscription for which the event was meant:
        Subscription* subscription = 0;
        Status acquireStatus = acquireExistingSubscription(clientSubscriptionHandle, subscription);

        if (acquireStatus.isGood())
        {
            // update the session state
            subscription->setSubscriptionState(uafc::subscriptionstates::toUaf(uaStatus));

            // release the acquired session
            releaseSubscription(subscription);
        }
    }


    // implemented from callback interface
    // =============================================================================================
    void SubscriptionFactory::keepAlive(OpcUa_UInt32 clientSubscriptionHandle)
    {
        logger_->debug("Subscription %d received a keep alive message", clientSubscriptionHandle);

        // acquire the subscription for which the event was meant:
        Subscription* subscription = 0;
        Status acquireStatus = acquireExistingSubscription(clientSubscriptionHandle, subscription);

        if (acquireStatus.isGood())
        {
            // update the session state
            subscription->keepAlive();

            // release the acquired session
            releaseSubscription(subscription);
        }
        else
        {
            logger_->warning("Unknown ClientSubscriptionHandle, discarding notification!");
        }
    }


    // implemented from callback interface
    // =============================================================================================
    void SubscriptionFactory::notificationsMissing(
            OpcUa_UInt32 clientSubscriptionHandle,
            OpcUa_UInt32 previousSequenceNumber,
            OpcUa_UInt32 newSequenceNumber)
    {
        logger_->debug("Notifications are missing for subscription %d! (%d + 1 != %d)",
                clientSubscriptionHandle,
                previousSequenceNumber,
                newSequenceNumber);

        // acquire the subscription:
        Subscription* subscription = 0;
        Status acquireStatus = acquireExistingSubscription(clientSubscriptionHandle, subscription);
        SubscriptionInformation info;

        if (acquireStatus.isGood())
        {
            // get the updated subscription info
            info = subscription->subscriptionInformation();

            // release the acquired session
            releaseSubscription(subscription);
        }
        else
        {
            logger_->warning("Unknown ClientSubscriptionHandle, discarding notification!");
        }

        // call the callback interface
        clientInterface_->notificationsMissing(info, previousSequenceNumber, newSequenceNumber);
    }


    // implemented from callback interface
    // =============================================================================================
    void SubscriptionFactory::dataChange(
            OpcUa_UInt32                clientSubscriptionHandle,
            const UaDataNotifications&  dataNotifications,
            const UaDiagnosticInfos &   diagnosticInfos)
    {
        logger_->debug("New data change event for subscription %d", clientSubscriptionHandle);


        // acquire the subscription for which the event was meant:
        Subscription* subscription = 0;
        Status acquireStatus = acquireExistingSubscription(clientSubscriptionHandle, subscription);

        if (acquireStatus.isGood())
        {
            // update the session state
            subscription->dataChange(dataNotifications, diagnosticInfos);

            // release the acquired session
            releaseSubscription(subscription);
        }
        else
        {
            logger_->warning("Unknown ClientSubscriptionHandle, discarding notification!");
        }

    }


    // implemented from callback interface
    // =============================================================================================
    void SubscriptionFactory::newEvents(
            OpcUa_UInt32        clientSubscriptionHandle,
            UaEventFieldLists&  uaEventFieldList)
    {
        logger_->debug("Subscription %d received %d new events",
                       clientSubscriptionHandle, uaEventFieldList.length());

        // acquire the subscription for which the event was meant:
        Subscription* subscription = 0;
        Status acquireStatus = acquireExistingSubscription(clientSubscriptionHandle, subscription);

        if (acquireStatus.isGood())
        {
            // update the session state
            subscription->newEvents(uaEventFieldList);

            // release the acquired session
            releaseSubscription(subscription);
        }
        else
        {
            logger_->warning("Unknown ClientSubscriptionHandle, discarding notification!");
        }
    }


    // implemented from callback interface
    // =============================================================================================
    void SubscriptionFactory::createMonitoredItemsComplete(
                    OpcUa_UInt32 transactionId,
                    const UaStatus &result,
                    const UaMonitoredItemCreateResults &createResults,
                    const UaDiagnosticInfos &diagnosticInfos)
    {
        logger_->debug("Create monitored items complete (transaction %d)", transactionId);
    }


    // implemented from callback interface
    // =============================================================================================
    void SubscriptionFactory::modifyMonitoredItemsComplete(
                    OpcUa_UInt32 transactionId,
                    const UaStatus &result,
                    const UaMonitoredItemModifyResults &modifyResults,
                    const UaDiagnosticInfos &diagnosticInfos)
    {
        logger_->debug("Modifying monitored items complete (transaction %d)", transactionId);
    }


    // implemented from callback interface
    // =============================================================================================
    void SubscriptionFactory::setMonitoringModeComplete(
                    OpcUa_UInt32 transactionId,
                    const UaStatus &result,
                    const UaStatusCodeArray &setModeResults,
                    const UaDiagnosticInfos &diagnosticInfos)
    {
        logger_->debug("Set monitoring mode complete (transaction %d)", transactionId);
    }


    // implemented from callback interface
    // =============================================================================================
    void SubscriptionFactory::deleteMonitoredItemsComplete(
            OpcUa_UInt32 transactionId,
            const UaStatus &result,
            const UaStatusCodeArray &deleteResults,
            const UaDiagnosticInfos &diagnosticInfos)
    {
        logger_->debug("Delete monitored items complete (transaction %d)", transactionId);
    }


}
