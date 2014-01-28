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

#ifndef UAFC_MONITOREDITEMSTATES_H_
#define UAFC_MONITOREDITEMSTATES_H_

// STD
#include <string>
#include <stdint.h>
// SDK
#include "uaclient/uaclientsdk.h"
// UAF
#include "uaf/client/clientexport.h"

namespace uafc
{


    namespace monitoreditemstates
    {

        /**
         * The state of the monitored item.
         *
         * @ingroup ClientSubscriptions
         */
        enum MonitoredItemState
        {
            Created    = 0, /**< The monitored item is created on the server. */
            NotCreated = 1, /**< The monitored item is NOT created on the server. */
        };


        /**
         * Get a string representation of the monitored item state.
         *
         * @param state The monitored item state (as an enum).
         * @return      The corresponding name of the monitored item state.
         *
         * @ingroup ClientSubscriptions
         */
        std::string UAFC_EXPORT toString(uafc::monitoreditemstates::MonitoredItemState state);
    }

}


#endif /* UAFC_MONITOREDITEMSTATES_H_ */
