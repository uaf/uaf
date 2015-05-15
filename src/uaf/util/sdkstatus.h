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



namespace uaf
{

    /*******************************************************************************************//**
     * An SdkStatus stores the information (i.e. status code and description) of a Status object
     * by the SDK.
     *
     * @ingroup Util
     **********************************************************************************************/
    class UAF_EXPORT SdkStatus
    {
    public:

        /** Construct an uncertain status without description */
        SdkStatus()
        : statusCode(OpcUa_Uncertain)
        {}

        /** Construct a status based on a UaStatus object. */
        SdkStatus(const UaStatus& uaStatus)
        : message(uaStatus.toString().toUtf8()),
          statusCode(uaStatus.statusCode())
        {}

        /** Construct a status based on a UaStatusCode object. */
        SdkStatus(const UaStatusCode& uaStatusCode)
        : message(uaStatusCode.toString().toUtf8()),
          statusCode(uaStatusCode.statusCode())
        {}

        /** Construct a status based on a OpcUa_StatusCode integer. */
        SdkStatus(OpcUa_StatusCode uaStatusCode)
        : message(UaStatusCode(uaStatusCode).toString().toUtf8()),
          statusCode(uaStatusCode)
        {}

        /** The message of the status. */
        std::string message;

        /** The OPC UA (!) status code. */
        uint32_t    statusCode;

        /** Check if the Status is good/bad/uncertain/... */
        bool isGood()           const { return OpcUa_IsGood(statusCode);      }
        bool isBad()            const { return OpcUa_IsBad(statusCode);       }
        bool isUncertain()      const { return OpcUa_IsUncertain(statusCode); }
        bool isNotGood()        const { return !isGood();      }
        bool isNotBad()         const { return !isBad();       }
        bool isNotUncertain()   const { return !isUncertain(); }


        /** Get a string representation. */
        std::string toString() const
        {
            UaStatus status;
            status.setStatus(statusCode, message.c_str());
            return status.toString().toUtf8();
        }

    };



}



#endif /* UAF_SDKSTATUS_H */
