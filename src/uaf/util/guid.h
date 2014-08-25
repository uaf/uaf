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

#ifndef UAF_GUID_H_
#define UAF_GUID_H_


// STD
#include <vector>
#include <string>
#include <stdint.h>
// SDK
#include "uabase/uaguid.h"
// UAF
#include "uaf/util/util.h"


namespace uaf
{


    /*******************************************************************************************//**
     * A Guid represents a Globally unique identifier.
     *
     * @ingroup Util
     **********************************************************************************************/
    class UAF_EXPORT Guid
    {
    public:


        /**
         * Construct an empty Guid.
         */
        Guid();


        /**
         * Construct a Guid from a string.
         *
         * @param s The UTF-8 string that will be converted to a binary representation.
         */
        Guid(const std::string& s);


        /**
         * Change the value of the GUID.
         *
         * @param s The UTF-8 string that will be converted to a binary representation.
         */
        void fromString(const std::string& s);


        /**
         * Get a string representation.
         */
        std::string toString() const { return std::string(uaGuid_.toString().toUtf8()); }


        /**
         * Get the contents of the GUID from a SDK UaGuid instance.
         *
         * @param uaGuid  SDK UaGuid instance.
         */
        void fromSdk(const UaGuid& uaGuid) { uaGuid_ = uaGuid; }


        /**
         * Copy the contents to an SDK instance.
         *
         * @param uaGuid  SDK UaGuid instance.
         */
        void toSdk(UaGuid& uaGuid) const { uaGuid = uaGuid_; };

        // comparison operators
        friend UAF_EXPORT bool operator==(const Guid& object1, const Guid& object2);
        friend UAF_EXPORT bool operator!=(const Guid& object1, const Guid& object2);
        friend UAF_EXPORT bool operator< (const Guid& object1, const Guid& object2);

    private:

        // the wrapped SDK variable
        UaGuid uaGuid_;

    };

}



#endif /* UAF_GUID_H_ */
