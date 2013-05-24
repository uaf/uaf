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

#ifndef UAFC_HISTORYREADRAWMODIFIEDREQUESTTARGET_H_
#define UAFC_HISTORYREADRAWMODIFIEDREQUESTTARGET_H_



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
    * A uafc::HistoryReadRawModifiedRequestTarget is the part of a
    * uafc::HistoryReadRawModifiedRequest that specifies the node that provides historical
    * information.
    *
    * @ingroup ClientRequests
    ***********************************************************************************************/
    class UAFC_EXPORT HistoryReadRawModifiedRequestTarget : public uafc::BaseSessionRequestTarget
    {
    public:


        /**
         * Construct an empty target.
         */
        HistoryReadRawModifiedRequestTarget();


        /**
         * Construct a history read target for a given node address.
         *
         * @param address           The address of the node from which the historical data should
         *                          be read.
         */
        HistoryReadRawModifiedRequestTarget(const uaf::Address& address);


        /**
         * Construct a history read target for a given node address and continuation point.
         *
         * @param address           The address of the node from which the historical data should
         *                          be read.
         * @param continuationPoint The continuation point of a previous HistoryRead service call.
         */
        HistoryReadRawModifiedRequestTarget(
                const uaf::Address&     address,
                const uaf::ByteString&  continuationPoint);


        /** The address of the node from which the historical data should be read. */
        uaf::Address address;

        /** The continuation point of a previous HistoryRead service call.
         *  The UAF can automatically handle continuation points, for more info take a look
         *  at the documentation of uafc::HistoryReadRawModifiedSettings::maxAutoReadMore
         *  If you decide to use the continuation points manually, you can still do so of course
         *  by copying the continuation point of a previous result
         *  (uafc::HistoryReadRawModifiedResultTarget::continuationPoint) to here. */
        uaf::ByteString continuationPoint;

        /** The index range in case the node is an array. */
        std::string indexRange;

        /** The data encoding.
         *  Leave NULL (i.e. don't touch) to use the default encoding. */
        uaf::QualifiedName dataEncoding;


        /**
         * Get a string representation of the target.
         *
         * @return  String representation.
         */
        virtual std::string toString(const std::string& indent="", std::size_t colon=21) const;


        // comparison operators
        friend bool UAFC_EXPORT operator==(
                const HistoryReadRawModifiedRequestTarget& object1,
                const HistoryReadRawModifiedRequestTarget& object2);
        friend bool UAFC_EXPORT operator!=(
                const HistoryReadRawModifiedRequestTarget& object1,
                const HistoryReadRawModifiedRequestTarget& object2);
        friend bool UAFC_EXPORT operator<(
                const HistoryReadRawModifiedRequestTarget& object1,
                const HistoryReadRawModifiedRequestTarget& object2);

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


#endif /* UAFC_HISTORYREADRAWMODIFIEDREQUESTTARGET_H_ */
