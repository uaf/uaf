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

#include "uaf/util/bytestring.h"

namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;


    // Constructor
    // =============================================================================================
    ByteString::ByteString()
    {}


    // Constructor
    // =============================================================================================
    ByteString::ByteString(int32_t length, uint8_t* data)
    {
        if (length > 0)
            uaByteString_ = UaByteString(length, data);
    }


    // Get a string representation
    // =============================================================================================
    string ByteString::toString() const
    {
        stringstream ss;
        if (uaByteString_.length() > 0)
            ss << length() << " bytes";
        else
            ss << "NULL";
        return ss.str();
    }


    // Convert a UaByteArray
    // =============================================================================================
    void ByteString::fromSdk(const UaByteArray& uaByteArray)
    {
        OpcUa_ByteString opcUaByteString;
        uaByteArray.copyTo(&opcUaByteString);
        uaByteString_.attach(&opcUaByteString); // uaByteString_ = opcUaByteString;
    }


    // Convert a UaByteArray
    // =============================================================================================
    void ByteString::toSdk(UaByteArray& uaByteArray) const
    {
        //uaByteArray = UaByteArray((char*) uaByteString_.data(), uaByteString_.length());
        OpcUa_ByteString opcUaByteString;
        uaByteString_.copyTo(&opcUaByteString);
        uaByteArray = opcUaByteString;
    }


    // Comparison operator ==
    // =============================================================================================
    bool operator==(const ByteString& object1, const ByteString& object2)
    {
        return object1.uaByteString_ == object2.uaByteString_;
    }


    // Comparison operator !=
    // =============================================================================================
    bool operator!=(const ByteString& object1, const ByteString& object2)
    {
        return object1.uaByteString_ != object2.uaByteString_;
    }


    // comparison operator <
    // =============================================================================================
    bool operator<(const ByteString& object1, const ByteString& object2)
    {
        return object1.uaByteString_ < object2.uaByteString_;
    }

}


