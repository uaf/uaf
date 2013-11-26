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


#ifndef UAFC_CREATEMONITOREDEVENTSINVOCATION_H_
#define UAFC_CREATEMONITOREDEVENTSINVOCATION_H_


// STD
#include <vector>
#include <string>
#include <map>
// SDK
#include "uabase/uaeventfilter.h"
#include "uaclient/uaclientsdk.h"
// UAF
#include "uaf/client/clientexport.h"
#include "uaf/client/requests/requests.h"
#include "uaf/client/results/results.h"
#include "uaf/client/invocations/baseserviceinvocation.h"

namespace uafc
{


    /*******************************************************************************************//**
    * An uafc::CreateMonitoredEventsInvocation wraps the functional SDK code to invoke the
    * CreateMonitoredItem service for monitored events.
    *
    * @ingroup ClientInvocations
    ***********************************************************************************************/
    class UAFC_EXPORT CreateMonitoredEventsInvocation
    : public uafc::BaseServiceInvocation< uafc::CreateMonitoredEventsSettings,
                                          uafc::CreateMonitoredEventsRequestTarget,
                                          uafc::CreateMonitoredEventsResultTarget >
    {
    public:


        // some public typedefs of handles that are needed for the invocation.
        typedef std::vector<uaf::ClientMonitoredItemHandle> ClientHandles;
        typedef std::vector<uaf::NotificationHandle>        NotificationHandles;


        /**
         * Set the handles that are needed for the invocation.
         *
         * @param clientHandles:        The client handles, as assigned by the UAF.
         * @param notificationHandles:  The notification handles, as assigned by the UAF.
         */
        void setHandles(
                const ClientHandles&        clientHandles,
                const NotificationHandles&  notificationHandles)
        {
            clientHandles_       = clientHandles;
            notificationHandles_ = notificationHandles;
        }


    private:


        /**
         * Overridden function from uafc::BaseServiceInvocation.
         */
        uaf::Status fromSyncUafToSdk(
                const std::vector<uafc::CreateMonitoredEventsRequestTarget>&    targets,
                const uafc::CreateMonitoredEventsSettings&                      settings,
                const uaf::NamespaceArray&                                      nameSpaceArray,
                const uaf::ServerArray&                                         serverArray);


        /**
         * Overridden function from uafc::BaseServiceInvocation.
         */
        uaf::Status fromAsyncUafToSdk(
                const std::vector<uafc::CreateMonitoredEventsRequestTarget>&    targets,
                const uafc::CreateMonitoredEventsSettings&                      settings,
                const uaf::NamespaceArray&                                      nameSpaceArray,
                const uaf::ServerArray&                                         serverArray);


        /**
         * Overridden function from uafc::BaseServiceInvocation.
         */
        uaf::Status invokeSyncSdkService(
                UaClientSdk::UaSubscription* uaSubscription);


        /**
         * Overridden function from uafc::BaseServiceInvocation.
         */
        uaf::Status invokeAsyncSdkService(
                UaClientSdk::UaSubscription* uaSubscription,
                uaf::TransactionId           transactionId);


        /**
         * Overridden function from uafc::BaseServiceInvocation.
         */
        uaf::Status fromSyncSdkToUaf(
                const uaf::NamespaceArray&                            nameSpaceArray,
                const uaf::ServerArray&                               serverArray,
                std::vector<uafc::CreateMonitoredEventsResultTarget>& targets);


        // private data members used during the invocation
        OpcUa_TimestampsToReturn        uaTimeStamps_;
        ClientHandles                   clientHandles_;
        NotificationHandles             notificationHandles_;
        UaClientSdk::ServiceSettings    uaServiceSettings_;
        UaMonitoredItemCreateRequests   uaCreateRequests_;
        UaMonitoredItemCreateResults    uaCreateResults_;
    };

}





#endif /* UAFC_CREATEMONITOREDEVENTSINVOCATION_H_ */
