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

#ifndef UAFC_BASENOTIFICATION_H_
#define UAFC_BASENOTIFICATION_H_


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
#include "uaf/client/clientexport.h"
#include "uaf/client/clienthandles.h"


namespace uafc
{


    /*******************************************************************************************//**
    * A uafc::BaseNotification is the common superclass class of uafc::DataChangeNotification and
    * uafc::EventNotification. It contains the common attributes of notifications that are received
    * when a subscription is made.
    *
    * @ingroup ClientSubscriptions
    ***********************************************************************************************/
    class UAFC_EXPORT BaseNotification : public uaf::Stringifiable
    {
    public:

        /**
         * Construct a notification.
         */
        BaseNotification();

        /**
         * A NotificationHandle is a handle defined by the UAF (not by the OPC UA standard!) to
         * associate monitored item notifications with the CreateMonitoredDataRequestTarget (or
         * CreateMonitoredEventsRequestTarget) that originally created them. It is a 64-bit number
         * that gets a unique value as soon as you create a monitored item. Even if the server of
         * this monitored item would crash, and the UAF determines that the monitored item should be
         * re-established on another server (e.g. because the browse path now points to a node in
         * another redundant server), then this value will not change. So if you create monitored
         * items once, you can be sure that the notification handle will always correctly identify
         * the same item, for the whole lifetime of the client.
         */
        uafc::NotificationHandle notificationHandle;

        /**
         * A clientHandle is a 32-bit number assigned by the UAF to newly created
         * monitored items. The number will be incremented on each new item creation, so in
         * theory it will take 2**32 items that have to be created before the number starts
         * to count from 0 again. In practice, it will never happen.
         */
        uafc::ClientMonitoredItemHandle clientHandle;

        /**
         * Get a string representation of the notification.
         */
        virtual std::string toString(const std::string& indent="", std::size_t colon=20) const;
    };


}




#endif /* UAFC_BASENOTIFICATION_H_ */
