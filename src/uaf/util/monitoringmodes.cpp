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

#include "uaf/util/monitoringmodes.h"

namespace uaf
{
    using namespace uaf;

    namespace monitoringmodes
    {

        // Get a string representation
        // =========================================================================================
        std::string toString(monitoringmodes::MonitoringMode mode)
        {
            switch (mode)
            {
                case monitoringmodes::Disabled:    return "Disabled";
                case monitoringmodes::Sampling:    return "Sampling";
                case monitoringmodes::Reporting:   return "Reporting";
                default:                           return "UNKNOWN";
            }
        }


        // UAF to SDK mode
        // =========================================================================================
        OpcUa_MonitoringMode fromUafToSdk(monitoringmodes::MonitoringMode mode)
        {
            switch (mode)
            {
                case monitoringmodes::Disabled:    return OpcUa_MonitoringMode_Disabled;
                case monitoringmodes::Sampling:    return OpcUa_MonitoringMode_Sampling;
                case monitoringmodes::Reporting:   return OpcUa_MonitoringMode_Reporting;
                default:                           return OpcUa_MonitoringMode_Reporting;
            }
        }

        // SDK to UAF mode
        // =========================================================================================
        monitoringmodes::MonitoringMode fromSdkToUaf(OpcUa_MonitoringMode mode)
        {
            switch (mode)
            {
                case OpcUa_MonitoringMode_Disabled:     return monitoringmodes::Disabled;
                case OpcUa_MonitoringMode_Sampling:     return monitoringmodes::Sampling;
                case OpcUa_MonitoringMode_Reporting:    return monitoringmodes::Reporting;
                default:                                return monitoringmodes::Reporting;
            }
        }
    }
}
