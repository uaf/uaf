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

#include "uaf/util/variant.h"

namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;


    // Constructor
    // =============================================================================================
    Variant::Variant()
    : isNativeUaf_(false),
      dataTypeIfNativeUaf_(opcuatypes::Null),
      arrayTypeIfNativeUaf_(OpcUa_VariantArrayType_Scalar)
    {}


    // Constructor
    // =============================================================================================
    Variant::Variant(const OpcUa_Variant& variant)
    : uaVariant_(variant),
      isNativeUaf_(false),
      dataTypeIfNativeUaf_(opcuatypes::Null),
      arrayTypeIfNativeUaf_(OpcUa_VariantArrayType_Scalar)
    {}


    // Convert the variant to a native C++ uint8_t.
    // =============================================================================================
    Status Variant::toByteArray(std::vector<uint8_t>& vec) const
    {
        UaByteArray arr;
        uaf::Status ret = evaluate(
                uaVariant_.toByteArray(arr),
                uaVariant_.type(),
                OpcUaType_Byte);
        vec.resize(arr.size());
        for (int i = 0; i < arr.size(); i++)
            vec[i] = arr[i];
        return ret;
    }

#define IMPLEMENT_VARIANT_TOXXX_METHOD(XXX, CPPTYPE)                                               \
    /** Convert the variant to a native C++ type.                                                  \
    =========================================================================================== */ \
    Status Variant::to##XXX(CPPTYPE &val) const                                                    \
    {                                                                                              \
        return evaluate(                                                                           \
                uaVariant_.to##XXX( (OpcUa_##XXX &) val ),                                         \
                uaVariant_.type(),                                                                 \
                OpcUaType_##XXX);                                                                  \
    }

    IMPLEMENT_VARIANT_TOXXX_METHOD(SByte  , int8_t)
    IMPLEMENT_VARIANT_TOXXX_METHOD(Byte   , uint8_t)
    IMPLEMENT_VARIANT_TOXXX_METHOD(Int16  , int16_t)
    IMPLEMENT_VARIANT_TOXXX_METHOD(UInt16 , uint16_t)
    IMPLEMENT_VARIANT_TOXXX_METHOD(Int32  , int32_t)
    IMPLEMENT_VARIANT_TOXXX_METHOD(UInt32 , uint32_t)
    IMPLEMENT_VARIANT_TOXXX_METHOD(Int64  , int64_t)
    IMPLEMENT_VARIANT_TOXXX_METHOD(UInt64 , uint64_t)
    IMPLEMENT_VARIANT_TOXXX_METHOD(Float  , float)
    IMPLEMENT_VARIANT_TOXXX_METHOD(Double , double)



#define IMPLEMENT_VARIANT_TOXXXARRAY_METHOD(XXX, CPPTYPE)                                          \
    /** Convert the variant to a native C++ array.                                                 \
    =========================================================================================== */ \
    Status Variant::to##XXX##Array(std::vector<CPPTYPE>& vec) const                                \
    {                                                                                              \
        Ua##XXX##Array arr;                                                                        \
        uaf::Status ret = evaluate(                                                                \
                uaVariant_.to##XXX##Array(arr),                                                    \
                uaVariant_.type(),                                                                 \
                OpcUaType_##XXX);                                                                  \
        vec.resize(arr.length());                                                                  \
        for (std::size_t i = 0; i < arr.length(); i++)                                             \
            vec[i] = arr[i];                                                                       \
        return ret;                                                                                \
    }

    IMPLEMENT_VARIANT_TOXXXARRAY_METHOD(SByte  , int8_t)
    IMPLEMENT_VARIANT_TOXXXARRAY_METHOD(Int16  , int16_t)
    IMPLEMENT_VARIANT_TOXXXARRAY_METHOD(UInt16 , uint16_t)
    IMPLEMENT_VARIANT_TOXXXARRAY_METHOD(Int32  , int32_t)
    IMPLEMENT_VARIANT_TOXXXARRAY_METHOD(UInt32 , uint32_t)
    IMPLEMENT_VARIANT_TOXXXARRAY_METHOD(Int64  , int64_t)
    IMPLEMENT_VARIANT_TOXXXARRAY_METHOD(UInt64 , uint64_t)
    IMPLEMENT_VARIANT_TOXXXARRAY_METHOD(Float  , float)
    IMPLEMENT_VARIANT_TOXXXARRAY_METHOD(Double , double)



#define IMPLEMENT_VARIANT_TOXXX_METHOD_NATIVE_UAF(XXX, INTERNAL)                                   \
    /** Convert the variant to a (possibly native UAF) C++ type.                                   \
    =========================================================================================== */ \
    Status Variant::to##XXX(uaf::XXX& val) const                                                   \
    {                                                                                              \
        uaf::Status ret;                                                                           \
        if (isNativeUaf_)                                                                          \
        {                                                                                          \
            if (dataTypeIfNativeUaf_ != uaf::opcuatypes::XXX)                                           \
                ret.setStatus(uaf::statuscodes::WrongTypeError, "The variant is of the wrong type");    \
            else if (arrayTypeIfNativeUaf_ != OpcUa_VariantArrayType_Scalar)                            \
                ret.setStatus(uaf::statuscodes::WrongTypeError, "The variant is not a scalar");         \
            else if (INTERNAL.size() != 1)                                                              \
                ret.setStatus(uaf::statuscodes::UnexpectedError, "Bug: wrong size of internal vector"); \
            else                                                                                   \
            {                                                                                      \
                ret.setGood();                                                                     \
                val = INTERNAL[0];                                                                 \
            }                                                                                      \
        }                                                                                          \
        else                                                                                       \
        {                                                                                          \
            Ua##XXX uaObject;                                                                      \
            ret = evaluate(uaVariant_.to##XXX(uaObject), uaVariant_.type(), OpcUaType_##XXX);      \
            val.fromSdk(uaObject);                                                                 \
        }                                                                                          \
        return ret;                                                                                \
    }

    IMPLEMENT_VARIANT_TOXXX_METHOD_NATIVE_UAF(NodeId          , nodeId_)
    IMPLEMENT_VARIANT_TOXXX_METHOD_NATIVE_UAF(ExpandedNodeId  , expandedNodeId_)
    IMPLEMENT_VARIANT_TOXXX_METHOD_NATIVE_UAF(QualifiedName   , qualifiedName_)
    IMPLEMENT_VARIANT_TOXXX_METHOD_NATIVE_UAF(ExtensionObject , extensionObject_)



#define IMPLEMENT_VARIANT_TOXXXARRAY_METHOD_NATIVE_UAF(XXX, INTERNAL)                              \
    /** Convert the variant to a (possibly native UAF) C++ array.                                  \
    =========================================================================================== */ \
    uaf::Status Variant::to##XXX##Array(std::vector<uaf::XXX>& vec) const                          \
    {                                                                                              \
        uaf::Status ret;                                                                           \
        if (isNativeUaf_)                                                                          \
        {                                                                                              \
            if (dataTypeIfNativeUaf_ != uaf::opcuatypes::XXX)                                          \
                ret.setStatus(uaf::statuscodes::WrongTypeError, "The variant is of the wrong type");   \
            else if (arrayTypeIfNativeUaf_ != OpcUa_VariantArrayType_Array)                            \
                ret.setStatus(uaf::statuscodes::WrongTypeError, "The variant is not a array");         \
            else                                                                                   \
            {                                                                                      \
                ret.setGood();                                                                     \
                vec = INTERNAL;                                                                    \
            }                                                                                      \
        }                                                                                          \
        else                                                                                       \
        {                                                                                          \
            Ua##XXX##Array arr;                                                                    \
            ret = evaluate(                                                                        \
                    uaVariant_.to##XXX##Array(arr),                                                \
                    uaVariant_.type(),                                                             \
                    OpcUaType_##XXX);                                                              \
            vec.resize(arr.length());                                                              \
            for (std::size_t i = 0; i < arr.length(); i++)                                         \
                vec[i].fromSdk(arr[i]);                                                            \
        }                                                                                          \
        return ret;                                                                                \
    }

    IMPLEMENT_VARIANT_TOXXXARRAY_METHOD_NATIVE_UAF(NodeId          , nodeId_)
    IMPLEMENT_VARIANT_TOXXXARRAY_METHOD_NATIVE_UAF(ExpandedNodeId  , expandedNodeId_)
    IMPLEMENT_VARIANT_TOXXXARRAY_METHOD_NATIVE_UAF(QualifiedName   , qualifiedName_)
    IMPLEMENT_VARIANT_TOXXXARRAY_METHOD_NATIVE_UAF(ExtensionObject , extensionObject_)




#define IMPLEMENT_VARIANT_SETXXX_METHOD(XXX, CPPTYPE)                                              \
    /** Set the variant to a C++ primitive type.                                                   \
    =========================================================================================== */ \
    void Variant::set##XXX(CPPTYPE val)                                                            \
    {                                                                                              \
        clear();                                                                                   \
        uaVariant_.set##XXX(val);                                                                  \
    }

    IMPLEMENT_VARIANT_SETXXX_METHOD(SByte  , int8_t)
    IMPLEMENT_VARIANT_SETXXX_METHOD(Byte   , uint8_t)
    IMPLEMENT_VARIANT_SETXXX_METHOD(Int16  , int16_t)
    IMPLEMENT_VARIANT_SETXXX_METHOD(UInt16 , uint16_t)
    IMPLEMENT_VARIANT_SETXXX_METHOD(Int32  , int32_t)
    IMPLEMENT_VARIANT_SETXXX_METHOD(UInt32 , uint32_t)
    IMPLEMENT_VARIANT_SETXXX_METHOD(Int64  , int64_t)
    IMPLEMENT_VARIANT_SETXXX_METHOD(UInt64 , uint64_t)
    IMPLEMENT_VARIANT_SETXXX_METHOD(Float  , float)
    IMPLEMENT_VARIANT_SETXXX_METHOD(Double , double)


    // Set the variant to a C++ primitive byte array.
    // ===========================================================================================
    void Variant::setByteArray(const std::vector<uint8_t>& vec)
    {
        clear();
        UaByteArray arr;
        arr.resize(vec.size());
        for (std::size_t i = 0; i < vec.size(); i++) { arr[int(i)] = vec[i]; }
        uaVariant_.setByteArray(arr);
    }


#define IMPLEMENT_VARIANT_SETXXXARRAY_METHOD(XXX, CPPTYPE)                                         \
    /** Set the variant to a C++ primitive type.                                                   \
    =========================================================================================== */ \
    void Variant::set##XXX##Array(const std::vector<CPPTYPE>& vec)                                 \
    {                                                                                              \
        clear();                                                                                   \
        Ua##XXX##Array arr;                                                                        \
        arr.create(vec.size());                                                                    \
        for (std::size_t i = 0; i < vec.size(); i++) { arr[i] = vec[i]; }                          \
        uaVariant_.set##XXX##Array(arr);                                                           \
    }

    IMPLEMENT_VARIANT_SETXXXARRAY_METHOD(SByte  , int8_t)
    IMPLEMENT_VARIANT_SETXXXARRAY_METHOD(Int16  , int16_t)
    IMPLEMENT_VARIANT_SETXXXARRAY_METHOD(UInt16 , uint16_t)
    IMPLEMENT_VARIANT_SETXXXARRAY_METHOD(Int32  , int32_t)
    IMPLEMENT_VARIANT_SETXXXARRAY_METHOD(UInt32 , uint32_t)
    IMPLEMENT_VARIANT_SETXXXARRAY_METHOD(Int64  , int64_t)
    IMPLEMENT_VARIANT_SETXXXARRAY_METHOD(UInt64 , uint64_t)
    IMPLEMENT_VARIANT_SETXXXARRAY_METHOD(Float  , float)
    IMPLEMENT_VARIANT_SETXXXARRAY_METHOD(Double , double)


    // Convert the variant to a bool.
    // =============================================================================================
    Status Variant::toBoolean(bool &val) const
    {
        OpcUa_Boolean opcUaVal;
        Status ret = evaluate(uaVariant_.toBool(opcUaVal), uaVariant_.type(), OpcUaType_Boolean);
        val = (bool)(opcUaVal);
        return ret;
    }

    // Convert the variant to a bool vector.
    // =============================================================================================
    Status Variant::toBooleanArray(std::vector<bool>& vec) const
    {
        UaBoolArray arr;
        uaf::Status ret = evaluate(uaVariant_.toBoolArray(arr), uaVariant_.type(), OpcUaType_Boolean);
        vec.resize(arr.length());
        for (std::size_t i = 0; i < arr.length(); i++)
            vec[i] = arr[i];
        return ret;
    }

    // Set the variant to a boolean.
    // =============================================================================================
    void Variant::setBoolean(bool val)
    {
        clear();
        uaVariant_.setBool(val ? OpcUa_True : OpcUa_False);
    }

    // Set the variant to a boolean array.
    // =============================================================================================
    void Variant::setBooleanArray(const std::vector<bool>& vec)
    {
        clear();
        UaBoolArray arr;
        arr.create(vec.size());
        for (std::size_t i = 0; i < vec.size(); i++) { arr[i] = vec[i]; }
        uaVariant_.setBoolArray(arr);
    }



    // Convert the variant to a string.
    // =============================================================================================
    Status Variant::toString(string &val) const
    {
        val = uaVariant_.toString().toUtf8();
        return uaf::Status(uaf::statuscodes::Good);
    }


    // Convert the variant to a string array.
    // =============================================================================================
    Status Variant::toStringArray(std::vector<std::string>& vec) const
    {
        UaStringArray arr;
        Status ret = evaluate(uaVariant_.toStringArray(arr), uaVariant_.type(), OpcUaType_String);
        vec.resize(arr.length());
        for (std::size_t i = 0; i < arr.length(); i++)
            vec[i] = string(UaString(&arr[i]).toUtf8());
        return ret;
    }


    // Set the variant to a string.
    // =============================================================================================
    void Variant::setString(const std::string& val)
    {
        clear();
        uaVariant_.setString(UaString(val.c_str()));
    }


    // Set the variant to a string array.
    // =============================================================================================
    void Variant::setStringArray(const std::vector<std::string>& vec)
    {
        clear();
        UaStringArray arr;
        arr.create(vec.size());
        for (std::size_t i = 0; i < vec.size(); i++) { UaString(vec[i].c_str()).copyTo(&arr[i]); }
        uaVariant_.setStringArray(arr);
    }


#define IMPLEMENT_VARIANT_TOXXX_METHOD_COMPLEX(XXX)                                                \
    /** Convert the variant to a complex native C++ type.                                          \
    =========================================================================================== */ \
    Status Variant::to##XXX(uaf::XXX& val) const                                                   \
    {                                                                                              \
        Ua##XXX ua##XXX;                                                                           \
        Status ret = evaluate(uaVariant_.to##XXX(ua##XXX), uaVariant_.type(), OpcUaType_##XXX);    \
        val.fromSdk(ua##XXX);                                                                      \
        return ret;                                                                                \
    }


    IMPLEMENT_VARIANT_TOXXX_METHOD_COMPLEX(ByteString)
    IMPLEMENT_VARIANT_TOXXX_METHOD_COMPLEX(LocalizedText)
    IMPLEMENT_VARIANT_TOXXX_METHOD_COMPLEX(DateTime)


#define IMPLEMENT_VARIANT_TOXXXARRAY_METHOD_COMPLEX(XXX)                                           \
    /** Convert the variant to a complex native C++ array.                                         \
    =========================================================================================== */ \
    Status Variant::to##XXX##Array(std::vector<uaf::XXX>& vec) const                               \
    {                                                                                              \
        Ua##XXX##Array arr;                                                                        \
        Status ret = evaluate(uaVariant_.to##XXX##Array(arr), uaVariant_.type(), OpcUaType_##XXX); \
        vec.resize(arr.length());                                                                  \
        for (std::size_t i = 0; i < arr.length(); i++)                                             \
            vec[i].fromSdk(Ua##XXX(arr[i]));                                                       \
        return ret;                                                                                \
    }

    IMPLEMENT_VARIANT_TOXXXARRAY_METHOD_COMPLEX(ByteString)
    IMPLEMENT_VARIANT_TOXXXARRAY_METHOD_COMPLEX(LocalizedText)
    IMPLEMENT_VARIANT_TOXXXARRAY_METHOD_COMPLEX(DateTime)


#define IMPLEMENT_VARIANT_SETXXX_METHOD_COMPLEX_WITH_DETACH(XXX)                                   \
    /** Convert the variant to a complex native C++ type.                                          \
    =========================================================================================== */ \
    void Variant::set##XXX(const uaf::XXX& val)                                                    \
    {                                                                                              \
        clear();                                                                                   \
        Ua##XXX uaObject;                                                                          \
        val.toSdk(uaObject);                                                                       \
        uaVariant_.set##XXX(uaObject, OpcUa_True);                                                 \
    }
    IMPLEMENT_VARIANT_SETXXX_METHOD_COMPLEX_WITH_DETACH(ByteString)


#define IMPLEMENT_VARIANT_SETXXX_METHOD_COMPLEX(XXX)                                               \
    /** Convert the variant to a complex native C++ type.                                          \
    =========================================================================================== */ \
    void Variant::set##XXX(const uaf::XXX& val)                                                    \
    {                                                                                              \
        clear();                                                                                   \
        Ua##XXX uaObject;                                                                          \
        val.toSdk(uaObject);                                                                       \
        uaVariant_.set##XXX(uaObject);                                                             \
    }
    IMPLEMENT_VARIANT_SETXXX_METHOD_COMPLEX(LocalizedText)
    IMPLEMENT_VARIANT_SETXXX_METHOD_COMPLEX(DateTime)


#define IMPLEMENT_VARIANT_SETXXXARRAY_METHOD_COMPLEX(XXX)                                          \
    /** Convert the variant to a complex native C++ type.                                          \
    =========================================================================================== */ \
    void Variant::set##XXX##Array(const std::vector<uaf::XXX>& vec)                                         \
    {                                                                                              \
        clear();                                                                                   \
        Ua##XXX##Array arr;                                                                        \
        arr.create(vec.size());                                                                    \
        for (std::size_t i = 0; i < vec.size(); i++) { vec[i].toSdk(&arr[i]); }                    \
        uaVariant_.set##XXX##Array(arr);                                                           \
    }
    IMPLEMENT_VARIANT_SETXXXARRAY_METHOD_COMPLEX(ByteString)
    IMPLEMENT_VARIANT_SETXXXARRAY_METHOD_COMPLEX(LocalizedText)
    IMPLEMENT_VARIANT_SETXXXARRAY_METHOD_COMPLEX(DateTime)


#define IMPLEMENT_VARIANT_SETXXX_METHOD_NATIVE_UAF(XXX, INTERNAL)                                  \
    /** Convert the variant to a native uaf:: C++ type.                                            \
    =========================================================================================== */ \
    void Variant::set##XXX(const uaf::XXX& val)                                                    \
    {                                                                                              \
        clear();                                                                                   \
        isNativeUaf_ = true;                                                                       \
        dataTypeIfNativeUaf_  = uaf::opcuatypes::XXX;                                              \
        INTERNAL.push_back(val);                                                                   \
    }
    IMPLEMENT_VARIANT_SETXXX_METHOD_NATIVE_UAF(QualifiedName, qualifiedName_)
    IMPLEMENT_VARIANT_SETXXX_METHOD_NATIVE_UAF(NodeId, nodeId_)
    IMPLEMENT_VARIANT_SETXXX_METHOD_NATIVE_UAF(ExpandedNodeId, expandedNodeId_)
    IMPLEMENT_VARIANT_SETXXX_METHOD_NATIVE_UAF(ExtensionObject, extensionObject_)


#define IMPLEMENT_VARIANT_SETXXXARRAY_METHOD_NATIVE_UAF(XXX, INTERNAL)                             \
    /** Convert the variant to a native uaf:: C++ type.                                            \
    =========================================================================================== */ \
    void Variant::set##XXX##Array(const std::vector<uaf::XXX>& vec)                                \
    {                                                                                              \
        clear();                                                                                   \
        isNativeUaf_ = true;                                                                       \
        dataTypeIfNativeUaf_  = uaf::opcuatypes::XXX;                                              \
        arrayTypeIfNativeUaf_ = OpcUa_VariantArrayType_Array;                                      \
        INTERNAL = vec;                                                                            \
    }
    IMPLEMENT_VARIANT_SETXXXARRAY_METHOD_NATIVE_UAF(QualifiedName, qualifiedName_)
    IMPLEMENT_VARIANT_SETXXXARRAY_METHOD_NATIVE_UAF(NodeId, nodeId_)
    IMPLEMENT_VARIANT_SETXXXARRAY_METHOD_NATIVE_UAF(ExpandedNodeId, expandedNodeId_)
    IMPLEMENT_VARIANT_SETXXXARRAY_METHOD_NATIVE_UAF(ExtensionObject, extensionObject_)


    // Get a string representation
    // =============================================================================================
    string Variant::toString() const
    {
        uaf::opcuatypes::OpcUaType t = type();

        stringstream ss;

        if (t == uaf::opcuatypes::Null)
        {
            ss << "NULL";
        }
        else
        {
            if (isNativeUaf_)
            {
                if (isArray())
                {
                    ss << "{";

                    for (uint32_t i = 0; i < arraySize(); i++)
                    {
                        if (i > 0) ss << ",";

                        switch (t)
                        {
                            case uaf::opcuatypes::NodeId:
                                ss << nodeId_[i].toString();
                                break;
                            case uaf::opcuatypes::ExpandedNodeId:
                                ss << expandedNodeId_[i].toString();
                                break;
                            case uaf::opcuatypes::QualifiedName:
                                ss << qualifiedName_[i].toString();
                                break;
                            case uaf::opcuatypes::ExtensionObject:
                                ss << extensionObject_[i].toString();
                                break;
                            default:
                                ss << "INVALID";
                                break;
                        }
                    }

                    ss << "}";
                }
                else
                {
                    switch (t)
                    {
                        case uaf::opcuatypes::NodeId:
                            ss << nodeId_[0].toString();
                            break;
                        case uaf::opcuatypes::ExpandedNodeId:
                            ss << expandedNodeId_[0].toString();
                            break;
                        case uaf::opcuatypes::QualifiedName:
                            ss << qualifiedName_[0].toString();
                            break;
                        case uaf::opcuatypes::ExtensionObject:
                            ss << extensionObject_[0].toString();
                            break;
                        default:
                            ss << "INVALID";
                            break;
                    }
                }
            }
            else
            {
                ss << string(uaVariant_.toString().toUtf8());
            }
        }

        return ss.str();
    }




#define IMPLEMENT_VARIANT_TOSDK_NATIVE_UAF(TYPE, INTERNAL)                                         \
    if (isArray())                                                                                 \
    {                                                                                              \
        Ua##TYPE##Array array;                                                                     \
        array.resize(INTERNAL.size());                                                             \
        for (std::size_t i = 0; i<INTERNAL.size(); i++)                                            \
            INTERNAL[i].toSdk(&array[i]);                                                          \
        uaVariant.set##TYPE##Array(array);                                                         \
    }                                                                                              \
    else                                                                                           \
    {                                                                                              \
        Ua##TYPE uaObject;                                                                         \
        INTERNAL[0].toSdk(uaObject);                                                               \
        uaVariant.set##TYPE(uaObject);                                                             \
    }

#define IMPLEMENT_VARIANT_TOSDK_NATIVE_UAF_WITH_DETACH(TYPE, INTERNAL)                             \
    if (isArray())                                                                                 \
    {                                                                                              \
        Ua##TYPE##Array array;                                                                     \
        array.resize(INTERNAL.size());                                                             \
        for (std::size_t i = 0; i<INTERNAL.size(); i++)                                            \
            INTERNAL[i].toSdk(&array[i]);                                                          \
        uaVariant.set##TYPE##Array(array);                                                         \
    }                                                                                              \
    else                                                                                           \
    {                                                                                              \
        Ua##TYPE uaObject;                                                                         \
        INTERNAL[0].toSdk(uaObject);                                                               \
        uaVariant.set##TYPE(uaObject, OpcUa_False);                                                \
    }



    // toSdk
    // =============================================================================================
    void Variant::toSdk(OpcUa_Variant* destination) const
    {
        if (isNativeUaf_)
        {
            UaVariant uaVariant;
            if (type() == uaf::opcuatypes::NodeId)
            {
                IMPLEMENT_VARIANT_TOSDK_NATIVE_UAF(NodeId, nodeId_)
            }
            else if (type() == uaf::opcuatypes::ExpandedNodeId)
            {
                IMPLEMENT_VARIANT_TOSDK_NATIVE_UAF(ExpandedNodeId, expandedNodeId_)
            }
            else if (type() == uaf::opcuatypes::QualifiedName)
            {
                IMPLEMENT_VARIANT_TOSDK_NATIVE_UAF(QualifiedName, qualifiedName_)
            }
            else if (type() == uaf::opcuatypes::ExtensionObject)
            {
                IMPLEMENT_VARIANT_TOSDK_NATIVE_UAF_WITH_DETACH(ExtensionObject, extensionObject_)
            }
            uaVariant.copyTo(destination);
        }
        else
        {
            uaVariant_.copyTo(destination);
        }
    }


    // Get a text string representation
    // =============================================================================================
    string Variant::toTextString() const
    {
        switch (type())
        {
            case uaf::opcuatypes::String:
            case uaf::opcuatypes::LocalizedText:
            {
                stringstream ss;
                ss << "\"" << toFullString() << "\"";
                return ss.str();
            }
            default:
                return toFullString();
        }
    }



    // Get a full string representation
    // =============================================================================================
    string Variant::toFullString() const
    {
        opcuatypes::OpcUaType t = type();

        stringstream ss;

        if (t == uaf::opcuatypes::Null)
            ss << "NULL";
        else
            ss << "(" << opcuatypes::toString(t) << (isArray() ? "Array" : "") << ")" << toString();

        return ss.str();
    }


    // Helper function: evaluate the status of the conversion
    // =============================================================================================
    Status Variant::evaluate(
            OpcUa_StatusCode    conversionResult,
            OpcUa_BuiltInType   fromType,
            OpcUa_BuiltInType   toType) const
    {
        Status ret;

        if (fromType != toType)
        {
            ret.setStatus(
                    statuscodes::WrongTypeError,
                    "Cannot convert %s to %s",
                    opcuatypes::toString(opcuatypes::fromSdkToUaf(fromType)).c_str(),
                    opcuatypes::toString(opcuatypes::fromSdkToUaf(toType  )).c_str());
        }
        else
        {
            ret.fromSdk(
                    conversionResult,
                    "Cannot convert the %s",
                    opcuatypes::toString(opcuatypes::fromSdkToUaf(fromType)).c_str());
        }

        return ret;
    }


    // Clear the Variant
    // =============================================================================================
    void Variant::clear()
    {
        uaVariant_.clear();
        nodeId_.clear();
        expandedNodeId_.clear();
        qualifiedName_.clear();
        extensionObject_.clear();
        isNativeUaf_ = false;
        dataTypeIfNativeUaf_ = opcuatypes::Null;
        arrayTypeIfNativeUaf_ = OpcUa_VariantArrayType_Scalar;
    }


    // Get the data type
    // =============================================================================================
    opcuatypes::OpcUaType Variant::type() const
    {
        if (isNativeUaf_)
            return dataTypeIfNativeUaf_;
        else
            return uaf::opcuatypes::fromSdkToUaf(uaVariant_.type());
    }


    // Does the variant represent an array?
    // =============================================================================================
    bool Variant::isArray() const
    {
        if (isNativeUaf_)
            return arrayTypeIfNativeUaf_ == OpcUa_VariantArrayType_Array;
        else
            return (bool)(uaVariant_.isArray());
    }


    // Size of the array in case isArra() is True
    // =============================================================================================
    uint32_t Variant::arraySize() const
    {
        if (isNativeUaf_)
        {
            switch (type())
            {
                case uaf::opcuatypes::NodeId:
                    return nodeId_.size();
                case uaf::opcuatypes::ExpandedNodeId:
                    return expandedNodeId_.size();
                case uaf::opcuatypes::QualifiedName:
                    return qualifiedName_.size();
                case uaf::opcuatypes::ExtensionObject:
                    return extensionObject_.size();
                default:
                    return -1;
            }
        }
        else
            return uaVariant_.arraySize();
    }


    // operator==
    // =============================================================================================
    bool operator==(const Variant& object1, const Variant& object2)
    {
        // first we test the most likely situation
        if ( (!object1.isNativeUaf_) && (!object2.isNativeUaf_) )
        {
            return object1.uaVariant_ == object2.uaVariant_;
        }
        // else, test the whole lot
        else
        {
            return    object1.uaVariant_ == object2.uaVariant_
                   && object1.isNativeUaf_ == object2.isNativeUaf_
                   && object1.arrayTypeIfNativeUaf_ == object2.arrayTypeIfNativeUaf_
                   && object1.dataTypeIfNativeUaf_ == object2.dataTypeIfNativeUaf_
                   && object1.expandedNodeId_ == object2.expandedNodeId_
                   && object1.nodeId_ == object2.nodeId_
                   && object1.qualifiedName_ == object2.qualifiedName_;
        }
    }


    // operator!=
    // =============================================================================================
    bool operator!=(const Variant& object1, const Variant& object2)
    {
        return !(object1 == object2);
    }

    // operator==
    // =============================================================================================
    bool operator<(const Variant& object1, const Variant& object2)
    {
        if (object1.uaVariant_ != object2.uaVariant_)
            return object1.uaVariant_ < object2.uaVariant_;
        else if (object1.isNativeUaf_ != object2.isNativeUaf_)
            return object1.isNativeUaf_ < object2.isNativeUaf_;
        else if (object1.arrayTypeIfNativeUaf_ != object2.arrayTypeIfNativeUaf_)
            return object1.arrayTypeIfNativeUaf_ < object2.arrayTypeIfNativeUaf_;
        else if (object1.dataTypeIfNativeUaf_ != object2.dataTypeIfNativeUaf_)
            return object1.dataTypeIfNativeUaf_ < object2.dataTypeIfNativeUaf_;
        else if (object1.expandedNodeId_ != object2.expandedNodeId_)
            return object1.expandedNodeId_ < object2.expandedNodeId_;
        else if (object1.nodeId_ != object2.nodeId_)
            return object1.nodeId_ < object2.nodeId_;
        else
            return object1.qualifiedName_ < object2.qualifiedName_;
    }


}
