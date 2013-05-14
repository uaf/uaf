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

#include "uaf/util/browsepath.h"

namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;
    using std::vector;


    // Constructor
    // =============================================================================================
    BrowsePath::BrowsePath()
    {}


    // Constructor
    // =============================================================================================
    BrowsePath::BrowsePath(
            const ExpandedNodeId&               startingExpandedNodeId,
            const vector<RelativePathElement>&  relativePath)
    : startingExpandedNodeId(startingExpandedNodeId),
      relativePath(relativePath)
    {}


    // Get a string representation
    // =============================================================================================
    string BrowsePath::toString(const string& delimiter) const
    {
        stringstream ss;

        ss << startingExpandedNodeId.toString();

        if (relativePath.size() == 0)
        {
            ss << delimiter;
        }
        else
        {
            for (vector<RelativePathElement>::const_iterator it = relativePath.begin();
                    it != relativePath.end();
                    ++it)
            {
                ss << delimiter << it->toString();
            }
        }

        return ss.str();
    }


    // operator==
    // =============================================================================================
    bool operator==(const BrowsePath& object1, const BrowsePath& object2)
    {
        return    object1.relativePath == object2.relativePath
               && object1.startingExpandedNodeId == object2.startingExpandedNodeId;
    }


    // operator!=
    // =============================================================================================
    bool operator!=(const BrowsePath& object1, const BrowsePath& object2)
    {
        return !(object1 == object2);
    }


    // operator<
    // =============================================================================================
    bool operator<(const BrowsePath& object1, const BrowsePath& object2)
    {
        if (object1.relativePath != object2.relativePath)
            return object1.relativePath < object2.relativePath;
        else
            return object1.startingExpandedNodeId < object2.startingExpandedNodeId;
    }


}
