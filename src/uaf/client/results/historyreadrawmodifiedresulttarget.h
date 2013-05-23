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

#ifndef UAFC_HISTORYREADRAWMODIFIEDRESULTTARGET_H_
#define UAFC_HISTORYREADRAWMODIFIEDRESULTTARGET_H_



// STD
// SDK
// UAF
#include "uaf/util/status.h"
#include "uaf/util/modificationinfo.h"
#include "uaf/util/datavalue.h"
#include "uaf/client/clientexport.h"
#include "uaf/client/clienthandles.h"
#include "uaf/client/results/basesessionresulttarget.h"



namespace uafc
{


    /*******************************************************************************************//**
    * An uafc::HistoryReadRawModifiedResultTarget is the "result target" of the corresponding
    * "request target" that specified the node to get the historical data from and the constraints
    * etc.
    *
    * @ingroup ClientResults
    ***********************************************************************************************/
    class UAFC_EXPORT HistoryReadRawModifiedResultTarget : public uafc::BaseSessionResultTarget
    {
    public:

        /**
         * Create an empty result target.
         */
        HistoryReadRawModifiedResultTarget();


        /** The resulting status for the operation. */
        uaf::Status status;

        /** The continuation point, in case there are still results left at the server.
         *  If the continuation point is not NULL (i.e. if it contains more than 0 bytes),
         *  then you should copy the continuation point to the continuation point of the
         *  HistoryReadRawModifiedRequestTarget, and perform another call. */
        uaf::ByteString continuationPoint;

        /** How many times did the UAF automatically invoke the historical read OPC UA service
         *  in addition to the original request, in order to get the remaining results?
         *  In case the UAF did not read more data automatically, this value will be 0. */
        uint32_t autoReadMore;

        /** The requested historical data. */
        std::vector<uaf::DataValue> dataValues;

        /** The modification information, in case the isReadModified flag was set in the
         *  request target. */
        uaf::ModificationInfo modificationInformation;


        /**
         * Get a string representation of the target.
         */
        std::string toString(const std::string& indent="", std::size_t colon=22) const;

    };

}


#endif /* UAFC_HISTORYREADRAWMODIFIEDRESULTTARGET_H_ */
