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

#include "uaf/client/invocations/readinvocation.h"

namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;
    using std::vector;


    // Fill the synchronous SDK members
    // =============================================================================================
    Status ReadInvocation::fromSyncUafToSdk(
            const vector<ReadRequestTarget>&    targets,
            const ReadSettings&                 settings,
            const NamespaceArray&               nameSpaceArray,
            const ServerArray&                  serverArray)
    {
        Status ret;

        // update the uaServiceSettings_
        ret = settings.toSdk(uaServiceSettings_);

        // update the uaMaxAge (allow for a rounding error of 1 ms)
        if (settings.maxAgeSec > 0.001)
            uaMaxAge_ = settings.maxAgeSec * 1000.0;
        else
            uaMaxAge_ = 0;

        // ToDo: add support for timestampsToReturn
        uaTimestampsToReturn_ = OpcUa_TimestampsToReturn_Both;

        // declare the number of targets
        size_t noOfTargets = targets.size();

        // resize the number of uaReadValueIds_
        uaReadValueIds_.create(noOfTargets);

        // loop through the targets
        for (size_t i = 0; i < noOfTargets && ret.isGood(); i++)
        {
            // update the node id of the target
            ret = nameSpaceArray.fillOpcUaNodeId(targets[i].address, uaReadValueIds_[i].NodeId);

            // only update the rest of the SDK variables if no error has occurred yet
            if (ret.isGood())
            {
                // update the attribute id of the target
                uaReadValueIds_[i].AttributeId = targets[i].attributeId;

                // update the index range of the target
                // BUGFIX: only do this if needed!
                // Otherwise the OpcUa_String will be initialized and some servers
                // may return BadIndexRangeInvalid errors
                if (!targets[i].indexRange.empty())
                    UaString(targets[i].indexRange.c_str()).copyTo(
                            &(uaReadValueIds_[i].IndexRange));
            }
        }

        return ret;
    }


    // Fill the asynchronous SDK members
    // =============================================================================================
    Status ReadInvocation::fromAsyncUafToSdk(
            const vector<ReadRequestTarget>&    targets,
            const ReadSettings&                 settings,
            const NamespaceArray&               nameSpaceArray,
            const ServerArray&                  serverArray)
    {
        // same as synchronous
        return fromSyncUafToSdk(targets, settings, nameSpaceArray, serverArray);
    }


    // Invoke the service synchronously
    // =============================================================================================
    Status ReadInvocation::invokeSyncSdkService(UaClientSdk::UaSession* uaSession)
    {
        Status ret;

        UaStatus sdkStatus = uaSession->read(
                uaServiceSettings_,
                uaMaxAge_,
                uaTimestampsToReturn_,
                uaReadValueIds_,
                uaDataValues_,
                uaDiagnosticInfos_);

        if (sdkStatus.isGood())
            ret = uaf::statuscodes::Good;
        else
            ret = ReadInvocationError(sdkStatus);

        return ret;
    }


    // Invoke the service asynchronously
    // =============================================================================================
    Status ReadInvocation::invokeAsyncSdkService(
            UaClientSdk::UaSession* uaSession,
            TransactionId           transactionId)
    {
        Status ret;

        UaStatus sdkStatus = uaSession->beginRead(
                uaServiceSettings_,
                uaMaxAge_,
                uaTimestampsToReturn_,
                uaReadValueIds_,
                transactionId);

        if (sdkStatus.isGood())
            ret = uaf::statuscodes::Good;
        else
            ret = BeginReadInvocationError(sdkStatus);

        return ret;
    }


    // Fill the UAF members
    // =============================================================================================
    Status ReadInvocation::fromSyncSdkToUaf(
            const NamespaceArray&       nameSpaceArray,
            const ServerArray&          serverArray,
            vector<ReadResultTarget>&   targets)
    {
        // declare the return Status
        Status ret;

        // declare the number of targets, and resize the output parameter accordingly
        uint32_t noOfTargets = uaDataValues_.length();
        targets.resize(noOfTargets);

        // check the number of targets
        if (noOfTargets == uaReadValueIds_.length())
        {
            for (uint32_t i=0; i<noOfTargets ; i++)
            {
                targets[i].fromSdk(UaDataValue(uaDataValues_[i]));
                nameSpaceArray.fillVariant(targets[i].data);
                serverArray.fillVariant(targets[i].data);

                // update the status
                if (OpcUa_IsGood(uaDataValues_[i].StatusCode))
                    targets[i].status = statuscodes::Good;
                else
                    targets[i].status = ServerCouldNotReadError(SdkStatus(uaDataValues_[i].StatusCode));
            }

            ret = statuscodes::Good;
        }
        else
        {
            ret = UnexpectedError("Number of targets does not match number of targets");
        }

        return ret;
    }




}
