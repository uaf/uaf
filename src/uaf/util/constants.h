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

#ifndef UAF_CONSTANTS_H_
#define UAF_CONSTANTS_H_

// STD
#include <string>
#include <vector>
#include <stdint.h>
// SDK
#include "uabase/uaplatformlayer.h"
// UAF

namespace uaf
{


    namespace constants
    {

        /** The OPC UA NameSpace URI. */
        static const std::string OPCUA_NAMESPACE_URI = "http://opcfoundation.org/UA/";

        /** The OPC UA NameSpace ID. */
        static const uint16_t OPCUA_NAMESPACE_ID = 0;

        /** Client handle value when it was not assigned. */
        static const uint32_t CLIENTHANDLE_NOT_ASSIGNED = OpcUa_UInt32_Max;

        /** Maximum client handle value. */
        static const uint32_t CLIENTHANDLE_MAX = OpcUa_UInt32_Max - 1;

        /** RequestHandle value when it was not assigned. */
        static const uaf::RequestHandle REQUESTHANDLE_NOT_ASSIGNED = OpcUa_UInt64_Max;

        /** Maximum RequestHandle value. */
        static const uaf::RequestHandle REQUESTHANDLE_MAX          = OpcUa_UInt64_Max - 1;

    }


}


#endif /* UAF_CONSTANTS_H_ */
