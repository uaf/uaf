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

namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;
    using std::size_t;


    // Constructor
    // =============================================================================================
    SessionInformation::SessionInformation()
    : sessionState(uaf::sessionstates::Disconnected),
      serverState(uaf::serverstates::Unknown),
      clientConnectionId(0),
      lastConnectionAttemptStep(uaf::connectionsteps::ActivateSession)
    {}


    // Constructor
    // =============================================================================================
    SessionInformation::SessionInformation(
            ClientConnectionId                      clientConnectionId,
            uaf::sessionstates::SessionState        sessionState,
            uaf::serverstates::ServerState          serverState,
            const string&                           serverUri,
            const SessionSettings&                  sessionSettings,
            const connectionsteps::ConnectionStep&  lastConnectionAttemptStep,
            const Status&                           lastConnectionAttemptStatus)
      : sessionState(sessionState),
        serverState(serverState),
        clientConnectionId(clientConnectionId),
        serverUri(serverUri),
        sessionSettings(sessionSettings),
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
        ss << ": " << sessionState << " (" << uaf::sessionstates::toString(sessionState) << ")\n";

        ss << indent << " - serverState";
        ss << fillToPos(ss, colon);
        ss << ": " << serverState << " (" << uaf::serverstates::toString(serverState) << ")\n";

        ss << indent << " - serverUri";
        ss << fillToPos(ss, colon);
        ss << ": " << serverUri << "\n";

        ss << indent << " - sessionSettings\n";
        ss << sessionSettings.toString(indent + "   ", colon) << "\n";

        ss << indent << " - lastConnectionAttemptStep";
        ss << fillToPos(ss, colon);
        ss << ": " << uaf::connectionsteps::toString(lastConnectionAttemptStep) << "\n";

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
               && object1.serverState == object2.serverState
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
        else if (object1.sessionState != object2.sessionState)
            return object1.sessionState < object2.sessionState;
        else
            return object1.serverState < object2.serverState;
    }
}
