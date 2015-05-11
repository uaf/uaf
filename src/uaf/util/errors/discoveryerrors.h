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


#ifndef UAF_DISCOVERYERRORS_H_
#define UAF_DISCOVERYERRORS_H_


// STD
#include <vector>
#include <string>
// SDK
// UAF
#include "uaf/util/sdkstatus.h"
#include "uaf/util/stringifiable.h"
#include "uaf/util/errors/invalidrequesterror.h"
#include "uaf/client/clientexport.h"

namespace uaf
{


    class UAF_EXPORT DiscoveryError : public uaf::InvalidRequestError
    {
    public:
        DiscoveryError()
        : uaf::InvalidRequestError("Discovery error")
        {}

        DiscoveryError(const std::string& description)
        : uaf::InvalidRequestError(description)
        {}
    };





    class UAF_EXPORT NoEndpointsProvidedByServerError : public uaf::DiscoveryError
    {
    public:
        NoEndpointsProvidedByServerError()
        : uaf::DiscoveryError("The server did not provide any endpoints")
        {}
    };

    class UAF_EXPORT NoDiscoveryUrlsExposedByServerError : public uaf::DiscoveryError
    {
    public:
        NoDiscoveryUrlsExposedByServerError()
        : uaf::DiscoveryError("No discovery Urls are exposed by the server")
        {}

        NoDiscoveryUrlsExposedByServerError(const std::string& serverUri)
        : uaf::DiscoveryError(uaf::format("Server %s has been discovered, but there are no "
                                           "discovery URLs exposed by it", serverUri.c_str()))
        {}
    };

    class UAF_EXPORT NoDiscoveryUrlsFoundError : public uaf::DiscoveryError
    {
    public:
        NoDiscoveryUrlsFoundError()
        : uaf::DiscoveryError("No discovery Urls were found")
        {}
    };



    class UAF_EXPORT GetEndpointsError : public uaf::DiscoveryError
    {
    public:
        GetEndpointsError()
        : uaf::DiscoveryError("The GetEndpoints service failed")
        {}

        GetEndpointsError(const uaf::SdkStatus& sdkStatus)
        : uaf::DiscoveryError(uaf::format("The GetEndpoints service failed: %s", sdkStatus.toString().c_str())),
          sdkStatus(sdkStatus)
        {}

        uaf::SdkStatus sdkStatus;
    };





    class UAF_EXPORT UnknownServerError : public uaf::DiscoveryError
    {
    public:
        UnknownServerError()
        : uaf::DiscoveryError("The requested server has not been discovered")
        {}

        UnknownServerError(const std::string& unknownServerUri, std::vector<std::string> knownServerUris)
        : uaf::DiscoveryError(),
          unknownServerUri(unknownServerUri),
          knownServerUris(knownServerUris)
        {
            std::stringstream ss;
            ss << "No server with URI='" << unknownServerUri.c_str() << "' has been discovered." << std::endl;
            if (knownServerUris.size() == 0)
            {
                ss << "The client could not discover a single server.";
            }
            else
            {
                ss << "Only the following server URIs have been discovered:";
                for (std::vector<std::string>::const_iterator it = knownServerUris.begin();
                        it != knownServerUris.end();
                        ++it)
                {
                    ss << std::endl << " - " << *it;
                }
            }

            message = ss.str();
        }

        std::string unknownServerUri;
        std::vector<std::string> knownServerUris;
    };


    class UAF_EXPORT FindServersError : public uaf::DiscoveryError
    {
    public:
        FindServersError()
        : uaf::DiscoveryError("The FindServers service failed")
        {}

        FindServersError(
                const std::vector<uaf::SdkStatus>& sdkStatuses,
                int noOfFailed,
                int noOfUrls)
        : uaf::DiscoveryError(uaf::format("The FindServers service failed for %d out of %d urls",
                                           noOfFailed, noOfUrls)),
          sdkStatuses(sdkStatuses)
        {}

        std::vector<uaf::SdkStatus> sdkStatuses;
    };


    class UAF_EXPORT NoParallelFindServersAllowedError : public uaf::DiscoveryError
    {
    public:
        NoParallelFindServersAllowedError()
        : uaf::DiscoveryError("The FindServers service is already being "
                               "invoked (no parallel invocations allowed)")
        {}
    };

}

#endif /* UAF_DISCOVERYERRORS_H_ */
