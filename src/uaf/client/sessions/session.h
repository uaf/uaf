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

#ifndef UAF_SESSION_H_
#define UAF_SESSION_H_


// STD
#include <string>
#include <sstream>
// SDK
#include "uaclient/uaclientsdk.h"
#include "uaclient/uasession.h"
#include "uabase/uastring.h"
#include "uabase/uadir.h"
#include "uapki/uapkicertificate.h"
// UAF
#include "uaf/util/status.h"
#include "uaf/util/logger.h"
#include "uaf/util/serverarray.h"
#include "uaf/util/namespacearray.h"
#include "uaf/util/nodeid.h"
#include "uaf/util/browsepath.h"
#include "uaf/util/status.h"
#include "uaf/util/structuredefinition.h"
#include "uaf/util/helperfunctions.h"
#include "uaf/client/clientexport.h"
#include "uaf/client/sessions/sessionstates.h"
#include "uaf/client/sessions/sessioninformation.h"
#include "uaf/client/settings/sessionsettings.h"
#include "uaf/client/subscriptions/subscriptionfactory.h"
#include "uaf/client/discovery/discoverer.h"
#include "uaf/client/clientservices.h"





namespace uaf
{


    /*******************************************************************************************//**
    * An uaf::Session wraps the Session object of the SDK and adds some functionality.
    *
    * @ingroup ClientSessions
    ***********************************************************************************************/
    class UAF_EXPORT Session
    {
    public:


        /**
         * Construct a session.
         *
         * @param loggerFactory      Logger factory to log all messages to.
         * @param sessionSettings    Settings of the session.
         * @param serverUri          Server URI of the session.
         * @param clientConnectionId Id of the connection.
         * @param uaSessionCallback  Callback interface of the session.
         * @param clientInterface    Client interface to call when asynchronous
         *                           communication is received.
         * @param discoverer         The discoverer of the client.
         * @param database           Pointer to the client database.
         */
        Session(
                uaf::LoggerFactory*             loggerFactory,
                const uaf::SessionSettings&    sessionSettings,
                const std::string&              serverUri,
                uaf::ClientConnectionId         clientConnectionId,
                UaClientSdk::UaSessionCallback* uaSessionCallback,
                uaf::ClientInterface*          clientInterface,
                uaf::Discoverer*               discoverer,
                uaf::Database*                 database);


        /**
         * Destruct the session.
         */
        virtual ~Session();


        ////////////////////////////////////////////////////////////////////////////////////////////
        /**
         *  @name Connection
         *  Connect and disconnect the session.
         */
        ///@{


        /**
         * Connect the session.
         */
        uaf::Status connect();


        /**
         * Connect the session to a specific endpoint.
         */
        uaf::Status connectToSpecificEndpoint(
                const std::string&          endpointUrl,
                const uaf::PkiCertificate&  serverCertificate);


        /**
         * Disconnect the session.
         *
         * @return  Good if the session could be disconnected successfully, bad if not.
         */
        uaf::Status disconnect();


        ///@} //////////////////////////////////////////////////////////////////////////////////////
        /**
         *  @name SessionInfo
         *  Get information about the session.
         */
        ///@{


        /**
         * Check if the session is created on the server side.
         *
         * @return  True if the session is established, False if not.
         */
        bool isConnected() const;


        /**
         * Get information about the session.
         *
         * @return  The information.
         */
        uaf::SessionInformation sessionInformation() const;


        /**
         * Get the client connection id of the session.
         */
        uaf::ClientConnectionId clientConnectionId()        const { return clientConnectionId_; };

        /**
         * Get the server URI of the session.
         */
        std::string serverUri()                             const { return serverUri_; };

        /**
         * Get the settings of the session.
         */
        uaf::SessionSettings sessionSettings()             const { return sessionSettings_; };

        /**
         * Get the state of the session.
         */
        uaf::sessionstates::SessionState sessionState()    const { return sessionState_; };


        ///@} //////////////////////////////////////////////////////////////////////////////////////
        /**
         *  @name Subscriptions
         *  Subscribe, unsubscribe, and get information about subscriptions.
         */
        ///@{

        /**
         * Manually create a subscription.
         *
         * For more info about "manual" methods, see the documentation on the
         * uaf::Client::manuallyConnect method.
         *
         * @param settings              The settings of the subscription you'd like to create.
         * @param clientSubscriptionHandle  Output parameter, giving you the handle of the newly
         *                                  created subscription.
         * @return                      Good if the subscription was successfully created, Bad if
         *                              something went wrong.
         */
        uaf::Status manuallySubscribe(
                const uaf::SubscriptionSettings&   settings,
                uaf::ClientSubscriptionHandle&      clientSubscriptionHandle);


        /**
         * Manually delete a subscription.
         *
         * @param clientSubscriptionHandle  The handle of the subscription.
         * @return                          Good if the subscription could be deleted, bad if there
         *                                  was some problem.
         */
        uaf::Status manuallyUnsubscribe(uaf::ClientSubscriptionHandle clientSubscriptionHandle);


        /**
         * Get information about a particular subscription.
         *
         * @param clientSubscriptionHandle  The handle identifying the subscription.
         * @param subscriptionInformation   Output parameter, giving you the information about the
         *                                  subscription.
         * @return                          Good if the subscription could be found, Bad if not.
         */
        uaf::Status subscriptionInformation(
                 uaf::ClientSubscriptionHandle      clientSubscriptionHandle,
                 uaf::SubscriptionInformation&     subscriptionInformation);


        /**
        * Get some information about the specified monitored item.
        *
        * @param clientHandle               The handle identifying the monitored item.
        * @param monitoredItemInformation   Output parameter: the requested information.
        * @return                           True if the monitored item was found, False if not.
        */
        bool monitoredItemInformation(
                uaf::ClientHandle               clientHandle,
                uaf::MonitoredItemInformation& monitoredItemInformation);

        /**
         * Get information about all subscriptions.
         *
         * @return  A vector of all available SubscriptionInformation.
         */
        std::vector<uaf::SubscriptionInformation> allSubscriptionInformations();


        /**
         * Set the publishing mode of a particular subscription.
         *
         * @param clientSubscriptionHandle  The handle identifying the subscription.
         * @param publishingEnabled         True to enable the subscription, false if not.
         * @param serviceSettings           The service settings to be used.
         * @param subscriptionFound         Output parameter, True if the subscription specified
         *                                  by the clientSubscriptionHandle was found, False if not.
         * @return                          Result of the service call.
         */
        uaf::Status setPublishingMode(
                uaf::ClientSubscriptionHandle  clientSubscriptionHandle,
                bool                           publishingEnabled,
                const uaf::ServiceSettings*   serviceSettings,
                bool&                          subscriptionFound);


        /**
        * Set the monitoring mode for the specified monitored items.
        *
        * @param clientHandles     The ClientHandles of the monitored items to be affected.
        * @param monitoringMode    The new monitoring mode.
        * @param serviceSettings   The service settings to be used.
        * @param results           A vector of statuses (one result for each ClientHandle).
        * @return                  The immediate result of the service call.
        */
        uaf::Status setMonitoringModeIfNeeded(
               std::vector<uaf::ClientHandle>          clientHandles,
               uaf::monitoringmodes::MonitoringMode    monitoringMode,
               const uaf::ServiceSettings*            serviceSettings,
               std::vector<uaf::Status>&               results);

        /**
         * Get the definition of a structured datatype.
         *
         * @param dataTypeId	The NodeId of the structured datatype.
         * @param definition    Output parameter, the definition (if found).
         * @return				DefinitionNotFoundError if no definition was found,
         * 						Good otherwise.
         */
         uaf::Status structureDefinition(
        		 const uaf::NodeId& 		dataTypeId,
				 uaf::StructureDefinition& 	definition);



        ///@} //////////////////////////////////////////////////////////////////////////////////////
        /**
         *  @name ServiceInvocations
         *  Invoke a service within this session.
         */
        ///@{

        /**
         * Invoke the Session service at this level (the Session level).
         *
         * @param request       The SessionRequest corresponding with the invocation.
         * @param invocation    The invocation.
         */
        template<typename _Service>
        uaf::Status invokeService(
                const uaf::BaseSessionRequest<typename _Service::Settings,
                                               typename _Service::RequestTarget,
                                               _Service::asynchronous>& request,
                typename _Service::Invocation& invocation)
        {
            return invocation.invoke(uaSession_, namespaceArray_, serverArray_, logger_);
        }



        /**
         * Invoke the Subscription service at this level (the Subscription level).
         *
         * @param request       The SubscriptionRequest corresponding with the invocation.
         * @param invocation    The invocation.
         */
        template<typename _Service>
        uaf::Status invokeService(
                const uaf::BaseSubscriptionRequest<typename _Service::Settings,
                                                    typename _Service::RequestTarget,
                                                    _Service::asynchronous>& request,
                typename _Service::Invocation& invocation)
        {
            return subscriptionFactory_->invokeService<_Service>(
                    invocation,
                    request,
                    namespaceArray_,
                    serverArray_);
        }


        ///@} //////////////////////////////////////////////////////////////////////////////////////
        /**
         *  @name Misc.
         *  Miscellaneous methods.
         */
        ///@{


        /**
         * Get a compact string representation of the Session.
         *
         * @return  Compact string representation.
         */
        std::string toString() const;


        /**
         * Change the state of the session.
         *
         * @param sessionState     The new state.
         */
        void setSessionState(uaf::sessionstates::SessionState sessionState);


        /**
         * Change the last connection attempt status.
         *
         * @param status The new status.
         */
        void setConnectionStatus(
                uaf::connectionsteps::ConnectionStep   step,
                uaf::Status                            error,
                bool                                   clientSideError);


        ///@}

    private:


        DISALLOW_COPY_AND_ASSIGN(Session);


        /**
         * Update the ServerArray and NamespaceArray (not locked!).
         *
         * @return  Good if the arrays could be fetched, false if not.
         */
        uaf::Status updateArrays();


        /**
         * Update the connection info.
         */
        void updateConnectionInfo(
                UaClientSdk::SessionConnectInfo& info,
                uaf::ClientConnectionId clientConnectionId,
                bool retryInitialConnect);


        /**
         * Initialize the PKI store
         */
        uaf::Status initializePkiStore(UaClientSdk::SessionSecurityInfo& uaSecurity);


        /**
         * Load the client certificate from the file specified in the ClientSettings.
         */
        uaf::Status loadClientCertificate(UaClientSdk::SessionSecurityInfo& uaSecurity);


        /**
         * Verify the server certificate.
         */
        uaf::Status verifyServerCertificate(UaClientSdk::SessionSecurityInfo& uaSecurity);


        /**
         * Load the server certificate from an endpoint description (which was fetched by the
         * discovery process).
         */
        uaf::Status loadServerCertificateFromEndpoint(
                UaClientSdk::SessionSecurityInfo& uaSecurity,
                const uaf::EndpointDescription& endpoint);


        /**
         * Set the user security info based on the given security settings.
         */
        uaf::Status setUserIdentity(
                UaClientSdk::SessionSecurityInfo& uaSecurity,
                const uaf::SessionSecuritySettings& securitySettings);

        /**
         * Helper function to check if a path exists, or create the path if needed.
         */
        uaf::Status checkOrCreatePath(
                bool checkOnly,
                const std::string& path,
                const std::string& description) const;


        // Wrapped SDK session instance and callback instance
        UaClientSdk::UaSession*             uaSession_;
        UaClientSdk::UaSessionCallback*     uaSessionCallback_;

        // server and namespace arrays
        uaf::ServerArray                    serverArray_;
        uaf::NamespaceArray                 namespaceArray_;

        // the current session state:
        uaf::sessionstates::SessionState   sessionState_;

        // the last connection attempt information:
        uaf::connectionsteps::ConnectionStep lastConnectionAttemptStep_;
        uaf::Status                          lastConnectionAttemptStatus_;

        // fixed session properties:
        uaf::ClientConnectionId             clientConnectionId_;
        std::string                         serverUri_;
        uaf::SessionSettings               sessionSettings_;

        // the logger of the session
        uaf::Logger*                        logger_;
        // pointer to the client databse
        uaf::Database*                     database_;
        // the subscription factory of this session
        uaf::SubscriptionFactory*          subscriptionFactory_;
        // the SessionConnectInfo
        UaClientSdk::SessionConnectInfo     uaSessionConnectInfo_;
        UaClientSdk::SessionConnectInfo     uaSessionConnectInfoNoInitialRetry_;
        // mutex for critical sections
        UaMutex                             sessionMutex_;
        // the RequesterInterface to call when asynchronous messages are received
        uaf::ClientInterface*              clientInterface_;
        // the Discoverer to use
        uaf::Discoverer*                   discoverer_;


    };


}


#endif /* UAF_SESSION_H_ */
