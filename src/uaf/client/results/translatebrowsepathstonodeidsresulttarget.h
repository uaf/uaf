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

#ifndef UAFC_TRANSLATEBROWSEPATHSTONODEIDSRESULTTARGET_H_
#define UAFC_TRANSLATEBROWSEPATHSTONODEIDSRESULTTARGET_H_



// STD
// SDK
// UAF
#include "uaf/util/status.h"
#include "uaf/util/expandednodeid.h"
#include "uaf/util/handles.h"
#include "uaf/client/clientexport.h"
#include "uaf/client/results/basesessionresulttarget.h"



namespace uafc
{


    /*******************************************************************************************//**
    * An uafc::TranslateBrowsePathsToNodeIdsResultTarget is the "result target" of the corresponding
    * "request target" that specified the browse path to be translated.
    *
    * It tells you the translation status, the translation result, etc.
    *
    * @ingroup ClientResults
    ***********************************************************************************************/
    class UAFC_EXPORT TranslateBrowsePathsToNodeIdsResultTarget
    : public uafc::BaseSessionResultTarget
    {
    public:


        /**
         * Create a default result target.
         */
        TranslateBrowsePathsToNodeIdsResultTarget();


        /** The status of the translation target (good if the browse path could be translated,
         *  bad if not). */
        uaf::Status status;

        /** The resulting expanded node ids. */
        std::vector<uaf::ExpandedNodeId> expandedNodeIds;

        /** The remaining path indexes. */
        std::vector<uint32_t> remainingPathIndexes;


        /**
         * Get a string representation of the target.
         */
        std::string toString(const std::string& indent="", std::size_t colon=29) const;


        // comparison operators
        friend bool UAFC_EXPORT operator==(
                const TranslateBrowsePathsToNodeIdsResultTarget& object1,
                const TranslateBrowsePathsToNodeIdsResultTarget& object2);
        friend bool UAFC_EXPORT operator!=(
                const TranslateBrowsePathsToNodeIdsResultTarget& object1,
                const TranslateBrowsePathsToNodeIdsResultTarget& object2);
        friend bool UAFC_EXPORT operator<(
                const TranslateBrowsePathsToNodeIdsResultTarget& object1,
                const TranslateBrowsePathsToNodeIdsResultTarget& object2);

    };

}


#endif /* UAFC_TRANSLATEBROWSEPATHSTONODEIDSRESULTTARGET_H_ */
