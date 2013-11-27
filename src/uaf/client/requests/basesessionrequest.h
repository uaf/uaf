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

#ifndef UAFC_BASESESSIONREQUEST_H_
#define UAFC_BASESESSIONREQUEST_H_


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
#include "uaf/util/stringifiable.h"
#include "uaf/client/clientexport.h"
#include "uaf/util/handles.h"
#include "uaf/client/resolution/resolvable.h"
#include "uaf/client/requests/basesessionrequesttarget.h"
#include "uaf/client/configs/baseserviceconfig.h"
#include "uaf/client/configs/sessionconfig.h"


namespace uafc
{

    /*******************************************************************************************//**
    * A uafc::SessionRequest is a service request logically handled at the session level.
    *
    * @ingroup ClientRequests
    ***********************************************************************************************/
    template<typename _ServiceConfig, typename _Target, bool _Async>
    class UAFC_EXPORT BaseSessionRequest : public uaf::Stringifiable
    {
    public:


        // some public typedefs
        typedef _ServiceConfig ServiceConfigType;
        typedef _Target        TargetType;


        /**
         * Construct an empty session request.
         */
        BaseSessionRequest()
        : requestHandle_(uaf::REQUESTHANDLE_NOT_ASSIGNED)
        {}


        /**
         * Construct a session request with the specified number of targets.
         *
         * @param noOfTargets   The number of targets.
         * @param serviceConfig The service config.
         * @param sessionConfig The session config.
         */
        BaseSessionRequest(
                std::size_t                 noOfTargets,
                const _ServiceConfig&       serviceConfig = _ServiceConfig(),
                const uafc::SessionConfig&  sessionConfig = uafc::SessionConfig())
        : requestHandle_(uaf::REQUESTHANDLE_NOT_ASSIGNED),
          serviceConfig(serviceConfig),
          sessionConfig(sessionConfig),
          targets(noOfTargets)
        {}


        /**
         * Construct a session request with the specified number of targets.
         *
         * @param target        A single target.
         * @param serviceConfig The service config.
         * @param sessionConfig The session config.
         */
        BaseSessionRequest(
                const _Target&              target,
                const _ServiceConfig&       serviceConfig = _ServiceConfig(),
                const uafc::SessionConfig&  sessionConfig = uafc::SessionConfig())
        : requestHandle_(uaf::REQUESTHANDLE_NOT_ASSIGNED),
          serviceConfig(serviceConfig),
          sessionConfig(sessionConfig)
        { targets.push_back(target); }


        /**
         * Construct a session request with the specified number of targets.
         *
         * @param targets       The targets.
         * @param serviceConfig The service config.
         * @param sessionConfig The session config.
         */
        BaseSessionRequest(
                const typename std::vector<_Target>&    targets,
                const _ServiceConfig&                   serviceConfig = _ServiceConfig(),
                const uafc::SessionConfig&              sessionConfig = uafc::SessionConfig())
        : requestHandle_(uaf::REQUESTHANDLE_NOT_ASSIGNED),
          serviceConfig(serviceConfig),
          sessionConfig(sessionConfig),
          targets(targets)
        {}


        /** The targets. */
        typename std::vector<_Target> targets;

        /** Service settings to use. */
        _ServiceConfig serviceConfig;

        /** Session config to use */
        uafc::SessionConfig sessionConfig;

        /** Static attribute: is this an asynchronous request or not. */
        static const bool asynchronous = _Async;


        /**
         * Get the request handle of the request.
         *
         * This is implemented as a getter method (instead of a public data member) so that
         * the request handle is publicly visible, but only modifiable by friend classes.
         *
         * @return The request handle, as assigned by the UAF.
         */
        uaf::RequestHandle requestHandle() const { return requestHandle_; }


        /**
         * Get a string representation of the request.
         *
         * @return  String representation.
         */
        virtual std::string toString(const std::string& indent="", std::size_t colon=36) const
        {
            std::stringstream ss;

            ss << indent << " - requestHandle";
            ss << uaf::fillToPos(ss, colon);
            if (requestHandle_ == uaf::REQUESTHANDLE_NOT_ASSIGNED)
                ss << ": NOT_ASSIGNED\n";
            else
                ss << ": " << requestHandle_ << "\n";

            ss << indent << " - targets[]\n";
            for (std::size_t i = 0; i < targets.size(); i++)
            {
                ss << indent << "    - targets[" << i << "]";

                // append the target description in a nice way
                // (both for single and multi line strings)
                if (uaf::isMultiLine(targets[i].toString()))
                {
                    ss << "\n";
                    ss << targets[i].toString(indent + "      ", colon) << "\n";
                }
                else
                {
                    ss << uaf::fillToPos(ss, colon);
                    ss << ": " << targets[i].toString() << "\n";
                }
            }

            ss << indent << " - serviceConfig\n";
            ss << serviceConfig.toString(indent + "   ", colon) << "\n";
            ss << indent << " - sessionConfig\n";
            ss << sessionConfig.toString(indent + "   ", colon);

            return ss.str();
        }


        // comparison operators
        friend bool operator==(
                const BaseSessionRequest<_ServiceConfig, _Target, _Async>& object1,
                const BaseSessionRequest<_ServiceConfig, _Target, _Async>& object2)
        {
            if (object1.targets.size() != object2.targets.size())
                return false;

            for (std::size_t i = 0; i < object1.targets.size(); i++)
                if (object1.targets[i] != object2.targets[i])
                    return false;

            if (object1.serviceConfig != object2.serviceConfig)
                return false;

            if (object1.sessionConfig != object2.sessionConfig)
                return false;

            return true;
        }

        friend bool operator!=(
                const BaseSessionRequest<_ServiceConfig, _Target, _Async>& object1,
                const BaseSessionRequest<_ServiceConfig, _Target, _Async>& object2)
        {
            return !(object1 == object2);
        }

        friend bool operator<(
                const BaseSessionRequest<_ServiceConfig, _Target, _Async>& object1,
                const BaseSessionRequest<_ServiceConfig, _Target, _Async>& object2)
        {
            if (object1.targets.size() != object2.targets.size())
                return object1.targets.size() < object2.targets.size();

            if (object1.serviceConfig != object2.serviceConfig)
                return object1.serviceConfig < object2.serviceConfig;

            if (object1.sessionConfig != object2.sessionConfig)
                return object1.sessionConfig < object2.sessionConfig;

            return false;
        }


    private:


        // friend declarations
        friend class Client;
        friend class Resolver;
        friend class SessionFactory;


        // the UAF handle is private since it will be assigned by the "befriended" Client class
        uaf::RequestHandle requestHandle_;

    };

}


#endif /* UAFC_BASESESSIONREQUEST_H_ */
