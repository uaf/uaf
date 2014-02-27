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

#ifndef UAF_VIEWDESCRIPTION_H_
#define UAF_VIEWDESCRIPTION_H_


// STD
#include <string>
#include <stdint.h>
#include <sstream>
// SDK
#include "uabase/uaplatformlayer.h"
// UAF
#include "uaf/util/util.h"
#include "uaf/util/stringifiable.h"
#include "uaf/util/nodeid.h"


namespace uaf
{



    /*******************************************************************************************//**
    * A uaf::ViewDescription instance specifies an OPC UA View.
    *
    * @ingroup Util
    ***********************************************************************************************/
    class UAF_EXPORT ViewDescription
    {
    public:


        /**
         * Construct a default view description.
         */
        ViewDescription();


        /**
         * The node id of the View to query.
         *
         * Leave the NodeId to its default value (= without any contents, so uaf::NodeId::isNull()
         * will return true) if you want to specify the whole address space.
         */
        uaf::NodeId viewId;


        // ToDo add timestamp and viewVersion


        /**
         * Get a string representation.
         *
         * @return  A string representation.
         */
        std::string toString(const std::string& indent="", std::size_t colon=10) const;


        // comparison operators
        friend bool UAF_EXPORT operator<(
                const ViewDescription& object1,
                const ViewDescription& object2);
        friend bool UAF_EXPORT operator==(
                const ViewDescription& object1,
                const ViewDescription& object2);
        friend bool UAF_EXPORT operator!=(
                const ViewDescription& object1,
                const ViewDescription& object2);

    };



}

#endif /* UAF_VIEWDESCRIPTION_H_ */
