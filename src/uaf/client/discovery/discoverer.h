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

#ifndef UAFC_DISCOVERER_H_
#define UAFC_DISCOVERER_H_


// STD
#include <vector>
#include <string>
#include <ctime>
// SDK
#include "uaclient/uaclientsdk.h"
#include "uaclient/uadiscovery.h"
// UAF
#include "uaf/util/logger.h"
#include "uaf/util/status.h"
#include "uaf/util/sdkstatus.h"
#include "uaf/util/applicationdescription.h"
#include "uaf/util/endpointdescription.h"
#include "uaf/client/clientexport.h"
#include "uaf/client/clientstatus.h"
#include "uaf/client/database/database.h"


namespace uafc
{


    /*******************************************************************************************//**
    * An uafc::Discoverer can discover OPC UA servers in the system.
    *
    * @ingroup ClientDiscovery
    ***********************************************************************************************/
    class UAFC_EXPORT Discoverer
    {
    public:


        /**
         * Construct a Discoverer instance by providing a pointer to a logger factory and a client
         * database.
         */
        Discoverer(uaf::LoggerFactory *loggerFactory, uafc::Database* database);


        /**
         * Destruct the discoverer.
         */
        virtual ~Discoverer();


        /**
         * Update the server descriptions by calling the OPC UA FindServers service
         * on all configured discovery servers.
         */
        uafc::ClientStatus findServers();


        /**
         * Get the discovery URLs for the given server URI.
         *
         * @param serverUri     The URI of the server of which you would like to get the
         *                      discoveryUrls from.
         * @param discoveryUrls Output parameter: the list of the discoveryUrls.
         * @return              Good if the server with the given serverUri was discovered, bad
         *                      if not.
         */
        uafc::ClientStatus getDiscoveryUrls(
                const std::string&          serverUri,
                std::vector<std::string>&   discoveryUrls);


        /**
         * Get the endpoint descriptions for a given server by calling the OPC UA
         * GetEndpoints service on the given URL.
         *
         * @param discoveryUrl          URL of the server to discover.
         * @param endpointDescriptions  Endpoint descriptions that will be fetched.
         * @return                      Status of the service call.
         */
        uafc::ClientStatus getEndpoints(
                const std::string&                      discoveryUrl,
                std::vector<uaf::EndpointDescription>&  endpointDescriptions);


        /**
         * Get a const reference to the servers that were found.
         *
         * @return  A vector of the application descriptions that were discovered.
         */
        const std::vector<uaf::ApplicationDescription>& serversFound() const;


    private:

        // no copying or assigning allowed
        DISALLOW_COPY_AND_ASSIGN(Discoverer);


        // the logger of the discoverer
        uaf::Logger* logger_;
        // a pointer to the shared database
        uafc::Database* database_;
        // are we busy with findServers()?
        bool findServersBusy_;
        // mutex to change the internal state
        UaMutex findServersBusyMutex_;
        // the latest application descriptions
        std::vector<uaf::ApplicationDescription> serverDescriptions_;
        // UaDiscovery instance
        UaClientSdk::UaDiscovery uaDiscovery_;
    };


}





#endif /* UAFC_DISCOVERER_H_ */
