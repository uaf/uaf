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

#include "uaf/client/results/translatebrowsepathstonodeidsresulttarget.h"


namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;
    using std::vector;
    using std::size_t;


    // Constructor
    // =============================================================================================
    TranslateBrowsePathsToNodeIdsResultTarget::TranslateBrowsePathsToNodeIdsResultTarget()
    {}



    // Get a string representation
    // =============================================================================================
    string TranslateBrowsePathsToNodeIdsResultTarget::toString(
            const string&   indent,
            size_t          colon) const
    {
        stringstream ss;
        ss << " - status";
        ss << fillToPos(ss, colon);
        ss << ": " << status.toString() << "\n";

        ss << indent << " - opcUaStatusCode";
        ss << fillToPos(ss, colon);
        ss << ": " << double(opcUaStatusCode) << "\n";

        ss << indent << " - expandedNodeIds[]";
        if (expandedNodeIds.size() == 0)
        {
            ss << fillToPos(ss, colon);
            ss << ": []\n";
        }
        else
        {
            ss << "\n";
            for (size_t i = 0; i < expandedNodeIds.size(); i++)
            {
                ss << indent << "   " << " - expandedNodeIds[" << i << "]";
                ss << fillToPos(ss, colon);
                ss << ": " << expandedNodeIds[i].toString() << "\n";
            }
        }

        ss << " - remainingPathIndexes[]";
        if (remainingPathIndexes.size() == 0)
        {
            ss << fillToPos(ss, colon);
            ss << ": []";
        }
        else
        {
            ss << "\n";
            for (size_t i = 0; i < remainingPathIndexes.size(); i++)
            {
                ss << indent << "   " << " - remainingPathIndexes[" << i << "]";
                ss << fillToPos(ss, colon);
                ss << ": " << remainingPathIndexes[i];
                if (i < (remainingPathIndexes.size() - 1))
                    ss << "\n";
            }
        }
        return ss.str();
    }



    // operator==
    // =============================================================================================
    bool operator==(
            const TranslateBrowsePathsToNodeIdsResultTarget& object1,
            const TranslateBrowsePathsToNodeIdsResultTarget& object2)
    {
        return    object1.clientConnectionId   == object2.clientConnectionId
               && object1.status               == object2.status
               && object1.opcUaStatusCode      == object2.opcUaStatusCode
               && object1.expandedNodeIds      == object2.expandedNodeIds
               && object1.remainingPathIndexes == object2.remainingPathIndexes;
    }


    // operator!=
    // =============================================================================================
    bool operator!=(
            const TranslateBrowsePathsToNodeIdsResultTarget& object1,
            const TranslateBrowsePathsToNodeIdsResultTarget& object2)
    {
        return !(object1 == object2);
    }


    // operator<
    // =============================================================================================
    bool operator<(
            const TranslateBrowsePathsToNodeIdsResultTarget& object1,
            const TranslateBrowsePathsToNodeIdsResultTarget& object2)
    {
        if (object1.clientConnectionId != object2.clientConnectionId)
            return object1.clientConnectionId < object2.clientConnectionId;
        else if (object1.status != object2.status)
            return object1.status < object2.status;
        else if (object1.opcUaStatusCode != object2.opcUaStatusCode)
            return object1.opcUaStatusCode < object2.opcUaStatusCode;
        else if (object1.expandedNodeIds != object2.expandedNodeIds)
            return object1.expandedNodeIds < object2.expandedNodeIds;
        else
            return object1.remainingPathIndexes < object2.remainingPathIndexes;
    }


}
