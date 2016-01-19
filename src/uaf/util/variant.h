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

#ifndef UAF_VARIANT_H_
#define UAF_VARIANT_H_


// STD
#include <string>
#include <sstream>
#include <vector>
#include <cctype>
#include <stdint.h>
#include <stdio.h>
#include <iostream>
// SDK
#include "uabase/uavariant.h"
// UAF
#include "uaf/util/util.h"
#include "uaf/util/status.h"
#include "uaf/util/datetime.h"
#include "uaf/util/bytestring.h"
#include "uaf/util/opcuatypes.h"
#include "uaf/util/guid.h"
#include "uaf/util/nodeid.h"
#include "uaf/util/expandednodeid.h"
#include "uaf/util/localizedtext.h"
#include "uaf/util/qualifiedname.h"
#include "uaf/util/extensionobject.h"

#include "uaf/util/primitives.h"





namespace uaf
{


    /*******************************************************************************************//**
    * A Variant is a union class that can hold various kinds of data types.
    *
    * A variant can hold primitive types and some OPC UA related non-primitive types (such as a
    * NodeId).
    *
    * @ingroup Util
    ***********************************************************************************************/
    class UAF_EXPORT Variant
    {
    public:


        /**
         * Construct an empty variant.
         */
        Variant();


        /**
         * Construct a copy of a OpcUa_Variant stack object.
         */
        Variant(const OpcUa_Variant &variant);


        /**
         * Clear the variant.
         */
        void clear();


        /**
         * Check if a variant is undefined ("empty").
         *
         * @return  True if empty.
         */
        bool isNull() const { return (!isNativeUaf_) && ((bool)(uaVariant_.isEmpty())); }


        /**
         * Get the OPC UA type of the variant.
         *
         * @return The type of the variant.
         */
        uaf::opcuatypes::OpcUaType type() const;


        /**
         * Is the variant an array?
         *
         * @return True if the variant is an array.
         */
        bool isArray() const;


        /**
         * Get the array size if isArray() == true.
         *
         * @return The size of the array.
         */
        uint32_t arraySize() const;


#define DECLARE_VARIANT_METHODS(XXX, TYPE, CONSTTYPE)                                              \
        /** Convert the variant to the specified type.                                             \
         *                                                                                         \
         * @param val   Value to update.                                                           \
         * @return      Status of the conversion.                                                  \
         */                                                                                        \
        uaf::Status to##XXX(TYPE& val) const;                                                      \
                                                                                                   \
        /** Convert the variant array to a native C++ primitive vector.                            \
         *                                                                                         \
         * @param vec   Value to update.                                                           \
         * @return      Status of the conversion.                                                  \
         */                                                                                        \
        Status to##XXX##Array(std::vector<TYPE>& vec) const;                                       \
                                                                                                   \
        /** Set the variant to a C++ primitive type.                                               \
         *                                                                                         \
         * @param val   New value.                                                                 \
         */                                                                                        \
        void set##XXX(CONSTTYPE val);                                                              \
                                                                                                   \
        /** Set the variant to a C++ primitive array.                                              \
         *                                                                                         \
         * @param vec   New value.                                                                 \
         */                                                                                        \
        void set##XXX##Array(const std::vector<TYPE>& vec);




        DECLARE_VARIANT_METHODS(Boolean         , bool                , bool)
        DECLARE_VARIANT_METHODS(SByte           , int8_t              , int8_t)
        DECLARE_VARIANT_METHODS(Byte            , uint8_t             , uint8_t)
        DECLARE_VARIANT_METHODS(Int16           , int16_t             , int16_t)
        DECLARE_VARIANT_METHODS(UInt16          , uint16_t            , uint16_t)
        DECLARE_VARIANT_METHODS(Int32           , int32_t             , int32_t)
        DECLARE_VARIANT_METHODS(UInt32          , uint32_t            , uint32_t)
        DECLARE_VARIANT_METHODS(Int64           , int64_t             , int64_t)
        DECLARE_VARIANT_METHODS(UInt64          , uint64_t            , uint64_t)
        DECLARE_VARIANT_METHODS(Float           , float               , float)
        DECLARE_VARIANT_METHODS(Double          , double              , double)
        DECLARE_VARIANT_METHODS(ByteString      , uaf::ByteString     , const uaf::ByteString&)
        DECLARE_VARIANT_METHODS(NodeId          , uaf::NodeId         , const uaf::NodeId&)
        DECLARE_VARIANT_METHODS(Guid            , uaf::Guid           , const uaf::Guid&)
        DECLARE_VARIANT_METHODS(ExpandedNodeId  , uaf::ExpandedNodeId , const uaf::ExpandedNodeId&)
        DECLARE_VARIANT_METHODS(QualifiedName   , uaf::QualifiedName  , const uaf::QualifiedName&)
        DECLARE_VARIANT_METHODS(LocalizedText   , uaf::LocalizedText  , const uaf::LocalizedText&)
        DECLARE_VARIANT_METHODS(DateTime        , uaf::DateTime       , const uaf::DateTime&)
        DECLARE_VARIANT_METHODS(String          , std::string         , const std::string&)
        DECLARE_VARIANT_METHODS(ExtensionObject , uaf::ExtensionObject, const uaf::ExtensionObject&)


        /**
         * Set the variant to a bytestring.
         *
         * @param data The data.
         * @param length Lenght of the data.
         */
        void setByteString(uint8_t* data, int32_t length)
        {
            clear();
            UaByteString byteString(length, data);
            uaVariant_.setByteString(byteString, OpcUa_True);
        }


        /**
         * Update an OpcUa_Variant stack object.
         *
         * @param destination   Stack object to modify.
         */
        void toSdk(OpcUa_Variant* destination) const;


        /**
         * Get a UTF-8 encoded string representation of the variant.
         *
         * @return  String representation.
         */
        std::string toString() const;


        /**
         * Get a (possibly "quoted") UTF-8 encoded string representation of the variant.
         *
         * This method will add quotes if the type of the variant is a textual value.
         * Some examples: 4, 3.14, "some text", ...
         *
         * @return  String representation.
         */
        std::string toTextString() const;


        /**
         * Get an elaborate string representation of the variant.
         *
         * @return  Full string representation.
         */
        std::string toFullString() const;


        // comparison operators
        friend UAF_EXPORT bool operator==(const Variant& object1, const Variant& object2);
        friend UAF_EXPORT bool operator!=(const Variant& object1, const Variant& object2);
        friend UAF_EXPORT bool operator<(const Variant& object1, const Variant& object2);


    private:

        // internal SDK object - used for everything but the ones hereafter
        UaVariant uaVariant_;

        // variant types that must be stored as a native UAF instance
        // (because these support namespace URIs and/or server URIs instead of only
        //  namespace IDs and/or server IDs)
        // We store them as vectors, so that they can also represent array types if necessary.
        std::vector<uaf::NodeId> nodeId_;
        std::vector<uaf::Guid> guid_;
        std::vector<uaf::ExpandedNodeId> expandedNodeId_;
        std::vector<uaf::QualifiedName> qualifiedName_;
        std::vector<uaf::ExtensionObject> extensionObject_;

        bool isNativeUaf_;
        uaf::opcuatypes::OpcUaType dataTypeIfNativeUaf_;
        OpcUa_Byte arrayTypeIfNativeUaf_;


        /**
         * Helper function to evaluate the conversion result and create a nice Status object.
         *
         * @param conversionResult  Result from the conversion.
         * @param fromType          The conversion was from this type.
         * @param toType            The conversion was to this type.
         */
        Status evaluate(OpcUa_StatusCode    conversionResult,
                        OpcUa_BuiltInType   fromType,
                        OpcUa_BuiltInType   toType) const;
    };




}


#endif /* UAF_VARIANT_H_ */
