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

#ifndef UAF_SERVICESETTINGS_H_
#define UAF_SERVICESETTINGS_H_


// STD
#include <string>
#include <stdint.h>
#include <sstream>
// SDK
#include "uaclient/uaclientsdk.h"
// UAF
#include "uaf/util/util.h"
#include "uaf/util/status.h"
#include "uaf/util/stringifiable.h"
#include "uaf/client/clientexport.h"


namespace uaf
{


    /*******************************************************************************************//**
    * An uaf::ServiceSettings instance stores the settings of a service call
    * (e.g. read/write/...).
    *
    * @ingroup ClientSettings
    ***********************************************************************************************/
    class UAF_EXPORT ServiceSettings
    {
    public:


        /**
         * Construct default settings.
         */
        ServiceSettings();

        /**
         * The maximum time allowed for each service communication between client and server.
         */
        double callTimeoutSec;


        /**
         * Get a string representation of the settings.
         *
         * @return  String representation.
         */
        std::string toString(const std::string& indent="", std::size_t colon=18) const;


        /**
         * Copy the contents to the corresponding SDK variable.
         *
         * @param uaServiceSettings A service settings instance as defined by the SDK.
         */
        uaf::Status toSdk(UaClientSdk::ServiceSettings& uaServiceSettings) const;


        // comparison operators
        friend bool UAF_EXPORT operator<(
                const ServiceSettings& object1,
                const ServiceSettings& object2);
        friend bool UAF_EXPORT operator==(
                const ServiceSettings& object1,
                const ServiceSettings& object2);
        friend bool UAF_EXPORT operator!=(
                const ServiceSettings& object1,
                const ServiceSettings& object2);


    };
}

#endif /* UAF_SERVICESETTINGS_H_ */
