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

#include "uaf/util/datachangefilter.h"


namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::size_t;
    using std::stringstream;


    // Constructor
    // =============================================================================================
    DataChangeFilter::DataChangeFilter()
    : trigger(DataChangeTrigger_StatusValue),
      deadBandType(DeadBandType_None),
      deadBandValue(0.0)
    {}


    // Constructor
    // =============================================================================================
    DataChangeFilter::DataChangeFilter(DataChangeTrigger trigger, DeadBandType type, double value)
    : trigger(trigger),
      deadBandType(type),
      deadBandValue(value)
    {}


    // Update a stack object
    // =============================================================================================
    void DataChangeFilter::toSdk(OpcUa_DataChangeFilter *destination) const
    {
        if (trigger == DataChangeTrigger_Status)
            destination->Trigger = OpcUa_DataChangeTrigger_Status;
        else if (trigger == DataChangeTrigger_StatusValue)
            destination->Trigger = OpcUa_DataChangeTrigger_StatusValue;
        else
            destination->Trigger = OpcUa_DataChangeTrigger_StatusValueTimestamp;

        if (deadBandType == DeadBandType_None)
            destination->DeadbandType = OpcUa_DeadbandType_None;
        else if (deadBandType == DeadBandType_Absolute)
            destination->DeadbandType = OpcUa_DeadbandType_Absolute;
        else
            destination->DeadbandType = OpcUa_DeadbandType_Percent;

        destination->DeadbandValue = deadBandValue;
    }



    // Get a string representation
    // =============================================================================================
    string DataChangeFilter::toString(const string& indent, size_t colon) const
    {
        stringstream ss;

        ss << indent << " - trigger";
        ss << fillToPos(ss, colon);
        ss << ": " << int(trigger) << " ";
        if (trigger == DataChangeTrigger_Status)
            ss << "(Status)\n";
        else if (trigger == DataChangeTrigger_StatusValue)
            ss << "(StatusValue)\n";
        else if (trigger == DataChangeTrigger_StatusValueTimestamp)
            ss << "(StatusValueTimestamp)\n";
        else
            ss << "!!!INVALID!!!\n";

        ss << indent << " - deadBandType";
        ss << fillToPos(ss, colon);
        ss << ": " << int(deadBandType) << " ";

        if (deadBandType == DeadBandType_None)
            ss << "(None)\n";
        else if (deadBandType == DeadBandType_Absolute)
            ss << "(Absolute)\n";
        else if (deadBandType == DeadBandType_Percent)
            ss << "(Percent)\n";
        else
            ss << "!!!INVALID!!!\n";

        ss << indent << " - deadBandValue";
        ss << fillToPos(ss, colon);
        ss << ": " << deadBandValue;

        return ss.str();
    }


    // operator<
    // =============================================================================================
    bool operator<(
            const DataChangeFilter& object1,
            const DataChangeFilter& object2)
    {
        if (object1.trigger != object2.trigger)
            return object1.trigger < object2.trigger;
        else if (object1.deadBandType != object2.deadBandType)
            return object1.deadBandType < object2.deadBandType;
        else if (int(object1.deadBandValue*1000) != int(object2.deadBandValue*1000))
            return int(object1.deadBandValue*1000) < int(object2.deadBandValue*1000);
        else
            return false;
    }


    // operator==
    // =============================================================================================
    bool operator==(
            const DataChangeFilter& object1,
            const DataChangeFilter& object2)
    {
        return   (object1.trigger == object2.trigger)
              && (object1.deadBandType == object2.deadBandType)
              && (int(object1.deadBandValue*1000) == int(object2.deadBandValue*1000));
    }


    // operator!=
    // =============================================================================================
    bool operator!=(
            const DataChangeFilter& object1,
            const DataChangeFilter& object2)
    {
        return !(object1 == object2);
    }
}

