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

#ifndef UAF_LOGLEVELS_H_
#define UAF_LOGLEVELS_H_

// STD
#include <string>
// SDK
// UAF
#include "uaf/util/util.h"


/** @file */


namespace uaf
{

    namespace loglevels
    {

        /**
         * The UAF log levels.
         *
         * @ingroup Util
         */
        enum LogLevel
        {
            Disabled = 0, /**< Don't log any messages. */
            Error    = 1, /**< Log only error messages or worse. */
            Warning  = 2, /**< Log only warning messages or worse. */
            Info     = 3, /**< Log only info messages, or warnings, or worse. */
            Debug    = 4  /**< Log all messages. */
        };

        /**
         * Get a string representation of the LogLevel.
         *
         * @param level The log level as a numerical value (e.g. 4).
         * @return              The corresponding name of the log level (e.g. "Debug").
         *
         * @ingroup Util
         */
        std::string UAF_EXPORT toString(LogLevel level);
    }



}


#endif /* UAF_LOGLEVELS_H_ */
