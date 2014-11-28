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

#ifndef UAF_SDKSTATUS_H
#define UAF_SDKSTATUS_H

// STD
#include <string>
#include <vector>
// SDK
#include "uabase/statuscode.h"
// UAF
#include "uaf/util/status.h"



namespace uaf
{


    class UAF_EXPORT SdkStatus
    {
    public:

        SdkStatus()
        : statusCode(OpcUa_Uncertain)
        {}

        SdkStatus(const UaStatus& uaStatus)
        : description(uaStatus.toString().toUtf8()),
          statusCode(uaStatus.statusCode())
        {}

        SdkStatus(const UaStatusCode& uaStatusCode)
        : description(uaStatusCode.toString().toUtf8()),
          statusCode(uaStatusCode.statusCode())
        {}

        std::string description;
        uint32_t    statusCode;

        bool isGood()           const { return OpcUa_IsGood(statusCode);      }
        bool isBad()            const { return OpcUa_IsBad(statusCode);       }
        bool isUncertain()      const { return OpcUa_IsUncertain(statusCode); }

        bool isNotGood()        const { return !isGood();      }
        bool isNotBad()         const { return !isBad();       }
        bool isNotUncertain()   const { return !isUncertain(); }

        std::string toString() const
        {
            UaStatus status;
            status.setStatus(statusCode, description.c_str());
            return status.toString().toUtf8();
        }

    };



}



#endif /* UAF_SDKSTATUS_H */
