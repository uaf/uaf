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

#ifndef UAFC_METHODCALLREQUESTTARGET_H_
#define UAFC_METHODCALLREQUESTTARGET_H_



// STD
// SDK
// UAF
#include "uaf/util/address.h"
#include "uaf/util/variant.h"
#include "uaf/util/monitoringmodes.h"
#include "uaf/util/attributeids.h"
#include "uaf/client/clientexport.h"
#include "uaf/client/requests/basesessionrequesttarget.h"



namespace uafc
{


    /*******************************************************************************************//**
    * A uafc::MethodCallRequestTarget is the part of a uafc::MethodCallRequest that specifies the
    * target to call.
    *
    * @ingroup ClientRequests
    ***********************************************************************************************/
    class UAFC_EXPORT MethodCallRequestTarget : public uafc::BaseSessionRequestTarget
    {
    public:


        /**
         * Construct an empty method call target.
         */
        MethodCallRequestTarget();


        /**
         * Construct a method call target for a given object address, method address and
         * input arguments.
         *
         * @param objectAddress     The address of the parent node of the method.
         * @param methodAddress     The address of the method node itself.
         * @param inputArguments    The input arguments as a vector of variants.
         */
        MethodCallRequestTarget(
                const uaf::Address&                 objectAddress,
                const uaf::Address&                 methodAddress,
                const std::vector<uaf::Variant>&    inputArguments);


        /** The address of the node in which context the method call should be executed. */
        uaf::Address objectAddress;


        /** The address of the node representing the method. */
        uaf::Address methodAddress;


        /** The input arguments of the method. */
        std::vector<uaf::Variant> inputArguments;


        /**
         * Get a string representation of the target.
         *
         * @return  String representation.
         */
        virtual std::string toString(const std::string& indent="", std::size_t colon=10) const;


        // comparison operators
        friend bool UAFC_EXPORT operator==(
                const MethodCallRequestTarget& object1,
                const MethodCallRequestTarget& object2);
        friend bool UAFC_EXPORT operator!=(
                const MethodCallRequestTarget& object1,
                const MethodCallRequestTarget& object2);
        friend bool UAFC_EXPORT operator<(
                const MethodCallRequestTarget& object1,
                const MethodCallRequestTarget& object2);

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
        std::size_t resolvableItemsCount() const { return 2; }


        /**
         * Set the resolved items as a "flat" list of ExpandedNodeIds and Statuses.
         */
        uaf::Status setResolvedItems(
                const std::vector<uaf::ExpandedNodeId>& expandedNodeIds,
                const std::vector<uaf::Status>&         resolutionStatuses);


    };


}


#endif /* UAFC_METHODCALLREQUESTTARGET_H_ */
