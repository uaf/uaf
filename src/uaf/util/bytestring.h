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
#include <stdint.h>
// SDK
#include "uabase/uabytestring.h"
// UAF
#include "uaf/util/util.h"


namespace uaf
{


    /*******************************************************************************************//**
     * A ByteString holds some raw data.
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
         * Get the length of the byte string (i.e. the number of bytes).
         */
        int32_t length() const { return uaByteString_.length(); }


        /**
         * Get a pointer to the bytes.
         */
        const uint8_t* data() const { return uaByteString_.data(); }


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
