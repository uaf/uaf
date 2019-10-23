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

#ifndef UAF_REFERENCEDESCRIPTION_H_
#define UAF_REFERENCEDESCRIPTION_H_


// STD
#include <string>
#include <sstream>
#include <vector>
#include <stdint.h>
// SDK
#include "uaclientcpp/uadiscovery.h"
// UAF
#include "uaf/util/util.h"
#include "uaf/util/localizedtext.h"
#include "uaf/util/stringifiable.h"
#include "uaf/util/expandednodeid.h"
#include "uaf/util/qualifiedname.h"
#include "uaf/util/nodeclasses.h"


namespace uaf
{

    /*******************************************************************************************//**
    * A ReferenceDescription instance describes a Reference to a specific Node in some address
    * space.
    *
    * @ingroup Util
    ***********************************************************************************************/
    class UAF_EXPORT ReferenceDescription
    {
    public:


        /**
         * Create an empty reference description.
         */
        ReferenceDescription();


        /** The NodeId of the type of the reference. */
        uaf::NodeId referenceTypeId;

        /** True if the server followed a forward reference, false if not. */
        bool isForward;

        /** The ExpandedNodeId of the node to which the reference is pointing. */
        uaf::ExpandedNodeId nodeId;

        /** The browse name of the node to which the reference is pointing. */
        uaf::QualifiedName browseName;

        /** The display name of the node to which the reference is pointing. */
        uaf::LocalizedText displayName;

        /** The node class of the node to which the reference is pointing. */
        uaf::nodeclasses::NodeClass nodeClass;

        /** The ExpandedNodeId of the type of the node to which the reference is pointing to
         *  (only in case the node class of this node is an Object or a Variable). */
        uaf::ExpandedNodeId typeDefinition;


        /**
         * Get a string representation of the ReferenceDescription.
         *
         * @param indent Indentation to add to each line (e.g. "  " to indent with 2 spaces).
         * @param colon  The position to put the colon (double point).
         * @return       A string representation (multiple lines, separated by newline-characters).
         */
        std::string toString(const std::string& indent="", std::size_t colon=19) const;


        // comparison operators
        friend bool UAF_EXPORT operator==(
                const ReferenceDescription& object1,
                const ReferenceDescription& object2);
        friend bool UAF_EXPORT operator!=(
                const ReferenceDescription& object1,
                const ReferenceDescription& object2);
        friend bool UAF_EXPORT operator<(
                const ReferenceDescription& object1,
                const ReferenceDescription& object2);


    };


}



#endif /* UAF_REFERENCEDESCRIPTION_H_ */
