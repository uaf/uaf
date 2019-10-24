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

#ifndef UAF_BROWSEDIRECTIONS_H_
#define UAF_BROWSEDIRECTIONS_H_

// STD
#include <string>
// SDK
#include "uabasecpp/uaplatformlayer.h"
// UAF
#include "uaf/util/util.h"

namespace uaf
{

    namespace browsedirections
    {

        /**
         * The browse direction.
         *
         * @ingroup Util
         */
        enum BrowseDirection
        {
            Forward   = 0,   /**< Only forward references. */
            Inverse   = 1,   /**< Only inverse references. */
            Both      = 2    /**< Forward and inverse references. */
        };


        /**
         * Get a string representation of the browse direction.
         *
         * @param direction The browse direction (as an enum).
         * @return          The corresponding name.
         *
         * @ingroup Util
         */
        std::string UAF_EXPORT toString(BrowseDirection direction);


        /**
         * Convert the SDK/Stack instance to a UAF instance.
         *
         * @ingroup Util
         */
        OpcUa_BrowseDirection UAF_EXPORT fromUafToSdk(BrowseDirection direction);


        /**
         * Convert the UAF instance to a SDK/Stack instance.
         *
         * @ingroup Util
         */
        BrowseDirection UAF_EXPORT fromSdkToUaf(OpcUa_BrowseDirection direction);



    }

}


#endif /* UAF_BROWSEDIRECTIONS_H_ */
