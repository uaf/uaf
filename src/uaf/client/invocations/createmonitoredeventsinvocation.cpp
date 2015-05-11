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

#include "uaf/client/invocations/createmonitoredeventsinvocation.h"

namespace uaf
{
    using namespace uaf;
    using namespace uaf::monitoringmodes;
    using std::string;
    using std::stringstream;
    using std::vector;


    // Fill the synchronous SDK members
    // =============================================================================================
    Status CreateMonitoredEventsInvocation::fromSyncUafToSdk(
            const vector<CreateMonitoredEventsRequestTarget>&   targets,
            const CreateMonitoredEventsSettings&                settings,
            const NamespaceArray&                               nameSpaceArray,
            const ServerArray&                                  serverArray)
    {
        Status ret;

        // update the uaServiceSettings_
        ret = settings.toSdk(uaServiceSettings_);

        // ToDo update the timestampstoreturn
        uaTimeStamps_ = OpcUa_TimestampsToReturn_Both;

        // declare the number of targets
        size_t noOfTargets = targets.size();

        // resize the number of requests
        uaCreateRequests_.resize(noOfTargets);

        // check if the client handles have been set correctly
        if (clientHandles_.size() == noOfTargets)
            ret = statuscodes::Good;
        else
            ret = UnexpectedError("Handles have not been set correctly!");

        // loop through the targets
        for (size_t i = 0; i < noOfTargets && ret.isGood(); i++)
        {
            // set the NodeId of the item to monitor
            ret = nameSpaceArray.fillOpcUaNodeId(
                    targets[i].address,
                    uaCreateRequests_[i].ItemToMonitor.NodeId);

            if (ret.isGood())
            {
                // convert the relevant UAF properties to SDK properties
                OpcUa_MonitoringMode mode     = fromUafToSdk(targets[i].monitoringMode);
                OpcUa_Double samplingInterval = targets[i].samplingIntervalSec * 1000;
                OpcUa_Boolean discardOldest   = targets[i].discardOldest;

                // set the other properties
                uaCreateRequests_[i].ItemToMonitor.AttributeId = OpcUa_Attributes_EventNotifier;
                uaCreateRequests_[i].MonitoringMode = mode;
                uaCreateRequests_[i].RequestedParameters.ClientHandle = clientHandles_[i];
                uaCreateRequests_[i].RequestedParameters.SamplingInterval = samplingInterval;
                uaCreateRequests_[i].RequestedParameters.DiscardOldest = discardOldest;
                uaCreateRequests_[i].RequestedParameters.QueueSize = targets[i].queueSize;

                UaEventFilter eventFilter;

                size_t noOfSelectClauses = targets[i].eventFilter.selectClauses.size();

                for (size_t clauseIndex = 0;
                     clauseIndex < noOfSelectClauses && ret.isGood();
                     clauseIndex++)
                {
                    // create an operand
                    UaSimpleAttributeOperand operand;

                    SimpleAttributeOperand selectClause;
                    selectClause = targets[i].eventFilter.selectClauses[clauseIndex];

                    // set the attribute ID
                    operand.setAttributeId(selectClause.attributeId);

                    // set the type definition ID
                    OpcUa_NodeId typeId;
                    ret = nameSpaceArray.fillOpcUaNodeId(selectClause.typeId, typeId);
                    if (ret.isGood())
                        operand.setTypeId(typeId);

                    // set the browse path
                    size_t noOfBrowseNames = selectClause.browsePath.size();
                    for (size_t nameIndex = 0;
                         nameIndex < noOfBrowseNames && ret.isGood();
                         nameIndex++)
                    {
                        OpcUa_QualifiedName qualifiedName;
                        ret = nameSpaceArray.fillOpcUaQualifiedName(
                                selectClause.browsePath[nameIndex],
                                qualifiedName);

                        if (ret.isGood())
                            operand.setBrowsePathElement(nameIndex, qualifiedName, noOfBrowseNames);
                    }

                    if (ret.isGood())
                        eventFilter.setSelectClauseElement(clauseIndex, operand, noOfSelectClauses);
                }

                if (ret.isGood())
                    eventFilter.detachFilter(uaCreateRequests_[i].RequestedParameters.Filter);
            }
        }

        return ret;
    }



    // Fill the asynchronous SDK members
    // =============================================================================================
    Status CreateMonitoredEventsInvocation::fromAsyncUafToSdk(
            const vector<CreateMonitoredEventsRequestTarget>&   targets,
            const CreateMonitoredEventsSettings&                settings,
            const NamespaceArray&                               nameSpaceArray,
            const ServerArray&                                  serverArray)
    {
        // same as synchronous
        return fromSyncUafToSdk(targets, settings, nameSpaceArray, serverArray);
    }


    // Invoke the service synchronously
    // =============================================================================================
    Status CreateMonitoredEventsInvocation::invokeSyncSdkService(
            UaClientSdk::UaSubscription* uaSubscription)

    {
        uaf::Status ret;

        SdkStatus sdkStatus = uaSubscription->createMonitoredItems(
                uaServiceSettings_,
                uaTimeStamps_,
                uaCreateRequests_,
                uaCreateResults_);

        if (sdkStatus.isGood())
            ret = statuscodes::Good;
        else
            ret = CreateMonitoredItemsInvocationError(sdkStatus);

        return ret;
    }



    // Invoke the service asynchronously
    // =============================================================================================
    Status CreateMonitoredEventsInvocation::invokeAsyncSdkService(
            UaClientSdk::UaSubscription* uaSubscription,
            TransactionId                transactionId)
    {
        uaf::Status ret;

        SdkStatus sdkStatus = uaSubscription->beginCreateMonitoredItems(
                uaServiceSettings_,
                uaTimeStamps_,
                uaCreateRequests_,
                transactionId);

        if (sdkStatus.isGood())
            ret = statuscodes::Good;
        else
            ret = BeginCreateMonitoredItemsInvocationError(sdkStatus);

        return ret;
    }



    // Fill the UAF members
    // =============================================================================================
    Status CreateMonitoredEventsInvocation::fromSyncSdkToUaf(
            const NamespaceArray&                       nameSpaceArray,
            const ServerArray&                          serverArray,
            vector<CreateMonitoredEventsResultTarget>&  targets)

    {
        uaf::Status ret;

        // declare the number of results
        uint32_t noOfResults = uaCreateResults_.length();
        targets.resize(noOfResults);

        // check if the number of results is correct
        if (noOfResults == clientHandles_.size())
            ret = statuscodes::Good;
        else
            ret = UnexpectedError("Mismatch between number of results and number of client handles");

        // if everything is OK so far, update the targets
        if (ret.isGood())
        {
            for (uint32_t i = 0; i < noOfResults; i++)
            {
                targets[i].clientHandle = clientHandles_[i];
                targets[i].monitoredItemId = uaCreateResults_[i].MonitoredItemId;
                targets[i].revisedQueueSize = uaCreateResults_[i].RevisedQueueSize;
                targets[i].revisedSamplingIntervalSec
                    = uaCreateResults_[i].RevisedSamplingInterval / 1000.0;
                targets[i].opcUaStatusCode = uaCreateResults_[i].StatusCode;

                if (OpcUa_IsGood(uaCreateResults_[i].StatusCode))
                    targets[i].status = uaf::statuscodes::Good;
                else
                    targets[i].status = ServerCouldNotCreateMonitoredItemsError(
                            SdkStatus(UaStatus(uaCreateResults_[i].StatusCode)));
            }
        }

        return ret;
    }




}
