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

#include "uaf/util/logmessage.h"

namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;


    // Constructor
    // =============================================================================================
    LogMessage::LogMessage(
            uaf::loglevels::LogLevel    level,
            const string&               applicationName,
            const string&               loggerName,
            const string&               message)
    : level(level),
      applicationName(applicationName),
      loggerName(loggerName),
      message(message)
    {
        // update the ctime
        time_t t;
        time(&t);
        ctime = t;

        // update the msec
#ifdef _MSC_VER
        SYSTEMTIME st;
        GetSystemTime(&st);
        msec = (int16_t) st.wMilliseconds;
#else
        struct timeval tv;
        gettimeofday(&tv, 0);
        msec = (int16_t) (tv.tv_usec / 1000);
#endif

    }


    // Get a string representation
    // =============================================================================================
    string LogMessage::toString() const
    {
        std::string ret;

        std::stringstream ss(message);
        std::string line;

        uint16_t noOfLines = 0;

        while ( std::getline(ss, line, '\n') )
        {
            std::string result = toTimeString(ctime, msec) + " " + loglevels::toString(level).c_str();
            result.resize(32, ' ');
            result = result + applicationName;
            result.resize(50, ' ');
            result = result + loggerName;
            result.resize(70, ' ');
            result += line;
            result += "\n";

            noOfLines++;

            ret += result;
        }

        if (noOfLines > 0)
            ret.erase(ret.length()-1);

        return ret;
    }

    // Convert a number of seconds and milliseconds to a time string like "YYYY-MM-DD hh:mm:ss.sss"
    // =============================================================================================
    string LogMessage::toTimeString(time_t t, int16_t msec) const
    {
        char buffer[20];
#ifdef _MSC_VER
        struct tm* timeInfo = localtime(&t);
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %X", timeInfo);
#else
        tm r = {0};
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %X", localtime_r(&t, &r));
#endif
        char result[100] = {0};
        sprintf(result, "%s.%03d", buffer, msec);
        return result;
    }

}


