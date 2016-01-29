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

#ifndef UAF_PRIMITIVES_H_
#define UAF_PRIMITIVES_H_

// STD
#include <string>
#include <sstream>
#include <stdint.h>
// SDK
#include "uabase/uaplatformlayer.h"
// UAF
#include "uaf/util/util.h"
#include "uaf/util/bytestring.h"
#include "uaf/util/opcuatypes.h"


/** @file */




namespace uaf
{

    namespace primitives
    {


        #define DEFINE_PRIMITIVE(NAME, DEFAULT, CTYPE, TOSTRING)                            \
        /**  A primitive value.                                                             \
         *                                                                                  \
         * This class is only used in wrapped languages that don't support primitive        \
         * datatypes such as uint64, uint32 etc. (such as Python).                          \
         *                                                                                  \
         * @ingroup Util                                                                    \
         */                                                                                 \
        struct UAF_EXPORT NAME                                                              \
        {                                                                                   \
            /** Create a primitive with default value. */                                   \
            NAME() : value(DEFAULT) {}                                                      \
            /** Create a primitive with given value. */                                     \
            NAME(CTYPE value) : value(value) {}                                             \
            /** The value. */                                                               \
            CTYPE value;                                                                    \
            /** The type of the primitive. */                                               \
            static uaf::opcuatypes::OpcUaType type() { return uaf::opcuatypes::NAME; }      \
            /** The name of the type. */                                                    \
            static std::string typeName()                                                   \
            { return uaf::opcuatypes::toString(uaf::opcuatypes::NAME); }                    \
            /** Get a string representation. */                                             \
            std::string toString() const                                                    \
            {                                                                               \
                std::stringstream ss;                                                       \
                ss << TOSTRING;                                                             \
                return ss.str();                                                            \
            }                                                                               \
            /** comparison operators. */                                                    \
            friend UAF_EXPORT bool operator==(const NAME& object1, const NAME& object2)     \
            { return object1.value == object2.value && object1.type() == object2.type();  } \
            friend UAF_EXPORT bool operator!=(const NAME& object1, const NAME& object2)     \
            { return !(object1 == object2); }                                               \
            friend UAF_EXPORT bool operator<(const NAME& object1, const NAME& object2)      \
            {                                                                               \
                if (object1.type() != object2.type())                                       \
                    return object1.type() < object2.type();                                 \
                else                                                                        \
                    return object1.value < object2.value;                                   \
            }                                                                               \
        };


        // define some primitives:
        DEFINE_PRIMITIVE(Boolean    , false             , bool              , value)
        DEFINE_PRIMITIVE(SByte      , 0                 , int8_t            , value)
        DEFINE_PRIMITIVE(Byte       , 0                 , uint8_t           , value)
        DEFINE_PRIMITIVE(Int16      , 0                 , int16_t           , value)
        DEFINE_PRIMITIVE(UInt16     , 0                 , uint16_t          , value)
        DEFINE_PRIMITIVE(Int32      , 0                 , int32_t           , value)
        DEFINE_PRIMITIVE(UInt32     , 0                 , uint32_t          , value)
        DEFINE_PRIMITIVE(Int64      , 0                 , int64_t           , value)
        DEFINE_PRIMITIVE(UInt64     , 0                 , uint64_t          , value)
        DEFINE_PRIMITIVE(Float      , 0.0               , float             , value)
        DEFINE_PRIMITIVE(Double     , 0.0               , double            , value)
        DEFINE_PRIMITIVE(String     , ""                , std::string       , value)
        DEFINE_PRIMITIVE(ByteString , uaf::ByteString() , uaf::ByteString   , value.toString())



    }


}


#endif /* UAF_PRIMITIVES_H_ */







