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

#ifndef UAF_STRUCTUREDEFINITION_H_
#define UAF_STRUCTUREDEFINITION_H_


// STD
#include <string>
#include <sstream>
#include <stdint.h>

// SDK
#include "uabase/uastructuredefinition.h"
// UAF
#include "uaf/util/util.h"
#include "uaf/util/localizedtext.h"
#include "uaf/util/nodeid.h"
#include "uaf/util/opcuatypes.h"
#include "uaf/util/stringifiable.h"
#include "uaf/util/structurefield.h"


namespace uaf
{


    /*******************************************************************************************//**
     * A StructureDefinition defines structures (datatypes).
     *
     * @ingroup Util
     **********************************************************************************************/
    class UAF_EXPORT StructureDefinition
    {
    public:

        /**
         * Construct a StructureField.
         */
        StructureDefinition();


        /**
         * Is the name of the field empty?
         *
         * @return True if empty.
         */
        bool isNull() const;


        /**
         * Clear the defintion.
         */
        void clear();


        /**
         * Get the data type id of the definition.
         */
        void setDataTypeId(const uaf::NodeId& dataTypeId);


        /**
         * Get the data type id of the definition.
         */
        uaf::NodeId dataTypeId() const;


        /**
         * Get the name of the definition.
         */
        std::string name() const;


        /**
         * Set the name of the definition.
         */
        void setName(const std::string& name);


        /**
         * Get the documentation of the definition.
         */
        uaf::LocalizedText documentation() const;


        /**
         * Set the documentation of the definition.
         */
        void setDocumentation(const uaf::LocalizedText& doc);


        /**
         * Get the namespace of the definition.
         */
        std::string getNamespace() const; // can't use "namespace()" because namespace is a reserved word


        /**
         * Set the namespace of the definition.
         */
        void setNamespace(const std::string& name);


        /**
         * Set the base type.
         */
        void setBaseType(const uaf::StructureDefinition& baseType);

        /**
         * Get the NodeId of the base type.
         */
        uaf::NodeId baseTypeId() const;

        /**
         * Create and return a subtype.
         */
        uaf::StructureDefinition createSubtype() const;


        /**
         * Get the number of children.
         */
        int childrenCount() const;

        /**
         * Get the field of the child with the given number.
         */
        uaf::StructureField child(int i) const;


        /**
         * Add a child.
         */
        void addChild(const uaf::StructureField& newChild);


        /**
         * Remove the field with the given name.
         */
        void remove(const std::string& fieldName);


        /**
         * Does the definition represent a Union?
         */
        bool isUnion() const;


        /**
         * Set the binary encoding ID.
         */
        void setBinaryEncodingId(const uaf::NodeId& nodeId);


        /**
         * Get the binary encoding ID.
         */
        uaf::NodeId binaryEncodingId() const;


        /**
         * Set the XML encoding ID.
         */
        void setXmlEncodingId(const uaf::NodeId& nodeId);

        /**
         * Get the XML encoding ID.
         */
        uaf::NodeId xmlEncodingId() const;


        /**
         * Get a string representation.
         *
         * @return The string representation.
         */
        std::string toString(const std::string& indent="", std::size_t colon=23) const;


        /**
         * Fill the instance from an SDK instance.
         */
        void fromSdk(const UaStructureDefinition& uaStructureDefinition) { uaStructureDefinition_ = uaStructureDefinition; }


        /**
         * Copy the instance to an SDK instance.
         */
        void toSdk(UaStructureDefinition& uaStructureDefinition) const { uaStructureDefinition = uaStructureDefinition_; };

    private:

        // the wrapped SDK variable
        UaStructureDefinition uaStructureDefinition_;
    };

}



#endif /* UAF_STRUCTUREDEFINITION_H_ */
