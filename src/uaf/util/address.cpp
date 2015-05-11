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

#include "uaf/util/address.h"


namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;
    using std::vector;
    using std::size_t;


    // Constructor
    // =============================================================================================
    Address::Address()
    : isRelativePath_(false),
      isStartingAddressOwned_(false),
      relativePath_(0),
      startingAddress_(0),
      expandedNodeId_(new ExpandedNodeId)
    {}


    // Constructor
    // =============================================================================================
    Address::Address(Address* startingAddress, const vector<RelativePathElement>& relativePath)
    : isRelativePath_(true),
      isStartingAddressOwned_(false),
      relativePath_(new vector<RelativePathElement>(relativePath)),
      startingAddress_(startingAddress),
      expandedNodeId_(0)
    {}


    // Constructor
    // =============================================================================================
    Address::Address(Address* startingAddress, const RelativePathElement& relativePath)
    : isRelativePath_(true),
      isStartingAddressOwned_(false),
      startingAddress_(startingAddress),
      expandedNodeId_(0)
    {
        relativePath_ = new vector<RelativePathElement>();
        relativePath_->push_back(relativePath);
    }



    // Constructor
    // =============================================================================================
    Address::Address(const uaf::BrowsePath& browsePath)
    : isRelativePath_(true),
      isStartingAddressOwned_(true),
      relativePath_(new vector<RelativePathElement>(browsePath.relativePath)),
      startingAddress_(new Address(browsePath.startingExpandedNodeId)),
      expandedNodeId_(0)
    {}


    // Constructor
    // =============================================================================================
    Address::Address(const uaf::ExpandedNodeId& expandedNodeId)
    : isRelativePath_(false),
      isStartingAddressOwned_(false),
      relativePath_(0),
      startingAddress_(0),
      expandedNodeId_(new ExpandedNodeId(expandedNodeId))
    {}


    // Constructor
    // =============================================================================================
    Address::Address(const uaf::NodeId& nodeId, const std::string& serverUri)
    : isRelativePath_(false),
      isStartingAddressOwned_(false),
      relativePath_(0),
      startingAddress_(0),
      expandedNodeId_(new ExpandedNodeId(nodeId, serverUri))
    {}


    // Constructor
    // =============================================================================================
    Address::Address(const Address& other)
    {
        isRelativePath_ = other.isRelativePath_;
        isStartingAddressOwned_ = other.isStartingAddressOwned_;
        
        if (isRelativePath_)
        {
            relativePath_    = new vector<RelativePathElement>(*other.relativePath_);
            
            if (isStartingAddressOwned_)
                startingAddress_ = new Address(*other.startingAddress_);
            else
                startingAddress_ = other.startingAddress_;
        }
        else
        {
            expandedNodeId_ = new ExpandedNodeId(*other.expandedNodeId_);
        }
    }


    // Assignment operator
    // =============================================================================================
    Address& Address::operator=(const Address& other)
    {
        // protect for self-assignment
        if (&other != this)
        {
            clear();

            isRelativePath_ = other.isRelativePath_;
            isStartingAddressOwned_ = other.isStartingAddressOwned_;
            if (isRelativePath_)
            {
                relativePath_    = new vector<RelativePathElement>(*other.relativePath_);
                
                if (isStartingAddressOwned_)
                    startingAddress_ = new Address(*other.startingAddress_);
                else
                    startingAddress_ = other.startingAddress_;
            }
            else
            {
                expandedNodeId_ = new ExpandedNodeId(*other.expandedNodeId_);
            }
        }

        return *this;
    }


    // Destructor
    // =============================================================================================
    Address::~Address()
    {
        clear();
    }


    // Clear the internal variables
    // =============================================================================================
    void Address::clear()
    {
        if (isRelativePath_)
        {
            delete relativePath_;
            relativePath_ = 0;
            
            if (isStartingAddressOwned_)
            {
                delete startingAddress_;
                startingAddress_ = 0;
            }
        }
        else
        {
            delete expandedNodeId_;
            expandedNodeId_ = 0;
        }
    }

    // Get the relative path
    // =============================================================================================
    vector<RelativePathElement> Address::getRelativePath() const
    {
        if (isRelativePath_)
        {
            return *relativePath_;
        }
        else
        {
            return vector<RelativePathElement>();
        }
    }


    // Get the starting address
    // =============================================================================================
    Address* Address::getStartingAddress() const
    {
        if (isRelativePath_)
            return startingAddress_;
        else
            return 0;
    }


    // Get the expanded node id
    // =============================================================================================
    ExpandedNodeId Address::getExpandedNodeId() const
    {
        if (!isRelativePath_)
            return *expandedNodeId_;
        else
            return ExpandedNodeId();
    }


    // Get a string representation
    // =============================================================================================
    string Address::toString(const string& indent, size_t colon) const
    {
        stringstream ss;

        if (isRelativePath_)
        {
            ss << indent << " - type";
            ss << fillToPos(ss, colon);
            ss << ": RelativePath\n";

            ss << indent << " - startingAddress\n";
            ss << startingAddress_->toString(indent + "   ", colon) << "\n";

            ss << indent << " - relativePath[]";
            if (relativePath_->size() == 0)
            {
                ss << fillToPos(ss, colon);
                ss << ": []";
            }
            else
            {
                for (size_t i = 0; i < relativePath_->size(); i++)
                {
                    if (i == 0)
                        ss << "\n";

                    ss << indent << "    - relativePath[" << i << "]\n";
                    ss << relativePath_->operator[](i).toString(indent + "      ", colon);
                }
            }
        }
        else
        {
            ss << indent << " - type";
            ss << fillToPos(ss, colon);
            ss << ": ExpandedNodeId\n";

            ss << indent << " - expandedNodeId";
            ss << fillToPos(ss, colon);
            ss << ": " << expandedNodeId_->toString();
        }

        return ss.str();
    }


    // Get the server URI of the address (if possible)
    // =============================================================================================
    Status extractServerUri(const Address& address, string& serverUri)
    {
        Status ret;

        if (address.isExpandedNodeId())
        {
            if (address.expandedNodeId_->hasServerUri())
            {
                serverUri = address.expandedNodeId_->serverUri();
                ret = statuscodes::Good;
            }
            else
            {
                ret = EmptyServerUriError();
            }
        }
        else
        {
            ret = ExpandedNodeIdAddressExpectedError();
        }

        return ret;
    }




    // Extract an OpcUa_NodeId
    // =============================================================================================
    Status Address::toSdk(OpcUa_NodeId* uaNodeId) const
    {
        Status ret;

        if (isExpandedNodeId())
            ret = expandedNodeId_->nodeId().toSdk(uaNodeId);
        else
            ret = ExpandedNodeIdAddressExpectedError();

        return ret;
    }



    // operator==
    // =============================================================================================
    bool operator==(const Address& object1, const Address& object2)
    {
        if (object1.isRelativePath_ != object2.isRelativePath_)
            return false;
        else
        {
            if (object1.isRelativePath_)
            {
                if (*(object1.relativePath_) != *(object2.relativePath_))
                    return *(object1.relativePath_) == *(object2.relativePath_);
                else
                    return *(object1.startingAddress_) == *(object2.startingAddress_);
            }
            else
            {
                return *(object1.expandedNodeId_) == *(object2.expandedNodeId_);
            }
        }
    }


    // operator!=
    // =============================================================================================
    bool operator!=(const Address& object1, const Address& object2)
    {
        return !(object1 == object2);
    }


    // operator<
    // =============================================================================================
    bool operator<(const Address& object1, const Address& object2)
    {
        if (object1.isRelativePath_ != object2.isRelativePath_)
            return object1.isRelativePath_;
        else
        {
            if (object1.isRelativePath_)
            {
                if (*(object1.relativePath_) != *(object2.relativePath_))
                    return *(object1.relativePath_) < *(object2.relativePath_);
                else
                    return *(object1.startingAddress_) < *(object2.startingAddress_);
            }
            else
            {
                return *(object1.expandedNodeId_) < *(object2.expandedNodeId_);
            }
        }
    }


}
