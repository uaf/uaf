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

#ifndef UAF_STATUSCODES_H_
#define UAF_STATUSCODES_H_

// STD
#include <string>
#include <vector>
// SDK
#include "uabase/uaplatformlayer.h"
// UAF
#include "uaf/util/util.h"


/** @file */


namespace uaf
{

    namespace statuscodes
    {

        /**
         * This enum defines the status codes as specified by the UAF.
         *
         * These status codes are more general than the (more than hundred!) status codes specified
         * by the OPC UA standard. Each "OPC UA status code" can be mapped to exactly one
         * "UAF statuscode".
         *
         * For instance, an OpcUa_BadUserAccessDenied, OpcUa_BadCertificateInvalid,
         * OpcUa_BadCertificateUntrusted (and many more) OPC UA status codes lead to a
         * uaf::statuscodes::SecurityError status code.
         *
         * @ingroup Util
         */
        enum StatusCode
        {
            Good,
            Uncertain,
            ConfigurationError,
            ConnectionError,
            DataFormatError,
            DataSizeError,
            DataSourceError,
            DisconnectionError,
            DiscoveryError,
            InvalidRequestError,
            LowLevelError,
            ResolutionError,
            WrongTypeError,
            OtherError,
            SecurityError,
            TimeoutError,
            NoResultReceivedError,
            SubscriptionError,
            UnexpectedError,
            UnknownHandleError,
            UnsupportedError
        };


        /**
         * Get a string representation of the status code.
         *
         * @param code  The status code (as an enum).
         * @return      The corresponding name of the status code.
         *
         * @ingroup Util
         */
        std::string UAF_EXPORT toString(uaf::statuscodes::StatusCode code);


        /**
         * Convert the SDK/Stack code to a UAF code.
         *
         * @ingroup Util
         */
        uaf::statuscodes::StatusCode UAF_EXPORT fromSdkToUaf(OpcUa_StatusCode code);


        /**
         * Convert the UAF code to a SDK code.
         *
         * @ingroup Util
         */
        OpcUa_StatusCode UAF_EXPORT fromUafToSdk(uaf::statuscodes::StatusCode code);

    }


}


#endif /* UAF_STATUSCODES_H_ */
