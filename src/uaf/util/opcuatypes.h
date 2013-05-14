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

#ifndef UAF_OPCUATYPES_H_
#define UAF_OPCUATYPES_H_

// STD
#include <string>
// SDK
#include "uabase/uaplatformlayer.h"
// UAF
#include "uaf/util/util.h"


/** @file */


namespace uaf
{

    namespace opcuatypes
    {

        /**
         * The OPC UA type.
         *
         * @ingroup Util
         */
        enum OpcUaType
        {
            Null            = 0,
            Boolean         = 1,
            SByte           = 2,
            Byte            = 3,
            Int16           = 4,
            UInt16          = 5,
            Int32           = 6,
            UInt32          = 7,
            Int64           = 8,
            UInt64          = 9,
            Float           = 10,
            Double          = 11,
            String          = 12,
            DateTime        = 13,
            Guid            = 14,
            ByteString      = 15,
            XmlElement      = 16,
            NodeId          = 17,
            ExpandedNodeId  = 18,
            StatusCode      = 19,
            QualifiedName   = 20,
            LocalizedText   = 21,
            ExtensionObject = 22,
            DataValue       = 23,
            Variant         = 24,
            DiagnosticInfo  = 25
        };


        /**
         * Get a string representation of the OPC UA type.
         *
         * @param type  The OPC UA type (as an enum).
         * @return      The corresponding name of the OPC UA type.
         *
         * @ingroup Util
         */
        std::string UAF_EXPORT toString(uaf::opcuatypes::OpcUaType type);


        /**
         * Convert the SDK/Stack instance to a UAF instance.
         *
         * @ingroup Util
         */
        OpcUaType UAF_EXPORT fromSdkToUaf(OpcUa_BuiltInType type);


        /**
         * Convert the UAF instance to a SDK/Stack instance.
         *
         * @ingroup Util
         */
        OpcUa_BuiltInType UAF_EXPORT fromUafToSdk(OpcUaType type);

    }


}


#endif /* UAF_OPCUATYPES_H_ */
