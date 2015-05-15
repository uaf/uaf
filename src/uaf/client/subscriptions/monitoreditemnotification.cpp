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





namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;
    using std::vector;
    using std::size_t;



    // Constructor
    // =============================================================================================
    MonitoredItemNotification::MonitoredItemNotification()
    : clientHandle(CLIENTHANDLE_NOT_ASSIGNED)
    {}


    // Get a string representation
    // =============================================================================================
    string MonitoredItemNotification::toString(const string& indent, size_t colon) const
    {
        stringstream ss;
        ss << indent << " - clientHandle";
        ss << fillToPos(ss, colon);
        if (clientHandle == CLIENTHANDLE_NOT_ASSIGNED)
            ss << ": 0xFFFFFFFF (CLIENTHANDLE_NOT_ASSIGNED)";
        else
            ss << ": " << clientHandle;

        return ss.str();
    }


    // operator==
    // =============================================================================================
    bool operator==(
            const MonitoredItemNotification& object1,
            const MonitoredItemNotification& object2)
    {
        return object1.clientHandle == object2.clientHandle;
    }


    // operator!=
    // =============================================================================================
    bool operator!=(
            const MonitoredItemNotification& object1,
            const MonitoredItemNotification& object2)
    {
        return !(object1 == object2);
    }


    // operator<
    // =============================================================================================
    bool operator<(
            const MonitoredItemNotification& object1,
            const MonitoredItemNotification& object2)
    {
        return object1.clientHandle < object2.clientHandle;
    }



}




