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


#ifndef UAF_METHODCALLINVOCATION_H_
#define UAF_METHODCALLINVOCATION_H_


// STD
#include <vector>
#include <string>
#include <map>
// SDK
#include "uaclient/uaclientsdk.h"
// UAF
#include "uaf/client/clientexport.h"
#include "uaf/client/requests/requests.h"
#include "uaf/client/results/results.h"
#include "uaf/client/invocations/baseserviceinvocation.h"

namespace uaf
{


    /*******************************************************************************************//**
    * An uaf::MethodCallInvocation wraps the functional SDK code to invoke the MethodCall service.
    *
    * @ingroup ClientInvocations
    ***********************************************************************************************/
    class UAF_EXPORT MethodCallInvocation
    : public uaf::BaseServiceInvocation< uaf::MethodCallSettings,
                                          uaf::MethodCallRequestTarget,
                                          uaf::MethodCallResultTarget >
    {

    private:


        /**
         * Overridden function from uaf::BaseServiceInvocation.
         */
        uaf::Status fromSyncUafToSdk(
                const std::vector<uaf::MethodCallRequestTarget>&   targets,
                const uaf::MethodCallSettings&                     settings,
                const uaf::NamespaceArray&                          nameSpaceArray,
                const uaf::ServerArray&                             serverArray);


        /**
         * Overridden function from uaf::BaseServiceInvocation.
         */
        uaf::Status fromAsyncUafToSdk(
                const std::vector<uaf::MethodCallRequestTarget>&   targets,
                const uaf::MethodCallSettings&                     settings,
                const uaf::NamespaceArray&                          nameSpaceArray,
                const uaf::ServerArray&                             serverArray);


        /**
         * Overridden function from uaf::BaseServiceInvocation.
         */
        uaf::Status invokeSyncSdkService(UaClientSdk::UaSession* uaSession);


        /**
         * Overridden function from uaf::BaseServiceInvocation.
         */
        uaf::Status invokeAsyncSdkService(
                UaClientSdk::UaSession*     uaSession,
                uaf::TransactionId          transactionId);


        /**
         * Overridden function from uaf::BaseServiceInvocation.
         */
        uaf::Status fromSyncSdkToUaf(
                const uaf::NamespaceArray&                  nameSpaceArray,
                const uaf::ServerArray&                     serverArray,
                std::vector<uaf::MethodCallResultTarget>&  targets);


        // private data members used during the invocation
        UaClientSdk::ServiceSettings    uaServiceSettings_;
        UaClientSdk::CallIn             uaCallIn_;
        UaCallMethodRequests            uaCallMethodRequests_;
        UaCallMethodResults             uaCallMethodResults_;
        UaDiagnosticInfos               uaDiagnosticInfos_;

    };

}





#endif /* UAF_METHODCALLINVOCATION_H_ */
