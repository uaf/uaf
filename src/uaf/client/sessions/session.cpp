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
      lastConnectionAttemptStep_(connectionsteps::NoAttemptYet),
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

        updateConnectionInfo(uaSessionConnectInfo_, clientConnectionId, true);
        updateConnectionInfo(uaSessionConnectInfoNoInitialRetry_, clientConnectionId, false);

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
    void Session::updateConnectionInfo(
            UaClientSdk::SessionConnectInfo& info,
            ClientConnectionId clientConnectionId,
            bool retryInitialConnect)
    {
        Status ret;

        // update the session specific settings
        info.clientConnectionId   = clientConnectionId;
        info.nSessionTimeout      = uint32_t(sessionSettings_.sessionTimeoutSec * 1000);
        info.nConnectTimeout      = uint32_t(sessionSettings_.connectTimeoutSec * 1000);
        info.nWatchdogTimeout     = uint32_t(sessionSettings_.watchdogTimeoutSec * 1000);
        info.nWatchdogTime        = uint32_t(sessionSettings_.watchdogTimeSec * 1000);

        // update the client specific settings
        info.sApplicationName     = UaString(database_->clientSettings.applicationName.c_str());
        info.sApplicationUri      = UaString(database_->clientSettings.applicationUri.c_str());
        info.sProductUri          = UaString(database_->clientSettings.productUri.c_str());
        info.sLocaleId            = UaString(database_->clientSettings.localeId.c_str());

        // update the UAF specific settings
        info.bRetryInitialConnect = retryInitialConnect ? OpcUa_True : OpcUa_False;
        info.bAutomaticReconnect  = OpcUa_True;
    }


    // Initialize the PKI store
    // =============================================================================================
    Status Session::initializePkiStore(UaClientSdk::SessionSecurityInfo& uaSecurity)
    {
        Status ret;
        logger_->debug("Initializing the PKI store");

        string certificateRevocationListLocation = \
                database_->clientSettings.certificateRevocationListLocation;
        string certificateTrustListLocation = \
                database_->clientSettings.certificateTrustListLocation;
        string issuersRevocationListLocation = \
                database_->clientSettings.issuersRevocationListLocation;
        string issuersCertificatesLocation = \
                database_->clientSettings.issuersCertificatesLocation;

        bool checkOnly = !(database_->clientSettings.createSecurityLocationsIfNeeded);

        ret = checkOrCreatePath(
                checkOnly,
                certificateRevocationListLocation,
                "certificate revocation list location");

        if (ret.isGood())
            Status ret = checkOrCreatePath(
                    checkOnly,
                    certificateTrustListLocation,
                    "certificate trust list location");

        if (ret.isGood())
            Status ret = checkOrCreatePath(
                    checkOnly,
                    issuersRevocationListLocation,
                    "issuers revocation trust list location");

        if (ret.isGood())
            Status ret = checkOrCreatePath(
                    checkOnly,
                    issuersCertificatesLocation,
                    "issuers certificates location");

        if (ret.isGood())
        {
            UaStatus uaStatus = uaSecurity.initializePkiProviderOpenSSL(
                    UaString(certificateRevocationListLocation.c_str()),
                    UaString(certificateTrustListLocation.c_str()),
                    UaString(issuersRevocationListLocation.c_str()),
                    UaString(issuersCertificatesLocation.c_str()));
            ret.fromSdk(uaStatus.statusCode(), "Could not initialize the PKI store");
        }

        if (ret.isGood())
            logger_->debug("The PKI store has been initialized");
        else
            logger_->error(ret);

        return ret;
    }


    // Load the client certificate from a file
    // =============================================================================================
    Status Session::loadClientCertificate(UaClientSdk::SessionSecurityInfo& uaSecurity)
    {
        logger_->debug("Loading the client certificate and private key");

        string clientCertificate = database_->clientSettings.clientCertificate;
        string clientPrivateKey = database_->clientSettings.clientPrivateKey;

        const bool checkOnly = true;

        Status ret = checkOrCreatePath(checkOnly, clientCertificate, "client certificate");

        if (ret.isGood())
            ret = checkOrCreatePath(checkOnly, clientPrivateKey, "client private key");

        if (ret.isGood())
        {
            UaStatus uaStatus = uaSecurity.loadClientCertificateOpenSSL(
                    UaString(clientCertificate.c_str()),
                    UaString(clientPrivateKey.c_str()));
            ret.fromSdk(uaStatus.statusCode(), "Could not load the client certificate");
        }

        if (ret.isGood())
            logger_->debug("The client certificate and private key are loaded");
        else
            logger_->error(ret);

        return ret;
    }


//    // Load the server certificate from a file
//    // =============================================================================================
//    Status Session::loadServerCertificateFromFile(UaClientSdk::SessionSecurityInfo& uaSecurity)
//    {
//        Status ret;
//        logger_->debug("Loading the server certificate from file");
//
//        string certificate = replacePathSeparators(replaceVariables(
//                database_->clientSettings.serverCertificateAbsoluteFileName));
//
//        logger_->debug("Server certificate: %s", certificate.c_str());
//
//        UaStatus uaStatus = uaSecurity.loadServerCertificateOpenSSL(UaString(certificate.c_str()));
//
//        ret.fromSdk(uaStatus.statusCode(), "Could not load the server certificate");
//        return ret;
//    }


    // Load the server certificate from an endpoint
    // =============================================================================================
    Status Session::loadServerCertificateFromEndpoint(
                    UaClientSdk::SessionSecurityInfo& uaSecurity,
                    const EndpointDescription& endpoint)
    {
        Status ret;
        logger_->debug("Loading the server certificate from the endpoint");

        if (!endpoint.serverCertificate.isNull())
        {
            endpoint.serverCertificate.toSdk(uaSecurity.serverCertificate);
            ret.setGood();
        }
        else
            ret.setStatus(statuscodes::SecurityError, "Server did not provide a certificate!");

        return ret;
    }


    // Set the user identity
    // =============================================================================================
    Status Session::setUserIdentity(
            UaClientSdk::SessionSecurityInfo& uaSecurity,
            const uafc::SessionSecuritySettings& securitySettings)
    {
        Status ret;
        logger_->debug("Setting the user identity");
        if (securitySettings.userTokenType == usertokentypes::Anonymous)
        {
            logger_->debug("User is not authenticating (anonymous log in)");
            uaSecurity.setAnonymousUserIdentity();
            ret.setGood();
        }
        else if (securitySettings.userTokenType == usertokentypes::UserName)
        {
            logger_->debug("User is authenticating with UserName=%s Password=(hidden)",
                    securitySettings.userName.c_str());

            uaSecurity.setUserPasswordUserIdentity(
                    UaString(securitySettings.userName.c_str()),
                    UaString(securitySettings.userPassword.c_str()));

            ret.setGood();
        }
        else if (securitySettings.userTokenType == usertokentypes::Certificate)
        {
            logger_->debug("User is authenticating with a certificate:");

            string certificate = replacePathSeparators(replaceVariables(
                    securitySettings.userCertificateFileName));

            string privateKey = replacePathSeparators(replaceVariables(
                    securitySettings.userPrivateKeyFileName));

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
                ret.setGood();
            }
        }
        return ret;
    }




    // Connect the session
    // =============================================================================================
    Status Session::verifyServerCertificate(UaClientSdk::SessionSecurityInfo& uaSecurity)
    {
        Status ret;

        logger_->debug("Now verifying the server certificate");

        UaStatus uaTrustStatus(uaSecurity.verifyServerCertificate());

        if (uaTrustStatus.isGood())
        {
            logger_->debug("The server certificate is trusted");
            ret.setGood();
        }
        else
        {
            logger_->debug("The server certificate is NOT trusted");
            logger_->debug("Therefore we call the untrustedServerCertificateReceived(...) callback:");

            ByteString bs;
            bs.fromSdk(uaSecurity.serverCertificate);
            PkiCertificate cert = PkiCertificate::fromDER(bs);

            Status verificationStatus;
            verificationStatus.fromSdk(uaTrustStatus.statusCode(), "The certificated was not trusted");

            PkiCertificate::Action action;
            action = clientInterface_->untrustedServerCertificateReceived(cert, verificationStatus);

            if (action == PkiCertificate::Action_Reject)
            {
                logger_->debug("The server certificate was rejected by the user");
                ret.setStatus(statuscodes::SecurityError,
                              "The server certificate was rejected by the user");
            }
            else if (action == PkiCertificate::Action_AcceptTemporarily)
            {
                logger_->debug("The server certificate was accepted temporarily by the user");
                uaSecurity.doServerCertificateVerify = false;
                ret.setGood();
            }
            else if (action == PkiCertificate::Action_AcceptPermanently)
            {
                logger_->debug("The server certificate was accepted permanently by the user");
                logger_->debug("We therefore try to store the certificate first");
                UaPkiCertificate uaCert = UaPkiCertificate::fromDER(uaSecurity.serverCertificate);
                UaString uaThumbprint = uaCert.thumbPrint().toHex();

                logger_->debug("Name of the certificate (thumbprint): %s", uaThumbprint.toUtf8());

                UaStatus savingStatus = uaSecurity.saveServerCertificate(uaThumbprint);

                if (savingStatus.isGood())
                {
                    logger_->debug("Certificate %s was stored", uaThumbprint.toUtf8());
                    ret.setGood();
                }
                else
                {
                    ret.fromSdk(savingStatus.statusCode(), "Could not save the certificate");
                }
                uaSecurity.doServerCertificateVerify = true;
            }
        }

        return ret;
    }


    // Connect the session
    // =============================================================================================
    Status Session::connect()
    {
        Status ret;
        logger_->debug("Connecting the session");

        // reset the last connection attempt step and status
        lastConnectionAttemptStep_ = connectionsteps::NoAttemptYet;
        lastConnectionAttemptStatus_.setUncertain();

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

        if (ret.isGood())
        {
            logger_->debug("The following SessionSecuritySettings were found suitable:");
            logger_->debug(suitableSettings.toString());
            logger_->debug("The following endpoint was found suitable:");
            logger_->debug(suitableEndpoint.toString());
        }

        // initialize the PKI store so that we can verify the server certificate
        if (ret.isGood())
            ret = initializePkiStore(uaSecurity);

        // load the server certificate from the endpoint description
        if (ret.isGood())
            ret = loadServerCertificateFromEndpoint(uaSecurity, suitableEndpoint);

        // always verify the server certificate
        if (ret.isGood())
            ret = verifyServerCertificate(uaSecurity);

        // only load the client certificate if we need to sign or encrypt the data!
        if (ret.isGood())
        {
            if (   suitableSettings.messageSecurityMode == messagesecuritymodes::Mode_Sign
                || suitableSettings.messageSecurityMode == messagesecuritymodes::Mode_SignAndEncrypt)
                ret = loadClientCertificate(uaSecurity);
            else
                logger_->debug("Security is not needed so we don't need to initialize the PKI store");
        }

        // try to set the user identity, security policy and message security mode
        if (ret.isGood())
        {
            setUserIdentity(uaSecurity, suitableSettings);
            uaSecurity.sSecurityPolicy     = UaString(suitableSettings.securityPolicy.c_str());
            uaSecurity.messageSecurityMode = messagesecuritymodes::fromUafToSdk(
                                                        suitableSettings.messageSecurityMode);
        }

        // if everything is OK, we can try to connect!
        if (ret.isGood())
        {
            logger_->debug("Now connecting the session at the SDK level");

            UaStatus uaStatus = uaSession_->connect(
                    suitableEndpoint.endpointUrl.c_str(),
                    uaSessionConnectInfo_,//uaSessionConnectInfo_, uaSessionConnectInfoNoInitialRetry_
                    uaSecurity,
                    uaSessionCallback_);

            // update the return status
            ret.fromSdk(uaStatus.statusCode(),
                        "Could not connect to %s", suitableEndpoint.endpointUrl.c_str());
        }

        // log the result
        if (ret.isGood())
            logger_->debug("The connection was finished (%s)", ret.toString().c_str());
        else
        {
            ret.addDiagnostic("Connection failed");
            logger_->error(ret);
        }

        // update the lastConnectionAttemptStatus_ and lastConnectionAttemptStep_ if they
        // weren't updated yet by a connectError event:
        if (lastConnectionAttemptStep_ == connectionsteps::NoAttemptYet)
        {
            lastConnectionAttemptStep_ = connectionsteps::ActivateSession;
            lastConnectionAttemptStatus_ = ret;
        }

        return ret;
    }


    // Connect to a specific endpoint
    // =============================================================================================
    Status Session::connectToSpecificEndpoint(
            const string&           endpointUrl,
            const PkiCertificate&   serverCertificate)
    {
        Status ret;

        logger_->debug("Connecting the session to endpoint %s", endpointUrl.c_str());

        if (sessionSettings_.securitySettingsList.size() == 0)
            ret.setStatus(uaf::statuscodes::InvalidRequestError,
                          "Can't connect to endpoint %s because no security settings given "
                          "(empty securitySettingsList)!", endpointUrl.c_str());

        // try to connect to the endpoint URL for each of SessionSecuritySettings that are
        // given by the SessionSettings
        typedef vector<SessionSecuritySettings>::const_iterator Iter;
        for(Iter securitySettings = sessionSettings_.securitySettingsList.begin();
            securitySettings != sessionSettings_.securitySettingsList.end() && ret.isNotGood();
            ++securitySettings)
        {
            logger_->debug("Trying to connect with the following security settings:");
            logger_->debug(securitySettings->toString());

            Status connectionAttemptStatus;
            connectionAttemptStatus.setGood();

            // declare the SDK SessionSecurityInfo
            UaClientSdk::SessionSecurityInfo uaSecurity;

            // ============

            // initialize the PKI store so that we can verify the server certificate
            if (ret.isGood())
                ret = initializePkiStore(uaSecurity);

            // load the server certificate
            if (ret.isGood())
                serverCertificate.toDER().toSdk(uaSecurity.serverCertificate);

            // always verify the server certificate
            if (ret.isGood())
                ret = verifyServerCertificate(uaSecurity);

            // only load the client certificate if we need to sign or encrypt the data!
            if (ret.isGood())
            {
                if (   securitySettings->messageSecurityMode == messagesecuritymodes::Mode_Sign
                    || securitySettings->messageSecurityMode == messagesecuritymodes::Mode_SignAndEncrypt)
                    ret = loadClientCertificate(uaSecurity);
                else
                    logger_->debug("Security is not needed so we don't need to initialize the PKI store");
            }

            // try to set the user identity, security policy and message security mode
            if (ret.isGood())
            {
                setUserIdentity(uaSecurity, *securitySettings);
                uaSecurity.sSecurityPolicy     = UaString(securitySettings->securityPolicy.c_str());
                uaSecurity.messageSecurityMode = messagesecuritymodes::fromUafToSdk(
                        securitySettings->messageSecurityMode);
            }

            // if everything is OK, we can try to connect!
            if (connectionAttemptStatus.isGood())
            {
                logger_->debug("Now connecting the session at the SDK level");

                UaStatus uaStatus = uaSession_->connect(
                        endpointUrl.c_str(),
                        uaSessionConnectInfoNoInitialRetry_,
                        uaSecurity,
                        uaSessionCallback_);

                logger_->error("Connection result: %s", uaStatus.toString().toUtf8());

                // if the resulting statuscode is simply "Bad", make it a ConnectionError:
                if (uaStatus.statusCode() == OpcUa_Bad)
                    connectionAttemptStatus.setStatus(
                            uaf::statuscodes::ConnectionError,
                            "Could not connect to %s", endpointUrl.c_str());
                else
                    connectionAttemptStatus.fromSdk(
                            uaStatus.statusCode(),
                            "Could not connect to %s", endpointUrl.c_str());
            }

            ret = connectionAttemptStatus;
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
        uafc::SessionInformation info(
                clientConnectionId_,
                sessionState_,
                serverUri_,
                lastConnectionAttemptStep_,
                lastConnectionAttemptStatus_);
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
                        // when manually connecting to an endpoint, no server URI is known yet
                        // In this case serverUri_ is an empty string.
                        if (serverUri_.length() == 0)
                        {
                            logger_->debug("No serverUri was known for this session,"
                                           "so we can now update it to %s", thisServerUri.c_str());
                            serverUri_ = thisServerUri;
                        }
                        else
                        {
                            logger_->warning("ServerArray[0] is not the same as the server URI "
                                             "that was found during the discovery process:");
                            logger_->warning(" - ServerArray[0]       : %s", thisServerUri.c_str());
                            logger_->warning(" - discovered serverUri : %s", serverUri_.c_str());
                            logger_->warning("This means that the server is not configured "
                                             "correctly");
                            logger_->warning("The UAF will therefore ignore ServerArray[0] and use "
                                             "the server URI that was found during the discovery "
                                             "process instead");
                            serverArray_.update(0, serverUri_);
                            logger_->debug("ServerArray with modified ServerArray[0]:");
                        }
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
            ClientHandle                clientHandle,
            MonitoredItemInformation&   monitoredItemInformation)
    {
        return subscriptionFactory_->monitoredItemInformation(clientHandle, monitoredItemInformation);
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

        // call the callback interface
        clientInterface_->connectionStatusChanged(sessionInformation());
    }


    // Set the connection status.
    // =============================================================================================
    void Session::setConnectionStatus(
            uafc::connectionsteps::ConnectionStep   step,
            uaf::Status                             error,
            bool                                    clientSideError)
    {
        lastConnectionAttemptStep_   = step;
        lastConnectionAttemptStatus_ = error;
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


    // Set the monitoring mode
    // =============================================================================================
    Status Session::setMonitoringModeIfNeeded(
            vector<ClientHandle>            clientHandles,
            monitoringmodes::MonitoringMode monitoringMode,
            const ServiceSettings&          serviceSettings,
            vector<Status>&                 results)
    {
        return subscriptionFactory_->setMonitoringModeIfNeeded(clientHandles,
                                                               monitoringMode,
                                                               serviceSettings,
                                                               results);
    }


    // Set the publishing mode.
    // =============================================================================================
    Status Session::checkOrCreatePath(
            bool checkOnly, const string& path, const string& description) const
    {
        Status ret;

        logger_->debug("Checking %s: %s", description.c_str(), path.c_str());
        UaDir helperDir(UaUniString(""));
        if (helperDir.exists(UaUniString(path.c_str())))
        {
            ret.setGood();
            logger_->debug("OK, the %s exists", description.c_str());
        }
        else
        {
            if (checkOnly)
            {
                ret.setStatus(uaf::statuscodes::ConfigurationError,
                              "The %s '%s' does not exist", description.c_str(), path.c_str());
                logger_->error(ret);
            }
            else
            {
                logger_->debug("The path does not exist so we try to create it");
                if (helperDir.mkpath(UaUniString(path.c_str())))
                {
                    ret.setGood();
                    logger_->debug("%s has been created", path.c_str());
                }
                else
                {
                    ret.setStatus(uaf::statuscodes::ConfigurationError,
                                  "Failed to create the %s location (%s)",
                                  description.c_str(), path.c_str());
                    logger_->error(ret);
                }
            }
        }

        return ret;
    }
}
