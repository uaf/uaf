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

#include "uaf/client/sessions/sessionfactory.h"

namespace uafc
{
    using namespace uaf;
    using namespace uafc;
    using std::string;
    using std::vector;
    using std::map;


    // Constructor
    // =============================================================================================
    SessionFactory::SessionFactory(
            LoggerFactory *loggerFactory,
            ClientInterface* clientInterface,
            Discoverer* discoverer,
            Database* database)
    : clientInterface_(clientInterface),
      discoverer_(discoverer),
      database_(database)
    {
        logger_ = new Logger(loggerFactory, "SessionFactory");

        transactionId_ = 0;

        logger_->debug("The SessionFactory has been constructed");
    }


    // Destructor
    // =============================================================================================
    SessionFactory::~SessionFactory()
    {
        logger_->debug("Destructing the SessionFactory");

        deleteAllSessions();

        delete logger_;
        logger_ = 0;

    }


    // Delete all sessions on the client side
    // =============================================================================================
    void SessionFactory::deleteAllSessions()
    {
        logger_->debug("Deleting all sessions and their subscriptions and monitored items");

        // lock the mutex to make sure the sessionMap is not being manipulated
        UaMutexLocker sessionMapLocker(&sessionMapMutex_);

        // also lock the mutex to make sure the activity cannot change anymore
        UaMutexLocker activityMapLocker(&activityMapMutex_);

        SessionMap::iterator iter;
        for (iter = sessionMap_.begin(); iter != sessionMap_.end() ; ++iter)
        {
            logger_->debug("Now deleting session %d - %s",
                            iter->second->clientConnectionId(),
                            iter->second->serverUri().c_str());

            delete iter->second;
            iter->second = 0;

            logger_->debug("The session has been deleted");
        }

        sessionMap_.clear();
        activityMap_.clear();

        logger_->debug("All sessions have been deleted");
    }





    // Manually connect a session
    // =============================================================================================
    Status SessionFactory::manuallyConnect(
            const string&           serverUri,
            const SessionSettings&  settings,
            ClientConnectionId&     clientConnectionId)
    {
        Status ret;
        Session* session = 0;

        ret = acquireSession(serverUri, settings, session);

        if (ret.isGood())
        {
            clientConnectionId = session->clientConnectionId();

            Activity activity;

            // important: increment the number of activities
            // (since we are manually connecting, we want the connection to remain open!)
            activityMapMutex_.lock();
            activity = activityMap_[clientConnectionId];
            activityMap_[clientConnectionId] = activity + 1;
            activityMapMutex_.unlock();

            logger_->debug("#activities has been incremented to %d", activity+1);

            ret = releaseSession(session);
        }
        else
        {
            ret.addDiagnostic("Could not manually connect");
            logger_->error(ret);
        }


        return ret;
    }


    // Manually disconnect a session
    // =============================================================================================
    Status SessionFactory::manuallyDisconnect(ClientConnectionId clientConnectionId)
    {
        Status ret;

        Session* session = 0;
        ret = acquireExistingSession(clientConnectionId, session);

        if (ret.isGood())
        {
            Activity activity;

            // important: decrement the number of activities
            // (since we are manually disconnecting, the connection doesn't have to remain open
            // anymore!)
            activityMapMutex_.lock();
            activity = activityMap_[clientConnectionId];
            activityMap_[clientConnectionId] = activity - 1;
            activityMapMutex_.unlock();

            logger_->debug("#activities has been decremented to %d", activity-1);

            ret = session->disconnect();
            releaseSession(session);
        }

        return ret;
    }




    // Manually disconnect a session
    // =============================================================================================
    void SessionFactory::doHouseKeeping()
    {
        vector<SessionInformation> infos = allSessionInformations();

        Session* session = 0;
        Status acquisitionStatus;
        bool tryToReconnect;
        for (vector<SessionInformation>::const_iterator it = infos.begin();
                it != infos.end();
                ++it)
        {
            acquisitionStatus = acquireExistingSession(it->clientConnectionId, session);

            if (acquisitionStatus.isGood())
            {
                if (session->sessionState() == uafc::sessionstates::Disconnected)
                {
                    // if other activities are going on besides the house keeping,
                    // then try to reconnect the session
                    activityMapMutex_.lock();
                    tryToReconnect = (activityMap_[it->clientConnectionId] > 1);
                    activityMapMutex_.unlock();

                    if (tryToReconnect)
                        session->connect();
                }
                releaseSession(session);
            }
        }

    }


    // Get information about the session
    // =============================================================================================
    Status SessionFactory::sessionInformation(
            ClientConnectionId  clientConnectionId,
            SessionInformation& sessionInformation)
    {
        Status ret;

        Session* session = 0;
        ret = acquireExistingSession(clientConnectionId, session);

        if (ret.isGood())
        {
            sessionInformation = session->sessionInformation();
            releaseSession(session);
        }

        return ret;
    }

    // Get information about the subscription
    // =============================================================================================
    Status SessionFactory::subscriptionInformation(
            ClientSubscriptionHandle    clientSubscriptionHandle,
            SubscriptionInformation&    subscriptionInformation)
    {
        Status ret;

        // lock the mutex to make sure the sessionMap_ is not being manipulated
        UaMutexLocker locker(&sessionMapMutex_);

        // loop trough the sessions
        for (SessionMap::const_iterator it = sessionMap_.begin(); it != sessionMap_.end(); ++it)
        {
            ret = it->second->subscriptionInformation(
                    clientSubscriptionHandle,
                    subscriptionInformation);

            if (ret.isGood())
                return ret;
        }

        return Status(statuscodes::InvalidRequestError,
                      "ClientSubscriptionHandle %d was not found",
                      clientSubscriptionHandle);
    }


    // Get information about the monitored item
    // =============================================================================================
    Status SessionFactory::monitoredItemInformation(
            ClientMonitoredItemHandle   clientMonitoredItemHandle,
            MonitoredItemInformation&   monitoredItemInformation)
    {
        Status ret;

        ret.setStatus(statuscodes::InvalidRequestError,
                      "clientMonitoredItemHandle %d was not found", clientMonitoredItemHandle);

        // lock the mutex to make sure the sessionMap_ is not being manipulated
        UaMutexLocker locker(&sessionMapMutex_);

        bool monitoredItemFound = false;

        // loop trough the sessions
        for (SessionMap::const_iterator it = sessionMap_.begin();
                it != sessionMap_.end() && (!monitoredItemFound);
                ++it)
        {
            monitoredItemFound = it->second->monitoredItemInformation(
                    clientMonitoredItemHandle,
                    monitoredItemInformation);

            if (monitoredItemFound)
                ret.setGood();
        }

        return ret;
    }


    // Manual subscription
    //==============================================================================================
    Status SessionFactory::manuallySubscribe(
            ClientConnectionId          clientConnectionId,
            const SubscriptionSettings& settings,
            ClientSubscriptionHandle&   clientSubscriptionHandle)
    {
        Status ret;

        Session* session = 0;
        ret = acquireExistingSession(clientConnectionId, session);

        if (ret.isGood())
        {
            ret = session->manuallySubscribe(settings, clientSubscriptionHandle);
            releaseSession(session);
        }

        return ret;
    }

    // Manual subscription
    //==============================================================================================
    Status SessionFactory::manuallyUnsubscribe(
            ClientConnectionId          clientConnectionId,
            ClientSubscriptionHandle    clientSubscriptionHandle)
    {
        Status ret;

        Session* session = 0;
        ret = acquireExistingSession(clientConnectionId, session);

        if (ret.isGood())
        {
            ret = session->manuallyUnsubscribe(clientSubscriptionHandle);
            releaseSession(session);
        }

        return ret;
    }

    // Get information about the sessions
    // =============================================================================================
    vector<SessionInformation> SessionFactory::allSessionInformations()
    {
        logger_->debug("Getting the session information for all sessions");

        vector<SessionInformation> ret;

        // lock the mutex to make sure the sessionMap_ is not being manipulated
        UaMutexLocker locker(&sessionMapMutex_);

        // loop trough the sessions
        for (SessionMap::const_iterator it = sessionMap_.begin(); it != sessionMap_.end(); ++it)
        {
            ret.push_back(it->second->sessionInformation());
        }

        return ret;
    }


    // Get information about all subscriptions
    // =============================================================================================
    vector<SubscriptionInformation> SessionFactory::allSubscriptionInformations()
    {
        logger_->debug("Getting the subscription information for all sessions");

        vector<SubscriptionInformation> ret;

        // lock the mutex to make sure the sessionMap_ is not being manipulated
        UaMutexLocker locker(&sessionMapMutex_);

        // loop trough the sessions
        for (SessionMap::const_iterator it = sessionMap_.begin(); it != sessionMap_.end(); ++it)
        {
            vector<SubscriptionInformation> tmp = it->second->allSubscriptionInformations();
            ret.insert(ret.end(),tmp.begin(),tmp.end());
        }

        return ret;
    }

    // Set the publishing mode.
    // =============================================================================================
    Status SessionFactory::setPublishingMode(
            ClientSubscriptionHandle    clientSubscriptionHandle,
            bool                        publishingEnabled,
            const ServiceSettings&      serviceSettings)
    {
        Status ret;

        // lock the mutex to make sure the sessionMap_ is not being manipulated
        UaMutexLocker locker(&sessionMapMutex_);

        bool subscriptionFound = false;

        // loop trough the sessions
        for (SessionMap::const_iterator it = sessionMap_.begin(); it != sessionMap_.end(); ++it)
        {
            ret = it->second->setPublishingMode(clientSubscriptionHandle,
                                                publishingEnabled,
                                                serviceSettings,
                                                subscriptionFound);

            if (subscriptionFound)
                return ret;
        }

        return Status(statuscodes::InvalidRequestError,
                      "ClientSubscriptionHandle %d was not found",
                      clientSubscriptionHandle);
    }


    // Construct a session if needed, without connecting
    // =============================================================================================
    Status SessionFactory::acquireSession(
            const string&           serverUri,
            const SessionSettings&  sessionSettings,
            Session*&               session)
    {
        logger_->debug("Acquiring Session to %s with the following settings:", serverUri.c_str());
        logger_->debug(sessionSettings.toString());

        Status ret;

        session = 0;

        // lock the mutex to make sure the sessionMap_ is not being manipulated
        UaMutexLocker locker(&sessionMapMutex_);

        // loop trough the sessions ...
        for (SessionMap::const_iterator it = sessionMap_.begin(); it != sessionMap_.end(); ++it)
        {
            // ... until a suitable one is found
            if (    it->second->serverUri() == serverUri
                &&  it->second->sessionSettings() == sessionSettings )
            {
                session = it->second;
                logger_->debug("A suitable session (ClientConnectionId=%d) already exists",
                               session->clientConnectionId());

                // get the ClientConnectionId of the session
                ClientConnectionId id = session->clientConnectionId();

                // increment the activity count of the session
                activityMapMutex_.lock();
                activityMap_[id] = activityMap_[id] + 1;
                activityMapMutex_.unlock();

                ret.setGood();

                break;
            }
        }

        // if no session exists (because none was found, or because it was just deleted),
        // then we create a new one
        if (ret.isUncertain())//session == 0)
        {
            ClientConnectionId clientConnectionId = database_->createUniqueClientConnectionId();

            logger_->debug("No suitable session exists yet, so we create a new one with "
                           "clientConnectionId %d",
                           clientConnectionId);

            // create a new session instance
            session = new Session(
                    logger_->loggerFactory(),
                    sessionSettings,
                    serverUri,
                    clientConnectionId,
                    this,
                    clientInterface_,
                    discoverer_,
                    database_);

            // store the new session instance in the sessionMap
            sessionMap_[clientConnectionId] = session;

            // create an activity count for the session
            activityMapMutex_.lock();
            activityMap_[clientConnectionId] = 1;
            activityMapMutex_.unlock();

            // connect to the session
            session->connect();

            // regardless of whether the connection succeeded or failed, set the return status
            // to 'good'
            ret.setGood();
        }

        // add some diagnostics
        if (ret.isGood())
        {
            activityMapMutex_.lock();
            logger_->debug("The requested session is acquired (#activities: %d)",
                           activityMap_[session->clientConnectionId()]);
            activityMapMutex_.unlock();
        }
        else
        {
            logger_->error("The requested session could not be acquired");
            ret.addDiagnostic("The requested session could not be acquired");
        }

        return ret;
    }


    // Acquire an existing session, if one is available.
    // =============================================================================================
    Status SessionFactory::acquireExistingSession(
            ClientConnectionId  clientConnectionId,
            Session*&           session)
    {
        logger_->debug("Acquiring existing session %d if available", clientConnectionId);

        Status ret;

        session = 0;

        // lock the mutex to make sure the sessionMap is not being manipulated
        UaMutexLocker locker(&sessionMapMutex_);

        SessionMap::iterator iter = sessionMap_.find(clientConnectionId);

        if (iter == sessionMap_.end())
        {
            ret.setStatus(statuscodes::InvalidRequestError,
                          "No session with clientConnectionId %d is known", clientConnectionId);

            logger_->error(ret);
        }
        else
        {
            // update the session argument
            session = iter->second;

            // increment the activity count of the session
            activityMapMutex_.lock();
            Activity newActivityCount = activityMap_[clientConnectionId] + 1;
            activityMap_[clientConnectionId] = newActivityCount;
            activityMapMutex_.unlock();

            // an existing session was acquired, so set the status to Good
            ret.setGood();

            logger_->debug("Session %d was acquired (#activities: %d)",
                           clientConnectionId, newActivityCount);
        }

        return ret;
    }


    // Release a session
    // =============================================================================================
    Status SessionFactory::releaseSession(Session*& session, bool allowGarbageCollection)
    {
        Status ret;

        // lock the mutex to make sure the sessionMap is nog being manipulated
        UaMutexLocker sessionMapLocker(&sessionMapMutex_);

        // also lock the mutex to make sure the activity cannot change anymore
        UaMutexLocker activityMapLocker(&activityMapMutex_);

        if (session == 0)
        {
            ret.setStatus(statuscodes::UnexpectedError, "releaseSession() got a null pointer!");
            logger_->error(ret);
        }
        else if (activityMap_[session->clientConnectionId()] == 0)
        {
            ret.setStatus(statuscodes::UnexpectedError,
                          "Trying to release a fully released session!");
            logger_->error(ret);
        }
        else
        {

            ClientConnectionId id = session->clientConnectionId();

            activityMap_[id] = activityMap_[id] - 1;
            ret.setGood();

            logger_->debug("Session %d is now released (#activities: %d)", id, activityMap_[id]);

            // check if the session is disconnected
            if (session->sessionState() == uafc::sessionstates::Disconnected)
            {
                // if there is no ongoing activity of the session (in other words: if there is no
                // pointer to this session being used), we may delete it!
                if (activityMap_[id] == 0 && allowGarbageCollection)
                {
                    logger_->debug("There's no ongoing activity of this disconnected session, so "
                                   "we may delete it");
                    delete session;
                    session = 0;
                    activityMap_.erase(id);
                    sessionMap_.erase(id);

                    logger_->debug("The session has been deleted");
                }
            }
        }

        return ret;
    }



    // Get a new transaction id
    // =============================================================================================
    uafc::TransactionId SessionFactory::getNewTransactionId()
    {
        UaMutexLocker locker(&transactionIdMutex_);

        uint32_t delta = 1;
        TransactionId newTransactionId;
        while (delta < OpcUa_UInt32_Max)
        {
            newTransactionId = transactionId_ + delta;

            if (transactionMap_.find(newTransactionId) == transactionMap_.end())
            {
                transactionId_ = newTransactionId;
                return transactionId_;
            }
            else
            {
                delta++;
            }
        }

        return 0;
    }


    // implemented from the callback interface
    // =============================================================================================
    void SessionFactory::connectionStatusChanged(
        OpcUa_UInt32                        clientConnectionId,
        UaClientSdk::UaClient::ServerStatus serverStatus)
    {
        // convert the serverStatus to the Session::SessionStatus enum
        sessionstates::SessionState state = sessionstates::toUaf(serverStatus);

        logger_->debug("Received a ConnectionStatusChanged event for clientConnectionId %d "
                       "(new state: %s)",
                       clientConnectionId,
                       sessionstates::toString(state).c_str());

        // acquire the session for which the event was meant:
        Session* session = 0;
        Status acquireStatus = acquireExistingSession(clientConnectionId, session);

        if (acquireStatus.isGood())
        {
            // update the session state
            session->setSessionState(state);

            // release the acquired session
            releaseSession(session, false);
        }
    }


    // implemented from the callback interface
    // =============================================================================================
    void SessionFactory::callComplete(
        OpcUa_UInt32                transactionId,
        const UaStatus&             uaStatus,
        const UaClientSdk::CallOut& callResponse)
    {
        logger_->debug("Call complete: transactionId %d", transactionId);

        // find the request handle for the given transaction id
        RequestHandle handle = 0;
        bool transactionIdFound;
        transactionMapMutex_.lock();
        TransactionMap::iterator iter = transactionMap_.find(transactionId);
        transactionIdFound = (iter != transactionMap_.end());
        if (transactionIdFound)
            handle = iter->second;
        transactionMapMutex_.unlock();

        // create a result to fill it
        MethodCallResult result;

        // fill the status
        result.overallStatus.fromSdk(uaStatus.statusCode(), uaStatus.toString().toUtf8());

        // create the target and requestHandle
        result.requestHandle = handle;
        result.targets.resize(1);

        // set the status of the target
        result.targets[0].status.fromSdk(
                callResponse.callResult.statusCode(),
                callResponse.callResult.toString().toUtf8());

        // fill the output arguments of the target
        for (uint32_t i = 0; i < callResponse.outputArguments.length(); i++)
            result.targets[0].outputArguments.push_back(Variant(callResponse.outputArguments[i]));

        // fill the input argument results
        for (uint32_t i = 0; i < callResponse.inputArgumentResults.length(); i++)
        {
            Status status;
            status.fromSdk(callResponse.inputArgumentResults[i], "Invalid argument");
            result.targets[0].inputArgumentStatuses.push_back(status);
        }

        // if the transaction id was found, put the result in the correct cache
        if (transactionIdFound)
        {
            logger_->debug("Transaction id %d corresponds to the asynchronous handle %d",
                           transactionId, handle);

            // remove the transaction id : request handle pair
            transactionMapMutex_.lock();      // lock the map
            transactionMap_.erase(transactionId);         // erase the key
            transactionMapMutex_.unlock();    // unlock the map
        }
        // if the transaction id was not found, we cannot store the result in the cache
        else
        {
            logger_->error("Unknown transaction id received, so we cannot cache the result");
        }

        // call the callback interface
        clientInterface_->callComplete(result);
    }


    // implemented from the callback interface
    // =============================================================================================
    void SessionFactory::readComplete(
        OpcUa_UInt32             transactionId,     //!< [in] Client defined transction id for the read
        const UaStatus&          uaStatus,          //!< [in] Overall read result
        const UaDataValues&      values,            //!< [in] List of read results contained in OpcUa_DataValue structures
        const UaDiagnosticInfos& diagnosticInfos    //!< [in] List of diagnostic information
        )
    {
        logger_->debug("Read complete: transactionId %d", transactionId);


        // find the request handle for the given transaction id
        RequestHandle handle = 0;
        bool transactionIdFound;
        transactionMapMutex_.lock();
        TransactionMap::iterator iter = transactionMap_.find(transactionId);
        transactionIdFound = (iter != transactionMap_.end());
        if (transactionIdFound)
            handle = iter->second;
        transactionMapMutex_.unlock();

        // create a result to fill it
        ReadResult result;

        // fill the status and requestHandle
        result.requestHandle = handle;
        result.overallStatus.fromSdk(uaStatus.statusCode(), uaStatus.toString().toUtf8());

        // create the target
        result.targets.resize(values.length());

        // walk through the received data values
        for (uint32_t i = 0; i < values.length(); i++)
        {
            result.targets[i].status.fromSdk(values[i].StatusCode, "Server reported error");
            result.targets[i].data = Variant(values[i].Value);
        }
        logger_->debug("ReadResult for request %d (transaction %d):", handle, transactionId);
        logger_->debug(result.toString());

//        // if the transaction id was found, put the result in the correct cache
//        if (transactionIdFound)
//        {
//            logger_->debug("Transaction id %d corresponds to the asynchronous handle %d",
//                           transactionId, handle);
//
//            // add the result to the database
//            database_->asyncMethodCallResultCache.set(handle, result);
//
//            // remove the transaction id : request handle pair
//            transactionMapMutex_.lock();      // lock the map
//            transactionMap_.erase(transactionId);         // erase the key
//            transactionMapMutex_.unlock();    // unlock the map
//        }
//        // if the transaction id was not found, we cannot store the result in the cache
//        else
//        {
//            logger_->error("Unknown transaction id received, so we cannot cache the result");
//        }

        // call the callback interface
        clientInterface_->readComplete(result);
    }


    // implemented from the callback interface
    // =============================================================================================
    void SessionFactory::writeComplete(
        OpcUa_UInt32             transactionId,     //!< [in] Client defined transction id for the write
        const UaStatus&          uaStatus,          //!< [in] Overall write result
        const UaStatusCodeArray& results,           //!< [in] List of write results
        const UaDiagnosticInfos& diagnosticInfos    //!< [in] List of diagnostic information
        )
    {
        logger_->debug("Write complete: transactionId %d", transactionId);


        // find the request handle for the given transaction id
        RequestHandle handle = 0;
        bool transactionIdFound;
        transactionMapMutex_.lock();
        TransactionMap::iterator iter = transactionMap_.find(transactionId);
        transactionIdFound = (iter != transactionMap_.end());
        if (transactionIdFound)
            handle = iter->second;
        transactionMapMutex_.unlock();

        // create a result to fill it
        WriteResult result;

        // fill the status and requestHandle
        result.requestHandle = handle;
        result.overallStatus.fromSdk(uaStatus.statusCode(), uaStatus.toString().toUtf8());

        // create the target
        result.targets.resize(results.length());

        // walk through the received results
        for (uint32_t i = 0; i < results.length(); i++)
        {
            result.targets[i].status.fromSdk(results[i], "Server reported error");
        }
        logger_->debug("WriteResult for request %d (transaction %d):", handle, transactionId);
        logger_->debug(result.toString());

//        // if the transaction id was found, put the result in the correct cache
//        if (transactionIdFound)
//        {
//            logger_->debug("Transaction id %d corresponds to the asynchronous handle %d",
//                           transactionId, handle);
//
//            // add the result to the database
//            database_->asyncMethodCallResultCache.set(handle, result);
//
//            // remove the transaction id : request handle pair
//            transactionMapMutex_.lock();      // lock the map
//            transactionMap_.erase(transactionId);         // erase the key
//            transactionMapMutex_.unlock();    // unlock the map
//        }
//        // if the transaction id was not found, we cannot store the result in the cache
//        else
//        {
//            logger_->error("Unknown transaction id received, so we cannot cache the result");
//        }

        // call the callback interface
        clientInterface_->writeComplete(result);
    }

}
