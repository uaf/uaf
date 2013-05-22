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

#include "uaf/util/timestampstoreturn.h"

namespace uaf
{
    using namespace uaf;
    using std::string;

    namespace timestampstoreturn
    {

        using namespace timestampstoreturn;


        // Get a string representation
        // =========================================================================================
        string toString(TimestampsToReturn timestamps)
        {
            switch (timestamps)
            {
                case Source:    return "Source";
                case Server:    return "Server";
                case Both:      return "Both";
                case Neither:   return "Neither";
                default:        return "UNKNOWN";
            }
        }


        // SDK to UAF mode
        // =========================================================================================
        TimestampsToReturn fromSdkToUaf(OpcUa_TimestampsToReturn timestamps)
        {
            switch (timestamps)
            {
                case OpcUa_TimestampsToReturn_Source:   return Source;
                case OpcUa_TimestampsToReturn_Server:   return Server;
                case OpcUa_TimestampsToReturn_Both:     return Both;
                case OpcUa_TimestampsToReturn_Neither:  return Neither;
                default:                                return Source;
            }
        }


        // UAF to SDK mode
        // =========================================================================================
        OpcUa_TimestampsToReturn fromUafToSdk(TimestampsToReturn timestamps)
        {
            switch (timestamps)
            {
                case Source:    return OpcUa_TimestampsToReturn_Source;
                case Server:    return OpcUa_TimestampsToReturn_Server;
                case Both:      return OpcUa_TimestampsToReturn_Both;
                case Neither:   return OpcUa_TimestampsToReturn_Neither;
                default:        return OpcUa_TimestampsToReturn_Source;
            }
        }

    }
}
