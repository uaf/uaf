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

#include "uaf/util/eventfilter.h"


namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::size_t;
    using std::stringstream;


    // Constructor
    // =============================================================================================
    EventFilter::EventFilter()
    {}


    // Get a string representation
    // =============================================================================================
    string EventFilter::toString(const string& indent, size_t colon) const
    {
        stringstream ss;

        ss << indent << " - selectClauses[]";

        if (selectClauses.size() == 0)
        {
            fillToPos(ss, colon);
            ss << ": []\n";
        }
        else
        {
            for (size_t i = 0; i<selectClauses.size(); i++)
            {
                ss << "\n";
                ss << indent << "    - " << "selectClauses[" << i << "]\n";
                ss << selectClauses[i].toString(indent + "      ", colon);
            }
        }

        return ss.str();
    }


    // operator<
    // =============================================================================================
    bool operator<(const EventFilter& object1, const EventFilter& object2)
    {
        return object1.selectClauses < object2.selectClauses;
    }


    // operator==
    // =============================================================================================
    bool operator==(const EventFilter& object1, const EventFilter& object2)
    {
        return (object1.selectClauses == object2.selectClauses);
    }


    // operator!=
    // =============================================================================================
    bool operator!=(const EventFilter& object1, const EventFilter& object2)
    {
        return !(object1 == object2);
    }
}

