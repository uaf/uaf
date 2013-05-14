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

#ifndef UAF_USERTOKENTYPES_H_
#define UAF_USERTOKENTYPES_H_

// STD
#include <string>
// SDK
// UAF
#include "uaf/util/util.h"

namespace uaf
{

    namespace usertokentypes
    {

        /**
         * This enum defines the types user tokens, i.e. the ways how users can identify themselves.
         *
         * @ingroup Util
         */
        enum UserTokenType
        {
            Anonymous   = 0,    /**< No token is required. */
            UserName    = 1,    /**< Username/password token is required. */
            Certificate = 2,    /**< Certificate token is required. */
            IssuedToken = 3     /**< A WS-Security token is required. */
        };


        /**
         * Get a string representation of the UserTokenType.
         *
         * @param userTokenType The user token type as a numerical value (e.g. 2).
         * @return              The corresponding name of the user token type (e.g. "Certificate").
         *
         * @ingroup Util
         */
        std::string UAF_EXPORT toString(uaf::usertokentypes::UserTokenType userTokenType);


        /**
         * Convert the SDK/Stack instance to a UAF instance.
         *
         * @ingroup Util
         */
        uaf::usertokentypes::UserTokenType UAF_EXPORT fromSdkToUaf(OpcUa_UserTokenType type);


        /**
         * Convert the UAF instance to a SDK/Stack instance.
         *
         * @ingroup Util
         */
        OpcUa_UserTokenType UAF_EXPORT fromUafToSdk(uaf::usertokentypes::UserTokenType type);


    }
}


#endif /* UAF_USERTOKENTYPES_H_ */
