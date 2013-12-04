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

#ifndef UAF_ADDRESS_H_
#define UAF_ADDRESS_H_

// STD
#include <string>
#include <sstream>
// UAF
#include "uaf/util/util.h"
#include "uaf/util/status.h"
#include "uaf/util/stringifiable.h"
#include "uaf/util/relativepathelement.h"
#include "uaf/util/expandednodeid.h"
#include "uaf/util/constants.h"
// SDK


namespace uaf
{



    /*******************************************************************************************//**
    * An uaf::Address points to a node within an server address space by means of an
    * absolute address (an ExpandedNodeId) or by means of a relative address (a path relative to
    * another address).
    *
    * An "address" is a term defined by the UAF, and *not* by the OPC UA standard. It's basically
    * a union class that holds information to identify a node within an address space.
    * Several addresses can all point to the same node.
    *
    * A relative address may point to other relative addresses. More formally, the starting
    * point of an Address based on a relative path, may also be an Address based on a
    * relative path in turn. This way you can define large and complex hierarchies of Nodes,
    * with just a single absolute address (based on an ExpandedNodeId) as the starting point.
    *
    * @ingroup Util
    ***********************************************************************************************/
    class UAF_EXPORT Address : public uaf::Stringifiable
    {
    public:

        /**
         * Construct an Address without any addressing information.
         */
        Address();


        /**
         * Construct a relative Address by providing another Address and a path relative to that
         * Address.
         *
         * @param startingAddress   Starting address.
         * @param relativePath      The relative path starting from the starting address.
         */
        Address(uaf::Address*                                     startingAddress,
                const std::vector<uaf::RelativePathElement>&      relativePath);


        /**
         * Construct an address by providing an ExpandedNodeId.
         *
         * This ExpandedNodeId can already be resolved, or not.
         *
         * @param expandedNodeId        The ExpandedNodeId corresponding to this address.
         */
        Address(const uaf::ExpandedNodeId& expandedNodeId);


        /**
         * Convenience function: provide (NodeId, serverUri) instead of (ExpandedNodeId).
         *
         * @param nodeId    The NodeId corresponding to this address.
         * @param serverUri The URI of the server that hosts the nodeId.
         */
        Address(const uaf::NodeId& nodeId, const std::string& serverUri);


        /**
         * Copy constructor.
         *
         * @param other     Address to be copied.
         */
        Address(const Address& other);


        /**
         * Destructor.
         */
        ~Address();


        /**
         * Assignment operator.
         *
         * @param other     Address to be assigned.
         * @return          Reference to this instance.
         */
        Address& operator=(const Address& other);


        /**
         * Remove any information about this address.
         */
        void clear();


        /**
         * Get the path relative to the starting address (of which a pointer can be requested
         * with getStartingAddress), in case isRelativePath() is true.
         *
         * @return The path relative to the starting address.
         */
        std::vector<uaf::RelativePathElement> getRelativePath() const;


        /**
         * Get a pointer to the starting Address of a relative path, in case isRelativePath()
         * is true.
         *
         * @return  A pointer to the starting Address.
         */
        uaf::Address* getStartingAddress() const { return startingAddress_; }


        /**
         * Get the ExpandedNodeId in case isExpandedNodeId() is true.
         *
         * @return The ExpandedNodeId corresponding with this Address.
         */
        uaf::ExpandedNodeId getExpandedNodeId() const;


        /**
         * Check if the address is defined as an ExpandedNodeId.
         *
         * @return True if the address is in fact an ExpandedNodeId (and you're allowed to call
         *         getExpandedNodeId()), false if not.
         */
        bool isExpandedNodeId() const { return !isRelativePath_; }


        /**
         * Check if the address is defined as a RelativePath.
         *
         * @return True if the address is in fact a relative path (and you're allowed to call
         *         getStartingAddress() and getRelativePath()), false if not.
         */
        bool isRelativePath() const { return isRelativePath_; }


        /**
         * Get a string representation.
         *
         * @return String representation.
         */
        std::string toString(const std::string& indent="", std::size_t colon=20) const;


        uaf::Status toSdk(OpcUa_NodeId* uaNodeId) const;



        /**
         * Get the serverUri of the address, in case isExpandedNodeId() is true and in case the
         * serverUri is given for this address!
         *
         * @param address   The address to extract the serverUri from.
         * @param serverUri ServerUri Server URI to update.
         * @return          Good status if a serverUri could be given, Bad status if not.
         */
        friend UAF_EXPORT uaf::Status extractServerUri(
                const Address&  address,
                std::string&    serverUri);


        // comparison operators
        friend UAF_EXPORT bool operator==(const Address& object1, const Address& object2);
        friend UAF_EXPORT bool operator!=(const Address& object1, const Address& object2);
        friend UAF_EXPORT bool operator<(const Address& object1, const Address& object2);

    private:

        // Is the address a relative path, or not?
        bool isRelativePath_;

        // The relative path and its starting address in case the address is relative.
        std::vector<uaf::RelativePathElement>* relativePath_;
        uaf::Address* startingAddress_;

        // The ExpandedNodeId in case the address is absolute.
        uaf::ExpandedNodeId* expandedNodeId_;

    };



}


#endif /* UAF_ADDRESS_H_ */
