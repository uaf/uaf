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

#ifndef UAFC_SESSIONSTATE_H_
#define UAFC_SESSIONSTATE_H_

// STD
#include <string>
#include <stdint.h>
// SDK
#include "uaclient/uaclientsdk.h"
#include "uaclient/uasession.h"
// UAF
#include "uaf/client/clientexport.h"

namespace uafc
{


    namespace sessionstates
    {

        /**
         * The state of the session.
         *
         * @ingroup ClientSessions
         */
        enum SessionState
        {
            Disconnected                     = 0, /**< The session was disconnected by the user on the client side. */
            Connected                        = 1, /**< The session was connected by the user on the client side, and is running in normal mode. */
            ConnectionWarningWatchdogTimeout = 2, /**< There was a watchdog timeout, indicating a potential connection problem. */
            ConnectionErrorApiReconnect      = 3, /**< The client is trying to reconnect after a connection problem. */
            ServerShutdown                   = 4, /**< The client is trying to reconnect after the server announced its shutdown. */
            NewSessionCreated                = 5  /**< A new session has been created since the old one could not be reused. */
        };


        /**
         * Get a string representation of the session state.
         *
         * @param state  The session state (as an enum).
         * @return       The corresponding name of the session state.
         *
         * @ingroup ClientSessions
         */
        std::string UAFC_EXPORT toString(uafc::sessionstates::SessionState state);


        /**
         * Convert a UAF "session state" into an SDK "server status".
         *
         * @param state The session state as defined by the UAF.
         * @return      The server status as defined by the SDK.
         *
         * @ingroup ClientSessions
         */
        UaClientSdk::UaClient::ServerStatus UAFC_EXPORT toSdk(
                uafc::sessionstates::SessionState state);


        /**
         * Convert a SDK "server status" into a UAF "session state".
         *
         * @param status    The server status as defined by the SDK.
         * @return          The session state as defined by the UAF.
         *
         * @ingroup ClientSessions
         */
        uafc::sessionstates::SessionState UAFC_EXPORT toUaf(
                UaClientSdk::UaClient::ServerStatus status);
    }

}


#endif /* UAFC_SESSIONSTATE_H_ */
