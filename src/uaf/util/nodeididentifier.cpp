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

#include "uaf/util/nodeididentifier.h"


namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;
    using namespace uaf::nodeididentifiertypes;


    // Constructor
    // =============================================================================================
    NodeIdIdentifier::NodeIdIdentifier()
    : type(Identifier_Numeric),
      idNumeric(0)
    {}


    // Constructor
    // =============================================================================================
    NodeIdIdentifier::NodeIdIdentifier(const NodeIdIdentifier& other)
    : type(other.type),
      idString(other.idString),
      idNumeric(other.idNumeric),
      idGuid(other.idGuid),
      idOpaque(other.idOpaque)
    {}


    // Constructor
    // =============================================================================================
    NodeIdIdentifier::NodeIdIdentifier(const string& idString)
    : type(Identifier_String),
      idString(idString),
      idNumeric(0)
    {}


    // Constructor
    // =============================================================================================
    NodeIdIdentifier::NodeIdIdentifier(uint32_t idNumeric)
    : type(Identifier_Numeric),
      idNumeric(idNumeric)
    {}


    // Constructor
    // =============================================================================================
    NodeIdIdentifier::NodeIdIdentifier(const Guid& idGuid)
    : type(Identifier_Guid),
      idNumeric(0),
      idGuid(idGuid)
    {}


    // Constructor
    // =============================================================================================
    NodeIdIdentifier::NodeIdIdentifier(const ByteString& idOpaque)
    : type(Identifier_Opaque),
      idNumeric(0),
      idOpaque(idOpaque)
    {}


    // Is the identifier NULL?
    // =============================================================================================
    bool NodeIdIdentifier::isNull() const
    {
        return     (type == Identifier_Numeric)
                && (idNumeric == 0)
                && idString.empty();
    }


    // Get a string representation
    // =============================================================================================
    std::string NodeIdIdentifier::toString() const
    {
        stringstream ss;
        if (type == Identifier_String)
            ss << "String|" << idString;
        else if (type == Identifier_Numeric)
            ss << "Numeric|" << idNumeric;
        else if (type == Identifier_Guid)
            ss << "Guid|" << idGuid.toString();
        else if (type == Identifier_Opaque)
            ss << "Opaque|" << int(idOpaque.length()) << "bytes";
        else
            ss << "UNKNOWN_IDENTIFIER_TYPE";
        return ss.str();
    }


    // Fill out the NodeIdIdentifier with information from an OpcUa_NodeId instance
    // =============================================================================================
    Status NodeIdIdentifier::fromSdk(const OpcUa_NodeId& opcUaNodeId)
    {
        Status ret;

        if (opcUaNodeId.IdentifierType == OpcUa_IdentifierType_Numeric)
        {
            type = Identifier_Numeric;
            idNumeric = opcUaNodeId.Identifier.Numeric;
            ret.setGood();
        }
        else if (opcUaNodeId.IdentifierType == OpcUa_IdentifierType_String)
        {
            type = Identifier_String;
            idString = UaString(&opcUaNodeId.Identifier.String).toUtf8();
            ret.setGood();
        }
        else if (opcUaNodeId.IdentifierType == OpcUa_IdentifierType_Guid)
        {
            type = Identifier_Guid;
            idGuid.fromSdk(UaGuid(*opcUaNodeId.Identifier.Guid));
            ret.setGood();
        }
        else if (opcUaNodeId.IdentifierType == OpcUa_IdentifierType_Opaque)
        {
            type = Identifier_Opaque;
            idOpaque.fromSdk(UaByteString(opcUaNodeId.Identifier.ByteString));
            ret.setGood();
        }
        else
        {
            ret.setStatus(statuscodes::UnexpectedError, "Unknown identifier type!");
        }

        return ret;
    }


    // operator==
    // =============================================================================================
    bool operator==(const NodeIdIdentifier& object1, const NodeIdIdentifier& object2)
    {
        return object1.type == object2.type
            && object1.idNumeric == object2.idNumeric
            && object1.idString == object2.idString
            && object1.idGuid == object2.idGuid
            && object1.idOpaque == object2.idOpaque;
    }


    // operator!=
    // =============================================================================================
    bool operator!=(const NodeIdIdentifier& object1, const NodeIdIdentifier& object2)
    {
        return !(object1 == object2);
    }


    // operator<
    // =============================================================================================
    bool operator<(const NodeIdIdentifier& object1, const NodeIdIdentifier& object2)
    {
        if (object1.type != object2.type)
            return object1.type < object2.type;
        else if (object1.idNumeric != object2.idNumeric)
            return object1.idNumeric < object2.idNumeric;
        else if (object1.idGuid != object2.idGuid)
            return object1.idGuid < object2.idGuid;
        else if (object1.idOpaque != object2.idOpaque)
            return object1.idOpaque < object2.idOpaque;
        else
            return object1.idString < object2.idString;
    }


}
