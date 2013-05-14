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
    : type(Numeric),
      idNumeric(0)
    {}


    // Constructor
    // =============================================================================================
    NodeIdIdentifier::NodeIdIdentifier(const NodeIdIdentifier& other)
    : type(other.type),
      idNumeric(other.idNumeric),
      idString(other.idString)
    {}


    // Constructor
    // =============================================================================================
    NodeIdIdentifier::NodeIdIdentifier(const string& idString)
    : idString(idString),
      idNumeric(0),
      type(String)
    {}


    // Constructor
    // =============================================================================================
    NodeIdIdentifier::NodeIdIdentifier(uint32_t idNumeric)
    : idNumeric(idNumeric),
      type(Numeric)
    {}


    // Get a string representation
    // =============================================================================================
    std::string NodeIdIdentifier::toString() const
    {
        stringstream ss;
        if (type == String)
        {
            ss << "String|" << idString;
        }
        else if (type == Numeric)
        {
            ss << "Numeric|" << idNumeric;
        }
        else
        {
            ss << "???";
        }
        return ss.str();
    }


    // Fill out the NodeIdIdentifier with information from an OpcUa_NodeId instance
    // =============================================================================================
    Status NodeIdIdentifier::fromSdk(const OpcUa_NodeId& opcUaNodeId)
    {
        Status ret;

        if (opcUaNodeId.IdentifierType == OpcUa_IdentifierType_Numeric)
        {
            type = Numeric;
            idNumeric = opcUaNodeId.Identifier.Numeric;
            ret.setGood();
        }
        else if (opcUaNodeId.IdentifierType == OpcUa_IdentifierType_String)
        {
            type = String;
            idString = UaString(&opcUaNodeId.Identifier.String).toUtf8();
            ret.setGood();
        }
        else
        {
            ret.setStatus(statuscodes::UnsupportedError,
                          "Identifier type currently not supported by the UAF");
        }

        return ret;
    }


    // operator==
    // =============================================================================================
    bool operator==(const NodeIdIdentifier& object1, const NodeIdIdentifier& object2)
    {
        return object1.type == object2.type
            && object1.idNumeric == object2.idNumeric
            && object1.idString == object2.idString;
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
        {
            return object1.type < object2.type;
        }
        else if (object1.idNumeric != object2.idNumeric)
        {
            return object1.idNumeric < object2.idNumeric;
        }
        else
        {
            return object1.idString < object2.idString;
        }
    }


}
