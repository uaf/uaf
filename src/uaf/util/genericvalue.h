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

#ifndef UAF_GENERICVALUE_H_
#define UAF_GENERICVALUE_H_


// STD
#include <string>
#include <sstream>
#include <stdint.h>

// SDK
#include "uabase/uagenericvalue.h"
// UAF
#include "uaf/util/util.h"
#include "uaf/util/localizedtext.h"
#include "uaf/util/nodeid.h"
#include "uaf/util/opcuatypes.h"
#include "uaf/util/stringifiable.h"


namespace uaf
{


    /*******************************************************************************************//**
     * A GenericValue may represent a Structure or Enumeration.
     *
     * @ingroup Util
     **********************************************************************************************/
    class UAF_EXPORT GenericValue
    {
    public:


        /**
         * This enum defines the encoding of the generic value.
         *
         * @ingroup Util
         */
        enum Encoding
        {
            Binary = OpcUa_ExtensionObjectEncoding_Binary,
            Xml    = OpcUa_ExtensionObjectEncoding_Xml
        };


        /**
         * Construct a GenericValue.
         */
        GenericValue();


        /**
         * Clear the generic value.
         */
        void clear();


        /**
         * Set a value.
         */
        uaf::Status setGenericValue(
                const uaf::ByteString&          data,
                Encoding                        encoding,
                const uaf::StructureDefinition& structureDefinition);

        uaf::Status setField(const std::string& sfieldName, const uaf::Variant& value);
        uaf::Status setField(int index, const uaf::Variant& value);

        uaf::Variant value(const std::string& fieldName) const;
        uaf::Variant value(int index) const;

        uaf::StructureDefinition definition() const;

        /**
         * Get a string representation.
         *
         * @return The string representation.
         */
        std::string toString(const std::string& indent="", std::size_t colon=17) const;


        /**
         * Fill the instance from an SDK instance.
         */
        void fromSdk(const GenericValue& uaStructureField) { uaStructureField_ = uaStructureField; }


        /**
         * Copy the instance to an SDK instance.
         */
        void toSdk(GenericValue& uaStructureField) const { uaStructureField = uaStructureField_; };

    private:

        // the wrapped SDK variable
        UaGenericValue uaStructureField_;

    };

}



#endif /* UAF_GENERICVALUE_H_ */
