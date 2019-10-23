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

#ifndef UAF_APPLICATIONDESCRIPTION_H_
#define UAF_APPLICATIONDESCRIPTION_H_


// STD
#include <string>
#include <sstream>
#include <vector>
#include <stdint.h>
// SDK
#include "uaclientcpp/uadiscovery.h"
// UAF
#include "uaf/util/util.h"
#include "uaf/util/localizedtext.h"
#include "uaf/util/stringifiable.h"
#include "uaf/util/applicationtypes.h"


namespace uaf
{

    /*******************************************************************************************//**
    * An ApplicationDescription instance describes a Server or Client or ClientAndServer, or a
    * DiscoveryServer.
    *
    * @ingroup Util
    ***********************************************************************************************/
    class UAF_EXPORT ApplicationDescription
    {
    public:


        /**
         * Create an empty application description.
         */
        ApplicationDescription();


        /**
         * Create an application description based on the corresponding SDK variable.
         */
        ApplicationDescription(const OpcUa_ApplicationDescription& desc);


        /**
         * Construct a new application description.
         *
         * @param applicationUri        The URI of the server.
         * @param productUri            Unique identifier for the product.
         * @param applicationName       Name of the server (or application in the general case).
         * @param applicationType       Either Server, Client, ServerAndClient, or DiscoveryServer.
         * @param gatewayServerUri      Server URI of the gateway in case a gateway is needed to
         *                              connect to the server.
         * @param discoveryProfileUri   An alternative discovery profile such as UDDI or LDAP.
         * @param discoveryUrls         A list of URLs of which we can request the endpoints from.
         */
        ApplicationDescription(
                std::string                             applicationUri,
                std::string                             productUri,
                uaf::LocalizedText                      applicationName,
                uaf::applicationtypes::ApplicationType  applicationType,
                std::string                             gatewayServerUri,
                std::string                             discoveryProfileUri,
                std::vector<std::string>                discoveryUrls);


        /** The application URI. */
        std::string                             applicationUri;
        /** The product URI. */
        std::string                             productUri;
        /** The application name. */
        uaf::LocalizedText                      applicationName;
        /** The application type. */
        uaf::applicationtypes::ApplicationType  applicationType;
        /** The server URI. */
        std::string                             gatewayServerUri;
        /** The profile URI. */
        std::string                             discoveryProfileUri;
        /** The discovery URLs. */
        std::vector<std::string>                discoveryUrls;


        /**
         * Is this a valid application description or an empty one?
         */
        bool isEmpty() const;


        /**
         * Get a string representation of the ApplicationDescription.
         *
         * @param indent Indentation to add to each line (e.g. "  " to indent with 2 spaces).
         * @param colon  The position to put the colon (double point).
         * @return       A string representation (multiple lines, separated by newline-characters).
         */
        std::string toString(const std::string& indent="", std::size_t colon=11) const;


        // comparison operators
        friend UAF_EXPORT bool operator==(
                const ApplicationDescription& object1,
                const ApplicationDescription& object2);
        friend UAF_EXPORT bool operator!=(
                const ApplicationDescription& object1,
                const ApplicationDescription& object2);
        friend UAF_EXPORT bool operator<(
                const ApplicationDescription& object1,
                const ApplicationDescription& object2);


    };


}



#endif /* UAF_APPLICATIONDESCRIPTION_H_ */
