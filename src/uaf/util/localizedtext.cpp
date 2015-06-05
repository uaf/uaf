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

#include "uaf/util/localizedtext.h"

namespace uaf
{
    using namespace uaf;
    using std::string;



    // Constructor
    // =============================================================================================
    LocalizedText::LocalizedText()
    {}



    // Constructor
    // =============================================================================================
    LocalizedText::LocalizedText(const LocalizedText& other)
    : uaLocalizedText_(other.uaLocalizedText_)
    {}


    // Constructor
    // =============================================================================================
    LocalizedText::LocalizedText(const string& locale, const string& text)
    : uaLocalizedText_(locale.c_str(), text.c_str())
    {}



    // Constructor
    // =============================================================================================
    LocalizedText::LocalizedText(const OpcUa_LocalizedText& opcUaLocalizedText)
    : uaLocalizedText_(opcUaLocalizedText)
    {}


    // Get the text part
    // =============================================================================================
    string LocalizedText::text() const
    {
        UaString uaString(uaLocalizedText_.text());

        if (uaString.isNull() || uaString.isEmpty())
            return "";
        else
            return string(uaString.toUtf8());
    }


    // Get the locale part
    // =============================================================================================
    string LocalizedText::locale() const
    {
        UaString uaString(uaLocalizedText_.locale());

        if (uaString.isNull() || uaString.isEmpty())
            return "";
        else
            return string(uaString.toUtf8());
    }


    // Get a string representation
    // =============================================================================================
    string LocalizedText::toString() const
    {
        if (!uaLocalizedText_.isNull())
            return string(uaLocalizedText_.toString().toUtf8());
        else
            return string("");
    }


    // Get a full string representation
    // =============================================================================================
    string LocalizedText::toFullString() const
    {
        if (!uaLocalizedText_.isNull())
            return string(uaLocalizedText_.toFullString().toUtf8());
        else
            return string("''");
    }


    // Fill the localized text from an SDK object
    // =============================================================================================
    void LocalizedText::fromSdk(const UaLocalizedText& uaLocalizedText)
    {
        uaLocalizedText_ = uaLocalizedText;
    }


    // Fill the SDK object
    // =============================================================================================
    void LocalizedText::toSdk(UaLocalizedText& uaLocalizedText) const
    {
        uaLocalizedText = uaLocalizedText_;
    }


    // Fill the SDK object
    // =============================================================================================
    void LocalizedText::toSdk(OpcUa_LocalizedText* uaLocalizedText) const
    {
        uaLocalizedText_.copyTo(uaLocalizedText);
    }


    // operator==
    // =============================================================================================
    bool operator==(const LocalizedText& object1, const LocalizedText& object2)
    {
        return object1.uaLocalizedText_ == object2.uaLocalizedText_;
    }


    // operator!=
    // =============================================================================================
    bool operator!=(const LocalizedText& object1, const LocalizedText& object2)
    {
        return !(object1 == object2);
    }


    // operator<
    // =============================================================================================
    bool operator<(const LocalizedText& object1, const LocalizedText& object2)
    {
        if (object1.locale() != object2.locale())
            return object1.locale() < object2.locale();
        else
            return object1.text() < object2.text();
    }


}
