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

#include "uaf/client/requests/browsenextrequesttarget.h"


namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;
    using std::vector;



    // Constructor
    // =============================================================================================
    BrowseNextRequestTarget::BrowseNextRequestTarget()
    {}


    // Constructor
    // =============================================================================================
    BrowseNextRequestTarget::BrowseNextRequestTarget(
            const Address&      address,
            const ByteString&   continuationPoint)
    : address(address),
      continuationPoint(continuationPoint)
    {}


    // Get a string representation
    // =============================================================================================
    string BrowseNextRequestTarget::toString(const string& indent, std::size_t colon) const
    {
        stringstream ss;

        ss << indent << " - address\n";
        ss << address.toString(indent + "   ", colon) << "\n";

        ss << indent << " - continuationPoint";
        ss << fillToPos(ss, colon);
        ss << ": " << continuationPoint.toString() << "\n";

        return ss.str();
    }


    // operator==
    // =============================================================================================
    bool operator==(const BrowseNextRequestTarget& object1, const BrowseNextRequestTarget& object2)
    {
        return    object1.address == object2.address
               && object1.continuationPoint == object2.continuationPoint;
    }


    // operator!=
    // =============================================================================================
    bool operator!=(const BrowseNextRequestTarget& object1, const BrowseNextRequestTarget& object2)
    {
        return !(object1 == object2);
    }


    // operator<
    // =============================================================================================
    bool operator<(const BrowseNextRequestTarget& object1, const BrowseNextRequestTarget& object2)
    {
        if (object1.address != object2.address)
            return object1.address < object2.address;
        else
            return object1.continuationPoint < object2.continuationPoint;
    }


    // Get the resolvable items
    // =============================================================================================
    vector<Address> BrowseNextRequestTarget::getResolvableItems() const
    {
        vector<Address> ret;
        ret.push_back(address);
        return ret;
    }


    // Set the resolved items
    // =============================================================================================
    Status BrowseNextRequestTarget::setResolvedItems(
            const vector<ExpandedNodeId>& expandedNodeIds,
            const vector<Status>&         resolutionStatuses)
    {
        Status ret;

        if (   expandedNodeIds.size()    == resolvableItemsCount()
            && resolutionStatuses.size() == resolvableItemsCount())
        {
            if (resolutionStatuses[0].isGood())
                address = Address(expandedNodeIds[0]);

            ret = statuscodes::Good;
        }
        else
        {
            ret = UnexpectedError("Could not set the resolved items");
        }

        return ret;
    }


    // Get the server URI
    // =============================================================================================
    Status BrowseNextRequestTarget::getServerUri(string& serverUri) const
    {
        return extractServerUri(address, serverUri);
    }



}
