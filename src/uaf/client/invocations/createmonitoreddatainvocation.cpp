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

#include "uaf/client/invocations/createmonitoreddatainvocation.h"

namespace uafc
{
    using namespace uaf;
    using namespace uafc;
    using namespace uaf::monitoringmodes;
    using std::string;
    using std::stringstream;
    using std::vector;


    // Fill the synchronous SDK members
    // =============================================================================================
    Status CreateMonitoredDataInvocation::fromSyncUafToSdk(
            const vector<CreateMonitoredDataRequestTarget>& targets,
            const CreateMonitoredDataSettings&              settings,
            const NamespaceArray&                           nameSpaceArray,
            const ServerArray&                              serverArray)
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
            ret.setGood();
        else
            ret.setStatus(statuscodes::UnexpectedError, "Handles have not been set correctly!");

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
                UaString indexRange(targets[i].indexRange.c_str());

                // set the other properties
                uaCreateRequests_[i].ItemToMonitor.AttributeId = targets[i].attributeId;
                uaCreateRequests_[i].MonitoringMode = mode;
                uaCreateRequests_[i].RequestedParameters.ClientHandle = clientHandles_[i];
                uaCreateRequests_[i].RequestedParameters.SamplingInterval = samplingInterval;
                uaCreateRequests_[i].RequestedParameters.DiscardOldest = discardOldest;
                uaCreateRequests_[i].RequestedParameters.QueueSize = targets[i].queueSize;
                indexRange.copyTo(&(uaCreateRequests_[i].ItemToMonitor.IndexRange));

                OpcUa_DataChangeFilter* pDataChangeFilter = (OpcUa_DataChangeFilter*)OpcUa_Null;

                OpcUa_EncodeableObject_CreateExtension(
                        &OpcUa_DataChangeFilter_EncodeableType,
                        &uaCreateRequests_[i].RequestedParameters.Filter,
                        (OpcUa_Void**)&pDataChangeFilter);

                OpcUa_DataChangeFilter_Initialize(pDataChangeFilter);

                targets[i].dataChangeFilter.toSdk(pDataChangeFilter);

            }
        }

        return ret;
    }


    // Fill the asynchronous SDK members
    // =============================================================================================
    Status CreateMonitoredDataInvocation::fromAsyncUafToSdk(
            const vector<CreateMonitoredDataRequestTarget>& targets,
            const CreateMonitoredDataSettings&              settings,
            const NamespaceArray&                           nameSpaceArray,
            const ServerArray&                              serverArray)
    {
        // same as synchronous
        return fromSyncUafToSdk(targets, settings, nameSpaceArray, serverArray);
    }


    // Invoke the service synchronously
    // =============================================================================================
    Status CreateMonitoredDataInvocation::invokeSyncSdkService(
            UaClientSdk::UaSubscription* uaSubscription)

    {
        Status ret;

        UaStatus status = uaSubscription->createMonitoredItems(
                uaServiceSettings_,
                uaTimeStamps_,
                uaCreateRequests_,
                uaCreateResults_);

        ret.fromSdk(status.statusCode(),
                    "The synchronous CreateMonitoredItems service failed");

        return ret;
    }


    // Invoke the service asynchronously
    // =============================================================================================
    Status CreateMonitoredDataInvocation::invokeAsyncSdkService(
            UaClientSdk::UaSubscription* uaSubscription,
            TransactionId                transactionId)
    {
        Status ret;

        UaStatus status = uaSubscription->beginCreateMonitoredItems(
                uaServiceSettings_,
                uaTimeStamps_,
                uaCreateRequests_,
                transactionId);

        ret.fromSdk(status.statusCode(),
                    "The asynchronous CreateMonitoredItems service failed");

        return ret;
    }


    // Fill the UAF members
    // =============================================================================================
    Status CreateMonitoredDataInvocation::fromSyncSdkToUaf(
            const NamespaceArray&                    nameSpaceArray,
            const ServerArray&                       serverArray,
            vector<CreateMonitoredDataResultTarget>& targets)
    {
        Status ret;

        // declare the number of results, and resize the output parameter accordingly
        uint32_t noOfResults = uaCreateResults_.length();
        targets.resize(noOfResults);

        // check if the number of results is correct
        if (noOfResults == clientHandles_.size())
            ret.setGood();
        else
            ret.setStatus(statuscodes::UnexpectedError,
                          "Mismatch between number of results and number of client handles");

        // if everything is OK so far, update the targets
        if (ret.isGood())
        {

            for (uint32_t i = 0; i < noOfResults; i++)
            {
                targets[i].notificationHandle = notificationHandles_[i];
                targets[i].clientHandle = clientHandles_[i];
                targets[i].monitoredItemId = uaCreateResults_[i].MonitoredItemId;
                targets[i].revisedQueueSize = uaCreateResults_[i].RevisedQueueSize;
                targets[i].revisedSamplingIntervalSec
                    = uaCreateResults_[i].RevisedSamplingInterval / 1000.0;
                targets[i].status.fromSdk(uaCreateResults_[i].StatusCode,
                                                       "Error on the server side");
            }
        }

        return ret;
    }


}
