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

#ifndef UAF_APPLICATIONTYPES_H_
#define UAF_APPLICATIONTYPES_H_

// STD
#include <string>
// SDK
#include "uabase/uaplatformlayer.h"
// UAF
#include "uaf/util/util.h"


/** @file */


namespace uaf
{

    namespace applicationtypes
    {

        /**
         * The type of the application.
         *
         * @ingroup Util
         */
        enum ApplicationType
        {
            Server          = 0,    /**< The application is a Server. */
            Client          = 1,    /**< The application is a Client. */
            ClientAndServer = 2,    /**< The application is a Client and Server. */
            DiscoveryServer = 3     /**< The application is a Discovery Server. */
        };


        /**
         * Get a string representation of the application type.
         *
         * @param type  The application type (as an enum).
         * @return      The corresponding name of the application type.
         *
         * @ingroup Util
         */
        std::string UAF_EXPORT toString(uaf::applicationtypes::ApplicationType type);


        /**
         * Convert the SDK/Stack instance to a UAF instance.
         *
         * @ingroup Util
         */
        ApplicationType UAF_EXPORT fromSdkToUaf(OpcUa_ApplicationType type);


        /**
         * Convert the UAF instance to a SDK/Stack instance.
         *
         * @ingroup Util
         */
        OpcUa_ApplicationType UAF_EXPORT fromUafToSdk(ApplicationType type);

    }


}


#endif /* UAF_APPLICATIONTYPES_H_ */
