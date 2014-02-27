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

#ifndef UAFC_SUBSCRIPTIONCONFIG_H_
#define UAFC_SUBSCRIPTIONCONFIG_H_



// STD
#include <string>
#include <sstream>
// SDK
// UAF
#include "uaf/util/status.h"
#include "uaf/util/stringifiable.h"
#include "uaf/client/clientexport.h"
#include "uaf/client/settings/subscriptionsettings.h"


namespace uafc
{

    /*******************************************************************************************//**
    * A SubscriptionConfig instance can be used to configure one or more Subscriptions that need
    * to be created, e.g. in order to successfully create some MonitoredItems.
    *
    * See the SubscriptionConfigs example in the examples/ directory for more info.
    *
    * @ingroup ClientConfigs
    ***********************************************************************************************/
    class UAFC_EXPORT SubscriptionConfig
    {
    public:


        /**
         * Construct a new subscription config.
         */
        SubscriptionConfig()
        {}


        /**
         * Construct a new subscription config with the given default subscription settings.
         */
        SubscriptionConfig(const uafc::SubscriptionSettings& defaultSubscriptionSettings)
        : defaultSubscriptionSettings(defaultSubscriptionSettings)
        {}


        /** The default subscription settings. */
        uafc::SubscriptionSettings defaultSubscriptionSettings;

        /** The subscription settings per server URI. */
        std::map<std::string, uafc::SubscriptionSettings> specificSubscriptionSettings;


        /**
         * Get a string representation.
         */
        std::string toString(const std::string& indent="", std::size_t colon=33) const;

    private:

        // define the map that will store the settings for specific servers
        typedef std::map<std::string, uafc::SubscriptionSettings> SpecificsMap;

    };

}


#endif /* UAFC_SUBSCRIPTIONCONFIG_H_ */
