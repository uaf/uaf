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


#ifndef UAFC_DISCOVERYERRORS_H_
#define UAFC_DISCOVERYERRORS_H_


// STD
#include <vector>
#include <string>
// SDK
// UAF
#include "uaf/util/sdkstatus.h"
#include "uaf/util/stringifiable.h"
#include "uaf/client/errors/clienterror.h"
#include "uaf/client/clientexport.h"

namespace uafc
{


    class UAFC_EXPORT EmptyUrlError : public uafc::ClientError
    {
    public:
        EmptyUrlError()
        : uafc::ClientError("An empty URL was given")
        {}
    };


    class UAFC_EXPORT DiscoveryError : public uafc::ClientError
    {
    public:
        DiscoveryError()
        : uafc::ClientError("Discovery error")
        {}

        DiscoveryError(const std::string& description)
        : uafc::ClientError(description)
        {}
    };


    class UAFC_EXPORT CouldNotConnectError : public uafc::ClientError
    {
    public:
        CouldNotConnectError()
        : uafc::ClientError("Could not connect")
        {}

        CouldNotConnectError(const std::string& endpointUrl, const uaf::SdkStatus& sdkStatus)
        : uafc::ClientError(uaf::format("could not connect to endpoint '%s': %s",
                                        sdkStatus.toString().c_str(),
                                        endpointUrl.c_str())),
          sdkStatus(sdkStatus),
          endpointUrl(endpointUrl)
        {}

        uaf::SdkStatus sdkStatus;
        std::string endpointUrl;
    };




    class UAFC_EXPORT NoEndpointsProvidedByServerError : public uafc::DiscoveryError
    {
    public:
        NoEndpointsProvidedByServerError()
        : uafc::DiscoveryError("The server did not provide any endpoints")
        {}
    };

    class UAFC_EXPORT NoDiscoveryUrlsExposedByServerError : public uafc::DiscoveryError
    {
    public:
        NoDiscoveryUrlsExposedByServerError()
        : uafc::DiscoveryError("No discovery Urls are exposed by the server")
        {}

        NoDiscoveryUrlsExposedByServerError(const std::string& serverUri)
        : uafc::DiscoveryError(uaf::format("Server %s has been discovered, but there are no "
                                           "discovery URLs exposed by it", serverUri.c_str()))
        {}
    };

    class UAFC_EXPORT NoDiscoveryUrlsFoundError : public uafc::DiscoveryError
    {
    public:
        NoDiscoveryUrlsFoundError()
        : uafc::DiscoveryError("No discovery Urls were found")
        {}
    };



    class UAFC_EXPORT GetEndpointsError : public uafc::DiscoveryError
    {
    public:
        GetEndpointsError()
        : uafc::DiscoveryError("The GetEndpoints service failed")
        {}

        GetEndpointsError(const uaf::SdkStatus& sdkStatus)
        : uafc::DiscoveryError(uaf::format("The GetEndpoints service failed: %s", sdkStatus.toString().c_str())),
          sdkStatus(sdkStatus)
        {}

        uaf::SdkStatus sdkStatus;
    };





    class UAFC_EXPORT UnknownServerError : public uafc::DiscoveryError
    {
    public:
        UnknownServerError()
        : uafc::DiscoveryError("The requested server has not been discovered")
        {}

        UnknownServerError(const std::string& unknownServerUri)
        : uafc::DiscoveryError(uaf::format("No server with URI='%s' has been discovered", unknownServerUri.c_str())),
          unknownServerUri(unknownServerUri)
        {}

        std::string unknownServerUri;
    };


    class UAFC_EXPORT FindServersError : public uafc::DiscoveryError
    {
    public:
        FindServersError()
        : uafc::DiscoveryError("The FindServers service failed")
        {}

        FindServersError(
                const std::vector<uaf::SdkStatus>& sdkStatuses,
                int noOfFailed,
                int noOfUrls)
        : uafc::DiscoveryError(uaf::format("The FindServers service failed for %d out of %d urls",
                                           noOfFailed, noOfUrls)),
          sdkStatuses(sdkStatuses)
        {}

        std::vector<uaf::SdkStatus> sdkStatuses;
    };


    class UAFC_EXPORT NoParallelFindServersAllowedError : public uafc::DiscoveryError
    {
    public:
        NoParallelFindServersAllowedError()
        : uafc::DiscoveryError("The FindServers service is already being "
                               "invoked (no parallel invocations allowed)")
        {}
    };

}

#endif /* UAFC_DISCOVERYERRORS_H_ */
