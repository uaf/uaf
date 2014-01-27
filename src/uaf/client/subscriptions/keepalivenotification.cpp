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

#include "uaf/client/subscriptions/keepalivenotification.h"





namespace uafc
{
    using namespace uaf;
    using namespace uafc;
    using std::string;
    using std::stringstream;
    using std::vector;


    // Constructor
    // =============================================================================================
    KeepAliveNotification::KeepAliveNotification()
    : SubscriptionInformation()
    {}


    // Get a string representation
    // =============================================================================================
    string KeepAliveNotification::toString(const string& indent, size_t colon) const
    {
        stringstream ss;

        ss << SubscriptionInformation::toString(indent, colon) << "\n";

        ss << indent << " - clientHandles";
        ss << fillToPos(ss, colon);
        ss << ": [";
        for(size_t i = 0; i < clientHandles.size(); i++)
        {
            ss << clientHandles[i];
            // add a comma unless we're printing the last handle
            if (i != clientHandles.size() - 1)
                ss << ",";
        }
        ss << "]";

        return ss.str();
    }

}




