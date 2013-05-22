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

#include "uaf/util/nodeclasses.h"

namespace uaf
{
    using namespace uaf;

    namespace nodeclasses
    {

        // Get a string representation
        // =========================================================================================
        std::string toString(nodeclasses::NodeClass nodeClass)
        {
            switch (nodeClass)
            {
                case nodeclasses::Unspecified:      return "Unspecified";
                case nodeclasses::Object:           return "Object";
                case nodeclasses::Variable:         return "Variable";
                case nodeclasses::Method:           return "Method";
                case nodeclasses::ObjectType:       return "ObjectType";
                case nodeclasses::VariableType:     return "VariableType";
                case nodeclasses::ReferenceType:    return "ReferenceType";
                case nodeclasses::DataType:         return "DataType";
                case nodeclasses::View:             return "View";
                default:                            return "UNKNOWN";
            }
        }


        // UAF to SDK mode
        // =========================================================================================
        OpcUa_NodeClass fromUafToSdk(nodeclasses::NodeClass nodeClass)
        {
            switch (nodeClass)
            {
                case nodeclasses::Unspecified:      return OpcUa_NodeClass_Unspecified;
                case nodeclasses::Object:           return OpcUa_NodeClass_Object;
                case nodeclasses::Variable:         return OpcUa_NodeClass_Variable;
                case nodeclasses::Method:           return OpcUa_NodeClass_Method;
                case nodeclasses::ObjectType:       return OpcUa_NodeClass_ObjectType;
                case nodeclasses::VariableType:     return OpcUa_NodeClass_VariableType;
                case nodeclasses::ReferenceType:    return OpcUa_NodeClass_ReferenceType;
                case nodeclasses::DataType:         return OpcUa_NodeClass_DataType;
                case nodeclasses::View:             return OpcUa_NodeClass_View;
                default:                            return OpcUa_NodeClass_Unspecified;
            }
        }

        // SDK to UAF mode
        // =========================================================================================
        nodeclasses::NodeClass fromSdkToUaf(OpcUa_NodeClass nodeClass)
        {
            switch (nodeClass)
            {
                case OpcUa_NodeClass_Unspecified:      return nodeclasses::Unspecified;
                case OpcUa_NodeClass_Object:           return nodeclasses::Object;
                case OpcUa_NodeClass_Variable:         return nodeclasses::Variable;
                case OpcUa_NodeClass_Method:           return nodeclasses::Method;
                case OpcUa_NodeClass_ObjectType:       return nodeclasses::ObjectType;
                case OpcUa_NodeClass_VariableType:     return nodeclasses::VariableType;
                case OpcUa_NodeClass_ReferenceType:    return nodeclasses::ReferenceType;
                case OpcUa_NodeClass_DataType:         return nodeclasses::DataType;
                case OpcUa_NodeClass_View:             return nodeclasses::View;
                default:                               return nodeclasses::Unspecified;
            }
        }
    }
}
