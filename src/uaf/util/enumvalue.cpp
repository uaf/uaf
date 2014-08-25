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

#include "uaf/util/enumvalue.h"

namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;


    // Constructor
    // =============================================================================================
    EnumValue::EnumValue()
    {}


    // Constructor
    // =============================================================================================
    EnumValue::EnumValue(int value)
    {
        setValue(value);
    }

    // Constructor
    // =============================================================================================
    EnumValue::EnumValue(int value, const string& name)
    {
        setValue(value);
        setName(name);
    }

    // Constructor
    // =============================================================================================
    EnumValue::EnumValue(int value, const string& name, const LocalizedText& documentation)
    {
        setValue(value);
        setName(name);
        setDocumentation(documentation);
    }

    // Get a string representation
    // =============================================================================================
    string EnumValue::toString() const
    {
        stringstream ss;
        ss << value();
        if (name().size() > 0)
            ss << " = '" << name() << "'";
        if (documentation().toString().size() > 0)
            ss << " (" << documentation().toString() << ")";
        return ss.str();
    }

    // Getter/Setter of name
    // =============================================================================================
    string EnumValue::name() const
    {
        if (uaEnumValue_.name().isEmpty())
            return string("");
        else
            return string(uaEnumValue_.name().toUtf8());
    }
    void EnumValue::setName(const string& name)
    {
        uaEnumValue_.setName(UaString(name.c_str()));
    }

    // Getter/Setter of documentation
    // =============================================================================================
    LocalizedText EnumValue::documentation() const
    {
        LocalizedText localizedText;
        localizedText.fromSdk(uaEnumValue_.documentation());
        return localizedText;
    }
    void EnumValue::setDocumentation(const uaf::LocalizedText& documentation)
    {
        UaLocalizedText uaLocalizedText;
        documentation.toSdk(uaLocalizedText);
        uaEnumValue_.setDocumentation(uaLocalizedText);
    }

    // Getter/Setter of documentation
    // =============================================================================================
    int EnumValue::value() const
    {
        return uaEnumValue_.value();
    }
    void EnumValue::setValue(int i)
    {
        uaEnumValue_.setValue(i);
    }


    // Comparison operator ==
    // =============================================================================================
    bool operator==(const EnumValue& object1, const EnumValue& object2)
    {
        return    object1.value()         == object2.value()
               && object1.name()          == object2.name()
               && object1.documentation() == object2.documentation();
    }


    // Comparison operator !=
    // =============================================================================================
    bool operator!=(const EnumValue& object1, const EnumValue& object2)
    {
        return !(object1 == object2);
    }


    // comparison operator <
    // =============================================================================================
    bool operator<(const EnumValue& object1, const EnumValue& object2)
    {
        if (object1.value() != object2.value())
            return object1.value() < object2.value();
        else if (object1.name() != object2.name())
            return object1.name() < object2.name();
        else
            return object1.documentation() < object2.documentation();
    }

}


