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

#include "uaf/util/applicationtypes.h"

namespace uaf
{
    namespace applicationtypes
    {

        using namespace uaf::applicationtypes;


        // Get a string representation
        // =========================================================================================
        std::string toString(ApplicationType type)
        {
            switch (type)
            {
                case Server:            return "Server";
                case Client:            return "Client";
                case ClientAndServer:   return "ClientAndServer";
                case DiscoveryServer:   return "DiscoveryServer";
                default:                return "INVALID";
            }
        }


        // Convert the SDK/Stack instance to a UAF instance.
        // =========================================================================================
        ApplicationType fromSdkToUaf(OpcUa_ApplicationType type)
        {
            switch (type)
            {
                case OpcUa_ApplicationType_Server:          return Server;
                case OpcUa_ApplicationType_Client:          return Client;
                case OpcUa_ApplicationType_ClientAndServer: return ClientAndServer;
                case OpcUa_ApplicationType_DiscoveryServer: return DiscoveryServer;
                default:                                    return Server;
            }
        }


        // Convert the UAF instance to a SDK/Stack instance.
        // =========================================================================================
        OpcUa_ApplicationType fromUafToSdk(ApplicationType type)
        {
            switch (type)
            {
                case Server:          return OpcUa_ApplicationType_Server;
                case Client:          return OpcUa_ApplicationType_Client;
                case ClientAndServer: return OpcUa_ApplicationType_ClientAndServer;
                case DiscoveryServer: return OpcUa_ApplicationType_DiscoveryServer;
                default:              return OpcUa_ApplicationType_Server;
            }
        }


    }
}
