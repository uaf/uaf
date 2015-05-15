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


#ifndef UAF_CREATEMONITOREDDATAINVOCATION_H_
#define UAF_CREATEMONITOREDDATAINVOCATION_H_


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

namespace uaf
{


    /*******************************************************************************************//**
    * An uaf::CreateMonitoredDataInvocation wraps the functional SDK code to invoke the
    * CreateMonitoredItem service for monitored data.
    *
    * @ingroup ClientInvocations
    ***********************************************************************************************/
    class UAF_EXPORT CreateMonitoredDataInvocation
    : public uaf::BaseServiceInvocation< uaf::CreateMonitoredDataSettings,
                                          uaf::CreateMonitoredDataRequestTarget,
                                          uaf::CreateMonitoredDataResultTarget >
    {
    public:


        // some public typedefs of handles that are needed for the invocation.
        typedef std::vector<uaf::ClientHandle> ClientHandles;


        /**
         * Set the handles that are needed for the invocation.
         *
         * @param clientHandles:        The client handles, as assigned by the UAF.
         */
        void setHandles(const ClientHandles& clientHandles)
        {
            clientHandles_ = clientHandles;
        }


    private:


        /**
         * Overridden function from uaf::BaseServiceInvocation.
         */
        uaf::Status fromSyncUafToSdk(
                const std::vector<uaf::CreateMonitoredDataRequestTarget>&  targets,
                const uaf::CreateMonitoredDataSettings&                    settings,
                const uaf::NamespaceArray&                                  nameSpaceArray,
                const uaf::ServerArray&                                     serverArray);


        /**
         * Overridden function from uaf::BaseServiceInvocation.
         */
        uaf::Status fromAsyncUafToSdk(
                const std::vector<uaf::CreateMonitoredDataRequestTarget>&  targets,
                const uaf::CreateMonitoredDataSettings&                    settings,
                const uaf::NamespaceArray&                                  nameSpaceArray,
                const uaf::ServerArray&                                     serverArray);


        /**
         * Overridden function from uaf::BaseServiceInvocation.
         */
        uaf::Status invokeSyncSdkService(
                UaClientSdk::UaSubscription* uaSubscription);


        /**
         * Overridden function from uaf::BaseServiceInvocation.
         */
        uaf::Status invokeAsyncSdkService(
                UaClientSdk::UaSubscription* uaSubscription,
                uaf::TransactionId           transactionId);


        /**
         * Overridden function from uaf::BaseServiceInvocation.
         */
        uaf::Status fromSyncSdkToUaf(
                const uaf::NamespaceArray&                          nameSpaceArray,
                const uaf::ServerArray&                             serverArray,
                std::vector<uaf::CreateMonitoredDataResultTarget>& targets);


        // private data members used during the invocation
        OpcUa_TimestampsToReturn        uaTimeStamps_;
        ClientHandles                   clientHandles_;
        UaClientSdk::ServiceSettings    uaServiceSettings_;
        UaMonitoredItemCreateRequests   uaCreateRequests_;
        UaMonitoredItemCreateResults    uaCreateResults_;
    };

}





#endif /* UAF_CREATEMONITOREDDATAINVOCATION_H_ */
