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


#ifndef UAF_RESOLUTIONERRORS_H_
#define UAF_RESOLUTIONERRORS_H_


// STD
#include <vector>
#include <string>
#include <sstream>
// SDK
// UAF
#include "uaf/util/sdkstatus.h"
#include "uaf/util/stringifiable.h"
#include "uaf/util/errors/uaferror.h"
#include "uaf/util/util.h"
#include "uaf/util/handles.h"

namespace uaf
{


    class UAF_EXPORT ResolutionError : public uaf::UafError
    {
    public:
        ResolutionError()
        : uaf::UafError("Resolution error")
        {}

        ResolutionError(const std::string& description)
        : uaf::UafError(description)
        {}
    };



    class UAF_EXPORT NotAllTargetsCouldBeResolvedError : public uaf::ResolutionError
    {
    public:
        NotAllTargetsCouldBeResolvedError()
        : uaf::ResolutionError("Could not convert all targets")
        {}

        NotAllTargetsCouldBeResolvedError(const std::vector<uint32_t>& unresolvedTargetNumbers)
        : unresolvedTargetNumbers(unresolvedTargetNumbers)
        {
            message = uaf::format("Could not convert the following targets: %s",
                                  uint32ArrayToString(unresolvedTargetNumbers).c_str());
        }

        std::vector<uint32_t> unresolvedTargetNumbers;
    };


    class UAF_EXPORT ServerArrayConversionError : public uaf::ResolutionError
    {
    public:
        ServerArrayConversionError()
        : uaf::ResolutionError("Could not convert the value received from the server to a server array")
        {}
    };



    class UAF_EXPORT NamespaceArrayConversionError : public uaf::ResolutionError
    {
    public:
        NamespaceArrayConversionError()
        : uaf::ResolutionError("Could not convert the value received from the server to a namespace array")
        {}
    };


    class UAF_EXPORT BadNamespaceArrayError : public uaf::ResolutionError
    {
    public:
        BadNamespaceArrayError()
        : uaf::ResolutionError("The namespace array received by the server has a Bad value")
        {}
    };


    class UAF_EXPORT BadServerArrayError : public uaf::ResolutionError
    {
    public:
        BadServerArrayError()
        : uaf::ResolutionError("The server array received by the server has a Bad value")
        {}
    };




    class UAF_EXPORT UnknownNamespaceUriError : public uaf::ResolutionError
    {
    public:
        UnknownNamespaceUriError()
        : uaf::ResolutionError("The namespace uri is not known"),
          unknownNamespaceUri("")
        {}

        UnknownNamespaceUriError(
                const std::string&                           unknownNamespaceUri,
                const std::map<NameSpaceIndex, std::string>& nameSpaceMap,
                const std::string&                           nameSpaceMapString
                )
        : uaf::ResolutionError(uaf::format("The namespace uri '%s' is not known.\n" \
                                           "This is the namespace map for the server:\n" \
                                           "%s",
                                           unknownNamespaceUri.c_str(),
                                           nameSpaceMapString.c_str())),
          unknownNamespaceUri(unknownNamespaceUri),
          nameSpaceMap(nameSpaceMap),
          nameSpaceMapString(nameSpaceMapString)
        {}

        std::string                             unknownNamespaceUri;
        std::map<NameSpaceIndex, std::string>   nameSpaceMap;
        std::string                             nameSpaceMapString;
    };


    class UAF_EXPORT EmptyServerUriError : public uaf::ResolutionError
    {
    public:
        EmptyServerUriError()
        : uaf::ResolutionError("The server uri is empty")
        {}
    };

    class UAF_EXPORT ExpandedNodeIdAddressExpectedError : public uaf::ResolutionError
    {
    public:
        ExpandedNodeIdAddressExpectedError()
        : uaf::ResolutionError("The given address should contain an ExpandedNodeId")
        {}
    };


    class UAF_EXPORT EmptyServerUriAndUnknownNamespaceIndexError : public uaf::ResolutionError
    {
    public:
        EmptyServerUriAndUnknownNamespaceIndexError()
        : uaf::ResolutionError("The server uri is empty and namespace index is unknown"),
          unknownNamespaceIndex(0)
        {}

        EmptyServerUriAndUnknownNamespaceIndexError(uaf::NameSpaceIndex unknownNamespaceIndex)
        : uaf::ResolutionError(uaf::format("The server uri is empty, and namespace index %d is not known", unknownNamespaceIndex)),
          unknownNamespaceIndex(unknownNamespaceIndex)
        {}

        uaf::NameSpaceIndex unknownNamespaceIndex;
    };


    class UAF_EXPORT NoNamespaceIndexOrUriGivenError : public uaf::ResolutionError
    {
    public:
        NoNamespaceIndexOrUriGivenError()
        : uaf::ResolutionError("No namespace index or URI were given")
        {}
    };


    class UAF_EXPORT UnknownServerIndexError : public uaf::ResolutionError
    {
    public:
        UnknownServerIndexError()
        : uaf::ResolutionError("The server index is not known"),
          unknownServerIndex(0)
        {}

        UnknownServerIndexError(uaf::ServerIndex unknownServerIndex)
        : uaf::ResolutionError(uaf::format("The server index %d is not known", unknownServerIndex)),
          unknownServerIndex(unknownServerIndex)
        {}

        uaf::ServerIndex unknownServerIndex;
    };


    class UAF_EXPORT UnknownNamespaceIndexError : public uaf::ResolutionError
    {
    public:
        UnknownNamespaceIndexError()
        : uaf::ResolutionError("The namespace index is not known"),
          unknownNamespaceIndex(0)
        {}

        UnknownNamespaceIndexError(uaf::NameSpaceIndex unknownNamespaceIndex)
        : uaf::ResolutionError(uaf::format("The namespace index %d is not known", unknownNamespaceIndex)),
          unknownNamespaceIndex(unknownNamespaceIndex)
        {}

        uaf::NameSpaceIndex unknownNamespaceIndex;
    };




    class UAF_EXPORT UnknownNamespaceIndexAndServerIndexError : public uaf::ResolutionError
    {
    public:
        UnknownNamespaceIndexAndServerIndexError()
        : uaf::ResolutionError("The namespace index is not known"),
          unknownNamespaceIndex(0),
          unknownServerIndex(0)
        {}

        UnknownNamespaceIndexAndServerIndexError(
                uaf::NameSpaceIndex unknownNamespaceIndex,
                uaf::ServerIndex    unknownServerIndex)
        : uaf::ResolutionError(
                uaf::format("The namespace index %d and server index %d is not known",
                            unknownNamespaceIndex,
                            unknownServerIndex)),
          unknownNamespaceIndex(unknownNamespaceIndex),
          unknownServerIndex(unknownServerIndex)
        {}

        uaf::NameSpaceIndex unknownNamespaceIndex;
        uaf::ServerIndex unknownServerIndex;
    };



    class UAF_EXPORT InvalidAddressError : public uaf::ResolutionError
    {
    public:
        InvalidAddressError()
        : uaf::ResolutionError("Invalid address")
        {}
    };

    class UAF_EXPORT MultipleTranslationResultsError : public uaf::ResolutionError
    {
    public:
        MultipleTranslationResultsError()
        : uaf::ResolutionError("Multiple nodes were found when translating the given browsepath")
        {}
    };



}

#endif /* UAF_RESOLUTIONERRORS_H_ */
