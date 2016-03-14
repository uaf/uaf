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

#include "uaf/util/structurefielddatatypes.h"

namespace uaf
{
    namespace structurefielddatatypes
    {

        using namespace uaf::structurefielddatatypes;

        // Get a string representation
        // =========================================================================================
        std::string toString(StructureFieldDataType type)
        {
            switch (type)
            {
                case Variant:               return "Variant";
                case GenericStructure:      return "GenericStructure";
                case GenericStructureArray: return "GenericStructureArray";
                case GenericUnion:          return "GenericUnion";
                case GenericUnionArray:     return "GenericUnionArray";
                case GenericOptionSet:      return "GenericOptionSet";
                case GenericOptionSetArray: return "GenericOptionSetArray";
                case Empty:                 return "Empty";
                default:                                           return "INVALID";
            }
        }


        // UAF to SDK type
        // =========================================================================================
        UaStructureFieldDataType fromUafToSdk(StructureFieldDataType type)
        {
            return static_cast<UaStructureFieldDataType>(type);
        }


        // SDK to UAF type
        // =========================================================================================
        StructureFieldDataType fromSdkToUaf(UaStructureFieldDataType type)
        {
            return static_cast<StructureFieldDataType>(type);
        }


    }
}
