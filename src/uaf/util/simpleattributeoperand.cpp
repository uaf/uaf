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

#include "uaf/util/simpleattributeoperand.h"





namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::size_t;
    using std::stringstream;
    using std::vector;


    // Constructor
    // =============================================================================================
    SimpleAttributeOperand::SimpleAttributeOperand()
    : attributeId(uaf::attributeids::Value)
    {
        typeId = NodeId(OpcUaId_BaseEventType, 0);
    }


    // Get a string representation
    // =============================================================================================
    std::string SimpleAttributeOperand::toString(const string& indent, size_t colon) const
    {
        stringstream ss;

        ss << indent << " - typeId";
        ss << fillToPos(ss, colon);
        ss << ": " << typeId.toString();

        if(typeId == NodeId(OpcUaId_BaseEventType, 0))
            ss << " (BaseEventType)\n";
        else
            ss << "\n";

        ss << indent << " - attributeId";
        ss << fillToPos(ss, colon);
        ss << ": " << int(attributeId) << " (" << attributeids::toString(attributeId) << ")\n";

        ss << indent << " - browsePath[]";
        ss << fillToPos(ss, colon);


        if (browsePath.size() == 0)
        {
            fillToPos(ss, colon);
            ss << ": []\n";
        }
        else
        {
            ss << "\n";
            for (size_t i = 0; i<browsePath.size(); i++)
            {
                ss << indent << "    - " << "browsePath[" << i << "]";
                ss << fillToPos(ss, colon);
                ss << ": " << browsePath[i].toString() << "\n";
            }
        }

        ss << indent << " - indexRange";
        ss << fillToPos(ss, colon);
        ss << ": " << indexRange;

        return ss.str();
    }


    // operator<
    // =============================================================================================
    bool operator<(const SimpleAttributeOperand& object1, const SimpleAttributeOperand& object2)
    {
        if ( object1.attributeId != object2.attributeId )
            return object1.attributeId < object2.attributeId;
        else if ( object1.typeId != object2.typeId )
            return object1.typeId < object2.typeId;
        else if ( object1.browsePath != object2.browsePath )
            return object1.browsePath < object2.browsePath;
        else if ( object1.indexRange != object2.indexRange )
            return object1.indexRange < object2.indexRange;
        else
            return false;
    }


    // operator==
    // =============================================================================================
    bool operator==(const SimpleAttributeOperand& object1, const SimpleAttributeOperand& object2)
    {
        return    ( object1.attributeId == object2.attributeId )
               && ( object1.typeId == object2.typeId )
               && ( object1.browsePath == object2.browsePath )
               && ( object1.indexRange == object2.indexRange );
    }


    // operator!=
    // =============================================================================================
    bool operator!=(const SimpleAttributeOperand& object1, const SimpleAttributeOperand& object2)
    {
        return !(object1 == object2);
    }




}




