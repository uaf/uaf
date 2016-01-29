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

#include "uaf/util/structuredefinition.h"

namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;


    // Constructor
    // =============================================================================================
    StructureDefinition::StructureDefinition()
    {}


    // is the definition NULL?
    // =============================================================================================
    bool StructureDefinition::isNull() const
    {
        return uaStructureDefinition_.isNull();
    }


    // Clear the definition
    // =============================================================================================
    void StructureDefinition::clear()
    {
        uaStructureDefinition_.clear();
    }


    // Set the data type nodeid
    // =============================================================================================
    void StructureDefinition::setDataTypeId(const NodeId& nodeId)
    {
        UaNodeId uaNodeId;
        nodeId.toSdk(uaNodeId);
        uaStructureDefinition_.setDataTypeId(uaNodeId);
    }


    // Get the data type nodeid
    // =============================================================================================
    NodeId StructureDefinition::dataTypeId() const
    {
        NodeId ret;
        UaNodeId uaNodeId(uaStructureDefinition_.dataTypeId());
        ret.fromSdk(uaNodeId);
        return ret;
    }


    // Get the name
    // =============================================================================================
    std::string StructureDefinition::name() const
    {
        string ret;
        UaString uaString(uaStructureDefinition_.name());
        if ( ! (uaString.isNull() || uaString.isEmpty() ) )
            ret = uaString.toUtf8();
        return ret;
    }


    // Set the name
    // =============================================================================================
    void StructureDefinition::setName(const string& name)
    {
        uaStructureDefinition_.setName(UaString(name.c_str()));
    }

    // Get the documentation
    // =============================================================================================
    LocalizedText StructureDefinition::documentation() const
    {
        LocalizedText ret;
        UaLocalizedText uaText(uaStructureDefinition_.documentation());
        ret.fromSdk(uaText);
        return ret;
    }

    // Set the documentation
    // =============================================================================================
    void StructureDefinition::setDocumentation(const LocalizedText& doc)
    {
        UaLocalizedText uaText;
        doc.toSdk(uaText);
        uaStructureDefinition_.setDocumentation(uaText);
    }


    // Get the name
    // =============================================================================================
    std::string StructureDefinition::getNamespace() const
    {
        string ret;
        UaString uaString(uaStructureDefinition_.getNamespace());
        if ( ! (uaString.isNull() || uaString.isEmpty() ) )
            ret = uaString.toUtf8();
        return ret;
    }


    // Set the namespace
    // =============================================================================================
    void StructureDefinition::setNamespace(const string& name)
    {
        uaStructureDefinition_.setNamespace(UaString(name.c_str()));
    }


    // Get the base type id
    // =============================================================================================
    NodeId StructureDefinition::baseTypeId() const
    {
        NodeId ret;
        UaNodeId uaNodeId(uaStructureDefinition_.baseTypeId());
        ret.fromSdk(uaNodeId);
        return ret;
    }

    // Set the base type id
    // =============================================================================================
    void StructureDefinition::setBaseType(const StructureDefinition& definition)
    {
        UaStructureDefinition uaDefinition;
        definition.toSdk(uaDefinition);
        uaStructureDefinition_.setBaseType(uaDefinition);
    }

    // Create a subtype
    // =============================================================================================
    StructureDefinition StructureDefinition::createSubtype() const
    {
        StructureDefinition ret;
        UaStructureDefinition uaSubtype(uaStructureDefinition_.createSubtype());
        ret.fromSdk(uaSubtype);
        return ret;
    }


    // Get the children count
    // =============================================================================================
    int StructureDefinition::childrenCount() const
    {
        return uaStructureDefinition_.childrenCount();
    }


    // Get child i
    // =============================================================================================
    StructureField StructureDefinition::child(int i) const
    {
        StructureField ret;
        UaStructureField uaField(uaStructureDefinition_.child(i));
        ret.fromSdk(uaField);
        return ret;
    }


    // Add child
    // =============================================================================================
    void StructureDefinition::addChild(const StructureField &newChild)
    {
        UaStructureField uaChild;
        newChild.toSdk(uaChild);
        uaStructureDefinition_.addChild(uaChild);
    }


    // Remove
    // =============================================================================================
    void StructureDefinition::remove(const string& name)
    {
        uaStructureDefinition_.remove(UaString(name.c_str()));
    }


    // Is the definition a union?
    // =============================================================================================
    bool StructureDefinition::isUnion() const
    {
        return uaStructureDefinition_.isUnion();
    }


    // Set the binary encoding ID
    // =============================================================================================
    void StructureDefinition::setBinaryEncodingId(const NodeId& nodeId)
    {
        UaNodeId uaNodeId;
        nodeId.toSdk(uaNodeId);
        uaStructureDefinition_.setBinaryEncodingId(uaNodeId);
    }


    // Get the binary encoding ID
    // =============================================================================================
    NodeId StructureDefinition::binaryEncodingId() const
    {
        NodeId ret;
        UaNodeId uaNodeId(uaStructureDefinition_.binaryEncodingId());
        ret.fromSdk(uaNodeId);
        return ret;
    }

    // Set the XML encoding ID
    // =============================================================================================
    void StructureDefinition::setXmlEncodingId(const NodeId& nodeId)
    {
        UaNodeId uaNodeId;
        nodeId.toSdk(uaNodeId);
        uaStructureDefinition_.setXmlEncodingId(uaNodeId);
    }


    // Get the XML encoding ID
    // =============================================================================================
    NodeId StructureDefinition::xmlEncodingId() const
    {
        NodeId ret;
        UaNodeId uaNodeId(uaStructureDefinition_.xmlEncodingId());
        ret.fromSdk(uaNodeId);
        return ret;
    }




    // Get a string representation
    // =============================================================================================
    std::string StructureDefinition::toString(const string& indent, size_t colon) const
    {
        if (isNull())
            return indent + string("NULL");
        else
        {
            stringstream ss;

            ss << indent << " - name";
            ss << fillToPos(ss, colon);
            ss << ": " << name() << "\n";

            ss << indent << " - documentation";
            ss << fillToPos(ss, colon);
            ss << ": " << documentation().toString() << "\n";

            ss << indent << " - dataTypeId";
            ss << fillToPos(ss, colon);
            ss << ": " << dataTypeId().toString() << "\n";

            ss << indent << " - name";
            ss << fillToPos(ss, colon);
            ss << ": " << name() << "\n";

            ss << indent << " - namespace";
            ss << fillToPos(ss, colon);
            ss << ": " << getNamespace() << "\n";

            ss << indent << " - baseTypeId";
            ss << fillToPos(ss, colon);
            ss << ": " << baseTypeId().toString() << "\n";

            ss << indent << " - childrenCount";
            ss << fillToPos(ss, colon);
            ss << ": " << childrenCount() << "\n";

            ss << indent << " - children";

            if (childrenCount() == 0)
            {
                ss << fillToPos(ss, colon);
                ss << ": []\n";
            }
            else
            {
                ss << "\n";

                for (int i = 0; i<childrenCount(); i++)
                {
                    ss << indent << "    - " << "child(" << i << ")\n";
                    ss << child(i).toString(indent + string("      "), colon) << "\n";
                }
            }

            ss << indent << " - isUnion";
            ss << fillToPos(ss, colon);
            ss << ": " << (isUnion() ? "True" : "False") << "\n";

            ss << indent << " - binaryEncodingId";
            ss << fillToPos(ss, colon);
            ss << ": " << binaryEncodingId().toString() << "\n";

            ss << indent << " - xmlEncodingId";
            ss << fillToPos(ss, colon);
            ss << ": " << xmlEncodingId().toString();

            return ss.str();
        }
    }

}


