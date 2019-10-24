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

#ifndef UAF_TIMESTAMPSTORETURN_H_
#define UAF_TIMESTAMPSTORETURN_H_

// STD
#include <string>
// SDK
#include "uabasecpp/uaplatformlayer.h"
// UAF
#include "uaf/util/util.h"

namespace uaf
{

    namespace timestampstoreturn
    {

        /**
         * The timestamps to return.
         *
         * @ingroup Util
         */
        enum TimestampsToReturn
        {
            Source   = 0,
            Server   = 1,
            Both     = 2,
            Neither  = 3
        };


        /**
         * Get a string representation of the timestamps to return.
         *
         * @param timestamps    The timestamps to return (as an enum).
         * @return              The corresponding name of the timestamps to return.
         *
         * @ingroup Util
         */
        std::string UAF_EXPORT toString(TimestampsToReturn timestamps);


        /**
         * Convert the SDK/Stack instance to a UAF instance.
         *
         * @ingroup Util
         */
        OpcUa_TimestampsToReturn UAF_EXPORT fromUafToSdk(TimestampsToReturn timestamps);


        /**
         * Convert the UAF instance to a SDK/Stack instance.
         *
         * @ingroup Util
         */
        TimestampsToReturn UAF_EXPORT fromSdkToUaf(OpcUa_TimestampsToReturn timestamps);



    }

}


#endif /* UAF_TIMESTAMPSTORETURN_H_ */
