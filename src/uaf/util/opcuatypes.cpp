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

#include "uaf/util/opcuatypes.h"

namespace uaf
{
    namespace opcuatypes
    {

        using namespace uaf::opcuatypes;


        // Get a string representation
        // =========================================================================================
        std::string toString(OpcUaType type)
        {
            switch(type)
            {
                case Null:              return "Null";
                case Boolean:           return "Boolean";
                case SByte:             return "SByte";
                case Byte:              return "Byte";
                case Int16:             return "Int16";
                case UInt16:            return "UInt16";
                case Int32:             return "Int32";
                case UInt32:            return "UInt32";
                case Int64:             return "Int64";
                case UInt64:            return "UInt64";
                case Float:             return "Float";
                case Double:            return "Double";
                case String:            return "String";
                case DateTime:          return "DateTime";
                case Guid:              return "Guid";
                case ByteString:        return "ByteString";
                case XmlElement:        return "XmlElement";
                case NodeId:            return "NodeId";
                case ExpandedNodeId:    return "ExpandedNodeId";
                case StatusCode:        return "StatusCode";
                case QualifiedName:     return "QualifiedName";
                case LocalizedText:     return "LocalizedText";
                case ExtensionObject:   return "ExtensionObject";
                case DataValue:         return "DataValue";
                case Variant:           return "Variant";
                case DiagnosticInfo:    return "DiagnosticInfo";
                default:                return "Unknown";
            }
        }


        // Convert the SDK/Stack instance to a UAF instance.
        // =========================================================================================
        OpcUa_BuiltInType fromUafToSdk(OpcUaType type)
        {
            switch (type)
            {
                case Null:              return OpcUaType_Null;
                case Boolean:           return OpcUaType_Boolean;
                case SByte:             return OpcUaType_SByte;
                case Byte:              return OpcUaType_Byte;
                case Int16:             return OpcUaType_Int16;
                case UInt16:            return OpcUaType_UInt16;
                case Int32:             return OpcUaType_Int32;
                case UInt32:            return OpcUaType_UInt32;
                case Int64:             return OpcUaType_Int64;
                case UInt64:            return OpcUaType_UInt64;
                case Float:             return OpcUaType_Float;
                case Double:            return OpcUaType_Double;
                case String:            return OpcUaType_String;
                case DateTime:          return OpcUaType_DateTime;
                case Guid:              return OpcUaType_Guid;
                case ByteString:        return OpcUaType_ByteString;
                case XmlElement:        return OpcUaType_XmlElement;
                case NodeId:            return OpcUaType_NodeId;
                case ExpandedNodeId:    return OpcUaType_ExpandedNodeId;
                case StatusCode:        return OpcUaType_StatusCode;
                case QualifiedName:     return OpcUaType_QualifiedName;
                case LocalizedText:     return OpcUaType_LocalizedText;
                case ExtensionObject:   return OpcUaType_ExtensionObject;
                case DataValue:         return OpcUaType_DataValue;
                case Variant:           return OpcUaType_Variant;
                case DiagnosticInfo:    return OpcUaType_DiagnosticInfo;
                default:                return OpcUaType_Null;
            }
        }



        OpcUaType fromSdkToUaf(OpcUa_BuiltInType type)
        {
            switch (type)
            {
                case OpcUaType_Null:              return Null;
                case OpcUaType_Boolean:           return Boolean;
                case OpcUaType_SByte:             return SByte;
                case OpcUaType_Byte:              return Byte;
                case OpcUaType_Int16:             return Int16;
                case OpcUaType_UInt16:            return UInt16;
                case OpcUaType_Int32:             return Int32;
                case OpcUaType_UInt32:            return UInt32;
                case OpcUaType_Int64:             return Int64;
                case OpcUaType_UInt64:            return UInt64;
                case OpcUaType_Float:             return Float;
                case OpcUaType_Double:            return Double;
                case OpcUaType_String:            return String;
                case OpcUaType_DateTime:          return DateTime;
                case OpcUaType_Guid:              return Guid;
                case OpcUaType_ByteString:        return ByteString;
                case OpcUaType_XmlElement:        return XmlElement;
                case OpcUaType_NodeId:            return NodeId;
                case OpcUaType_ExpandedNodeId:    return ExpandedNodeId;
                case OpcUaType_StatusCode:        return StatusCode;
                case OpcUaType_QualifiedName:     return QualifiedName;
                case OpcUaType_LocalizedText:     return LocalizedText;
                case OpcUaType_ExtensionObject:   return ExtensionObject;
                case OpcUaType_DataValue:         return DataValue;
                case OpcUaType_Variant:           return Variant;
                case OpcUaType_DiagnosticInfo:    return DiagnosticInfo;
                default:                          return Null;
            }
        }


    }
}
