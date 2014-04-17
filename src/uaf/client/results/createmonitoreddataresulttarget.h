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

#ifndef UAFC_CREATEMONITOREDDATARESULTTARGET_H_
#define UAFC_CREATEMONITOREDDATARESULTTARGET_H_



// STD
// SDK
// UAF
#include "uaf/util/status.h"
#include "uaf/util/handles.h"
#include "uaf/client/clientexport.h"
#include "uaf/client/results/basesubscriptionresulttarget.h"



namespace uafc
{



    /*******************************************************************************************//**
    * An uafc::CreateMonitoredItemResultTarget is the "result target" of the corresponding "request
    * target" that specified the item to be monitored.
    *
    * It tells you whether or not the item is now being monitored, the value of the handle of the
    * monitored item, the value of the handle of the notifications that you can expect, ...
    *
    * @ingroup ClientResults
    ***********************************************************************************************/
    class UAFC_EXPORT CreateMonitoredDataResultTarget : public uafc::BaseSubscriptionResultTarget
    {
    public:


        /**
         * Create a default result target.
         */
        CreateMonitoredDataResultTarget()
        : clientHandle(uaf::CLIENTHANDLE_NOT_ASSIGNED),
          monitoredItemId(0),
          revisedSamplingIntervalSec(0.0),
          revisedQueueSize(0)
        {}


        /** Status of the result (Good if the monitored item was created, Bad if not). */
        uaf::Status status;

        /** Client handle that was assigned to the monitored item by the client. */
        uaf::ClientHandle clientHandle;

        /** MonitoredItemId that was assigned to the monitored item by the server. */
        uaf::MonitoredItemId monitoredItemId;

        /** The revised sampling interval of the monitored item, in seconds. */
        double revisedSamplingIntervalSec;

        /** The revised queue size on the server side. */
        uint32_t revisedQueueSize;


        /**
         * Get a string representation of the result.
         *
         * @return  String representation.
         */
        std::string toString(const std::string& indent="", std::size_t colon=32) const;


        // comparison operators
        friend bool UAFC_EXPORT operator==(
                const CreateMonitoredDataResultTarget& object1,
                const CreateMonitoredDataResultTarget& object2);
        friend bool UAFC_EXPORT operator!=(
                const CreateMonitoredDataResultTarget& object1,
                const CreateMonitoredDataResultTarget& object2);
        friend bool UAFC_EXPORT operator<(
                const CreateMonitoredDataResultTarget& object1,
                const CreateMonitoredDataResultTarget& object2);

    };


}


#endif /* UAFC_CREATEMONITOREDDATARESULTTARGET_H_ */
