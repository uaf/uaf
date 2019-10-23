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

#ifndef UAF_ENUMVALUE_H_
#define UAF_ENUMVALUE_H_


// STD
#include <vector>
#include <string>
#include <sstream>
#include <stdint.h>
// SDK
#include "uabasecpp/uaenumvalue.h"
// UAF
#include "uaf/util/util.h"
#include "uaf/util/localizedtext.h"


namespace uaf
{


    /*******************************************************************************************//**
     * An EnumValue represents a child of an enumerated value definition.
     *
     * @ingroup Util
     **********************************************************************************************/
    class UAF_EXPORT EnumValue
    {
    public:


        /**
         * Construct an empty EnumValue.
         */
        EnumValue();


        /**
         * Construct an EnumValue from a value.
         *
         * @param value The value of the enum
         */
        EnumValue(int value);


        /**
         * Construct an EnumValue from a value and name.
         *
         * @param value The value of the enum
         * @param name  The name of the enum
         */
        EnumValue(int value, const std::string& name);


        /**
         * Construct an EnumValue from a value and name and documentation.
         *
         * @param value         The value of the enum
         * @param name          The name of the enum
         * @param documentation The documentation of the enum
         */
        EnumValue(int value, const std::string& name, const uaf::LocalizedText& documentation);


        /** Set the name of the enum value. */
        void setName(const std::string &name);
        /** Get the name of the enum value. */
        std::string name() const;

        /** Set the documentation of the enum value. */
        void setDocumentation(const uaf::LocalizedText& documentation);
        /** Get the documentation of the enum value. */
        uaf::LocalizedText documentation() const;

        /** Set the value of the enum value. */
        void setValue(int i);
        /** Get the value of the enum value. */
        int value() const;


        /**
         * Get a string representation.
         */
        std::string toString() const;


        // comparison operators
        friend UAF_EXPORT bool operator==(const EnumValue& object1, const EnumValue& object2);
        friend UAF_EXPORT bool operator!=(const EnumValue& object1, const EnumValue& object2);
        friend UAF_EXPORT bool operator< (const EnumValue& object1, const EnumValue& object2);


        /**
         * Get the contents of the EnumValue from a SDK UaEnumValue instance.
         *
         * @param uaEnumValue  SDK UaEnumValue instance.
         */
        void fromSdk(const UaEnumValue& uaEnumValue) { uaEnumValue_ = uaEnumValue; }


        /**
         * Copy the contents to an SDK instance.
         *
         * @param uaEnumValue  SDK UaEnumValue instance.
         */
        void toSdk(UaEnumValue& uaEnumValue) const { uaEnumValue = uaEnumValue_; };


    private:

        // the wrapped SDK variable
        UaEnumValue uaEnumValue_;

    };

}



#endif /* UAF_ENUMVALUE_H_ */
