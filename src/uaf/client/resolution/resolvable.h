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


#ifndef UAFC_RESOLVABLE_H_
#define UAFC_RESOLVABLE_H_


// STD
#include <vector>
#include <string>
// SDK
// UAF
#include "uaf/util/status.h"
#include "uaf/util/address.h"
#include "uaf/util/mask.h"
#include "uaf/client/clientexport.h"
#include "uaf/util/handles.h"

namespace uafc
{


    /*******************************************************************************************//**
    * A uafc::Resolvable class has some items that can be resolved by a uafc::Resolver.
    *
    * @ingroup ClientResolution
    ***********************************************************************************************/
    class UAFC_EXPORT Resolvable
    {
    public:

        /**
         * Virtual destructor.
         */
        virtual ~Resolvable() {}


    private:

        // make sure a Resolver has access to all members
        friend class Resolver;


        /**
         * Get all resolvable items.
         *
         * @return  The addresses that can be resolved by the resolver.
         */
        virtual std::vector<uaf::Address> getResolvableItems() const = 0;


        /**
         * Get the number of resolvable items.
         *
         * @return  Number of resolvable items.
         */
        virtual std::size_t resolvableItemsCount() const = 0;


        /**
         * Update the resolvable items.
         *
         * @param   The resolved items.
         * @param   The statuses (Good if given item is resolved, Bad if not).
         */
        virtual uaf::Status             setResolvedItems(
                const std::vector<uaf::ExpandedNodeId>& expandedNodeIds,
                const std::vector<uaf::Status>&         resolutionStatuses) = 0;
    };



}



#endif /* UAFC_RESOLVABLE_H_ */
