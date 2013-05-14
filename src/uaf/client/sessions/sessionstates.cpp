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

namespace uafc
{
    using namespace uafc;

    namespace sessionstates
    {

        // Get a string representation
        // =============================================================================================
        std::string toString(uafc::sessionstates::SessionState state)
        {
            switch (state)
            {
                case uafc::sessionstates::Disconnected:
                    return "Disconnected";
                case uafc::sessionstates::Connected:
                    return "Connected";
                case uafc::sessionstates::ConnectionErrorApiReconnect:
                    return "ConnectionErrorApiReconnect";
                case uafc::sessionstates::ConnectionWarningWatchdogTimeout:
                    return "ConnectionWarningWatchdogTimeout";
                case uafc::sessionstates::NewSessionCreated:
                    return "NewSessionCreated";
                case uafc::sessionstates::ServerShutdown:
                    return "ServerShutdown";
                default:
                    return "UNKNOWN";
            }
        }


        // SDK to UAF mode
        // =============================================================================================
        UaClientSdk::UaClient::ServerStatus toSdk(uafc::sessionstates::SessionState state)
        {
            switch (state)
            {
                case uafc::sessionstates::Disconnected:
                    return UaClientSdk::UaClient::Disconnected;
                case uafc::sessionstates::Connected:
                    return UaClientSdk::UaClient::Connected;
                case uafc::sessionstates::ConnectionErrorApiReconnect:
                    return UaClientSdk::UaClient::ConnectionErrorApiReconnect;
                case uafc::sessionstates::ConnectionWarningWatchdogTimeout:
                    return UaClientSdk::UaClient::ConnectionWarningWatchdogTimeout;
                case uafc::sessionstates::NewSessionCreated:
                    return UaClientSdk::UaClient::NewSessionCreated;
                case uafc::sessionstates::ServerShutdown:
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
                    return uafc::sessionstates::Disconnected;
                case UaClientSdk::UaClient::Connected:
                    return uafc::sessionstates::Connected;
                case UaClientSdk::UaClient::ConnectionErrorApiReconnect:
                    return uafc::sessionstates::ConnectionErrorApiReconnect;
                case UaClientSdk::UaClient::ConnectionWarningWatchdogTimeout:
                    return uafc::sessionstates::ConnectionWarningWatchdogTimeout;
                case UaClientSdk::UaClient::NewSessionCreated:
                    return uafc::sessionstates::NewSessionCreated;
                case UaClientSdk::UaClient::ServerShutdown:
                    return uafc::sessionstates::ServerShutdown;
                default:
                    return uafc::sessionstates::Disconnected;
            }
        }
    }
}
