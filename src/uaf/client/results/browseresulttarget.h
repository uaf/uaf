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

#ifndef UAFC_BROWSERESULTTARGET_H_
#define UAFC_BROWSERESULTTARGET_H_



// STD
// SDK
// UAF
#include "uaf/util/status.h"
#include "uaf/util/bytestring.h"
#include "uaf/util/referencedescription.h"
#include "uaf/client/clientexport.h"
#include "uaf/client/clienthandles.h"
#include "uaf/client/results/basesessionresulttarget.h"



namespace uafc
{


    /*******************************************************************************************//**
    * An uafc::BrowseResultTarget is the "result target" of the corresponding
    * "request target" that specified the node etc. to be browsed.
    *
    * It tells you the browse status, the references that were found during the browse, etc.
    *
    * @ingroup ClientResults
    ***********************************************************************************************/
    class UAFC_EXPORT BrowseResultTarget : public uafc::BaseSessionResultTarget
    {
    public:

        /**
         * Create an empty result target.
         */
        BrowseResultTarget();


        /** The status of the browse target. */
        uaf::Status status;


        /** How many times did the UAF automatically invoked the "BrowseNext" OPC UA service in
         *  order to get the results? */
        uint32_t autoBrowsedNext;


        /** The continuation point (a server-defined byte string) that should be provided to the
         *  next BrowseNext call, to get the remaining browse results. Since the
         *  UAF can automatically call BrowseNext for you (via the
         *  uaf::BrowseSettings::maxAutoBrowseNext parameter), you normally don't have to
         *  use the continuation point and the BrowseNext service yourself.*/
        uaf::ByteString continuationPoint;


        /** The reference descriptions that were found during the browsing. */
        std::vector<uaf::ReferenceDescription> references;


        /**
         * Get a string representation of the target.
         */
        std::string toString(const std::string& indent="", std::size_t colon=22) const;

    };

}


#endif /* UAFC_BROWSERESULTTARGET_H_ */
