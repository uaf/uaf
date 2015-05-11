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


#ifndef UAF_SUBSCRIPTIONERRORS_H_
#define UAF_SUBSCRIPTIONERRORS_H_


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

    class UAF_EXPORT SubscriptionError : public uaf::UafError
    {
    public:
        SubscriptionError()
        : uaf::UafError("Subscription error")
        {}
        SubscriptionError(const std::string& description)
        : uaf::UafError(description)
        {}

    };

    class UAF_EXPORT SubscriptionNotCreatedError : public uaf::SubscriptionError
    {
    public:
        SubscriptionNotCreatedError()
        : uaf::SubscriptionError("The subscription is not created")
        {}

    };


    class UAF_EXPORT CouldNotManuallySubscribeError : public uaf::SubscriptionError
    {
    public:
        CouldNotManuallySubscribeError()
        : uaf::SubscriptionError("Could not manually subscribe")
        {}

    };


    class UAF_EXPORT CouldNotManuallyUnsubscribeError : public uaf::SubscriptionError
    {
    public:
        CouldNotManuallyUnsubscribeError()
        : uaf::SubscriptionError("Could not manually unsubscribe")
        {}
    };



    class UAF_EXPORT SubscriptionHasBeenDeletedError : public uaf::SubscriptionError
    {
    public:
        SubscriptionHasBeenDeletedError()
        : uaf::SubscriptionError("The subscription has been deleted")
        {}
    };



    class UAF_EXPORT CreateSubscriptionError : public uaf::SubscriptionError
    {
    public:
        CreateSubscriptionError()
        : uaf::SubscriptionError("Could not create the subscription")
        {}

        CreateSubscriptionError(const uaf::SdkStatus& sdkStatus)
        : uaf::SubscriptionError(uaf::format("Could not create the subscription: %s",
                                             sdkStatus.toString().c_str())),
          sdkStatus(sdkStatus)
        {}

        uaf::SdkStatus sdkStatus;
    };


    class UAF_EXPORT DeleteSubscriptionError : public uaf::SubscriptionError
    {
    public:
        DeleteSubscriptionError()
        : uaf::SubscriptionError("Could not delete the subscription")
        {}

        DeleteSubscriptionError(const uaf::SdkStatus& sdkStatus)
        : uaf::SubscriptionError(uaf::format("Could not delete the subscription: %s",
                                             sdkStatus.toString().c_str())),
          sdkStatus(sdkStatus)
        {}

        uaf::SdkStatus sdkStatus;
    };


}

#endif /* UAF_SUBSCRIPTIONERRORS_H_ */
