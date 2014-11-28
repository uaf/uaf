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

#ifndef UAFC_SESSIONINFORMATION_H_
#define UAFC_SESSIONINFORMATION_H_

// STD
#include <string>
#include <sstream>
// SDK
#include "uaclient/uaclientsdk.h"
// UAF
#include "uaf/util/stringifiable.h"
#include "uaf/util/handles.h"
#include "uaf/util/datetime.h"
#include "uaf/util/status.h"
#include "uaf/client/clientexport.h"
#include "uaf/client/clientstatus.h"
#include "uaf/client/sessions/sessionstates.h"
#include "uaf/client/sessions/connectionsteps.h"

namespace uafc
{

    /*******************************************************************************************//**
    * A SessionInformation object contains information about a session such as the state of the
    * session, the server URI of the server to which it is connected, etc.
    *
    * @ingroup ClientSessions
    ***********************************************************************************************/
    class UAFC_EXPORT SessionInformation
    {
    public:


        /**
         * Create a default SessionInformation object.
         */
        SessionInformation();


        /**
         * Create a SessionInformation object with the given information.
         *
         * @param clientConnectionId    The id of the session.
         * @param sessionState          The state of the session.
         * @param serverUri             The URI of the server to which the session should be
         *                              connected.
         * @param sessionState          The time of the last connection attempt.
         * @param sessionState          The status of the last connection attempt.
         */
        SessionInformation(
                uaf::ClientConnectionId                         clientConnectionId,
                uafc::sessionstates::SessionState               sessionState,
                const std::string&                              serverUri,
                const uafc::connectionsteps::ConnectionStep&    lastConnectionAttemptStep,
                const uafc::ClientStatus&                       lastConnectionAttemptStatus);


        /** The state of the session. */
        uafc::sessionstates::SessionState   sessionState;

        /** The id of the session. */
        uaf::ClientConnectionId             clientConnectionId;

        /** The URI of the server to which the session should be connected. */
        std::string                         serverUri;

        /** The status of the last connection attempt. */
        uafc::ClientStatus                  lastConnectionAttemptStatus;

        /** The step of the last connection attempt. */
        uafc::connectionsteps::ConnectionStep lastConnectionAttemptStep;

        /**
         * Get a string representation of the information.
         */
        std::string toString(const std::string& indent="", std::size_t colon=31) const;


        // comparison operators
        friend UAFC_EXPORT bool operator==(
                const SessionInformation& object1,
                const SessionInformation& object2);
        friend UAFC_EXPORT bool operator!=(
                const SessionInformation& object1,
                const SessionInformation& object2);
        friend UAFC_EXPORT bool operator<(
                const SessionInformation& object1,
                const SessionInformation& object2);
    };


}


#endif /* UAFC_SESSIONINFORMATION_H_ */
