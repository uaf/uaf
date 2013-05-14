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

#ifndef UAFC_SESSIONCONFIG_H_
#define UAFC_SESSIONCONFIG_H_



// STD
#include <string>
#include <sstream>
// SDK
// UAF
#include "uaf/util/status.h"
#include "uaf/util/stringifiable.h"
#include "uaf/client/clientexport.h"
#include "uaf/client/settings/sessionsettings.h"


namespace uafc
{


    /*******************************************************************************************//**
    * A SessionConfig instance can be used to configure one or more sessions that need to be
    * created, in order to successfully invoke an OPC UA service.
    *
    * See the SessionConfigs example in the examples/ directory for more info.
    *
    * @ingroup ClientConfigs
    ***********************************************************************************************/
    class UAFC_EXPORT SessionConfig : public uaf::Stringifiable
    {
    public:


        /**
         * Construct a new session config.
         */
        SessionConfig();


        /**
         * Construct a new session config with the given default settings.
         */
        SessionConfig(const uafc::SessionSettings& defaultSettings);


        /**
         * The default session settings.
         *
         * These settings will be used to create the sessions to servers that aren't specified in
         * the 'specificSessionSettings' map (unless 'useOnlySpecificSettings' is true).
         */
        uafc::SessionSettings defaultSessionSettings;


        /**
         * The session settings for particular serverURIs.
         */
        std::map<std::string, uafc::SessionSettings> specificSessionSettings;


        /**
         * Put this flag to True to make sure that only the specificSessionSettings are used.
         *
         * This flag can be used to make sure that no session will be created (with default
         * settings) other than those that you specify yourself, using the specificSessionSettings.
         * Use this flag in case you want to keep control over the kinds of sessions that are
         * created by the UAF.
         */
        bool useOnlySpecificSettings;


        /**
         * Get a string representation.
         */
        std::string toString(const std::string& indent="", std::size_t colon=40) const;


    private:

        /** Typedef for the map that maps serverUris to session settings. */
        typedef std::map<std::string, uafc::SessionSettings> SpecificsMap;

    };

}


#endif /* UAFC_SESSIONCONFIG_H_ */
