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

#ifndef UAFC_SUBSCRIPTIONSETTINGS_H_
#define UAFC_SUBSCRIPTIONSETTINGS_H_


// STD
#include <string>
#include <stdint.h>
#include <sstream>
// SDK
#include "uaclient/uaclientsdk.h"
// UAF
#include "uaf/util/stringifiable.h"
#include "uaf/client/clientexport.h"


namespace uafc
{


    /*******************************************************************************************//**
    * An uafc::SubscriptionSettings instance stores the settings of a uafc::Subscription.
    *
    * @ingroup ClientSettings
    ***********************************************************************************************/
    class UAFC_EXPORT SubscriptionSettings : public uaf::Stringifiable
    {
    public:


        /**
         * Construct default settings.
         *
         * Default values are:
         *   - unique                     = false
         *   - publishingIntervalSec      = 1.0
         *   - lifeTimeCount              = 1200
         *   - maxKeepAliveCount          = 5
         *   - maxNotificationsPerPublish = 0
         *   - priority                   = 0
         */
        SubscriptionSettings();


        /** Set this flag to true in order to force the UAF to create a new unique subscription
            (instead of allowing the UAF to re-use an existing one with the same settings). */
        bool unique;

        /** The publishing interval in seconds. */
        double publishingIntervalSec;

        /** The life time count. */
        uint32_t lifeTimeCount;

        /** The max keep alive count. */
        uint32_t maxKeepAliveCount;

        /** The max number of notifications per publish */
        uint32_t maxNotificationsPerPublish;

        /** The priority of the subscription. */
        uint8_t priority;

        /**
         * Get a string representation of the settings.
         *
         * @return  String representation.
         */
        std::string toString(const std::string& indent="", std::size_t colon=30) const;


        // comparison operators
        friend bool UAFC_EXPORT operator==(
                const SubscriptionSettings& object1,
                const SubscriptionSettings& object2);
        friend bool UAFC_EXPORT operator!=(
                const SubscriptionSettings& object1,
                const SubscriptionSettings& object2);
        friend bool UAFC_EXPORT operator<(
                const SubscriptionSettings& object1,
                const SubscriptionSettings& object2);


        /**
         * Convert the settings to an SDK object.
         *
         * @param settings  UAF subscription settings.
         * @return          SDK subscription settings.
         */
        friend UaClientSdk::SubscriptionSettings toSdk(const SubscriptionSettings& settings);

    };
}

#endif /* UAFC_SUBSCRIPTIONSETTINGS_H_ */
