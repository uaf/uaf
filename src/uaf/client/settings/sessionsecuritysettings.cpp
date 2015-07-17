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

#include "uaf/client/settings/sessionsecuritysettings.h"

namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;
    using std::vector;
    using std::size_t;


    // Constructor
    // =============================================================================================
    SessionSecuritySettings::SessionSecuritySettings()
    : securityPolicy(securitypolicies::UA_None),
      messageSecurityMode(messagesecuritymodes::Mode_None),
      userTokenType(usertokentypes::Anonymous)
    {}


    // Get a string representation
    // =============================================================================================
    string SessionSecuritySettings::toString(const string& indent, size_t colon) const
    {
        stringstream ss;

        ss << indent << " - securityPolicy";
        ss << fillToPos(ss, colon);
        ss << ": " << securityPolicy << "\n";

        ss << indent << " - messageSecurityMode";
        ss << fillToPos(ss, colon);
        ss << ": " << messageSecurityMode << " (" << messagesecuritymodes::toString(messageSecurityMode) << ")\n";

        ss << indent << " - userTokenType";
        ss << fillToPos(ss, colon);
        ss << ": " << userTokenType << " (" << usertokentypes::toString(userTokenType) << ")\n";

        ss << indent << " - userName";
        ss << fillToPos(ss, colon);
        ss << ": " << userName << "\n";

        ss << indent << " - userPassword";
        ss << fillToPos(ss, colon);
        ss << ": " << userPassword << "\n";

        ss << indent << " - userCertificateFileName";
        ss << fillToPos(ss, colon);
        ss << ": " << userCertificateFileName << "\n";

        ss << indent << " - userPrivateKeyFileName";
        ss << fillToPos(ss, colon);
        ss << ": " << userPrivateKeyFileName;

        return ss.str();
    }


    // operator<
    // =============================================================================================
    bool operator<(const SessionSecuritySettings& object1, const SessionSecuritySettings& object2)
    {
        if (object1.securityPolicy != object2.securityPolicy)
            return object1.securityPolicy < object2.securityPolicy;
        else if (object1.messageSecurityMode != object2.messageSecurityMode)
            return object1.messageSecurityMode < object2.messageSecurityMode;
        else if (object1.userTokenType != object2.userTokenType)
            return object1.userTokenType < object2.userTokenType;
        else if (object1.userName != object2.userName)
            return object1.userName < object2.userName;
        else if (object1.userPassword != object2.userPassword)
            return object1.userPassword < object2.userPassword;
        else if (object1.userCertificateFileName != object2.userCertificateFileName)
            return object1.userCertificateFileName < object2.userCertificateFileName;
        else
            return object1.userPrivateKeyFileName < object2.userPrivateKeyFileName;
    }


    // operator==
    // =============================================================================================
    bool operator==(const SessionSecuritySettings& object1, const SessionSecuritySettings& object2)
    {
        return (object1.securityPolicy == object2.securityPolicy)
                && (object1.messageSecurityMode == object2.messageSecurityMode)
                && (object1.userTokenType == object2.userTokenType)
                && (object1.userName == object2.userName)
                && (object1.userPassword == object2.userPassword)
                && (object1.userCertificateFileName == object2.userCertificateFileName)
                && (object1.userPrivateKeyFileName == object2.userPrivateKeyFileName);
    }


    // operator!=
    // =============================================================================================
    bool operator!=( const SessionSecuritySettings& object1, const SessionSecuritySettings& object2)
    {
        return !(object1 == object2);
    }



    // Match a SessionSecuritySettings with an EndpointDescription.
    // =============================================================================================
    Status match(
            const SessionSecuritySettings&    settings,
            const EndpointDescription&        endpoint)
    {
        vector<UserTokenPolicy> tokens = endpoint.userIdentityTokens;

        for (vector<UserTokenPolicy>::const_iterator it = tokens.begin(); it != tokens.end(); ++it)
        {
            if (   settings.userTokenType       == it->tokenType
                && settings.messageSecurityMode == endpoint.securityMode
                && settings.securityPolicy      == endpoint.securityPolicyUri)
            {
                return Status(statuscodes::Good);
            }
        }

        return SessionSecuritySettingsDontMatchEndpointError();
    }


    // Match multiple SessionSecuritySettings with multiple EndpointDescription.
    // =============================================================================================
    uaf::Status match(
            const SessionSecuritySettings&      settings,
            const vector<EndpointDescription>&  endpoints,
            EndpointDescription&                suitableEndpoint)
    {
        vector<EndpointDescription>::const_iterator endpointsIter;

        for (endpointsIter = endpoints.begin(); endpointsIter != endpoints.end(); ++endpointsIter)
        {
            if (match(settings, *endpointsIter).isGood())
            {
                suitableEndpoint = *endpointsIter;
                return statuscodes::Good;
            }
        }

        return SecuritySettingsMatchError();
    }

}
