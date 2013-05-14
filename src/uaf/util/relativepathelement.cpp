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

#include "uaf/util/relativepathelement.h"

namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;
    using std::vector;



    // Constructor
    // =============================================================================================
    RelativePathElement::RelativePathElement()
    : referenceType(OpcUaId_HierarchicalReferences, 0),
      isInverse(false),
      includeSubtypes(true)
    {}


    // Constructor
    // =============================================================================================
    RelativePathElement::RelativePathElement(const QualifiedName& targetName)
    : targetName(targetName),
      referenceType(OpcUaId_HierarchicalReferences, 0),
      isInverse(false),
      includeSubtypes(true)
    {}


    // Constructor
    // =============================================================================================
    RelativePathElement::RelativePathElement(
            const QualifiedName&    targetName,
            const NodeId&           referenceType,
            bool                    isInverse,
            bool                    includeSubtypes)
    : targetName(targetName),
      referenceType(referenceType),
      isInverse(isInverse),
      includeSubtypes(includeSubtypes)
    {}


    // Get a string representation
    // =============================================================================================
    string RelativePathElement::toString(const string& indent, size_t colon) const
    {
        stringstream ss;

        ss << indent << " - targetName";
        ss << fillToPos(ss, colon);
        ss << ": " << targetName.toString() << "\n";

        ss << indent << " - referenceType";
        ss << fillToPos(ss, colon);
        ss << ": " << referenceType.toString() << "\n";

        ss << indent << " - isInverse";
        ss << fillToPos(ss, colon);
        ss << ": " << (isInverse ? "true" : "false") << "\n";

        ss << indent << " - includeSubtypes";
        ss << fillToPos(ss, colon);
        ss << ": " << (includeSubtypes ? "true" : "false");

        return ss.str();
    }


    // operator==
    // =============================================================================================
    bool operator==(const RelativePathElement& object1, const RelativePathElement& object2)
    {
        return    object1.targetName       == object2.targetName
               && object1.referenceType    == object2.referenceType
               && object1.isInverse        == object2.isInverse
               && object1.includeSubtypes  == object2.includeSubtypes;
    }


    // operator!=
    // =============================================================================================
    bool operator!=(const RelativePathElement& object1, const RelativePathElement& object2)
    {
        return !(object1 == object2);
    }


    // operator<
    // =============================================================================================
    bool operator<(const RelativePathElement& object1, const RelativePathElement& object2)
    {
        if (object1.targetName != object2.targetName)
            return object1.targetName < object2.targetName;
        else if (object1.referenceType != object2.referenceType)
            return object1.referenceType < object2.referenceType;
        else if (object1.isInverse != object2.isInverse)
            return object1.isInverse < object2.isInverse;
        else
            return object1.includeSubtypes  < object2.includeSubtypes;
    }


}
