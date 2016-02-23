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

#ifndef UAF_STRUCTUREFIELDDATATYPES_H_
#define UAF_STRUCTUREFIELDDATATYPES_H_

// STD
#include <string>
// SDK
#include "uabase/uaplatformlayer.h"
#include "uabase/uastructurefielddata.h"
// UAF
#include "uaf/util/util.h"


/** @file */


namespace uaf
{

    namespace structurefielddatatypes
    {

		/**
		 * DataType of the structure field.
		 *
		 * @ingroup Util
		 */


		enum StructureFieldDataType
		{

			Variant                 = DataVariant,
			GenericStructure        = DataGenericStructure,
			GenericStructureArray   = DataGenericStructureArray,
			GenericUnion        	= DataGenericUnion,
			GenericUnionArray       = DataGenericUnionArray,
			GenericOptionSet        = DataGenericOptionSet,
			GenericOptionSetArray   = DataGenericOptionSetArray,
			Empty        			= DataEmpty
		};


        /**
         * Get a string representation of the data type.
         *
         * @param type  The data type (as an enum value).
         * @return      The corresponding name.
         *
         * @ingroup Util
         */
        std::string UAF_EXPORT toString(uaf::structurefielddatatypes::StructureFieldDataType type);


        /**
         * Convert the SDK/Stack instance to a UAF instance.
         *
         * @ingroup Util
         */
        uaf::structurefielddatatypes::StructureFieldDataType UAF_EXPORT fromSdkToUaf(
        		UaStructureFieldDataType uaType);


        /**
         * Convert the UAF instance to a SDK/Stack instance.
         *
         * @ingroup Util
         */
        UaStructureFieldDataType UAF_EXPORT fromUafToSdk(
        		uaf::structurefielddatatypes::StructureFieldDataType type);

    }


}


#endif /* UAF_STRUCTUREFIELDDATATYPES_H_ */
