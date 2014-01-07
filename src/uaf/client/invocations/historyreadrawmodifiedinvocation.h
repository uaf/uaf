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


#ifndef UAFC_HISTORYREADRAWMODIFIEDINVOCATION_H_
#define UAFC_HISTORYREADRAWMODIFIEDINVOCATION_H_


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

namespace uafc
{

    /*******************************************************************************************//**
    * An uafc::HistoryReadRawModifiedInvocation wraps the functional SDK code to invoke the
    * HistoryReadRawModified service.
    *
    * @ingroup ClientInvocations
    ***********************************************************************************************/
    class UAFC_EXPORT HistoryReadRawModifiedInvocation
    : public uafc::BaseServiceInvocation< uafc::HistoryReadRawModifiedSettings,
                                          uafc::HistoryReadRawModifiedRequestTarget,
                                          uafc::HistoryReadRawModifiedResultTarget >
    {
    private:


        /**
         * Overridden function from uafc::BaseServiceInvocation.
         */
        uaf::Status fromSyncUafToSdk(
                const std::vector<uafc::HistoryReadRawModifiedRequestTarget>&   targets,
                const uafc::HistoryReadRawModifiedSettings&                     settings,
                const uaf::NamespaceArray&                                      nameSpaceArray,
                const uaf::ServerArray&                                         serverArray);


        /**
         * Overridden function from uafc::BaseServiceInvocation.
         */
        uaf::Status fromAsyncUafToSdk(
                const std::vector<uafc::HistoryReadRawModifiedRequestTarget>&   targets,
                const uafc::HistoryReadRawModifiedSettings&                     settings,
                const uaf::NamespaceArray&                                      nameSpaceArray,
                const uaf::ServerArray&                                         serverArray);


        /**
         * Overridden function from uafc::BaseServiceInvocation.
         */
        uaf::Status invokeSyncSdkService(UaClientSdk::UaSession* uaSession);


        /**
         * Overridden function from uafc::BaseServiceInvocation.
         */
        uaf::Status invokeAsyncSdkService(
                UaClientSdk::UaSession*     uaSession,
                uaf::TransactionId          transactionId);


        /**
         * Overridden function from uafc::BaseServiceInvocation.
         */
        uaf::Status fromSyncSdkToUaf(
                const uaf::NamespaceArray&                              nameSpaceArray,
                const uaf::ServerArray&                                 serverArray,
                std::vector<uafc::HistoryReadRawModifiedResultTarget>&  targets);


        // private data members used during the invocation
        UaClientSdk::ServiceSettings                uaServiceSettings_;
        UaClientSdk::HistoryReadRawModifiedContext  uaContext_;
        UaHistoryReadValueIds                       uaNodesToRead_;
        UaClientSdk::HistoryReadDataResults         uaResults_;
        std::vector<uint32_t>                       autoReadMorePerTarget_;

        // onwards from version 1.4 we require a UaDiagnosticInfos object for the service calls
        UaDiagnosticInfos                           uaDiagnosticInfos_;
    };

}





#endif /* UAFC_HISTORYREADRAWMODIFIEDINVOCATION_H_ */
