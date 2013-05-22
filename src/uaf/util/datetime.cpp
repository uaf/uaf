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

#include "uaf/util/datetime.h"

namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;


    // Constructor
    // =============================================================================================
    DateTime::DateTime()
    {}


    // Constructor
    // =============================================================================================
    DateTime::DateTime(double t)
    {
        uaDateTime_ = UaDateTime::fromTime_t((time_t)t);
        uaDateTime_.addMilliSecs( (t - ((time_t)t)) *1000 );
    }


    // Static function to get the current time
    // =============================================================================================
    DateTime DateTime::now()
    {
        UaDateTime uaNow = UaDateTime::now();
        DateTime ret;
        ret.fromSdk(uaNow);
        return ret;
    }


    // Static function to get the time from a string representation.
    // =============================================================================================
    DateTime DateTime::fromString(const string& s)
    {
        UaDateTime uaDateTime = UaDateTime::fromString(UaString(s.c_str()));
        DateTime ret;
        ret.fromSdk(uaDateTime);
        return ret;
    }


    // Static function to get the time from a (platform dependent) time_t.
    // =============================================================================================
    DateTime DateTime::fromTime_t(time_t t)
    {
        return DateTime((double)t);
    }


    // Static function to get the time from a 64-bit FILETIME-like number.
    // =============================================================================================
    DateTime DateTime::fromFileTime(int64_t t)
    {
        UaDateTime uaDateTime(t);
        DateTime ret;
        ret.fromSdk(uaDateTime);
        return ret;
    }


    // Set the time to time_t + msec
    // =============================================================================================
    void DateTime::setCtime(double t)
    {
        DateTime newTime(t);
        uaDateTime_ = UaDateTime(newTime.toFileTime());
    }


    // Conver to OpcUa_DateTime
    // =============================================================================================
    void DateTime::toSdk(OpcUa_DateTime& uaDateTime) const
    {
        uint64_t t = toFileTime();
        uaDateTime.dwLowDateTime = (OpcUa_UInt32)(t & 0xFFFFFFFF);
        uaDateTime.dwHighDateTime = (OpcUa_UInt32)(t >> 32);
    }


    // Get the time interval in days
    // =============================================================================================
    int32_t DateTime::daysTo(const DateTime& other) const
    {
        UaDateTime uaOther;
        other.toSdk(uaOther);
        return uaDateTime_.daysTo(uaOther);
    }


    // Get the time interval in seconds
    // =============================================================================================
    int32_t DateTime::secsTo(const DateTime& other) const
    {
        UaDateTime uaOther;
        other.toSdk(uaOther);
        return uaDateTime_.secsTo(uaOther);
    }


    // Get the time interval in milliseconds
    // =============================================================================================
    int32_t DateTime::msecsTo(const DateTime& other) const
    {
        UaDateTime uaOther;
        other.toSdk(uaOther);
        return uaDateTime_.msecsTo(uaOther);
    }


    // Comparison operator ==
    // =============================================================================================
    bool operator==(const DateTime& object1, const DateTime& object2)
    {
        return object1.uaDateTime_ == object2.uaDateTime_;
    }


    // Comparison operator !=
    // =============================================================================================
    bool operator!=(const DateTime& object1, const DateTime& object2)
    {
        return object1.uaDateTime_ != object2.uaDateTime_;
    }


    // comparison operator <
    // =============================================================================================
    bool operator<(const DateTime& object1, const DateTime& object2)
    {
        return object1.uaDateTime_ < object2.uaDateTime_;
    }


    // comparison operator >
    // =============================================================================================
    bool operator>(const DateTime& object1, const DateTime& object2)
    {
        return object1.uaDateTime_ > object2.uaDateTime_;
    }

}


