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

#ifndef UAF_TRANSLATEBROWSEPATHSTONODEIDSINVOCATION_H_
#define UAF_TRANSLATEBROWSEPATHSTONODEIDSINVOCATION_H_


// STD
#include <vector>
#include <string>
#include <map>
// SDK
#include "uaclient/uaclientsdk.h"
// UAF
#include "uaf/client/clientexport.h"
#include "uaf/client/invocations/baseserviceinvocation.h"
#include "uaf/client/requests/requests.h"
#include "uaf/client/results/results.h"

namespace uaf
{


    /*******************************************************************************************//**
    * An uaf::ReadResultTarget is the "result target" of the corresponding
    * "request target" that specified the attribute and node etc. to be read.
    *
    * It tells you the read status, the read data, etc.
    *
    * @ingroup ClientInvocations
    ***********************************************************************************************/
    class UAF_EXPORT TranslateBrowsePathsToNodeIdsInvocation
    : public uaf::BaseServiceInvocation< uaf::TranslateBrowsePathsToNodeIdsSettings,
                                          uaf::TranslateBrowsePathsToNodeIdsRequestTarget,
                                          uaf::TranslateBrowsePathsToNodeIdsResultTarget >
    {
    private:


        /**
         * Overridden function from uaf::BaseServiceInvocation.
         */
        uaf::Status fromSyncUafToSdk(
                const std::vector<uaf::TranslateBrowsePathsToNodeIdsRequestTarget>& targets,
                const uaf::TranslateBrowsePathsToNodeIdsSettings&                   settings,
                const uaf::NamespaceArray&                                           nameSpaceArray,
                const uaf::ServerArray&                                              serverArray);


        /**
         * Overridden function from uaf::BaseServiceInvocation.
         */
        uaf::Status fromAsyncUafToSdk(
                const std::vector<uaf::TranslateBrowsePathsToNodeIdsRequestTarget>& targets,
                const uaf::TranslateBrowsePathsToNodeIdsSettings&                   settings,
                const uaf::NamespaceArray&                                           nameSpaceArray,
                const uaf::ServerArray&                                              serverArray);


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
                const uaf::NamespaceArray&                                      nameSpaceArray,
                const uaf::ServerArray&                                         serverArray,
                std::vector<uaf::TranslateBrowsePathsToNodeIdsResultTarget>&   targets);


        // private data members used during the invocation
        UaClientSdk::ServiceSettings    uaServiceSettings_;
        UaBrowsePaths                   uaBrowsePaths_;
        UaBrowsePathResults             uaBrowsePathResults_;
        UaDiagnosticInfos               uaDiagnosticInfos_;

    };

}


#endif /* UAF_TRANSLATEBROWSEPATHSTONODEIDSINVOCATION_H_ */
