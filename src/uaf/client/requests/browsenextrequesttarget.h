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

#ifndef UAFC_BROWSENEXTREQUESTTARGET_H_
#define UAFC_BROWSENEXTREQUESTTARGET_H_



// STD
// SDK
// UAF
#include "uaf/util/address.h"
#include "uaf/util/monitoringmodes.h"
#include "uaf/util/browsedirections.h"
#include "uaf/client/clientexport.h"
#include "uaf/client/requests/basesessionrequesttarget.h"
#include "uaf/client/configs/configs.h"



namespace uafc
{


    /*******************************************************************************************//**
    * A uafc::BrowseNextRequestTarget is the part of a uafc::BrowseNextRequest that specifies the
    * continuation point.
    *
    * @ingroup ClientRequests
    ***********************************************************************************************/
    class UAFC_EXPORT BrowseNextRequestTarget : public uafc::BaseSessionRequestTarget
    {
    public:

        /**
         * Construct an empty BrowseNext target.
         */
        BrowseNextRequestTarget();


        /**
         * Construct a BrowseNext target for the given clientConnectionId and continuation point.
         *
         * @param address               The address of the node being browsed (the UAF needs it
         *                              to identify the correct session).
         * @param continuationPoint     The continuation point.
         */
        BrowseNextRequestTarget(
                const uaf::Address&     address,
                const uaf::ByteString&  continuationPoint);


        /** The address of the node that is being browsed (the UAF needs it to identify the
         * correct session). */
        uaf::Address address;

        /** The continuation point, as received by the previous Browse or BrowseNext call. */
        uaf::ByteString continuationPoint;


        /**
         * Get the server URI to which the service should be invoked for this target.
         *
         * @param serverUri The server URI as an output parameter.
         * @return          A good status if a server URI could be synthesized, a bad one if not.
         */
        uaf::Status getServerUri(std::string& serverUri) const;


        /**
         * Get a string representation of the target.
         *
         * @return  String representation
         */
        std::string toString(const std::string& indent="", std::size_t colon=22) const;


        // comparison operators
        friend bool UAFC_EXPORT operator==(
                const BrowseNextRequestTarget& object1,
                const BrowseNextRequestTarget& object2);
        friend bool UAFC_EXPORT operator!=(
                const BrowseNextRequestTarget& object1,
                const BrowseNextRequestTarget& object2);
        friend bool UAFC_EXPORT operator<(
                const BrowseNextRequestTarget& object1,
                const BrowseNextRequestTarget& object2);



    private:

        // the Resolver can see all private members
        friend class Resolver;


        /**
         * Get the resolvable items from the target as a "flat" list of Addresses.
         */
        std::vector<uaf::Address> getResolvableItems() const;


        /**
         * Get the number of resolvable items of this target.
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


#endif /* UAFC_BROWSENEXTREQUESTTARGET_H_ */
