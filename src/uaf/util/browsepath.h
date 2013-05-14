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

#ifndef UAF_BROWSEPATH_H_
#define UAF_BROWSEPATH_H_


// STD
#include <vector>
#include <string>
// SDK
// UAF
#include "uaf/util/util.h"
#include "uaf/util/relativepathelement.h"
#include "uaf/util/expandednodeid.h"


namespace uaf
{


    /*******************************************************************************************//**
     * A BrowsePath holds a path from a resolved starting node to another node within the address
     * space.
     *
     * @ingroup Util
     **********************************************************************************************/
    class UAF_EXPORT BrowsePath
    {
    public:


        /**
         * Construct an empty BrowsePath and no starting ExpandedNodeId.
         */
        BrowsePath();


        /**
         * Construct a BrowsePath from the given starting ExpandedNodeId and relative path.
         *
         * @param startingExpandedNodeId    The starting ExpandedNodeId of the browsepath.
         * @param relativePath              The relative path.
         */
        BrowsePath(
                const uaf::ExpandedNodeId&                      startingExpandedNodeId,
                const std::vector<uaf::RelativePathElement>&    relativePath);


        /** The starting point (as an ExpandedNodeId) of the relative path. */
        uaf::ExpandedNodeId startingExpandedNodeId;


        /** The relative path of the BrowsePath. */
        std::vector<uaf::RelativePathElement> relativePath;


        /**
         * Get a string representation of the browse path.
         *
         * @return string representation
         */
        std::string toString(const std::string& delimiter="/") const;


        // comparison operators
        friend UAF_EXPORT bool operator==(const BrowsePath& object1, const BrowsePath& object2);
        friend UAF_EXPORT bool operator!=(const BrowsePath& object1, const BrowsePath& object2);
        friend UAF_EXPORT bool operator<(const BrowsePath& object1, const BrowsePath& object2);

    };

}



#endif /* UAF_BROWSEPATH_H_ */
