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

#ifndef UAF_TRANSLATEBROWSEPATHSTONODEIDSREQUESTTARGET_H_
#define UAF_TRANSLATEBROWSEPATHSTONODEIDSREQUESTTARGET_H_



// STD
// SDK
// UAF
#include "uaf/util/address.h"
#include "uaf/util/browsepath.h"
#include "uaf/client/clientexport.h"
#include "uaf/client/requests/basesessionrequesttarget.h"



namespace uaf
{


    /*******************************************************************************************//**
    * A uaf::TranslateBrowsePathsToNodeIdsRequestTarget is the part of a
    * uaf::TranslateBrowsePathsToNodeIdsRequest that specifies the target to translate.
    *
    * @ingroup ClientRequests
    ***********************************************************************************************/
    class UAF_EXPORT TranslateBrowsePathsToNodeIdsRequestTarget
    : public uaf::BaseSessionRequestTarget
    {
    public:


        /**
         * Construct an empty TranslateBrowsePathsToNodeIds request target.
         */
        TranslateBrowsePathsToNodeIdsRequestTarget();


        /**
         * Construct a TranslateBrowsePathsToNodeIds request target for a given node.
         *
         * @param browsePath    The browse path to translate.
         */
        TranslateBrowsePathsToNodeIdsRequestTarget(const uaf::BrowsePath& browsePath);


        /**
         * Virtual destructor.
         */
        virtual ~TranslateBrowsePathsToNodeIdsRequestTarget() {}


        /** Browse path to be translated. */
        uaf::BrowsePath browsePath;


        /**
         * Get a string representation of the target.
         *
         * @return  String representation
         */
        std::string toString(const std::string& indent="", std::size_t colon=20) const;


        // comparison operators
        friend bool UAF_EXPORT operator==(
                const TranslateBrowsePathsToNodeIdsRequestTarget& object1,
                const TranslateBrowsePathsToNodeIdsRequestTarget& object2);
        friend bool UAF_EXPORT operator!=(
                const TranslateBrowsePathsToNodeIdsRequestTarget& object1,
                const TranslateBrowsePathsToNodeIdsRequestTarget& object2);
        friend bool UAF_EXPORT operator<(
                const TranslateBrowsePathsToNodeIdsRequestTarget& object1,
                const TranslateBrowsePathsToNodeIdsRequestTarget& object2);


        /**
         * Get the server URI to which the service should be invoked for this target.
         *
         * @param serverUri The server URI as an output parameter.
         * @return          A good status if a server URI could be synthesized, a bad one if not.
         */
        uaf::Status getServerUri(std::string& serverUri) const;


    private:

        // the Resolver can see all private members
        friend class Resolver;


        /**
         * Get the resolvable items from the target as a "flat" list of Addresses.
         */
        std::vector<uaf::Address> getResolvableItems() const;


        /**
         * Get the number of resolvable items of this kind of target.
         */
        std::size_t resolvableItemsCount() const { return 1; }


        /**
         * Set the resolved items as a "flat" list of ExpandedNodeIds and Statuses.
         */
        uaf::Status setResolvedItems(
                const std::vector<uaf::ExpandedNodeId>& expandedNodeIds,
                const std::vector<uaf::Status>&         resolutionStatuses);



    };




}


#endif /* UAF_TRANSLATEBROWSEPATHSTONODEIDSREQUESTTARGET_H_ */
