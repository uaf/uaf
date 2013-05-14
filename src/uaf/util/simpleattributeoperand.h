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

#ifndef UAF_SIMPLEATTRIBUTEOPERAND_H_
#define UAF_SIMPLEATTRIBUTEOPERAND_H_


// STD
#include <vector>
#include <string>
#include <sstream>
// SDK
// UAF
#include "uaf/util/util.h"
#include "uaf/util/nodeid.h"
#include "uaf/util/browsepath.h"
#include "uaf/util/stringifiable.h"
#include "uaf/util/attributeids.h"

namespace uaf
{


    /*******************************************************************************************//**
    * A uaf::SimpleAttributeOperand is part of a filter and can describe select clauses,
    * where clauses, etc.
    *
    * @ingroup Util
    ***********************************************************************************************/
    struct UAF_EXPORT SimpleAttributeOperand
    {
    public:


        /**
         * Construct a default SimpleAttributeOperand.
         */
        SimpleAttributeOperand();



        /**
         * Get a string representation.
         *
         * @return  A string representation.
         */
        virtual std::string toString(const std::string& indent="", std::size_t colon=20) const;


        /**
         * Attribute id.
         */
        uaf::attributeids::AttributeId attributeId;


        /**
         * Browse path.
         */
        std::vector<uaf::QualifiedName> browsePath;


        /**
         * Type id.
         */
        uaf::NodeId typeId;


        /**
         * Numeric range for the array.
         */
        std::string indexRange;


        // comparison operators
        friend bool UAF_EXPORT operator<(
                const SimpleAttributeOperand& object1,
                const SimpleAttributeOperand& object2);
        friend bool UAF_EXPORT operator==(
                const SimpleAttributeOperand& object1,
                const SimpleAttributeOperand& object2);
        friend bool UAF_EXPORT operator!=(
                const SimpleAttributeOperand& object1,
                const SimpleAttributeOperand& object2);

    };

}


#endif /* UAF_SIMPLEATTRIBUTEOPERAND_H_ */
