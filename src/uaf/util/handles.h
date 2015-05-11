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


#ifndef UAF_HANDLES_H_
#define UAF_HANDLES_H_


// STD
#include <stdint.h>
// SDK
#include "uabase/uaplatformlayer.h"
// UAF

namespace uaf
{

    /**
     * Each request will be assigned a handle that will remain unique during the lifetime of the
     * client. The handle is 64 bit, meaning that even at 1 million requests per second, the client
     * will be able to assign unique handles for more than 500000 years...
     *
     * @ingroup Util
     */
    typedef uint64_t RequestHandle;

    /** RequestHandle value when it was not assigned. */
    static const uaf::RequestHandle REQUESTHANDLE_NOT_ASSIGNED = OpcUa_UInt64_Max;

    /** Maximum RequestHandle value. */
    static const uaf::RequestHandle REQUESTHANDLE_MAX          = OpcUa_UInt64_Max - 1;

    /**
     * A TransactionId is internally assigned and stored by the UAF to keep track of asynchronous
     * requests and their results.
     *
     * @ingroup Util
     */
    typedef uint32_t TransactionId;

    /**
     * A ClientConnectionId is a 32-bit number assigned by the UAF to newly created sessions.
     * The number will be incremented on each new session creation, so in theory it will take 2**32
     * sessions that have to be created before the number starts to count from 0 again.
     *
     * @ingroup Util
     */
    typedef uint32_t ClientConnectionId;

    /**
     * A SubscriptionId is assigned to a subscription by the server (so NOT by the client!).
     *
     * @ingroup Util
     */
    typedef uint32_t SubscriptionId;

    /**
     * A ClientSubscriptionHandle is a 32-bit number assigned by the UAF to newly created
     * subscriptions. The number will be incremented on each new subscription creation, so in
     * theory it will take 2**32 subscriptions that have to be created before the number starts
     * to count from 0 again. In practice, it will never happen.
     *
     * @ingroup Util
     */
    typedef uint32_t ClientSubscriptionHandle;

    /**
     * A SubscriptionId is assigned to a monitored item by the server (so NOT by the client!).
     *
     * @ingroup Util
     */
    typedef uint32_t MonitoredItemId;

    /**
     * A ClientHandle is a 32-bit number assigned by the UAF to newly created
     * monitored items. The number will be incremented on each new item creation, so in
     * theory it will take 2**32 items that have to be created before the number starts
     * to count from 0 again. In practice, it will never happen.
     *
     * @ingroup Util
     */
    typedef uint32_t ClientHandle;

    /** Client handle value when it was not assigned. */
    static const uint32_t CLIENTHANDLE_NOT_ASSIGNED = OpcUa_UInt32_Max;

    /** Maximum client handle value. */
    static const uint32_t CLIENTHANDLE_MAX = OpcUa_UInt32_Max - 1;

    /**
     * A ServerIndex is an unsigned 32-bit integer, identifying a server in a ServerArray.
     *
     * @ingroup Util
     */
    typedef uint32_t ServerIndex;

    /**
     * An OPC UA namespace index is used to relate something (e.g. a NodeIdIdentifier) to a
     * namespace URI via a namespace array.
     *
     * @ingroup Util
     */
    typedef uint16_t NameSpaceIndex;

}



#endif /* UAF_HANDLES_H_ */
