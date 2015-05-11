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

#ifndef UAF_MONITOREDITEMNOTIFICATION_H_
#define UAF_MONITOREDITEMNOTIFICATION_H_


// STD
#include <vector>
#include <string>
#include <sstream>
// SDK
// UAF
#include "uaf/util/status.h"
#include "uaf/util/variant.h"
#include "uaf/util/logger.h"
#include "uaf/util/address.h"
#include "uaf/util/stringifiable.h"
#include "uaf/util/handles.h"
#include "uaf/client/clientexport.h"


namespace uaf
{


    /*******************************************************************************************//**
    * A uaf::MonitoredItemNotification is the common superclass class of
    * uaf::DataChangeNotification and uaf::EventNotification.
    *
    * @ingroup ClientSubscriptions
    ***********************************************************************************************/
    class UAF_EXPORT MonitoredItemNotification
    {
    public:

        /**
         * Construct a notification.
         */
        MonitoredItemNotification();

        /**
         * A clientHandle (or sometimes called ClientHandle) is a 32-bit number
         * assigned by the UAF to newly created monitored items.
         */
        uaf::ClientHandle clientHandle;

        /**
         * Get a string representation of the notification.
         */
        std::string toString(const std::string& indent="", std::size_t colon=20) const;


        // comparison operators
        friend UAF_EXPORT bool operator==(
                const MonitoredItemNotification& object1,
                const MonitoredItemNotification& object2);
        friend UAF_EXPORT bool operator!=(
                const MonitoredItemNotification& object1,
                const MonitoredItemNotification& object2);
        friend UAF_EXPORT bool operator<(
                const MonitoredItemNotification& object1,
                const MonitoredItemNotification& object2);
    };


}




#endif /* UAF_MONITOREDITEMNOTIFICATION_H_ */
