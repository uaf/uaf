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

#include "uaf/util/securitypolicies.h"

namespace uaf
{
    using namespace uaf;
    using std::string;

    namespace securitypolicies
    {
        using namespace securitypolicies;


        // Get a string representation
        // =============================================================================================
        string toCompactString(const string& policy)
        {
            if      (policy == UA_None)             return "None";
            else if (policy == UA_Basic128)         return "Basic128";
            else if (policy == UA_Basic128Rsa15)    return "Basic128Rsa15";
            else if (policy == UA_Basic192)         return "Basic192";
            else if (policy == UA_Basic192Rsa15)    return "Basic192Rsa15";
            else if (policy == UA_Basic256)         return "Basic256";
            else if (policy == UA_Basic256Rsa15)    return "Basic256Rsa15";
            else if (policy == UA_Basic256Sha256)   return "Basic256Sha256";
            else                                    return policy;
        }

    }

}
