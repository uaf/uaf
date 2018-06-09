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

#ifndef UAF_RANGE_H_
#define UAF_RANGE_H_


// STD
#include <string>
#include <sstream>
#include <stdint.h>

// SDK
#include "uabase/uarange.h"
// UAF
#include "uaf/util/util.h"
#include "uaf/util/extensionobject.h"


namespace uaf
{

    /*******************************************************************************************//**
     * A Range defines a low and high limit of a value.
     *
     * @ingroup Util
     **********************************************************************************************/
    class UAF_EXPORT Range
    {
    public:

        /**
         * Construct a Range.
         */
        Range();

        /**
         * Construct a Range.
         */
        Range(double low, double high);

        /**
         * Construct a Range.
         */
        Range(const uaf::ExtensionObject& extensionObject);

        /**
         * Clear the generic value.
         */
        void clear();

        /**
         * Set the low value.
         */
        void setLow(double value) { uaRange_.setLow(value); }

        /**
         * Set the low value.
         */
        void setHigh(double value) { uaRange_.setHigh(value); }

        /**
         * Get the low value.
         */
        double getLow() const { return uaRange_.getLow(); }

        /**
         * Get the low value.
         */
        double getHigh() const { return uaRange_.getHigh(); }

        /**
         * Get a string representation.
         *
         * @return The string representation.
         */
        std::string toString() const;

        /**
         * Fill the instance from an SDK instance.
         */
        void fromSdk(const UaRange& uaRange) { uaRange_ = uaRange; }


        /**
         * Copy the instance to an SDK instance.
         */
        void toSdk(UaRange& uaRange) const { uaRange = uaRange_; };


    private:

        // the wrapped SDK variable
        UaRange uaRange_;

    };

}



#endif /* UAF_RANGE_H_ */
