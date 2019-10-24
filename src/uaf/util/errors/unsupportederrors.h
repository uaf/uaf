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

#ifndef UAF_UNSUPPORTEDERRORS_H
#define UAF_UNSUPPORTEDERRORS_H

// STD
#include <string>
// SDK
#include "uabasecpp/statuscode.h"
// UAF
#include "uaf/util/errors/uaferror.h"



namespace uaf
{

    class UAF_EXPORT UnsupportedError : public uaf::UafError
    {
    public:
        UnsupportedError()
        : uaf::UafError("UnsupportedError")
        {}

        UnsupportedError(const std::string& description)
        : uaf::UafError(description)
        {}

    };


    class UAF_EXPORT UnsupportedNodeIdIdentifierTypeError : public uaf::UnsupportedError
    {
    public:
        UnsupportedNodeIdIdentifierTypeError()
        : uaf::UnsupportedError("The given NodeId identifier type is not supported")
        {}
    };


    class UAF_EXPORT SyncInvocationNotSupportedError : public uaf::UnsupportedError
    {
    public:
        SyncInvocationNotSupportedError()
        : uaf::UnsupportedError("Synchronous invocation is not supported")
        {}
    };

    class UAF_EXPORT AsyncInvocationNotSupportedError : public uaf::UnsupportedError
    {
    public:
        AsyncInvocationNotSupportedError()
        : uaf::UnsupportedError("Asynchronous invocation is not supported")
        {}
    };


    class UAF_EXPORT AsyncInvocationOnMultipleSessionsNotSupportedError : public uaf::UnsupportedError
    {
    public:
        AsyncInvocationOnMultipleSessionsNotSupportedError()
        : uaf::UnsupportedError("Asynchronous invocation on multiple sessions is not supported")
        {}
    };


    class UAF_EXPORT AsyncMultiMethodCallNotSupportedError : public uaf::UnsupportedError
    {
    public:
        AsyncMultiMethodCallNotSupportedError()
        : uaf::UnsupportedError("Asynchronous multiple method calls are not supported")
        {}
    };

}



#endif /* UAF_UNSUPPORTEDERRORS_H */
