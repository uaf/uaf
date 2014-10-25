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

#ifndef UAFC_CONNECTIONSTEP_H_
#define UAFC_CONNECTIONSTEP_H_

// STD
#include <string>
#include <stdint.h>
// SDK
#include "uaclient/uaclientsdk.h"
// UAF
#include "uaf/client/clientexport.h"

namespace uafc
{


    namespace connectionsteps
    {


        /**
         * The steps during the connection of a session.
         *
         * @ingroup ClientSessions
         */
        enum ConnectionStep
        {
            NoAttemptYet            = 0, /*!< Connection has not started yet. */
            CertificateValidation   = 1, /*!< Certificate validation step. */
            OpenSecureChannel       = 2, /*!< Opening a secure channel. */
            CreateSession           = 3, /*!< Creating the session. */
            ActivateSession         = 4, /*!< Activating the session. */
            Unknown                 = 5  /*!< Unknown. */
        };



        /**
         * Get a string representation of the connection step.
         *
         * @param step  The connection step (as an enum).
         * @return      The corresponding name of the connection step.
         *
         * @ingroup ClientSessions
         */
        std::string UAFC_EXPORT toString(uafc::connectionsteps::ConnectionStep step);


        /**
         * Convert a SDK "server status" into a UAF "session state".
         *
         * @param status    The server status as defined by the SDK.
         * @return          The session state as defined by the UAF.
         *
         * @ingroup ClientSessions
         */
        uafc::connectionsteps::ConnectionStep UAFC_EXPORT fromSdk(
                UaClientSdk::UaClient::ConnectServiceType step);
    }

}


#endif /* UAFC_CONNECTIONSTEP_H_ */
