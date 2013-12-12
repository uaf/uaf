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

#ifndef UAF_NODEID_H_
#define UAF_NODEID_H_

// STD
#include <string>
#include <sstream>
// UAF
#include "uaf/util/util.h"
#include "uaf/util/constants.h"
#include "uaf/util/nodeididentifier.h"
// SDK


namespace uaf
{

    /**
     * An OPC UA namespace index is used to relate something (e.g. a NodeIdIdentifier) to a
     * namespace URI via a namespace array.
     *
     * @ingroup Util
     */
    typedef uint16_t NameSpaceIndex;


    /*******************************************************************************************//**
    * A NodeId is the unique "address" of a node within the address space of an OPC UA server.
    *
    * @ingroup Util
    ***********************************************************************************************/
    class UAF_EXPORT NodeId
    {
    public:


        /**
         * Construct an empty NodeId.
         */
        NodeId();


        /**
         * Construct a NodeId based on a string identifier and a namespace URI.
         *
         * @param idString          String identifier of the NodeId.
         * @param nameSpaceUri      Namespace URI of the NodeId.
         */
        NodeId(const std::string&   idString,
               const std::string&   nameSpaceUri);


        /**
         * Construct a NodeId based on a string identifier and a namespace URI and a namespace
         * Index.
         *
         * @param idString          String identifier of the NodeId.
         * @param nameSpaceUri      Namespace URI of the NodeId.
         * @param nameSpaceIndex    Namespace index of the NodeId.
         */
        NodeId(const std::string&   idString,
               const std::string&   nameSpaceUri,
               uaf::NameSpaceIndex  nameSpaceIndex);


        /**
         * Construct a NodeId based on a string identifier and a namespace index.
         *
         * @param idString          String identifier of the NodeId.
         * @param nameSpaceIndex    Namespace index of the NodeId.
         */
        NodeId(const std::string&   idString,
               uaf::NameSpaceIndex  nameSpaceIndex);


        /**
         * Construct a NodeId based on a numerical identifier and a namespace URI.
         *
         * @param idNumeric         Numerical identifier of the NodeId.
         * @param nameSpaceUri      Namespace URI of the NodeId.
         */
        NodeId(uint32_t             idNumeric,
               const std::string&   nameSpaceUri);


        /**
         * Construct a NodeId based on a numerical identifier and a namespace URI and a namespace
         * index.
         *
         * @param idNumeric         Numerical identifier of the NodeId.
         * @param nameSpaceUri      Namespace URI of the NodeId.
         * @param nameSpaceIndex    Namespace index of the NodeId.
         */
        NodeId(uint32_t             idNumeric,
               const std::string&   nameSpaceUri,
               uaf::NameSpaceIndex  nameSpaceIndex);


        /**
         * Construct a NodeId based on a numerical identifier and a namespace index.
         *
         * @param idNumeric         Numerical identifier of the NodeId.
         * @param nameSpaceIndex    Namespace index of the NodeId.
         */
        NodeId(uint32_t             idNumeric,
               uaf::NameSpaceIndex  nameSpaceIndex);


        /**
         * Is a namespace index provided?
         *
         * @return  True if the NodeId has a namespace index.
         */
        bool hasNameSpaceIndex() const { return nameSpaceIndexGiven_; }


        /**
         * Is a namespace URI provided?
         *
         * @return  True if the NodeId has a namespace URI.
         */
        bool hasNameSpaceUri() const { return nameSpaceUriGiven_ && (!nameSpaceUri_.empty()); }


        /**
         * Get the namespace index (in case hasNameSpaceIndex is True).
         *
         * @return  The namespace index of the NodeId.
         */
        uaf::NameSpaceIndex nameSpaceIndex() const { return nameSpaceIndex_; }


        /**
         * Get the namespace URI (in case hasNameSpaceUri is True).
         *
         * @return  The namespace URI of the NodeId.
         */
        std::string nameSpaceUri()   const { return nameSpaceUri_; }


        /**
         * Set the namespace index.
         *
         * @param index The namespace index of the NodeId.
         */
        void setNameSpaceIndex(uaf::NameSpaceIndex index)
        { nameSpaceIndex_ = index; nameSpaceIndexGiven_ = true; }


        /**
         * Set the namespace URI.
         *
         * @param uri   The namespace URI of the NodeId.
         */
        void setNameSpaceUri(const std::string& uri)
        { nameSpaceUri_ = uri; nameSpaceUriGiven_ = true; }


        /**
         * Was the NodeId initialized with some contents?
         *
         * @return  True if the NodeId does not have any contents.
         */
        bool isNull() const;


        /**
         * Get the identifier of the NodeId.
         *
         * @return  The identifier part of the NodeId.
         */
        uaf::NodeIdIdentifier identifier() const { return identifier_; }


        /**
         * Get a string representation.
         *
         * @return String representation.
         */
        std::string toString() const;


        /**
         * Update a stack OpcUa_NodeId object.
         *
         * @param destination   Stack object to be modified.
         */
        uaf::Status toSdk(OpcUa_NodeId *destination) const;


        /**
         * Update a stack OpcUa_NodeId object.
         *
         * @param destination   Stack object to be modified.
         */
        uaf::Status toSdk(UaNodeId& destination) const;


        /**
         * Construct a NodeId based on a stack OpcUa_NodeId instance and a namespace URI.
         *
         * @param opcUaNodeId       OPC UA stack OpcUa_NodeId instance.
         * @param nameSpaceUri      Namespace URI of the NodeId.
         * @return                  Good in case the NodeId was successfully updated.
         */
        uaf::Status fromSdk(const OpcUa_NodeId& opcUaNodeId,const std::string& nameSpaceUri);


        /**
         * Construct a NodeId based on a stack OpcUa_NodeId instance.
         *
         * @param opcUaNodeId       OPC UA stack OpcUa_NodeId instance.
         * @return                  Good in case the NodeId was successfully updated.
         */
        uaf::Status fromSdk(const OpcUa_NodeId& opcUaNodeId);


        /**
         * Construct a NodeId based on an SDK UaNodeId instance and a namespace URI.
         *
         * @param uaNodeId      SDK UaNodeId instance.
         * @param nameSpaceUri  Namespace URI of the NodeId.
         * @return              Good in case the NodeId was successfully updated.
         */
        uaf::Status fromSdk(const UaNodeId& uaNodeId, const std::string& nameSpaceUri);


        /**
         * Construct a NodeId based on an SDK UaNodeId instance.
         *
         * @param uaNodeId          SDK UaNodeId instance.
         * @return                  Good in case the NodeId was successfully updated.
         */
        uaf::Status fromSdk(const UaNodeId& uaNodeId);



        // comparison operators
        friend UAF_EXPORT bool operator==(const NodeId& object1, const NodeId& object2);
        friend UAF_EXPORT bool operator!=(const NodeId& object1, const NodeId& object2);
        friend UAF_EXPORT bool operator<(const NodeId& object1, const NodeId& object2);

    private:
        // namespace index
        uaf::NameSpaceIndex     nameSpaceIndex_;
        // namespace URI
        std::string             nameSpaceUri_;
        // identifier part of the NodeId
        uaf::NodeIdIdentifier   identifier_;
        // true if a namespace index was provided
        bool                    nameSpaceIndexGiven_;
        // true if a namespace URI was provided
        bool                    nameSpaceUriGiven_;
    };

}



#endif /* UAF_NODEID_H_ */
