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

#include "uaf/client/sessions/sessionstates.h"

namespace uaf
{

    namespace sessionstates
    {

        // Get a string representation
        // =============================================================================================
        std::string toString(uaf::sessionstates::SessionState state)
        {
            switch (state)
            {
                case uaf::sessionstates::Disconnected:
                    return "Disconnected";
                case uaf::sessionstates::Connected:
                    return "Connected";
                case uaf::sessionstates::ConnectionErrorApiReconnect:
                    return "ConnectionErrorApiReconnect";
                case uaf::sessionstates::ConnectionWarningWatchdogTimeout:
                    return "ConnectionWarningWatchdogTimeout";
                case uaf::sessionstates::NewSessionCreated:
                    return "NewSessionCreated";
                case uaf::sessionstates::ServerShutdown:
                    return "ServerShutdown";
                default:
                    return "UNKNOWN";
            }
        }


        // SDK to UAF mode
        // =============================================================================================
        UaClientSdk::UaClient::ServerStatus toSdk(uaf::sessionstates::SessionState state)
        {
            switch (state)
            {
                case uaf::sessionstates::Disconnected:
                    return UaClientSdk::UaClient::Disconnected;
                case uaf::sessionstates::Connected:
                    return UaClientSdk::UaClient::Connected;
                case uaf::sessionstates::ConnectionErrorApiReconnect:
                    return UaClientSdk::UaClient::ConnectionErrorApiReconnect;
                case uaf::sessionstates::ConnectionWarningWatchdogTimeout:
                    return UaClientSdk::UaClient::ConnectionWarningWatchdogTimeout;
                case uaf::sessionstates::NewSessionCreated:
                    return UaClientSdk::UaClient::NewSessionCreated;
                case uaf::sessionstates::ServerShutdown:
                    return UaClientSdk::UaClient::ServerShutdown;
                default:
                    return UaClientSdk::UaClient::Disconnected;
            }
        }

        // UAF to SDK mode
        // =============================================================================================
        SessionState toUaf(UaClientSdk::UaClient::ServerStatus serverStatus)
        {
            switch (serverStatus)
            {
                case UaClientSdk::UaClient::Disconnected:
                    return uaf::sessionstates::Disconnected;
                case UaClientSdk::UaClient::Connected:
                    return uaf::sessionstates::Connected;
                case UaClientSdk::UaClient::ConnectionErrorApiReconnect:
                    return uaf::sessionstates::ConnectionErrorApiReconnect;
                case UaClientSdk::UaClient::ConnectionWarningWatchdogTimeout:
                    return uaf::sessionstates::ConnectionWarningWatchdogTimeout;
                case UaClientSdk::UaClient::NewSessionCreated:
                    return uaf::sessionstates::NewSessionCreated;
                case UaClientSdk::UaClient::ServerShutdown:
                    return uaf::sessionstates::ServerShutdown;
                default:
                    return uaf::sessionstates::Disconnected;
            }
        }
    }
}
