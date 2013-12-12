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

#include "uaf/util/expandednodeid.h"


namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;


    // Constructor
    // =============================================================================================
    ExpandedNodeId::ExpandedNodeId()
    : serverIndex_(0),
      serverIndexGiven_(false),
      serverUriGiven_(false)
    {}


    // Constructor
    // =============================================================================================
    ExpandedNodeId::ExpandedNodeId(
            const string&   idString,
            const string&   nameSpaceUri,
            const string&   serverUri)
    : nodeId_(idString, nameSpaceUri),
      serverUri_(serverUri),
      serverIndex_(0),
      serverIndexGiven_(false),
      serverUriGiven_(true)
    {}


    // Constructor
    // =============================================================================================
    ExpandedNodeId::ExpandedNodeId(
            const string&   idString,
            NameSpaceIndex  nameSpaceIndex,
            const string&   serverUri)
    : nodeId_(idString, nameSpaceIndex),
      serverUri_(serverUri),
      serverIndex_(0),
      serverIndexGiven_(false),
      serverUriGiven_(true)
    {}


    // Constructor
    // =============================================================================================
    ExpandedNodeId::ExpandedNodeId(
            uint32_t        idNumeric,
            const string&   nameSpaceUri,
            const string&   serverUri)
    : nodeId_(idNumeric, nameSpaceUri),
      serverUri_(serverUri),
      serverIndex_(0),
      serverIndexGiven_(false),
      serverUriGiven_(true)
    {}


    // Constructor
    // =============================================================================================
    ExpandedNodeId::ExpandedNodeId(
            uint32_t        idNumeric,
            NameSpaceIndex  nameSpaceIndex,
            const string&   serverUri)
    : nodeId_(idNumeric, nameSpaceIndex),
      serverUri_(serverUri),
      serverIndex_(0),
      serverIndexGiven_(false),
      serverUriGiven_(true)
    {}


    // Constructor
    // =============================================================================================
    ExpandedNodeId::ExpandedNodeId(
            const string&   idString,
            const string&   nameSpaceUri,
            const string&   serverUri,
            ServerIndex     serverIndex)
    : nodeId_(idString, nameSpaceUri),
      serverUri_(serverUri),
      serverIndex_(serverIndex),
      serverIndexGiven_(true),
      serverUriGiven_(true)
    {}


    // Constructor
    // =============================================================================================
    ExpandedNodeId::ExpandedNodeId(
            const string&   idString,
            NameSpaceIndex  nameSpaceIndex,
            const string&   serverUri,
            ServerIndex     serverIndex)
    : nodeId_(idString, nameSpaceIndex),
      serverUri_(serverUri),
      serverIndex_(serverIndex),
      serverIndexGiven_(true),
      serverUriGiven_(true)
    {}


    // Constructor
    // =============================================================================================
    ExpandedNodeId::ExpandedNodeId(
            uint32_t        idNumeric,
            const string&   nameSpaceUri,
            const string&   serverUri,
            ServerIndex     serverIndex)
    : nodeId_(idNumeric, nameSpaceUri),
      serverUri_(serverUri),
      serverIndex_(serverIndex),
      serverIndexGiven_(true),
      serverUriGiven_(true)
    {}


    // Constructor
    // =============================================================================================
    ExpandedNodeId::ExpandedNodeId(
            uint32_t        idNumeric,
            NameSpaceIndex  nameSpaceIndex,
            const string&   serverUri,
            ServerIndex     serverIndex)
    : nodeId_(idNumeric, nameSpaceIndex),
      serverUri_(serverUri),
      serverIndex_(serverIndex),
      serverIndexGiven_(true),
      serverUriGiven_(true)
    {}


    // Constructor
    // =============================================================================================
    ExpandedNodeId::ExpandedNodeId(
            const string&   idString,
            const string&   nameSpaceUri,
            ServerIndex     serverIndex)
    : nodeId_(idString, nameSpaceUri),
      serverIndex_(serverIndex),
      serverIndexGiven_(true),
      serverUriGiven_(false)
    {}


    // Constructor
    // =============================================================================================
    ExpandedNodeId::ExpandedNodeId(
            const string&   idString,
            NameSpaceIndex  nameSpaceIndex,
            ServerIndex     serverIndex)
    : nodeId_(idString, nameSpaceIndex),
      serverIndex_(serverIndex),
      serverIndexGiven_(true),
      serverUriGiven_(false)
    {}


    // Constructor
    // =============================================================================================
    ExpandedNodeId::ExpandedNodeId(
            uint32_t        idNumeric,
            const string&   nameSpaceUri,
            ServerIndex     serverIndex)
    : nodeId_(idNumeric, nameSpaceUri),
      serverIndex_(serverIndex),
      serverIndexGiven_(true),
      serverUriGiven_(false)
    {}


    // Constructor
    // =============================================================================================
    ExpandedNodeId::ExpandedNodeId(
            uint32_t             idNumeric,
            NameSpaceIndex       nameSpaceIndex,
            ServerIndex          serverIndex)
    : nodeId_(idNumeric, nameSpaceIndex),
      serverIndex_(serverIndex),
      serverIndexGiven_(true),
      serverUriGiven_(false)
    {}


    // Constructor
    // =============================================================================================
    ExpandedNodeId::ExpandedNodeId(
            const NodeId&   nodeId,
            const string&   serverUri,
            ServerIndex     serverIndex)
    : nodeId_(nodeId),
      serverUri_(serverUri),
      serverIndex_(serverIndex),
      serverIndexGiven_(true),
      serverUriGiven_(true)
    {}


    // Constructor
    // =============================================================================================
    ExpandedNodeId::ExpandedNodeId(
            const NodeId&   nodeId,
            const string&   serverUri)
    : nodeId_(nodeId),
      serverUri_(serverUri),
      serverIndex_(0),
      serverIndexGiven_(false),
      serverUriGiven_(true)
    {}


    // Constructor
    // =============================================================================================
    ExpandedNodeId::ExpandedNodeId(
            const NodeId&   nodeId,
            ServerIndex     serverIndex)
    : nodeId_(nodeId),
      serverIndex_(serverIndex),
      serverIndexGiven_(true),
      serverUriGiven_(false)
    {}


    // Get a string representation
    // =============================================================================================
    string ExpandedNodeId::toString() const
    {
        stringstream ss;

        ss << "Svr";

        if (serverIndexGiven_)
            ss << "=" << serverIndex_;

        if (serverUriGiven_)
            ss << "='" << serverUri_ << "'";

        if ( (!serverIndexGiven_) && (!serverUriGiven_) )
            ss << "=???";

        ss << "|" << nodeId_.toString();

        return ss.str();
    }


    // Update a stack expanded node id object.
    // =============================================================================================
    void ExpandedNodeId::toSdk(OpcUa_ExpandedNodeId *destination) const
    {
        nodeId_.toSdk(&destination->NodeId);
        UaString(serverUri_.c_str()).copyTo(&destination->NamespaceUri);
        destination->ServerIndex = serverIndex_;
    }


    // Update an SDK expanded node id object.
    // =============================================================================================
    void ExpandedNodeId::toSdk(UaExpandedNodeId& destination) const
    {
        UaNodeId nodeId;
        nodeId_.toSdk(nodeId);
        destination.setExpandedNodeId(nodeId, UaString(serverUri_.c_str()), serverIndex_);
    }


    // Fill out the NodeId with information from an OpcUa_ExpandedNodeId instance
    // =============================================================================================
    Status ExpandedNodeId::fromSdk(
            const OpcUa_ExpandedNodeId& opcUaExpandedNodeId,
            const string&               nameSpaceUri,
            const string&               serverUri)
    {
        serverUri_          = serverUri;
        serverUriGiven_     = true;
        serverIndex_        = opcUaExpandedNodeId.ServerIndex;
        serverIndexGiven_   = true;
        return nodeId_.fromSdk(opcUaExpandedNodeId.NodeId, nameSpaceUri);
    }


    // Fill out the NodeId with information from an OpcUa_ExpandedNodeId instance
    // =============================================================================================
    Status ExpandedNodeId::fromSdk(
            const OpcUa_ExpandedNodeId& opcUaExpandedNodeId,
            const string&               nameSpaceUri)
    {
        serverIndex_        = opcUaExpandedNodeId.ServerIndex;
        serverIndexGiven_   = true;
        return nodeId_.fromSdk(opcUaExpandedNodeId.NodeId, nameSpaceUri);
    }


    // Fill out the NodeId with information from an UaExpandedNodeId instance
    // =============================================================================================
    Status ExpandedNodeId::fromSdk(
            const UaExpandedNodeId& uaExpandedNodeId,
            const string&           nameSpaceUri,
            const string&           serverUri)
    {
        serverUri_          = serverUri;
        serverUriGiven_     = true;
        serverIndex_        = uaExpandedNodeId.serverIndex();
        serverIndexGiven_   = true;
        return nodeId_.fromSdk(uaExpandedNodeId.nodeId(), nameSpaceUri);
    }


    // Fill out the NodeId with information from an UaExpandedNodeId instance
    // =============================================================================================
    Status ExpandedNodeId::fromSdk(const UaExpandedNodeId& uaExpandedNodeId)
    {
        serverUriGiven_     = false;
        serverIndex_        = uaExpandedNodeId.serverIndex();
        serverIndexGiven_   = true;
        return nodeId_.fromSdk(uaExpandedNodeId.nodeId());
    }


    // operator==
    // =============================================================================================
    bool operator==(const ExpandedNodeId& object1, const ExpandedNodeId& object2)
    {
        return    object1.nodeId_ == object2.nodeId_
               && object1.serverIndex_ == object2.serverIndex_
               && object1.serverUri_ == object2.serverUri_;
    }


    // operator!=
    // =============================================================================================
    bool operator!=(const ExpandedNodeId& object1, const ExpandedNodeId& object2)
    {
        return !(object1 == object2);
    }

    // operator<
    // =============================================================================================
    bool operator<(const ExpandedNodeId& object1, const ExpandedNodeId& object2)
    {
        if (object1.nodeId_ != object2.nodeId_)
        {
            return object1.nodeId_ < object2.nodeId_;
        }
        else if (object1.serverIndex_ != object2.serverIndex_)
        {
            return object1.serverIndex_ < object2.serverIndex_;
        }
        else
        {
            return object1.serverUri_ < object2.serverUri_;
        }
    }


}
