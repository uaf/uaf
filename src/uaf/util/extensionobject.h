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

#ifndef UAF_EXTENSIONOBJECT_H_
#define UAF_EXTENSIONOBJECT_H_


// STD
#include <string>
#include <sstream>
// SDK
#include "uabasecpp/uaextensionobject.h"
// UAF
#include "uaf/util/util.h"
#include "uaf/util/stringifiable.h"
#include "uaf/util/nodeid.h"


namespace uaf
{


    /*******************************************************************************************//**
     * An ExtensionObject is a special type of Variant (see variant.h).
     *
     * @ingroup Util
     **********************************************************************************************/
    class UAF_EXPORT ExtensionObject
    {
    public:

        /**
         * Construct an empty ExtensionObject.
         */
        ExtensionObject();


        /**
         * Get a string representation.
         *
         * @return string representation
         */
        std::string toString(const std::string& indent="", std::size_t colon=18) const;
        
        
        /** Get the NodeId of the DataTypeEncoding node of the server. */
        uaf::NodeId encodingTypeId;
        
        /** Returns the data type id of the encodeable object.*/
        uaf::NodeId dataTypeId;

//        /** Get the NodeId of the DataTypeEncoding node of the server. */
//        uaf::NodeId encodingTypeId() const;
//
//        /** Returns the data type id of the encodeable object.*/
//        uaf::NodeId dataTypeId() const;

        
        /** Fill the extension object from an SDK object. */
        void fromSdk(const UaExtensionObject& uaExtensionObject);


        /** Fill the extension object from a stack object. */
        void fromSdk(const OpcUa_ExtensionObject& opcUaExtensionObject);


        /** Fill the SDK object. */
        void toSdk(UaExtensionObject& uaExtensionObject) const;


        /** Fill the stack object. */
        void toSdk(OpcUa_ExtensionObject* uaExtensionObject) const;


    private:
        UaExtensionObject uaExtensionObject_;
    };

}


#endif /* UAF_EXTENSIONOBJECT_H_ */
