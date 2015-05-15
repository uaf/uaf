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

#include "uaf/util/stringifiable.h"

namespace uaf
{


    // Is a string a multi-line string?
    // =============================================================================================
    std::string uint32ArrayToString(const std::vector<uint32_t> arr)
    {
        std::stringstream ss;
        std::vector<uint32_t>::const_iterator iter;
        for (iter = arr.begin(); iter != arr.end(); ++iter)
        {
            if (ss.str().size() == 0)
                ss << *iter;
            else
                ss << ", " << *iter;
        }
        return ss.str();
    }

    // Is a string a multi-line string?
    // =============================================================================================
    std::string format(const char* msg, ...)
    {
        va_list args;
        va_start(args, msg);
        char buffer[UAF_STRING_MAX_BUFFER_SIZE];
        vsprintf(buffer, msg, args);
        va_end(args);
        return std::string(buffer);
    }

    // Is a string a multi-line string?
    // =============================================================================================
    bool isMultiLine(const std::string& s)
    {
        return s.find("\n") != std::string::npos;
    }


    // Add spaces up to the given position
    // =============================================================================================
    std::string fillToPos(const std::stringstream& ss, std::size_t pos)
    {
        std::string ret;
        std::string s = ss.str();
        std::size_t fromPos = s.find_last_of('\n');
        if (fromPos == std::string::npos)
            fromPos = 0; // no \n character found, so we count from the beginning of the string
        else
            fromPos++; // advance the "from" position to just after the \n character
        std::size_t lastLineLength = s.length() - fromPos;
        if (pos > lastLineLength)
            ret.append(pos - lastLineLength, ' ');
        return ret;
    }
}
