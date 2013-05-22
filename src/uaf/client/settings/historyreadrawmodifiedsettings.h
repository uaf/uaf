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

#ifndef UAFC_HISTORYREADRAWMODIFIEDSETTINGS_H_
#define UAFC_HISTORYREADRAWMODIFIEDSETTINGS_H_



// STD
// SDK
// UAF
#include "uaf/util/timestampstoreturn.h"
#include "uaf/util/datetime.h"
#include "uaf/client/clientexport.h"
#include "uaf/client/settings/baseservicesettings.h"



namespace uafc
{


    /*******************************************************************************************//**
    * An uafc::HistoryReadRawModifiedSettings object holds the service settings that are particular
    * for the HistoryReadRawModified service.
    *
    * @ingroup ClientSettings
    ***********************************************************************************************/
    class UAFC_EXPORT HistoryReadRawModifiedSettings : public uafc::BaseServiceSettings
    {
    public:

        /**
         * Create default HistoryReadRawModifiedSettings settings.
         *
         * Defaults are:
         *  - isReadModified            : False
         *  - timestampsToReturn        : uaf::timestampstoreturn::Source
         *  - releaseContinuationPoints : False
         *  - numValuesPerNode          : 0
         *  - returnBounds              : False
         */
        HistoryReadRawModifiedSettings();


        /** Begin of the time interval to read. */
        uaf::DateTime startTime;

        /** End of the time interval to read. */
        uaf::DateTime endTime;

        /** Boolean flag: False if the values stored in the history database should be returned
         *  directly, True if the values that are replaced by other values (with the same
         *  timestamps) should be returned. Default is False. */
        bool isReadModified;

        /** The maximum number of values that may be returned for each node.
         *  Default = 0 = no limit. */
        uint32_t numValuesPerNode;

        /** Boolean flag: True if the bounds (a value at or just before the start time and a value
         *  at or just after the end time) should be returned, False if not.
         *  Default is False.
         */
        bool returnBounds;

        /** Select and return the timestamps as specified by this attribute.
         *  If uaf::timestampstoreturn::Both is specified, the source timestamp
         *  will be used for selection.
         *  Default is  uaf::timestampstoreturn::Source. */
        uaf::timestampstoreturn::TimestampsToReturn timestampsToReturn;

        /** Boolean flag: True to let the Server know that no more historical data is needed,
         *  and so the server may release any resources associated with the call.
         *  Default is False. */
        bool releaseContinuationPoints;


        /**
         * Get a string representation of the settings.
         *
         * @return  String representation
         */
        virtual std::string toString(const std::string& indent="", std::size_t colon=28) const;

    };

}



#endif /* UAFC_HISTORYREADRAWMODIFIEDSETTINGS_H_ */
