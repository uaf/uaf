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
     * A GenericValue may represent a Structure or Enumeration.
     *
     * @ingroup Util
     **********************************************************************************************/
    class UAF_EXPORT GenericUnionValue
    {
    public:


        /**
         * This enum defines the encoding of the generic value.
         *
         * @ingroup Util
         */
        enum Encoding
        {
            Encoding_Binary = OpcUa_ExtensionObjectEncoding_Binary,
			Encoding_Xml    = OpcUa_ExtensionObjectEncoding_Xml
        };

        /**
         * Construct a GenericValue.
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


        uaf::SdkStatus setValue(const std::string& fieldName, const uaf::Variant& value);
        uaf::SdkStatus setValue(int index, const uaf::Variant& value);

        uaf::SdkStatus setValue(const std::string& sfieldName, const uaf::GenericStructureValue& value);
        uaf::SdkStatus setValue(int index, const uaf::GenericStructureValue& value);

        uaf::SdkStatus setValue(const std::string& sfieldName, const std::vector<uaf::GenericStructureValue>& array);
        uaf::SdkStatus setValue(int index, const std::vector<uaf::GenericStructureValue>& array);

        uaf::SdkStatus setValue(const std::string& sfieldName, const uaf::GenericUnionValue& value);
        uaf::SdkStatus setValue(int index, const uaf::GenericUnionValue& value);

        uaf::SdkStatus setValue(const std::string& sfieldName, const std::vector<uaf::GenericUnionValue>& array);
        uaf::SdkStatus setValue(int index, const std::vector<uaf::GenericUnionValue>& array);

        uaf::Variant value() const;

        uaf::GenericStructureValue genericStructureValue(uint32_t* opcUaStatusCode) const;

        std::vector<uaf::GenericStructureValue> genericStructureArray(uint32_t* opcUaStatusCode) const;

        uaf::GenericUnionValue genericUnionValue(uint32_t* opcUaStatusCode) const;

        std::vector<uaf::GenericUnionValue> genericUnionArray(uint32_t* opcUaStatusCode) const;


        uaf::StructureDefinition definition() const;

        int switchValue() const;
        uaf::StructureField field() const;


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
