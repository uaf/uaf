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

#include "uaf/util/attributeids.h"

namespace uaf
{

    namespace attributeids
    {
        using namespace uaf::attributeids;


        // Get a string representation
        // =============================================================================================
        std::string toString(AttributeId id)
        {
            switch (id)
            {
                case NodeId:                  return "NodeId";
                case NodeClass:               return "NodeClass";
                case BrowseName:              return "BrowseName";
                case DisplayName:             return "DisplayName";
                case Description:             return "Description";
                case WriteMask:               return "WriteMask";
                case UserWriteMask:           return "UserWriteMask";
                case IsAbstract:              return "IsAbstract";
                case Symmetric:               return "Symmetric";
                case InverseName:             return "InverseName";
                case ContainsNoLoops:         return "ContainsNoLoops";
                case EventNotifier:           return "EventNotifier";
                case Value:                   return "Value";
                case DataType:                return "DataType";
                case ValueRank:               return "ValueRank";
                case ArrayDimensions:         return "ArrayDimensions";
                case AccessLevel:             return "AccessLevel";
                case UserAccessLevel:         return "UserAccessLevel";
                case MinimumSamplingInterval: return "MinimumSamplingInterval";
                case Historizing:             return "Historizing";
                case Executable:              return "Executable";
                case UserExecutable:          return "UserExecutable";
                default:                      return "UNKNOWN";
            }
        }

    }
}
