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

#include "uaf/client/settings/sessionsettings.h"


namespace uafc
{
    using namespace uaf;
    using namespace uafc;
    using std::string;
    using std::stringstream;
    using std::size_t;


    // Constructor
    // =============================================================================================
    SessionSettings::SessionSettings()
    {
        sessionTimeoutSec          = 1200.0; // 1200 sec
        connectTimeoutSec          = 2.0;
        watchdogTimeoutSec         = 2.0;
        watchdogTimeSec            = 5.0;
        securitySettingsList.resize(1);

    }

    // Get a string representation
    // =============================================================================================
    string SessionSettings::toString(const string& indent, size_t colon) const
    {
        stringstream ss;

        ss << indent << " - sessionTimeoutSec";
        ss << fillToPos(ss, colon);
        ss << ": " << sessionTimeoutSec << "\n";
        ss << indent << " - connectTimeoutSec";
        ss << fillToPos(ss, colon);
        ss << ": " << connectTimeoutSec << "\n";
        ss << indent << " - watchdogTimeoutSec";
        ss << fillToPos(ss, colon);
        ss << ": " << watchdogTimeoutSec << "\n";
        ss << indent << " - watchdogTimeSec";
        ss << fillToPos(ss, colon);
        ss << ": " << watchdogTimeSec;

        return ss.str();
    }


    // operator<
    // =============================================================================================
    bool operator<(
            const SessionSettings& object1,
            const SessionSettings& object2)
    {
        if (int(object1.sessionTimeoutSec*1000) != int(object2.sessionTimeoutSec*1000))
            return int(object1.sessionTimeoutSec*1000) < int(object2.sessionTimeoutSec*1000);
        else if (int(object1.connectTimeoutSec*1000) != int(object2.connectTimeoutSec*1000))
            return int(object1.connectTimeoutSec*1000) < int(object2.connectTimeoutSec*1000);
        else if (int(object1.watchdogTimeoutSec*1000) != int(object2.watchdogTimeoutSec*1000))
            return int(object1.watchdogTimeoutSec*1000) < int(object2.watchdogTimeoutSec*1000);
        else if (int(object1.watchdogTimeSec*1000) != int(object2.watchdogTimeSec*1000))
            return int(object1.watchdogTimeSec*1000) < int(object2.watchdogTimeSec*1000);
        else
            return false;
    }


    // operator==
    // =============================================================================================
    bool operator==(
            const SessionSettings& object1,
            const SessionSettings& object2)
    {
        return ( (int(object1.sessionTimeoutSec*1000)  == int(object2.sessionTimeoutSec*1000))
           &&    (int(object1.connectTimeoutSec*1000)  == int(object2.connectTimeoutSec*1000))
           &&    (int(object1.watchdogTimeoutSec*1000) == int(object2.watchdogTimeoutSec*1000))
           &&    (int(object1.watchdogTimeSec*1000)    == int(object2.watchdogTimeSec*1000)));
    }


    // operator!=
    // =============================================================================================
    bool operator!=(
            const SessionSettings& object1,
            const SessionSettings& object2)
    {
        return !(object1 == object2);
    }

}
