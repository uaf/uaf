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

#ifndef UAF_GENERICSTRUCTUREVALUE_H_
#define UAF_GENERICSTRUCTUREVALUE_H_


// STD
#include <string>
#include <sstream>
#include <stdint.h>

// SDK
#include "uabase/uagenericstructurevalue.h"
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


    /*******************************************************************************************//**
     * A GenericValue may represent a Structure or Enumeration.
     *
     * @ingroup Util
     **********************************************************************************************/
    class UAF_EXPORT GenericStructureValue
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
        GenericStructureValue();


        /**
         * Construct a GenericValue.
         */
        GenericStructureValue(
        		const uaf::ExtensionObject& extensionObject,
        		const uaf::StructureDefinition& definition);


        /**
         * Clear the generic value.
         */
        void clear();


        /**
         * Set a value.
         */
        uaf::SdkStatus setGenericValue(
                const uaf::ByteString&          data,
                Encoding                        encoding,
                const uaf::StructureDefinition& structureDefinition);
        uaf::SdkStatus setGenericValue(
                const uaf::ExtensionObject&     extensionObject,
                const uaf::StructureDefinition& structureDefinition);


        uaf::SdkStatus setField(const std::string& fieldName, const uaf::Variant& value);
        uaf::SdkStatus setField(int index, const uaf::Variant& value);

        uaf::SdkStatus setField(const std::string& sfieldName, const uaf::GenericStructureValue& value);
        uaf::SdkStatus setField(int index, const uaf::GenericStructureValue& value);

        uaf::SdkStatus setField(const std::string& sfieldName, const std::vector<uaf::GenericStructureValue>& array);
        uaf::SdkStatus setField(int index, const std::vector<uaf::GenericStructureValue>& array);

        uaf::Variant value(const std::string& fieldName) const;
        uaf::Variant value(int index) const;

        uaf::GenericStructureValue genericStructureValue(const std::string& fieldName) const;
        uaf::GenericStructureValue genericStructureValue(int index) const;

        std::vector<uaf::GenericStructureValue> genericStructureArray(const std::string& fieldName) const;
        std::vector<uaf::GenericStructureValue> genericStructureArray(int index) const;

        uaf::StructureDefinition definition() const;
        void setDefinition(const uaf::StructureDefinition& definition, bool createDefaultValues = false);

        bool isFieldSet(const std::string& name) const;
        bool isFieldSet(int index) const;

        uaf::SdkStatus unsetField(const std::string& sname);
        uaf::SdkStatus unsetField(int index);


        uaf::structurefielddatatypes::StructureFieldDataType valueType(int index, SdkStatus& status) const;
        uaf::structurefielddatatypes::StructureFieldDataType valueType(int index) const;


        void toExtensionObject(
        		uaf::ExtensionObject& extensionObject,
        		Encoding valueEncoding = GenericStructureValue::Encoding_Binary) const;


        /**
         * Get a string representation.
         *
         * @return The string representation.
         */
        std::string toString(const std::string& indent="", std::size_t colon=26) const;


        /**
         * Fill the instance from an SDK instance.
         */
        void fromSdk(const UaGenericStructureValue& uaGenericStructureValue) { uaGenericStructureValue_ = uaGenericStructureValue; }


        /**
         * Copy the instance to an SDK instance.
         */
        void toSdk(UaGenericStructureValue& uaGenericStructureValue) const { uaGenericStructureValue = uaGenericStructureValue_; };



    private:

        // the wrapped SDK variable
        UaGenericStructureValue uaGenericStructureValue_;

    };

}



#endif /* UAF_GENERICSTRUCTUREVALUE_H_ */
