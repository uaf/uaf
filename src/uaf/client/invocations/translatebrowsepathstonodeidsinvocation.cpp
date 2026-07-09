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

#include "uaf/client/invocations/translatebrowsepathstonodeidsinvocation.h"

namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;
    using std::vector;


    // Fill the synchronous SDK members
    // =============================================================================================
    Status TranslateBrowsePathsToNodeIdsInvocation::fromSyncUafToSdk(
            const vector<TranslateBrowsePathsToNodeIdsRequestTarget>&   targets,
            const TranslateBrowsePathsToNodeIdsSettings&                settings,
            const NamespaceArray&                                       nameSpaceArray,
            const ServerArray&                                          serverArray)
    {
        Status ret;

        // update the uaServiceSettings_
        ret = settings.toSdk(uaServiceSettings_);

        // declare the number of targets
        size_t noOfTargets = targets.size();

        // resize the number of uaReadValueIds_
        uaBrowsePaths_.create(noOfTargets);

        // loop through the targets
        for (size_t i = 0; i < noOfTargets && ret.isGood(); i++)
        {
            // get the starting ExpandedNodeId and the elements of the relative path
            vector<RelativePathElement> elements = targets[i].browsePath.relativePath;
            ExpandedNodeId startingNodeId        = targets[i].browsePath.startingExpandedNodeId;

            // declare and resize the "relative path elements" part of the uaBrowsePaths
            UaRelativePathElements uaElements;
            uaElements.create(elements.size());

            // update the node id of the target
            ret = nameSpaceArray.fillOpcUaNodeId(
                    startingNodeId.nodeId(),
                    uaBrowsePaths_[i].StartingNode);

            // only update the rest of the SDK variables if no error has occurred yet
            if (ret.isGood())
            {
                // Loop through the path elements for as long as the elements can be updated without
                // problems.
                // In case an element could not be resolved, we remember its index (because we will
                // be able to let the server translate the part of the path that we can resolve).
                Status elementsStatus(statuscodes::Good);
                uint32_t index = 0;

                while (index < elements.size() && elementsStatus.isGood())
                {
                    // update uaElements[index]
                    elementsStatus = nameSpaceArray.fillOpcUaRelativePathElement(
                            elements[index],
                            uaElements[index]);

                    if (elementsStatus.isGood())
                        index++;
                }

                // we now resize the uaElements to include all resolved elements
                uaElements.resize(index);
            }

            // continue if everything went fine, and if we have a valid path of at least one element
            if (ret.isGood() && uaElements.length() > 0)
            {
                // update the uaBrowsePaths[0].RelativePath
                uaBrowsePaths_[i].RelativePath.NoOfElements = uaElements.length();
                uaBrowsePaths_[i].RelativePath.Elements     = uaElements.detach();
            }
        }

        return ret;
    }


    // Fill the asynchronous SDK members
    // =============================================================================================
    Status TranslateBrowsePathsToNodeIdsInvocation::fromAsyncUafToSdk(
            const vector<TranslateBrowsePathsToNodeIdsRequestTarget>&   targets,
            const TranslateBrowsePathsToNodeIdsSettings&                settings,
            const NamespaceArray&                                       nameSpaceArray,
            const ServerArray&                                          serverArray)
    {
        return AsyncInvocationNotSupportedError();
    }


    // Invoke the service synchronously
    // =============================================================================================
    Status TranslateBrowsePathsToNodeIdsInvocation::invokeSyncSdkService(
            UaClientSdk::UaSession* uaSession)
    {
        Status ret;

        SdkStatus sdkStatus = uaSession->translateBrowsePathsToNodeIds(
                uaServiceSettings_,
                uaBrowsePaths_,
                uaBrowsePathResults_,
                uaDiagnosticInfos_);

        if (sdkStatus.isGood())
            ret = uaf::statuscodes::Good;
        else
            ret = TranslateBrowsePathsToNodeIdsInvocationError(sdkStatus);

        return ret;
    }


    // Invoke the service asynchronously
    // =============================================================================================
    Status TranslateBrowsePathsToNodeIdsInvocation::invokeAsyncSdkService(
            UaClientSdk::UaSession* uaSession,
            TransactionId           transactionId)
    {
        return AsyncInvocationNotSupportedError();
    }


    // Fill the UAF members
    // =============================================================================================
    Status TranslateBrowsePathsToNodeIdsInvocation::fromSyncSdkToUaf(
            const NamespaceArray&                               nameSpaceArray,
            const ServerArray&                                  serverArray,
            vector<TranslateBrowsePathsToNodeIdsResultTarget>&  targets)
    {
        // declare the return Status
        Status ret;

        // declare the number of request targets and resize the output parameter
        uint32_t noOfRequestTargets = uaBrowsePaths_.length();
        targets.resize(noOfRequestTargets);

        // check the number of targets
        if (noOfRequestTargets == uaBrowsePathResults_.length())
        {

            // loop through the targets
            for (uint32_t i = 0; i < noOfRequestTargets; i++)
            {

                // update the status
                if (OpcUa_IsGood(uaBrowsePathResults_[i].StatusCode))
                    targets[i].status = statuscodes::Good;
                else
                    targets[i].status = ServerCouldNotTranslateBrowsePathsToNodeIdsError(
                            SdkStatus(uaBrowsePathResults_[i].StatusCode));

                // update the status code
                targets[i].opcUaStatusCode = uaBrowsePathResults_[i].StatusCode;

                // Make sure we don't try to process an empty or null array of target results.
                if(uaBrowsePathResults_[i].NoOfTargets <= 0)
                    continue;

                // declare the number of "targets of the current ResultTarget"
                uint32_t noOfResultTargetTargets = uaBrowsePathResults_[i].NoOfTargets;

                // reserve space for the "targets of the current ResultTarget"
                targets[i].expandedNodeIds.reserve(noOfResultTargetTargets);
                targets[i].remainingPathIndexes.reserve(noOfResultTargetTargets);

                for (uint32_t j=0; j < noOfResultTargetTargets && targets[i].status.isNotBad(); j++)
                {

                    // declare the server index
                    ServerIndex index = uaBrowsePathResults_[i].Targets[j].TargetId.ServerIndex;

                    // try to get the serverUri
                    string serverUri;
                    bool serverUriFound = serverArray.findServerUri(index, serverUri);

                    // try to fill the nodeId
                    NodeId nodeId;
                    Status nodeIdStatus = nameSpaceArray.fillNodeId(
                            uaBrowsePathResults_[i].Targets[j].TargetId.NodeId,
                            nodeId);

                    // add the remainingPathIndex
                    targets[i].remainingPathIndexes.push_back(
                            uaBrowsePathResults_[i].Targets[j].RemainingPathIndex);

                    if (nodeIdStatus.isGood())
                    {
                        if (serverUriFound)
                        {
                            // update the ExpandedNodeId
                            targets[i].expandedNodeIds.push_back(
                                    ExpandedNodeId(nodeId, serverUri, index));
                            // leave the status to good or to uncertain
                        }
                        else
                        {
                            // update the status
                            targets[i].status = uaf::UnknownServerIndexError();
                        }
                    }
                    else
                    {
                        if (serverUriFound)
                        {
                            // update the status
                            targets[i].status = nodeIdStatus;
                        }
                        else
                        {
                            // update the status
                            targets[i].status = uaf::UnknownNamespaceIndexAndServerIndexError();
                        }
                    }
                }
            }

            ret = uaf::statuscodes::Good;
        }
        else
        {
            ret = uaf::UnexpectedError("Number of targets does not match number of targets");
        }

        return ret;
    }


}
