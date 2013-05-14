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

#ifndef UAF_MESSAGESECURITYMODES_H_
#define UAF_MESSAGESECURITYMODES_H_

// STD
#include <string>
// SDK
#include "uabase/uaplatformlayer.h"
// UAF
#include "uaf/util/util.h"

namespace uaf
{

    namespace messagesecuritymodes
    {

        /**
         * The message security modes.
         *
         * @ingroup Util
         */
        enum MessageSecurityMode
        {
            Mode_Invalid         = 0,    /**< Invalid message security mode. */
            Mode_None            = 1,    /**< No signing, no encryption. */
            Mode_Sign            = 2,    /**< Signing only. */
            Mode_SignAndEncrypt  = 3     /**< Signing and encryption. */
        };


        /**
         * Get a string representation of the message security mode.
         *
         * @param mode  The message security mode (as an enum).
         * @return      The corresponding name of the message security mode.
         *
         * @ingroup Util
         */
        std::string UAF_EXPORT toString(MessageSecurityMode mode);


        /**
         * Convert the SDK/Stack instance to a UAF instance.
         *
         * @ingroup Util
         */
        OpcUa_MessageSecurityMode UAF_EXPORT fromUafToSdk(MessageSecurityMode mode);


        /**
         * Convert the UAF instance to a SDK/Stack instance.
         *
         * @ingroup Util
         */
        MessageSecurityMode UAF_EXPORT fromSdkToUaf(OpcUa_MessageSecurityMode mode);



    }

}


#endif /* UAF_MESSAGESECURITYMODES_H_ */
