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

#ifndef UAFC_MONITOREDITEMSETTINGS_H_
#define UAFC_MONITOREDITEMSETTINGS_H_


// STD
#include <string>
#include <stdint.h>
#include <sstream>
// SDK
// UAF
#include "uaf/util/util.h"
#include "uaf/util/datachangefilter.h"
#include "uaf/util/eventfilter.h"
#include "uaf/client/clientexport.h"


namespace uafc
{


    /*******************************************************************************************//**
    * A uafc::MonitoredItemSettings instance holds the settings for a both a data and an event
    * monitored item.
    *
    * @ingroup ClientSettings
    ***********************************************************************************************/
    class UAFC_EXPORT MonitoredItemSettings
    {
    public:


        /**
         * An enum describing the kind of monitored item: either a monitored data item or a
         * monitored event item.
         */
        enum MonitoredItemKind
        {
            Data,
            Event
        };


        /**
         * Construct default monitored item settings.
         *
         * Defaults are:
         *  - kind()              : uafc::MonitoredItemSettings::Data
         *  - dataChangeFilter    : new DataChangeFilter()
         *  - eventFilter         : NULL
         *  - samplingIntervalSec : 1.0
         *  - queueSize           : 1
         *  - discardOldest       : true
         */
        MonitoredItemSettings();


        /**
         * Construct default monitored item settings for a given kind (data or event).
         *
         * @param kind      The kind (data or event) of the newly created monitored item settings.
         */
        MonitoredItemSettings(MonitoredItemKind kind);


        /**
         * Copy constructor.
         *
         * @param other     Monitored item settings to copy.
         */
        MonitoredItemSettings(const MonitoredItemSettings& other);


        /**
         * Construct a settings object with given settings for monitoring data changes.
         */
        MonitoredItemSettings(
                double                          samplingIntervalSec,
                uint32_t                        queueSize,
                bool                            discardOldest,
                const uaf::DataChangeFilter&    dataChangeFilter);


        /**
         * Construct a settings object with given settings for monitoring events.
         */
        MonitoredItemSettings(
                double                          samplingIntervalSec,
                uint32_t                        queueSize,
                bool                            discardOldest,
                const uaf::EventFilter&         eventFilter);


        /**
         * Destruct the monitored item settings.
         */
        virtual ~MonitoredItemSettings();


        /** The data change filter, in case the kind() is MonitoredItemSettings::Data. */
        uaf::DataChangeFilter*  dataChangeFilter;
        /** The event filter, in case the kind() is MonitoredItemSettings::Data. */
        uaf::EventFilter*       eventFilter;
        /** The sampling interval of the monitored item, in seconds. */
        double                  samplingIntervalSec;
        /** The queue size on the server side. */
        uint32_t                queueSize;
        /** True to discard the oldest item in the queue. */
        bool                    discardOldest;


        /**
         * Get the kind of the monitored item (either Data or Event).
         *
         * @return  The kind of the monitored item.
         */
        MonitoredItemKind kind() const { return kind_; }


        /**
         * Assignment operator.
         *
         * @param other Settings to assign to this monitored item settings.
         * @return      A reference to this settings instance.
         */
        MonitoredItemSettings& operator=(const MonitoredItemSettings& other);


        /**
         * Get a string representation.
         *
         * @return  A string representation.
         */
        const std::string toString() const;


        // comparison operators
        friend bool UAFC_EXPORT operator<(
                const MonitoredItemSettings& object1,
                const MonitoredItemSettings& object2);
        friend bool UAFC_EXPORT operator==(
                const MonitoredItemSettings& object1,
                const MonitoredItemSettings& object2);
        friend bool UAFC_EXPORT operator!=(
                const MonitoredItemSettings& object1,
                const MonitoredItemSettings& object2);

    private:
        // kind of the monitored item: either a monitored data or a monitored event
        MonitoredItemKind kind_;
    };

}

#endif /* UAFC_MONITOREDITEMSETTINGS_H_ */
