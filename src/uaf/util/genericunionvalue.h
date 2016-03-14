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

#ifndef UAF_GENERICUNIONVALUE_H_
#define UAF_GENERICUNIONVALUE_H_


// STD
#include <string>
#include <sstream>
#include <stdint.h>

// SDK
#include "uabase/uagenericunionvalue.h"
#include "uabase/uastructurefielddata.h"
// UAF
#include "uaf/util/util.h"
#include "uaf/util/localizedtext.h"
#include "uaf/util/nodeid.h"
#include "uaf/util/opcuatypes.h"
#include "uaf/util/extensionobject.h"
#include "uaf/util/variant.h"
#include "uaf/util/structuredefinition.h"
#include "uaf/util/structurefielddatatypes.h"


namespace uaf
{

	// forward declarations
	class UAF_EXPORT GenericStructureValue;


    /*******************************************************************************************//**
     * A GenericUnionValue may represent a Union.
     *
     * @ingroup Util
     **********************************************************************************************/
    class UAF_EXPORT GenericUnionValue
    {
    public:


        /**
         * This enum defines the encoding of the generic union value.
         *
         * @ingroup Util
         */
        enum Encoding
        {
            Encoding_Binary = OpcUa_ExtensionObjectEncoding_Binary,
			Encoding_Xml    = OpcUa_ExtensionObjectEncoding_Xml
        };

        /**
         * Construct a GenericUnionValue.
         */
        GenericUnionValue();

        /**
         * Construct a GenericValue.
         */
        GenericUnionValue(
        		const uaf::ExtensionObject& extensionObject,
        		const uaf::StructureDefinition& definition);

        /**
         * Clear the generic value.
         */
        void clear();

        /**
         * Set a value.
         */
        uaf::SdkStatus setGenericUnion(
                const uaf::ByteString&          data,
                Encoding                        encoding,
                const uaf::StructureDefinition& structureDefinition);
        uaf::SdkStatus setGenericUnion(
                const uaf::ExtensionObject&     extensionObject,
                const uaf::StructureDefinition& structureDefinition);

        /**
         * Set a new value (Variant) for the specified field.
         */
        uaf::SdkStatus setValue(const std::string& fieldName, const uaf::Variant& value);
        uaf::SdkStatus setValue(int index, const uaf::Variant& value);

        /**
         * Set a new value (GenericStructureValue) for the specified field.
         */
        uaf::SdkStatus setValue(const std::string& fieldName, const uaf::GenericStructureValue& value);
        uaf::SdkStatus setValue(int index, const uaf::GenericStructureValue& value);

        /**
         * Set a new value (vector of GenericStructureValue) for the specified field.
         */
        uaf::SdkStatus setValue(const std::string& sfieldName, const std::vector<uaf::GenericStructureValue>& array);
        uaf::SdkStatus setValue(int index, const std::vector<uaf::GenericStructureValue>& array);

        /**
         * Set a new value (GenericUnionValue) for the specified field.
         */
        uaf::SdkStatus setValue(const std::string& sfieldName, const uaf::GenericUnionValue& value);
        uaf::SdkStatus setValue(int index, const uaf::GenericUnionValue& value);

        /**
         * Set a new value (vector of GenericUnionValue) for the specified field.
         */
        uaf::SdkStatus setValue(const std::string& sfieldName, const std::vector<uaf::GenericUnionValue>& array);
        uaf::SdkStatus setValue(int index, const std::vector<uaf::GenericUnionValue>& array);

        /**
         * Get the value of the active field if it is a Variant.
         */
        uaf::Variant value() const;

        /**
         * Get the value of the active field if it is a GenericStructureValue.
         */
        uaf::GenericStructureValue genericStructure(uint32_t* opcUaStatusCode) const;

        /**
         * Get the value of the active field if it is a vector of GenericStructureValues.
         */
        std::vector<uaf::GenericStructureValue> genericStructureArray(uint32_t* opcUaStatusCode) const;

        /**
         * Get the value of the active field if it is a GenericUnionValue.
         */
        uaf::GenericUnionValue genericUnion(uint32_t* opcUaStatusCode) const;

        /**
         * Get the value of the active field if it is a vector of GenericUnionValues.
         */
        std::vector<uaf::GenericUnionValue> genericUnionArray(uint32_t* opcUaStatusCode) const;

        /**
         * Get the definition.
         */
        uaf::StructureDefinition definition() const;

        /**
         * Get the index of the active value.
         */
        int switchValue() const;

        /**
         * Get the currently used field.
         */
        uaf::StructureField field() const;

        /**
         * Convert the GenericStructureValue to an ExtensionObject.
         */
        void toExtensionObject(
        		uaf::ExtensionObject& extensionObject,
        		Encoding valueEncoding = GenericUnionValue::Encoding_Binary) const;

        /**
         * Get a string representation.
         *
         * @return The string representation.
         */
        std::string toString(const std::string& indent="", std::size_t colon=26) const;

        /**
         * Fill the instance from an SDK instance.
         */
        void fromSdk(const UaGenericUnionValue& uaGenericUnionValue) { uaGenericUnionValue_ = uaGenericUnionValue; }


        /**
         * Copy the instance to an SDK instance.
         */
        void toSdk(UaGenericUnionValue& uaGenericUnionValue) const { uaGenericUnionValue = uaGenericUnionValue_; };


    private:

        // the wrapped SDK variable
        UaGenericUnionValue uaGenericUnionValue_;

    };

}



#endif /* UAF_GENERICUNIONVALUE_H_ */
