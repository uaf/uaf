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

#ifndef UAF_NODEIDIDENTIFIERTYPES_H_
#define UAF_NODEIDIDENTIFIERTYPES_H_

// STD
#include <string>
// SDK
#include "uabasecpp/uaplatformlayer.h"
// UAF
#include "uaf/util/util.h"


/** @file */


namespace uaf
{

    namespace nodeididentifiertypes
    {


        /**
         * Type of the identifier.
         *
         * @ingroup Util
         */
        enum NodeIdIdentifierType
        {
            Identifier_Numeric    = 0, /**< The NodeId identifier is a numerical value. */
            Identifier_String     = 1, /**< The NodeId identifier is a string. */
            Identifier_Guid       = 2, /**< The NodeId identifier is a globally unique identifier (GUID). */
            Identifier_Opaque     = 3  /**< The NodeId identifier is an opaque value. */
        };

        /**
         * Get a string representation of the NodeId identifier type.
         *
         * @param type  The identifier type (as an enum value).
         * @return      The corresponding name of the identifier type.
         *
         * @ingroup Util
         */
        std::string UAF_EXPORT toString(uaf::nodeididentifiertypes::NodeIdIdentifierType type);


        /**
         * Convert the SDK/Stack instance to a UAF instance.
         *
         * @ingroup Util
         */
        uaf::nodeididentifiertypes::NodeIdIdentifierType UAF_EXPORT fromSdkToUaf(
                OpcUa_IdentifierType type);


        /**
         * Convert the UAF instance to a SDK/Stack instance.
         *
         * @ingroup Util
         */
        OpcUa_IdentifierType UAF_EXPORT fromUafToSdk(
                uaf::nodeididentifiertypes::NodeIdIdentifierType type);

    }


}


#endif /* UAF_APPLICATIONTYPES_H_ */
