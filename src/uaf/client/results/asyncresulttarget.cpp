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

#include "uaf/client/results/asyncresulttarget.h"


namespace uafc
{
    using namespace uaf;
    using namespace uafc;
    using std::string;
    using std::stringstream;
    using std::size_t;
    using std::vector;



    // Get a string representation
    // =============================================================================================
    string AsyncResultTarget::toString(const string& indent, size_t colon) const
    {
        stringstream ss;
        ss << "status: " << status.toString();
        return ss.str();
    }


    // operator==
    // =============================================================================================
    bool operator==(
            const AsyncResultTarget& object1,
            const AsyncResultTarget& object2)
    {
        return    object1.clientConnectionId == object2.clientConnectionId
               && object1.status             == object2.status;
    }


    // operator!=
    // =============================================================================================
    bool operator!=(
            const AsyncResultTarget& object1,
            const AsyncResultTarget& object2)
    {
        return !(object1 == object2);
    }


    // operator<
    // =============================================================================================
    bool operator<(
            const AsyncResultTarget& object1,
            const AsyncResultTarget& object2)
    {
        if (object1.clientConnectionId != object2.clientConnectionId)
            return object1.clientConnectionId < object2.clientConnectionId;
        else
            return object1.status < object2.status;
    }



}
