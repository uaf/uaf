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

#include "uaf/client/invocations/browseinvocation.h"

namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::size_t;
    using std::stringstream;
    using std::vector;


    // Constructor
    // =============================================================================================
    BrowseInvocation::BrowseInvocation()
    : uaf::BaseServiceInvocation< uaf::BrowseSettings,
                                   uaf::BrowseRequestTarget,
                                   uaf::BrowseResultTarget >()
    {
        // initialize the view description
        OpcUa_ViewDescription_Initialize(&uaViewDescription_);
    }


    // Destructor
    // =============================================================================================
    BrowseInvocation::~BrowseInvocation()
    {
        // clear the view description
        OpcUa_ViewDescription_Clear(&uaViewDescription_);
    }


    // Fill the synchronous SDK members
    // =============================================================================================
    Status BrowseInvocation::fromSyncUafToSdk(
            const vector<BrowseRequestTarget>&  targets,
            const BrowseSettings&               settings,
            const NamespaceArray&               nameSpaceArray,
            const ServerArray&                  serverArray)
    {
        Status ret;

        // update the uaServiceSettings_
        ret = settings.toSdk(uaServiceSettings_);

        // update the uaMaxReferencesToReturn_
        uaMaxReferencesToReturn_ = settings.maxReferencesToReturn;

        // update the uaViewDescription_
        if (!settings.view.viewId.isNull())
            ret = nameSpaceArray.fillOpcUaNodeId(settings.view.viewId, uaViewDescription_.ViewId);

        // declare the number of targets
        size_t noOfTargets = targets.size();

        // resize the number of uaReadValueIds_
        uaBrowseDescriptions_.create(noOfTargets);

        // initialize the autoBrowsedNextPerTarget_ vector
        autoBrowsedNextPerTarget_.resize(noOfTargets, 0);

        // loop through the targets
        for (size_t i = 0; i < noOfTargets && ret.isGood(); i++)
        {
            // update the node id of the target
            ret = nameSpaceArray.fillOpcUaNodeId(
                    targets[i].address,
                    uaBrowseDescriptions_[i].NodeId);

            // update the reference type id of the target if needed
            if (ret.isGood() && !targets[i].referenceTypeId.isNull())
                ret = nameSpaceArray.fillOpcUaNodeId(
                        targets[i].referenceTypeId,
                        uaBrowseDescriptions_[i].ReferenceTypeId);

            // update the other parameters
            if (ret.isGood())
            {
                // the browse direction
                uaBrowseDescriptions_[i].BrowseDirection = browsedirections::fromUafToSdk(
                        targets[i].browseDirection);

                // include subtypes of the reference type id or not
                if (targets[i].includeSubtypes)
                    uaBrowseDescriptions_[i].IncludeSubtypes = OpcUa_True;
                else
                    uaBrowseDescriptions_[i].IncludeSubtypes = OpcUa_False;

                // the masks
                uaBrowseDescriptions_[i].NodeClassMask = targets[i].nodeClassMask;
                uaBrowseDescriptions_[i].ResultMask = targets[i].resultMask;
            }
        }

        return ret;
    }


    // Fill the asynchronous SDK members
    // =============================================================================================
    Status BrowseInvocation::fromAsyncUafToSdk(
            const vector<BrowseRequestTarget>&  targets,
            const BrowseSettings&               settings,
            const NamespaceArray&               nameSpaceArray,
            const ServerArray&                  serverArray)
    {
        return AsyncInvocationNotSupportedError();
    }


    // Invoke the service synchronously
    // =============================================================================================
    Status BrowseInvocation::invokeSyncSdkService(UaClientSdk::UaSession* uaSession)
    {
        Status ret;

        SdkStatus sdkStatus = uaSession->browseList(
                uaServiceSettings_,
                uaViewDescription_,
                uaMaxReferencesToReturn_,
                uaBrowseDescriptions_,
                uaBrowseResults_,
                uaDiagnosticInfos_);

        if (sdkStatus.isGood())
            ret = uaf::statuscodes::Good;
        else
            ret = BrowseInvocationError(sdkStatus);

        uint32_t autoBrowsedNext   = 0;
        uint32_t maxAutoBrowseNext = this->serviceSettings().maxAutoBrowseNext;

        // do we still have to automatically invoke BrowseNext, or are we finished?
        bool finished = (maxAutoBrowseNext == 0);

        // if we're not finished already, and the initial Browse request was successful, we
        // may need to invoke the BrowseNext service
        while ((!finished) && ret.isGood())
        {
            UaByteStringArray    uaNextContinuationPoints;
            UaBrowseResults      uaNextResults;
            UaDiagnosticInfos    uaNextDiagnosticInfos;
            vector<uint32_t>     ranks; // the rank numbers of the original request

            // loop through the results and append "unfinished" browse results to the
            // variables for the BrowseNext call, as defined above
            for (uint32_t i = 0; i < uaBrowseResults_.length(); i++)
            {
                if (   uaBrowseResults_[i].ContinuationPoint.Length > 0
                    && OpcUa_IsGood(uaBrowseResults_[i].StatusCode))
                {
                    // get the rank number for the BrowseNext call
                    uint32_t current = uaNextContinuationPoints.length();

                    // increase the size of the continuation points for the next BrowseNext call
                    uaNextContinuationPoints.resize(current + 1);

                    // store the rank number of the current result
                    ranks.push_back(i);

                    // update the continuation point
                    UaByteString(uaBrowseResults_[i].ContinuationPoint).copyTo(
                            &uaNextContinuationPoints[current]);

                    // so   ranks[current] = i
                    // and  uaNextContinuationPoints[current] = the non-NULL continuation point
                }
            }

            // if necessary, call the BrowseNext service
            if (uaNextContinuationPoints.length() > 0)
            {
                // perform the BrowseNext call
                SdkStatus sdkNextStatus = uaSession->browseListNext(
                        uaServiceSettings_,
                        OpcUa_False,              // do not release the continuation point yet
                        uaNextContinuationPoints,
                        uaNextResults,
                        uaNextDiagnosticInfos);

                if (sdkNextStatus.isGood())
                    ret = uaf::statuscodes::Good;
                else
                    ret = BrowseNextInvocationError(sdkNextStatus);

                // we've finished an automatic BrowseNext call, so increment the counter
                autoBrowsedNext++;

                // now append the results to the results of the original Browse call
                for (uint32_t iNext = 0; iNext < uaNextResults.length() && ret.isGood(); iNext++)
                {
                    // get the rank number of the original request
                    uint32_t rank = ranks[iNext];

                    // increment the autoBrowsedNext
                    autoBrowsedNextPerTarget_[rank] = autoBrowsedNext;

                    // update the status
                    uaBrowseResults_[rank].StatusCode = uaNextResults[iNext].StatusCode;

                    if (OpcUa_IsGood(uaBrowseResults_[rank].StatusCode))
                    {
                        // update the continuation point
                        UaByteString(uaNextResults[iNext].ContinuationPoint).copyTo(
                                &uaBrowseResults_[rank].ContinuationPoint);

                        // now we want to append the BrowseNext results to the existing Browse
                        // results. This requires some memory copying

                        uint32_t oldDataLength = uaBrowseResults_[rank].NoOfReferences;
                        uint32_t nextDataLength = uaNextResults[iNext].NoOfReferences;

                        // create an array that will hold the existing ("old") data + the data
                        // from the BrowseNext call:
                        UaReferenceDescriptions newData;

                        // already assign the existing data to the new data:
                        newData.attach(uaBrowseResults_[rank].NoOfReferences,
                                       uaBrowseResults_[rank].References);

                        // resize the new data array, so that it can accommodate the data found
                        // during the last BrowseNext call
                        newData.resize(oldDataLength + nextDataLength);

                        // create a shortcut to the ReferenceDescriptions
                        OpcUa_ReferenceDescription* ref = uaNextResults[iNext].References;

                        // now copy the data from the BrowseNext call to the new data array:
                        for (uint32_t i=0, j=oldDataLength; i<nextDataLength; i++, j++)
                        {
                            newData[j].IsForward = ref[i].IsForward;
                            newData[j].NodeClass = ref[i].NodeClass;
                            UaQualifiedName(ref[i].BrowseName).copyTo(&newData[j].BrowseName);
                            UaLocalizedText(ref[i].DisplayName).copyTo(&newData[j].DisplayName);
                            UaExpandedNodeId(ref[i].NodeId).copyTo(&newData[j].NodeId);
                            UaNodeId(ref[i].ReferenceTypeId).copyTo(&newData[j].ReferenceTypeId);
                            UaExpandedNodeId(ref[i].TypeDefinition).copyTo(&newData[j].TypeDefinition);
                        }

                        // update the member variable that holds the browse data
                        uaBrowseResults_[rank].NoOfReferences = newData.length();
                        uaBrowseResults_[rank].References     = newData.detach();
                    }
                }

                // check if we may still need to do another automatic BrowseNext
                finished = autoBrowsedNext >= maxAutoBrowseNext;
            }
            else
            {
                // ok, no more automatic BrowseNext invocations needed!
                finished = true;
            }
        }

        return ret;
    }


    // Invoke the service asynchronously
    // =============================================================================================
    Status BrowseInvocation::invokeAsyncSdkService(
            UaClientSdk::UaSession* uaSession,
            TransactionId           transactionId)
    {
        return AsyncInvocationNotSupportedError();
    }


    // Fill the UAF members
    // =============================================================================================
    Status BrowseInvocation::fromSyncSdkToUaf(
            const NamespaceArray&       nameSpaceArray,
            const ServerArray&          serverArray,
            vector<BrowseResultTarget>& targets)
    {
        // declare the return Status
        Status ret;

        // declare the number of targets, and resize the output parameter accordingly
        uint32_t noOfTargets = uaBrowseResults_.length();
        targets.resize(noOfTargets);

        // check the number of targets
        if (noOfTargets == uaBrowseDescriptions_.length()
            && noOfTargets == autoBrowsedNextPerTarget_.size())
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

                // update the autoBrowsedNext counter
                target.autoBrowsedNext = autoBrowsedNextPerTarget_[i];

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
