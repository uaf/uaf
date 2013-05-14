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

#include "uaf/util/messagesecuritymodes.h"

namespace uaf
{
    using namespace uaf;
    using std::string;

    namespace messagesecuritymodes
    {

        using namespace messagesecuritymodes;


        // Get a string representation
        // =========================================================================================
        string toString(MessageSecurityMode mode)
        {
            switch (mode)
            {
                case Mode_Invalid:        return "Invalid";
                case Mode_None:           return "None";
                case Mode_Sign:           return "Sign";
                case Mode_SignAndEncrypt: return "SignAndEncrypt";
                default:                  return "UNKNOWN";
            }
        }


        // SDK to UAF mode
        // =========================================================================================
        MessageSecurityMode fromSdkToUaf(OpcUa_MessageSecurityMode mode)
        {
            switch (mode)
            {
                case OpcUa_MessageSecurityMode_Invalid:         return Mode_Invalid;
                case OpcUa_MessageSecurityMode_None:            return Mode_None;
                case OpcUa_MessageSecurityMode_Sign:            return Mode_Sign;
                case OpcUa_MessageSecurityMode_SignAndEncrypt:  return Mode_SignAndEncrypt;
                default:                                        return Mode_Invalid;
            }
        }


        // UAF to SDK mode
        // =========================================================================================
        OpcUa_MessageSecurityMode fromUafToSdk(MessageSecurityMode mode)
        {
            switch (mode)
            {
                case Mode_Invalid:        return OpcUa_MessageSecurityMode_Invalid;
                case Mode_None:           return OpcUa_MessageSecurityMode_None;
                case Mode_Sign:           return OpcUa_MessageSecurityMode_Sign;
                case Mode_SignAndEncrypt: return OpcUa_MessageSecurityMode_SignAndEncrypt;
                default:                  return OpcUa_MessageSecurityMode_Invalid;
            }
        }

    }
}
