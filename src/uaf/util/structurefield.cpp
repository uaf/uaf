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

#include "uaf/util/structurefield.h"

namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;


    // Constructor
    // =============================================================================================
    StructureField::StructureField()
    {}


    // Get the name
    // =============================================================================================
    std::string StructureField::name() const
    {
        string ret;
        UaString uaString(uaStructureField_.name());
        if ( ! (uaString.isNull() || uaString.isEmpty() ) )
            ret = uaString.toUtf8();
        return ret;
    }

    // Set the documentation
    // =============================================================================================
    void StructureField::setName(const string& name)
    {
        uaStructureField_.setName(UaString(name.c_str()));
    }

    // Get the documentation
    // =============================================================================================
    LocalizedText StructureField::documentation() const
    {
        LocalizedText ret;
        UaLocalizedText uaText(uaStructureField_.documentation());
        ret.fromSdk(uaText);
        return ret;
    }

    // Set the documentation
    // =============================================================================================
    void StructureField::setDocumentation(const LocalizedText& doc)
    {
        UaLocalizedText uaText;
        doc.toSdk(uaText);
        uaStructureField_.setDocumentation(uaText);
    }

    // Get the type id
    // =============================================================================================
    NodeId StructureField::typeId() const
    {
        NodeId ret;
        UaNodeId uaNodeId(uaStructureField_.typeId());
        ret.fromSdk(uaNodeId);
        return ret;
    }

    // Set the type id
    // =============================================================================================
    void StructureField::setDataTypeId(const NodeId& dataTypeId)
    {
        UaNodeId uaNodeId;
        dataTypeId.toSdk(uaNodeId);
        uaStructureField_.setDataTypeId(uaNodeId);
    }

    // Get the value type
    // =============================================================================================
    uaf::opcuatypes::OpcUaType StructureField::valueType() const
    {
        return uaf::opcuatypes::fromSdkToUaf(uaStructureField_.valueType());
    }

    // Set the value type
    // =============================================================================================
    void StructureField::setValueType(uaf::opcuatypes::OpcUaType valueType)
    {
        uaStructureField_.setValueType(uaf::opcuatypes::fromUafToSdk(valueType));
    }

    // Get the value type
    // =============================================================================================
    uaf::StructureField::ArrayType StructureField::arrayType() const
    {
        if (uaStructureField_.arrayType() == UaStructureField::ArrayType_Scalar)
            return uaf::StructureField::ArrayType_Scalar;
        else if (uaStructureField_.arrayType() == UaStructureField::ArrayType_Array)
            return uaf::StructureField::ArrayType_Array;
        else
            // not possible, but return Scalar to avoid segfaults
            return uaf::StructureField::ArrayType_Scalar;
    }

    // Set the value type
    // =============================================================================================
    void StructureField::setArrayType(uaf::StructureField::ArrayType arrayType)
    {
        if (arrayType == uaf::StructureField::ArrayType_Scalar)
            uaStructureField_.setArrayType(UaStructureField::ArrayType_Scalar);
        else if (arrayType == uaf::StructureField::ArrayType_Array)
            uaStructureField_.setArrayType(UaStructureField::ArrayType_Array);
    }


    // Get a string representation
    // =============================================================================================
    std::string StructureField::toString(const string& indent, size_t colon) const
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

            ss << indent << " - typeId";
            ss << fillToPos(ss, colon);
            ss << ": " << typeId().toString() << "\n";

            ss << indent << " - valueType";
            ss << fillToPos(ss, colon);
            ss << ": " << valueType() << " (" << uaf::opcuatypes::toString(valueType()) << ")" << "\n";

            ss << indent << " - arrayType";
            ss << fillToPos(ss, colon);
            if (arrayType() == uaf::StructureField::ArrayType_Scalar)
                ss << ": ArrayType_Scalar";
            else if (arrayType() == uaf::StructureField::ArrayType_Array)
                ss << ": ArrayType_Array";
            else
                ss << ": UNKNOWN";

            return ss.str();
        }
    }

}


