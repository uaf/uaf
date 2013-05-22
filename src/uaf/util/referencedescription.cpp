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

#include "uaf/util/referencedescription.h"

namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;
    using std::vector;
    using std::size_t;


    // Constructor
    // =============================================================================================
    ReferenceDescription::ReferenceDescription()
    : isForward(false),
      nodeClass(nodeclasses::Unspecified)
    {}



    // Get a string representation
    // =============================================================================================
    string ReferenceDescription::toString(const string& indentation, size_t colon) const
    {
        stringstream ss;

        ss << indentation << " - referenceTypeId";
        ss << fillToPos(ss, colon);
        ss << ": " << referenceTypeId.toString() << "\n";

        ss << indentation << " - isForward";
        ss << fillToPos(ss, colon);
        ss << ": " << (isForward ? "True" : "False") << "\n";

        ss << indentation << " - nodeId";
        ss << fillToPos(ss, colon);
        ss << ": " << nodeId.toString() << "\n";

        ss << indentation << " - browseName";
        ss << fillToPos(ss, colon);
        ss << ": " << browseName.toString() << "\n";

        ss << indentation << " - displayName";
        ss << fillToPos(ss, colon);
        ss << ": " << displayName.toString() << "\n";

        ss << indentation << " - nodeClass";
        ss << fillToPos(ss, colon);
        ss << ": " << nodeClass << " (" << nodeclasses::toString(nodeClass) << ")\n";

        ss << indentation << " - typeDefinition";
        ss << fillToPos(ss, colon);
        ss << ": " << typeDefinition.toString();

        return ss.str();
    }

    // operator==
    // =============================================================================================
    bool operator==(const ReferenceDescription& object1, const ReferenceDescription& object2)
    {
        return    object1.referenceTypeId == object2.referenceTypeId
               && object1.isForward == object2.isForward
               && object1.nodeId == object2.nodeId
               && object1.browseName == object2.browseName
               && object1.displayName == object2.displayName
               && object1.nodeClass == object2.nodeClass
               && object1.typeDefinition == object2.typeDefinition;
    }


    // operator!=
    // =============================================================================================
    bool operator!=(const ReferenceDescription& object1, const ReferenceDescription& object2)
    {
        return !(object1 == object2);
    }


    // operator<
    // =============================================================================================
    bool operator<(const ReferenceDescription& object1, const ReferenceDescription& object2)
    {
        if (object1.referenceTypeId != object2.referenceTypeId)
            return object1.referenceTypeId < object2.referenceTypeId;
        else if (object1.isForward != object2.isForward)
            return object1.isForward < object2.isForward;
        else if (object1.nodeId != object2.nodeId)
            return object1.nodeId < object2.nodeId;
        else if (object1.browseName != object2.browseName)
            return object1.browseName < object2.browseName;
        else if (object1.displayName != object2.displayName)
            return object1.displayName < object2.displayName;
        else if (object1.nodeClass != object2.nodeClass)
            return object1.nodeClass < object2.nodeClass;
        else
            return object1.typeDefinition < object2.typeDefinition;
    }


}
