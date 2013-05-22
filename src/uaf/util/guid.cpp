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

#include "uaf/util/guid.h"

namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;


    // Constructor
    // =============================================================================================
    Guid::Guid()
    {}


    // Constructor
    // =============================================================================================
    Guid::Guid(const string& s)
    {
        uaGuid_.fromString(UaString(s.c_str()));
    }



    // Comparison operator ==
    // =============================================================================================
    bool operator==(const Guid& object1, const Guid& object2)
    {
        return object1.uaGuid_ == object2.uaGuid_;
    }


    // Comparison operator !=
    // =============================================================================================
    bool operator!=(const Guid& object1, const Guid& object2)
    {
        return object1.uaGuid_ != object2.uaGuid_;
    }


    // comparison operator <
    // =============================================================================================
    bool operator<(const Guid& object1, const Guid& object2)
    {
        // we need to convert the GUID to strings in order to compare them
        return object1.uaGuid_.toString() < object2.uaGuid_.toString();
    }

}


