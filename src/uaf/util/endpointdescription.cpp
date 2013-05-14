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

#include "uaf/util/endpointdescription.h"

namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;
    using std::vector;
    using std::size_t;
    using std::pair;
    using uaf::messagesecuritymodes::MessageSecurityMode;


    // Constructor
    // =============================================================================================
    EndpointDescription::EndpointDescription()
    {}


    // Constructor
    // =============================================================================================
    EndpointDescription::EndpointDescription(const OpcUa_EndpointDescription& uaDesc)
    : server(uaDesc.Server),
      serverCertificate(uaDesc.ServerCertificate.Length, uaDesc.ServerCertificate.Data),
      securityLevel(uaDesc.SecurityLevel),
      securityMode(uaf::messagesecuritymodes::fromSdkToUaf(uaDesc.SecurityMode))
    {
        if (!UaString(&uaDesc.EndpointUrl).isEmpty())
            endpointUrl = UaString(&uaDesc.EndpointUrl).toUtf8();
        if (!UaString(&uaDesc.SecurityPolicyUri).isEmpty())
            securityPolicyUri = UaString(&uaDesc.SecurityPolicyUri).toUtf8();
        if (!UaString(&uaDesc.TransportProfileUri).isEmpty())
            transportProfileUri = UaString(&uaDesc.TransportProfileUri).toUtf8();

        // set the user token policies
        for (int32_t i = 0; i < uaDesc.NoOfUserIdentityTokens; i++)
            userIdentityTokens.push_back(uaDesc.UserIdentityTokens[i]);
    }


    // Constructor
    // =============================================================================================
    EndpointDescription::EndpointDescription(
            std::string                                     endpointUrl,
            uaf::ApplicationDescription                     server,
            std::pair<int32_t, uint8_t*>                    serverCertificate,
            uaf::messagesecuritymodes::MessageSecurityMode  securityMode,
            std::string                                     securityPolicyUri,
            std::vector<uaf::UserTokenPolicy>               userIdentityTokens,
            std::string                                     transportProfileUri,
            uint8_t                                         securityLevel)
    : endpointUrl(endpointUrl),
      server(server),
      serverCertificate(serverCertificate),
      securityMode(securityMode),
      securityPolicyUri(securityPolicyUri),
      userIdentityTokens(userIdentityTokens),
      transportProfileUri(transportProfileUri),
      securityLevel(securityLevel)
    {}


    // Is the endpoint description empty?
    // =============================================================================================
    bool EndpointDescription::isEmpty() const
    {
        return endpointUrl.empty();
    }


    // Get a string representation
    // =============================================================================================
    string EndpointDescription::toString(const string& indent, size_t colon) const
    {
        stringstream ss;

        if (isEmpty())
        {
            ss << indent << "{}";
        }
        else
        {
            ss << indent << " - endpointUrl";
            ss << fillToPos(ss, colon);
            ss << ": " << endpointUrl << "\n";

            ss << indent << " - server\n";
            ss << server.toString(indent + "   ", colon);

            ss << indent << " - serverCertificate";
            ss << fillToPos(ss, colon);
            ss << ": " << serverCertificate.first << " bytes\n";

            ss << indent << " - securityMode";
            ss << fillToPos(ss, colon);
            ss << ": " << securityMode << " ("
                    << messagesecuritymodes::toString(securityMode) << ")\n";

            ss << indent << " - securityPolicyUri";
            ss << fillToPos(ss, colon);
            ss << ": " << securityPolicyUri << "\n";

            ss << indent        << " - userIdentityTokens[]";
            if (userIdentityTokens.size() == 0)
            {
                ss << fillToPos(ss, colon);
                ss << ": []\n";
            }
            else
            {
                ss << "\n";
                for (size_t i = 0; i<userIdentityTokens.size(); i++)
                {
                    ss << indent << "   " << " - userIdentityTokens[" << i << "]\n";
                    ss << userIdentityTokens[i].toString(indent + "      ", colon) << "\n";
                }
            }

            ss << indent << " - transportProfileUri";
            ss << fillToPos(ss, colon);
            ss << ": " << transportProfileUri << "\n";


            ss << indent << " - securityLevel";
            ss << fillToPos(ss, colon);
            ss << ": " << (int)securityLevel;
        }

        return ss.str();
    }








}
