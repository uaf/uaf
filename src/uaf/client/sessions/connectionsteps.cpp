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

#include "uaf/client/sessions/connectionsteps.h"

namespace uaf
{

    namespace connectionsteps
    {

        // Get a string representation
        // =============================================================================================
        std::string toString(uaf::connectionsteps::ConnectionStep step)
        {
            switch (step)
            {
                case uaf::connectionsteps::ActivateSession:
                    return "ActivateSession";
                case uaf::connectionsteps::CertificateValidation:
                    return "CertificateValidation";
                case uaf::connectionsteps::CreateSession:
                    return "CreateSession";
                case uaf::connectionsteps::OpenSecureChannel:
                    return "OpenSecureChannel";
                case uaf::connectionsteps::NoAttemptYet:
                    return "NoAttemptYet";
                default:
                    return "Unknown";
            }
        }

        // to UAF
        // =============================================================================================
        uaf::connectionsteps::ConnectionStep fromSdk(UaClientSdk::UaClient::ConnectServiceType step)
        {
            switch (step)
            {
                case UaClientSdk::UaClient::ActivateSession:
                    return uaf::connectionsteps::ActivateSession;
                case UaClientSdk::UaClient::CertificateValidation:
                    return uaf::connectionsteps::CertificateValidation;
                case UaClientSdk::UaClient::CreateSession:
                    return uaf::connectionsteps::CreateSession;
                case UaClientSdk::UaClient::OpenSecureChannel:
                    return uaf::connectionsteps::OpenSecureChannel;
                default:
                    return uaf::connectionsteps::Unknown;
            }
        }
    }
}
