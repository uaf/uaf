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

#include "uaf/util/extensionobject.h"

namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;



    // Constructor
    // =============================================================================================
    ExtensionObject::ExtensionObject()
    {}


//    // Get the encoding type nodeid
//    // =============================================================================================
//    NodeId ExtensionObject::encodingTypeId() const
//    {
//        NodeId ret;
//        ret.fromSdk(uaExtensionObject_.encodingTypeId());
//        return ret;
//    }
//
//    // Get the data type nodeid
//    // =============================================================================================
//    NodeId ExtensionObject::dataTypeId() const
//    {
//        NodeId ret;
//        ret.fromSdk(uaExtensionObject_.dataTypeId());
//        return ret;
//    }

    
    // Get a string representation
    // =============================================================================================
    string ExtensionObject::toString(const string& indent, size_t colon) const
    {
        stringstream ss;

        ss << indent << " - encodingTypeId";
        ss << fillToPos(ss, colon);
        ss << ": " << encodingTypeId.toString() << "\n";

        ss << indent << " - dataTypeId";
        ss << fillToPos(ss, colon);
        ss << ": " << dataTypeId.toString();

        return ss.str();
    }



    // Fill the ExtensionObject from an SDK object
    // =============================================================================================
    void ExtensionObject::fromSdk(const UaExtensionObject& uaExtensionObject)
    {
        uaExtensionObject_ = uaExtensionObject;
        encodingTypeId.fromSdk(uaExtensionObject.encodingTypeId());
        dataTypeId.fromSdk(uaExtensionObject.dataTypeId());
    }

    // Fill the ExtensionObject from a stack object
    // =============================================================================================
    void ExtensionObject::fromSdk(const OpcUa_ExtensionObject& opcUaExtensionObject)
    {
        uaExtensionObject_ = UaExtensionObject(opcUaExtensionObject);
        encodingTypeId.fromSdk(uaExtensionObject_.encodingTypeId());
        dataTypeId.fromSdk(uaExtensionObject_.dataTypeId());
    }


    // Fill the SDK object
    // =============================================================================================
    void ExtensionObject::toSdk(UaExtensionObject& uaExtensionObject) const
    {
        uaExtensionObject = uaExtensionObject_;
        // cannot copy information from encodingTypeId and dataTypeId, not supported by SDK!
    }


    // Fill the SDK object
    // =============================================================================================
    void ExtensionObject::toSdk(OpcUa_ExtensionObject* opcUaExtensionObject) const
    {
        uaExtensionObject_.copyTo(opcUaExtensionObject);
        // cannot copy information from encodingTypeId and dataTypeId, not supported by SDK!
    }


}
