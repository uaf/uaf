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

#ifndef UAFC_CLIENT_H
#define UAFC_CLIENT_H


// STD
#include <string>
#include <vector>
#include <map>
// SDK
#include "uabase/uathread.h"
#include "uabase/uamutex.h"
#include "uabase/uadatetime.h"
// UAF
#include "uaf/util/logger.h"
#include "uaf/util/mask.h"
#include "uaf/util/logginginterface.h"
#include "uaf/client/clientexport.h"
#include "uaf/client/settings/clientsettings.h"
#include "uaf/client/database/database.h"
#include "uaf/client/resolution/resolver.h"
#include "uaf/client/sessions/sessionfactory.h"
#include "uaf/client/clientservices.h"



namespace uafc
{


    /*******************************************************************************************//**
    * A Client offers a clean API to easily invoke OPC UA services.
    *
    * @ingroup Client
    ***********************************************************************************************/
    class UAFC_EXPORT Client : private UaThread,
                               public uafc::ClientInterface,
                               public uaf::LoggingInterface
    {
    public:


        /**
         * Create a client without a name.
         *
         * The name of the application (reflected in the logging and in
         * uafc::ClientSettings::clientApplicationName) will remain empty.
         */
        Client();


        /**
         * Create a client with a given applicationName.
         *
         * @param applicationName  Name of the client.
         */
        Client(const std::string& applicationName);


        /**
         * Create a client with the given settings.
         *
         * @param settings  The Client settings.
         */
        Client(const uafc::ClientSettings& settings);


        /**
         * Create a client with a given settings and logger factory.
         *
         * @param settings  The Client settings.
         * @param loggerFactory Logger factory to which the client must log all its messages.
         */
        Client(const uafc::ClientSettings& settings, uaf::LoggerFactory* loggerFactory);


        /**
         * Destruct the client.
         */
        virtual ~Client();


        /**
         * Get a copy of the current client settings.
         *
         * @return The currently active client settings.
         */
        uafc::ClientSettings clientSettings() const;


        /**
         * Overwrite the current client settings.
         */
        void setClientSettings(const uafc::ClientSettings& settings);


        ////////////////////////////////////////////////////////////////////////////////////////////
        /**
         *  @name ServerDiscovery
         *  Find the servers in the system.
         */
        ///@{


        /**
         * Find the servers in the system now (i.e. irrespective of the thread running in the
         * background, which is also periodically trying to find the servers in the system).
         */
        uaf::Status findServersNow();


        /**
         * Get a const reference to the servers that were found.
         *
         * @return  A vector of the application descriptions that were discovered.
         */
        const std::vector<uaf::ApplicationDescription>& serversFound() const;


        ///@} //////////////////////////////////////////////////////////////////////////////////////
        /**
         *  @name Convenience
         *  Convenience methods to read, write, create monitored items, ...
         */
        ///@{

        /**
         * Read a number of node attributes synchronously.
         *
         * @param addresses     Addresses of the nodes of which the attributes should be read.
         * @param attributeId   The attribute to be read (e.g. Value or DisplayName).
         * @param serviceConfig Read config.
         * @param sessionConfig Session config.
         * @param result        Result of the request.
         * @return              Client-side status.
         */
        uaf::Status read(
                const std::vector<uaf::Address>&     addresses,
                const uaf::attributeids::AttributeId attributeId,
                const uafc::ReadConfig&              serviceConfig,
                const uafc::SessionConfig&           sessionConfig,
                uafc::ReadResult&                    result);


        /**
         * Read a number of node attributes asynchronously.
         *
         * Note that asynchronous requests MUST be invoked on a single session. Meaning:
         * if you provide multiple addresses to beginRead(), the addresses MUST point to nodes that
         * belong to the same server (as the UAF can currently not reconstruct an asynchronous
         * request that must be "split up" to be called on multiple servers).
         *
         * @param addresses     Addresses of the nodes of which the attributes should be read.
         * @param attributeId   The attribute to be read (e.g. Value or DisplayName).
         * @param serviceConfig Read config.
         * @param sessionConfig Session config.
         * @param result        Result of the request.
         * @return              Client-side status.
         */
        uaf::Status beginRead(
                const std::vector<uaf::Address>&     addresses,
                const uaf::attributeids::AttributeId attributeId,
                const uafc::ReadConfig&              serviceConfig,
                const uafc::SessionConfig&           sessionConfig,
                uafc::AsyncReadResult&               result);


        /**
         * Write a number of node attributes synchronously.
         *
         * @param addresses         Addresses of the nodes of which the attribute should be written.
         * @param data              Data values that should be written (one data value per address).
         * @param attributeId       Attribute id that should be written for all nodes.
         * @param serviceConfig     Write config.
         * @param sessionConfig     Session config.
         * @param result            Result of the request.
         * @return                  Client-side status.
         */
        uaf::Status write(
                const std::vector<uaf::Address>&     addresses,
                const std::vector<uaf::Variant>&     data,
                const uaf::attributeids::AttributeId attributeId,
                const uafc::WriteConfig&             serviceConfig,
                const uafc::SessionConfig&           sessionConfig,
                uafc::WriteResult&                   result);


        /**
         * Write a number of node attributes asynchronously.
         *
         * Note that asynchronous requests MUST be invoked on a single session. Meaning:
         * if you provide multiple addresses to beginWrite(), the addresses MUST point to nodes that
         * belong to the same server (as the UAF can currently not reconstruct an asynchronous
         * request that must be "split up" to be called on multiple servers).
         *
         * @param addresses         Addresses of the nodes of which the attribute should be written.
         * @param data              Data values that should be written (one data value per address).
         * @param attributeId       Attribute id that should be written for all nodes.
         * @param serviceConfig     Write config.
         * @param sessionConfig     Session config.
         * @param result            Result of the request.
         * @return                  Client-side status.
         */
        uaf::Status beginWrite(
                const std::vector<uaf::Address>&     addresses,
                const std::vector<uaf::Variant>&     data,
                const uaf::attributeids::AttributeId attributeId,
                const uafc::WriteConfig&             serviceConfig,
                const uafc::SessionConfig&           sessionConfig,
                uafc::AsyncWriteResult&              result);


        /**
         * Call a single method synchronously.
         *
         * To call multiple methods at once, use the generic processRequest method.
         *
         * @param objectAddress     Address of the parent node of the method.
         * @param methodAddress     Address of the method node.
         * @param inputArguments    Input arguments as a vector of variants.
         * @param serviceConfig     Method call config.
         * @param sessionConfig     Session config.
         * @param result            Result of the request.
         * @return                  Client-side status.
         */
        uaf::Status call(
                const uaf::Address&                 objectAddress,
                const uaf::Address&                 methodAddress,
                const std::vector<uaf::Variant>&    inputArguments,
                const uafc::MethodCallConfig&       serviceConfig,
                const uafc::SessionConfig&          sessionConfig,
                uafc::MethodCallResult&             result);


        /**
         * Call a single method asynchronously.
         *
         * You cannot call multiple methods at once asynchronously
         * (but you can do it synchronously!).
         *
         * @param objectAddress     Address of the parent node of the method.
         * @param methodAddress     Address of the method node.
         * @param inputArguments    Input arguments as a vector of variants.
         * @param serviceConfig     Method call config.
         * @param sessionConfig     Session config.
         * @param result            Result of the request.
         * @return                  Client-side status.
         */
        uaf::Status beginCall(
                const uaf::Address&                 objectAddress,
                const uaf::Address&                 methodAddress,
                const std::vector<uaf::Variant>&    inputArguments,
                const uafc::MethodCallConfig&       serviceConfig,
                const uafc::SessionConfig&          sessionConfig,
                uafc::AsyncMethodCallResult&        result);


        /**
         * Browse one or more nodes synchronously.
         *
         * This is a convenience method, with few parameters. Use the
         * processRequest(BrowseRequest()) function to specify your browse request much more in
         * detail!
         *
         * @param addresses         Addresses of the starting point nodes to browse.
         * @param maxAutoBrowseNext How many times do you allow the UAF to automatically invoke a
         *                          BrowseNext for you (if that's needed to fetch all results)?
         *                          This parameter will always be used instead of the
         *                          maxAutoBrowseNext attribute in the serviceSettings attribute of
         *                          the serviceConfig parameter!
         * @param serviceConfig     Browse config.
         * @param sessionConfig     Session config.
         * @param result            Result of the request.
         * @return                  Client-side status.
         */
        uaf::Status browse(
                const std::vector<uaf::Address>&    addresses,
                uint32_t                            maxAutoBrowseNext,
                const uafc::BrowseConfig&           serviceConfig,
                const uafc::SessionConfig&          sessionConfig,
                uafc::BrowseResult&                 result);


        /**
         * Read the raw historical data from one or more nodes synchronously.
         *
         * This is a convenience method, with few parameters. Use the
         * processRequest(HistoryReadRawModifiedRequest()) function to specify your history read
         * request much more in detail!
         *
         * Since this convenience method is meant to fetch raw historical data, the isReadModified
         * flag of the serviceSettings attribute of the serviceConfig parameter
         * will be forced to False!
         *
         * @param addresses             Addresses of the nodes to that provide the historical data.
         * @param startTime             The start time of the interval from which you would like
         *                              to see the historical data.
         *                              This parameter will always be used instead of the
         *                              startTime attribute in the serviceSettings attribute
         *                              of the serviceConfig parameter!
         * @param endTime               The end time of the interval from which you would like
         *                              to see the historical data.
         *                              This parameter will always be used instead of the
         *                              endTime attribute in the serviceSettings attribute
         *                              of the serviceConfig parameter!
         * @param numValuesPerNode      The maximum number of values that may be returned for each
         *                              node. 0 means no limit, but you may want to put it to a
         *                              "safe" value (e.g. 100 if you expect to receive at most
         *                              50 historical values or so) to make sure that you're not
         *                              flooded by a huge stream of data values, e.g. in case you've
         *                              made some mistake in the time interval!
         * @param maxAutoReadMore       How many times do you allow the UAF to automatically invoke
         *                              a "continuation request" for you (if that's needed to fetch
         *                              all results)? E.g. if you specify maxAutoReadMore = 10,
         *                              then the UAF will automatically perform subsequent
         *                              history requests, until either all results are fetched, or
         *                              until 10 additional requests have been invoked
         *                              automatically.
         *                              This parameter will always be used instead of the
         *                              maxAutoReadMore attribute in the serviceSettings attribute
         *                              of the serviceConfig parameter!
         * @param continuationPoints    Continuation points, in case you're continuing to read the
         *                              historical data of a previous request manually. By
         *                              specifying a sufficiently large number for maxAutoReadMore,
         *                              you can actually let the UAF handle the "continuation
         *                              requests", if you want. If you're not using
         *                              continuationPoints manually, you can simply provide an
         *                              empty vector.
         * @param serviceConfig         HistoryReadRawModifiedConfig config.
         * @param sessionConfig         Session config.
         * @param result                Result of the request.
         * @return                      Client-side status.
         */
        uaf::Status historyReadRaw(
                const std::vector<uaf::Address>&            addresses,
                const uaf::DateTime&                        startTime,
                const uaf::DateTime&                        endTime,
                uint32_t                                    numValuesPerNode,
                uint32_t                                    maxAutoReadMore,
                const std::vector<uaf::ByteString>&         continuationPoints,
                const uafc::HistoryReadRawModifiedConfig&   serviceConfig,
                const uafc::SessionConfig&                  sessionConfig,
                uafc::HistoryReadRawModifiedResult&         result);


        /**
         * Read the modification information of the historical data from one or more nodes
         * synchronously.
         *
         * This is a convenience method, with few parameters. Use the
         * processRequest(HistoryReadRawModifiedRequest()) function to specify your history read
         * request much more in detail!
         *
         * Since this convenience method is meant to fetch the modification information of the
         * historical data, the isReadModified flag of the serviceSettings attribute of the
         * serviceConfig parameter will be forced to True!
         *
         * @param addresses             Addresses of the nodes to that provide the historical data.
         *                              continuationPoints manually, you can simply provide an
         *                              empty vector.
         * @param startTime             The start time of the interval from which you would like
         *                              to see the historical data.
         *                              This parameter will always be used instead of the
         *                              startTime attribute in the serviceSettings attribute
         *                              of the serviceConfig parameter!
         * @param endTime               The end time of the interval from which you would like
         *                              to see the historical data.
         *                              This parameter will always be used instead of the
         *                              endTime attribute in the serviceSettings attribute
         *                              of the serviceConfig parameter!
         * @param numValuesPerNode      The maximum number of values that may be returned for each
         *                              node. 0 means no limit, but you may want to put it to a
         *                              "safe" value (e.g. 100 if you expect to receive at most
         *                              50 historical values or so) to make sure that you're not
         *                              flooded by a huge stream of data values, e.g. in case you've
         *                              made some mistake in the time interval!
         * @param maxAutoReadMore       How many times do you allow the UAF to automatically invoke
         *                              a "continuation request" for you (if that's needed to fetch
         *                              all results)? E.g. if you specify maxAutoReadMore = 10,
         *                              then the UAF will automatically perform subsequent
         *                              history requests, until either all results are fetched, or
         *                              until 10 additional requests have been invoked
         *                              automatically.
         *                              This parameter will always be used instead of the
         *                              maxAutoReadMore attribute in the serviceSettings attribute
         *                              of the serviceConfig parameter!
         * @param continuationPoints    Continuation points, in case you're continuing to read the
         *                              historical data of a previous request manually. By
         *                              specifying a sufficiently large number for maxAutoReadMore,
         *                              you can actually let the UAF handle the "continuation
         *                              requests", if you want. If you're not using
         * @param serviceConfig         HistoryReadRawModifiedConfig config.
         * @param sessionConfig         Session config.
         * @param result                Result of the request.
         * @return                      Client-side status.
         */
        uaf::Status historyReadModified(
                const std::vector<uaf::Address>&            addresses,
                const uaf::DateTime&                        startTime,
                const uaf::DateTime&                        endTime,
                uint32_t                                    numValuesPerNode,
                uint32_t                                    maxAutoReadMore,
                const std::vector<uaf::ByteString>&         continuationPoints,
                const uafc::HistoryReadRawModifiedConfig&   serviceConfig,
                const uafc::SessionConfig&                  sessionConfig,
                uafc::HistoryReadRawModifiedResult&         result);


        /**
         * Continue a previous synchronous Browse request, in case you didn't use the automatic
         * BrowseNext feature of the UAF.
         *
         * You only need to use this function if you have put maxAutoBrowseNext to 0 in the previous
         * Browse request (or if the automatic BrowseNext calls still resulted in continuationPoints).
         * For your convenience, it's much easier to simply use the browse() method, and let the
         * UAF do the BrowseNext calls for you!
         *
         * This is a convenience method, with few parameters. Use the
         * processRequest(BrowseNextRequest()) function to specify your browse request much more in
         * detail!
         *
         * @param addresses             Addresses of the nodes that serve as the
         *                              starting point to browse. You need to copy the addresses to
         *                              here from the original Browse request, so that the UAF can
         *                              use these addresses to find out to which server the
         *                              BrowseNext call should be sent.
         * @param continuationPoints    The continuation points.
         * @param serviceConfig         BrowseNext config.
         * @param sessionConfig         Session config.
         * @param result                Result of the request.
         * @return                      Client-side status.
         */
        uaf::Status browseNext(
                const std::vector<uaf::Address>&    addresses,
                const std::vector<uaf::ByteString>& continuationPoints,
                const uafc::BrowseNextConfig&       serviceConfig,
                const uafc::SessionConfig&          sessionConfig,
                uafc::BrowseNextResult&             result);


        /**
         * Start to monitor data.
         *
         * @param addresses                 The addresses of the nodes of which the Value
         *                                  attribute should be monitored.
         * @param serviceConfig             Create monitored data config.
         * @param sessionConfig             Session config.
         * @param subscriptionConfig        Subscription config.
         * @param result                    Result of the request.
         * @return                          Client-side status.
         */
        uaf::Status createMonitoredData(
                const std::vector<uaf::Address>&        addresses,
                const uafc::CreateMonitoredDataConfig&  serviceConfig,
                const uafc::SessionConfig&              sessionConfig,
                const uafc::SubscriptionConfig&         subscriptionConfig,
                uafc::CreateMonitoredDataResult&        result);


        /**
         * Start to monitor events.
         *
         * @param addresses             The addresses of the nodes that should be monitored
         *                              for events.
         * @param eventFilter           The event filter common to all monitored items.
         * @param serviceConfig         Create monitored events config.
         * @param sessionConfig         Session config.
         * @param subscriptionConfig    Subscription settings.
         * @param result                Result of the request.
         * @return                      Client-side status.
         */
        uaf::Status createMonitoredEvents(
                const std::vector<uaf::Address>&            addresses,
                const uaf::EventFilter&                     eventFilter,
                const uafc::CreateMonitoredEventsConfig&    serviceConfig,
                const uafc::SessionConfig&                  sessionConfig,
                const uafc::SubscriptionConfig&             subscriptionConfig,
                uafc::CreateMonitoredEventsResult&          result);




        ///@} //////////////////////////////////////////////////////////////////////////////////////
        /**
         *  @name Generic
         *  Generic methods to process any service request.
         */
        ///@{

        /**
         * Process a synchronous read request.
         *
         * @param request   The request.
         * @param result    The result.
         * @return          The client-side status.
         */
        uaf::Status processRequest(
                const uafc::ReadRequest&    request,
                uafc::ReadResult&           result);

        /**
         * Process a synchronous read request.
         *
         * @param request   The request.
         * @param result    The result.
         * @return          The client-side status.
         */
        uaf::Status processRequest(
                const uafc::AsyncReadRequest&   request,
                uafc::AsyncReadResult&          result);

        /**
         * Process a synchronous write request.
         *
         * @param request   The request.
         * @param result    The result.
         * @return          The client-side status.
         */
        uaf::Status processRequest(
                const uafc::WriteRequest&   request,
                uafc::WriteResult&          result);

        /**
         * Process an asynchronous write request.
         *
         * @param request   The request.
         * @param result    The result.
         * @return          The client-side status.
         */
        uaf::Status processRequest(
                const uafc::AsyncWriteRequest&   request,
                uafc::AsyncWriteResult&          result);


        /**
         * Process a synchronous method call request.
         *
         * @param request   The request.
         * @param result    The result.
         * @return          The client-side status.
         */
        uaf::Status processRequest(
                const uafc::MethodCallRequest&  request,
                uafc::MethodCallResult&         result);


        /**
         * Process an asynchronous method call request.
         *
         * @param request   The request.
         * @param result    The result.
         * @return          The client-side status.
         */
        uaf::Status processRequest(
                const uafc::AsyncMethodCallRequest&  request,
                uafc::AsyncMethodCallResult&         result);

        /**
         * Process a synchronous browse request.
         *
         * @param request   The request.
         * @param result    The result.
         * @return          The client-side status.
         */
        uaf::Status processRequest(
                const uafc::BrowseRequest&   request,
                uafc::BrowseResult&          result);

        /**
         * Process a synchronous BrowseNext request.
         *
         * @param request   The request.
         * @param result    The result.
         * @return          The client-side status.
         */
        uaf::Status processRequest(
                const uafc::BrowseNextRequest&   request,
                uafc::BrowseNextResult&          result);

        /**
         * Process a synchronous "create monitored data" request.
         *
         * @param request   The request.
         * @param result    The result.
         * @return          The client-side status.
         */
        uaf::Status processRequest(
                const uafc::CreateMonitoredDataRequest& request,
                uafc::CreateMonitoredDataResult&        result);

        /**
         * Process a synchronous "create monitored events" request.
         *
         * @param request   The request.
         * @param result    The result.
         * @return          The client-side status.
         */
        uaf::Status processRequest(
                const uafc::CreateMonitoredEventsRequest&   request,
                uafc::CreateMonitoredEventsResult&          result);

        /**
         * Process a synchronous HistoryReadRawModified request.
         *
         * @param request   The request.
         * @param result    The result.
         * @return          The client-side status.
         */
        uaf::Status processRequest(
                const uafc::HistoryReadRawModifiedRequest&  request,
                uafc::HistoryReadRawModifiedResult&         result);



        ///@} //////////////////////////////////////////////////////////////////////////////////////
        /**
         *  @name ManualConnection
         *  Manually create and remove sessions.
         */
        ///@{


        /**
         * Create a session manually (instead of having the UAF do it behind the scenes).
         *
         * One of the advantages of the UAF is that you can just define some addresses (that point
         * to nodes), and then read/write/monitor/... them without worrying about the technical
         * concerns such as session creation, subscription creation etc. So you don't have to
         * create sessions yourself, because the UAF will do it for you.
         * However, if you want to "keep control" over the session/subscription/... management
         * yourself, you can use methods like "manuallyConnect", "manuallyDisconnect",
         * "manuallySubscribe", etc. In this case, you can create the sessions/subscriptions/...
         * in advance, and then afterwards read/write/... variables by using the same sessions
         * and subscriptions. So these "manual" methods allow you to use OPC UA in the "traditional
         * way", however it's much easier to do it the "UAF way" and simply forget about the
         * creation and deletion of sessions, subscriptions, and monitored items.
         *
         * @param serverUri     The server URI to which the client must connect. This server URI
         *                      (e.g. 'urn:UnifiedAutomation:UaDemoserver') must have been found
         *                      by the discovery process (which requires a Discovery URL that you
         *                      must provide via the uafc::Client::setClientSettings method).
         * @param settings      The session settings that you want your session to have.
         * @param clientConnectionId A return parameter, giving you the id of the session if it
         *                           was created.
         * @return              Good if the session was created, Bad if not.
         */
        uaf::Status manuallyConnect(
                const std::string&              serverUri,
                const uafc::SessionSettings&    settings,
                uafc::ClientConnectionId&       clientConnectionId);


        /**
         * Disconnect a session that was created manually.
         *
         *A session which has been disconnected manually is "garbage collected" on the client side.
         * When a session is created afterwards, a new ClientConnectionId will be assigned to this
         * session (even if the properties of the new session are exactly the same as the old one).
         *
         * Only use this for sessions that were created via the manuallyConnect method!
         *
         * @param clientConnectionId    The id of the session (that was given as an output parameter
         *                              of the manuallyConnect method.
         * @return                      Good if the session was successfully deleted, bad if not.
         */
        uaf::Status manuallyDisconnect(uafc::ClientConnectionId clientConnectionId);


        ///@} //////////////////////////////////////////////////////////////////////////////////////
        /**
         *  @name SessionInformation
         *  Get information about the available session(s).
         */
        ///@{


        /**
         * Get some information about a particular session.
         *
         * @param clientConnectionId    The id of the session.
         * @param sessionInformation    Output parameter, giving you the information (if the
         *                              returned Status was good!).
         * @return                      Good if the clientConnectionIf was pointing to a known
         *                              (connected or disconnected) Session, or Bad if it is
         *                              pointing to a session that is not available (anymore).
         */
        uaf::Status sessionInformation(
                 uafc::ClientConnectionId   clientConnectionId,
                 uafc::SessionInformation&  sessionInformation);


        /**
         * Get the information of all sessions currently created by the client.
         *
         * These sessions may be connected, or trying to be reconnected.
         *
         * @return  A vector of the information of all sessions.
         */
        std::vector<uafc::SessionInformation> allSessionInformations();


        ///@} //////////////////////////////////////////////////////////////////////////////////////
        /**
         *  @name ManualSubscription
         *  Manually create and remove subscriptions.
         */
        ///@{


        /**
         * Manually create a subscription.
         *
         * For more info about "manual" methods, see the documentation on the
         * uafc::Client::manuallyConnect method.
         *
         * @param clientConnectionId    The id of the session which should host the subscription.
         * @param settings              The settings of the subscription you'd like to create.
         * @param clientSubscriptionHandle  Output parameter, giving you the handle of the newly
         *                                  created subscription.
         * @return                      Good if the subscription was successfully created, Bad if
         *                              something went wrong.
         */
        uaf::Status manuallySubscribe(
                uafc::ClientConnectionId            clientConnectionId,
                const uafc::SubscriptionSettings&   settings,
                uafc::ClientSubscriptionHandle&     clientSubscriptionHandle);


        /**
         * Manually delete a subscription.
         *
         * A subscription which has been deleted manually is "garbage collected" on the client side.
         * When a subscription is created afterwards, a new clientSubscriptionHandle will be
         * assigned to this session (even if the properties of the new subscription are exactly the
         * same as the old one).
         *
         * @param clientConnectionId        The id of the session that hosts the subscription.
         * @param clientSubscriptionHandle  The handle of the subscription.
         * @return                          Good if the subscription could be deleted, bad if there
         *                                  was some problem.
         */
        uaf::Status manuallyUnsubscribe(
                uafc::ClientConnectionId        clientConnectionId,
                uafc::ClientSubscriptionHandle  clientSubscriptionHandle);


        ///@} //////////////////////////////////////////////////////////////////////////////////////
        /**
         *  @name SubscriptionInformation
         *  Get information about the available subscription(s).
         */
        ///@{


        /**
         * Get information about a particular subscription.
         *
         * @param clientSubscriptionHandle  The handle identifying the subscription.
         * @param subscriptionInformation   Output parameter, giving you the information about the
         *                                  subscription.
         * @return                          Good if the subscription could be found, Bad if not.
         */
        uaf::Status subscriptionInformation(
                 uafc::ClientSubscriptionHandle     clientSubscriptionHandle,
                 uafc::SubscriptionInformation&     subscriptionInformation);


        /**
         * Get information about all subscriptions.
         *
         * @return  A vector of all available SubscriptionInformation.
         */
        std::vector<uafc::SubscriptionInformation> allSubscriptionInformations();


    private:

        DISALLOW_COPY_AND_ASSIGN(Client);

        /** The logger of the client. */
        uaf::Logger* logger_;

        /** The session factory of the client. */
        uafc::SessionFactory* sessionFactory_;

        /** The resolver of the client (to resolve browse paths). */
        uafc::Resolver* resolver_;

        /** The discoverer (to find servers in the network). */
        uafc::Discoverer* discoverer_;

        /** The shared database of the client. */
        uafc::Database* database_;

        /** The flag to finish the run() method of the thread during destruction of the client. */
        bool doFinishThread_;

        /** The current request handle (only to be incremented when requestHandleMutex_ is locked). */
        uafc::RequestHandle currentRequestHandle_;

        /** The mutex to lock when the currentRequestHandle_ is read or manipulated. */
        UaMutex requestHandleMutex_;

        /**
         * Run method of the thread.
         */
        void run();


        /**
         * Common code of the constructors.
         */
        void construct();



#ifndef SWIG /* The private template functions below do not need to be seen by SWIG. */


        ///@} //////////////////////////////////////////////////////////////////////////////////////
        /**
         *  @name PrivateTemplates
         *  Private template functions to generically handle requests.
         */
        ///@{


        /**
         * Assign a Request handle to the given request and result.
         *
         * A request handle uniquely identifies each request (and corresponding result) processed by
         * the UAF client instance during its lifetime. The handle is represented by a 64-bit
         * integer which is incremented for each request. The 64-bit number is practically
         * unlimited (even at 1 million requests per second, the client will be able to assign
         * unique handles for more than 500000 years...).
         *
         * @tparam _Service The Service type, as defined in uaf/client/services/services.h.
         * @param request   The request to get a new UAF handle.
         * @param result    The result to get a new UAF handle.
         * @return          Good if a new handle was assigned, UnexpectedError if not.
         */
        template <typename _Service>
        uaf::Status assignRequestHandle(
                typename _Service::Request& request,
                typename _Service::Result&  result);
        // Private template functions can be implemented in the CPP file (keeps the header clean!)



        /**
         * Private templated member function to process requests that were already stored in a
         * Store.
         *
         * Persistent requests are requests such as CreateMonitoredDataRequests that we want to
         * reconstruct automatically after severe failures. E.g. when the NodeId of a monitored
         * item (that was created via a relative path) has changed after a restart of the server,
         * this monitored item will be reconstructed from the original request information (in this
         * case, the relative path, which may now point to another NodeId).
         *
         * @tparam _Store   The request store type of which the "bad" items will be reconstructed.
         * @param store     The request store instance of which the "bad" items will be
         *                  reconstructed.
         */
        template<typename _Store>
        void processPersistedRequests(_Store& store);
        // Private template functions can be implemented in the CPP file (keeps the header clean!)


        /**
         * Private templated member function to process a request.
         *
         * @tparam _Service The Service type, as defined in uaf/client/services/services.h.
         * @param request   The request to be processed.
         * @param result    The result to be updated.
         * @return          The client-side status.
         */
        template<typename _Service>
        uaf::Status processRequest(
                const typename _Service::Request&   request,
                typename _Service::Result&          result);
        // Private template functions can be implemented in the CPP file (keeps the header clean!)


        /**
         * Private templated member function to process a masked request.
         *
         * Masked-out targets (i.e. targets with mask.isUnset(rank)==True) will not be processed!
         *
         * @tparam _Service The Service type, as defined in uaf/client/services/services.h.
         * @param request   The request to be processed.
         * @param mask      The mask, specifying the targets that need to be processed.
         * @param result    The result to be updated.
         * @return          The client-side status.
         */
        template<typename _Service>
        uaf::Status processRequest(
                const typename _Service::Request&   request,
                const uaf::Mask&                    mask,
                typename _Service::Result&          result);
        // Private template functions can be implemented in the CPP file (keeps the header clean!)

#endif  /* SWIG (the section above is not visible by the SWIG preprocessor) */

        ///@}

    };

}

#endif /* UAFC_CLIENT_H */
