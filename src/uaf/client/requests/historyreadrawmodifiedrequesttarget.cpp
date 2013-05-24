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

#include "uaf/client/requests/historyreadrawmodifiedrequesttarget.h"


namespace uafc
{
    using namespace uaf;
    using namespace uafc;
    using std::string;
    using std::stringstream;
    using std::vector;
    using std::size_t;



    // Constructor
    // =============================================================================================
    HistoryReadRawModifiedRequestTarget::HistoryReadRawModifiedRequestTarget()
    {}


    // Constructor
    // =============================================================================================
    HistoryReadRawModifiedRequestTarget::HistoryReadRawModifiedRequestTarget(
            const Address&          address)
    : address(address)
    {}


    // Constructor
    // =============================================================================================
    HistoryReadRawModifiedRequestTarget::HistoryReadRawModifiedRequestTarget(
            const Address&      address,
            const ByteString&   continuationPoint)
    : address(address),
      continuationPoint(continuationPoint)
    {}


    // Get a string representation
    // =============================================================================================
    string HistoryReadRawModifiedRequestTarget::toString(const string& indent, size_t colon) const
    {
        stringstream ss;
        ss << indent << " - address\n";
        ss << address.toString(indent + "   ", colon) << "\n";

        ss << indent << " - continuationPoint";
        ss << fillToPos(ss, colon);
        ss << ": " << continuationPoint.toString() << "\n";

        ss << indent << " - indexRange";
        ss << fillToPos(ss, colon);
        ss << ": " << indexRange << "\n";

        ss << indent << " - dataEncoding";
        ss << fillToPos(ss, colon);
        ss << ": " << dataEncoding.toString();

        return ss.str();
    }


    // operator==
    // =============================================================================================
    bool operator==(
            const HistoryReadRawModifiedRequestTarget& object1,
            const HistoryReadRawModifiedRequestTarget& object2)
    {
        return    (object1.address == object2.address)
               && (object1.continuationPoint == object2.continuationPoint)
               && (object1.indexRange == object2.indexRange)
               && (object1.dataEncoding == object2.dataEncoding);
    }


    // operator!=
    // =============================================================================================
    bool operator!=(
            const HistoryReadRawModifiedRequestTarget& object1,
            const HistoryReadRawModifiedRequestTarget& object2)
    {
        return !(object1 == object2);
    }


    // operator<
    // =============================================================================================
    bool operator<(
            const HistoryReadRawModifiedRequestTarget& object1,
            const HistoryReadRawModifiedRequestTarget& object2)
    {
        if (object1.address != object2.address)
            return object1.address < object2.address;
        else if (object1.continuationPoint != object2.continuationPoint)
            return object1.continuationPoint < object2.continuationPoint;
        else if (object1.indexRange != object2.indexRange)
            return object1.indexRange < object2.indexRange;
        else
            return object1.dataEncoding < object2.dataEncoding;
    }


    // Get the resolvable items
    // =============================================================================================
    vector<Address> HistoryReadRawModifiedRequestTarget::getResolvableItems() const
    {
        vector<Address> ret;
        ret.push_back(address);
        return ret;
    }


    // Get a string representation
    // =============================================================================================
    Status HistoryReadRawModifiedRequestTarget::getServerUri(string& serverUri) const
    {
        return extractServerUri(address, serverUri);
    }



    // Set the resolved items
    // =============================================================================================
    Status HistoryReadRawModifiedRequestTarget::setResolvedItems(
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

}
