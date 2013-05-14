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

#include "uaf/util/nodeididentifiertypes.h"

namespace uaf
{
    namespace nodeididentifiertypes
    {

        using namespace uaf::nodeididentifiertypes;


        // Get a string representation
        // =========================================================================================
        std::string toString(NodeIdIdentifierType type)
        {
            switch (type)
            {
                case Numeric:   return "Numeric";
                case String:    return "String";
                case Guid:      return "Guid";
                case Opaque:    return "Opaque";
                default:        return "INVALID";
            }
        }


        // UAF to SDK type
        // =========================================================================================
        OpcUa_IdentifierType fromUafToSdk(NodeIdIdentifierType type)
        {
            switch (type)
            {
                case Numeric:   return OpcUa_IdentifierType_Numeric;
                case String:    return OpcUa_IdentifierType_String;
                case Guid:      return OpcUa_IdentifierType_Guid;
                case Opaque:    return OpcUa_IdentifierType_Opaque;
                default:        return OpcUa_IdentifierType_Numeric;
            }
        }


        // SDK to UAF type
        // =========================================================================================
        NodeIdIdentifierType fromSdkToUaf(OpcUa_IdentifierType type)
        {
            switch (type)
            {
                case OpcUa_IdentifierType_Numeric:  return Numeric;
                case OpcUa_IdentifierType_String:   return String;
                case OpcUa_IdentifierType_Guid:     return Guid;
                case OpcUa_IdentifierType_Opaque:   return Opaque;
                default:                            return Numeric;
            }
        }


    }
}
