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

#include "uaf/client/requests/browserequesttarget.h"


namespace uafc
{
    using namespace uaf;
    using namespace uafc;
    using std::string;
    using std::stringstream;
    using std::vector;



    // Constructor
    // =============================================================================================
    BrowseRequestTarget::BrowseRequestTarget()
    : browseDirection(browsedirections::Forward),
      includeSubtypes(false),
      nodeClassMask(0),
      resultMask(63)
    {}


    // Constructor
    // =============================================================================================
    BrowseRequestTarget::BrowseRequestTarget(const Address& address)
    : address(address),
      browseDirection(browsedirections::Forward),
      includeSubtypes(false),
      nodeClassMask(0),
      resultMask(63)
    {}


    // Get a string representation
    // =============================================================================================
    string BrowseRequestTarget::toString(const string& indent, std::size_t colon) const
    {
        stringstream ss;

        ss << indent << " - address\n";
        ss << address.toString(indent + "   ", colon) << "\n";

        ss << indent << " - browseDirection";
        ss << fillToPos(ss, colon);
        ss << ": " << browseDirection << " (" << browsedirections::toString(browseDirection);
        ss << ")\n";

        ss << indent << " - referenceTypeId";
        ss << fillToPos(ss, colon);
        ss << ": " << referenceTypeId.toString() << "\n";

        ss << indent << " - includeSubtypes";
        ss << fillToPos(ss, colon);
        ss << ": " << (includeSubtypes ? "True" : "False") << "\n";

        ss << indent << " - nodeClassMask";
        ss << fillToPos(ss, colon);
        ss << ": " << int(nodeClassMask) << "\n";

        ss << indent << " - resultMask";
        ss << fillToPos(ss, colon);
        ss << ": " << int(resultMask);

        return ss.str();
    }


    // operator==
    // =============================================================================================
    bool operator==(const BrowseRequestTarget& object1, const BrowseRequestTarget& object2)
    {
        return    object1.address == object2.address
               && object1.browseDirection == object2.browseDirection
               && object1.referenceTypeId == object2.referenceTypeId
               && object1.includeSubtypes == object2.includeSubtypes
               && object1.nodeClassMask == object2.nodeClassMask
               && object1.resultMask == object2.resultMask;
    }


    // operator!=
    // =============================================================================================
    bool operator!=(const BrowseRequestTarget& object1, const BrowseRequestTarget& object2)
    {
        return !(object1 == object2);
    }


    // operator<
    // =============================================================================================
    bool operator<(const BrowseRequestTarget& object1, const BrowseRequestTarget& object2)
    {
        if (object1.address != object2.address)
            return object1.address < object2.address;
        else if (object1.browseDirection != object2.browseDirection)
            return object1.browseDirection < object2.browseDirection;
        else if (object1.referenceTypeId != object2.referenceTypeId)
            return object1.referenceTypeId < object2.referenceTypeId;
        else if (object1.includeSubtypes != object2.includeSubtypes)
            return object1.includeSubtypes < object2.includeSubtypes;
        else if (object1.nodeClassMask != object2.nodeClassMask)
            return object1.nodeClassMask < object2.nodeClassMask;
        else
            return object1.resultMask < object2.resultMask;
    }


    // Get the resolvable items
    // =============================================================================================
    vector<Address> BrowseRequestTarget::getResolvableItems() const
    {
        vector<Address> ret;
        ret.push_back(address);
        return ret;
    }


    // Set the resolved items
    // =============================================================================================
    Status BrowseRequestTarget::setResolvedItems(
            const vector<ExpandedNodeId>& expandedNodeIds,
            const vector<Status>&         resolutionStatuses)
    {
        Status ret;

        if (   expandedNodeIds.size()    == resolvableItemsCount()
            && resolutionStatuses.size() == resolvableItemsCount())
        {
            if (resolutionStatuses[0].isGood())
                address = Address(expandedNodeIds[0]);

            ret.setGood();
        }
        else
        {
            ret.setStatus(statuscodes::UnexpectedError, "Could not set the resolved items");
        }

        return ret;
    }


    // Get the server URI
    // =============================================================================================
    Status BrowseRequestTarget::getServerUri(string& serverUri) const
    {
        return extractServerUri(address, serverUri);
    }



}
