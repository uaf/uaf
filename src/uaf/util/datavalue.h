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

#ifndef UAF_DATAVALUE_H_
#define UAF_DATAVALUE_H_


// STD
#include <vector>
#include <string>
#include <sstream>
#include <stdint.h>
// SDK
#include "uabase/uadatavalue.h"
// UAF
#include "uaf/util/util.h"
#include "uaf/util/variant.h"
#include "uaf/util/statuscodes.h"
#include "uaf/util/datetime.h"
#include "uaf/util/stringifiable.h"


namespace uaf
{


    /*******************************************************************************************//**
     * A DataValue holds some data value, a status, timestamps, ...
     *
     * @ingroup Util
     **********************************************************************************************/
    class UAF_EXPORT DataValue
    {
    public:


        /**
         * Construct a Good NULL DataValue.
         */
        DataValue();


        /**
         * Construct a Good DataValue from the given data.
         *
         * @param data  The data.
         */
        DataValue(const uaf::Variant& data);


        /**
         * Construct a DataValue from the given data and status.
         *
         * @param data  The data.
         */
        DataValue(const uaf::Variant& data, const uaf::Status& status);


        /** The data. */
        uaf::Variant data;

        /** The status of the data. */
        uaf::Status status;

        /** The source timestamp. */
        uaf::DateTime sourceTimestamp;

        /** The server timestamp. */
        uaf::DateTime serverTimestamp;

        /** The number of 10 picosecond intervals that need to be added to the source timestamp
         *  (to get a higher time resolution). */
        uint16_t sourcePicoseconds;

        /** The number of 10 picosecond intervals that need to be added to the server timestamp
         *  (to get a higher time resolution). */
        uint16_t serverPicoseconds;

        /**
         * Get a string representation.
         */
        std::string toString(const std::string& indent="", std::size_t colon=21) const;

        /**
         * Get a compact string representation.
         *
         * @return The string representation as a single line.
         */
        std::string toCompactString() const;


        /**
         * Get the contents of the DataValue from a SDK UaDataValue instance.
         *
         * @param uaDataValue  SDK UaDataValue instance.
         */
        void fromSdk(const UaDataValue& uaDataValue);


        /**
         * Copy the contents to an SDK instance.
         *
         * @param uaDataValue  SDK UaDataValue instance.
         */
        void toSdk(UaDataValue& uaDataValue) const;


        /**
         * Copy the contents to a stack OpcUa_DataValue instance.
         *
         * @param dest  Destination stack OpcUa_DataValue instance.
         */
        void toSdk(OpcUa_DataValue* dest) const;


        // comparison operators
        friend UAF_EXPORT bool operator==(const DataValue& object1, const DataValue& object2);
        friend UAF_EXPORT bool operator!=(const DataValue& object1, const DataValue& object2);
        friend UAF_EXPORT bool operator< (const DataValue& object1, const DataValue& object2);


    };

}



#endif /* UAF_DATAVALUE_H_ */
