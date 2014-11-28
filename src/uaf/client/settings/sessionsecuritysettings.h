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

#ifndef UAFC_SESSIONSECURITYSETTINGS_H_
#define UAFC_SESSIONSECURITYSETTINGS_H_

// STD
#include <string>
#include <sstream>
// SDK
#include "uaclient/uaclientsdk.h"
#include "uaclient/uasession.h"
// UAF
#include "uaf/util/status.h"
#include "uaf/util/securitypolicies.h"
#include "uaf/util/usertokentypes.h"
#include "uaf/util/stringifiable.h"
#include "uaf/util/messagesecuritymodes.h"
#include "uaf/util/endpointdescription.h"
#include "uaf/client/clientexport.h"
#include "uaf/client/clientstatus.h"

namespace uafc
{


    /*******************************************************************************************//**
    * The security info used to connect a session.
    *
    * @ingroup ClientSettings
    ***********************************************************************************************/
    class UAFC_EXPORT SessionSecuritySettings
    {
    public:


        /**
         * Create a new SessionSecuritySettings object.
         */
        SessionSecuritySettings();


        /** The security policy to be used (e.g. uaf::securitypolicies::Basic128). */
        std::string securityPolicy;

        /** The message security mode to be used (e.g. uaf::MessageSecurityMode::SignAndEncrypt). */
        uaf::messagesecuritymodes::MessageSecurityMode messageSecurityMode;

        /** The type of the User token, to be used (e.g. uaf::UserTokenType::UserName). */
        uaf::usertokentypes::UserTokenType userTokenType;

        /** The user name
         *  (only relevant if the userTokenType == uaf::UserTokenType::UserName). */
        std::string userName;

        /** The user password
         *  (only relevant if the userTokenType == uaf::UserTokenType::UserName). */
        std::string userPassword;

        /** The user certificate file name
         *  (only relevant if the userTokenType == uaf::UserTokenType::Certificate). */
        std::string userCertificateFileName;

        /** The user certificate private key file name
         *  (only relevant if the userTokenType == uaf::UserTokenType::Certificate). */
        std::string userPrivateKeyFileName;


        /**
         * Get a string representation.
         */
        std::string toString(const std::string& indent="", std::size_t colon=28) const;


        // comparison operators
        friend UAFC_EXPORT bool operator<(
                const SessionSecuritySettings& object1,
                const SessionSecuritySettings& object2);
        friend UAFC_EXPORT bool operator==(
                const SessionSecuritySettings& object1,
                const SessionSecuritySettings& object2);
        friend UAFC_EXPORT bool operator!=(
                const SessionSecuritySettings& object1,
                const SessionSecuritySettings& object2);



    };



    /**
     * Check if session security settings (e.g. as specified by the user) match the given endpoint
     * of a (e.g. discovered) server.
     *
     * @param settings  The security settings, e.g. as specified by the user.
     * @param endpoint  The endpoint description, e.g. as discovered by the UAF client.
     * @return          Good if the settings and the endpoint match, bad if not.
     */
    uaf::Status UAFC_EXPORT match(
            const uafc::SessionSecuritySettings&    settings,
            const uaf::EndpointDescription&         endpoint);


    /**
     * Check if one of the given session security settings (e.g. as specified by the user) match
     * one of the given endpoints of a (e.g. discovered) server.
     *
     * @param settings          The vector of security settings, e.g. as specified by the user.
     * @param endpoints         The vector of endpoint description, e.g. as discovered by the
     *                          UAF client.
     * @param suitableSettings  The settings that matched (if the returned status is Good)!
     * @param suitableEndpoint  The endpoint that matched (if the returned status is Good)!
     * @return                  Good if one of the settings and one of the endpoints match, bad if
     *                          not.
     */
    uafc::ClientStatus UAFC_EXPORT match(
            const std::vector<uafc::SessionSecuritySettings>&   settings,
            const std::vector<uaf::EndpointDescription>&        endpoints,
            uafc::SessionSecuritySettings&                      suitableSettings,
            uaf::EndpointDescription&                           suitableEndpoint);


}


#endif /* UAFC_SESSIONSECURITYSETTINGS_H_ */
