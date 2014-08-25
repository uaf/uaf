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

#include "uaf/util/nodeid.h"


namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;


    // Constructor
    // =============================================================================================
    NodeId::NodeId()
    : nameSpaceIndex_(0),
      nameSpaceIndexGiven_(false),
      nameSpaceUriGiven_(false)
    {}


    // Constructor
    // =============================================================================================
    NodeId::NodeId(const string& idString, const string& nameSpaceUri)
    : nameSpaceIndex_(0),
      nameSpaceUri_(nameSpaceUri),
      identifier_(idString),
      nameSpaceIndexGiven_(false),
      nameSpaceUriGiven_(true)
    {}


    // Constructor
    // =============================================================================================
    NodeId::NodeId(
            const string& idString,
            const string& nameSpaceUri,
            NameSpaceIndex nameSpaceIndex)
    : nameSpaceIndex_(nameSpaceIndex),
      nameSpaceUri_(nameSpaceUri),
      identifier_(idString),
      nameSpaceIndexGiven_(true),
      nameSpaceUriGiven_(true)
    {}


    // Constructor
    // =============================================================================================
    NodeId::NodeId(const string& idString, NameSpaceIndex nameSpaceIndex)
    : nameSpaceIndex_(nameSpaceIndex),
      identifier_(idString),
      nameSpaceIndexGiven_(true),
      nameSpaceUriGiven_(false)
    {}


    // Constructor
    // =============================================================================================
    NodeId::NodeId(uint32_t idNumeric, const string& nameSpaceUri)
    : nameSpaceIndex_(0),
      nameSpaceUri_(nameSpaceUri),
      identifier_(idNumeric),
      nameSpaceIndexGiven_(false),
      nameSpaceUriGiven_(true)
    {}


    // Constructor
    // =============================================================================================
    NodeId::NodeId(uint32_t idNumeric, const string& nameSpaceUri, NameSpaceIndex nameSpaceIndex)
    : nameSpaceIndex_(nameSpaceIndex),
      nameSpaceUri_(nameSpaceUri),
      identifier_(idNumeric),
      nameSpaceIndexGiven_(true),
      nameSpaceUriGiven_(true)
    {}


    // Constructor
    // =============================================================================================
    NodeId::NodeId(uint32_t idNumeric, NameSpaceIndex nameSpaceIndex)
    : nameSpaceIndex_(nameSpaceIndex),
      identifier_(idNumeric),
      nameSpaceIndexGiven_(true),
      nameSpaceUriGiven_(false)
    {}


    // Constructor
    // =============================================================================================
    NodeId::NodeId(const Guid& idGuid, const string& nameSpaceUri)
    : nameSpaceIndex_(0),
      nameSpaceUri_(nameSpaceUri),
      identifier_(idGuid),
      nameSpaceIndexGiven_(false),
      nameSpaceUriGiven_(true)
    {}


    // Constructor
    // =============================================================================================
    NodeId::NodeId(const Guid& idGuid, const string& nameSpaceUri, NameSpaceIndex nameSpaceIndex)
    : nameSpaceIndex_(nameSpaceIndex),
      nameSpaceUri_(nameSpaceUri),
      identifier_(idGuid),
      nameSpaceIndexGiven_(true),
      nameSpaceUriGiven_(true)
    {}


    // Constructor
    // =============================================================================================
    NodeId::NodeId(const Guid& idGuid, NameSpaceIndex nameSpaceIndex)
    : nameSpaceIndex_(nameSpaceIndex),
      identifier_(idGuid),
      nameSpaceIndexGiven_(true),
      nameSpaceUriGiven_(false)
    {}


    // Constructor
    // =============================================================================================
    NodeId::NodeId(const NodeIdIdentifier& identifier, const string& nameSpaceUri)
    : nameSpaceIndex_(0),
      nameSpaceUri_(nameSpaceUri),
      identifier_(identifier),
      nameSpaceIndexGiven_(false),
      nameSpaceUriGiven_(true)
    {}


    // Constructor
    // =============================================================================================
    NodeId::NodeId(const NodeIdIdentifier& identifier, const string& nameSpaceUri, NameSpaceIndex nameSpaceIndex)
    : nameSpaceIndex_(nameSpaceIndex),
      nameSpaceUri_(nameSpaceUri),
      identifier_(identifier),
      nameSpaceIndexGiven_(true),
      nameSpaceUriGiven_(true)
    {}


    // Constructor
    // =============================================================================================
    NodeId::NodeId(const NodeIdIdentifier& identifier, NameSpaceIndex nameSpaceIndex)
    : nameSpaceIndex_(nameSpaceIndex),
      identifier_(identifier),
      nameSpaceIndexGiven_(true),
      nameSpaceUriGiven_(false)
    {}


    // Is the NodeId NULL?
    // =============================================================================================
    bool NodeId::isNull() const
    {
        return     (nameSpaceIndexGiven_ == false)
                && (nameSpaceUriGiven_ == false)
                && (nameSpaceIndex_ == 0)
                && identifier_.isNull();
    }


    // Get a string representation
    // =============================================================================================
    string NodeId::toString() const
    {
        stringstream ss;

        ss << "Ns";

        if (nameSpaceIndexGiven_)
            ss << "=" << nameSpaceIndex_;

        if (nameSpaceUriGiven_)
            ss << "='" << nameSpaceUri_ << "'";

        if ( (!nameSpaceIndexGiven_) && (!nameSpaceUriGiven_) )
            ss << "=???";

        ss << "|" << identifier_.toString();

        return ss.str();
    }


    // Copy to SDK object
    // =============================================================================================
    Status NodeId::toSdk(UaNodeId& destination) const
    {
        Status ret;

        if (hasNameSpaceIndex() || nameSpaceUri() == uaf::constants::OPCUA_NAMESPACE_URI)
        {
            // fill the just created UaNodeId
            if (identifier_.type == nodeididentifiertypes::Identifier_String)
            {
                destination.setNodeId(identifier_.idString.c_str(), nameSpaceIndex_);
                ret.setGood();
            }
            else if (identifier_.type == nodeididentifiertypes::Identifier_Numeric)
            {
                destination.setNodeId(identifier_.idNumeric, nameSpaceIndex_);
                ret.setGood();
            }
            else if (identifier_.type == nodeididentifiertypes::Identifier_Guid)
            {
                UaGuid uaGuid;
                identifier_.idGuid.toSdk(uaGuid);
                destination.setNodeId(uaGuid, nameSpaceIndex_);
                ret.setGood();
            }
            else if (identifier_.type == nodeididentifiertypes::Identifier_Opaque)
            {
                UaByteString uaOpaque;
                identifier_.idOpaque.toSdk(uaOpaque);
                destination.setNodeId(uaOpaque, nameSpaceIndex_);
                ret.setGood();
            }
            else
            {
                ret.setStatus(uaf::statuscodes::UnexpectedError, "Unknown NodeId identifier!");
            }
        }
        else
        {
            // update the status
            ret.setStatus(statuscodes::UnexpectedError,
                          "Cannot prepare an OpcUa_NodeId since no namespace index is known");
        }

        return ret;
    }


    // Copy to stack object
    // =============================================================================================
    Status NodeId::toSdk(OpcUa_NodeId *destination) const
    {
        Status ret;

        UaNodeId uaNodeId;
        ret = toSdk(uaNodeId);

        if (ret.isGood())
            uaNodeId.copyTo(destination);

        return ret;
    }


    // Fill out the NodeId with information from an OpcUa_NodeId instance
    // =============================================================================================
    Status NodeId::fromSdk(const OpcUa_NodeId& opcUaNodeId, const string& nameSpaceUri)
    {
        nameSpaceIndexGiven_ = true;
        nameSpaceUriGiven_ = true;
        nameSpaceIndex_ = opcUaNodeId.NamespaceIndex;
        nameSpaceUri_ = nameSpaceUri;
        return identifier_.fromSdk(opcUaNodeId);
    }


    // Fill out the NodeId with information from an OpcUa_NodeId instance
    // =============================================================================================
    Status NodeId::fromSdk(const OpcUa_NodeId& opcUaNodeId)
    {
        nameSpaceIndexGiven_ = true;
        nameSpaceUriGiven_ = false;
        nameSpaceIndex_ = opcUaNodeId.NamespaceIndex;
        return identifier_.fromSdk(opcUaNodeId);
    }


    // Fill out the NodeId with information from an UaNodeId instance
    // =============================================================================================
    Status NodeId::fromSdk(const UaNodeId& uaNodeId, const string& nameSpaceUri)
    {
        OpcUa_NodeId sdkNodeId;
        uaNodeId.copyTo(&sdkNodeId);
        return fromSdk(sdkNodeId, nameSpaceUri);
    }


    // Fill out the NodeId with information from an UaNodeId instance
    // =============================================================================================
    Status NodeId::fromSdk(const UaNodeId& uaNodeId)
    {
        OpcUa_NodeId sdkNodeId;
        uaNodeId.copyTo(&sdkNodeId);
        return fromSdk(sdkNodeId);
    }


    // operator==
    // =============================================================================================
    bool operator==(const NodeId& object1, const NodeId& object2)
    {
        return    object1.identifier_ == object2.identifier_
               && object1.nameSpaceIndex_ == object2.nameSpaceIndex_
               && object1.nameSpaceUri_ == object2.nameSpaceUri_;
    }


    // operator!=
    // =============================================================================================
    bool operator!=(const NodeId& object1, const NodeId& object2)
    {
        return !(object1 == object2);
    }


    // operator<
    // =============================================================================================
    bool operator<(const NodeId& object1, const NodeId& object2)
    {
        if (object1.identifier_ != object2.identifier_)
        {
            return object1.identifier_ < object2.identifier_;
        }
        else if (object1.nameSpaceIndex_ != object2.nameSpaceIndex_)
        {
            return object1.nameSpaceIndex_ < object2.nameSpaceIndex_;
        }
        else
        {
            return object1.nameSpaceUri_ < object2.nameSpaceUri_;
        }
    }

}
