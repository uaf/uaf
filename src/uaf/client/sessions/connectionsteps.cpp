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

namespace uafc
{
    using namespace uafc;

    namespace connectionsteps
    {

        // Get a string representation
        // =============================================================================================
        std::string toString(uafc::connectionsteps::ConnectionStep step)
        {
            switch (step)
            {
                case uafc::connectionsteps::ActivateSession:
                    return "ActivateSession";
                case uafc::connectionsteps::CertificateValidation:
                    return "CertificateValidation";
                case uafc::connectionsteps::CreateSession:
                    return "CreateSession";
                case uafc::connectionsteps::OpenSecureChannel:
                    return "OpenSecureChannel";
                case uafc::connectionsteps::NoAttemptYet:
                    return "NoAttemptYet";
                default:
                    return "Unknown";
            }
        }

        // to UAF
        // =============================================================================================
        uafc::connectionsteps::ConnectionStep fromSdk(UaClientSdk::UaClient::ConnectServiceType step)
        {
            switch (step)
            {
                case UaClientSdk::UaClient::ActivateSession:
                    return uafc::connectionsteps::ActivateSession;
                case UaClientSdk::UaClient::CertificateValidation:
                    return uafc::connectionsteps::CertificateValidation;
                case UaClientSdk::UaClient::CreateSession:
                    return uafc::connectionsteps::CreateSession;
                case UaClientSdk::UaClient::OpenSecureChannel:
                    return uafc::connectionsteps::OpenSecureChannel;
                default:
                    return uafc::connectionsteps::Unknown;
            }
        }
    }
}
