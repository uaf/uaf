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

#ifndef UAF_MONITORINGMODES_H_
#define UAF_MONITORINGMODES_H_

// STD
#include <string>
// SDK
#include "uabasecpp/uaplatformlayer.h"
// UAF
#include "uaf/util/util.h"

namespace uaf
{

    namespace monitoringmodes
    {

        /**
         * The monitoring mode.
         *
         * @ingroup Util
         */
        enum MonitoringMode
        {
            Disabled    = 0,    /**< The data source is not monitored. */
            Sampling    = 1,    /**< The data source is being sampled, but not reported. */
            Reporting   = 2,    /**< The data source is being sampled and reported. */
        };



        /**
         * Get a string representation of the monitoring mode.
         *
         * @param mode  The monitoring mode (as an enum).
         * @return      The corresponding name of the monitoring mode.
         *
         * @ingroup Util
         */
        std::string UAF_EXPORT toString(uaf::monitoringmodes::MonitoringMode mode);


        /**
         * Convert the SDK/Stack instance to a UAF instance.
         *
         * @ingroup Util
         */
        MonitoringMode UAF_EXPORT fromSdkToUaf(OpcUa_MonitoringMode mode);


        /**
         * Convert the UAF instance to a SDK/Stack instance.
         *
         * @ingroup Util
         */
        OpcUa_MonitoringMode UAF_EXPORT fromUafToSdk(MonitoringMode mode);


    }
}


#endif /* UAF_MONITORINGMODES_H_ */
