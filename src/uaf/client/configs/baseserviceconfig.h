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


#ifndef UAFC_BASESERVICECONFIG_H_
#define UAFC_BASESERVICECONFIG_H_


// STD
#include <vector>
#include <string>
#include <sstream>
// SDK
// UAF
#include "uaf/util/stringifiable.h"
#include "uaf/client/clientexport.h"
#include "uaf/client/settings/translatebrowsepathstonodeidssettings.h"


namespace uafc
{


    /*******************************************************************************************//**
    * A BaseServiceConfig is the base template class for a ReadConfig, WriteConfig, ...
    *
    * It holds both a "settings" object for a particular service (e.g. ReadSettings, WriteSettings)
    * and a TranslateBrowsePathsToNodeIdsSettings object that can be used by the UAF to resolve
    * the addresses that are involved in the service call.
    *
    * @ingroup ClientConfigs
    ***********************************************************************************************/
    template<typename _ServiceSettings>
    class UAFC_EXPORT BaseServiceConfig : public uaf::Stringifiable
    {
    public:

        typedef _ServiceSettings ServiceSettingsType;

        /** The settings for a particular service. */
        _ServiceSettings                            serviceSettings;

        /** The settings to translate any relative addresses that are involved in the service
         *  call. */
        uafc::TranslateBrowsePathsToNodeIdsSettings translationSettings;


        /**
         * Get a string representation of the config.
         */
        virtual std::string toString(const std::string& indent="", std::size_t colon=40) const
        {
            std::stringstream ss;
            ss << indent << " - serviceSettings\n";
            ss << serviceSettings.toString(indent + "   ", colon) << "\n";
            ss << indent << " - translationSettings\n";
            ss << translationSettings.toString(indent + "   ", colon);
            return ss.str();
        }
    };



}



#endif /* UAFC_BASESERVICECONFIG_H_ */
