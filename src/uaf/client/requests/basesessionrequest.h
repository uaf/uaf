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

#ifndef UAF_BASESESSIONREQUEST_H_
#define UAF_BASESESSIONREQUEST_H_


// STD
#include <vector>
#include <string>
// SDK
#include "uaclientcpp/uaclientsdk.h"
// UAF
#include "uaf/util/logger.h"
#include "uaf/util/status.h"
#include "uaf/util/variant.h"
#include "uaf/util/address.h"
#include "uaf/util/stringifiable.h"
#include "uaf/client/clientexport.h"
#include "uaf/util/handles.h"
#include "uaf/util/constants.h"
#include "uaf/client/resolution/resolvable.h"
#include "uaf/client/requests/basesessionrequesttarget.h"
#include "uaf/client/settings/sessionsettings.h"
#include "uaf/client/settings/translatebrowsepathstonodeidssettings.h"


namespace uaf
{

    /*******************************************************************************************//**
    * A uaf::SessionRequest is a service request logically handled at the session level.
    *
    * @ingroup ClientRequests
    ***********************************************************************************************/
    template<typename _ServiceSettings, typename _Target, bool _Async>
    class UAF_EXPORT BaseSessionRequest
    {
    public:


        // some public typedefs
        typedef _ServiceSettings ServiceSettingsType;
        typedef _Target          TargetType;


        /**
         * Construct an empty session request.
         */
        BaseSessionRequest()
        : clientConnectionIdGiven(false),
          serviceSettingsGiven(false),
          translateSettingsGiven(false),
          sessionSettingsGiven(false),
          clientConnectionId(uaf::constants::CLIENTHANDLE_NOT_ASSIGNED),
          requestHandle_(uaf::constants::REQUESTHANDLE_NOT_ASSIGNED)
        {}


        /**
         * Construct an empty session request.
         *
         * @param noOfTargets   The number of targets.
         */
        BaseSessionRequest(
                std::size_t                                       noOfTargets,
                uaf::ClientConnectionId                           clientConnectionId  = uaf::constants::CLIENTHANDLE_NOT_ASSIGNED,
                const _ServiceSettings*                           serviceSettings     = NULL,
                const uaf::TranslateBrowsePathsToNodeIdsSettings* translateSettings   = NULL,
                const uaf::SessionSettings*                       sessionSettings     = NULL)
        : targets(noOfTargets),
          clientConnectionIdGiven(clientConnectionId != uaf::constants::CLIENTHANDLE_NOT_ASSIGNED),
          serviceSettingsGiven(serviceSettings != NULL),
          translateSettingsGiven(translateSettings != NULL),
          sessionSettingsGiven(sessionSettings != NULL),
          requestHandle_(uaf::constants::REQUESTHANDLE_NOT_ASSIGNED)
        {
            if (clientConnectionId != uaf::constants::CLIENTHANDLE_NOT_ASSIGNED)
                this->clientConnectionId = clientConnectionId;
            if (serviceSettings != NULL)
                this->serviceSettings = *serviceSettings;
            if (translateSettings != NULL)
                this->translateSettings = *translateSettings;
            if (sessionSettings != NULL)
                this->sessionSettings = *sessionSettings;
        }


        /**
         * Construct an empty session request.
         *
         * @param noOfTargets   The number of targets.
         */
        BaseSessionRequest(
                const _Target&                                    target,
                uaf::ClientConnectionId                           clientConnectionId  = uaf::constants::CLIENTHANDLE_NOT_ASSIGNED,
                const _ServiceSettings*                           serviceSettings     = NULL,
                const uaf::TranslateBrowsePathsToNodeIdsSettings* translateSettings   = NULL,
                const uaf::SessionSettings*                       sessionSettings     = NULL)
        : clientConnectionIdGiven(clientConnectionId != uaf::constants::CLIENTHANDLE_NOT_ASSIGNED),
          serviceSettingsGiven(serviceSettings != NULL),
          translateSettingsGiven(translateSettings != NULL),
          sessionSettingsGiven(sessionSettings != NULL),
          requestHandle_(uaf::constants::REQUESTHANDLE_NOT_ASSIGNED)
        {
            targets.push_back(target);

            if (clientConnectionId != uaf::constants::CLIENTHANDLE_NOT_ASSIGNED)
                this->clientConnectionId = clientConnectionId;
            if (serviceSettings != NULL)
                this->serviceSettings = *serviceSettings;
            if (translateSettings != NULL)
                this->translateSettings = *translateSettings;
            if (sessionSettings != NULL)
                this->sessionSettings = *sessionSettings;
        }


        /**
         * Construct an empty session request.
         *
         * @param noOfTargets   The number of targets.
         */
        BaseSessionRequest(
                const typename std::vector<_Target>&              targets,
                uaf::ClientConnectionId                           clientConnectionId  = uaf::constants::CLIENTHANDLE_NOT_ASSIGNED,
                const _ServiceSettings*                           serviceSettings     = NULL,
                const uaf::TranslateBrowsePathsToNodeIdsSettings* translateSettings   = NULL,
                const uaf::SessionSettings*                       sessionSettings     = NULL)
        : targets(targets),
          clientConnectionIdGiven(clientConnectionId != uaf::constants::CLIENTHANDLE_NOT_ASSIGNED),
          serviceSettingsGiven(serviceSettings != NULL),
          translateSettingsGiven(translateSettings != NULL),
          sessionSettingsGiven(sessionSettings != NULL),
          requestHandle_(uaf::constants::REQUESTHANDLE_NOT_ASSIGNED)
        {
            if (clientConnectionId != uaf::constants::CLIENTHANDLE_NOT_ASSIGNED)
                this->clientConnectionId = clientConnectionId;
            if (serviceSettings != NULL)
                this->serviceSettings = *serviceSettings;
            if (translateSettings != NULL)
                this->translateSettings = *translateSettings;
            if (sessionSettings != NULL)
                this->sessionSettings = *sessionSettings;
        }


        /** The targets. */
        typename std::vector<_Target> targets;

        bool clientConnectionIdGiven;

        /** True if the serviceSettings are given, false if not. */
        bool serviceSettingsGiven;

        /** True if the translateSettings are given, false if not. */
        bool translateSettingsGiven;

        bool sessionSettingsGiven;

        /**
         * The ClientConnectionId, identifying the session to invoke the request.
         * Only used if connectionPolicy equals uaf::sessionpolicies::KnownClientConnectionId.
         */
        uaf::ClientConnectionId clientConnectionId;


        /** Service settings to invoke the request, if serviceSettingsGiven is true.
         *  If serviceSettingsGiven is false, then the default service settings will be used
         *  (as can be configured by uaf::Client::setClientSettings). */
        _ServiceSettings serviceSettings;

        /** If translateSettingsGiven is true, then these TranslateBrowsePathsToNodeIds settings
         *  will be used by the client to resolve NodeIds, QualifiedNames etc.  of the
         *  request.
         *  If translateSettingsGiven is false, then the default translate settings will be used
         *  (as can be configured by uaf::Client::setClientSettings). */
        uaf::TranslateBrowsePathsToNodeIdsSettings translateSettings;


        /** Session settings to use, to create new session(s) to invoke the request, if
         * clientConnectionIdGiven is false and sessionSettingsGiven is true.
         * If clientConnectionIdGiven and sessionSettingsGiven are both false, then the
         * default session settings will be used (as configured by uaf::Client::setClientSettings). */
        uaf::SessionSettings sessionSettings;


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
        std::string toString(const std::string& indent="", std::size_t colon=36) const
        {
            std::stringstream ss;

            ss << indent << " - requestHandle";
            ss << uaf::fillToPos(ss, colon);
            if (requestHandle_ == uaf::constants::REQUESTHANDLE_NOT_ASSIGNED)
                ss << ": REQUESTHANDLE_NOT_ASSIGNED\n";
            else
                ss << ": " << requestHandle_ << "\n";

            ss << indent << " - targets[]";
            if (targets.size() > 0)
            {
                ss << "\n";
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
            }
            else
            {
                ss << uaf::fillToPos(ss, colon);
                ss << ": []\n";
            }

            ss << indent << " - clientConnectionIdGiven";
            ss << uaf::fillToPos(ss, colon);
            ss << ": " << (clientConnectionIdGiven ? "true" : "false") << "\n";

            ss << indent << " - clientConnectionId";
            if (clientConnectionIdGiven)
            {
                if (clientConnectionId == uaf::constants::CLIENTHANDLE_NOT_ASSIGNED)
                    ss << uaf::fillToPos(ss, colon) << ": CLIENTHANDLE_NOT_ASSIGNED\n";
                else
                    ss << uaf::fillToPos(ss, colon) << ": " << clientConnectionId << "\n";
            }
            else
                ss << uaf::fillToPos(ss, colon) << ": (not given)\n";

            ss << indent << " - serviceSettingsGiven";
            ss << uaf::fillToPos(ss, colon);
            ss << ": " << (serviceSettingsGiven ? "true" : "false") << "\n";

            ss << indent << " - serviceSettings";
            if (serviceSettingsGiven)
                ss << "\n" << serviceSettings.toString(indent + "   ", colon) << "\n";
            else
                ss << uaf::fillToPos(ss, colon) << ": (not given)\n";

            ss << indent << " - translateSettingsGiven";
            ss << uaf::fillToPos(ss, colon);
            ss << ": " << (translateSettingsGiven ? "true" : "false") << "\n";

            ss << indent << " - translateSettings";
            if (translateSettingsGiven)
                ss << "\n" << translateSettings.toString(indent + "   ", colon) << "\n";
            else
                ss << uaf::fillToPos(ss, colon) << ": (not given)\n";

            ss << indent << " - sessionSettingsGiven";
            ss << uaf::fillToPos(ss, colon);
            ss << ": " << (sessionSettingsGiven ? "true" : "false") << "\n";

            ss << indent << " - sessionSettings";
            if (sessionSettingsGiven)
                ss << "\n" << sessionSettings.toString(indent + "   ", colon);
            else
                ss << uaf::fillToPos(ss, colon) << ": (not given)";

            return ss.str();
        }


        // comparison operators
        friend bool operator==(
                const BaseSessionRequest<_ServiceSettings, _Target, _Async>& object1,
                const BaseSessionRequest<_ServiceSettings, _Target, _Async>& object2)
        {
            if (object1.targets.size() != object2.targets.size())
                return false;

            for (std::size_t i = 0; i < object1.targets.size(); i++)
                if (object1.targets[i] != object2.targets[i])
                    return false;

            return    object1.serviceSettingsGiven == object2.serviceSettingsGiven
                   && object1.serviceSettings == object2.serviceSettings
                   && object1.translateSettingsGiven == object2.translateSettingsGiven
                   && object1.translateSettings == object2.translateSettings
                   && object1.clientConnectionIdGiven == object2.clientConnectionIdGiven
                   && object1.clientConnectionId == object2.clientConnectionId
                   && object1.sessionSettingsGiven == object2.sessionSettingsGiven
                   && object1.sessionSettings == object2.sessionSettings;
        }

        friend bool operator!=(
                const BaseSessionRequest<_ServiceSettings, _Target, _Async>& object1,
                const BaseSessionRequest<_ServiceSettings, _Target, _Async>& object2)
        {
            return !(object1 == object2);
        }

        friend bool operator<(
                const BaseSessionRequest<_ServiceSettings, _Target, _Async>& object1,
                const BaseSessionRequest<_ServiceSettings, _Target, _Async>& object2)
        {
            if (object1.targets.size() != object2.targets.size())
                return object1.targets.size() < object2.targets.size();
            else if (object1.serviceSettingsGiven != object2.serviceSettingsGiven)
                return object1.serviceSettingsGiven < object2.serviceSettingsGiven;
            else if (object1.serviceSettings != object2.serviceSettings)
                return object1.serviceSettings < object2.serviceSettings;
            else if (object1.translateSettingsGiven != object2.translateSettingsGiven)
                return object1.translateSettingsGiven < object2.translateSettingsGiven;
            else if (object1.translateSettings != object2.translateSettings)
                return object1.translateSettings < object2.translateSettings;
            else if (object1.clientConnectionIdGiven != object2.clientConnectionIdGiven)
                return object1.clientConnectionIdGiven < object2.clientConnectionIdGiven;
            else if (object1.clientConnectionId != object2.clientConnectionId)
                return object1.clientConnectionId < object2.clientConnectionId;
            else if (object1.sessionSettingsGiven != object2.sessionSettingsGiven)
                return object1.sessionSettingsGiven < object2.sessionSettingsGiven;
            else if (object1.sessionSettings != object2.sessionSettings)
                return object1.sessionSettings < object2.sessionSettings;
            else
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


#endif /* UAF_BASESESSIONREQUEST_H_ */
