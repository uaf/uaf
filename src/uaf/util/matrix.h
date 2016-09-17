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

#ifndef UAF_MATRIX_H_
#define UAF_MATRIX_H_

// STD
#include <string>
#include <sstream>
// UAF
#include "uaf/util/variant.h"
// SDK


namespace uaf
{



    /*******************************************************************************************//**
    * A uaf::Matrix is a wrapper for a Variant of the OpcUa_VariantArrayType_Matrix type.
    *
    * @ingroup Util
    ***********************************************************************************************/
    class UAF_EXPORT Matrix
    {
    public:

        /**
         * Construct an empty Matrix.
         */
        Matrix();


        /**
         * Remove any information about this address.
         */
        void clear();


        /**
         * Check if the status of the matrix is OK (e.g. if the number of elements match the dimensions)
         */
        uaf::SdkStatus status() const;


        /** The OPC UA type of the variant. */
        uaf::opcuatypes::OpcUaType type;

        /** The elements of the matrix. */
        std::vector<uaf::Variant> elements;

        /** The dimensions of the matrix. */
        std::vector<int32_t> dimensions;


        /**
         * Set a matrix element.
         *
         * @param dimensionNumbers E.g. [1,1,1]
         * @param value The value to be changed.
         */
        void setElement(std::vector<int32_t> dimensionNumbers, const uaf::Variant& value);


        /**
         * Get a matrix element.
         *
         * @param dimensionNumbers E.g. [1,1,1]
         * @return value .
         */
        uaf::Variant getElement(std::vector<int32_t> dimensionNumbers) const;


        /**
         * Get a string representation.
         *
         * @return String representation.
         */
        std::string toString(const std::string& indent="", std::size_t colon=20) const;


        /**
         * Convert a SDK UaVariant to this matrix.
         */
        void fromSdk(const UaVariant& uaVariant);


        /**
         * Convert this matrix to a SDK UaVariant.
         */
        void toSdk(UaVariant& uaVariant);


        /**
         * Get the element number (e.g. 1) for given dimension numbers (e.g. [0,0,1]).
         */
        int32_t getElementNumber(std::vector<int32_t> dimensionNumbers) const;


    private:

        // an internal status code
        uint32_t opcUaStatusCode_;

        // the internal UaVariant object
        UaVariant uaVariant_;

    };



}


#endif /* UAF_MATRIX_H_ */
