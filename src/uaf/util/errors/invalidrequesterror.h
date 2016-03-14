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

#ifndef UAF_INVALIDREQUESTERROR_H
#define UAF_INVALIDREQUESTERROR_H

// STD
#include <string>
// SDK
#include "uabase/statuscode.h"
// UAF
#include "uaf/util/errors/uaferror.h"



namespace uaf
{

    class UAF_EXPORT InvalidRequestError : public uaf::UafError
    {
    public:
        InvalidRequestError()
        : uaf::UafError("InvalidRequestError")
        {}
        InvalidRequestError(const std::string& description)
        : uaf::UafError(description)
        {}

    };


    class UAF_EXPORT DataDontMatchAddressesError : public uaf::InvalidRequestError
    {
    public:
        DataDontMatchAddressesError()
        : uaf::InvalidRequestError("The data don't match the addresses")
        {}
    };

    class UAF_EXPORT ContinuationPointsDontMatchAddressesError : public uaf::InvalidRequestError
    {
    public:
        ContinuationPointsDontMatchAddressesError()
        : uaf::InvalidRequestError("The continuation points don't match the addresses")
        {}
    };

    class UAF_EXPORT NoTargetsGivenError : public uaf::InvalidRequestError
    {
    public:
        NoTargetsGivenError()
        : uaf::InvalidRequestError("No targets are given")
        {}
    };

    class UAF_EXPORT NoStatusesGivenError : public uaf::InvalidRequestError
    {
    public:
        NoStatusesGivenError()
        : uaf::InvalidRequestError("No statuses are given")
        {}
    };

    class UAF_EXPORT InvalidServerUriError : public uaf::InvalidRequestError
    {
    public:
        InvalidServerUriError()
        : uaf::InvalidRequestError("The server URI is invalid")
        {}

        InvalidServerUriError(const std::string& invalidServerUri)
        : uaf::InvalidRequestError(uaf::format("The server URI '%s' is invalid", invalidServerUri.c_str())),
          invalidServerUri(invalidServerUri)
        {}
        std::string invalidServerUri;
    };

    class UAF_EXPORT BadStatusesPresentError : public uaf::InvalidRequestError
    {
    public:
        BadStatusesPresentError()
        : uaf::InvalidRequestError("Bad statuses are present"),
          noOfGood(0),
          noOfUncertain(0),
          noOfBad(0)
        {}

        BadStatusesPresentError(uint32_t noOfGood, uint32_t noOfUncertain, uint32_t noOfBad)
        : uaf::InvalidRequestError("Bad statuses are present"),
          noOfGood(noOfGood),
          noOfUncertain(noOfUncertain),
          noOfBad(noOfBad)
        {}

        uint32_t noOfGood;
        uint32_t noOfUncertain;
        uint32_t noOfBad;
    };

    class UAF_EXPORT ItemNotFoundForTheGivenHandleError : public uaf::InvalidRequestError
    {
    public:
        ItemNotFoundForTheGivenHandleError()
        : uaf::InvalidRequestError("No item was found for the given handle")
        {}
    };

    class UAF_EXPORT TargetRankOutOfBoundsError : public uaf::InvalidRequestError
    {
    public:
        TargetRankOutOfBoundsError()
        : uaf::InvalidRequestError("The target rank is out of bounds"),
          targetRank(0),
          noOfTargets(0)
        {}

        TargetRankOutOfBoundsError(uint32_t targetRank, uint32_t noOfTargets)
        : uaf::InvalidRequestError(
                uaf::format("The target rank %d is out of bounds (total number of targets: %d)",
                            targetRank, noOfTargets)),
          targetRank(targetRank),
          noOfTargets(noOfTargets)
        {}

        uint32_t targetRank;
        uint32_t noOfTargets;
    };

    class UAF_EXPORT NoItemFoundForTheGivenRequestHandleError : public uaf::InvalidRequestError
    {
    public:
        NoItemFoundForTheGivenRequestHandleError()
        : uaf::InvalidRequestError("No item was found for the given request handle"),
          requestHandle(0)
        {}

        NoItemFoundForTheGivenRequestHandleError(uaf::RequestHandle requestHandle)
        : uaf::InvalidRequestError(
                uaf::format("No item was found for the given request handle (%d)",
                            requestHandle)),
          requestHandle(requestHandle)
        {}

        uaf::RequestHandle requestHandle;
    };


    class UAF_EXPORT EmptyAddressError : public uaf::InvalidRequestError
    {
    public:
        EmptyAddressError()
        : uaf::InvalidRequestError("The address is empty (no valid NodeId or BrowsePath)")
        {}
    };


    class UAF_EXPORT UnknownClientSubscriptionHandleError : public uaf::InvalidRequestError
    {
    public:
        UnknownClientSubscriptionHandleError()
        : uaf::InvalidRequestError("Unknown client subscription handle"),
          unknownClientSubscriptionHandle(0)
        {}

        UnknownClientSubscriptionHandleError(uaf::ClientSubscriptionHandle unknownClientSubscriptionHandle)
        : uaf::InvalidRequestError(
                uaf::format("Unknown client handle (%d)",
                            unknownClientSubscriptionHandle)),
          unknownClientSubscriptionHandle(unknownClientSubscriptionHandle)
        {}

        uaf::ClientSubscriptionHandle unknownClientSubscriptionHandle;
    };




    class UAF_EXPORT UnknownClientHandleError : public uaf::InvalidRequestError
    {
    public:
        UnknownClientHandleError()
        : uaf::InvalidRequestError("Unknown client handle"),
          unknownClientHandle(0)
        {}

        UnknownClientHandleError(uaf::ClientHandle unknownClientHandle)
        : uaf::InvalidRequestError(uaf::format("Unknown client handle (%d)", unknownClientHandle)),
          unknownClientHandle(unknownClientHandle)
        {}

        uaf::ClientHandle unknownClientHandle;
    };


    class UAF_EXPORT UnknownClientConnectionIdError : public uaf::InvalidRequestError
    {
    public:
        UnknownClientConnectionIdError()
        : uaf::InvalidRequestError("Unknown client connection id"),
          unknownClientConnectionId(0)
        {}

        UnknownClientConnectionIdError(uaf::ClientHandle unknownClientConnectionId)
        : uaf::InvalidRequestError(uaf::format("Unknown client connection id (%d)", unknownClientConnectionId)),
          unknownClientConnectionId(unknownClientConnectionId)
        {}

        uaf::ClientConnectionId unknownClientConnectionId;
    };


    class UAF_EXPORT DefinitionNotFoundError : public uaf::InvalidRequestError
    {
    public:
    	DefinitionNotFoundError()
        : uaf::InvalidRequestError("No valid definition was found")
        {}
    };
}



#endif /* UAF_INVALIDREQUESTERROR_H */
