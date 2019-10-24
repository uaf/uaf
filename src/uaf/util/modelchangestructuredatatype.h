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

#ifndef UAF_MODELCHANGESTRUCTUREDATATYPE_H_
#define UAF_MODELCHANGESTRUCTUREDATATYPE_H_


// STD
#include <string>
#include <sstream>
// SDK
#include "uabasecpp/uamodelchangestructuredatatype.h"
// UAF
#include "uaf/util/util.h"
#include "uaf/util/stringifiable.h"
#include "uaf/util/extensionobject.h"


namespace uaf
{


    /*******************************************************************************************//**
     * A ModelChangeStructureDataType is usually passed as an event to notify model changes.
     *
     * @ingroup Util
     **********************************************************************************************/
    class UAF_EXPORT ModelChangeStructureDataType
    {
    public:

        /**
         * Construct an empty ModelChangeStructureDataType.
         */
        ModelChangeStructureDataType();


        /**
         * Construct an ModelChangeStructureDataType from an ExtensionObject.
         */
        ModelChangeStructureDataType(const uaf::ExtensionObject& eo);


        /**
         * Get a string representation.
         *
         * @return string representation
         */
        std::string toString(const std::string& indent="", std::size_t colon=16) const;
        
        
        /** The NodeId of the affected node. */
        uaf::NodeId affected;
        
        /** The NodeId of the affected node type. */
        uaf::NodeId affectedType;

        /** Verb */
        uint8_t verb;


        // comparison operators
        friend bool UAF_EXPORT operator<(
                const ModelChangeStructureDataType& object1,
                const ModelChangeStructureDataType& object2);
        friend bool UAF_EXPORT operator==(
                const ModelChangeStructureDataType& object1,
                const ModelChangeStructureDataType& object2);
        friend bool UAF_EXPORT operator!=(
                const ModelChangeStructureDataType& object1,
                const ModelChangeStructureDataType& object2);

    };

}


#endif /* UAF_MODELCHANGESTRUCTUREDATATYPE_H_ */
