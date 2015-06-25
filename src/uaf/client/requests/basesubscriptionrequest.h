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

#ifndef UAF_BASESUBSCRIPTIONREQUEST_H_
#define UAF_BASESUBSCRIPTIONREQUEST_H_


// STD
#include <vector>
#include <string>
// SDK
#include "uaclient/uaclientsdk.h"
// UAF
#include "uaf/util/logger.h"
#include "uaf/util/status.h"
#include "uaf/util/variant.h"
#include "uaf/util/address.h"
#include "uaf/client/clientexport.h"
#include "uaf/client/requests/basesubscriptionrequesttarget.h"
#include "uaf/client/requests/basesessionrequest.h"
#include "uaf/client/settings/subscriptionsettings.h"

namespace uaf
{


    /*******************************************************************************************//**
    * A uaf::BaseSubscriptionRequest is a service request logically handled at the subscription
    * level.
    *
    * @ingroup ClientRequests
    ***********************************************************************************************/
    template<typename _ServiceSettings, typename _Target, bool _Async>
    class UAF_EXPORT BaseSubscriptionRequest
    : public uaf::BaseSessionRequest<_ServiceSettings, _Target, _Async>
    {
    public:

        typedef _ServiceSettings  ServiceSettingsType;
        typedef _Target     TargetType;

        friend class Client;
        friend class SessionFactory;



        /**
         * Construct an empty subscription request.
         */
        BaseSubscriptionRequest()
        : uaf::BaseSessionRequest<_ServiceSettings, _Target, _Async>(),
          subscriptionSettingsGiven(false)
        {}


        /**
         * Construct a subscription request with the specified number of targets.
         *
         * @param noOfTargets           The number of targets.
         */
        BaseSubscriptionRequest(std::size_t noOfTargets)
        : uaf::BaseSessionRequest<_ServiceSettings, _Target, _Async>(noOfTargets),
          subscriptionSettingsGiven(false)
        {}


        /**
         * Construct a subscription request with the specified number of targets.
         *
         * @param noOfTargets           The number of targets.
         * @param serviceSettings         The service settings.
         * @param sessionSettings         The session settings.
         * @param subscriptionSettings    The subscription settings.
         */
        BaseSubscriptionRequest(
                std::size_t                         noOfTargets,
                const _ServiceSettings&             serviceSettings,
                const uaf::SessionSettings&         sessionSettings,
                const uaf::SubscriptionSettings&    subscriptionSettings)
        : uaf::BaseSessionRequest<_ServiceSettings, _Target, _Async>(
                noOfTargets,
                serviceSettings,
                sessionSettings),
          subscriptionSettings(subscriptionSettings),
          subscriptionSettingsGiven(true)
        {}


        /**
         * Construct a subscription request for a single target.
         *
         * @param target                The only target of the request.
         * @param serviceSettings         The service settings.
         * @param sessionSettings         The session settings.
         * @param subscriptionSettings    The subscription settings.
         */
        BaseSubscriptionRequest(
                const _Target&                      target,
                const _ServiceSettings&             serviceSettings,
                const uaf::SessionSettings&         sessionSettings,
                const uaf::SubscriptionSettings&    subscriptionSettings)
        : uaf::BaseSessionRequest<_ServiceSettings, _Target, _Async>(
                target,
                serviceSettings,
                sessionSettings),
          subscriptionSettings(subscriptionSettings),
          subscriptionSettingsGiven(true)
        {}


        /**
         * Construct a subscription request for multiple targets.
         *
         * @param targets               The targets of the request.
         * @param serviceSettings         The service settings.
         * @param sessionSettings         The session settings.
         * @param subscriptionSettings    The subscription settings.
         */
        BaseSubscriptionRequest(
                const typename std::vector<_Target>&    targets,
                const _ServiceSettings&                   serviceSettings      = _ServiceSettings(),
                const uaf::SessionSettings&              sessionSettings       = uaf::SessionSettings(),
                const uaf::SubscriptionSettings&         subscriptionSettings  = uaf::SubscriptionSettings())
        : uaf::BaseSessionRequest<_ServiceSettings, _Target, _Async>(
                targets,
                serviceSettings,
                sessionSettings),
          subscriptionSettings(subscriptionSettings)
        {}



        /** Session settings to use. */
        uaf::SubscriptionSettings subscriptionSettings;

        bool subscriptionSettingsGiven;

        /**
         * Get a string representation of the request.
         *
         * @return  String representation.
         */
        std::string toString(const std::string& indent="", std::size_t colon=36) const
        {
            std::stringstream ss;

            ss << uaf::BaseSessionRequest<_ServiceSettings, _Target, _Async>::toString(indent, colon);
            ss << "\n";

            ss << indent << " - subscriptionSettingsGiven";
            ss << uaf::fillToPos(ss, colon);
            ss << ": " << (subscriptionSettingsGiven ? "true" : "false") << "\n";

            ss << indent << " - subscriptionSettings\n";
            ss << subscriptionSettings.toString(indent + "   ", colon);

            return ss.str();
        }


        // comparison operators
        friend bool operator==(
                const BaseSubscriptionRequest<_ServiceSettings, _Target, _Async>& object1,
                const BaseSubscriptionRequest<_ServiceSettings, _Target, _Async>& object2)
        {
            if (   (uaf::BaseSessionRequest<_ServiceSettings, _Target, _Async>&)object1
                != (uaf::BaseSessionRequest<_ServiceSettings, _Target, _Async>&)object2)
                return false;

            if (object1.subscriptionSettingsGiven != object2.subscriptionSettingsGiven)
                return false;

            if (object1.subscriptionSettings != object2.subscriptionSettings)
                return false;

            return true;
        }


        friend bool operator!=(
                const BaseSubscriptionRequest<_ServiceSettings, _Target, _Async>& object1,
                const BaseSubscriptionRequest<_ServiceSettings, _Target, _Async>& object2)
        {
            return !(object1 == object2);
        }


        friend bool operator<(
                const BaseSubscriptionRequest<_ServiceSettings, _Target, _Async>& object1,
                const BaseSubscriptionRequest<_ServiceSettings, _Target, _Async>& object2)
        {
            if (   (uaf::BaseSessionRequest<_ServiceSettings, _Target, _Async>&)object1
                != (uaf::BaseSessionRequest<_ServiceSettings, _Target, _Async>&)object2)
                return   (uaf::BaseSessionRequest<_ServiceSettings, _Target, _Async>&)object1
                       < (uaf::BaseSessionRequest<_ServiceSettings, _Target, _Async>&)object2;

            if (object1.subscriptionSettingsGiven != object2.subscriptionSettingsGiven)
                return object1.subscriptionSettingsGiven < object2.subscriptionSettingsGiven;
            else if (object1.subscriptionSettings != object2.subscriptionSettings)
                return object1.subscriptionSettings < object2.subscriptionSettings;

            return false;
        }


    private:


    };







}


#endif /* UAF_BASESUBSCRIPTIONREQUEST_H_ */
