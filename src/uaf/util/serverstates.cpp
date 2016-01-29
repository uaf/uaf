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

#include "uaf/util/serverstates.h"

namespace uaf
{
    namespace serverstates
    {

        using namespace uaf::serverstates;

        // Get a string representation
        // =========================================================================================
        std::string toString(ServerState state)
        {
            switch (state)
            {
                case Running:               return "Running";
                case Failed:                return "Failed";
                case NoConfiguration:       return "NoConfiguration";
                case Suspended:             return "Suspended";
                case Shutdown:              return "Shutdown";
                case Test:                  return "Test";
                case CommunicationFault:    return "CommunicationFault";
                case Unknown:               return "Unknown";
                default:                    return "INVALID";
            }
        }


        // UAF to SDK type
        // =========================================================================================
        OpcUa_ServerState fromUafToSdk(ServerState state)
        {
            switch (state)
            {
                case Running:               return OpcUa_ServerState_Running;
                case Failed:                return OpcUa_ServerState_Failed;
                case NoConfiguration:       return OpcUa_ServerState_NoConfiguration;
                case Suspended:             return OpcUa_ServerState_Suspended;
                case Shutdown:              return OpcUa_ServerState_Shutdown;
                case Test:                  return OpcUa_ServerState_Test;
                case CommunicationFault:    return OpcUa_ServerState_CommunicationFault;
                case Unknown:               return OpcUa_ServerState_Unknown;
                default:                    return OpcUa_ServerState_Unknown;
            }
        }


        // SDK to UAF type
        // =========================================================================================
        ServerState fromSdkToUaf(OpcUa_ServerState type)
        {
            switch (type)
            {
                case OpcUa_ServerState_Running:             return Running;
                case OpcUa_ServerState_Failed:              return Failed;
                case OpcUa_ServerState_NoConfiguration:     return NoConfiguration;
                case OpcUa_ServerState_Suspended:           return Suspended;
                case OpcUa_ServerState_Shutdown:            return Shutdown;
                case OpcUa_ServerState_Test:                return Test;
                case OpcUa_ServerState_CommunicationFault:  return CommunicationFault;
                case OpcUa_ServerState_Unknown:             return Unknown;
                default:                                    return Unknown;
            }
        }


    }
}
