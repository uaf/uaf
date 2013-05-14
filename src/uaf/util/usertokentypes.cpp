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

#include "uaf/util/usertokentypes.h"

namespace uaf
{
    namespace usertokentypes
    {

        using uaf::usertokentypes::UserTokenType;
        using std::string;


        // Get a string representation
        // =========================================================================================
        string toString(UserTokenType type)
        {
            switch (type)
            {
                case Anonymous:     return "Anonymous";
                case UserName:      return "UserName";
                case Certificate:   return "Certificate";
                case IssuedToken:   return "IssuedToken";
                default:            return "UNKNOWN";
            }
        }


        // Convert the SDK to UAF instance
        // =========================================================================================
        OpcUa_UserTokenType fromUafToSdk(UserTokenType type)
        {
            switch (type)
            {
                case Anonymous:     return OpcUa_UserTokenType_Anonymous;
                case UserName:      return OpcUa_UserTokenType_UserName;
                case Certificate:   return OpcUa_UserTokenType_Certificate;
                case IssuedToken:   return OpcUa_UserTokenType_IssuedToken;
                default:            return OpcUa_UserTokenType_Anonymous;
            }
        }


        // Convert the UAF to SDK instance
        // =========================================================================================
        UserTokenType fromSdkToUaf(OpcUa_UserTokenType type)
        {
            switch (type)
            {
                case OpcUa_UserTokenType_Anonymous:     return Anonymous;
                case OpcUa_UserTokenType_UserName:      return UserName;
                case OpcUa_UserTokenType_Certificate:   return Certificate;
                case OpcUa_UserTokenType_IssuedToken:   return IssuedToken;
                default:                                return Anonymous;
            }
        }

    }
}
