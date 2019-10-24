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

#ifndef UAF_RELATIVEPATHELEMENT_H_
#define UAF_RELATIVEPATHELEMENT_H_


// STD
#include <vector>
#include <string>
// SDK
#include "uabasecpp/uabase.h"
// UAF
#include "uaf/util/util.h"
#include "uaf/util/stringifiable.h"
#include "uaf/util/qualifiedname.h"
#include "uaf/util/constants.h"
#include "uaf/util/nodeid.h"


namespace uaf
{


    /*******************************************************************************************//**
     * A RelativePathElement describes one element of a RelativePath and basically contains a target
     * (a qualified name), the type of the reference to this target, and some other properties.
     *
     * @ingroup Util
     **********************************************************************************************/
    class UAF_EXPORT RelativePathElement
    {
    public:

        /**
         * Construct an empty RelativePathElement.
         */
        RelativePathElement();


        /**
         * Construct a RelativePathElement with a target name and default other properties.
         *
         * By default:
         *  - hierarchical references will be followed, OR a subtype of hierarchical references
         *  - the forward (and not the inverse) reference will be followed
         *
         * @param targetName        The target of the element, as a qualified name.
         */
        RelativePathElement(const uaf::QualifiedName& targetName);


        /**
         * Construct a RelativePathElement with full freedom to choose reference type, to include
         * subtypes or not, etc.
         *
         * @param targetName        The target of the element, as a qualified name.
         * @param referenceType     The type of the reference, as a NodeId (which can be resolved,
         *                          but may be unresolved!).
         * @param isInverse         True to use the inverse reference.
         * @param includeSubtypes   True to include subtypes of the reference type.
         */
        RelativePathElement(
                const uaf::QualifiedName&   targetName,
                const uaf::NodeId&          referenceType,
                bool                        isInverse,
                bool                        includeSubtypes);


        /** The target name. */
        uaf::QualifiedName targetName;

        /** The reference type as a NodeId (which may, or may not be resolved) */
        uaf::NodeId referenceType;

        /** Flag specifying whether or not the inverse reference is meant. */
        bool isInverse;

        /** Flag specifying if subtypes of the reference type should be included. */
        bool includeSubtypes;


        /**
         * Get a string representation of the browse path.
         *
         * @return string representation
         */
        std::string toString(const std::string& indent="", std::size_t colon=16) const;


        // comparison operators
        friend UAF_EXPORT bool operator==(
                const RelativePathElement& object1,
                const RelativePathElement& object2);
        friend UAF_EXPORT bool operator!=(
                const RelativePathElement& object1,
                const RelativePathElement& object2);
        friend UAF_EXPORT bool operator<(
                const RelativePathElement& object1,
                const RelativePathElement& object2);

    };

}


#endif /* UAF_RELATIVEPATHELEMENT_H_ */
