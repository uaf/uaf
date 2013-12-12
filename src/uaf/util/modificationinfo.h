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

#ifndef UAF_MODIFICATIONINFO_H_
#define UAF_MODIFICATIONINFO_H_


// STD
#include <string>
#include <stdint.h>
#include <sstream>
// SDK
#include "uabase/uaplatformlayer.h"
#include "uabase/uastring.h"
// UAF
#include "uaf/util/util.h"
#include "uaf/util/stringifiable.h"
#include "uaf/util/datetime.h"


namespace uaf
{



    /*******************************************************************************************//**
    * A uaf::ModificationInfo instance holds some information about a historical data modification.
    *
    * @ingroup Util
    ***********************************************************************************************/
    class UAF_EXPORT ModificationInfo : public uaf::Stringifiable
    {
    public:


        /**
         * An enum describing the type of the modification of the historical data.
         */
        enum HistoryUpdateType {
            HistoryUpdateType_Insert  = 1,
            HistoryUpdateType_Replace = 2,
            HistoryUpdateType_Update  = 3,
            HistoryUpdateType_Delete  = 4
        };


        /**
         * Construct a default ModificationInfo instance.
         */
        ModificationInfo();


        /** The time when the modification took place. */
        uaf::DateTime modificationTime;

        /** The type of the modification of the historical data. */
        uaf::ModificationInfo::HistoryUpdateType historyUpdateType;

        /** Name of the user that modified the data. */
        std::string userName;


        /**
         * Get a string representation.
         *
         * @return  A string representation.
         */
        std::string toString(const std::string& indent="", std::size_t colon=21) const;


        /**
         * Get a compact string representation.
         *
         * @return  A one-line short string representation.
         */
        std::string toCompactString() const;


        /**
         * Get the contents from a stack OpcUa_ModificationInfo instance.
         *
         * @param uaInfo   OpcUa_ModificationInfo instance (as defined by the stack)
         */
        void fromSdk(const OpcUa_ModificationInfo& uaInfo);


        // comparison operators
        friend bool UAF_EXPORT operator<(
                const ModificationInfo& object1,
                const ModificationInfo& object2);
        friend bool UAF_EXPORT operator==(
                const ModificationInfo& object1,
                const ModificationInfo& object2);
        friend bool UAF_EXPORT operator!=(
                const ModificationInfo& object1,
                const ModificationInfo& object2);

    };



}

#endif /* UAF_DATACHANGEFILTER_H_ */
