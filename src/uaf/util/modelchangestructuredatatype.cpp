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

#include "uaf/util/modelchangestructuredatatype.h"

namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;



    // Constructor
    // =============================================================================================
    ModelChangeStructureDataType::ModelChangeStructureDataType()
    : verb(0)
    {}

    // Constructor
    // =============================================================================================
    ModelChangeStructureDataType::ModelChangeStructureDataType(const ExtensionObject& eo)
    {
        UaExtensionObject uaEO;
        eo.toSdk(uaEO);

        UaModelChangeStructureDataType uaObj(uaEO);

        verb = uaObj.getVerb();
        affected.fromSdk(uaObj.getAffected());
        affectedType.fromSdk(uaObj.getAffectedType());
    }
    
    // Get a string representation
    // =============================================================================================
    string ModelChangeStructureDataType::toString(const string& indent, size_t colon) const
    {
        stringstream ss;

        ss << indent << " - affected";
        ss << fillToPos(ss, colon);
        ss << ": " << affected.toString() << "\n";

        ss << indent << " - affectedType";
        ss << fillToPos(ss, colon);
        ss << ": " << affectedType.toString() << "\n";

        ss << indent << " - verb";
        ss << fillToPos(ss, colon);
        ss << ": " << int(verb);

        return ss.str();
    }



    // operator==
    // =============================================================================================
    bool operator==(const ModelChangeStructureDataType& object1, const ModelChangeStructureDataType& object2)
    {
        return    (object1.affected == object2.affected)
               && (object1.affectedType == object2.affectedType)
               && (object1.verb == object2.verb);
    }


    // operator!=
    // =============================================================================================
    bool operator!=(const ModelChangeStructureDataType& object1, const ModelChangeStructureDataType& object2)
    {
        return !(object1 == object2);
    }


    // operator<
    // =============================================================================================
    bool operator<(const ModelChangeStructureDataType& object1, const ModelChangeStructureDataType& object2)
    {
        if (object1.affected != object2.affected)
            return object1.affected < object2.affected;
        else if (object1.affectedType != object2.affectedType)
            return object1.affectedType < object2.affectedType;
        else
            return object1.verb < object2.verb;
    }


}
