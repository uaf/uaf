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

#ifndef UAF_ENDPOINTDESCRIPTION_H_
#define UAF_ENDPOINTDESCRIPTION_H_


// STD
#include <string>
#include <stdint.h>
// SDK
#include "uaclient/uadiscovery.h"
// UAF
#include "uaf/util/util.h"
#include "uaf/util/applicationdescription.h"
#include "uaf/util/stringifiable.h"
#include "uaf/util/usertokenpolicy.h"
#include "uaf/util/securitypolicies.h"
#include "uaf/util/messagesecuritymodes.h"


namespace uaf
{

    /*******************************************************************************************//**
    * An EndpointDescription instance describes an endpoint of a Server (as returned during the
    * discovery process, so that the client can choose an endpoint and connect to it).
    *
    * @ingroup Util
    ***********************************************************************************************/
    class UAF_EXPORT EndpointDescription
    {
    public:


        /**
         * Create an empty application description.
         */
        EndpointDescription();


        /**
         * Create an application description based on the corresponding SDK variable.
         */
        EndpointDescription(const OpcUa_EndpointDescription& uaDesc);


        /**
         * Construct a new application description.
         *
         * @param endpointUrl           The endpoint URL.
         * @param server                The description of the server hosting this endpoint.
         * @param serverCertificate     The server certificate as a bytestring.
         * @param securityMode          The security mode of the endpoint.
         * @param securityPolicyUri     The URI of the security policy URI.
         * @param userIdentityTokens    The user identity tokens.
         * @param transportProfileUri   The URI of the transport profile.
         * @param securityLevel         The security level.
         */
        EndpointDescription(
                std::string                                     endpointUrl,
                uaf::ApplicationDescription                     server,
                std::pair<int32_t, uint8_t*>                    serverCertificate,
                uaf::messagesecuritymodes::MessageSecurityMode  securityMode,
                std::string                                     securityPolicyUri,
                std::vector<UserTokenPolicy>                    userIdentityTokens,
                std::string                                     transportProfileUri,
                uint8_t                                         securityLevel);


        /**
         * Is this a valid application description or an empty one?
         */
        bool isEmpty() const;


        /** The endpoint URL. */
        std::string endpointUrl;

        /** The server description. */
        uaf::ApplicationDescription server;

        /** The server certificate. */
        std::pair<int32_t, uint8_t*> serverCertificate;

        /** The message security mode (e.g. None or SignAndEncrypt). */
        uaf::messagesecuritymodes::MessageSecurityMode securityMode;

        /** The security policy URI (e.g. uaf::securitypolicies::UA_Basic128). */
        std::string securityPolicyUri;

        /** The allowed user identity token policies. */
        std::vector<UserTokenPolicy> userIdentityTokens;

        /** The transport profile URI. */
        std::string transportProfileUri;

        /** The security level. */
        uint8_t securityLevel;


        /**
         * Get a string representation of the EndpointDescription.
         *
         * @param indent Indent each line with this string.
         * @param colon  Put the colon (double point) at this position.
         * @return       A string representation (multiple lines, separated by newline-characters).
         */
        std::string toString(const std::string& indent="",  std::size_t colon=23) const;

    };

}



#endif /* UAF_ENDPOINTDESCRIPTION_H_ */
