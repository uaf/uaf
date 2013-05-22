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

#ifndef UAFC_WRITEREQUESTTARGET_H_
#define UAFC_WRITEREQUESTTARGET_H_



// STD
// SDK
// UAF
#include "uaf/util/address.h"
#include "uaf/util/variant.h"
#include "uaf/util/monitoringmodes.h"
#include "uaf/util/datavalue.h"
#include "uaf/util/attributeids.h"
#include "uaf/client/clientexport.h"
#include "uaf/client/requests/basesessionrequesttarget.h"



namespace uafc
{


    /*******************************************************************************************//**
    * A uafc::WriteRequestTarget is the part of a uafc::WriteRequest that specifies the target
    * to write.
    *
    * @ingroup ClientRequests
    ***********************************************************************************************/
    class UAFC_EXPORT WriteRequestTarget : public uafc::BaseSessionRequestTarget,
                                           public uaf::DataValue
    {
    public:


        /**
         * Construct an empty write target.
         */
        WriteRequestTarget();


        /**
         * Construct a write target for a given address, value and attribute id.
         *
         * @param address       Address of the node of which the attribute should be written.
         * @param data          Data to write.
         * @param attributeId   Attribute id of the node to write.
         */
        WriteRequestTarget(
                const uaf::Address&             address,
                const uaf::Variant&             data,
                uaf::attributeids::AttributeId  attributeId = uaf::attributeids::Value);


        /** Address of the node of which the attribute should be written. */
        uaf::Address address;

        /** Attribute id to be written. */
        uaf::attributeids::AttributeId attributeId;

        /** Index range. */
        std::string indexRange;

        /**
         * Get a string representation of the target.
         *
         * @return  String representation
         */
        std::string toString(const std::string& indent="", std::size_t colon=30) const;


        // comparison operators
        friend bool UAFC_EXPORT operator==(
                const WriteRequestTarget& object1,
                const WriteRequestTarget& object2);
        friend bool UAFC_EXPORT operator!=(
                const WriteRequestTarget& object1,
                const WriteRequestTarget& object2);
        friend bool UAFC_EXPORT operator<(
                const WriteRequestTarget& object1,
                const WriteRequestTarget& object2);


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


#endif /* UAFC_WRITEREQUESTTARGET_H_ */
