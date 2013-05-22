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

namespace uafc
{
    using namespace uaf;
    using namespace uafc;
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
        return Status(statuscodes::UnsupportedError, "Asynchronous BrowseNext is not supported");
    }


    // Invoke the service synchronously
    // =============================================================================================
    Status BrowseNextInvocation::invokeSyncSdkService(UaClientSdk::UaSession* uaSession)
    {
        Status ret;

        UaStatus uaStatus = uaSession->browseListNext(
                uaServiceSettings_,
                uaReleaseContinuationPoint_,
                uaContinuationPoints_,
                uaBrowseResults_,
                uaDiagnosticInfos_);

        ret.fromSdk(uaStatus.statusCode(), "Synchronous BrowseNext invocation failed");

        return ret;
    }


    // Invoke the service asynchronously
    // =============================================================================================
    Status BrowseNextInvocation::invokeAsyncSdkService(
            UaClientSdk::UaSession* uaSession,
            TransactionId           transactionId)
    {
        return Status(statuscodes::UnsupportedError, "Asynchronous BrowseNext is not supported");
    }


    // Fill the UAF members
    // =============================================================================================
    Status BrowseNextInvocation::fromSyncSdkToUaf(
            const NamespaceArray&           nameSpaceArray,
            const ServerArray&              serverArray,
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
                // update the status
                targets[i].status.fromSdk(uaBrowseResults_[i].StatusCode,
                                          "The server reported a browse failure");

                // update the continuation point
                targets[i].continuationPoint = ByteString(
                        uaBrowseResults_[i].ContinuationPoint.Length,
                        uaBrowseResults_[i].ContinuationPoint.Data);

                // update the references
                targets[i].references.resize(uaBrowseResults_[i].NoOfReferences);

                for (int32_t j = 0; j < uaBrowseResults_[i].NoOfReferences; j++)
                {
                    if (uaBrowseResults_[i].References[j].IsForward)
                        targets[i].references[j].isForward = true;
                    else
                        targets[i].references[j].isForward = false;

                    targets[i].references[j].nodeClass = nodeclasses::fromSdkToUaf(
                            uaBrowseResults_[i].References[j].NodeClass);

                    targets[i].references[j].browseName.fromSdk(
                            UaQualifiedName(uaBrowseResults_[i].References[j].BrowseName));

                    targets[i].references[j].displayName.fromSdk(
                            UaLocalizedText(uaBrowseResults_[i].References[j].DisplayName));

                    Status resolutionStatus;

                    resolutionStatus = nameSpaceArray.fillQualifiedName(
                            uaBrowseResults_[i].References[j].BrowseName,
                            targets[i].references[j].browseName);

                    if (targets[i].status.isGood() && resolutionStatus.isNotGood())
                        targets[i].status = resolutionStatus;

                    resolutionStatus = nameSpaceArray.fillNodeId(
                            uaBrowseResults_[i].References[j].ReferenceTypeId,
                            targets[i].references[j].referenceTypeId);

                    if (targets[i].status.isGood() && resolutionStatus.isNotGood())
                        targets[i].status = resolutionStatus;

                    resolutionStatus = nameSpaceArray.fillExpandedNodeId(
                            uaBrowseResults_[i].References[j].NodeId,
                            targets[i].references[j].nodeId);

                    if (targets[i].status.isGood() && resolutionStatus.isNotGood())
                        targets[i].status = resolutionStatus;

                    resolutionStatus = serverArray.updateServerUri(
                            uaBrowseResults_[i].References[j].NodeId,
                            targets[i].references[j].nodeId);

                    if (targets[i].status.isGood() && resolutionStatus.isNotGood())
                        targets[i].status = resolutionStatus;

                    resolutionStatus = nameSpaceArray.fillExpandedNodeId(
                            uaBrowseResults_[i].References[j].TypeDefinition,
                            targets[i].references[j].typeDefinition);

                    if (targets[i].status.isGood() && resolutionStatus.isNotGood())
                        targets[i].status = resolutionStatus;

                    resolutionStatus = serverArray.updateServerUri(
                            uaBrowseResults_[i].References[j].TypeDefinition,
                            targets[i].references[j].typeDefinition);

                    if (targets[i].status.isGood() && resolutionStatus.isNotGood())
                        targets[i].status = resolutionStatus;
                }
            }

            ret.setGood();
        }
        else
        {
            ret.setStatus(statuscodes::UnexpectedError,
                          "Number of result targets does not match number of request targets,"
                          "or number of automatic BrowseNext counters");
        }

        return ret;
    }




}
