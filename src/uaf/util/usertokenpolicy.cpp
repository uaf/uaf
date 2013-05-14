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

#include "uaf/util/usertokenpolicy.h"

namespace uaf
{
    using namespace uaf;
    using namespace uaf::usertokentypes;
    using std::string;
    using std::stringstream;
    using std::vector;
    using std::size_t;


    // Constructor
    // =============================================================================================
    UserTokenPolicy::UserTokenPolicy()
    : tokenType(Anonymous)
    {}


    // Constructor
    // =============================================================================================
    UserTokenPolicy::UserTokenPolicy(const OpcUa_UserTokenPolicy& uaPolicy)
    : policyId(),
      tokenType(usertokentypes::fromSdkToUaf(uaPolicy.TokenType))
    {
        if (!UaString(&uaPolicy.PolicyId).isEmpty())
            policyId = UaString(&uaPolicy.PolicyId).toUtf8();
        if (!UaString(&uaPolicy.IssuedTokenType).isEmpty())
            issuedTokenType = UaString(&uaPolicy.IssuedTokenType).toUtf8();
        if (!UaString(&uaPolicy.IssuerEndpointUrl).isEmpty())
            issuerEndpointUrl = UaString(&uaPolicy.IssuerEndpointUrl).toUtf8();
        if (!UaString(&uaPolicy.SecurityPolicyUri).isEmpty())
            securityPolicyUri = UaString(&uaPolicy.SecurityPolicyUri).toUtf8();
    }


    // Constructor
    // =============================================================================================
    UserTokenPolicy::UserTokenPolicy(
            string          policyId,
            UserTokenType   tokenType,
            string          issuedTokenType,
            string          issuerEndpointUrl,
            string          securityPolicyUri)
    : policyId(policyId),
      tokenType(tokenType),
      issuedTokenType(issuedTokenType),
      issuerEndpointUrl(issuerEndpointUrl),
      securityPolicyUri(securityPolicyUri)
    {}


    // Get a string representation
    // =============================================================================================
    string UserTokenPolicy::toString(const std::string& indent, size_t colon) const
    {
        stringstream ss;

        ss << indent << " - tokenType";
        ss << fillToPos(ss, colon);
        ss << ": " << tokenType << " (" << uaf::usertokentypes::toString(tokenType) << ")\n";

        ss << indent << " - issuedTokenType";
        ss << fillToPos(ss, colon);
        ss << ": " << issuedTokenType << "\n";

        ss << indent << " - issuerEndpointUrl";
        ss << fillToPos(ss, colon);
        ss << ": " << issuerEndpointUrl << "\n";

        ss << indent << " - securityPolicyUri";
        ss << fillToPos(ss, colon);
        ss << ": " << securityPolicyUri;

        return ss.str();
    }








}
