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

#include "uaf/client/requests/translatebrowsepathstonodeidsrequesttarget.h"


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
    TranslateBrowsePathsToNodeIdsRequestTarget::TranslateBrowsePathsToNodeIdsRequestTarget()
    {}


    // Constructor
    // =============================================================================================
    TranslateBrowsePathsToNodeIdsRequestTarget::TranslateBrowsePathsToNodeIdsRequestTarget(
            const BrowsePath& browsePath)
    : browsePath(browsePath)
    {}


    // Get a string representation
    // =============================================================================================
    string TranslateBrowsePathsToNodeIdsRequestTarget::toString(
            const string&   indent,
            size_t          colon) const
    {
        stringstream ss;
        ss << "browsePath: " << browsePath.toString();
        return ss.str();
    }

    // operator==
    // =============================================================================================
    bool operator==(
            const TranslateBrowsePathsToNodeIdsRequestTarget& object1,
            const TranslateBrowsePathsToNodeIdsRequestTarget& object2)
    {
        return object1.browsePath == object2.browsePath;
    }

    // operator!=
    // =============================================================================================
    bool operator!=(
            const TranslateBrowsePathsToNodeIdsRequestTarget& object1,
            const TranslateBrowsePathsToNodeIdsRequestTarget& object2)
    {
        return !(object1 == object2);
    }

    // operator<
    // =============================================================================================
    bool operator<(
            const TranslateBrowsePathsToNodeIdsRequestTarget& object1,
            const TranslateBrowsePathsToNodeIdsRequestTarget& object2)
    {
        return object1.browsePath < object2.browsePath;
    }


    // Get the resolvable items
    // =============================================================================================
    vector<Address> TranslateBrowsePathsToNodeIdsRequestTarget::getResolvableItems() const
    {
        // don't return anything
        vector<Address> ret;
        return ret;
    }


    // Set the resolved items
    // =============================================================================================
    Status TranslateBrowsePathsToNodeIdsRequestTarget::setResolvedItems(
            const vector<ExpandedNodeId>& expandedNodeIds,
            const vector<Status>&         resolutionStatuses)
    {
        return Status(statuscodes::UnexpectedError, "No items to set");
    }


    // Get the server URI
    // =============================================================================================
    Status TranslateBrowsePathsToNodeIdsRequestTarget::getServerUri(string& serverUri) const
    {
        if (browsePath.startingExpandedNodeId.hasServerUri())
        {
            serverUri = browsePath.startingExpandedNodeId.serverUri();
            return Status(statuscodes::Good);
        }
        else
            return Status(statuscodes::UnexpectedError, "No valid starting node");
    }



}
