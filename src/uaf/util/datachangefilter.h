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

#ifndef UAF_DATACHANGEFILTER_H_
#define UAF_DATACHANGEFILTER_H_


// STD
#include <string>
#include <stdint.h>
#include <sstream>
// SDK
#include "uabasecpp/uaplatformlayer.h"
// UAF
#include "uaf/util/util.h"
#include "uaf/util/stringifiable.h"


namespace uaf
{



    /*******************************************************************************************//**
    * A uaf::DataChangeFilter instance holds the filter settings for a monitored data item.
    *
    * @ingroup Util
    ***********************************************************************************************/
    class UAF_EXPORT DataChangeFilter
    {
    public:


        /**
         * An enum describing the trigger for the notifications: either when
         *  - the status of the data changes,
         *  - the status or the value of the data changes (default!)
         *  - the status or the value or the timestamp of the data changes.
         */
        enum DataChangeTrigger {
            DataChangeTrigger_Status                = 0,
            DataChangeTrigger_StatusValue           = 1,
            DataChangeTrigger_StatusValueTimestamp  = 2
        };


        /**
         * An enum describing the type of deadband: None, Absolute or Percent.
         */
        enum DeadBandType {
            DeadBandType_None     = 0, //!< NONE
            DeadBandType_Absolute = 1, //!< ABSOLUTE
            DeadBandType_Percent  = 2  //!< PERCENT
        };


        /**
         * Construct a default data change filter
         *
         * By default, there is no deadband enabled (so deadBandType is DeadBand_None),
         * and the trigger is DataChangeTrigger_StatusValue.
         */
        DataChangeFilter();


        /**
         * Construct a data change filter
         */
        DataChangeFilter(DataChangeTrigger trigger, DeadBandType type, double value);


        /**
         * The trigger of the data change.
         */
        DataChangeTrigger trigger;


        /**
         * The type of deadband, e.g. DeadBand_Absolute or DeadBand_Percent.
         */
        DeadBandType deadBandType;


        /**
         * The value of the deadband.
         */
        double deadBandValue;


        /**
         * Get a string representation.
         *
         * @return  A string representation.
         */
        std::string toString(const std::string& indent="", std::size_t colon=17) const;


        /**
         * Update a stack OpcUa_DataChangeFilter instance.
         *
         * @param destination   OpcUa_DataChangeFilter instance (as defined by the stack) to be
         *                      modified.
         */
        void toSdk(OpcUa_DataChangeFilter* destination) const;


        // comparison operators
        friend bool UAF_EXPORT operator<(
                const DataChangeFilter& object1,
                const DataChangeFilter& object2);
        friend bool UAF_EXPORT operator==(
                const DataChangeFilter& object1,
                const DataChangeFilter& object2);
        friend bool UAF_EXPORT operator!=(
                const DataChangeFilter& object1,
                const DataChangeFilter& object2);

    };



}

#endif /* UAF_DATACHANGEFILTER_H_ */
