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

#ifndef UAFC_BROWSEREQUESTTARGET_H_
#define UAFC_BROWSEREQUESTTARGET_H_



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
    * A uafc::BrowseRequestTarget is the part of a uafc::BrowseRequest that specifies the target
    * to be browsed.
    *
    * @ingroup ClientRequests
    ***********************************************************************************************/
    class UAFC_EXPORT BrowseRequestTarget : public uafc::BaseSessionRequestTarget
    {
    public:

        /**
         * Construct an empty browse target.
         */
        BrowseRequestTarget();


        /**
         * Construct a browse target for the given address of a node.
         *
         * @param address    The address of the node to be browsed.
         */
        BrowseRequestTarget(const uaf::Address& address);


        /**
         * Virtual destructor.
         */
        virtual ~BrowseRequestTarget() {}


        /** The address of the node to be browsed. */
        uaf::Address address;

        /** Direction to follow when browsing the nodes (Forward by default). */
        uaf::browsedirections::BrowseDirection browseDirection;

        /** NodeId of the type of references (i.e. the ReferenceType) to follow (or its subtypes
         *  if the includeSubtypes flag is true).
         *  By default, the nodeId is not initialized with contents (i.e. nodeId.isNull() returns
         *  true), so that all references will be followed. */
        uaf::NodeId referenceTypeId;

        /** Flag indicating that, if the referenceTypeId points to a valid node, also the subtypes
         *  of the referenceTypeId should be followed. */
        bool includeSubtypes;

        /** A mask specifying the node classes that should be returned. The mask has the following
         *  bits assigned:
         *   - 0: Object
         *   - 1: Variable
         *   - 2: Method
         *   - 3: ObjectType
         *   - 4: VariableType
         *   - 5: ReferenceType
         *   - 6: DataType
         *   - 7: View
         *
         *  Leave the mask 0 (=default!) to return all node classes. */
        uint32_t nodeClassMask;

        /** A mask specifying the fields in the reference description to be returned. The mask has
         * the following bits assigned:
         *  - 0: ReferenceType
         *  - 1: IsForward
         *  - 2: NodeClass
         *  - 3: BrowseName
         *  - 4: DisplayName
         *  - 5: TypeDefinition
         *
         *  By default, this mask is 63 (so 0b111111)*/
        uint32_t resultMask;


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
                const BrowseRequestTarget& object1,
                const BrowseRequestTarget& object2);
        friend bool UAFC_EXPORT operator!=(
                const BrowseRequestTarget& object1,
                const BrowseRequestTarget& object2);
        friend bool UAFC_EXPORT operator<(
                const BrowseRequestTarget& object1,
                const BrowseRequestTarget& object2);



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


#endif /* UAFC_BROWSEREQUESTTARGET_H_ */
