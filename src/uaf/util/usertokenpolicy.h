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

#ifndef UAF_USERTOKENPOLICY_H_
#define UAF_USERTOKENPOLICY_H_


// STD
#include <string>
#include <sstream>
#include <vector>
#include <stdint.h>
// SDK
#include "uaclient/uadiscovery.h"
// UAF
#include "uaf/util/util.h"
#include "uaf/util/usertokentypes.h"
#include "uaf/util/stringifiable.h"


namespace uaf
{

    /*******************************************************************************************//**
    * A UserTokenPolicy instance describes the type, ID, issued token type, etc. of a user token.
    *
    * @ingroup Util
    ***********************************************************************************************/
    class UAF_EXPORT UserTokenPolicy
    {
    public:


        /**
         * Construct an empty user token policy.
         */
        UserTokenPolicy();


        /**
         * Create a user token policy based on the corresponding SDK variable.
         */
        UserTokenPolicy(const OpcUa_UserTokenPolicy& uaPolicy);


        /**
         * Construct a user token policy.
         */
        UserTokenPolicy(
                std::string                         policyId,
                uaf::usertokentypes::UserTokenType  tokenType,
                std::string                         issuedTokenType,
                std::string                         issuerEndpointUrl,
                std::string                         securityPolicyUri);

        /** The policy id. */
        std::string                         policyId;
        /** The user token type. */
        uaf::usertokentypes::UserTokenType  tokenType;
        /** The issued token type. */
        std::string                         issuedTokenType;
        /** The endpoint URL of the issuer. */
        std::string                         issuerEndpointUrl;
        /** The security policy URI. */
        std::string                         securityPolicyUri;


        /**
         * Get a string representation of the UserTokenPolicy.
         *
         * @param indentation   Indent each line with this string.
         * @param colon         Put the colon (double point) at this position.
         * @return              A string representation (multiple lines, separated by
         *                      newline-characters).
         */
        std::string toString(const std::string& indentation="", std::size_t colon=21) const;


        // comparison operators
        friend bool UAF_EXPORT operator<(
                const UserTokenPolicy& object1,
                const UserTokenPolicy& object2);
        friend bool UAF_EXPORT operator==(
                const UserTokenPolicy& object1,
                const UserTokenPolicy& object2);
        friend bool UAF_EXPORT operator!=(
                const UserTokenPolicy& object1,
                const UserTokenPolicy& object2);


    };
}
#endif /* UAF_USERTOKENPOLICY_H_ */
