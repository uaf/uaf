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

#ifndef UAF_EUINFORMATION_H_
#define UAF_EUINFORMATION_H_


// STD
#include <string>
#include <sstream>
#include <stdint.h>

// SDK
#include "uabase/uaeuinformation.h"
// UAF
#include "uaf/util/util.h"
#include "uaf/util/extensionobject.h"
#include "uaf/util/localizedtext.h"


namespace uaf
{

    /*******************************************************************************************//**
     * A EUInformation object holds the engineering units of a variable.
     *
     * @ingroup Util
     **********************************************************************************************/
    class UAF_EXPORT EUInformation
    {
    public:

        /**
         * Construct a EUInformation.
         */
        EUInformation();

        /**
         * Construct a EUInformation.
         */
        EUInformation(
                const std::string &namespaceUri,
                int32_t unitId,
                const uaf::LocalizedText& displayName,
                const uaf::LocalizedText& description);

        /**
         * Construct a EUInformation.
         */
        EUInformation(const uaf::ExtensionObject& extensionObject);

        /**
         * Clear the generic value.
         */
        void clear();

        /**
         * Set the namespace uri.
         */
        void setNamespaceUri(const std::string& nsUri) { uaEUInformation_.setNamespaceUri(UaString(nsUri.c_str())); }

        /**
         * Set the unit id.
         */
        void setUnitId(int32_t unitId) { uaEUInformation_.setUnitId(unitId); }

        /**
         * Set the display name.
         */
        void setDisplayName(const uaf::LocalizedText& displayName) {
            UaLocalizedText uaLocalizedText;
            displayName.toSdk(uaLocalizedText);
            uaEUInformation_.setDisplayName(uaLocalizedText);
        }

        /**
         * Set the description.
         */
        void setDescription(const uaf::LocalizedText& description) {
            UaLocalizedText uaLocalizedText;
            description.toSdk(uaLocalizedText);
            uaEUInformation_.setDescription(uaLocalizedText);
        }

        /**
         * Get the namespace uri.
         */
        std::string getNamespaceUri() const {
            return std::string(UaString(uaEUInformation_.getNamespaceUri()).toUtf8());
        }

        /**
         * Get the unit id.
         */
        uint32_t getUnitId() const { return uaEUInformation_.getUnitId(); }

        /**
         * Get the display name.
         */
        uaf::LocalizedText getDisplayName() const {
            uaf::LocalizedText ret;
            ret.fromSdk(uaEUInformation_.getDisplayName());
            return ret;
        }

        /**
         * Get the description.
         */
        uaf::LocalizedText getDescription() const {
            uaf::LocalizedText ret;
            ret.fromSdk(uaEUInformation_.getDescription());
            return ret;
        }

        /**
         * Get a string representation.
         *
         * @return The string representation.
         */
        std::string toString(const std::string& indent="", std::size_t colon=26) const;

        /**
         * Fill the instance from an SDK instance.
         */
        void fromSdk(const UaEUInformation& uaEUInformation) { uaEUInformation_ = uaEUInformation; }


        /**
         * Copy the instance to an SDK instance.
         */
        void toSdk(UaEUInformation& uaEUInformation) const { uaEUInformation = uaEUInformation_; };


    private:

        // the wrapped SDK variable
        UaEUInformation uaEUInformation_;

    };

}



#endif /* UAF_EUINFORMATION_H_ */
