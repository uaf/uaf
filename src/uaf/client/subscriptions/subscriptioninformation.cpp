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

#include "uaf/client/subscriptions/subscriptioninformation.h"

namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;
    using std::size_t;


    // Constructor
    // =============================================================================================
    SubscriptionInformation::SubscriptionInformation()
    : clientConnectionId(0),
      clientSubscriptionHandle(0),
      subscriptionState(uaf::subscriptionstates::Deleted)
    {}


    // Constructor
    // =============================================================================================
    SubscriptionInformation::SubscriptionInformation(
            uaf::ClientConnectionId                     clientConnectionId,
            uaf::ClientSubscriptionHandle               clientSubscriptionHandle,
            uaf::subscriptionstates::SubscriptionState subscriptionState)
    : clientConnectionId(clientConnectionId),
      clientSubscriptionHandle(clientSubscriptionHandle),
      subscriptionState(subscriptionState)
    {}

    // Get a new client connection id
    // =============================================================================================
    string SubscriptionInformation::toString(const string& indent, size_t colon) const
    {
        stringstream ss;

        ss << indent << " - clientConnectionId";
        ss << fillToPos(ss, colon);
        ss << ": " << clientConnectionId << "\n";

        ss << indent << " - clientSubscriptionHandle";
        ss << fillToPos(ss, colon);
        ss << ": " << clientSubscriptionHandle << "\n";

        ss << indent << " - subscriptionState";
        ss << fillToPos(ss, colon);
        ss << ": " << subscriptionState
                << " (" << uaf::subscriptionstates::toString(subscriptionState) << ")";


        return ss.str();
    }


    // operator==
    // =============================================================================================
    bool operator==(const SubscriptionInformation& object1, const SubscriptionInformation& object2)
    {
        return    object1.clientConnectionId == object2.clientConnectionId
               && object1.clientSubscriptionHandle == object2.clientSubscriptionHandle
               && object1.subscriptionState == object2.subscriptionState;
    }


    // operator!=
    // =============================================================================================
    bool operator!=(const SubscriptionInformation& object1, const SubscriptionInformation& object2)
    {
        return !(object1 == object2);
    }


    // operator<
    // =============================================================================================
    bool operator<(const SubscriptionInformation& object1, const SubscriptionInformation& object2)
    {
        if (object1.clientConnectionId != object2.clientConnectionId)
            return object1.clientConnectionId < object2.clientConnectionId;
        else if (object1.clientSubscriptionHandle != object2.clientSubscriptionHandle)
            return object1.clientSubscriptionHandle < object2.clientSubscriptionHandle;
        else
            return object1.subscriptionState < object2.subscriptionState;
    }
}
