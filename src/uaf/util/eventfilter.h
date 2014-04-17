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

#ifndef UAFC_EVENTFILTER_H_
#define UAFC_EVENTFILTER_H_



// STD
#include <vector>
#include <string>
#include <sstream>
// SDK
// UAF
#include "uaf/util/util.h"
#include "uaf/util/stringifiable.h"
#include "uaf/util/simpleattributeoperand.h"


namespace uaf
{

    /*******************************************************************************************//**
    * An uafc::EventFilter defines select clauses and a where clause.
    *
    * @ingroup Util
    ***********************************************************************************************/
    class UAF_EXPORT EventFilter
    {
    public:


        /**
         * Construct an event filter.
         */
        EventFilter();

        std::vector<uaf::SimpleAttributeOperand> selectClauses;

        //uafc::WhereClause whereClause;


        /**
         * Get a string representation.
         *
         * @return  A string representation.
         */
        std::string toString(const std::string& indent="", std::size_t colon=26) const;


        // comparison operators
        friend bool UAF_EXPORT operator<(const EventFilter& object1, const EventFilter& object2);
        friend bool UAF_EXPORT operator==(const EventFilter& object1, const EventFilter& object2);
        friend bool UAF_EXPORT operator!=(const EventFilter& object1, const EventFilter& object2);
    };

}
#endif /* UAFC_EVENTFILTER_H_ */
