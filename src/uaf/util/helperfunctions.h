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

#ifndef UAF_HELPERFUNCTIONS_H_
#define UAF_HELPERFUNCTIONS_H_

// STD
#include <string>
#include <algorithm>

#ifndef _WIN32
#include <limits.h>
#include <unistd.h>
#endif

// SDK
// UAF
#include "uaf/util/util.h"

namespace uaf
{

    /**
     * Get the host name of the platform.
     *
     * @ingroup Util
     */
    std::string UAF_EXPORT getHostName();


    /**
     * Get the path of this UAF application.
     *
     * @ingroup Util
     */
    std::string UAF_EXPORT getApplicationPath();


    /**
     * A constant variable denoting the host name at the startup of the application.
     */
    static const std::string HOST_NAME = getHostName();


    /**
     * A constant variable denoting the application path at the startup of the application.
     */
    static const std::string APPLICATION_PATH = getApplicationPath();


    /**
     * Replace variables in a string such as [hostname] and [applicationpath] by their real value.
     *
     * The tokens (hostname and applicationpath) are not case-sensitive.
     *
     * @param s     The string that may contain tokens to be replaced.
     * @return      The new string with all tokens replaced.
     *
     * @ingroup Util
     */
    std::string UAF_EXPORT replaceVariables(const std::string& s);


    /**
     * Replace the path separators (e.g. forward slashes in Windows) to backslashes.
     *
     * @param s     The string that may contain path separators to be replaced.
     * @return      The new string with all path separators replaced.
     *
     * @ingroup Util
     */
    std::string UAF_EXPORT replacePathSeparators(const std::string& s);

}

#endif /* UAF_HELPERFUNCTIONS_H_ */
