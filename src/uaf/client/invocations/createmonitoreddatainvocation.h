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


#ifndef UAFC_CREATEMONITOREDDATAINVOCATION_H_
#define UAFC_CREATEMONITOREDDATAINVOCATION_H_


// STD
#include <vector>
#include <string>
#include <map>
// SDK
#include "uaclient/uaclientsdk.h"
// UAF
#include "uaf/util/monitoringmodes.h"
#include "uaf/util/handles.h"
#include "uaf/client/clientexport.h"
#include "uaf/client/invocations/baseserviceinvocation.h"
#include "uaf/client/requests/requests.h"
#include "uaf/client/results/results.h"

namespace uafc
{


    /*******************************************************************************************//**
    * An uafc::CreateMonitoredDataInvocation wraps the functional SDK code to invoke the
    * CreateMonitoredItem service for monitored data.
    *
    * @ingroup ClientInvocations
    ***********************************************************************************************/
    class UAFC_EXPORT CreateMonitoredDataInvocation
    : public uafc::BaseServiceInvocation< uafc::CreateMonitoredDataSettings,
                                          uafc::CreateMonitoredDataRequestTarget,
                                          uafc::CreateMonitoredDataResultTarget >
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
                const std::vector<uafc::CreateMonitoredDataRequestTarget>&  targets,
                const uafc::CreateMonitoredDataSettings&                    settings,
                const uaf::NamespaceArray&                                  nameSpaceArray,
                const uaf::ServerArray&                                     serverArray);


        /**
         * Overridden function from uafc::BaseServiceInvocation.
         */
        uaf::Status fromAsyncUafToSdk(
                const std::vector<uafc::CreateMonitoredDataRequestTarget>&  targets,
                const uafc::CreateMonitoredDataSettings&                    settings,
                const uaf::NamespaceArray&                                  nameSpaceArray,
                const uaf::ServerArray&                                     serverArray);


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
                const uaf::NamespaceArray&                          nameSpaceArray,
                const uaf::ServerArray&                             serverArray,
                std::vector<uafc::CreateMonitoredDataResultTarget>& targets);


        // private data members used during the invocation
        OpcUa_TimestampsToReturn        uaTimeStamps_;
        ClientHandles                   clientHandles_;
        NotificationHandles             notificationHandles_;
        UaClientSdk::ServiceSettings    uaServiceSettings_;
        UaMonitoredItemCreateRequests   uaCreateRequests_;
        UaMonitoredItemCreateResults    uaCreateResults_;
    };

}





#endif /* UAFC_CREATEMONITOREDDATAINVOCATION_H_ */
