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

#ifndef UAF_EXPANDEDNODEID_H_
#define UAF_EXPANDEDNODEID_H_

// STD
#include <string>
#include <sstream>
// SDK
// UAF
#include "uaf/util/util.h"
#include "uaf/util/nodeid.h"
#include "uaf/util/serverarray.h"


namespace uaf
{


    /*******************************************************************************************//**
    * An ExpandedNodeId is fully identifies the node by means of a NodeId part, and a part
    * containing the serverIndex and/or serverUri of the server hosting the node.
    *
    * @ingroup Util
    ***********************************************************************************************/
    class UAF_EXPORT ExpandedNodeId
    {
    public:


        /**
         * Construct an empty ExpandedNodeId.
         */
        ExpandedNodeId();


        /**
         * Construct an ExpandedNodeId from a string identifier, a namespace URI and a server URI.
         *
         * @param idString          String identifier of the NodeId.
         * @param nameSpaceUri      Namespace URI of the NodeId.
         * @param serverUri         URI of the server hosting this NodeId.
         */
        ExpandedNodeId(
                const std::string&   idString,
                const std::string&   nameSpaceUri,
                const std::string&   serverUri);


        /**
         * Construct an ExpandedNodeId from a string identifier, a namespace index and a server URI.
         *
         * @param idString          String identifier of the NodeId.
         * @param nameSpaceIndex    Namespace Index of the NodeId.
         * @param serverUri         URI of the server hosting this NodeId.
         */
        ExpandedNodeId(
                const std::string&   idString,
                uaf::NameSpaceIndex  nameSpaceIndex,
                const std::string&   serverUri);


        /**
         * Construct an ExpandedNodeId from a numerical identifier, a namespace URI and a server
         * URI.
         *
         * @param idNumeric         Numerical identifier of the NodeId.
         * @param nameSpaceUri      Namespace URI of the NodeId.
         * @param serverUri         URI of the server hosting this NodeId.
         */
        ExpandedNodeId(
                uint32_t             idNumeric,
                const std::string&   nameSpaceUri,
                const std::string&   serverUri);


        /**
         * Construct an ExpandedNodeId from a numerical identifier, a namespace index and a server
         * URI.
         *
         * @param idNumeric         Numerical identifier of the NodeId.
         * @param nameSpaceIndex    Namespace Index of the NodeId.
         * @param serverUri         URI of the server hosting this NodeId.
         */
        ExpandedNodeId(
                uint32_t             idNumeric,
                uaf::NameSpaceIndex  nameSpaceIndex,
                const std::string&   serverUri);


        /**
         * Construct an ExpandedNodeId from a string identifier, a namespace URI and a server
         * index.
         *
         * @param idString          String identifier of the NodeId.
         * @param nameSpaceUri      Namespace URI of the NodeId.
         * @param serverIndex       Index of the server hosting this NodeId.
         */
        ExpandedNodeId(
                const std::string&   idString,
                const std::string&   nameSpaceUri,
                uaf::ServerIndex     serverIndex);

        /**
         * Construct an ExpandedNodeId from a string identifier, a namespace Index and a server
         * index.
         *
         * @param idString          String identifier of the NodeId.
         * @param nameSpaceIndex    Namespace Index of the NodeId.
         * @param serverIndex       Index of the server hosting this NodeId.
         */
        ExpandedNodeId(
                const std::string&   idString,
                uaf::NameSpaceIndex  nameSpaceIndex,
                uaf::ServerIndex     serverIndex);


        /**
         * Construct an ExpandedNodeId from a numerical identifier, a namespace URI and a server
         * index.
         *
         * @param idNumeric         Numerical identifier of the NodeId.
         * @param nameSpaceUri      Namespace URI of the NodeId.
         * @param serverIndex       Index of the server hosting this NodeId.
         */
        ExpandedNodeId(
                uint32_t             idNumeric,
                const std::string&   nameSpaceUri,
                uaf::ServerIndex     serverIndex);


        /**
         * Construct an ExpandedNodeId from a numerical identifier, a namespace Index and a server
         * index.
         *
         * @param idNumeric         Numerical identifier of the NodeId.
         * @param nameSpaceIndex    Namespace Index of the NodeId.
         * @param serverIndex       Index of the server hosting this NodeId.
         */
        ExpandedNodeId(
                uint32_t             idNumeric,
                uaf::NameSpaceIndex  nameSpaceIndex,
                uaf::ServerIndex     serverIndex);


        /**
         * Construct an ExpandedNodeId from a string identifier, a namespace URI and a server URI.
         *
         * @param idString          String identifier of the NodeId.
         * @param nameSpaceUri      Namespace URI of the NodeId.
         * @param serverUri         URI of the server hosting this NodeId.
         * @param serverIndex       Index of the server hosting this NodeId.
         */
        ExpandedNodeId(
                const std::string&   idString,
                const std::string&   nameSpaceUri,
                const std::string&   serverUri,
                uaf::ServerIndex     serverIndex);


        /**
         * Construct an ExpandedNodeId from a string identifier, a namespace index and a server URI.
         *
         * @param idString          String identifier of the NodeId.
         * @param nameSpaceIndex    Namespace Index of the NodeId.
         * @param serverUri         URI of the server hosting this NodeId.
         * @param serverIndex       Index of the server hosting this NodeId.
         */
        ExpandedNodeId(
                const std::string&   idString,
                uaf::NameSpaceIndex  nameSpaceIndex,
                const std::string&   serverUri,
                uaf::ServerIndex     serverIndex);


        /**
         * Construct an ExpandedNodeId from a numerical identifier, a namespace URI and a server
         * URI.
         *
         * @param idNumeric         Numerical identifier of the NodeId.
         * @param nameSpaceUri      Namespace URI of the NodeId.
         * @param serverUri         URI of the server hosting this NodeId.
         * @param serverIndex       Index of the server hosting this NodeId.
         */
        ExpandedNodeId(
                uint32_t             idNumeric,
                const std::string&   nameSpaceUri,
                const std::string&   serverUri,
                uaf::ServerIndex     serverIndex);


        /**
         * Construct an ExpandedNodeId from a numerical identifier, a namespace index and a server
         * URI.
         *
         * @param idNumeric         Numerical identifier of the NodeId.
         * @param nameSpaceIndex    Namespace Index of the NodeId.
         * @param serverUri         URI of the server hosting this NodeId.
         * @param serverIndex       Index of the server hosting this NodeId.
         */
        ExpandedNodeId(
                uint32_t             idNumeric,
                uaf::NameSpaceIndex  nameSpaceIndex,
                const std::string&   serverUri,
                uaf::ServerIndex     serverIndex);


        /**
         * Construct an ExpandedNodeId from a NodeId and a server URI.
         *
         * @param nodeId            A NodeId.
         * @param serverIndex       Index of the server hosting this NodeId.
         * @param serverUri         URI of the server hosting this NodeId.
         */
        ExpandedNodeId(
                const uaf::NodeId&   nodeId,
                const std::string&   serverUri,
                uaf::ServerIndex     serverIndex);


        /**
         * Construct an ExpandedNodeId from a NodeId and a server URI.
         *
         * @param nodeId            A NodeId.
         * @param serverUri         URI of the server hosting this NodeId.
         */
        ExpandedNodeId(
                const uaf::NodeId&   nodeId,
                const std::string&   serverUri);


        /**
         * Construct an ExpandedNodeId from a NodeId and a server index.
         *
         * @param nodeId            A NodeId.
         * @param serverIndex       Index of the server hosting this NodeId.
         */
        ExpandedNodeId(
                const uaf::NodeId&   nodeId,
                uaf::ServerIndex     serverIndex);


        /**
         * Check if a server index was given.
         *
         * @return  True if a serverIndex has been defined, false if not.
         */
        bool hasServerIndex() const { return serverIndexGiven_; }


        /**
         * Check if a non-empty server URI was given.
         *
         * @return  True if this ExpandedNodeId contains a non-empty server URI, false if not.
         */
        bool hasServerUri()   const { return serverUriGiven_ && (!serverUri_.empty()); }


        /**
         * Get the server index of the ExpandedNodeId.
         *
         * This function will always return an integer, so call hasServerIndex to see if it's a
         * valid one.
         *
         * @return  The server index.
         */
        uaf::ServerIndex  serverIndex() const { return serverIndex_; }


        /**
         * Get the server URI of the ExpandedNodeId.
         *
         * This function will always return a string, so call hasServerUri to see if it's a
         * valid one.
         *
         * @return  The server index.
         */
        const std::string& serverUri() const { return serverUri_; }


        /**
         * Get the NodeId part of the ExpandedNodeId.
         *
         * @return  The NodeId part of the ExpandedNodeId.
         */
        const uaf::NodeId& nodeId() const { return nodeId_; }


        /**
         * Get the NodeId part of the ExpandedNodeId.
         *
         * @return  The NodeId part of the ExpandedNodeId.
         */
        uaf::NodeId& nodeId() { return nodeId_; }


        /**
         * Get a string representation.
         *
         * @return String representation.
         */
        virtual std::string toString() const;


        /**
         * Update the given OpcUa_ExpandedNodeId stack object.
         *
         * @param destination   The OpcUa_ExpandedNodeId instance to be modified.
         */
        void toSdk(OpcUa_ExpandedNodeId *destination) const;


        /**
         * Update the given UaExpandedNodeId SDK object.
         *
         * @param destination   The UaExpandedNodeId instance to be modified.
         */
        void toSdk(UaExpandedNodeId& destination) const;


        /**
         * Construct an ExpandedNodeId based on a stack OpcUa_ExpandedNodeId instance, a namespace
         * URI and a server URI.
         *
         * @param opcUaExpandedNodeId   OPC UA stack OpcUa_ExpandedNodeId instance.
         * @param nameSpaceUri          Namespace URI of the NodeId.
         * @param serverUri             Server URI of the ExpandedNodeId.
         * @return                      Good in case the ExpandedNodeId was successfully updated.
         */
        uaf::Status fromSdk(
                const OpcUa_ExpandedNodeId& opcUaExpandedNodeId,
                const std::string&          nameSpaceUri,
                const std::string&          serverUri);


        /**
         * Construct an ExpandedNodeId based on an SDK UaExpandedNodeId instance.
         *
         * @param uaExpandedNodeId  OPC UA stack OpcUa_ExpandedNodeId instance.
         * @param nameSpaceUri      Namespace URI of the NodeId.
         * @param serverUri         Server URI of the ExpandedNodeId.
         * @return                  Good in case the ExpandedNodeId was successfully updated.
         */
        uaf::Status fromSdk(
                const UaExpandedNodeId& uaExpandedNodeId,
                const std::string&      nameSpaceUri,
                const std::string&      serverUri);


        /**
         * Construct an ExpandedNodeId based on an SDK UaExpandedNodeId instance.
         *
         * @param uaExpandedNodeId  OPC UA stack OpcUa_ExpandedNodeId instance.
         * @return                  Good in case the ExpandedNodeId was successfully updated.
         */
        uaf::Status fromSdk(const UaExpandedNodeId& uaExpandedNodeId);


        // comparison operators
        friend UAF_EXPORT bool operator==(
                const ExpandedNodeId& object1,
                const ExpandedNodeId& object2);
        friend UAF_EXPORT bool operator!=(
                const ExpandedNodeId& object1,
                const ExpandedNodeId& object2);
        friend UAF_EXPORT bool operator<(
                const ExpandedNodeId& object1,
                const ExpandedNodeId& object2);


    private:
        // the NodeId part of the ExpandedNodeId
        uaf::NodeId nodeId_;
        // the server URI (if given)
        std::string serverUri_;
        // the server index (if given)
        uaf::ServerIndex  serverIndex_;
        // true if a server index was given
        bool serverIndexGiven_;
        // true if a server URI was given
        bool serverUriGiven_;

    };

}



#endif /* UAF_EXPANDEDNODEID_H_ */
