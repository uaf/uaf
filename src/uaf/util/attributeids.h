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

#ifndef UAF_ATTRIBUTEIDS_H_
#define UAF_ATTRIBUTEIDS_H_

// STD
#include <string>
// SDK
// UAF
#include "uaf/util/util.h"

namespace uaf
{


    namespace attributeids
    {


        /**
         * The OPC UA attribute id.
         *
         * @ingroup Util
         */
        enum AttributeId
        {
            NodeId                  = 1,    /**< The NodeId is the absolute "address" of a node, unique within an address space. */
            NodeClass               = 2,    /**< The NodeClass can be ObjectType, Object, VariableType, Variable, Method, View, ... */
            BrowseName              = 3,    /**< A BrowseName is a human readable name to browse the node within an address space. */
            DisplayName             = 4,    /**< A DisplayName is a localized, human readable name of the node. */
            Description             = 5,    /**< A Description is a localized string which describes the node. */
            WriteMask               = 6,    /**< A WriteMask specifies which node attributes can be written. */
            UserWriteMask           = 7,    /**< A UserWriteMask specifies which node attributes can be written by the current user. */
            IsAbstract              = 8,    /**< The IsAbstract flag specifies whether or not the ObjectType, VariableType or DataType can be instantiated. */
            Symmetric               = 9,    /**< The Symmetric flag specifies whether or not the forward and inverse references of the ReferenceType have the same meaning. */
            InverseName             = 10,   /**< The InverseName holds the browse name for an inverse reference. */
            ContainsNoLoops         = 11,   /**< The ContainsNoLoops flag specifies whether or not forward references of a View may result in a loop. */
            EventNotifier           = 12,   /**< Indicates that the node can be used to subscribe to events. */
            Value                   = 13,   /**< The Value holds the value of a variable. */
            DataType                = 14,   /**< The DataType holds the node id of the data type of a Variable. */
            ValueRank               = 15,   /**< The ValueRank holds the number of dimensions in the value of a VariableType. */
            ArrayDimensions         = 16,   /**< The optional ArrayDimensions is an array of dimension lengths, in case the Variable is an array. */
            AccessLevel             = 17,   /**< The AccessLevel byte specifies how a Variable may be accessed. */
            UserAccessLevel         = 18,   /**< The UserAccessLevel byte specifies how a Variable may be accessed by the current user. */
            MinimumSamplingInterval = 19,   /**< The MinimumSamplingInterval specifies the minimum sampling time (in milliseconds!) for the Variable. */
            Historizing             = 20,   /**< The Historizing flag specifies whether or not the historical data is recorded for the Variable. */
            Executable              = 21,   /**< The Executable flag specifies whether or not the Method can be called. */
            UserExecutable          = 22    /**< The UserExecutable flag specifies whether or not the Method can be called by the current user. */
        };


        /**
         * Get a string representation of the AttributeId.
         *
         * @param attributeId   The attribute id as a numerical value (e.g. 13).
         * @return              The corresponding name of the attribute id (e.g. "Value").
         *
         * @ingroup Util
         */
        std::string UAF_EXPORT toString(uaf::attributeids::AttributeId attributeId);

    };

}


#endif /* UAF_ATTRIBUTEIDS_H_ */
