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

#include "uaf/client/invocations/historyreadrawmodifiedinvocation.h"

namespace uafc
{
    using namespace uaf;
    using namespace uafc;
    using std::string;
    using std::size_t;
    using std::stringstream;
    using std::vector;
    using std::cout;


    // Fill the synchronous SDK members
    // =============================================================================================
    Status HistoryReadRawModifiedInvocation::fromSyncUafToSdk(
            const vector<HistoryReadRawModifiedRequestTarget>&  targets,
            const HistoryReadRawModifiedSettings&               settings,
            const NamespaceArray&                               nameSpaceArray,
            const ServerArray&                                  serverArray)
    {
        Status ret;

        // update the uaServiceSettings_
        ret = settings.toSdk(uaServiceSettings_);

        // update the uaContext_
        // ---------------------

        uaContext_.bReleaseContinuationPoints = (settings.releaseContinuationPoints ?
                                                 OpcUa_True : OpcUa_False);
        uaContext_.isReadModified = (settings.isReadModified ? OpcUa_True : OpcUa_False);
        uaContext_.returnBounds = (settings.returnBounds ? OpcUa_True : OpcUa_False);
        settings.startTime.toSdk(uaContext_.startTime);
        settings.endTime.toSdk(uaContext_.endTime);
        uaContext_.numValuesPerNode = settings.numValuesPerNode;
        uaContext_.timeStamps = timestampstoreturn::fromUafToSdk(settings.timestampsToReturn);

        // update the uaNodesToRead_
        // -------------------------

        // declare the number of targets
        size_t noOfTargets = targets.size();

        // resize the number of uaNodesToRead_
        uaNodesToRead_.create(noOfTargets);

        // initialize the autoBrowsedNextPerTarget_ vector
        autoReadMorePerTarget_.resize(noOfTargets, 0);

        // loop through the targets
        for (size_t i = 0; i < noOfTargets && ret.isGood(); i++)
        {
            // update the node id of the target
            ret = nameSpaceArray.fillOpcUaNodeId(targets[i].address, uaNodesToRead_[i].NodeId);

            // update the other parameters
            if (ret.isGood())
            {
                // the index range
                if (targets[i].indexRange.size() > 0)
                {
                    UaString uaIndexRange(targets[i].indexRange.c_str());
                    uaIndexRange.copyTo(&uaNodesToRead_[i].IndexRange);
                }

                // the continuation point
                if (!targets[i].continuationPoint.isNull())
                    targets[i].continuationPoint.toSdk(&uaNodesToRead_[i].ContinuationPoint);

                // the data encoding
                if (!targets[i].dataEncoding.isNull())
                {
                    ret = nameSpaceArray.fillOpcUaQualifiedName(
                            targets[i].dataEncoding,
                            uaNodesToRead_[i].DataEncoding);
                }
            }
        }

        return ret;
    }


    // Fill the asynchronous SDK members
    // =============================================================================================
    Status HistoryReadRawModifiedInvocation::fromAsyncUafToSdk(
            const vector<HistoryReadRawModifiedRequestTarget>&  targets,
            const HistoryReadRawModifiedSettings&               settings,
            const NamespaceArray&                               nameSpaceArray,
            const ServerArray&                                  serverArray)
    {
        return Status(statuscodes::UnsupportedError, "Asynchronous HistoryRead is not supported");
    }


    // Invoke the service synchronously
    // =============================================================================================
    Status HistoryReadRawModifiedInvocation::invokeSyncSdkService(UaClientSdk::UaSession* uaSession)
    {
        Status ret;

        UaStatus uaStatus = uaSession->historyReadRawModified(
                uaServiceSettings_,
                uaContext_,
                uaNodesToRead_,
                uaResults_,
                uaDiagnosticInfos_);

        ret.fromSdk(uaStatus.statusCode(), "Synchronous HistoryRead invocation failed");

        uint32_t autoReadMore    = 0;
        uint32_t maxAutoReadMore = this->serviceSettings().maxAutoReadMore;

        // do we still have to automatically invoke another read, or are we finished?
        bool finished = (maxAutoReadMore == 0);


        // if we're not finished already, and the initial request was successful, we
        // may need to invoke the history read service again
        while ((!finished) && ret.isGood())
        {
            UaHistoryReadValueIds               uaNextNodesToRead;
            UaClientSdk::HistoryReadDataResults uaNextResults;
            vector<uint32_t>                    ranks; // the rank numbers of the original request

            // loop through the results and append "unfinished" read results to the
            // variables for the next read call, as defined above
            for (uint32_t i = 0; i < uaResults_.length(); i++)
            {
                if (   uaResults_[i].m_continuationPoint.length() > 0
                    && uaResults_[i].m_status.isGood())
                {
                    // get the rank number for the next call
                    uint32_t current = uaNextNodesToRead.length();

                    // increase the size of the continuation points for the next BrowseNext call
                    uaNextNodesToRead.resize(current + 1);

                    // store the rank number of the current result
                    ranks.push_back(i);

                    uaResults_[i].m_continuationPoint.copyTo(
                            &uaNextNodesToRead[current].ContinuationPoint);

                    UaNodeId(uaNodesToRead_[i].NodeId).copyTo(
                            &uaNextNodesToRead[current].NodeId);

                    if (!UaQualifiedName(uaNodesToRead_[i].DataEncoding).isNull())
                        UaQualifiedName(uaNodesToRead_[i].DataEncoding).copyTo(
                                &uaNextNodesToRead[current].DataEncoding);

                    if (!UaString(&uaNodesToRead_[i].IndexRange).isNull())
                        UaString(&uaNodesToRead_[i].IndexRange).copyTo(
                                &uaNextNodesToRead[current].IndexRange);
                }
            }

            // if necessary, call the historyReadRawModified service again
            if (uaNextNodesToRead.length() > 0)
            {
                // perform the BrowseNext call
                UaStatus uaNextStatus = uaSession->historyReadRawModified(
                        uaServiceSettings_,
                        uaContext_,
                        uaNextNodesToRead,
                        uaNextResults,
                        uaDiagnosticInfos_);

                ret.fromSdk(uaNextStatus.statusCode(),
                            "Synchronous HistoryReadRawModified invocation failed");

                // we've finished an automatic read call, so increment the counter
                autoReadMore++;

                // now append the results to the results of the original read call
                for (uint32_t iNext = 0; iNext < uaNextResults.length() && ret.isGood(); iNext++)
                {
                    // get the rank number of the original request
                    uint32_t rank = ranks[iNext];

                    // increment the autoBrowsedNext
                    autoReadMorePerTarget_[rank] = autoReadMore;

                    // update the status
                    uaResults_[rank].m_status = uaNextResults[iNext].m_status;

                    if (uaResults_[rank].m_status.isGood())
                    {
                        // update the continuation point
                        uaResults_[rank].m_continuationPoint = uaNextResults[iNext].m_continuationPoint;

                        // now we want to append the retrieved data values to the existing data
                        // values
                        uint32_t oldDataLength  = uaResults_[rank].m_dataValues.length();
                        uint32_t nextDataLength = uaNextResults[iNext].m_dataValues.length();

                        // resize the original results, so that it can hold the new results
                        uaResults_[rank].m_dataValues.resize(oldDataLength + nextDataLength);

                        // now copy the data from the new results to the original results:
                        for (uint32_t i=0, j=oldDataLength; i<nextDataLength; i++, j++)
                        {
                            UaVariant(uaNextResults[iNext].m_dataValues[i].Value).copyTo(
                                    &uaResults_[rank].m_dataValues[j].Value);

                            uaResults_[rank].m_dataValues[j].SourceTimestamp \
                                = uaNextResults[iNext].m_dataValues[i].SourceTimestamp;

                            uaResults_[rank].m_dataValues[j].ServerTimestamp \
                                = uaNextResults[iNext].m_dataValues[i].ServerTimestamp;

                            uaResults_[rank].m_dataValues[j].SourcePicoseconds \
                                = uaNextResults[iNext].m_dataValues[i].SourcePicoseconds;

                            uaResults_[rank].m_dataValues[j].ServerPicoseconds \
                                = uaNextResults[iNext].m_dataValues[i].ServerPicoseconds;
                        }

                        // now we want to append the retrieved modification info values to the
                        // existing modification info values
                        oldDataLength  = uaResults_[rank].m_modificationInformation.length();
                        nextDataLength = uaNextResults[iNext].m_modificationInformation.length();

                        // resize the original results, so that it can hold the new results
                        uaResults_[rank].m_modificationInformation.resize(oldDataLength + nextDataLength);

                        // now copy the data from the new results to the original results:
                        for (uint32_t i=0, j=oldDataLength; i<nextDataLength; i++, j++)
                        {
                            UaString userName(&uaNextResults[iNext].m_modificationInformation[i].UserName);
                            if (!userName.isNull())
                                userName.copyTo(&uaResults_[rank].m_modificationInformation[j].UserName);

                            uaResults_[rank].m_modificationInformation[j].ModificationTime \
                                = uaNextResults[iNext].m_modificationInformation[i].ModificationTime;

                            uaResults_[rank].m_modificationInformation[j].UpdateType \
                                = uaNextResults[iNext].m_modificationInformation[i].UpdateType;
                        }
                    }
                }

                // check if we may still need to do another automatic BrowseNext
                finished = autoReadMore >= maxAutoReadMore;
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
    Status HistoryReadRawModifiedInvocation::invokeAsyncSdkService(
            UaClientSdk::UaSession* uaSession,
            TransactionId           transactionId)
    {
        return Status(statuscodes::UnsupportedError, "Asynchronous HistoryRead is not supported");
    }


    // Fill the UAF members
    // =============================================================================================
    Status HistoryReadRawModifiedInvocation::fromSyncSdkToUaf(
            const NamespaceArray&                       nameSpaceArray,
            const ServerArray&                          serverArray,
            vector<HistoryReadRawModifiedResultTarget>& targets)
    {
        // declare the return Status
        Status ret;

        // declare the number of targets, and resize the output parameter accordingly
        uint32_t noOfTargets = uaResults_.length();
        targets.resize(noOfTargets);

        // check the number of targets
        if (noOfTargets == uaNodesToRead_.length()
            && noOfTargets == autoReadMorePerTarget_.size())
        {
            for (uint32_t i=0; i<noOfTargets ; i++)
            {

                // update the status
                targets[i].status.fromSdk(uaResults_[i].m_status.statusCode(),
                                          "The server reported a HistoryRead failure");

                // update the autoBrowsedNext counter
                targets[i].autoReadMore = autoReadMorePerTarget_[i];

                // update the continuation point
                targets[i].continuationPoint.fromSdk(uaResults_[i].m_continuationPoint);

                // update the data values
                uint32_t noOfDataValues = uaResults_[i].m_dataValues.length();
                targets[i].dataValues.resize(noOfDataValues);
                for (uint32_t j = 0; j < noOfDataValues; j++)
                    targets[i].dataValues[j].fromSdk(UaDataValue(uaResults_[i].m_dataValues[j]));

                // update the modification information
                uint32_t noOfModificationInfos = uaResults_[i].m_modificationInformation.length();
                targets[i].modificationInfos.resize(noOfModificationInfos);
                for (uint32_t j = 0; j < noOfModificationInfos; j++)
                    targets[i].modificationInfos[j].fromSdk(uaResults_[i].m_modificationInformation[j]);
            }

            ret.setGood();
        }
        else
        {
            ret.setStatus(statuscodes::UnexpectedError,
                          "Number of result targets does not match number of request targets,"
                          "or number of automatic ReadMore counters");
        }

        return ret;
    }




}
