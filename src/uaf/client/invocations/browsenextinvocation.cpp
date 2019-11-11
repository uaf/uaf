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

#include "uaf/client/invocations/browsenextinvocation.h"

namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::size_t;
    using std::stringstream;
    using std::vector;


    // Fill the synchronous SDK members
    // =============================================================================================
    Status BrowseNextInvocation::fromSyncUafToSdk(
            const vector<BrowseNextRequestTarget>&  targets,
            const BrowseNextSettings&               settings,
            const NamespaceArray&                   nameSpaceArray,
            const ServerArray&                      serverArray)
    {
        Status ret;

        // update the uaServiceSettings_
        ret = settings.toSdk(uaServiceSettings_);

        // update the uaReleaseContinuationPoint_
        uaReleaseContinuationPoint_ = (settings.releaseContinuationPoints ? OpcUa_True : OpcUa_False);

        // declare the number of targets
        size_t noOfTargets = targets.size();

        // resize the number of uaReadValueIds_
        uaContinuationPoints_.create(noOfTargets);

        // loop through the targets
        for (size_t i = 0; i < noOfTargets && ret.isGood(); i++)
        {
            targets[i].continuationPoint.toSdk(&uaContinuationPoints_[i]);
        }

        return ret;
    }


    // Fill the asynchronous SDK members
    // =============================================================================================
    Status BrowseNextInvocation::fromAsyncUafToSdk(
            const vector<BrowseNextRequestTarget>&  targets,
            const BrowseNextSettings&               settings,
            const NamespaceArray&               nameSpaceArray,
            const ServerArray&                  serverArray)
    {
        return AsyncInvocationNotSupportedError();
    }


    // Invoke the service synchronously
    // =============================================================================================
    Status BrowseNextInvocation::invokeSyncSdkService(UaClientSdk::UaSession* uaSession)
    {
        Status ret;

        SdkStatus sdkStatus = uaSession->browseListNext(
                uaServiceSettings_,
                uaReleaseContinuationPoint_,
                uaContinuationPoints_,
                uaBrowseResults_,
                uaDiagnosticInfos_);

        if (sdkStatus.isGood())
            ret = uaf::statuscodes::Good;
        else
            ret = BrowseNextInvocationError(sdkStatus);

        return ret;
    }


    // Invoke the service asynchronously
    // =============================================================================================
    Status BrowseNextInvocation::invokeAsyncSdkService(
            UaClientSdk::UaSession* uaSession,
            TransactionId           transactionId)
    {
        return AsyncInvocationNotSupportedError();
    }


    // Fill the UAF members
    // =============================================================================================
    Status BrowseNextInvocation::fromSyncSdkToUaf(
            const NamespaceArray&       nameSpaceArray,
            const ServerArray&          serverArray,
            vector<BrowseNextResultTarget>& targets)
    {
        // declare the return Status
        Status ret;

        // declare the number of targets, and resize the output parameter accordingly
        uint32_t noOfTargets = uaBrowseResults_.length();
        targets.resize(noOfTargets);

        // check the number of targets
        if (noOfTargets == uaContinuationPoints_.length())
        {

            for (uint32_t i=0; i<noOfTargets ; i++)
            {
                auto& target = targets[i];
                const auto& uaBrowseResult = uaBrowseResults_[i];

                // update the status code
                target.opcUaStatusCode = uaBrowseResult.StatusCode;

                // update the status
                if (OpcUa_IsGood(uaBrowseResult.StatusCode))
                {
                    target.status = statuscodes::Good;
                }
                else
                {
                    target.status = ServerCouldNotBrowseError(
                            SdkStatus(uaBrowseResult.StatusCode));
                    continue;
                }

                // update the continuation point
                target.continuationPoint = ByteString(
                        uaBrowseResult.ContinuationPoint.Length,
                        uaBrowseResult.ContinuationPoint.Data);

                if ((uaBrowseResult.NoOfReferences < 0) ||
                    (nullptr == uaBrowseResult.References))
                {
                    continue;
                }

                // update the references
                target.references.resize(
                        static_cast<std::size_t>(uaBrowseResult.NoOfReferences));

                for (int32_t j = 0; j < uaBrowseResult.NoOfReferences; j++)
                {
                    auto& targetReference = target.references[j];
                    const auto& reference = uaBrowseResult.References[j];

                    if (reference.IsForward)
                        targetReference.isForward = true;
                    else
                        targetReference.isForward = false;

                    targetReference.nodeClass = nodeclasses::fromSdkToUaf(
                            reference.NodeClass);

                    targetReference.browseName.fromSdk(
                            UaQualifiedName(reference.BrowseName));

                    targetReference.displayName.fromSdk(
                            UaLocalizedText(reference.DisplayName));

                    Status resolutionStatus;

                    resolutionStatus = nameSpaceArray.fillQualifiedName(
                            reference.BrowseName,
                            targetReference.browseName);

                    if (target.status.isGood() && resolutionStatus.isNotGood())
                        target.status = resolutionStatus;

                    resolutionStatus = nameSpaceArray.fillNodeId(
                            reference.ReferenceTypeId,
                            targetReference.referenceTypeId);

                    if (target.status.isGood() && resolutionStatus.isNotGood())
                        target.status = resolutionStatus;

                    resolutionStatus = nameSpaceArray.fillExpandedNodeId(
                            reference.NodeId,
                            targetReference.nodeId);

                    if (target.status.isGood() && resolutionStatus.isNotGood())
                        target.status = resolutionStatus;

                    resolutionStatus = serverArray.fillExpandedNodeId(
                            reference.NodeId,
                            targetReference.nodeId);

                    if (target.status.isGood() && resolutionStatus.isNotGood())
                        target.status = resolutionStatus;

                    resolutionStatus = nameSpaceArray.fillExpandedNodeId(
                            reference.TypeDefinition,
                            targetReference.typeDefinition);

                    if (target.status.isGood() && resolutionStatus.isNotGood())
                        target.status = resolutionStatus;

                    resolutionStatus = serverArray.fillExpandedNodeId(
                            reference.TypeDefinition,
                            targetReference.typeDefinition);

                    if (target.status.isGood() && resolutionStatus.isNotGood())
                        target.status = resolutionStatus;
                }
            }

            ret = uaf::statuscodes::Good;
        }
        else
        {
            ret = UnexpectedError(
                    "Number of result targets does not match number of request targets,"
                    "or number of automatic BrowseNext counters");
        }

        return ret;
    }


}
