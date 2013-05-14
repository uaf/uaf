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

#ifndef UAF_LOGMESSAGE_H_
#define UAF_LOGMESSAGE_H_


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
// UAF
#include "uaf/util/util.h"
#include "uaf/util/loglevels.h"


namespace uaf
{




    /*******************************************************************************************//**
     * A log message holds one message (including time stamp, log level, etc.).
     *
     * @ingroup Util
     **********************************************************************************************/
    struct UAF_EXPORT LogMessage
    {
    public:


        /**
         * Construct a LogMessage.
         */
        LogMessage(
                uaf::loglevels::LogLevel    level,
                const std::string&          applicationName,
                const std::string&          loggerName,
                const std::string&          message);


        /** The number of seconds past the epoch. */
        int64_t                     ctime;

        /** The number of milliseconds past the 'ctime'. */
        int16_t                     msec;

        /** The loglevel of the message. */
        uaf::loglevels::LogLevel    level;

        /** The name of the application. */
        std::string                 applicationName;

        /** The name of the logger. */
        std::string                 loggerName;

        /** The message itself. */
        std::string                 message;


        /**
         * Get a string representation of the log message.
         *
         * @return string representation
         */
        std::string toString() const;


    private:

        /**
         * Get the current time formatted as "YYYY-MM-DD hh:mm:ss.sss".
         *
         * @param t     Number of seconds past the epoch.
         * @param msec  Number of milliseconds past t.
         * @return      String formatted as "YYYY-MM-DD hh:mm:ss.sss".
         */
        std::string toTimeString(int64_t t, int16_t msec) const;

    };

}



#endif /* UAF_LOGMESSAGE_H_ */
