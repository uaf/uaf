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


#ifndef UAF_GENERALERRORS_H_
#define UAF_GENERALERRORS_H_


// STD
#include <vector>
#include <string>
// SDK
// UAF
#include "uaf/util/sdkstatus.h"
#include "uaf/util/stringifiable.h"
#include "uaf/util/errors/uaferror.h"

namespace uaf
{

    class UAF_EXPORT GeneralError : public uaf::UafError
    {
    public:
        GeneralError()
        : uaf::UafError("General error")
        {}

        GeneralError(const std::string& description)
        : uaf::UafError(description)
        {}
    };


    class UAF_EXPORT WrongTypeError : public uaf::GeneralError
    {
    public:
        WrongTypeError()
        : uaf::GeneralError("Wrong type")
        {}
        WrongTypeError(const std::string& description)
        : uaf::GeneralError(description)
        {}
    };


    class UAF_EXPORT UnexpectedError : public uaf::GeneralError
    {
    public:
        UnexpectedError()
        : uaf::GeneralError("Unexpected error")
        {}

        UnexpectedError(const std::string& description)
        : uaf::GeneralError(description)
        {}
    };



    class UAF_EXPORT EmptyUrlError : public uaf::GeneralError
    {
    public:
        EmptyUrlError()
        : uaf::GeneralError("An empty URL was given")
        {}
    };


    class UAF_EXPORT PathNotExistsError : public uaf::GeneralError
    {
    public:
        PathNotExistsError()
        : uaf::GeneralError("Patn does not exist")
        {}


        PathNotExistsError(const std::string& path, const std::string& description="path")
        : uaf::GeneralError(uaf::format("The %s '%s' does not exist",
                                        description.c_str(), path.c_str()))
        {}
    };


    class UAF_EXPORT PathCreationError : public uaf::GeneralError
    {
    public:
        PathCreationError()
        : uaf::GeneralError("Patn could not be created")
        {}

        PathCreationError(const std::string& path, const std::string& description="path")
        : uaf::GeneralError(uaf::format("The %s '%s' could not be created",
                                        description.c_str(), path.c_str()))
        {}
    };

}

#endif /* UAF_GENERALERRORS_H_ */
