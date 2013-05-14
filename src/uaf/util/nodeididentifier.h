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

#ifndef UAF_NODEIDIDENTIFIER_H_
#define UAF_NODEIDIDENTIFIER_H_


// STD
#include <string>
#include <sstream>
#include <stdint.h>
// SDK
#include "uabase/uaexpandednodeid.h"
#include "uabase/uanodeid.h"
// UAF
#include "uaf/util/util.h"
#include "uaf/util/nodeididentifiertypes.h"
#include "uaf/util/status.h"


namespace uaf
{


    /*******************************************************************************************//**
    * A NodeIdIdentifier is the identifying part of a NodeId.
    *
    * Currently only String and Numeric identifiers are supported, Guid and Opaque are not.
    *
    * @ingroup Util
    ***********************************************************************************************/
    struct UAF_EXPORT NodeIdIdentifier
    {


        /**
         * Construct an empty NodeIdIdentifier.
         */
        NodeIdIdentifier();


        /**
         * Construct a copy of another NodeIdIdentifier.
         */
        NodeIdIdentifier(const NodeIdIdentifier& other);


        /**
         * Construct a NodeIdIdentifier based on a string.
         *
         * @param idString      String defining the identifier.
         */
        NodeIdIdentifier(const std::string& idString);


        /**
         * Construct a NodeIdIdentifier based on an numeric value.
         *
         * @param idNumeric      UInt32 value defining the identifier.
         */
        NodeIdIdentifier(const uint32_t idNumeric);



        /** Type of the identifier (e.g. NodeIdIdentifier::String or NodeIdIdentifier::Numeric). */
        uaf::nodeididentifiertypes::NodeIdIdentifierType type;

        /** String in case the type equals NodeIdIdentifier::String. */
        std::string         idString;

        /** UInt32 in case the type equals NodeIdIdentifier::Numeric. */
        uint32_t            idNumeric;


        /**
         * Get a string representation.
         *
         * @return String representation.
         */
        std::string toString() const;


        /**
         * Construct a NodeIdIdentifier based on a stack OpcUa_NodeId instance and a namespace URI.
         *
         * @param opcUaNodeId   Stack node id object.
         * @return              Good in case the NodeIdIdentifier was successfully updated.
         */
        uaf::Status fromSdk(const OpcUa_NodeId& opcUaNodeId);


        // comparison operators
        friend UAF_EXPORT bool operator==(
                const NodeIdIdentifier& object1,
                const NodeIdIdentifier& object2);
        friend UAF_EXPORT bool operator!=(
                const NodeIdIdentifier& object1,
                const NodeIdIdentifier& object2);
        friend UAF_EXPORT bool operator<(
                const NodeIdIdentifier& object1,
                const NodeIdIdentifier& object2);

    };

}


#endif /* NODEIDIDENTIFIER_H_ */
