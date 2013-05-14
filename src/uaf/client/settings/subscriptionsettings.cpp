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

#include "uaf/client/settings/subscriptionsettings.h"


namespace uafc
{
    using namespace uaf;
    using namespace uafc;
    using std::string;
    using std::stringstream;
    using std::size_t;


    // Constructor
    // =============================================================================================
    SubscriptionSettings::SubscriptionSettings()
    {
        exclusive                  = false;
        publishingIntervalSec      = 1.0;
        lifeTimeCount              = 1200;
        maxKeepAliveCount          = 5;
        maxNotificationsPerPublish = 0;
        priority                   = 0;

    }


    // Get a string representation
    // =============================================================================================
    string SubscriptionSettings::toString(const string& indent, size_t colon) const
    {
        stringstream ss;

        ss << indent << " - exclusive";
        ss << fillToPos(ss, colon);
        ss << ": " << (exclusive ? string("true") : string("false")) << "\n";

        ss << indent << " - publishingIntervalSec";
        ss << fillToPos(ss, colon);
        ss << ": " << publishingIntervalSec << "\n";

        ss << indent << " - lifeTimeCount";
        ss << fillToPos(ss, colon);
        ss << ": " << lifeTimeCount << "\n";

        ss << indent << " - maxKeepAliveCount";
        ss << fillToPos(ss, colon);
        ss << ": " << maxKeepAliveCount << "\n";

        ss << indent << " - maxNotificationsPerPublish";
        ss << fillToPos(ss, colon);

        ss << ": " << maxNotificationsPerPublish << "\n";

        ss << indent << " - priority";
        ss << fillToPos(ss, colon);
        ss << ": " << int(priority);

        return ss.str();
    }


    // Convert to SDK object
    // =============================================================================================
    UaClientSdk::SubscriptionSettings toSdk(
                    const SubscriptionSettings& settings)
    {
        UaClientSdk::SubscriptionSettings uaSettings;

        uaSettings.publishingInterval           = settings.publishingIntervalSec * 1000.0;
        uaSettings.lifetimeCount                = settings.lifeTimeCount;
        uaSettings.maxKeepAliveCount            = settings.maxKeepAliveCount;
        uaSettings.maxNotificationsPerPublish   = settings.maxNotificationsPerPublish;
        uaSettings.priority                     = settings.priority;

        return uaSettings;
    }


    // operator==
    // =============================================================================================
    bool operator==(
            const SubscriptionSettings& object1,
            const SubscriptionSettings& object2)
    {
        return ( (int(object1.publishingIntervalSec*1000)
                  == int(object2.publishingIntervalSec*1000))
              && (object1.exclusive == object2.exclusive)
              && (object1.lifeTimeCount == object2.lifeTimeCount)
              && (object1.maxKeepAliveCount == object2.maxKeepAliveCount)
              && (object1.maxNotificationsPerPublish == object2.maxNotificationsPerPublish)
              && (object1.priority == object2.priority));
    }


    // operator!=
    // =============================================================================================
    bool operator!=(
            const SubscriptionSettings& object1,
            const SubscriptionSettings& object2)
    {
        return !(object1 == object2);
    }


    // operator<
    // =============================================================================================
    bool operator<(
            const SubscriptionSettings& object1,
            const SubscriptionSettings& object2)
    {
        if (object1.exclusive != object2.exclusive)
            return object1.exclusive < object2.exclusive;
        else if (int(object1.publishingIntervalSec*1000) != int(object2.publishingIntervalSec*1000))
            return int(object1.publishingIntervalSec*1000) < int(object2.publishingIntervalSec*1000);
        else if (object1.lifeTimeCount != object2.lifeTimeCount)
            return object1.lifeTimeCount < object2.lifeTimeCount;
        else if (object1.maxKeepAliveCount != object2.maxKeepAliveCount)
            return object1.maxKeepAliveCount < object2.maxKeepAliveCount;
        else if (object1.maxNotificationsPerPublish != object2.maxNotificationsPerPublish)
            return object1.maxKeepAliveCount < object2.maxKeepAliveCount;
        else if (object1.priority != object2.priority)
            return object1.priority < object2.priority;
        else
            return false;
    }


}
