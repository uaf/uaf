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

#ifndef UAFC_SUBSCRIPTIONINFORMATION_H_
#define UAFC_SUBSCRIPTIONINFORMATION_H_

// STD
#include <string>
#include <sstream>
// SDK
#include "uaclient/uaclientsdk.h"
// UAF
#include "uaf/util/stringifiable.h"
#include "uaf/util/handles.h"
#include "uaf/client/clientexport.h"
#include "uaf/client/subscriptions/subscriptionstates.h"

namespace uafc
{


    /*******************************************************************************************//**
    * Information about a subscription such as the state of the subscription, the handle, etc.
    *
    * @ingroup ClientSubscriptions
    ***********************************************************************************************/
    class UAFC_EXPORT SubscriptionInformation
    {
    public:


        /**
         * Create a default SubscriptionInformation object.
         */
        SubscriptionInformation();


        /**
         * Create a SubscriptionInformation object with the given information.
         *
         * @param clientConnectionId        The id of the session that hosts the subscription.
         * @param clientSubscriptionHandle  The handle of the subscription.
         * @param subscriptionState         The state of the subscription.
         */
        SubscriptionInformation(
                uaf::ClientConnectionId                     clientConnectionId,
                uaf::ClientSubscriptionHandle               clientSubscriptionHandle,
                uafc::subscriptionstates::SubscriptionState subscriptionState);


        /** The id of the session that hosts the subscription. */
        uaf::ClientConnectionId                     clientConnectionId;

        /** The handle of the subscription. */
        uaf::ClientSubscriptionHandle               clientSubscriptionHandle;

        /** The state of the subscription. */
        uafc::subscriptionstates::SubscriptionState subscriptionState;


        /**
         * Get a string representation of the information.
         */
        std::string toString(const std::string& indent="", std::size_t colon=22) const;


        // comparison operators
        friend UAFC_EXPORT bool operator==(
                const SubscriptionInformation& object1,
                const SubscriptionInformation& object2);
        friend UAFC_EXPORT bool operator!=(
                const SubscriptionInformation& object1,
                const SubscriptionInformation& object2);
        friend UAFC_EXPORT bool operator<(
                const SubscriptionInformation& object1,
                const SubscriptionInformation& object2);
    };


}


#endif /* UAFC_SUBSCRIPTIONINFORMATION_H_ */
