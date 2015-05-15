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

#ifndef UAF_KEEPALIVENOTIFICATION_H_
#define UAF_KEEPALIVENOTIFICATION_H_


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
#include "uaf/util/handles.h"
#include "uaf/client/subscriptions/subscriptioninformation.h"


namespace uaf
{

    /*******************************************************************************************//**
    * A uaf::KeepAliveNotification is the notification that a subscription is still alive.
    *
    * @ingroup ClientSubscriptions
    ***********************************************************************************************/
    class UAF_EXPORT KeepAliveNotification : public uaf::SubscriptionInformation
    {
    public:

        typedef std::vector<uaf::ClientHandle> ClientHandles;


        /**
         * Construct a keep alive notification.
         */
        KeepAliveNotification();


        /** The clientMonitoredItem handles of the monitored items that are owned by the
         * subscription that got a keep alive message. */
        ClientHandles clientHandles;


        /**
         * Get a string representation of the notification.
         */
        std::string toString(const std::string& indent="", std::size_t colon=18) const;
    };



}




#endif /* UAF_KEEPALIVENOTIFICATION_H_ */
