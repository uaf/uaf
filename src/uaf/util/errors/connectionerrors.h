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


#ifndef UAF_CONNECTIONERRORS_H_
#define UAF_CONNECTIONERRORS_H_


// STD
#include <vector>
#include <string>
// SDK
// UAF
#include "uaf/util/sdkstatus.h"
#include "uaf/util/stringifiable.h"
#include "uaf/util/errors/invalidrequesterror.h"

namespace uaf
{

    class UAF_EXPORT ConnectionError : public uaf::InvalidRequestError
    {
    public:
        ConnectionError()
        : uaf::InvalidRequestError("Connection error")
        {}
        ConnectionError(const std::string& description)
        : uaf::InvalidRequestError(description)
        {}

    };

    class UAF_EXPORT ConnectionFailedError : public uaf::ConnectionError
    {
    public:
        ConnectionFailedError()
        : uaf::ConnectionError("Connection failed")
        {}

        ConnectionFailedError(const std::string& endpointUrl, const uaf::SdkStatus& sdkStatus)
        : uaf::ConnectionError(uaf::format("Connection to endpoint '%s' failed: %s",
                                           sdkStatus.toString().c_str(),
                                           endpointUrl.c_str())),
          sdkStatus(sdkStatus),
          endpointUrl(endpointUrl)
        {}

        uaf::SdkStatus sdkStatus;
        std::string endpointUrl;
    };

    class UAF_EXPORT AsyncConnectionFailedError : public uaf::ConnectionError
    {
    public:
        AsyncConnectionFailedError()
        : uaf::ConnectionError("Connection failed")
        {}

        AsyncConnectionFailedError(const std::string& serverUri, const uaf::SdkStatus& sdkStatus)
        : uaf::ConnectionError(uaf::format("Connection to server URI '%s' failed: %s",
                                           sdkStatus.toString().c_str(),
                                           serverUri.c_str())),
          sdkStatus(sdkStatus),
          serverUri(serverUri)
        {}

        uaf::SdkStatus sdkStatus;
        std::string serverUri;
    };

    class UAF_EXPORT DisconnectionFailedError : public uaf::ConnectionError
    {
    public:
        DisconnectionFailedError()
        : uaf::ConnectionError("Disconnection failed")
        {}

        DisconnectionFailedError(const std::string& endpointUrl, const uaf::SdkStatus& sdkStatus)
        : uaf::ConnectionError(uaf::format("Disconnection from endpoint '%s' failed: %s",
                               endpointUrl.c_str(),
                               sdkStatus.toString().c_str())),
          sdkStatus(sdkStatus),
          endpointUrl(endpointUrl)
        {}

        uaf::SdkStatus sdkStatus;
        std::string endpointUrl;
    };

    class UAF_EXPORT NoConnectedSessionToUpdateArraysError : public uaf::ConnectionError
    {
    public:
        NoConnectedSessionToUpdateArraysError()
        : uaf::ConnectionError("There's no connected session to update the arrays")
        {}
    };


    class UAF_EXPORT SessionNotConnectedError : public uaf::ConnectionError
    {
    public:
        SessionNotConnectedError()
        : uaf::ConnectionError("The session is not connected")
        {}
    };





}

#endif /* UAF_CONNECTIONERRORS_H_ */
