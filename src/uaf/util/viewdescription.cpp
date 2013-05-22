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

#include "uaf/util/viewdescription.h"


namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::size_t;
    using std::stringstream;


    // Constructor
    // =============================================================================================
    ViewDescription::ViewDescription()
    {}


    // Get a string representation
    // =============================================================================================
    string ViewDescription::toString(const string& indent, size_t colon) const
    {
        stringstream ss;

        ss << indent << " - viewId";
        ss << fillToPos(ss, colon);
        ss << ": " << viewId.toString();

        return ss.str();
    }


    // operator<
    // =============================================================================================
    bool operator<(
            const ViewDescription& object1,
            const ViewDescription& object2)
    {
        return object1.viewId < object2.viewId;
    }


    // operator==
    // =============================================================================================
    bool operator==(
            const ViewDescription& object1,
            const ViewDescription& object2)
    {
        return   object1.viewId == object2.viewId;
    }


    // operator!=
    // =============================================================================================
    bool operator!=(
            const ViewDescription& object1,
            const ViewDescription& object2)
    {
        return !(object1 == object2);
    }
}

