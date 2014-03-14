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

#include "uaf/client/results/createmonitoreddataresulttarget.h"


namespace uafc
{
    using namespace uaf;
    using namespace uafc;
    using std::string;
    using std::stringstream;
    using std::vector;


    // Get a string representation
    // =============================================================================================
    string CreateMonitoredDataResultTarget::toString(const string& indent, size_t colon) const
    {
        stringstream ss;

        ss << indent <<  " - clientConnectionId";
        ss << fillToPos(ss, colon);
        ss << ": " << clientConnectionId << "\n";

        ss << indent <<  " - clientSubscriptionHandle";
        ss << fillToPos(ss, colon);
        ss << ": " << clientSubscriptionHandle << "\n";

        ss << indent <<  " - clientHandle";
        ss << fillToPos(ss, colon);
        ss << ": " << clientHandle << "\n";

        ss << indent << " - status";
        ss << fillToPos(ss, colon);
        ss << ": " << status.toString() << "\n";

        ss << indent << " - monitoredItemId";
        ss << fillToPos(ss, colon);
        ss << ": "<< int(monitoredItemId) << "\n";

        ss << indent << " - revisedSamplingIntervalSec";
        ss << fillToPos(ss, colon);
        ss << ": "<< revisedSamplingIntervalSec << "\n";

        ss << indent << " - revisedQueueSize";
        ss << fillToPos(ss, colon);
        ss << ": "<< int(revisedQueueSize);
        return ss.str();
    }


    // operator==
    // =============================================================================================
    bool operator==(
            const CreateMonitoredDataResultTarget& object1,
            const CreateMonitoredDataResultTarget& object2)
    {
        return    object1.clientConnectionId == object2.clientConnectionId
               && object1.clientSubscriptionHandle == object2.clientSubscriptionHandle
               && object1.clientHandle == object2.clientHandle
               && object1.status == object2.status
               && object1.monitoredItemId == object2.monitoredItemId
               && object1.revisedSamplingIntervalSec == object2.revisedSamplingIntervalSec
               && object1.revisedQueueSize == object2.revisedQueueSize;
    }


    // operator!=
    // =============================================================================================
    bool operator!=(
            const CreateMonitoredDataResultTarget& object1,
            const CreateMonitoredDataResultTarget& object2)
    {
        return !(object1 == object2);
    }


    // operator<
    // =============================================================================================
    bool operator<(
            const CreateMonitoredDataResultTarget& object1,
            const CreateMonitoredDataResultTarget& object2)
    {
        if (object1.clientConnectionId != object2.clientConnectionId)
            return object1.clientConnectionId < object2.clientConnectionId;
        else if (object1.clientSubscriptionHandle != object2.clientSubscriptionHandle)
            return object1.clientSubscriptionHandle < object2.clientSubscriptionHandle;
        else if (object1.clientHandle != object2.clientHandle)
            return object1.clientHandle < object2.clientHandle;
        else if (object1.status != object2.status)
            return object1.status < object2.status;
        else if (object1.monitoredItemId != object2.monitoredItemId)
            return object1.monitoredItemId < object2.monitoredItemId;
        else if (object1.revisedSamplingIntervalSec != object2.revisedSamplingIntervalSec)
            return object1.revisedSamplingIntervalSec < object2.revisedSamplingIntervalSec;
        else
            return object1.revisedQueueSize < object2.revisedQueueSize;
    }



}
