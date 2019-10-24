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

#ifndef UAF_NODECLASSES_H_
#define UAF_NODECLASSES_H_

// STD
#include <string>
// SDK
#include "uabasecpp/uaplatformlayer.h"
// UAF
#include "uaf/util/util.h"

namespace uaf
{

    namespace nodeclasses
    {

        /**
         * The node class.
         *
         * @ingroup Util
         */
        enum NodeClass
        {
            Unspecified     = 0,
            Object          = 1,
            Variable        = 2,
            Method          = 4,
            ObjectType      = 8,
            VariableType    = 16,
            ReferenceType   = 32,
            DataType        = 64,
            View            = 128
        };



        /**
         * Get a string representation of the node class.
         *
         * @param nodeClass  The node class (as an enum).
         * @return           The corresponding name of the node class.
         *
         * @ingroup Util
         */
        std::string UAF_EXPORT toString(NodeClass nodeClass);


        /**
         * Convert the SDK/Stack instance to a UAF instance.
         *
         * @ingroup Util
         */
        NodeClass UAF_EXPORT fromSdkToUaf(OpcUa_NodeClass nodeClass);


        /**
         * Convert the UAF instance to a SDK/Stack instance.
         *
         * @ingroup Util
         */
        OpcUa_NodeClass UAF_EXPORT fromUafToSdk(NodeClass nodeClass);


    }
}


#endif /* UAF_NODECLASSES_H_ */
