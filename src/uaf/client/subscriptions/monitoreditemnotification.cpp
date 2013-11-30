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

#include "uaf/client/subscriptions/monitoreditemnotification.h"





namespace uafc
{
    using namespace uaf;
    using namespace uafc;
    using std::string;
    using std::stringstream;
    using std::vector;
    using std::size_t;



    // Constructor
    // =============================================================================================
    MonitoredItemNotification::MonitoredItemNotification()
    : notificationHandle(NOTIFICATIONHANDLE_NOT_ASSIGNED),
      clientHandle(0)
    {}


    // Get a string representation
    // =============================================================================================
    string MonitoredItemNotification::toString(const string& indent, size_t colon) const
    {
        stringstream ss;
        ss << indent << " - notificationHandle";
        ss << fillToPos(ss, colon);
        if (notificationHandle == NOTIFICATIONHANDLE_NOT_ASSIGNED)
            ss << ": NOTIFICATIONHANDLE_NOT_ASSIGNED\n";
        else
            ss << ": " << notificationHandle << "\n";
        ss << indent << " - clientHandle";
        ss << fillToPos(ss, colon);
        ss << ": " << clientHandle;
        return ss.str();
    }


}




