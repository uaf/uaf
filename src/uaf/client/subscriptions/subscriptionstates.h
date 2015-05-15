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

#ifndef UAF_SUBSCRIPTIONSTATE_H_
#define UAF_SUBSCRIPTIONSTATE_H_

// STD
#include <string>
#include <stdint.h>
// SDK
#include "uaclient/uaclientsdk.h"
// UAF
#include "uaf/util/util.h"

namespace uaf
{


    namespace subscriptionstates
    {

        /**
         * The state of the subscription.
         *
         * @ingroup ClientSubscriptions
         */
        enum SubscriptionState
        {
            Created = 0, /**< The subscription is established. */
            Deleted = 1, /**< The subscription is not established. */
        };


        /**
         * Get a string representation of the subscription state.
         *
         * @param state The subscription state (as an enum).
         * @return      The corresponding name of the subscription state.
         *
         * @ingroup ClientSubscriptions
         */
        std::string UAF_EXPORT toString(uaf::subscriptionstates::SubscriptionState state);


        /**
         * Convert a UAF state into an SDK UaStatus object.
         *
         * @param state The subscription state as defined by the UAF.
         * @return      The subscription state as defined by the SDK.
         *
         * @ingroup ClientSubscriptions
         */
        UaStatus UAF_EXPORT toSdk(uaf::subscriptionstates::SubscriptionState state);


        /**
         * Convert a SDK UaStatus into a UAF state.
         *
         * @param status    The subscription state as defined by the SDK.
         * @return          The subscription state as defined by the UAF.
         *
         * @ingroup ClientSubscriptions
         */
        uaf::subscriptionstates::SubscriptionState UAF_EXPORT toUaf(const UaStatus& status);
    }

}


#endif /* UAF_SUBSCRIPTIONSTATE_H_ */
