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

#ifndef UAF_SECURITYPOLICIES_H_
#define UAF_SECURITYPOLICIES_H_

// STD
#include <string>
// SDK
// UAF
#include "uaf/util/util.h"

namespace uaf
{

    /**
     * The OPC UA attribute ids.
     */
    namespace securitypolicies
    {

        static const std::string UA_None           = "http://opcfoundation.org/UA/SecurityPolicy#None";
        static const std::string UA_Basic128       = "http://opcfoundation.org/UA/SecurityPolicy#Basic128";
        static const std::string UA_Basic128Rsa15  = "http://opcfoundation.org/UA/SecurityPolicy#Basic128Rsa15";
        static const std::string UA_Basic192       = "http://opcfoundation.org/UA/SecurityPolicy#Basic192";
        static const std::string UA_Basic192Rsa15  = "http://opcfoundation.org/UA/SecurityPolicy#Basic192Rsa15";
        static const std::string UA_Basic256       = "http://opcfoundation.org/UA/SecurityPolicy#Basic256";
        static const std::string UA_Basic256Rsa15  = "http://opcfoundation.org/UA/SecurityPolicy#Basic256Rsa15";
        static const std::string UA_Basic256Sha256 = "http://opcfoundation.org/UA/SecurityPolicy#Basic256Sha256";

        /**
         * Get a (short) string representation of the SecurityPolicy.
         *
         * @param securityPolicy    The security policy
         *                          (e.g. "http://opcfoundation.org/UA/SecurityPolicy#None").
         * @return                  The corresponding short name (e.g. "None").
         *
         * @ingroup Util
         */
        std::string UAF_EXPORT toCompactString(const std::string& securityPolicy);

    };

}


#endif /* UAF_SECURITYPOLICIES_H_ */
