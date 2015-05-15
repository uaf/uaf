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
    : securityMode(messagesecuritymodes::Mode_None),
      securityLevel(0)
    {}


    // Constructor
    // =============================================================================================
    EndpointDescription::EndpointDescription(const OpcUa_EndpointDescription& uaDesc)
    : server(uaDesc.Server),
      serverCertificate(uaDesc.ServerCertificate.Length, uaDesc.ServerCertificate.Data),
      securityMode(uaf::messagesecuritymodes::fromSdkToUaf(uaDesc.SecurityMode)),
      securityLevel(uaDesc.SecurityLevel)
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
            uaf::ByteString                                 serverCertificate,
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
            ss << server.toString(indent + "   ", colon) << "\n";

            ss << indent << " - serverCertificate";
            ss << fillToPos(ss, colon);
            ss << ": " << serverCertificate.toString() << "\n";

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


    // operator==
    // =============================================================================================
    bool operator==( const EndpointDescription& object1, const EndpointDescription& object2)
    {
        return    (object1.endpointUrl == object2.endpointUrl)
               && (object1.server == object2.server)
               && (object1.serverCertificate == object2.serverCertificate)
               && (object1.securityMode == object2.securityMode)
               && (object1.securityPolicyUri == object2.securityPolicyUri)
               && (object1.userIdentityTokens == object2.userIdentityTokens)
               && (object1.transportProfileUri == object2.transportProfileUri)
               && (object1.securityLevel == object2.securityLevel);
    }


    // operator!=
    // =============================================================================================
    bool operator!=(const EndpointDescription& object1, const EndpointDescription& object2)
    {
        return !(object1 == object2);
    }


    // operator<
    // =============================================================================================
    bool operator<(const EndpointDescription& object1, const EndpointDescription& object2)
    {
        if (object1.endpointUrl != object2.endpointUrl)
            return object1.endpointUrl < object2.endpointUrl;
        else if (object1.server != object2.server)
            return object1.server < object2.server;
        else if (object1.serverCertificate != object2.serverCertificate)
            return object1.serverCertificate < object2.serverCertificate;
        else if (object1.securityMode != object2.securityMode)
            return object1.securityMode < object2.securityMode;
        else if (object1.securityPolicyUri != object2.securityPolicyUri)
            return object1.securityPolicyUri < object2.securityPolicyUri;
        else if (object1.userIdentityTokens != object2.userIdentityTokens)
            return object1.userIdentityTokens < object2.userIdentityTokens;
        else if (object1.transportProfileUri != object2.transportProfileUri)
            return object1.transportProfileUri < object2.transportProfileUri;
        else
            return object1.securityLevel < object2.securityLevel;
    }








}
