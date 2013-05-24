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

#ifndef UAF_DATETIME_H_
#define UAF_DATETIME_H_


// STD
#include <string>
#include <sstream>
#include <stdint.h>

#ifdef _MSC_VER
#include <time.h>
#else /* _MSC_VER */
#include <sys/time.h>
#endif /* _MSC_VER */

// SDK
#include "uabase/uadatetime.h"
#include "uabase/uathread.h"
// UAF
#include "uaf/util/util.h"


namespace uaf
{


    /*******************************************************************************************//**
     * A DateTime holds a timestamp (it wraps the SDK UaDateTime quite literally).
     *
     * @ingroup Util
     **********************************************************************************************/
    class UAF_EXPORT DateTime
    {
    public:


        /**
         * Construct a DateTime.
         */
        DateTime();


        /**
         * Construct a DateTime from a double precision real number representing time_t
         * (=the number of seconds since UTC 1 January 1970 = 1970-01-01T00:00:00Z)
         * plus the number of milliseconds after the second.
         *
         * @param t     The time as a real number.
         */
        DateTime(double t);


#ifdef _MSC_VER
        /**
         * Construct a DateTime from a FILETIME struct
         * (two 32-bit values representing the number of 100-nanosecond intervals since January 1,
         * 1601 (UTC)).
         *
         * @param t The time as a FILETIME struct.
         */
        DateTime(const FILETIME& t) : uaDateTime_(t) {}
#endif /* _MSC_VER */


        /**
         * Static function to get the current time.
         *
         * @return The current time as a DateTime instance.
         */
        static DateTime now();


        /**
         * Static function to get a DateTime instance from a string.
         *
         * @return The timestamp from the string as a DateTime instance.
         */
        static DateTime fromString(const std::string& s);


        /**
         * Static function to get a DateTime instance from a (platform dependent) time_t.
         *
         * time_t is the number of seconds since UTC 1 January 1970 = 1970-01-01T00:00:00Z.
         *
         * @param t The timestamp as a time_t value.
         * @return  The timestamp as a DateTime instance.
         */
        static DateTime fromTime_t(time_t t);


        /**
         * Static function to get a DateTime instance from a 64-number corresponding to the
         * FILETIME (= the number of 100-nanosecond intervals since January 1, 1601 UTC).
         *
         * @param t The timestamp as a 64-bit number.
         * @return  The timestamp as a DateTime instance.
         */
        static DateTime fromFileTime(int64_t t);


        /**
         * Static function to sleep a number of seconds.
         *
         * @param secs The number of seconds to sleep.
         */
        static void sleep(uint32_t secs) { UaThread::sleep(secs); }


        /**
         * Static function to sleep a number of milliseconds.
         *
         * @param msecs The number of milliseconds to sleep.
         */
        static void msleep(uint32_t msecs) { UaThread::msleep(msecs); }


        /**
         * Get the stored time as a 64-bit number corresponding to the FILETIME
         * (so the number of 100-nanosecond intervals since January 1, 1601 (UTC)).
         *
         * @return The time as a 64-bit number.
         */
        uint64_t toFileTime() const { return uint64_t(uaDateTime_); }


        /**
         * Get a string representation.
         *
         * @return The string representation.
         */
        std::string toString() const;


        /**
         * Get a string representation of the 'date' part.
         *
         * @return The string representation.
         */
        std::string toDateString() const { return std::string(uaDateTime_.toDateString().toUtf8());}


        /**
         * Get a string representation of the 'time' part.
         *
         * @return The string representation.
         */
        std::string toTimeString() const { return std::string(uaDateTime_.toTimeString().toUtf8());}


        /**
         * Set the timestamp to the given double precision real number representing time_t
         * (=the number of seconds since UTC 1 January 1970 = 1970-01-01T00:00:00Z)
         * plus the number of milliseconds after the second.
         *
         * @param t     The time as a real number.
         */
        void setCtime(double t);


        /**
         * Get the time as a double precision real value corresponding to time_t + the milliseconds.
         *
         * time_t is the number of seconds since UTC 1 January 1970 = 1970-01-01T00:00:00Z.
         *
         * @return The timestamp as a real number, corresponding to toTime_t() + msec() / 1000.0.
         */
        double ctime() const { return (double)(uaDateTime_.toTime_t()) + msec() / 1000.0; }


        /**
         * Get the time as a time_t value.
         *
         * time_t is the number of seconds since UTC 1 January 1970 = 1970-01-01T00:00:00Z.
         *
         * @return The timestamp as time_t.
         */
        time_t toTime_t() const { return uaDateTime_.toTime_t(); }


        /**
         * Get the milliseconds part of the timestamp.
         *
         * @return The number of milliseconds after the second.
         */
        uint16_t msec() const { return (uint16_t)(uaDateTime_.msec()); }


        /**
         * Is the datetime NULL?
         *
         * @return True if the datetime is NULL, false if it has a real value.
         */
        bool isNull() const { return (uaDateTime_.isNull() ? true : false); }


        /**
         * Get the timestamp from an SDK UaDateTime instance.
         *
         * @param uaDateTime  SDK UaDateTime instance.
         */
        void fromSdk(const UaDateTime& uaDateTime) { uaDateTime_ = uaDateTime; }


        /**
         * Copy the timestamp to an SDK instance.
         *
         * @param uaDateTime  SDK uaDateTime instance.
         */
        void toSdk(UaDateTime& uaDateTime) const { uaDateTime = uaDateTime_; };


        /**
         * Copy the timestamp to a stack OpcUa_DateTime instance.
         *
         * @param uaDateTime  SDK uaDateTime instance.
         */
        void toSdk(OpcUa_DateTime& uaDateTime) const;


        /**
         * Get the number of days from this instance to the argument instance.
         *
         * @param other The other DateTime instance.
         * @return      Number of days.
         */
        int32_t daysTo(const DateTime& other) const;


        /**
         * Get the number of seconds from this instance to the argument instance.
         *
         * @param other The other DateTime instance.
         * @return      Number of seconds.
         */
        int32_t secsTo(const DateTime& other) const;


        /**
         * Get the number of milliseconds from this instance to the argument instance.
         *
         * @param other The other DateTime instance.
         * @return      Number of milliseconds.
         */
        int32_t msecsTo(const DateTime& other) const;


        /**
         * Add a number of seconds to the timestamp.
         *
         * @param secs Number of seconds to add.
         */
        void addSecs(int secs) { uaDateTime_.addSecs(secs); }


        /**
         * Add a number of milliseconds to the timestamp.
         *
         * @param msecs Number of milliseconds to add.
         */
        void addMilliSecs(int msecs) { uaDateTime_.addMilliSecs(msecs); }


        // comparison operators
        friend UAF_EXPORT bool operator==(const DateTime& object1, const DateTime& object2);
        friend UAF_EXPORT bool operator!=(const DateTime& object1, const DateTime& object2);
        friend UAF_EXPORT bool operator< (const DateTime& object1, const DateTime& object2);
        friend UAF_EXPORT bool operator> (const DateTime& object1, const DateTime& object2);

    private:

        // the wrapped SDK variable
        UaDateTime uaDateTime_;

    };

}



#endif /* UAF_DATETIME_H_ */
