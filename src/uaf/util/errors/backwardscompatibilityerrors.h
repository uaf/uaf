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


#ifndef UAF_BACKWARDSCOMPATIBILITYERRORS_H_
#define UAF_BACKWARDSCOMPATIBILITYERRORS_H_


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

    /**
     * Instead of removing some errors of before UAF v2, we keep them as subclasses of this class.
     */
    class UAF_EXPORT BackwardsCompatibilityError : public uaf::UafError
    {
    public:
        BackwardsCompatibilityError()
        : uaf::UafError("This error is only kept for backwards compatibility. "
                        "It will never be raised by the UAF.")
        {}
    };




    class UAF_EXPORT DataFormatError        : public uaf::BackwardsCompatibilityError {};
    class UAF_EXPORT DataSizeError          : public uaf::BackwardsCompatibilityError {};
    class UAF_EXPORT DataSourceError        : public uaf::BackwardsCompatibilityError {};
    class UAF_EXPORT DisconnectionError     : public uaf::BackwardsCompatibilityError {};
    class UAF_EXPORT LowLevelError          : public uaf::BackwardsCompatibilityError {};
    class UAF_EXPORT OtherError             : public uaf::BackwardsCompatibilityError {};
    class UAF_EXPORT TimeoutError           : public uaf::BackwardsCompatibilityError {};
    class UAF_EXPORT NoResultReceivedError  : public uaf::BackwardsCompatibilityError {};
    class UAF_EXPORT UnknownHandleError     : public uaf::BackwardsCompatibilityError {};


}

#endif /* UAF_BACKWARDSCOMPATIBILITYERRORS_H_ */
