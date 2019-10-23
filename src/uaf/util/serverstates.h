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

#ifndef UAF_SERVERSTATES_H_
#define UAF_SERVERSTATES_H_

// STD
#include <string>
// SDK
#include "uabasecpp/uaplatformlayer.h"
// UAF
#include "uaf/util/util.h"


/** @file */


namespace uaf
{

    namespace serverstates
    {

        /**
         * Type of the identifier.
         *
         * @ingroup Util
         */
        enum ServerState
        {
            Running            = OpcUa_ServerState_Running,
            Failed             = OpcUa_ServerState_Failed,
            NoConfiguration    = OpcUa_ServerState_NoConfiguration,
            Suspended          = OpcUa_ServerState_Suspended,
            Shutdown           = OpcUa_ServerState_Shutdown,
            Test               = OpcUa_ServerState_Test,
            CommunicationFault = OpcUa_ServerState_CommunicationFault,
            Unknown            = OpcUa_ServerState_Unknown
        };

        /**
         * Get a string representation of the server state
         *
         * @param type  The server state (as an enum value).
         * @return      The corresponding name.
         *
         * @ingroup Util
         */
        std::string UAF_EXPORT toString(uaf::serverstates::ServerState state);


        /**
         * Convert the SDK/Stack instance to a UAF instance.
         *
         * @ingroup Util
         */
        uaf::serverstates::ServerState UAF_EXPORT fromSdkToUaf(
                OpcUa_ServerState state);


        /**
         * Convert the UAF instance to a SDK/Stack instance.
         *
         * @ingroup Util
         */
        OpcUa_ServerState UAF_EXPORT fromUafToSdk(
                uaf::serverstates::ServerState state);

    }


}


#endif /* UAF_SERVERSTATES_H_ */
