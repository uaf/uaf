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

#include "uaf/client/subscriptions/monitorediteminformation.h"

namespace uafc
{
    using namespace uaf;
    using namespace uafc;
    using std::string;
    using std::stringstream;
    using std::size_t;


    // Constructor
    // =============================================================================================
    MonitoredItemInformation::MonitoredItemInformation()
    : monitoredItemState(uafc::monitoreditemstates::NotCreated),
      clientConnectionId(0),
      clientSubscriptionHandle(0),
      clientHandle(uaf::CLIENTHANDLE_NOT_ASSIGNED)
    {}


    // Constructor
    // =============================================================================================
    MonitoredItemInformation::MonitoredItemInformation(
            uafc::monitoreditemstates::MonitoredItemState   monitoredItemState,
            uaf::ClientConnectionId                         clientConnectionId,
            uaf::ClientSubscriptionHandle                   clientSubscriptionHandle,
            uaf::ClientHandle                               clientHandle,
            const MonitoredItemSettings&                    settings)
    : monitoredItemState(monitoredItemState),
      clientConnectionId(clientConnectionId),
      clientSubscriptionHandle(clientSubscriptionHandle),
      clientHandle(clientHandle),
      settings(settings)
    {}

    // Get a new client connection id
    // =============================================================================================
    string MonitoredItemInformation::toString(const string& indent, size_t colon) const
    {
        stringstream ss;

        ss << indent << " - monitoredItemState";
        ss << fillToPos(ss, colon);
        ss << ": " << uafc::monitoreditemstates::toString(monitoredItemState) << "\n";

        ss << indent << " - clientConnectionId";
        ss << fillToPos(ss, colon);
        ss << ": " << clientConnectionId << "\n";

        ss << indent << " - clientSubscriptionHandle";
        ss << fillToPos(ss, colon);
        ss << ": " << clientSubscriptionHandle << "\n";

        ss << indent << " - clientHandle";
        ss << fillToPos(ss, colon) << ": ";
        if (clientHandle == uaf::CLIENTHANDLE_NOT_ASSIGNED)
            ss << "0xFFFFFFFF (CLIENTHANDLE_NOT_ASSIGNED)\n";
        else
            ss << clientHandle << "\n";

        ss << indent << " - settings\n";
        ss << settings.toString(indent + "   ", colon);

        return ss.str();
    }


    // operator==
    // =============================================================================================
    bool operator==(
            const MonitoredItemInformation& object1,
            const MonitoredItemInformation& object2)
    {
        return    object1.clientConnectionId == object2.clientConnectionId
               && object1.clientSubscriptionHandle == object2.clientSubscriptionHandle
               && object1.clientHandle == object2.clientHandle
               && object1.settings == object2.settings;
    }


    // operator!=
    // =============================================================================================
    bool operator!=(
            const MonitoredItemInformation& object1,
            const MonitoredItemInformation& object2)
    {
        return !(object1 == object2);
    }


    // operator<
    // =============================================================================================
    bool operator<(
            const MonitoredItemInformation& object1,
            const MonitoredItemInformation& object2)
    {
        if (object1.clientConnectionId != object2.clientConnectionId)
            return object1.clientConnectionId < object2.clientConnectionId;
        else if (object1.clientSubscriptionHandle != object2.clientSubscriptionHandle)
            return object1.clientSubscriptionHandle < object2.clientSubscriptionHandle;
        else if (object1.clientHandle != object2.clientHandle)
            return object1.clientHandle < object2.clientHandle;
        else
            return object1.settings < object2.settings;
    }
}
