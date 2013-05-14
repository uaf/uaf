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

#ifndef UAFC_BASESUBSCRIPTIONREQUEST_H_
#define UAFC_BASESUBSCRIPTIONREQUEST_H_


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
#include "uaf/client/configs/subscriptionconfig.h"

namespace uafc
{


    /*******************************************************************************************//**
    * A uafc::BaseSubscriptionRequest is a service request logically handled at the subscription
    * level.
    *
    * @ingroup ClientRequests
    ***********************************************************************************************/
    template<typename _ServiceConfig, typename _Target, bool _Async>
    class UAFC_EXPORT BaseSubscriptionRequest
    : public uafc::BaseSessionRequest<_ServiceConfig, _Target, _Async>
    {
    public:

        typedef _ServiceConfig  ServiceConfigType;
        typedef _Target     TargetType;

        friend class Client;
        friend class SessionFactory;



        /**
         * Construct an empty subscription request.
         */
        BaseSubscriptionRequest()
        : uafc::BaseSessionRequest<_ServiceConfig, _Target, _Async>()
        {}


        /**
         * Construct a subscription request with the specified number of targets.
         *
         * @param noOfTargets           The number of targets.
         * @param serviceConfig         The service config.
         * @param sessionConfig         The session config.
         * @param subscriptionConfig    The subscription config.
         */
        BaseSubscriptionRequest(
                std::size_t                     noOfTargets,
                const _ServiceConfig&           serviceConfig       = _ServiceConfig(),
                const uafc::SessionConfig&      sessionConfig       = uafc::SessionConfig(),
                const uafc::SubscriptionConfig& subscriptionConfig  = uafc::SubscriptionConfig())
        : uafc::BaseSessionRequest<_ServiceConfig, _Target, _Async>(
                noOfTargets,
                serviceConfig,
                sessionConfig),
          subscriptionConfig(subscriptionConfig)
        {}


        /**
         * Construct a subscription request for a single target.
         *
         * @param target                The only target of the request.
         * @param serviceConfig         The service config.
         * @param sessionConfig         The session config.
         * @param subscriptionConfig    The subscription config.
         */
        BaseSubscriptionRequest(
                const _Target&                  target,
                const _ServiceConfig&           serviceConfig       = _ServiceConfig(),
                const uafc::SessionConfig&      sessionConfig       = uafc::SessionConfig(),
                const uafc::SubscriptionConfig& subscriptionConfig  = uafc::SubscriptionConfig())
        : uafc::BaseSessionRequest<_ServiceConfig, _Target, _Async>(
                target,
                serviceConfig,
                sessionConfig),
          subscriptionConfig(subscriptionConfig)
        {}


        /**
         * Construct a subscription request for multiple targets.
         *
         * @param targets               The targets of the request.
         * @param serviceConfig         The service config.
         * @param sessionConfig         The session config.
         * @param subscriptionConfig    The subscription config.
         */
        BaseSubscriptionRequest(
                const typename std::vector<_Target>&    targets,
                const _ServiceConfig&                   serviceConfig       = _ServiceConfig(),
                const uafc::SessionConfig&              sessionConfig       = uafc::SessionConfig(),
                const uafc::SubscriptionConfig&         subscriptionConfig  = uafc::SubscriptionConfig())
        : uafc::BaseSessionRequest<_ServiceConfig, _Target, _Async>(
                targets,
                serviceConfig,
                sessionConfig),
          subscriptionConfig(subscriptionConfig)
        {}



        /** Session settings to use. */
        uafc::SubscriptionConfig subscriptionConfig;


        /**
         * Get a string representation of the request.
         *
         * @return  String representation.
         */
        virtual std::string toString(const std::string& indent="", std::size_t colon=36) const
        {
            std::stringstream ss;

            ss << uafc::BaseSessionRequest<_ServiceConfig, _Target, _Async>::toString(indent, colon);
            ss << "\n";
            ss << indent << " - subscriptionConfig\n";
            ss << subscriptionConfig.toString(indent + "   ", colon);

            return ss.str();
        }


        // comparison operators
        friend bool operator==(
                const BaseSubscriptionRequest<_ServiceConfig, _Target, _Async>& object1,
                const BaseSubscriptionRequest<_ServiceConfig, _Target, _Async>& object2)
        {
            if (   (uafc::BaseSessionRequest<_ServiceConfig, _Target, _Async>&)object1
                != (uafc::BaseSessionRequest<_ServiceConfig, _Target, _Async>&)object2)
                return false;

            if (object1.subscriptionConfig != object2.subscriptionConfig)
                return false;

            return true;
        }


        friend bool operator!=(
                const BaseSubscriptionRequest<_ServiceConfig, _Target, _Async>& object1,
                const BaseSubscriptionRequest<_ServiceConfig, _Target, _Async>& object2)
        {
            return !(object1 == object2);
        }


        friend bool operator<(
                const BaseSubscriptionRequest<_ServiceConfig, _Target, _Async>& object1,
                const BaseSubscriptionRequest<_ServiceConfig, _Target, _Async>& object2)
        {
            if (   (uafc::BaseSessionRequest<_ServiceConfig, _Target, _Async>&)object1
                != (uafc::BaseSessionRequest<_ServiceConfig, _Target, _Async>&)object2)
                return   (uafc::BaseSessionRequest<_ServiceConfig, _Target, _Async>&)object1
                       < (uafc::BaseSessionRequest<_ServiceConfig, _Target, _Async>&)object2;

            if (object1.subscriptionConfig != object2.subscriptionConfig)
                return object1.subscriptionConfig < object2.subscriptionConfig;

            return false;
        }


    private:


    };







}


#endif /* UAFC_BASESUBSCRIPTIONREQUEST_H_ */
