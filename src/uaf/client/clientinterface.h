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

#ifndef UAF_CLIENTINTERFACE_H_
#define UAF_CLIENTINTERFACE_H_


// STD
#include <vector>
// SDK
// UAF
#include "uaf/util/pkicertificate.h"
#include "uaf/util/sdkstatus.h"
#include "uaf/client/results/results.h"
#include "uaf/client/sessions/sessioninformation.h"
#include "uaf/client/subscriptions/datachangenotification.h"
#include "uaf/client/subscriptions/eventnotification.h"
#include "uaf/client/subscriptions/keepalivenotification.h"
#include "uaf/client/subscriptions/subscriptioninformation.h"


namespace uaf
{


    /*******************************************************************************************//**
    * The uaf::ClientInterface must be implemented to handle asynchronous calls.
    *
    * @ingroup Client
    ***********************************************************************************************/
    class UAF_EXPORT ClientInterface
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
        virtual void connectionStatusChanged(const uaf::SessionInformation& info) {}


        /**
         * Override this method to handle changes in the status of subscriptions.
         *
         * @param info      The new subscription information.
         */
        virtual void subscriptionStatusChanged(const uaf::SubscriptionInformation& info) {}


        /**
         * Override this method to handle missing notifications.
         *
         * @param info                      Information about the subscription that has missing
         *                                  notifications.
         * @param previousSequenceNumber    The sequence number before the notifications were lost.
         * @param newSequenceNumber         The sequence number after the notifications were lost.
         */
        virtual void notificationsMissing(
                const uaf::SubscriptionInformation& info,
                uint32_t previousSequenceNumber,
                uint32_t newSequenceNumber) {}


        /**
         * Override this method to handle the results of asynchronous read requests.
         *
         * @param result    Read result.
         */
        virtual void readComplete(const uaf::ReadResult& result) {}


        /**
         * Override this method to handle the results of asynchronous write requests.
         *
         * @param result    Write result.
         */
        virtual void writeComplete(const uaf::WriteResult& result) {}


        /**
         * Override this method to handle the results of asynchronous method call requests.
         *
         * @param result    Result of the method call.
         */
        virtual void callComplete(const uaf::MethodCallResult& result) {}


        /**
         * Override this method to handle events.
         *
         * @param notifications Received event notifications.
         */
        virtual void eventsReceived(std::vector<uaf::EventNotification> notifications) {}


        /**
         * Override this method to handle data changes.
         *
         * @param notifications Received data change notifications.
         */
        virtual void dataChangesReceived(std::vector<uaf::DataChangeNotification> notifications) {}


        /**
         * Override this method to handle keep alive notifications.
         *
         * @param notifications Received Keep Alive notifications.
         */
        virtual void keepAliveReceived(uaf::KeepAliveNotification notification) {}


        /**
         * Override this method to trust or reject or the server certificate during connection.
         *
         * By default, uaf::PkiCertificate::Action_Reject will be returned. It means that all
         * untrusted server certificates will be rejected if you do not override this method.
         *
         * If you override this method and return uaf::PkiCertificate::Action_AcceptTemporarily
         * instead, the connection will be accepted but the certificate will *not* be stored by the
         * client (in the trust list, as configured by the uaf::ClientSettings).
         *
         * If you override this method and return uaf::PkiCertificate::Action_AcceptPermanently
         * instead, the connection will be accepted and the certificate will be stored by the
         * client (in the trust list, as configrued by the uaf::ClientSettings).
         *
         * @param certificate   The server certificate.
         * @param cause         The reason why the server certificate was untrusted, according to
         *                      the SDK.
         */
        virtual uaf::PkiCertificate::Action untrustedServerCertificateReceived(
                uaf::PkiCertificate&    certificate,
                const uaf::SdkStatus&   cause)
        { return uaf::PkiCertificate::Action_AcceptTemporarily; }
    };
}


#endif /* UAF_CLIENTINTERFACE_H_ */
