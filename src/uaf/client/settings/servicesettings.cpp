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

#include "uaf/client/settings/servicesettings.h"


namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;


    // Constructor
    // =============================================================================================
    ServiceSettings::ServiceSettings()
    {
        callTimeoutSec = 1.0; // 1 sec
    }


    // Get a string representation
    // =============================================================================================
    string ServiceSettings::toString(const string& indent, std::size_t colon) const
    {
        stringstream ss;

        ss << indent << " - callTimeoutSec";
        ss << fillToPos(ss, colon);
        ss << ": " << callTimeoutSec;

        return ss.str();
    }


    // Copy the contents to the SDK variable
    // =============================================================================================
    Status ServiceSettings::toSdk(UaClientSdk::ServiceSettings& uaServiceSettings) const
    {
        Status ret;

        uaServiceSettings.callTimeout = int32_t(callTimeoutSec * 1000);

        ret = statuscodes::Good;

        return ret;

    }


    // operator<
    // =============================================================================================
    bool operator<(const ServiceSettings& object1, const ServiceSettings& object2)
    {
        return int(object1.callTimeoutSec*1000) < int(object2.callTimeoutSec*1000);
    }


    // operator==
    // =============================================================================================
    bool operator==(const ServiceSettings& object1, const ServiceSettings& object2)
    {
        return (int(object1.callTimeoutSec*1000)  == int(object2.callTimeoutSec*1000));
    }


    // operator!=
    // =============================================================================================
    bool operator!=( const ServiceSettings& object1, const ServiceSettings& object2)
    {
        return !(object1 == object2);
    }

}
