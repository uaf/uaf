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

#include "uaf/client/sessions/sessioninformation.h"

namespace uafc
{
    using namespace uaf;
    using namespace uafc;
    using std::string;
    using std::stringstream;
    using std::size_t;


    // Constructor
    // =============================================================================================
    SessionInformation::SessionInformation()
    : sessionState(uafc::sessionstates::Disconnected),
      clientConnectionId(0),
      lastConnectionAttemptStep(uafc::connectionsteps::ActivateSession)
    {}


    // Constructor
    // =============================================================================================
    SessionInformation::SessionInformation(
            ClientConnectionId                      clientConnectionId,
            uafc::sessionstates::SessionState       sessionState,
            const string&                           serverUri,
            const connectionsteps::ConnectionStep&  lastConnectionAttemptStep,
            const Status&                           lastConnectionAttemptStatus)
      : sessionState(sessionState),
        clientConnectionId(clientConnectionId),
        serverUri(serverUri),
        lastConnectionAttemptStatus(lastConnectionAttemptStatus),
        lastConnectionAttemptStep(lastConnectionAttemptStep)
    {}


    // Get a new client connection id
    // =============================================================================================
    string SessionInformation::toString(const string& indent, size_t colon) const
    {
        stringstream ss;

        ss << indent << " - clientConnectionId";
        ss << fillToPos(ss, colon);
        ss << ": " << clientConnectionId << "\n";

        ss << indent << " - sessionState";
        ss << fillToPos(ss, colon);
        ss << ": " << sessionState << " (" << uafc::sessionstates::toString(sessionState) << ")\n";

        ss << indent << " - serverUri";
        ss << fillToPos(ss, colon);
        ss << ": " << serverUri << "\n";

        ss << indent << " - lastConnectionAttemptStep";
        ss << fillToPos(ss, colon);
        ss << ": " << uafc::connectionsteps::toString(lastConnectionAttemptStep) << "\n";

        ss << indent << " - lastConnectionAttemptStatus";
        ss << fillToPos(ss, colon);
        ss << ": " << lastConnectionAttemptStatus.toString();

        return ss.str();
    }


    // operator==
    // =============================================================================================
    bool operator==(const SessionInformation& object1, const SessionInformation& object2)
    {
        return    object1.clientConnectionId == object2.clientConnectionId
               && object1.serverUri == object2.serverUri
               && object1.sessionState == object2.sessionState
               && object1.lastConnectionAttemptStep == object2.lastConnectionAttemptStep
               && object1.lastConnectionAttemptStatus == object2.lastConnectionAttemptStatus;
    }


    // operator!=
    // =============================================================================================
    bool operator!=(const SessionInformation& object1, const SessionInformation& object2)
    {
        return !(object1 == object2);
    }


    // operator<
    // =============================================================================================
    bool operator<(const SessionInformation& object1, const SessionInformation& object2)
    {
        if (object1.clientConnectionId != object2.clientConnectionId)
            return object1.clientConnectionId < object2.clientConnectionId;
        else if (object1.serverUri != object2.serverUri)
            return object1.serverUri < object2.serverUri;
        else if (object1.lastConnectionAttemptStep != object2.lastConnectionAttemptStep)
            return object1.lastConnectionAttemptStep < object2.lastConnectionAttemptStep;
        else if (object1.lastConnectionAttemptStatus != object2.lastConnectionAttemptStatus)
            return object1.lastConnectionAttemptStatus < object2.lastConnectionAttemptStatus;
        else
            return object1.sessionState < object2.sessionState;
    }
}
