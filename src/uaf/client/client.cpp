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

#include "uaf/client/client.h"


namespace uafc
{
    using namespace uaf;
    using namespace uafc;
    using std::string;
    using std::map;
    using std::vector;
    using std::pair;


    // Constructor
    // =============================================================================================
    Client::Client()
    {
        logger_ = new Logger("", "Client");
        logger_->loggerFactory()->registerCallbackInterface(this);
        construct();
    }

    // Constructor
    // =============================================================================================
    Client::Client(const string& applicationName)
    {
        logger_ = new Logger(applicationName, "Client");
        logger_->loggerFactory()->registerCallbackInterface(this);
        construct();
        // update the settings
        setClientSettings(ClientSettings(applicationName));
    }


    // Constructor
    // =============================================================================================
    Client::Client(const uafc::ClientSettings& settings)
    {
        logger_ = new Logger(settings.applicationName, "Client");
        logger_->loggerFactory()->registerCallbackInterface(this);
        construct();
        setClientSettings(settings);
    }


    // Constructor
    // =============================================================================================
    Client::Client(const uafc::ClientSettings& settings, LoggerFactory* loggerFactory)
    {
        logger_ = loggerFactory->createLogger("Client");
        construct();
        // update the name
        setClientSettings(settings);
    }


    // Common constructor code
    // =============================================================================================
    void Client::construct()
    {
        currentRequestHandle_ = 0;
        doFinishThread_ = false;

        database_       = new Database(logger_->loggerFactory());
        discoverer_     = new Discoverer(logger_->loggerFactory(), database_);
        sessionFactory_ = new SessionFactory(logger_->loggerFactory(), this, discoverer_, database_);
        resolver_       = new Resolver(logger_->loggerFactory(), sessionFactory_, database_);

        logger_->debug("Now starting the thread to periodically check the requests");

        // start the thread
        start();

        logger_->debug("The client has been constructed");
    }


    // Destructor
    // =============================================================================================
    Client::~Client()
    {
        logger_->debug("Destructing the client");

        // make sure the thread isn't doing anything
        //UaMutexLocker locker(&threadStoppingMutex_);

        doFinishThread_ = true;

        wait();


        delete resolver_;
        resolver_ = 0;

        delete sessionFactory_;
        sessionFactory_ = 0;

        delete discoverer_;
        discoverer_ = 0;

        delete database_;
        database_ = 0;

        delete logger_;
        logger_ = 0;


    }


    // Get a copy of the client config
    //==============================================================================================
    ClientSettings Client::clientSettings() const
    {
        return database_->clientSettings;
    }


    // Set the client config
    //==============================================================================================
    void Client::setClientSettings(const ClientSettings& settings)
    {
        logger_->debug("Now updating the ClientSettings");

        logger_->loggerFactory()->setStdOutLevel(settings.logToStdOutLevel);
        logger_->loggerFactory()->setCallbackLevel(settings.logToCallbackLevel);

        bool doFindServers = (settings.discoveryUrls != database_->clientSettings.discoveryUrls);
        database_->clientSettings = settings;

        if (doFindServers)
        {
            logger_->debug("The discoveryUrls were changed, so we rediscover the system");
            findServersNow();
        }
    }




    // Find the servers now
    // =============================================================================================
    uaf::Status Client::findServersNow()
    {
        return discoverer_->findServers();
    }


    // Get the servers that were found
    // =============================================================================================
    const vector<ApplicationDescription>& Client::serversFound() const
    {
        return discoverer_->serversFound();
    }


    // Read a number of node attributes
    //==============================================================================================
    uaf::Status Client::read(
            const std::vector<uaf::Address>&        addresses,
            const uafc::attributeids::AttributeId   attributeId,
            const uafc::ReadConfig&                 serviceConfig,
            const uafc::SessionConfig&              sessionConfig,
            uafc::ReadResult&                       result)
    {
        // log read request
        logger_->debug("Reading %d node attributes", addresses.size());

        ReadRequest request(0, serviceConfig, sessionConfig);

        request.targets.reserve(addresses.size());

        for (vector<Address>::const_iterator it = addresses.begin(); it != addresses.end(); ++it)
            request.targets.push_back(ReadRequestTarget(*it, attributeId));

        // perform the read request
        return processRequest(request, result);
    }




    // Write a number of node attributes
    //==============================================================================================
    uaf::Status Client::write(
            const std::vector<uaf::Address>&        addresses,
            const std::vector<uaf::Variant>&        data,
            const uafc::attributeids::AttributeId   attributeId,
            const uafc::WriteConfig&                serviceConfig,
            const uafc::SessionConfig&              sessionConfig,
            uafc::WriteResult&                      result)
    {
        // log write request
        logger_->debug("Writing %d node attributes", addresses.size());

        // create a write target and write result
        WriteRequest request(0, serviceConfig, sessionConfig);

        // check if the addresses and the data match
        if (addresses.size() != data.size())
            return uaf::Status(uaf::statuscodes::InvalidRequestError,
                               "Data doesn't match addresses");

        // fill the targets
        for (std::size_t i = 0; i < addresses.size(); i++)
            request.targets.push_back(WriteRequestTarget(addresses[i], data[i], attributeId));

        // perform the write request
        return processRequest(request, result);
    }



    // Call a method synchronously
    //==============================================================================================
    Status Client::call(
            const uaf::Address&                 objectAddress,
            const uaf::Address&                 methodAddress,
            const std::vector<uaf::Variant>&    inputArguments,
            const uafc::MethodCallConfig&       serviceConfig,
            const uafc::SessionConfig&          sessionConfig,
            uafc::MethodCallResult&             result)
    {
        MethodCallRequest request(0, serviceConfig, sessionConfig);

        request.targets.resize(1);
        request.targets[0].objectAddress  = objectAddress;
        request.targets[0].methodAddress  = methodAddress;
        request.targets[0].inputArguments = inputArguments;

        // perform the write request
        return processRequest(request, result);
    }




    // Call a method asynchronously
    //==============================================================================================
    Status Client::beginCall(
            const uaf::Address&                 objectAddress,
            const uaf::Address&                 methodAddress,
            const std::vector<uaf::Variant>&    inputArguments,
            const uafc::MethodCallConfig&       serviceConfig,
            const uafc::SessionConfig&          sessionConfig,
            uafc::AsyncMethodCallResult&        result)
    {
        AsyncMethodCallRequest request(0, serviceConfig, sessionConfig);

        request.targets.resize(1);
        request.targets[0].objectAddress  = objectAddress;
        request.targets[0].methodAddress  = methodAddress;
        request.targets[0].inputArguments = inputArguments;

        // perform the write request
        return processRequest(request, result);
    }




    // Start monitoring data items
    //==============================================================================================
    Status Client::createMonitoredData(
            const std::vector<uaf::Address>&        addresses,
            const uafc::CreateMonitoredDataConfig&  serviceConfig,
            const uafc::SessionConfig&              sessionConfig,
            const uafc::SubscriptionConfig&         subscriptionConfig,
            uafc::CreateMonitoredDataResult&        result)
    {
        CreateMonitoredDataRequest request(
                0,
                serviceConfig,
                sessionConfig,
                subscriptionConfig);

        for (vector<Address>::const_iterator it = addresses.begin(); it != addresses.end(); ++it)
        {
            request.targets.push_back(CreateMonitoredDataRequestTarget(*it));
        }

        return processRequest(request, result);
    }




    // Start monitoring event items
    //==============================================================================================
    Status Client::createMonitoredEvents(
            const std::vector<uaf::Address>&            addresses,
            const uaf::EventFilter&                     eventFilter,
            const uafc::CreateMonitoredEventsConfig&    serviceConfig,
            const uafc::SessionConfig&                  sessionConfig,
            const uafc::SubscriptionConfig&             subscriptionConfig,
            uafc::CreateMonitoredEventsResult&          result)
    {
        CreateMonitoredEventsRequest request(
                0,
                serviceConfig,
                sessionConfig,
                subscriptionConfig);

        for (size_t i=0; i<addresses.size(); i++)
            request.targets.push_back(CreateMonitoredEventsRequestTarget(addresses[i],
                                      eventFilter));

        return processRequest(request, result);
    }




    // Manual connection
    //==============================================================================================
    Status Client::manuallyConnect(
            const string&           serverUri,
            const SessionSettings&  settings,
            ClientConnectionId&     clientConnectionId)
    {
        return sessionFactory_->manuallyConnect(serverUri, settings, clientConnectionId);
    }


    // Manual disconnection
    //==============================================================================================
    Status Client::manuallyDisconnect(ClientConnectionId clientConnectionId)
    {
        return sessionFactory_->manuallyDisconnect(clientConnectionId);
    }


    // Manual subscription
    //==============================================================================================
    Status Client::manuallySubscribe(
            ClientConnectionId          clientConnectionId,
            const SubscriptionSettings& settings,
            ClientSubscriptionHandle&   clientSubscriptionHandle)
    {
        return sessionFactory_->manuallySubscribe(
                clientConnectionId, settings, clientSubscriptionHandle);
    }

    // Manual unsubscription
    //==============================================================================================
    Status Client::manuallyUnsubscribe(
            ClientConnectionId          clientConnectionId,
            ClientSubscriptionHandle    clientSubscriptionHandle)
    {
        return sessionFactory_->manuallyUnsubscribe(clientConnectionId, clientSubscriptionHandle);
    }


    // Get information about the session
    // =============================================================================================
    Status Client::sessionInformation(
            ClientConnectionId  clientConnectionId,
            SessionInformation& sessionInformation)
    {
        return sessionFactory_->sessionInformation(clientConnectionId, sessionInformation);
    }


    // Get information about the session
    // =============================================================================================
    vector<SessionInformation> Client::allSessionInformations()
    {
        return sessionFactory_->allSessionInformations();
    }


    // Get information about the subscription
    // =============================================================================================
    Status Client::subscriptionInformation(
            uafc::ClientSubscriptionHandle  clientSubscriptionHandle,
            SubscriptionInformation&        subscriptionInformation)
    {
        return sessionFactory_->subscriptionInformation(
                clientSubscriptionHandle, subscriptionInformation);
    }


    // Get information about the session
    // =============================================================================================
    vector<SubscriptionInformation> Client::allSubscriptionInformations()
    {
        return sessionFactory_->allSubscriptionInformations();
    }

    // Run the thread
    // =============================================================================================
    void Client::run()
    {
        logger_->debug("Thread has started to periodically check the requests");

        // declare the current time and the time of the last actions
        time_t currentTime;
        time_t lastTime;

        // initialize the time values
        time(&currentTime);
        time(&lastTime);


        double updateInterval;

        while (!doFinishThread_)
        {
            updateInterval = database_->clientSettings.discoveryIntervalSec;

            msleep(100);

            time(&currentTime);

            if (difftime(currentTime, lastTime) > updateInterval)
            {
                logger_->debug("Now discovering the system and checking the persistent requests");

                // update the lastTime
                time(&lastTime);

                if (!doFinishThread_)
                    discoverer_->findServers();

                if (!doFinishThread_)
                    sessionFactory_->doHouseKeeping();

                if (!doFinishThread_)
                    processPersistentRequests(database_->createMonitoredDataRequestStore);

                if (!doFinishThread_)
                    processPersistentRequests(database_->createMonitoredEventsRequestStore);
            }
        }
    }




    // Process a ReadRequest
    // =============================================================================================
    Status Client::processRequest(const uafc::ReadRequest& request, uafc::ReadResult& result)
    {
        return processRequest<ReadService>(request, result);
    }

    // Process a ReadRequest
    // =============================================================================================
    Status Client::processRequest(const uafc::AsyncReadRequest& request, uafc::AsyncReadResult& result)
    {
        return processRequest<AsyncReadService>(request, result);
    }


    // Process a WriteRequest
    // =============================================================================================
    Status Client::processRequest(const uafc::WriteRequest& request, uafc::WriteResult& result)
    {
        return processRequest<uafc::WriteService>(request, result);
    }

    // Process a ReadRequest
    // =============================================================================================
    Status Client::processRequest(const uafc::AsyncWriteRequest& request, uafc::AsyncWriteResult& result)
    {
        return processRequest<AsyncWriteService>(request, result);
    }


    // Process a MethodCallRequest
    // =============================================================================================
    Status Client::processRequest(const uafc::MethodCallRequest& request, uafc::MethodCallResult& result)
    {
        return processRequest<uafc::MethodCallService>(request, result);
    }


    // Process an AsyncMethodCallRequest
    // =============================================================================================
    Status Client::processRequest(
            const uafc::AsyncMethodCallRequest&   request,
            uafc::AsyncMethodCallResult&          result)
    {
        return processRequest<uafc::AsyncMethodCallService>(request, result);
    }


    // Process a CreateMonitoredDataRequest
    // =============================================================================================
    Status Client::processRequest(
            const uafc::CreateMonitoredDataRequest&  request,
            uafc::CreateMonitoredDataResult&         result)
    {
        return processRequest<uafc::CreateMonitoredDataService>(request, result);
    }


    // Process a CreateMonitoredEventsRequest
    // =============================================================================================
    Status Client::processRequest(
            const uafc::CreateMonitoredEventsRequest&  request,
            uafc::CreateMonitoredEventsResult&         result)
    {
        return processRequest<uafc::CreateMonitoredEventsService>(request, result);
    }



    // Private template function implementation: assign a UAF handle
    // =============================================================================================
    template <typename _Service>
    Status Client::assignRequestHandle(
            typename _Service::Request& request,
            typename _Service::Result&  result)
    {
        Status ret;

        // lock the mutex until the locker is out of scope
        UaMutexLocker locker(&requestHandleMutex_);

        // check if we still can increment the handle
        if (currentRequestHandle_ < uafc::REQUESTHANDLE_MAX)
        {
            // increment the handle, assign it to the request and result, and update the status
            currentRequestHandle_++;
            request.requestHandle_ = currentRequestHandle_;
            result.requestHandle   = currentRequestHandle_;
            ret.setGood();
        }
        else
        {
            // more than 2**64 assigned is virtually impossible, we must have discovered a bug!
            ret.setStatus(uaf::statuscodes::UnexpectedError,
                          "Maximum number of UAF handles (2**64!) reached, this must be a bug");
        }

        if (ret.isGood())
            logger_->debug("Assigning handle %d to the request", currentRequestHandle_);
        else
            logger_->error(ret);

        return ret;
    }


    // Private template function implementation: process persistent requests
    // =============================================================================================
    template<typename _Store>
    void Client::processPersistentRequests(_Store& store)
    {
        // create a typedef for the vector holding the correct type of items
        typedef std::vector<typename _Store::Item> Items;

        // get the items that need to be reconstructed
        Items items = store.getBadItems();

        if (items.size() > 0)
            logger_->debug("A total of %d persistent requests need to be re-processed",
                           items.size());

        // loop through the items and process them
        // (We don't have to care about the Status result of the processRequest function,
        // since processPersistentRequests() is called automatically by a thread, and this
        // thread doesn't perform any actions in case of failures.)
        for (typename Items::iterator it = items.begin(); it != items.end(); ++it)
            processRequest<typename _Store::ServiceType>(
                    it->request,
                    it->badTargetsMask,
                    it->result);
    }


    // Private template function implementation: process a request
    // =============================================================================================
    template<typename _Service>
    uaf::Status Client::processRequest(
            const typename _Service::Request&   request,
            typename _Service::Result&          result)
    {
        return processRequest<_Service>(request, uaf::Mask(request.targets.size(), true), result);
    }


    // Private template function implementation: process a masked request
    // =============================================================================================
    template<typename _Service>
    uaf::Status Client::processRequest(
            const typename _Service::Request&   request,
            const uaf::Mask&                    mask,
            typename _Service::Result&          result)
    {
        // declare the return Status
        uaf::Status ret;

        logger_->debug("Processing the following %sRequest:", _Service::name().c_str());
        logger_->debug(request.toString());

        // resize the result
        result.targets.resize(request.targets.size());

        // create a copy of the request (so we can assign a handle, resolve the targets, ...)
        typename _Service::Request copiedRequest(request);

        // get a new unique request handle if necessary,
        // and update the copied request and result with it
        if (request.requestHandle() == uafc::REQUESTHANDLE_NOT_ASSIGNED)
            ret = assignRequestHandle<_Service>(copiedRequest, result);
        else
            ret.setGood();

        // assign notification handles if necessary
        // (this is only needed for CreateMonitoredDataRequests and CreateMonitoredEventsRequests)
        if (ret.isGood())
            ret = uafc::assignNotificationHandlesIfNeeded<_Service>(result, mask, database_);

        // if no error occurred, store the copied request if needed
        // (this is only needed for 'persistent' requests such as CreateMonitoredDataRequests)
        if (ret.isGood())
            ret = uafc::storeIfNeeded<_Service>(
                    copiedRequest,
                    result,
                    result.getBadTargetsMask(),
                    database_);

        // if no error occurred, resolve the unmasked targets of the copied request
        if (ret.isGood())
            ret = resolver_->resolve<_Service>(copiedRequest, mask, result);

        // if no error occurred, mask out the unresolved addresses and invoke the service request
        if (ret.isGood())
        {
            uaf::Mask resolvedMask = mask && result.getGoodTargetsMask();
            ret = sessionFactory_->invokeRequest<_Service>(copiedRequest, resolvedMask, result);
        }

        // finally, update the overall status
        if (ret.isGood())
            result.updateOverallStatus();

        // if no error occurred, update the result if needed
        // (this is only needed for 'persistent' results such as CreateMonitoredDataResults)
        if (ret.isGood())
            ret = updateResultIfNeeded<_Service>(result, mask, database_);

        // log the result, if good
        if (ret.isGood())
        {
            logger_->debug("%sResult %d:", _Service::name().c_str(), result.requestHandle);
            logger_->debug(result.toString());
        }

        return ret;
    }


}

