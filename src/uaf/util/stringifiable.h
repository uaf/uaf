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

#ifndef UAF_STRINGIFIABLE_H_
#define UAF_STRINGIFIABLE_H_


// STD
#include <string>
#include <sstream>
// SDK
// UAF
#include "uaf/util/util.h"


namespace uaf
{


    /**
     * Does a string have multiline characters or not?
     *
     * @param s     String to be checked for newline characters.
     * @return      True if the string has multiline characters.
     *
     * @ingroup Util
     */
    bool UAF_EXPORT isMultiLine(const std::string& s);


    /**
     * Add spaces from the beginning of the stream (or the last newline character) up to the given
     * character position.
     *
     * @ingroup Util
     */
    std::string UAF_EXPORT fillToPos(const std::stringstream& ss, std::size_t pos);


    /*******************************************************************************************//**
    * An Stringifiable interface provides a function to get a string representation of the object.
    *
    * @ingroup Util
    ***********************************************************************************************/
    class UAF_EXPORT Stringifiable
    {
    public:
        /**
         * Get a string representation.
         *
         * @param indent    The indentation to include in front of each line (often just an empty
         *                  string, but it may also be for example "   ").
         * @param colon     In case of key : value pairs, the colon will be put at this position.
         */
        virtual std::string toString(const std::string& indent="", std::size_t colon=0) const = 0;
    };


}



#endif /* UAF_STRINGIFIABLE_H_ */
