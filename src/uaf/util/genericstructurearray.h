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

#ifndef UAF_GENERICSTRUCTUREARRAY_H_
#define UAF_GENERICSTRUCTUREARRAY_H_


// STD
#include <string>
#include <sstream>
#include <stdint.h>

// SDK
// UAF
#include "uaf/util/genericstructurevalue.h"


namespace uaf
{


    /*******************************************************************************************//**
     * A GenericValue may represent a Structure or Enumeration.
     *
     * @ingroup Util
     **********************************************************************************************/
    class UAF_EXPORT GenericStructureArray
    {
    public:


        /**
         * Construct a GenericStructureArray with a NULL definition.
         */
        GenericStructureArray();


        /**
         * Construct a GenericStructureArray.
         */
        GenericStructureArray(const uaf::StructureDefinition& definition);


        /**
         * Clear the generic value.
         */
        void clear();

        /**
         * Create an array of the given length.
         */
        void create(uint32_t length);

        /**
         * Get the length of the array.
         */
        uint32_t length() const;

        /**
         * Get the definition of the structure.
         */
        uaf::StructureDefinition definition() const;

        /**
         * Get an array item.
         */
        uaf::GenericStructureValue __getitem__(uint32_t index) const;

        /**
         * Set an array item.
         */
        void __setitem__(uint32_t index, const uaf::GenericStructureValue& value);

        /**
         * Get a string representation.
         *
         * @return The string representation.
         */
        std::string toString(const std::string& indent="", std::size_t colon=26) const;


        /**
         * Fill the instance from an SDK instance.
         */
        void fromSdk(const UaGenericStructureArray& uaGenericStructureArray) { uaGenericStructureArray_ = uaGenericStructureArray; }


        /**
         * Copy the instance to an SDK instance.
         */
        void toSdk(UaGenericStructureArray& uaGenericStructureArray) const { uaGenericStructureArray = uaGenericStructureArray_; };


    private:

        // the wrapped SDK variable
        UaGenericStructureArray uaGenericStructureArray_;

    };

}



#endif /* UAF_GENERICSTRUCTUREARRAY_H_ */
