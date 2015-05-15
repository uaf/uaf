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

#ifndef UAF_BYTESTRING_H_
#define UAF_BYTESTRING_H_


// STD
#include <vector>
#include <string>
#include <sstream>
#include <stdint.h>
// SDK
#include "uabase/uabytestring.h"
#include "uabase/uabytearray.h"
// UAF
#include "uaf/util/util.h"


namespace uaf
{


    /*******************************************************************************************//**
     * A ByteString holds some raw data.
     *
     * Unlike the SDK UaByteString, length() will be 0 for a NULL ByteString!!!
     *
     * @ingroup Util
     **********************************************************************************************/
    class UAF_EXPORT ByteString
    {
    public:


        /**
         * Construct an empty ByteString.
         */
        ByteString();


        /**
         * Construct a ByteString with the specified length and the given data.
         *
         * @param length    Number of bytes.
         * @param data      Pointer to the bytes.
         */
        ByteString(int32_t length, uint8_t* data);


        /**
         * Check if the bytestring is NULL.
         *
         * An empty (NULL) ByteString has 0 length!
         */
        bool isNull() const { return uaByteString_.length() <= 0; }


        /**
         * Get the length of the byte string (i.e. the number of bytes).
         *
         * An empty (NULL) ByteString has 0 length!
         */
        int32_t length() const { return (uaByteString_.length() <= 0 ? 0 : uaByteString_.length()); }


        /**
         * Get a pointer to the bytes.
         */
        const uint8_t* data() const { return uaByteString_.data(); }


        /**
         * Get a string representation.
         */
        std::string toString() const;


        /**
         * Get the contents of the ByteString from a SDK UaByteString instance.
         *
         * @param uaByteString  SDK UaByteString instance.
         */
        void fromSdk(const UaByteString& uaByteString) { uaByteString_ = uaByteString; }


        /**
         * Get the contents of the ByteString from a SDK UaByteArray instance.
         *
         * @param uaByteArray  SDK UaByteArray instance.
         */
        void fromSdk(const UaByteArray& uaByteArray);


        /**
         * Copy the contents to an SDK instance.
         *
         * @param uaByteString  SDK UaByteString instance.
         */
        void toSdk(UaByteString& uaByteString) const { uaByteString = uaByteString_; };


        /**
         * Copy the contents to a stack OpcUa_ByteString instance.
         *
         * @param dest  Destination stack OpcUa_ByteString instance.
         */
        void toSdk(OpcUa_ByteString* dest) const { uaByteString_.copyTo(dest); };


        /**
         * Copy the contents to an SDK UaByteArray instance.
         *
         * @param uaByteArray  SDK UaByteString instance.
         */
        void toSdk(UaByteArray& uaByteArray) const;


        // comparison operators
        friend UAF_EXPORT bool operator==(const ByteString& object1, const ByteString& object2);
        friend UAF_EXPORT bool operator!=(const ByteString& object1, const ByteString& object2);
        friend UAF_EXPORT bool operator< (const ByteString& object1, const ByteString& object2);


    private:

        // the wrapped SDK variable
        UaByteString uaByteString_;

    };

}



#endif /* UAF_BYTESTRING_H_ */
