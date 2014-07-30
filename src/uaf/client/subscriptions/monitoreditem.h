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

#ifndef UAFC_MONITOREDITEM_H_
#define UAFC_MONITOREDITEM_H_


// STD
#include <vector>
#include <string>
#include <sstream>
// SDK
// UAF
#include "uaf/util/status.h"
#include "uaf/util/nodeid.h"
#include "uaf/util/variant.h"
#include "uaf/util/logger.h"
#include "uaf/util/address.h"
#include "uaf/util/handles.h"
#include "uaf/client/clientexport.h"
#include "uaf/client/settings/monitoreditemsettings.h"
#include "uaf/client/database/database.h"

namespace uafc
{


    /*******************************************************************************************//**
    * A uafc::MonitoredItem represents the monitored item from the client side.
    *
    * A uafc::MonitoredItem exists within a uafc::Subscription.
    *
    * @ingroup ClientSubscriptions
    ***********************************************************************************************/
    struct UAFC_EXPORT MonitoredItem
    {
        /** The settings of the monitored item. */
        uafc::MonitoredItemSettings     settings;

        /** The request handle of the monitored item (i.e. the handle that identifies the request
         * that created this monitored item). */
        uaf::RequestHandle             requestHandle;

        /** The order number of the target of the request that was used to create this monitored
         * item. E.g. requestHandle=12 targetRank=0 means that the first target of the
         * CreateMonitoredDataRequest (or CreateMonitoredEventsRequest) with handle 12 resulted in
         * the creation of this monitored item. */
        std::size_t                    targetRank;

        /** MonitoredItemId that was assigned to the monitored item by the server. */
        uaf::MonitoredItemId monitoredItemId;

        /** The revised sampling interval of the monitored item, in seconds. */
        double revisedSamplingIntervalSec;

        /** The revised queue size on the server side. */
        uint32_t revisedQueueSize;
    };
}


#endif /* UAFC_MONITOREDITEMREQUEST_H_ */
