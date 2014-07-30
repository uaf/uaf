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

#ifndef UAFC_CLIENTINTERFACE_H_
#define UAFC_CLIENTINTERFACE_H_


// STD
#include <vector>
// SDK
// UAF
#include "uaf/client/results/results.h"
#include "uaf/client/sessions/sessioninformation.h"
#include "uaf/client/subscriptions/datachangenotification.h"
#include "uaf/client/subscriptions/eventnotification.h"
#include "uaf/client/subscriptions/keepalivenotification.h"
#include "uaf/client/subscriptions/subscriptioninformation.h"


namespace uafc
{


    /*******************************************************************************************//**
    * The uafc::ClientInterface must be implemented to handle asynchronous calls.
    *
    * @ingroup Client
    ***********************************************************************************************/
    class UAFC_EXPORT ClientInterface
    {
    public:


        /**
         * Virtual destructor.
         */
        virtual ~ClientInterface() {}


        /**
         * Override this method to handle changes in the connection status of sessions.
         *
         * @param info      The new session information.
         */
        virtual void connectionStatusChanged(const uafc::SessionInformation& info) {}


        /**
         * Override this method to handle changes in the status of subscriptions.
         *
         * @param info      The new subscription information.
         */
        virtual void subscriptionStatusChanged(const uafc::SubscriptionInformation& info) {}


        /**
         * Override this method to handle missing notifications.
         *
         * @param info                      Information about the subscription that has missing
         *                                  notifications.
         * @param previousSequenceNumber    The sequence number before the notifications were lost.
         * @param newSequenceNumber         The sequence number after the notifications were lost.
         */
        virtual void notificationsMissing(
                const uafc::SubscriptionInformation& info,
                uint32_t previousSequenceNumber,
                uint32_t newSequenceNumber) {}


        /**
         * Override this method to handle the results of asynchronous read requests.
         *
         * @param result    Read result.
         */
        virtual void readComplete(const uafc::ReadResult& result) {}


        /**
         * Override this method to handle the results of asynchronous write requests.
         *
         * @param result    Write result.
         */
        virtual void writeComplete(const uafc::WriteResult& result) {}


        /**
         * Override this method to handle the results of asynchronous method call requests.
         *
         * @param result    Result of the method call.
         */
        virtual void callComplete(const uafc::MethodCallResult& result) {}


        /**
         * Override this method to handle events.
         *
         * @param notifications Received event notifications.
         */
        virtual void eventsReceived(std::vector<uafc::EventNotification> notifications) {}


        /**
         * Override this method to handle data changes.
         *
         * @param notifications Received data change notifications.
         */
        virtual void dataChangesReceived(std::vector<uafc::DataChangeNotification> notifications) {}


        /**
         * Override this method to handle keep alive notifications.
         *
         * @param notifications Received Keep Alive notifications.
         */
        virtual void keepAliveReceived(uafc::KeepAliveNotification notification) {}
    };
}


#endif /* UAFC_CLIENTINTERFACE_H_ */
