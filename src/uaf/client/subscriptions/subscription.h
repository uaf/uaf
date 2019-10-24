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

#ifndef UAF_SUBSCRIPTION_H_
#define UAF_SUBSCRIPTION_H_

// STD
#include <string>
#include <sstream>
#include <vector>
// SDK
#include "uaclientcpp/uaclientsdk.h"
#include "uaclientcpp/uasession.h"
#include "uaclientcpp/uasubscription.h"
#include "uabasecpp/uastring.h"
// UAF
#include "uaf/util/status.h"
#include "uaf/util/logger.h"
#include "uaf/util/handles.h"
#include "uaf/util/constants.h"
#include "uaf/client/clientexport.h"
#include "uaf/client/clientinterface.h"
#include "uaf/client/settings/subscriptionsettings.h"
#include "uaf/client/subscriptions/monitoreditem.h"
#include "uaf/client/subscriptions/subscriptionstates.h"
#include "uaf/client/subscriptions/subscriptioninformation.h"
#include "uaf/client/subscriptions/monitorediteminformation.h"
#include "uaf/client/subscriptions/keepalivenotification.h"
#include "uaf/client/database/database.h"
#include "uaf/client/invocations/invocations.h"





namespace uaf
{

    /*******************************************************************************************//**
    * An uaf::Subscription wraps an SDK Subscription instance and adds some functionality.
    *
    * @ingroup ClientSubscriptions
    ***********************************************************************************************/
    class UAF_EXPORT Subscription
    {
    public:

        /**
         * Construct a subscription.
         *
         * @param loggerFactory             Logger factory to log all messages to.
         * @param subscriptionSettings      Settings of the subscription.
         * @param clientSubscriptionHandle  Client handle of the subscription (unique per
         *                                  UaSubscriptionCallback instance, so in the case of UAF,
         *                                  also unique per session).
         * @param clientConnectionId        The id of the session hosting the subscription.
         * @param uaSession                 SDK Session object hosting the subscription.
         * @param uaSubscriptionCallback    SDK Subscription callback to call.
         * @param clientInterface           The client interface to pass the callbacks to.
         * @param database                  Client database.
         */
        Subscription(
                uaf::LoggerFactory*                     loggerFactory,
                const uaf::SubscriptionSettings&       subscriptionSettings,
                uaf::ClientSubscriptionHandle           clientSubscriptionHandle,
                uaf::ClientConnectionId                 clientConnectionId,
                UaClientSdk::UaSession*                 uaSession,
                UaClientSdk::UaSubscriptionCallback*    uaSubscriptionCallback,
                uaf::ClientInterface*                  clientInterface,
                uaf::Database*                         database);


        /**
         * Destruct the subscription.
         */
        virtual ~Subscription();


        /**
         * Establish the subscription between client and server.
         *
         * @return  Good if the subscription was established.
         */
        uaf::Status createSubscription();


        /**
         * Delete the subscription between client and server.
         *
         * @param deleteRequest  True to delete the persistent request that
         *                       created the subscription.
         * @return  Good if the subscription was deleted.
         */
        uaf::Status deleteSubscription(bool deletePersistentRequest = false);


        /**
         * Check if the subscription is established between client and server.
         *
         * @return  True if the subscription is established.
         */
        bool isCreated() const;



        /**
         * Tell the subscription that it's still alive.
         */
        void keepAlive();


        /**
         * Get some information about the subscription.
         *
         * @return  The information of the subscription.
         */
        uaf::SubscriptionInformation subscriptionInformation() const;


        /**
         * Get some information about the specified monitored item.
         *
         * @param clientHandle                  The handle identifying the monitored item.
         * @param monitoredItemInformation      Output parameter: the requested information.
         * @return                              True if the monitored item was found, False if not.
         */
         bool monitoredItemInformation(
                uaf::ClientHandle               clientHandle,
                uaf::MonitoredItemInformation& monitoredItemInformation);


        /**
         * Called every time a monitored item has changed,
         * overridden from UaSubscriptionCallback.
         */
        virtual void dataChange(
                const UaDataNotifications &dataNotifications,
                const UaDiagnosticInfos &diagnosticInfos);


        /**
         * Called every new events have been received, overridden from UaSubscriptionCallback.
         */
        virtual void newEvents(UaEventFieldLists &eventFieldList);


        /**
         * Set the publishing mode of the subscription.
         *
         * @param publishingEnabled         True to enable the subscription, false if not.
         * @param serviceSettings           The service settings to be used.
         * @return                          Result of the service call.
         */
        uaf::Status setPublishingMode(
                bool                           publishingEnabled,
                const uaf::ServiceSettings&   serviceSettings);


       /**
        * Set the monitoring mode for the given ClientHandles, if they are owned by the
        * subscription.
        *
        * @param clientHandles     The ClientHandles of the monitored items to be affected.
        * @param monitoringMode    The new monitoring mode.
        * @param serviceSettings   The service settings to be used.
        * @param results           A vector of statuses (one result for each ClientHandle).
        * @return                  The immediate result of the service call.
        */
        uaf::Status setMonitoringModeIfNeeded(
               std::vector<uaf::ClientHandle>          clientHandles,
               uaf::monitoringmodes::MonitoringMode    monitoringMode,
               const uaf::ServiceSettings&            serviceSettings,
               std::vector<uaf::Status>&               results);


        /**
         * Execute a CreateMonitoredData service invocation.
         *
         * @param invocation        The service invocation to execute.
         * @param nameSpaceArray    The name space array that was fetched by the client.
         * @param serverArray       The server array that was fetched by the client.
         * @return                  Good if there was no error on the client side.
         */
        uaf::Status invokeService(
                uaf::CreateMonitoredDataInvocation& invocation,
                const uaf::NamespaceArray&           nameSpaceArray,
                const uaf::ServerArray&              serverArray)
        {
            uaf::Status ret;

            // create a vector to store the ClientHandles
            std::vector<uaf::ClientHandle> clientHandles;

            for (std::size_t i = 0; i < invocation.requestTargets().size(); i++)
            {
                uaf::ClientHandle clientHandle = invocation.resultTargets()[i].clientHandle;

                // create a new unique client handle if necessary
                if (clientHandle == uaf::constants::CLIENTHANDLE_NOT_ASSIGNED)
                    clientHandle = database_->createUniqueClientHandle();

                // store the monitored item
                monitoredItemsMap_[clientHandle].settings = uaf::MonitoredItemSettings(
                        invocation.requestTargets()[i].samplingIntervalSec,
                        invocation.requestTargets()[i].queueSize,
                        invocation.requestTargets()[i].discardOldest,
                        invocation.requestTargets()[i].dataChangeFilter);
                monitoredItemsMap_[clientHandle].requestHandle = invocation.requestHandle();
                monitoredItemsMap_[clientHandle].targetRank    = invocation.ranks()[i];

                // store the new client handle
                clientHandles.push_back(clientHandle);
            }

            // provide the clientHandles to the invocation
            invocation.setHandles(clientHandles);

            // create the monitored items on the server side, by invoking the service
            ret = invocation.invoke(uaSubscription_, nameSpaceArray, serverArray, logger_);

            // store the MonitoredItemId, revised sampling interval etc.
            for (std::size_t i = 0; i < invocation.resultTargets().size(); i++)
            {
                uaf::ClientHandle clientHandle = invocation.resultTargets()[i].clientHandle;

                monitoredItemsMap_[clientHandle].revisedQueueSize \
                    = invocation.resultTargets()[i].revisedQueueSize;
                monitoredItemsMap_[clientHandle].revisedSamplingIntervalSec \
                    = invocation.resultTargets()[i].revisedSamplingIntervalSec;
                monitoredItemsMap_[clientHandle].monitoredItemId \
                    = invocation.resultTargets()[i].monitoredItemId;
            }


            return ret;
        }


        /**
         * Execute a CreateMonitoredEvents service invocation.
         *
         * @param invocation        The service invocation to execute.
         * @param nameSpaceArray    The name space array that was fetched by the client.
         * @param serverArray       The server array that was fetched by the client.
         * @return                  Good if there was no error on the client side.
         */
        uaf::Status invokeService(
                uaf::CreateMonitoredEventsInvocation& invocation,
                const uaf::NamespaceArray&             nameSpaceArray,
                const uaf::ServerArray&                serverArray)
        {
            uaf::Status ret;

            // create a vector to store the ClientHandles
            std::vector<uaf::ClientHandle> clientHandles;

            for (std::size_t i = 0; i < invocation.requestTargets().size(); i++)
            {
                uaf::ClientHandle clientHandle = invocation.resultTargets()[i].clientHandle;

                // create a new unique client handle if necessary
                if (clientHandle == uaf::constants::CLIENTHANDLE_NOT_ASSIGNED)
                    clientHandle = database_->createUniqueClientHandle();

                // store the monitored item
                monitoredItemsMap_[clientHandle].settings = uaf::MonitoredItemSettings(
                        invocation.requestTargets()[i].samplingIntervalSec,
                        invocation.requestTargets()[i].queueSize,
                        invocation.requestTargets()[i].discardOldest,
                        invocation.requestTargets()[i].eventFilter);
                monitoredItemsMap_[clientHandle].requestHandle = invocation.requestHandle();
                monitoredItemsMap_[clientHandle].targetRank    = invocation.ranks()[i];

                // store the new client handle
                clientHandles.push_back(clientHandle);
            }

            // provide the clientHandles to the invocation
            invocation.setHandles(clientHandles);

            // create the monitored items on the server side, by invoking the service
            ret = invocation.invoke(uaSubscription_, nameSpaceArray, serverArray, logger_);

            // store the MonitoredItemId, revised sampling interval etc.
            for (std::size_t i = 0; i < invocation.resultTargets().size(); i++)
            {
                uaf::ClientHandle clientHandle = invocation.resultTargets()[i].clientHandle;

                monitoredItemsMap_[clientHandle].revisedQueueSize \
                    = invocation.resultTargets()[i].revisedQueueSize;
                monitoredItemsMap_[clientHandle].revisedSamplingIntervalSec \
                    = invocation.resultTargets()[i].revisedSamplingIntervalSec;
                monitoredItemsMap_[clientHandle].monitoredItemId \
                    = invocation.resultTargets()[i].monitoredItemId;
            }

            return ret;
        }


        /**
         * Get the ClientSubscriptionHandle.
         *
         * @return  The ID of the subscription.
         */
        uaf::ClientSubscriptionHandle clientSubscriptionHandle()
        { return clientSubscriptionHandle_; };


        /**
         * Get the settings of the subscription.
         *
         * @return  The settings of the subscription.
         */
        uaf::SubscriptionSettings subscriptionSettings()
        { return subscriptionSettings_; };


        /**
         * Get the current status of the subscription.
         *
         * @return  The current status of the subscription.
         */
        uaf::subscriptionstates::SubscriptionState subscriptionState()
        { return subscriptionState_; }


        /**
         * Change the status of the subscription.
         *
         * @param subscriptionState    The new status of the subscription.
         */
        void setSubscriptionState(uaf::subscriptionstates::SubscriptionState subscriptionState);



    private:


        DISALLOW_COPY_AND_ASSIGN(Subscription);


        // a private typedef for the container that will hold the monitored items.
        typedef std::map<uaf::ClientHandle, uaf::MonitoredItem> MonitoredItemsMap;


        // logger of the subscription
        uaf::Logger*                                logger_;
        // SDK session instance
        UaClientSdk::UaSession*                     uaSession_;
        // SDK subscription instance
        UaClientSdk::UaSubscription*                uaSubscription_;
        // SDK subscription callback
        UaClientSdk::UaSubscriptionCallback*        uaSubscriptionCallback_;
        // the settings of the subscription
        uaf::SubscriptionSettings                  subscriptionSettings_;
        // the client handle of the subscription
        uaf::ClientSubscriptionHandle               clientSubscriptionHandle_;
        // the connection ID of the uaf::Session instance that hosts this subscription.
        uaf::ClientConnectionId                     clientConnectionId_;
        // the current status of the subscription
        uaf::subscriptionstates::SubscriptionState subscriptionState_;
        // the shared client database
        uaf::Database*                             database_;

        // the RequesterInterface to call when asynchronous messages are received
        uaf::ClientInterface*                      clientInterface_;

        // the current monitored item handle (gets incremented every time!) and its mutex.
        uaf::ClientHandle                           clientHandle_;
        UaMutex                                     clientHandleMutex_;

        // the container that will hold the monitored items, and its mutex.
        MonitoredItemsMap                           monitoredItemsMap_;
        UaMutex                                     monitoredItemsMapMutex_;



    };
}

#endif /* UAF_SUBSCRIPTION_H_ */
