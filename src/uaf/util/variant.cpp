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

#include "uaf/util/variant.h"

namespace uaf
{
    using namespace uaf;
    using std::string;


    // Constructor
    // =============================================================================================
    Variant::Variant()
    {}


    // Constructor
    // =============================================================================================
    Variant::Variant(const OpcUa_Variant& variant)
    {
        uaVariant_ = variant;
    }


    // Get a string representation
    // =============================================================================================
    string Variant::toString() const
    {
        if (uaVariant_.type() == OpcUaType_Null)
        {
            return "NULL";
        }
        else
        {
            return string(uaVariant_.toString().toUtf8());
        }
    }


    // Get a text string representation
    // =============================================================================================
    string Variant::toTextString() const
    {
        switch (uaVariant_.type())
        {
            case OpcUaType_String:
            case OpcUaType_LocalizedText:
                return string("\"") + string(uaVariant_.toFullString().toUtf8()) + string("\"");
            default:
            {
                opcuatypes::OpcUaType type = opcuatypes::fromSdkToUaf(uaVariant_.type());
                return toFullString();
            }
        }
    }



    // Get a full string representation
    // =============================================================================================
    string Variant::toFullString() const
    {
        if (uaVariant_.type() == OpcUaType_Null)
        {
            return "NULL";
        }
        else
        {
            opcuatypes::OpcUaType type = opcuatypes::fromSdkToUaf(uaVariant_.type());
            return string("(") + opcuatypes::toString(type) + string(")")
                    + string(uaVariant_.toFullString().toUtf8());
        }
    }


    // Helper function: evaluate the status of the conversion
    // =============================================================================================
    Status Variant::evaluate(
            OpcUa_StatusCode    conversionResult,
            OpcUa_BuiltInType   fromType,
            OpcUa_BuiltInType   toType) const
    {
        Status ret;

        if (fromType != toType)
        {
            ret.setStatus(
                    statuscodes::WrongTypeError,
                    "Cannot convert %s to %s",
                    opcuatypes::toString(opcuatypes::fromSdkToUaf(fromType)).c_str(),
                    opcuatypes::toString(opcuatypes::fromSdkToUaf(toType  )).c_str());
        }
        else
        {
            ret.fromSdk(
                    conversionResult,
                    "Cannot convert the %s",
                    opcuatypes::toString(opcuatypes::fromSdkToUaf(fromType)).c_str());
        }

        return ret;
    }


    // operator==
    // =============================================================================================
    bool operator==(const Variant& object1, const Variant& object2)
    {
        return object1.uaVariant_ == object2.uaVariant_;
    }


    // operator!=
    // =============================================================================================
    bool operator!=(const Variant& object1, const Variant& object2)
    {
        return !(object1 == object2);
    }

    // operator==
    // =============================================================================================
    bool operator<(const Variant& object1, const Variant& object2)
    {
        return object1.uaVariant_ < object2.uaVariant_;
    }


}
