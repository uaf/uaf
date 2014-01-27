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

#include "uaf/client/sessions/session.h"

namespace uafc
{
    using namespace uaf;
    using namespace uafc;
    using std::string;
    using std::stringstream;
    using std::vector;
    using std::size_t;
    using std::pair;


    // Constructor
    // =============================================================================================
    Session::Session(
            LoggerFactory*                  loggerFactory,
            const SessionSettings&          sessionSettings,
            const string&                   serverUri,
            ClientConnectionId              clientConnectionId,
            UaClientSdk::UaSessionCallback* uaSessionCallback,
            ClientInterface*                clientInterface,
            Discoverer*                     discoverer,
            Database*                       database)
    : uaSessionCallback_(uaSessionCallback),
      sessionState_(uafc::sessionstates::Disconnected),
      clientConnectionId_(clientConnectionId),
      serverUri_(serverUri),
      sessionSettings_(sessionSettings),
      database_(database),
      clientInterface_(clientInterface),
      discoverer_(discoverer)
    {
        // build the logger name:
        stringstream loggerName;
        loggerName << "Session-" << clientConnectionId;
        logger_ = new Logger(loggerFactory, loggerName.str());

        // create a UaSession
        uaSession_ = new UaClientSdk::UaSession();

        // create a subscription factory
        subscriptionFactory_ = new SubscriptionFactory(
                loggerFactory,
                clientConnectionId,
                uaSession_,
                clientInterface_,
                database);

        updateConnectionInfo(clientConnectionId);

        logger_->debug("Session %d to %s has been constructed, now waiting for connection",
                       clientConnectionId_, serverUri_.c_str());
        logger_->debug("Session settings:");
        logger_->debug(sessionSettings.toString());
    }


    // Destructor
    // =============================================================================================
    Session::~Session()
    {
        // try to disconnect the session
        Status disconnectionStatus = disconnect();

        // delete the subscription factory
        delete subscriptionFactory_;
        subscriptionFactory_ = 0;

        // delete the UaSession
        delete uaSession_;
        uaSession_ = 0;

        // delete the logger
        delete logger_;
        logger_ = 0;
    }


    // Update the connection info
    // =============================================================================================
    void Session::updateConnectionInfo(ClientConnectionId clientConnectionId)
    {
        Status ret;

        // update the session specific settings
        uaSessionConnectInfo_.clientConnectionId   = clientConnectionId;
        uaSessionConnectInfo_.nSessionTimeout      = uint32_t(sessionSettings_.sessionTimeoutSec * 1000);
        uaSessionConnectInfo_.nConnectTimeout      = uint32_t(sessionSettings_.connectTimeoutSec * 1000);
        uaSessionConnectInfo_.nWatchdogTimeout     = uint32_t(sessionSettings_.watchdogTimeoutSec * 1000);
        uaSessionConnectInfo_.nWatchdogTime        = uint32_t(sessionSettings_.watchdogTimeSec * 1000);

        // update the client specific settings
        uaSessionConnectInfo_.sApplicationName     = UaString(database_->clientSettings.applicationName.c_str());
        uaSessionConnectInfo_.sApplicationUri      = UaString(database_->clientSettings.applicationUri.c_str());
        uaSessionConnectInfo_.sProductUri          = UaString(database_->clientSettings.productUri.c_str());
        uaSessionConnectInfo_.sLocaleId            = UaString(database_->clientSettings.localeId.c_str());

        // update the UAF specific settings
        uaSessionConnectInfo_.bRetryInitialConnect = OpcUa_True;
        uaSessionConnectInfo_.bAutomaticReconnect  = OpcUa_True;
    }


    Status Session::connect()
    {
        Status ret;

        logger_->debug("Connecting the session");

        // declare an empty list of discovery URLs and endpoint descriptions
        vector<string>              discoveryUrls;
        vector<EndpointDescription> discoveredEndpoints;

        // declare a suitable SessionSecuritySettings and suitable Endpoint
        SessionSecuritySettings suitableSettings;
        EndpointDescription     suitableEndpoint;

        // get the discovery URL(s) for this server URI
        ret = discoverer_->getDiscoveryUrls(serverUri_, discoveryUrls);

        // use the discoverer to request the endpoint URLs for the given discovery URL(s)
        for (vector<string>::const_iterator it = discoveryUrls.begin();
             it != discoveryUrls.end() && ret.isGood();
             ++it)
        {
            vector<EndpointDescription> tmp;
            ret = discoverer_->getEndpoints(*it, tmp);

            if (ret.isGood())
                discoveredEndpoints.insert(discoveredEndpoints.end(), tmp.begin(), tmp.end());
        }

        // in case discovery went fine, check if we found some endpoints
        if (ret.isGood() && discoveredEndpoints.size() == 0)
            ret.setStatus(statuscodes::DiscoveryError, "No endpoints were found");

        // declare the SDK SessionSecurityInfo
        UaClientSdk::SessionSecurityInfo uaSecurity;

        // if the endpoints were gotten, match the endpoints with the given SessionSecuritySettings
        if (ret.isGood())
            ret = match(
                  sessionSettings_.securitySettingsList,
                  discoveredEndpoints,
                  suitableSettings,
                  suitableEndpoint);

        // check if we need to use certificates
        bool certificatesNeeded = \
                suitableSettings.messageSecurityMode == messagesecuritymodes::Mode_Sign
             || suitableSettings.messageSecurityMode == messagesecuritymodes::Mode_SignAndEncrypt
             || suitableSettings.userTokenType == usertokentypes::Certificate
             || suitableSettings.userTokenType == usertokentypes::IssuedToken;

        // try to initialize the certificate store if needed
        if (certificatesNeeded && ret.isGood())
        {
            logger_->debug("Initializing the PKI store");

            string revocationList = replacePathSeparators(replaceVariables(
                    database_->clientSettings.certificateRevocationListAbsoluteFileName));

            string trustDirectory = replacePathSeparators(replaceVariables(
                    database_->clientSettings.certificateTrustAbsoluteDirectory));

            logger_->debug(" - Revocation list : %s", revocationList.c_str());
            logger_->debug(" - Trust directory : %s", trustDirectory.c_str());

            UaStatus uaStatus = uaSecurity.initializePkiProviderOpenSSL(
                    UaString(revocationList.c_str()),
                    UaString(trustDirectory.c_str()));

            ret.fromSdk(uaStatus.statusCode(), "Could not initialize the PKI store");
        }

        // try to load the client certificate if needed
        if (certificatesNeeded && ret.isGood())
        {
            logger_->debug("Loading the client certificate");

            string certificate = replacePathSeparators(replaceVariables(
                    database_->clientSettings.clientCertificateAbsoluteFileName));

            string privateKey = replacePathSeparators(replaceVariables(
                    database_->clientSettings.clientPrivateKeyAbsoluteFileName));

            logger_->debug(" - Client certificate : %s", certificate.c_str());
            logger_->debug(" - Client private key : %s", privateKey.c_str());

            UaStatus uaStatus = uaSecurity.loadClientCertificateOpenSSL(
                    UaString(certificate.c_str()),
                    UaString(privateKey.c_str()));

            ret.fromSdk(uaStatus.statusCode(), "Could not load the client certificate");
        }

        // try to load the server certificate if needed
        if (certificatesNeeded && ret.isGood())
        {
            logger_->debug("Loading the server certificate from the endpoint");

            if (suitableEndpoint.serverCertificate.first > 0)
                uaSecurity.serverCertificate = UaByteString(
                        suitableEndpoint.serverCertificate.first,
                        suitableEndpoint.serverCertificate.second);
            else
                ret.setStatus(statuscodes::SecurityError, "Server did not provide a certificate!");
        }

        // try to set the user identity
        if (ret.isGood())
        {
            if (suitableSettings.userTokenType == usertokentypes::Anonymous)
            {
                logger_->debug("User is not authenticating (anonymous log in)");
                uaSecurity.setAnonymousUserIdentity();
            }
            else if (suitableSettings.userTokenType == usertokentypes::UserName)
            {
                logger_->debug("User is authenticating with UserName=%s Password=(hidden)",
                               suitableSettings.userName.c_str());

                uaSecurity.setUserPasswordUserIdentity(
                        UaString(suitableSettings.userName.c_str()),
                        UaString(suitableSettings.userPassword.c_str()));
            }
            else if (suitableSettings.userTokenType == usertokentypes::Certificate)
            {
                logger_->debug("User is authenticating with a certificate:");

                string certificate = replacePathSeparators(replaceVariables(
                        suitableSettings.userCertificateFileName));

                string privateKey = replacePathSeparators(replaceVariables(
                        suitableSettings.userPrivateKeyFileName));

                logger_->debug(" - User certificate : %s", certificate.c_str());
                logger_->debug(" - User private key : %s", privateKey.c_str());

                UaPkiCertificate uaUserCertificate = UaPkiCertificate::fromDERFile(
                                                            certificate.c_str());
                UaPkiRsaKeyPair uaUserPrivateKey   = UaPkiRsaKeyPair::fromPEMFile(
                                                            privateKey.c_str(),
                                                            OpcUa_Null);

                if (uaUserCertificate.isNull())
                {
                    ret.setStatus(statuscodes::SecurityError,
                                  "User certificate %s can not be imported!", certificate.c_str());
                }
                else if (!uaUserPrivateKey.isValid())
                {
                    ret.setStatus(statuscodes::SecurityError,
                                  "User private key %s is invalid!", privateKey.c_str());
                }
                else
                {
                    UaByteArray baUserCertificate = uaUserCertificate.toDER();
                    UaByteArray baUserPrivateKey  = uaUserPrivateKey.toDER();

                    UaByteString bsUserCertificate(
                            baUserCertificate.size(),
                            (OpcUa_Byte*)baUserCertificate.data());
                    UaByteString bsUserPrivateKey(
                            baUserPrivateKey.size(),
                            (OpcUa_Byte*)baUserPrivateKey.data());

                    uaSecurity.setCertificateUserIdentity(bsUserCertificate, bsUserPrivateKey);
                }
            }
        }

        // set the remaining security parameters
        if (ret.isGood())
        {
            uaSecurity.sSecurityPolicy     = UaString(suitableSettings.securityPolicy.c_str());
            uaSecurity.messageSecurityMode = messagesecuritymodes::fromUafToSdk(
                                                        suitableSettings.messageSecurityMode);

            // we let the SDK verify the server certificate
            uaSecurity.doServerCertificateVerify = true;
        }

        // if everything is OK, we can try to connect!
        if (ret.isGood())
        {
            logger_->debug("Now connecting the session at the SDK level");

            UaStatus uaStatus = uaSession_->connect(
                    suitableEndpoint.endpointUrl.c_str(),
                    uaSessionConnectInfo_,
                    uaSecurity,
                    uaSessionCallback_);

            // update the return status
            ret.fromSdk(uaStatus.statusCode(),
                        "Could not connect to %s", suitableEndpoint.endpointUrl.c_str());
        }

        // log the result
        if (ret.isGood())
            logger_->debug("The session has been connected successfully");
        else
        {
            // add some info
            ret.addDiagnostic("Connection failed");
            logger_->error(ret);
        }

        return ret;
    }


    // Disconnect the session
    // =============================================================================================
    Status Session::disconnect()
    {
        Status ret;

        // disconnect the session (and delete the subscriptions)
        if (uaSession_->isConnected())
        {
            logger_->debug("Now disconnecting %s and thereby deleting all subscriptions",
                           toString().c_str());

            // try to disconnect (and delete subscriptions)
            UaClientSdk::ServiceSettings serviceSettings;
            UaStatus uaStatus = uaSession_->disconnect(serviceSettings, OpcUa_True);

            ret.fromSdk(uaStatus.statusCode(),
                                   "The session could not be disconnected");

            // log the result
            if (ret.isGood())
                logger_->debug("The session has been disconnected successfully");
            else
                logger_->error(ret);
        }
        else
        {
            logger_->debug("The session was already disconnected");
            ret.setGood();
        }

        return ret;
    }


    // Get information about the session
    // =============================================================================================
    uafc::SessionInformation Session::sessionInformation() const
    {
        uafc::SessionInformation info(clientConnectionId_, sessionState_, serverUri_);
        logger_->debug("Fetching session information:");
        logger_->debug(info.toString());
        return info;
    }


    // Check if the session is established
    // =============================================================================================
    bool Session::isConnected() const
    {
        return sessionState_ == uafc::sessionstates::Connected;
    }


    // Update the server array and namespace array
    // =============================================================================================
    Status Session::updateArrays()
    {
        logger_->debug("Updating the ServerArray and NamespaceArray");

        Status ret;

        if (!isConnected())
        {
            ret.setStatus(statuscodes::ConnectionError,
                          "Cannot update the arrays (session is not connected)");
            logger_->error(ret);
        }
        else
        {
            UaStatus                        uaReadStatus;
            UaReadValueIds                  uaReadValueIds;
            UaDataValues                    uaDataValues;
            UaDiagnosticInfos               uaDiagnosticInfos;
            UaClientSdk::ServiceSettings    uaServiceSettings;

            // update the SDK service settings
            sessionSettings_.readServerInfoSettings.toSdk(uaServiceSettings);

            // two values will need to be read (the server array and namespace array)
            uaReadValueIds.create(2);
            //  1) the server array:
            UaNodeId(OpcUaId_Server_ServerArray).copyTo(&uaReadValueIds[0].NodeId);
            uaReadValueIds[0].AttributeId = OpcUa_Attributes_Value;
            //  2) the namespace array:
            UaNodeId(OpcUaId_Server_NamespaceArray).copyTo(&uaReadValueIds[1].NodeId);
            uaReadValueIds[1].AttributeId = OpcUa_Attributes_Value;

            // perform the read action
            uaReadStatus = uaSession_->read(
                    uaServiceSettings,                  // service settings
                    0,                                  // max age in milliseconds
                    OpcUa_TimestampsToReturn_Neither,   // no time stamps necessary
                    uaReadValueIds,                     // nodes to read
                    uaDataValues,                       // result
                    uaDiagnosticInfos);                 // diagnostics

            // process the result
            if (uaReadStatus.isBad())
            {
                ret.fromSdk(uaReadStatus.statusCode(),
                                       "Couldn't read server and namespace arrays");
                logger_->error(ret);
            }
            else
            {
                // the arrays have been read, so we can store them

                // 1) server array
                // ---------------
                Status serverArrayStatus = serverArray_.fromSdk(uaDataValues[0]);

                // log the result
                if (serverArrayStatus.isBad())
                {
                    serverArrayStatus.addDiagnostic("Could not read the server array");
                    logger_->error(serverArrayStatus);
                }
                else
                {
                    string thisServerUri;
                    if (serverArray_.findServerUri(0, thisServerUri) && thisServerUri != serverUri_)
                    {
                        logger_->warning("ServerArray[0] is not the same as the server URI "
                                         "that was found during the discovery process:");
                        logger_->warning(" - ServerArray[0]       : %s", thisServerUri.c_str());
                        logger_->warning(" - discovered serverUri : %s", serverUri_.c_str());
                        logger_->warning("This means that the server is not configured correctly");
                        logger_->warning("The UAF will therefore ignore ServerArray[0] and use "
                                         "the server URI that was found during the discovery "
                                         "process instead");
                        serverArray_.update(0, serverUri_);
                        logger_->debug("ServerArray with modified ServerArray[0]:");
                    }
                    else
                    {
                        logger_->debug("ServerArray:");
                    }
                    logger_->debug(serverArray_.toString());
                }

                // 2) namespace array
                // ---------------
                Status namespaceArrayStatus = namespaceArray_.fromSdk(uaDataValues[1]);

                // log the result
                if (serverArrayStatus.isBad())
                {
                    serverArrayStatus.addDiagnostic("Could not read the namespace array");
                    logger_->error(serverArrayStatus);
                }
                else
                {
                    logger_->debug("NamespaceArray:");
                    logger_->debug(namespaceArray_.toString());
                }

                // update the return status
                if (serverArrayStatus.isBad())
                    ret = serverArrayStatus;
                else if (namespaceArrayStatus.isBad())
                    ret = namespaceArrayStatus;
                else
                    ret.setGood();
            }
        }

        return ret;
    }


    // Get a compact string representation
    // =============================================================================================
    string Session::toString() const
    {
        stringstream ss;
        ss << "Session-" << clientConnectionId_ << ":" << serverUri_;
        return ss.str();
    }


    // Manual subscription
    //==============================================================================================
    Status Session::manuallySubscribe(
            const SubscriptionSettings& settings,
            ClientSubscriptionHandle&   clientSubscriptionHandle)
    {
        return subscriptionFactory_->manuallySubscribe(settings, clientSubscriptionHandle);
    }


    // Manual unsubscription
    //==============================================================================================
    Status Session::manuallyUnsubscribe(ClientSubscriptionHandle clientSubscriptionHandle)
    {
        return subscriptionFactory_->manuallyUnsubscribe(clientSubscriptionHandle);
    }


    // Get information about all subscriptions
    // =============================================================================================
    vector<SubscriptionInformation> Session::allSubscriptionInformations()
    {
        vector<SubscriptionInformation> ret = subscriptionFactory_->allSubscriptionInformations();

        for (vector<SubscriptionInformation>::iterator it = ret.begin(); it != ret.end(); ++it)
        {
            it->clientConnectionId = clientConnectionId_;
        }

        return ret;
    }


    // Get information about the subscription
    // =============================================================================================
    Status Session::subscriptionInformation(
            ClientSubscriptionHandle    clientSubscriptionHandle,
            SubscriptionInformation&    subscriptionInformation)
    {
        Status ret = subscriptionFactory_->subscriptionInformation(
                clientSubscriptionHandle,
                subscriptionInformation);

        if (ret.isGood())
        {
            subscriptionInformation.clientConnectionId = clientConnectionId_;
        }

        return ret;
    }


    // Get information about the monitored item
    // =============================================================================================
    bool Session::monitoredItemInformation(
            ClientMonitoredItemHandle   clientMonitoredItemHandle,
            MonitoredItemInformation&   monitoredItemInformation)
    {
        return subscriptionFactory_->monitoredItemInformation(
                clientMonitoredItemHandle,
                monitoredItemInformation);
    }


    // Update the session status.
    // =============================================================================================
    void Session::setSessionState(uafc::sessionstates::SessionState sessionState)
    {
        // acquire the session lock
        UaMutexLocker locker(&sessionMutex_); //auto-unlocks when out of scope

        logger_->debug(
                "The session has changed its state from %s to %s",
                uafc::sessionstates::toString(sessionState_).c_str(),
                uafc::sessionstates::toString(sessionState).c_str());

        // update the session state member
        sessionState_ = sessionState;

        // if the session became connected, update the arrays
        if (sessionState == uafc::sessionstates::Connected)
            updateArrays();
        // if the session has difficulties, we remove all references to this serverUri from
        // the address resolution cache (because maybe the node resolution is not valid anymore)
        else if (   (sessionState == uafc::sessionstates::ConnectionErrorApiReconnect)
                 || (sessionState == uafc::sessionstates::ConnectionWarningWatchdogTimeout)
                 || (sessionState == uafc::sessionstates::Disconnected)
                 || (sessionState == uafc::sessionstates::ServerShutdown))
            database_->addressCache.clear(serverUri_);

    }


    // Set the publishing mode.
    // =============================================================================================
    Status Session::setPublishingMode(
            ClientSubscriptionHandle    clientSubscriptionHandle,
            bool                        publishingEnabled,
            const ServiceSettings&      serviceSettings,
            bool&                       subscriptionFound)
    {
        return subscriptionFactory_->setPublishingMode(clientSubscriptionHandle,
                                                       publishingEnabled,
                                                       serviceSettings,
                                                       subscriptionFound);
    }


}
