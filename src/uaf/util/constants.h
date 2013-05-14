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
// UAF

namespace uaf
{


    namespace constants
    {

        /** The OPC UA NameSpace URI. */
        static const std::string OPCUA_NAMESPACE_URI = "http://opcfoundation.org/UA/";

        /** The OPC UA NameSpace ID. */
        static const uint16_t OPCUA_NAMESPACE_ID = 0;

    }


}


#endif /* UAF_CONSTANTS_H_ */
