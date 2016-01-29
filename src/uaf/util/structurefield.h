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

#ifndef UAF_STRUCTUREFIELD_H_
#define UAF_STRUCTUREFIELD_H_


// STD
#include <string>
#include <sstream>
#include <stdint.h>

// SDK
#include "uabase/uastructurefield.h"
// UAF
#include "uaf/util/util.h"
#include "uaf/util/localizedtext.h"
#include "uaf/util/nodeid.h"
#include "uaf/util/opcuatypes.h"
#include "uaf/util/stringifiable.h"


namespace uaf
{


    /*******************************************************************************************//**
     * A StructureField holds a field of a StructureDefinition (it wraps the SDK UaStructureField
     * quite literally).
     *
     * @ingroup Util
     **********************************************************************************************/
    class UAF_EXPORT StructureField
    {
    public:

        /**
         * This enum defines whether the field is scalar/array or matrix
         *
         * @ingroup Util
         */
        enum ArrayType
        {
            Scalar   = OpcUa_VariantArrayType_Scalar,
            Array    = OpcUa_VariantArrayType_Array
        };


        /**
         * Construct a StructureField.
         */
        StructureField();


        /**
         * Is the name of the field empty?
         *
         * @return True if empty.
         */
        bool isNull() const { return uaStructureField_.name().isNull(); } // uaStructureField_.isNull() is not const, bug


        /**
         * Get the name of the field.
         */
        std::string name() const;


        /**
         * Set the name of the field.
         */
        void setName(const std::string& name);


        /**
         * Get the documentation of the field.
         */
        uaf::LocalizedText documentation() const;


        /**
         * Set the documentation of the field.
         */
        void setDocumentation(const uaf::LocalizedText& doc);


        /**
         * Get the data type id of the field.
         */
        void setDataTypeId(const uaf::NodeId& dataTypeId);


        /**
         * Get the data type id of the field.
         */
        uaf::NodeId typeId() const;


        /**
         * Get the built-in type (value type).
         */
        uaf::opcuatypes::OpcUaType valueType() const;


        /**
         * Set the built-in type (value type).
         */
        void setValueType(const uaf::opcuatypes::OpcUaType valueType);


        /**
         * Set the array type.
         */
        void setArrayType(uaf::StructureField::ArrayType arrayType);


        /**
         * Get the array type.
         */
        uaf::StructureField::ArrayType arrayType() const;


        /**
         * Get a string representation.
         *
         * @return The string representation.
         */
        std::string toString(const std::string& indent="", std::size_t colon=17) const;


        /**
         * Fill the instance from an SDK instance.
         */
        void fromSdk(const UaStructureField& uaStructureField) { uaStructureField_ = uaStructureField; }


        /**
         * Copy the instance to an SDK instance.
         */
        void toSdk(UaStructureField& uaStructureField) const { uaStructureField = uaStructureField_; };

    private:

        // the wrapped SDK variable
        UaStructureField uaStructureField_;

    };

}



#endif /* UAF_STRUCTUREFIELD_H_ */
