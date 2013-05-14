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

#include "uaf/client/settings/monitoreditemsettings.h"


#include <stdio.h>



namespace uafc
{
    using namespace uaf;
    using namespace uafc;
    using std::string;
    using std::stringstream;
    using std::vector;


    // Constructor
    // =============================================================================================
    MonitoredItemSettings::MonitoredItemSettings()
    : kind_(MonitoredItemSettings::Data),
      eventFilter(0)
    {
        dataChangeFilter    = new DataChangeFilter();
        samplingIntervalSec = 1.0;
        queueSize           = 1;
        discardOldest       = true;
    }


    // Constructor
    // =============================================================================================
    MonitoredItemSettings::MonitoredItemSettings(MonitoredItemKind kind)
    : kind_(kind)
    {
        if ( kind == MonitoredItemSettings::Data )
        {
            dataChangeFilter    = new DataChangeFilter();
            eventFilter         = 0;
            samplingIntervalSec = 1.0;
            queueSize           = 1;
            discardOldest       = true;
        }
        else if ( kind == MonitoredItemSettings::Event )
        {
            eventFilter         = new EventFilter();
            dataChangeFilter    = 0;
            samplingIntervalSec = 1.0;
            queueSize           = 0;
            discardOldest       = true;
        }

    }


    // Constructor
    // =============================================================================================
    MonitoredItemSettings::MonitoredItemSettings(
                double                  samplingIntervalSec,
                uint32_t                queueSize,
                bool                    discardOldest,
                const DataChangeFilter& dataChangeFilter)
    : kind_(MonitoredItemSettings::Data),
      eventFilter(0),
      samplingIntervalSec(samplingIntervalSec),
      queueSize(queueSize),
      discardOldest(discardOldest),
      dataChangeFilter(new DataChangeFilter(dataChangeFilter))
    {}


    // Constructor
    // =============================================================================================
    MonitoredItemSettings::MonitoredItemSettings(
                double                  samplingIntervalSec,
                uint32_t                queueSize,
                bool                    discardOldest,
                const EventFilter&      eventFilter)
    : kind_(MonitoredItemSettings::Event),
      dataChangeFilter(0),
      samplingIntervalSec(samplingIntervalSec),
      queueSize(queueSize),
      discardOldest(discardOldest),
      eventFilter(new EventFilter(eventFilter))
    {}


    // Copy constructor
    // =============================================================================================
    MonitoredItemSettings::MonitoredItemSettings(const MonitoredItemSettings& other)
    {
        kind_               = other.kind();
        samplingIntervalSec = other.samplingIntervalSec;
        queueSize           = other.queueSize;
        discardOldest       = other.discardOldest;

        if ( kind_ == MonitoredItemSettings::Data )
        {
            dataChangeFilter = new DataChangeFilter(*(other.dataChangeFilter));
        }
        else if ( kind_ == MonitoredItemSettings::Event )
        {
            eventFilter = new EventFilter(*(other.eventFilter));
        }

    }


    // Destructor
    // =============================================================================================
    MonitoredItemSettings::~MonitoredItemSettings()
    {
        if ( kind_ == MonitoredItemSettings::Data )
        {
            delete dataChangeFilter;
        }
        else if ( kind_ == MonitoredItemSettings::Event )
        {
            delete eventFilter;
        }
    }


    // Assignment operator
    // =============================================================================================
    MonitoredItemSettings& MonitoredItemSettings::operator=(const MonitoredItemSettings& other )
    {
        if ( &other != this )
        {
            if ( kind_ == MonitoredItemSettings::Data )
            {
                delete dataChangeFilter;
            }
            else if ( kind_ == MonitoredItemSettings::Event )
            {
                delete eventFilter;
            }

            kind_               = other.kind();
            samplingIntervalSec = other.samplingIntervalSec;
            queueSize           = other.queueSize;
            discardOldest       = other.discardOldest;

            if ( other.kind() == MonitoredItemSettings::Data )
            {
                dataChangeFilter = new DataChangeFilter(*(other.dataChangeFilter));
                eventFilter = 0;
            }
            else if ( other.kind() == MonitoredItemSettings::Event )
            {
                dataChangeFilter = 0;
                eventFilter = new EventFilter(*(other.eventFilter));
            }
        }
        return *this;
    }


    // Get a string representation
    // =============================================================================================
    const string MonitoredItemSettings::toString() const
    {
        stringstream ss;

        if ( kind_ == MonitoredItemSettings::Data )
        {
            ss << "kind=data, ";
        }
        else if ( kind_ == MonitoredItemSettings::Event )
        {
            ss << "kind=event, ";
        }

        ss << "sampling=" << int(samplingIntervalSec*1000.0) << "ms, queueSize=" << queueSize;
        if (discardOldest)
        {
            ss << ", discard oldest, ";
        }
        else
        {
            ss << ", discard newest, ";
        }

        if ( kind_ == MonitoredItemSettings::Data )
        {
            ss << dataChangeFilter->toString();
        }
        else if ( kind_ == MonitoredItemSettings::Event )
        {
            ss << eventFilter->toString();
        }

        return ss.str();
    }


    // operator<
    // =============================================================================================
    bool operator<(
            const MonitoredItemSettings& object1,
            const MonitoredItemSettings& object2)
    {
        if ( object1.kind_ != object2.kind_ )
            return object1.kind_ < object2.kind_;
        else if (int(object1.samplingIntervalSec*1000) != int(object2.samplingIntervalSec*1000))
            return int(object1.samplingIntervalSec*1000) < int(object2.samplingIntervalSec*1000);
        else if (object1.queueSize != object2.queueSize)
            return object1.queueSize < object2.queueSize;
        else if (object1.discardOldest != object2.discardOldest)
            return object1.discardOldest < object2.discardOldest;
        else if (object1.kind_ == MonitoredItemSettings::Data)
            return object1.dataChangeFilter < object2.dataChangeFilter;
        else if (object1.kind_ == MonitoredItemSettings::Event)
            return object1.eventFilter < object2.eventFilter;
        else
            return false;
    }


    // operator==
    // =============================================================================================
    bool operator==(
            const MonitoredItemSettings& object1,
            const MonitoredItemSettings& object2)
    {
        if ( object1.kind_ == object2.kind_ )
        {
            if (    (int(object1.samplingIntervalSec*1000) == int(object2.samplingIntervalSec*1000))
                 && (object1.queueSize == object2.queueSize)
                 && (object1.discardOldest == object2.discardOldest) )
            {
                if ( object1.kind_ == MonitoredItemSettings::Data )
                {
                    return *(object1.dataChangeFilter) == *(object2.dataChangeFilter);
                }
                else if ( object1.kind_ == MonitoredItemSettings::Event )
                {
                    return *(object1.eventFilter) == *(object2.eventFilter);
                }
                else
                {
                    return false;
                }
            }
            else
                return false;
        }
        else
        {
            return false;
        }
    }


    // operator!=
    // =============================================================================================
    bool operator!=(
            const MonitoredItemSettings& object1,
            const MonitoredItemSettings& object2)
    {
        return !(object1 == object2);
    }
}

