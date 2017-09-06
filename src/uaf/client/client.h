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

#ifndef UAF_CLIENT_H
#define UAF_CLIENT_H


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
#include "uaf/util/callbackregistry.h"
#include "uaf/util/callbacks.h"
#include "uaf/client/clientexport.h"
#include "uaf/client/settings/clientsettings.h"
#include "uaf/client/database/database.h"
#include "uaf/client/resolution/resolver.h"
#include "uaf/client/sessions/sessionfactory.h"
#include "uaf/client/clientservices.h"



namespace uaf
{


    /*******************************************************************************************//**
    * A Client offers a clean API to easily invoke OPC UA services.
    *
    * @ingroup Client
    ***********************************************************************************************/
    class UAF_EXPORT Client : private UaThread,
                               public uaf::ClientInterface,
                               public uaf::LoggingInterface
    {
    public:


        /**
         * Create a client without a name.
         *
         * The name of the application (reflected in the logging and in
         * uaf::ClientSettings::clientApplicationName) will remain empty.
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
        Client(const uaf::ClientSettings& settings);


        /**
         * Create a client with a given settings and logger factory.
         *
         * @param settings  The Client settings.
         * @param loggerFactory Logger factory to which the client must log all its messages.
         */
        Client(const uaf::ClientSettings& settings, uaf::LoggerFactory* loggerFactory);


        /**
         * Destruct the client.
         */
        virtual ~Client();


        /**
         * Get a copy of the current client settings.
         *
         * @return The currently active client settings.
         */
        uaf::ClientSettings clientSettings() const;


        /**
         * Overwrite the current client settings.
         */
        void setClientSettings(const uaf::ClientSettings& settings);


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


        /**
         * Get the endpoint descriptions for a given server by calling the OPC UA
         * GetEndpoints service on the given URL.
         *
         * @param discoveryUrl          URL of the server to discover.
         * @param endpointDescriptions  Endpoint descriptions that will be fetched.
         * @return                      Status of the service call.
         */
        uaf::Status getEndpoints(
                const std::string&                      discoveryUrl,
                std::vector<uaf::EndpointDescription>&  endpointDescriptions);


        ///@} //////////////////////////////////////////////////////////////////////////////////////
        /**
         *  @name Convenience
         *  Convenience methods to read, write, create monitored items, ...
         */
        ///@{


        /**
         * Read a number of node attributes synchronously.
         *
         * The default session settings and read settings will be used.
         *
         * @param addresses         Addresses of the nodes of which the attributes should be read.
         * @param attributeId       The attribute to be read (e.g. Value or DisplayName).
         * @param result            Result of the request.
         * @return                  Client-side status.
         */
        uaf::Status read(
                const std::vector<uaf::Address>&                    addresses,
                uaf::attributeids::AttributeId                      attributeId,
                uaf::ClientConnectionId                             clientConnectionId,
                const uaf::ReadSettings*                            serviceSettings,
                const uaf::TranslateBrowsePathsToNodeIdsSettings*   translateSettings,
                const uaf::SessionSettings*                         sessionSettings,
                uaf::ReadResult&                                    result);



        /**
         * Read a number of node attributes asynchronously.
         *
         * Note that asynchronous requests MUST be invoked on a single session. Meaning:
         * if you provide multiple addresses to beginRead(), the addresses MUST point to nodes that
         * belong to the same server (as the UAF can currently not reconstruct an asynchronous
         * request that must be "split up" to be called on multiple servers).
         *
         * @param addresses       Addresses of the nodes of which the attributes should be read.
         * @param attributeId     The attribute to be read (e.g. Value or DisplayName).
         * @param serviceSettings Read settings.
         * @param sessionSettings Session settings.
         * @param result          Result of the request.
         * @return                Client-side status.
         */
        uaf::Status beginRead(
                const std::vector<uaf::Address>&                    addresses,
                const uaf::attributeids::AttributeId                attributeId,
                uaf::ClientConnectionId                             clientConnectionId,
                const uaf::ReadSettings*                            serviceSettings,
                const uaf::TranslateBrowsePathsToNodeIdsSettings*   translateSettings,
                const uaf::SessionSettings*                         sessionSettings,
                uaf::AsyncReadResult&                               result);


        /**
         * Write a number of node attributes synchronously.
         *
         * @param addresses         Addresses of the nodes of which the attribute should be written.
         * @param data              Data values that should be written (one data value per address).
         * @param attributeId       Attribute id that should be written for all nodes.
         * @param serviceSettings   Write settings.
         * @param sessionSettings   Session settings.
         * @param result            Result of the request.
         * @return                  Client-side status.
         */
        uaf::Status write(
                const std::vector<uaf::Address>&                    addresses,
                const std::vector<uaf::Variant>&                    data,
                const uaf::attributeids::AttributeId                attributeId,
                uaf::ClientConnectionId                             clientConnectionId,
                const uaf::WriteSettings*                           serviceSettings,
                const uaf::TranslateBrowsePathsToNodeIdsSettings*   translateSettings,
                const uaf::SessionSettings*                         sessionSettings,
                uaf::WriteResult&                                   result);


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
         * @param serviceSettings   Write settings.
         * @param sessionSettings   Session settings.
         * @param result            Result of the request.
         * @return                  Client-side status.
         */
        uaf::Status beginWrite(
                const std::vector<uaf::Address>&                    addresses,
                const std::vector<uaf::Variant>&                    data,
                const uaf::attributeids::AttributeId                attributeId,
                uaf::ClientConnectionId                             clientConnectionId,
                const uaf::WriteSettings*                           serviceSettings,
                const uaf::TranslateBrowsePathsToNodeIdsSettings*   translateSettings,
                const uaf::SessionSettings*                         sessionSettings,
                uaf::AsyncWriteResult&                              result);


        /**
         * Call a single method synchronously.
         *
         * To call multiple methods at once, use the generic processRequest method.
         *
         * @param objectAddress     Address of the parent node of the method.
         * @param methodAddress     Address of the method node.
         * @param inputArguments    Input arguments as a vector of variants.
         * @param serviceSettings   Method call settings.
         * @param sessionSettings   Session settings.
         * @param result            Result of thkme request.
         * @return                  Client-side status.
         */
        uaf::Status call(
                const uaf::Address&                                 objectAddress,
                const uaf::Address&                                 methodAddress,
                const std::vector<uaf::Variant>&                    inputArguments,
                uaf::ClientConnectionId                             clientConnectionId,
                const uaf::MethodCallSettings*                      serviceSettings,
                const uaf::TranslateBrowsePathsToNodeIdsSettings*   translateSettings,
                const uaf::SessionSettings*                         sessionSettings,
                uaf::MethodCallResult&                              result);


        /**
         * Call a single method asynchronously.
         *
         * You cannot call multiple methods at once asynchronously
         * (but you can do it synchronously!).
         *
         * @param objectAddress     Address of the parent node of the method.
         * @param methodAddress     Address of the method node.
         * @param inputArguments    Input arguments as a vector of variants.
         * @param serviceSettings   Method call settings.
         * @param sessionSettings   Session settings.
         * @param result            Result of the request.
         * @return                  Client-side status.
         */
        uaf::Status beginCall(
                const uaf::Address&                                 objectAddress,
                const uaf::Address&                                 methodAddress,
                const std::vector<uaf::Variant>&                    inputArguments,
                uaf::ClientConnectionId                             clientConnectionId,
                const uaf::MethodCallSettings*                      serviceSettings,
                const uaf::TranslateBrowsePathsToNodeIdsSettings*   translateSettings,
                const uaf::SessionSettings*                         sessionSettings,
                uaf::AsyncMethodCallResult&                         result);


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
         *                          the serviceSettings parameter!
         * @param serviceSettings   Browse settings.
         * @param sessionSettings   Session settings.
         * @param result            Result of the request.
         * @return                  Client-side status.
         */
        uaf::Status browse(
                const std::vector<uaf::Address>&                    addresses,
                uint32_t                                            maxAutoBrowseNext,
                uaf::ClientConnectionId                             clientConnectionId,
                const uaf::BrowseSettings*                          serviceSettings,
                const uaf::TranslateBrowsePathsToNodeIdsSettings*   translateSettings,
                const uaf::SessionSettings*                         sessionSettings,
                uaf::BrowseResult&                                  result);


        /**
         * Read the raw historical data from one or more nodes synchronously.
         *
         * This is a convenience method, with few parameters. Use the
         * processRequest(HistoryReadRawModifiedRequest()) function to specify your history read
         * request much more in detail!
         *
         * Since this convenience method is meant to fetch raw historical data, the isReadModified
         * flag of the serviceSettings attribute of the serviceSettings parameter
         * will be forced to False!
         *
         * @param addresses             Addresses of the nodes to that provide the historical data.
         * @param startTime             The start time of the interval from which you would like
         *                              to see the historical data.
         *                              This parameter will always be used instead of the
         *                              startTime attribute in the serviceSettings attribute
         *                              of the serviceSettings parameter!
         * @param endTime               The end time of the interval from which you would like
         *                              to see the historical data.
         *                              This parameter will always be used instead of the
         *                              endTime attribute in the serviceSettings attribute
         *                              of the serviceSettings parameter!
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
         *                              of the serviceSettings parameter!
         * @param continuationPoints    Continuation points, in case you're continuing to read the
         *                              historical data of a previous request manually. By
         *                              specifying a sufficiently large number for maxAutoReadMore,
         *                              you can actually let the UAF handle the "continuation
         *                              requests", if you want. If you're not using
         *                              continuationPoints manually, you can simply provide an
         *                              empty vector.
         * @param serviceSettings       HistoryReadRawModifiedSettings settings.
         * @param sessionSettings       Session settings.
         * @param result                Result of the request.
         * @return                      Client-side status.
         */
        uaf::Status historyReadRaw(
                const std::vector<uaf::Address>&                    addresses,
                const uaf::DateTime&                                startTime,
                const uaf::DateTime&                                endTime,
                uint32_t                                            numValuesPerNode,
                uint32_t                                            maxAutoReadMore,
                const std::vector<uaf::ByteString>&                 continuationPoints,
                uaf::ClientConnectionId                             clientConnectionId,
                const uaf::HistoryReadRawModifiedSettings*          serviceSettings,
                const uaf::TranslateBrowsePathsToNodeIdsSettings*   translateSettings,
                const uaf::SessionSettings*                         sessionSettings,
                uaf::HistoryReadRawModifiedResult&                  result);


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
         * serviceSettings parameter will be forced to True!
         *
         * @param addresses             Addresses of the nodes to that provide the historical data.
         *                              continuationPoints manually, you can simply provide an
         *                              empty vector.
         * @param startTime             The start time of the interval from which you would like
         *                              to see the historical data.
         *                              This parameter will always be used instead of the
         *                              startTime attribute in the serviceSettings attribute
         *                              of the serviceSettings parameter!
         * @param endTime               The end time of the interval from which you would like
         *                              to see the historical data.
         *                              This parameter will always be used instead of the
         *                              endTime attribute in the serviceSettings attribute
         *                              of the serviceSettings parameter!
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
         *                              of the serviceSettings parameter!
         * @param continuationPoints    Continuation points, in case you're continuing to read the
         *                              historical data of a previous request manually. By
         *                              specifying a sufficiently large number for maxAutoReadMore,
         *                              you can actually let the UAF handle the "continuation
         *                              requests", if you want. If you're not using
         * @param serviceSettings         HistoryReadRawModifiedSettings settings.
         * @param sessionSettings         Session settings.
         * @param result                Result of the request.
         * @return                      Client-side status.
         */
        uaf::Status historyReadModified(
                const std::vector<uaf::Address>&                    addresses,
                const uaf::DateTime&                                startTime,
                const uaf::DateTime&                                endTime,
                uint32_t                                            numValuesPerNode,
                uint32_t                                            maxAutoReadMore,
                const std::vector<uaf::ByteString>&                 continuationPoints,
                uaf::ClientConnectionId                             clientConnectionId,
                const uaf::HistoryReadRawModifiedSettings*          serviceSettings,
                const uaf::TranslateBrowsePathsToNodeIdsSettings*   translateSettings,
                const uaf::SessionSettings*                         sessionSettings,
                uaf::HistoryReadRawModifiedResult&                  result);


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
         * @param serviceSettings       BrowseNext settings.
         * @param sessionSettings       Session settings.
         * @param result                Result of the request.
         * @return                      Client-side status.
         */
        uaf::Status browseNext(
                const std::vector<uaf::Address>&                    addresses,
                const std::vector<uaf::ByteString>&                 continuationPoints,
                uaf::ClientConnectionId                             clientConnectionId,
                const uaf::BrowseNextSettings*                      serviceSettings,
                const uaf::TranslateBrowsePathsToNodeIdsSettings*   translateSettings,
                const uaf::SessionSettings*                         sessionSettings,
                uaf::BrowseNextResult&                              result);


        /**
         * Start to monitor data.
         *
         * Note that even when communication failed (e.g. because the server was not online),
         * a handle is already assigned to each monitored item when you call processRequest().
         * In the background, the UAF will try to (re)establish the connection, and as soon as
         * this is successful, it will create the monitored items for you on the server.
         * From that point on, you may start to receive notifications (that can be identified by
         * the handles that were already assigned and returned to you now).
         * You can access these assigned handles by looking at the 'result' parameter, or by looking
         * at the diagnostics object of the returned Status object.
         *
         * @param addresses                 The addresses of the nodes of which the Value
         *                                  attribute should be monitored.
         * @param serviceSettings           Create monitored data settings.
         * @param sessionSettings           Session settings.
         * @param subscriptionSettings      Subscription settings.
         * @param result                    Result of the request.
         * @return                          Client-side status.
         */
        uaf::Status createMonitoredData(
                const std::vector<uaf::Address>&                    addresses,
                uaf::ClientConnectionId                             clientConnectionId,
                const uaf::CreateMonitoredDataSettings*             serviceSettings,
                const uaf::TranslateBrowsePathsToNodeIdsSettings*   translateSettings,
                const uaf::SessionSettings*                         sessionSettings,
                uaf::ClientSubscriptionHandle                       clientSubscriptionHandle,
                const uaf::SubscriptionSettings*                    subscriptionSettings,
                uaf::CreateMonitoredDataResult&                     result);


        /**
         * Start to monitor events.
         *
         * Note that even when communication failed (e.g. because the server was not online),
         * a handle is already assigned to each monitored item when you call processRequest().
         * In the background, the UAF will try to (re)establish the connection, and as soon as
         * this is successful, it will create the monitored items for you on the server.
         * From that point on, you may start to receive notifications (that can be identified by
         * the handles that were already assigned and returned to you now).
         * You can access these assigned handles by looking at the 'result' parameter, or by looking
         * at the diagnostics object of the returned Status object.
         *
         * @param addresses             The addresses of the nodes that should be monitored
         *                              for events.
         * @param eventFilter           The event filter common to all monitored items.
         * @param serviceSettings       Create monitored events settings.
         * @param sessionSettings       Session settings.
         * @param subscriptionSettings  Subscription settings.
         * @param result                Result of the request.
         * @return                      Client-side status.
         */
        uaf::Status createMonitoredEvents(
                const std::vector<uaf::Address>&                    addresses,
                const uaf::EventFilter&                             eventFilter,
                uaf::ClientConnectionId                             clientConnectionId,
                const uaf::CreateMonitoredEventsSettings*           serviceSettings,
                const uaf::TranslateBrowsePathsToNodeIdsSettings*   translateSettings,
                const uaf::SessionSettings*                         sessionSettings,
                uaf::ClientSubscriptionHandle                       clientSubscriptionHandle,
                const uaf::SubscriptionSettings*                    subscriptionSettings,
                uaf::CreateMonitoredEventsResult&                   result);




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
                const uaf::ReadRequest&    request,
                uaf::ReadResult&           result);

        /**
         * Process a synchronous read request.
         *
         * @param request   The request.
         * @param result    The result.
         * @return          The client-side status.
         */
        uaf::Status processRequest(
                const uaf::AsyncReadRequest&   request,
                uaf::AsyncReadResult&          result);

        /**
         * Process a synchronous write request.
         *
         * @param request   The request.
         * @param result    The result.
         * @return          The client-side status.
         */
        uaf::Status processRequest(
                const uaf::WriteRequest&   request,
                uaf::WriteResult&          result);

        /**
         * Process an asynchronous write request.
         *
         * @param request   The request.
         * @param result    The result.
         * @return          The client-side status.
         */
        uaf::Status processRequest(
                const uaf::AsyncWriteRequest&   request,
                uaf::AsyncWriteResult&          result);


        /**
         * Process a synchronous method call request.
         *
         * @param request   The request.
         * @param result    The result.
         * @return          The client-side status.
         */
        uaf::Status processRequest(
                const uaf::MethodCallRequest&  request,
                uaf::MethodCallResult&         result);


        /**
         * Process an asynchronous method call request.
         *
         * @param request   The request.
         * @param result    The result.
         * @return          The client-side status.
         */
        uaf::Status processRequest(
                const uaf::AsyncMethodCallRequest&  request,
                uaf::AsyncMethodCallResult&         result);

        /**
         * Process a synchronous browse request.
         *
         * @param request   The request.
         * @param result    The result.
         * @return          The client-side status.
         */
        uaf::Status processRequest(
                const uaf::BrowseRequest&   request,
                uaf::BrowseResult&          result);

        /**
         * Process a synchronous BrowseNext request.
         *
         * @param request   The request.
         * @param result    The result.
         * @return          The client-side status.
         */
        uaf::Status processRequest(
                const uaf::BrowseNextRequest&   request,
                uaf::BrowseNextResult&          result);


        /**
         * Process a synchronous TranslateBrowsePathsToNodeIdsRequest.
         *
         * @param request   The request.
         * @param result    The result.
         * @return          The client-side status.
         */
        uaf::Status processRequest(
                const uaf::TranslateBrowsePathsToNodeIdsRequest&  request,
                uaf::TranslateBrowsePathsToNodeIdsResult&         result);

        
        /**
         * Process a synchronous "create monitored data" request.
         *
         * Note that even when communication failed (e.g. because the server was not online),
         * a handle is already assigned to each monitored item when you call processRequest().
         * In the background, the UAF will try to (re)establish the connection, and as soon as
         * this is successful, it will create the monitored items for you on the server.
         * From that point on, you may start to receive notifications (that can be identified by
         * the handles that were already assigned and returned to you now).
         * You can access these assigned handles by looking at the 'result' parameter, or by looking
         * at the diagnostics object of the returned Status object.
         *
         * @param request   The request.
         * @param result    The result.
         * @return          The client-side status.
         */
        uaf::Status processRequest(
                const uaf::CreateMonitoredDataRequest& request,
                uaf::CreateMonitoredDataResult&        result);

        /**
         * Process a synchronous "create monitored events" request.
         *
         * Note that even when communication failed (e.g. because the server was not online),
         * a handle is already assigned to each monitored item when you call processRequest().
         * In the background, the UAF will try to (re)establish the connection, and as soon as
         * this is successful, it will create the monitored items for you on the server.
         * From that point on, you may start to receive notifications (that can be identified by
         * the handles that were already assigned and returned to you now).
         * You can access these assigned handles by looking at the 'result' parameter, or by looking
         * at the diagnostics object of the returned Status object.
         *
         * @param request   The request.
         * @param result    The result.
         * @return          The client-side status.
         */
        uaf::Status processRequest(
                const uaf::CreateMonitoredEventsRequest&   request,
                uaf::CreateMonitoredEventsResult&          result);

        /**
         * Process a synchronous HistoryReadRawModified request.
         *
         * @param request   The request.
         * @param result    The result.
         * @return          The client-side status.
         */
        uaf::Status processRequest(
                const uaf::HistoryReadRawModifiedRequest&  request,
                uaf::HistoryReadRawModifiedResult&         result);



        ///@} //////////////////////////////////////////////////////////////////////////////////////
        /**
         *  @name Definitions
         *  Generic methods to get datatype definitions
         */
        ///@{


        /**
         * Get the definition of a structured datatype.
         *
         *
         * @param dataTypeId	The NodeId of the structured datatype.
         * @param definition    Output parameter, the definition (if found).
         * @return				DefinitionNotFoundError if no definition was found,
         * 						Good otherwise.
         */
        uaf::Status structureDefinition(
        		const uaf::NodeId &dataTypeId,
        		uaf::StructureDefinition& definition);


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
         *                      must provide via the uaf::Client::setClientSettings method).
         * @param settings      The session settings that you want your session to have.
         *                      Assign to NULL to use the specificSessionSettings/defaultSessionSettings
         *                      as configured by the ClientSettings.
         * @param clientConnectionId A return parameter, giving you the id of the session if it
         *                           was created.
         * @return              Good if the session was created, Bad if not.
         */
        uaf::Status manuallyConnect(
                const std::string&              serverUri,
                const uaf::SessionSettings*     settings,
                uaf::ClientConnectionId&        clientConnectionId);


        /**
         * Manually connect to a specific endpoint *without* any discovery involved.
         *
         * You should probably only use this method if you have a good reason not to rely on
         * the discovery services provided by the server. A server should be identified with
         * a serverURI, not with an endpointURL!
         *
         * The settings.securitySettingsList defines how you want to connect to the server.
         * settings.securitySettingsList[0] will be attempted first,
         * if that fails then settings.securitySettingsList[1] will be attempted, and so on.
         *
         * By default, a SessionSettings instance has one item in its securitySettingsList:
         * no authentication (anonymous) and no security (None).
         *
         * If this method fails (in other words, when the returned Status is bad), then no
         * Session will be created! This is different behavior from manuallyConnect, which will
         * retry to connect until there's no failure anymore.
         *
         * Compliant to OPC UA specs, the serverCertificate will:
         * - first be checked at the application level. If it's not valid or not found in the trust
         *   list, then the untrustedServerCertificateReceived() callback function will be called.
         *   Override this method if you want to handle those cases.
         * - then it may be used for encryption and/or signing (if a secure connection is needed,
         *   of course).
         *
         * You can provide an (invalid, null) default PkiCertificate instance for the
         * serverCertificate if you trust the server (i.e. if you make sure
         * untrustedServerCertificateReceived returns PkiCertificate::Action_AcceptTemporarily),
         * and if you don't need signing or encryption.
         *
         * @param endpointUrl   The endpoint URL to which you want to connect
         *                      (e.g. opc.tcp://localhost:48010)
         * @param settings      The session settings that you want your session to have.
         *                      Assign to NULL to use the defaultSessionSettings
         *                      as configured by the ClientSettings.
         * @param serverCertificate The server certificate (assign to NULL for a null certificate).
         * @param clientConnectionId A return parameter, giving you the id of the session if it
         *                           was created.
         * @return              Good if the session was created, Bad if not.
         */
        uaf::Status manuallyConnectToEndpoint(
                const std::string&              endpointUrl,
                const uaf::SessionSettings*     settings,
                const uaf::PkiCertificate*      serverCertificate,
                uaf::ClientConnectionId&        clientConnectionId);


        /**
         * Disconnect a session that was created manually.
         *
         * A session which has been disconnected manually is "garbage collected" on the client side.
         * When a session is created afterwards, a new ClientConnectionId will be assigned to this
         * session (even if the properties of the new session are exactly the same as the old one).
         *
         * Only use this for sessions that were created via the manuallyConnect method!
         *
         * @param clientConnectionId    The id of the session (that was given as an output parameter
         *                              of the manuallyConnect method.
         * @return                      Good if the session was successfully deleted, bad if not.
         */
        uaf::Status manuallyDisconnect(uaf::ClientConnectionId clientConnectionId);


        /**
         * Disconnect all sessions.
         *
         * To stress that normally the UAF takes care of session connection and disconnection,
         * this method has a "manually" prefix. Normally it should not be used explicitely,
         * as all sessions will be disconnected automatically when the client is deleted.
         */
        void manuallyDisconnectAllSessions();


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
                 uaf::ClientConnectionId   clientConnectionId,
                 uaf::SessionInformation&  sessionInformation);


        /**
         * Get the information of all sessions currently created by the client.
         *
         * These sessions may be connected, or trying to be reconnected.
         *
         * @return  A vector of the information of all sessions.
         */
        std::vector<uaf::SessionInformation> allSessionInformations();


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
         * uaf::Client::manuallyConnect method.
         *
         * @param clientConnectionId    The id of the session which should host the subscription.
         * @param settings              The settings of the subscription you'd like to create.
         * @param clientSubscriptionHandle  Output parameter, giving you the handle of the newly
         *                                  created subscription.
         *                                  Assign to NULL to use the defaultSubscriptionSettings
         *                                  as configured by the ClientSettings.
         * @return                      Good if the subscription was successfully created, Bad if
         *                              something went wrong.
         */
        uaf::Status manuallySubscribe(
                uaf::ClientConnectionId             clientConnectionId,
                const uaf::SubscriptionSettings*    settings,
                uaf::ClientSubscriptionHandle&      clientSubscriptionHandle);


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
                uaf::ClientConnectionId        clientConnectionId,
                uaf::ClientSubscriptionHandle  clientSubscriptionHandle);


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
                 uaf::ClientSubscriptionHandle      clientSubscriptionHandle,
                 uaf::SubscriptionInformation&     subscriptionInformation);


        /**
         * Get information about all subscriptions.
         *
         * @return  A vector of all available SubscriptionInformation.
         */
        std::vector<uaf::SubscriptionInformation> allSubscriptionInformations();


        ///@} //////////////////////////////////////////////////////////////////////////////////////
        /**
         *  @name SubscriptionInformation
         *  Get information about the available subscription(s).
         */
        ///@{


        /**
         * Get information about a particular subscription.
         *
         * @param clientHandle              The handle identifying the monitored item.
         * @param monitoredItemInformation  Output parameter, giving you the information about the
         *                                  monitored item.
         * @return                          Good if the monitored item could be found, Bad if not.
         */
        uaf::Status monitoredItemInformation(
                 uaf::ClientHandle                  clientHandle,
                 uaf::MonitoredItemInformation&    monitoredItemInformation);


        ///@} //////////////////////////////////////////////////////////////////////////////////////
        /**
         *  @name ChangeSubscriptions
         *  Change properties of the subscription(s).
         */
        ///@{


        /**
         * Set the publishing mode, by specifying a subscription handle.
         *
         * Note that a subscription handle may *not* be known at the time when you create the
         * monitored items. E.g. when you call createMonitoredData() or createMonitoredEvents(),
         * it can happen that the server that hosts the monitored items is not on-line yet.
         * In this case, the ClientSubscriptionHandle is *not* assigned yet, but
         * ClientHandles *are* assigned yet. Therefore it makes sense to first call
         * uaf::Client::monitoredItemInformation() of your monitored item, and get the subscription
         * handle from there.
         *
         * @param clientSubscriptionHandle  The handle identifying the subscription.
         * @param publishingEnabled         True to enable the publishing mode, false to disable.
         * @param serviceSettings           The service settings to be used.
         *                                  Assign to NULL to use the defaultSetPublishingModeSettings
         *                                  as configurable by the ClientSettings.
         * @return                          The result of the service call.
         */
        uaf::Status setPublishingMode(
                 uaf::ClientSubscriptionHandle  clientSubscriptionHandle,
                 bool                           publishingEnabled,
                 const uaf::ServiceSettings*    serviceSettings);


        /**
         * Set the monitoring mode for the specified monitored items.
         *
         * @param clientHandles     The ClientHandles of the monitored items to be affected.
         * @param monitoringMode    The new monitoring mode.
         * @param serviceSettings   The service settings to be used.
         *                          ssign to NULL to use the defaultSetMonitoringModeSettings
         *                          as configurable by the ClientSettings.
         * @param results           A vector of statuses (one result for each ClientHandle).
         * @return                  The immediate result of the service call.
         */
        uaf::Status setMonitoringMode(
                std::vector<uaf::ClientHandle>          clientHandles,
                uaf::monitoringmodes::MonitoringMode    monitoringMode,
                const uaf::ServiceSettings*             serviceSettings,
                std::vector<uaf::Status>&               results);


        ///@} //////////////////////////////////////////////////////////////////////////////////////
        /**
         *  @name Callbacks
         *  Manage callbacks for monitored items.
         */
        ///@{


        /**
        * Register a callback for a monitored data item.
        *
        * @param clientHandle      The ClientHandle of the monitored item.
        * @param callback          A callback function.
        */
        void registerDataChangeCallback(
               uaf::ClientHandle                       clientHandle,
               uaf::Callback<uaf::DataChangeNotification> callback);


        /**
        * Register a callback for all monitored data items.
        *
        * @param callback          A callback function.
        */
        void registerDataChangeCallback(
               uaf::Callback<uaf::DataChangeNotification> callback);


        /**
        * Register a callback for a monitored event.
        *
        * @param clientHandle      The ClientHandle of the monitored item.
        * @param callback          A callback function.
        */
        void registerEventCallback(
               uaf::ClientHandle                       clientHandle,
               uaf::Callback<uaf::EventNotification> callback);


        /**
        * Register a callback for all monitored events.
        *
        * @param callback          A callback function.
        */
        void registerEventCallback(
               uaf::Callback<uaf::EventNotification> callback);


        /**
        * Unregister all callbacks for a monitored data item.
        *
        * @param clientHandle      The ClientHandle of the monitored item.
        */
        void unregisterDataChangeCallbacks(
               uaf::ClientHandle                       clientHandle);


        /**
        * Unregister all callbacks that are registered for all monitored data items.
        *
        */
        void unregisterDataChangeCallbacks();


        /**
        * Unregister all callbacks for monitored data items.
        *
        */
        void unregisterAllDataChangeCallbacks();


        /**
        * Unregister a callback for a monitored event.
        *
        * @param clientHandle      The ClientHandle of the monitored item.
        * @param callback          A callback function.
        */
        void unregisterEventCallbacks(
               uaf::ClientHandle                       clientHandle);


        /**
        * Unregister all callbacks that are registered for all events.
        *
        */
        void unregisterEventCallbacks();


        /**
        * Unregister all callbacks for events.
        *
        */
        void unregisterAllEventCallbacks();

        ///@} //////////////////////////////////////////////////////////////////////////////////////
        ///@{

    private:

        DISALLOW_COPY_AND_ASSIGN(Client);

        /** The logger of the client. */
        uaf::Logger* logger_;

        /** The session factory of the client. */
        uaf::SessionFactory* sessionFactory_;

        /** The resolver of the client (to resolve browse paths). */
        uaf::Resolver* resolver_;

        /** The discoverer (to find servers in the network). */
        uaf::Discoverer* discoverer_;

        /** The shared database of the client. */
        uaf::Database* database_;

        /** The flag to finish the run() method of the thread during destruction of the client. */
        bool doFinishThread_;

        /** The current request handle (only to be incremented when requestHandleMutex_ is locked). */
        uaf::RequestHandle currentRequestHandle_;

        /** The mutex to lock when the currentRequestHandle_ is read or manipulated. */
        UaMutex requestHandleMutex_;

        /** The callback registry for events. */
        uaf::CallbackRegistry<EventNotification> eventCallbackRegistry_;

        /** The callback registry for monitored data. */
        uaf::CallbackRegistry<DataChangeNotification> dataCallbackRegistry_;

        /**
         * Run method of the thread.
         */
        void run();


        /**
         * Common code of the constructors.
         */
        void construct();


        /**
         * Handle data changes.
         *
         * @param notifications Received data change notifications.
         */
        virtual void dataChangesReceived(std::vector<uaf::DataChangeNotification> notifications);

        /**
         * Handle events.
         *
         * @param notifications Received event notifications.
         */
        virtual void eventsReceived(std::vector<uaf::EventNotification> notifications);



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

#endif /* UAF_CLIENT_H */
