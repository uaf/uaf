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
#include "uaf/util/nodeid.h"
#include "uaf/util/expandednodeid.h"
#include "uaf/util/localizedtext.h"
#include "uaf/util/qualifiedname.h"




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
        void clear() { uaVariant_.clear(); }


        /**
         * Check if a variant is undefined ("empty").
         *
         * @return  True if empty.
         */
        bool isNull() const { return uaVariant_.isEmpty() == 1; }


        /**
         * Get the OPC UA type of the variant.
         *
         * @return The type of the variant.
         */
        uaf::opcuatypes::OpcUaType type() const
        { return uaf::opcuatypes::fromSdkToUaf(uaVariant_.type()); }


        /**
         * Is the variant an array?
         *
         * @return True if the variant is an array.
         */
        bool isArray() const
        { return uaVariant_.isArray(); }


        /**
         * Get the array size if isArray() == true.
         *
         * @return The size of the array.
         */
        uint32_t arraySize() const
        { return uaVariant_.arraySize(); }


        /** Convert the variant to a signed 8-bit int.
         *
         * @param val   Value to update.
         * @return      Status of the conversion.
         */
        Status toSByte(int8_t &val) const
        {
            return evaluate(
                    uaVariant_.toSByte( (OpcUa_SByte&) val ),
                    uaVariant_.type(),
                    OpcUaType_SByte);
        }


        /** Convert the variant to a signed 8-bit int array.
         *
         * @param vec   Value to update.
         * @return      Status of the conversion.
         */
        Status toSByteArray(std::vector<int8_t>& vec) const
        {
            UaSByteArray arr;
            uaf::Status ret = evaluate(
                    uaVariant_.toSByteArray(arr),
                    uaVariant_.type(),
                    OpcUaType_SByte);
            vec.resize(arr.length());
            for (std::size_t i = 0; i < arr.length(); i++)
                vec[i] = arr[i];
            return ret;
        }


        /**
         * Convert the variant to an unsigned 8-bit int.
         *
         * @param val   Value to update.
         * @return      Status of the conversion.
         */
        Status toByte(uint8_t &val) const
        {
            return evaluate(
                    uaVariant_.toByte( (OpcUa_Byte&) val ),
                    uaVariant_.type(),
                    OpcUaType_Byte);
        }


        /**
         * Convert the variant to an unsigned 8-bit int array.
         *
         * @param vec   Value to update.
         * @return      Status of the conversion.
         */
        Status toByteArray(std::vector<uint8_t>& vec) const
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


        /**
         * Convert the variant to a signed 16-bit int.
         *
         * @param val   Value to update.
         * @return      Status of the conversion.
         */
        Status toInt16(int16_t &val) const
        {
            return evaluate(
                    uaVariant_.toInt16( (OpcUa_Int16&) val ),
                    uaVariant_.type(),
                    OpcUaType_Int16);
        }


        /**
         * Convert the variant to a signed 16-bit int array.
         *
         * @param vec   Value to update.
         * @return      Status of the conversion.
         */
        Status toInt16Array(std::vector<int16_t>& vec) const
        {
            UaInt16Array arr;
            uaf::Status ret = evaluate(
                    uaVariant_.toInt16Array(arr),
                    uaVariant_.type(),
                    OpcUaType_Int16);
            vec.resize(arr.length());
            for (std::size_t i = 0; i < arr.length(); i++)
                vec[i] = arr[i];
            return ret;
        }


        /**
         * Convert the variant to an unsigned 16-bit int.
         *
         * @param val   Value to update.
         * @return      Status of the conversion.
         */
        Status toUInt16(uint16_t &val) const
        {
            return evaluate(
                    uaVariant_.toUInt16( (OpcUa_UInt16&) val ),
                    uaVariant_.type(),
                    OpcUaType_UInt16);
        }


        /**
         * Convert the variant to an unsigned 16-bit int array.
         *
         * @param vec   Value to update.
         * @return      Status of the conversion.
         */
        Status toUInt16Array(std::vector<uint16_t>& vec) const
        {
            UaUInt16Array arr;
            uaf::Status ret = evaluate(
                    uaVariant_.toUInt16Array(arr),
                    uaVariant_.type(),
                    OpcUaType_UInt16);
            vec.resize(arr.length());
            for (std::size_t i = 0; i < arr.length(); i++)
                vec[i] = arr[i];
            return ret;
        }


        /**
         * Convert the variant to a signed 32-bit int.
         *
         * @param val   Value to update.
         * @return      Status of the conversion.
         */
        Status toInt32(int32_t &val) const
        {
            return evaluate(
                    uaVariant_.toInt32( (OpcUa_Int32&) val ),
                    uaVariant_.type(),
                    OpcUaType_Int32);
        }


        /**
         * Convert the variant to a signed 32-bit int array.
         *
         * @param vec   Value to update.
         * @return      Status of the conversion.
         */
        Status toInt32Array(std::vector<int32_t>& vec) const
        {
            UaInt32Array arr;
            uaf::Status ret = evaluate(
                    uaVariant_.toInt32Array(arr),
                    uaVariant_.type(),
                    OpcUaType_Int32);
            vec.resize(arr.length());
            for (std::size_t i = 0; i < arr.length(); i++)
                vec[i] = arr[i];
            return ret;
        }


        /**
         * Convert the variant to an unsigned 32-bit int.
         *
         * @param val   Value to update.
         * @return      Status of the conversion.
         */
        Status toUInt32(uint32_t &val) const
        {
            return evaluate(
                    uaVariant_.toUInt32( (OpcUa_UInt32&) val ),
                    uaVariant_.type(),
                    OpcUaType_UInt32);
        }


        /**
         * Convert the variant to an unsigned 32-bit int array.
         *
         * @param vec   Value to update.
         * @return      Status of the conversion.
         */
        Status toUInt32Array(std::vector<uint32_t>& vec) const
        {
            UaUInt32Array arr;
            uaf::Status ret = evaluate(
                    uaVariant_.toUInt32Array(arr),
                    uaVariant_.type(),
                    OpcUaType_UInt32);
            vec.resize(arr.length());
            for (std::size_t i = 0; i < arr.length(); i++)
                vec[i] = arr[i];
            return ret;
        }


        /**
         * Convert the variant to a signed 64-bit int.
         *
         * @param val   Value to update.
         * @return      Status of the conversion.
         */
        Status toInt64(int64_t &val) const
        {
            return evaluate(
                    uaVariant_.toInt64( (OpcUa_Int64&) val ),
                    uaVariant_.type(),
                    OpcUaType_Int64);
        }


        /**
         * Convert the variant to a signed 64-bit int array.
         *
         * @param vec   Value to update.
         * @return      Status of the conversion.
         */
        Status toInt64Array(std::vector<int64_t>& vec) const
        {
            UaInt64Array arr;
            uaf::Status ret = evaluate(
                    uaVariant_.toInt64Array(arr),
                    uaVariant_.type(),
                    OpcUaType_Int64);
            vec.resize(arr.length());
            for (std::size_t i = 0; i < arr.length(); i++)
                vec[i] = arr[i];
            return ret;
        }


        /**
         * Convert the variant to an unsigned 64-bit int.
         *
         * @param val   Value to update.
         * @return      Status of the conversion.
         */
        Status toUInt64(uint64_t &val) const
        {
            return evaluate(
                    uaVariant_.toUInt64( (OpcUa_UInt64&) val ),
                    uaVariant_.type(),
                    OpcUaType_UInt64);
        }


        /**
         * Convert the variant to an unsigned 64-bit int array.
         *
         * @param vec   Value to update.
         * @return      Status of the conversion.
         */
        Status toUInt64Array(std::vector<uint64_t>& vec) const
        {
            UaUInt64Array arr;
            uaf::Status ret = evaluate(
                    uaVariant_.toUInt64Array(arr),
                    uaVariant_.type(),
                    OpcUaType_UInt64);
            vec.resize(arr.length());
            for (std::size_t i = 0; i < arr.length(); i++)
                vec[i] = arr[i];
            return ret;
        }


        /**
         * Convert the variant to a bool.
         *
         * @param val   Value to update.
         * @return      Status of the conversion.
         */
        Status toBoolean(bool &val) const
        {
            OpcUa_Boolean opcUaVal;
            Status ret = evaluate(
                    uaVariant_.toBool(opcUaVal),
                    uaVariant_.type(),
                    OpcUaType_Boolean);
            val = (opcUaVal == 1);
            return ret;
        }


        /**
         * Convert the variant to a bool array.
         *
         * @param vec   Value to update.
         * @return      Status of the conversion.
         */
        Status toBooleanArray(std::vector<bool>& vec) const
        {
            UaBoolArray arr;
            uaf::Status ret = evaluate(
                    uaVariant_.toBoolArray(arr),
                    uaVariant_.type(),
                    OpcUaType_Boolean);
            vec.resize(arr.length());
            for (std::size_t i = 0; i < arr.length(); i++)
                vec[i] = arr[i];
            return ret;
        }


        /**
         * Convert the variant to a float.
         *
         * @param val   Value to update.
         * @return      Status of the conversion.
         */
        Status toFloat(float &val) const
        {
            return evaluate(uaVariant_.toFloat(val), uaVariant_.type(), OpcUaType_Float);
        }


        /**
         * Convert the variant to a float array.
         *
         * @param vec   Value to update.
         * @return      Status of the conversion.
         */
        Status toFloatArray(std::vector<float>& vec) const
        {
            UaFloatArray arr;
            uaf::Status ret = evaluate(
                    uaVariant_.toFloatArray(arr),
                    uaVariant_.type(),
                    OpcUaType_Float);
            vec.resize(arr.length());
            for (std::size_t i = 0; i < arr.length(); i++)
                vec[i] = arr[i];
            return ret;
        }


        /**
         * Convert the variant to a double.
         *
         * @param val   Value to update.
         * @return      Status of the conversion.
         */
        Status toDouble(double &val) const
        {
            return evaluate(
                    uaVariant_.toDouble(val),
                    uaVariant_.type(),
                    OpcUaType_Double);
        }


        /**
         * Convert the variant to a double array.
         *
         * @param vec   Value to update.
         * @return      Status of the conversion.
         */
        Status toDoubleArray(std::vector<double>& vec) const
        {
            UaDoubleArray arr;
            uaf::Status ret = evaluate(
                    uaVariant_.toDoubleArray(arr),
                    uaVariant_.type(),
                    OpcUaType_Double);
            vec.resize(arr.length());
            for (std::size_t i = 0; i < arr.length(); i++)
                vec[i] = arr[i];
            return ret;
        }


        /**
         * Convert the variant to a bytestring.
         *
         * @param val   Value to update.
         * @return      Status of the conversion.
         */
        Status toByteString(UaByteString& val) const
        {
            return evaluate(
                    uaVariant_.toByteString(val),
                    uaVariant_.type(),
                    OpcUaType_ByteString);
        }


        /**
         * Convert the variant to a string.
         *
         * @param val   Value to update.
         * @return      Status of the conversion.
         */
        Status toString(std::string& val) const
        {
            val = uaVariant_.toString().toUtf8();
            return uaf::Status(uaf::statuscodes::Good);
        }


        /**
         * Convert the variant to a bytestring.
         *
         * @param val   Value to update.
         * @return      Status of the conversion.
         */
        Status toByteString(uaf::ByteString& val) const
        {
            UaByteString uaByteString;
            uaf::Status ret = evaluate(
                    uaVariant_.toByteString(uaByteString),
                    uaVariant_.type(),
                    OpcUaType_ByteString);
            val.fromSdk(uaByteString);
            return ret;
        }


        /**
         * Convert the variant to a ByteString array.
         *
         * @param vec   Value to update.
         * @return      Status of the conversion.
         */
        Status toByteStringArray(std::vector<uaf::ByteString>& vec) const
        {
            UaByteStringArray arr;
            uaf::Status ret = evaluate(
                    uaVariant_.toByteStringArray(arr),
                    uaVariant_.type(),
                    OpcUaType_NodeId);
            vec.resize(arr.length());
            for (std::size_t i = 0; i < arr.length(); i++)
                vec[i].fromSdk(UaByteString(arr[i]));
            return ret;
        }


        /**
         * Convert the variant to a NodeId.
         *
         * @param val   Value to update.
         * @return      Status of the conversion.
         */
        Status toNodeId(uaf::NodeId& val) const
        {
            UaNodeId uaNodeId;
            uaf::Status ret = evaluate(
                    uaVariant_.toNodeId(uaNodeId),
                    uaVariant_.type(),
                    OpcUaType_NodeId);
            val.fromSdk(uaNodeId);
            return ret;
        }


        /**
         * Convert the variant to a NodeId array.
         *
         * @param vec   Value to update.
         * @return      Status of the conversion.
         */
        Status toNodeIdArray(std::vector<uaf::NodeId>& vec) const
        {
            UaNodeIdArray arr;
            uaf::Status ret = evaluate(
                    uaVariant_.toNodeIdArray(arr),
                    uaVariant_.type(),
                    OpcUaType_NodeId);
            vec.resize(arr.length());
            for (std::size_t i = 0; i < arr.length(); i++)
                vec[i].fromSdk(arr[i]);
            return ret;
        }


        /**
         * Convert the variant to an ExpandedNodeId.
         *
         * @param val   Value to update.
         * @return      Status of the conversion.
         */
        Status toExpandedNodeId(uaf::ExpandedNodeId& val) const
        {
            UaExpandedNodeId uaExpandedNodeId;
            uaf::Status ret = evaluate(
                    uaVariant_.toExpandedNodeId(uaExpandedNodeId),
                    uaVariant_.type(),
                    OpcUaType_ExpandedNodeId);
            val.fromSdk(uaExpandedNodeId);
            return ret;
        }


        /**
         * Convert the variant to an ExpandedNodeId array.
         *
         * @param vec   Value to update.
         * @return      Status of the conversion.
         */
        Status toExpandedNodeIdArray(std::vector<uaf::ExpandedNodeId>& vec) const
        {
            UaExpandedNodeIdArray arr;
            uaf::Status ret = evaluate(
                    uaVariant_.toExpandedNodeIdArray(arr),
                    uaVariant_.type(),
                    OpcUaType_ExpandedNodeId);
            vec.resize(arr.length());
            for (std::size_t i = 0; i < arr.length(); i++)
            {
                vec[i].fromSdk(UaExpandedNodeId(arr[i]));
            }
            return ret;
        }


        /**
         * Convert the variant to a LocalizedText.
         *
         * @param val   Value to update.
         * @return      Status of the conversion.
         */
        Status toLocalizedText(uaf::LocalizedText& val) const
        {
            UaLocalizedText uaLocalizedText;
            uaf::Status ret = evaluate(
                    uaVariant_.toLocalizedText(uaLocalizedText),
                    uaVariant_.type(),
                    OpcUaType_LocalizedText);
            val.fromSdk(uaLocalizedText);
            return ret;
        }


        /**
         * Convert the variant to a LocalizedText array.
         *
         * @param vec   Value to update.
         * @return      Status of the conversion.
         */
        Status toLocalizedTextArray(std::vector<uaf::LocalizedText>& vec) const
        {
            UaLocalizedTextArray arr;
            uaf::Status ret = evaluate(
                    uaVariant_.toLocalizedTextArray(arr),
                    uaVariant_.type(),
                    OpcUaType_LocalizedText);
            vec.resize(arr.length());
            for (std::size_t i = 0; i < arr.length(); i++)
                vec[i].fromSdk(arr[i]);
            return ret;
        }


        /**
         * Convert the variant to a QualifiedName.
         *
         * @param val   Value to update.
         * @return      Status of the conversion.
         */
        Status toQualifiedName(uaf::QualifiedName& val) const
        {
            UaQualifiedName uaQualifiedName;
            uaf::Status ret = evaluate(
                    uaVariant_.toQualifiedName(uaQualifiedName),
                    uaVariant_.type(),
                    OpcUaType_QualifiedName);
            val.fromSdk(uaQualifiedName);
            return ret;
        }


        /**
         * Convert the variant to a QualifiedName array.
         *
         * @param vec   Value to update.
         * @return      Status of the conversion.
         */
        Status toQualifiedNameArray(std::vector<uaf::QualifiedName>& vec) const
        {
            UaQualifiedNameArray arr;
            uaf::Status ret = evaluate(
                    uaVariant_.toQualifiedNameArray(arr),
                    uaVariant_.type(),
                    OpcUaType_QualifiedName);
            vec.resize(arr.length());
            for (std::size_t i = 0; i < arr.length(); i++)
                vec[i].fromSdk(arr[i]);
            return ret;
        }


        /**
         * Convert the variant to a DateTime.
         *
         * @param val   Value to update.
         * @return      Status of the conversion.
         */
        Status toDateTime(uaf::DateTime& val) const
        {
            UaDateTime uaDateTime;
            uaf::Status ret = evaluate(
                    uaVariant_.toDateTime(uaDateTime),
                    uaVariant_.type(),
                    OpcUaType_DateTime);
            val.fromSdk(uaDateTime);
            return ret;
        }


        /**
         * Convert the variant to a DateTime array.
         *
         * @param vec   Value to update.
         * @return      Status of the conversion.
         */
        Status toDateTimeArray(std::vector<uaf::DateTime>& vec) const
        {
            UaDateTimeArray arr;
            uaf::Status ret = evaluate(
                    uaVariant_.toDateTimeArray(arr),
                    uaVariant_.type(),
                    OpcUaType_DateTime);
            vec.resize(arr.length());
            for (std::size_t i = 0; i < arr.length(); i++)
                vec[i].fromSdk(arr[i]);
            return ret;
        }


        /**
         * Convert the variant to a string array.
         *
         * @param vec   Value to update.
         * @return      Status of the conversion.
         */
        Status toStringArray(std::vector<std::string>& vec) const
        {
            UaStringArray arr;
            uaf::Status ret = evaluate(
                    uaVariant_.toStringArray(arr),
                    uaVariant_.type(),
                    OpcUaType_String);
            vec.resize(arr.length());
            for (std::size_t i = 0; i < arr.length(); i++)
                vec[i] = std::string(UaString(&arr[i]).toUtf8());
            return ret;
        }


        /**
         * Set the variant to a boolean.
         *
         * @param val   New value.
         */
        void setBoolean(bool val) {
            if (val)
                uaVariant_.setBool(1);
            else
                uaVariant_.setBool(0);
        }


        /**
         * Set the variant to a boolean array.
         *
         * @param vec   New value.
         */
        void setBooleanArray(const std::vector<bool>& vec)
        {
            UaBoolArray arr;
            arr.create(vec.size());
            for (std::size_t i = 0; i < vec.size(); i++) { arr[i] = vec[i]; }
            uaVariant_.setBoolArray(arr);
        }


        /**
         * Set the variant to a signed 8-bit int.
         *
         * @param val   New value.
         */
        void setSByte(int8_t val) { uaVariant_.setSByte(val); }


        /**
         * Set the variant to a signed 8-bit int array.
         *
         * @param vec   New value.
         */
        void setSByteArray(const std::vector<int8_t>& vec)
        {
            UaSByteArray arr;
            arr.create(vec.size());
            for (std::size_t i = 0; i < vec.size(); i++) { arr[i] = vec[i]; }
            uaVariant_.setSByteArray(arr);
        }


        /**
         * Set the variant to an unsigned 8-bit int.
         *
         * @param val   New value.
         */
        void setByte(uint8_t val) { uaVariant_.setByte(val); }


        /**
         * Set the variant to an unsigned 8-bit int array.
         *
         * @param vec   New value.
         */
        void setByteArray(const std::vector<uint8_t>& vec)
        {
            UaByteArray arr;
            arr.resize(vec.size());
            for (int i = 0; i < vec.size(); i++) { arr[i] = vec[i]; }
            uaVariant_.setByteArray(arr);
        }


        /**
         * Set the variant to a signed 16-bit int.
         *
         * @param val   New value.
         */
        void setInt16(int16_t val) { uaVariant_.setInt16(val); }


        /**
         * Set the variant to a signed 16-bit int array.
         *
         * @param vec   New value.
         */
        void setInt16Array(const std::vector<int16_t>& vec)
        {
            UaInt16Array arr;
            arr.create(vec.size());
            for (std::size_t i = 0; i < vec.size(); i++) { arr[i] = vec[i]; }
            uaVariant_.setInt16Array(arr);
        }


        /**
         * Set the variant to an unsigned 16-bit int.
         *
         * @param val   New value.
         */
        void setUInt16(uint16_t val) { uaVariant_.setUInt16(val); }


        /**
         * Set the variant to an unsigned 16-bit int array.
         *
         * @param vec   New value.
         */
        void setUInt16Array(const std::vector<uint16_t>& vec)
        {
            UaUInt16Array arr;
            arr.create(vec.size());
            for (std::size_t i = 0; i < vec.size(); i++) { arr[i] = vec[i]; }
            uaVariant_.setUInt16Array(arr);
        }


        /**
         * Set the variant to a signed 32-bit int.
         *
         * @param val   New value.
         */
        void setInt32(int32_t val) { uaVariant_.setInt32(val); }


        /**
         * Set the variant to a signed 32-bit int array.
         *
         * @param vec   New value.
         */
        void setInt32Array(const std::vector<int32_t>& vec)
        {
            UaInt32Array arr;
            arr.create(vec.size());
            for (std::size_t i = 0; i < vec.size(); i++) { arr[i] = vec[i]; }
            uaVariant_.setInt32Array(arr);
        }


        /**
         * Set the variant to an unsigned 32-bit int.
         *
         * @param val   New value.
         */
        void setUInt32(uint32_t val) { uaVariant_.setUInt32(val); }


        /**
         * Set the variant to an unsigned 32-bit int array.
         *
         * @param vec   New value.
         */
        void setUInt32Array(const std::vector<uint32_t>& vec)
        {
            UaUInt32Array arr;
            arr.create(vec.size());
            for (std::size_t i = 0; i < vec.size(); i++) { arr[i] = vec[i]; }
            uaVariant_.setUInt32Array(arr);
        }


        /**
         * Set the variant to a signed 64-bit int.
         *
         * @param val   New value.
         */
        void setInt64(int64_t val) { uaVariant_.setInt64(val); }


        /**
         * Set the variant to a signed 64-bit int array.
         *
         * @param vec   New value.
         */
        void setInt64Array(const std::vector<int64_t>& vec)
        {
            UaInt64Array arr;
            arr.create(vec.size());
            for (std::size_t i = 0; i < vec.size(); i++) { arr[i] = vec[i]; }
            uaVariant_.setInt64Array(arr);
        }


        /**
         * Set the variant to an unsigned 64-bit int.
         *
         * @param val   New value.
         */
        void setUInt64(uint64_t val) { uaVariant_.setUInt64(val); }


        /**
         * Set the variant to an unsigned 64-bit int array.
         *
         * @param vec   New value.
         */
        void setUInt64Array(const std::vector<uint64_t>& vec)
        {
            UaUInt64Array arr;
            arr.create(vec.size());
            for (std::size_t i = 0; i < vec.size(); i++) { arr[i] = vec[i]; }
            uaVariant_.setUInt64Array(arr);
        }


        /**
         * Set the variant to a float.
         *
         * @param val   New value.
         */
        void setFloat(float val) { uaVariant_.setFloat(val); }


        /**
         * Set the variant to a float array.
         *
         * @param vec   New value.
         */
        void setFloatArray(const std::vector<float>& vec)
        {
            UaFloatArray arr;
            arr.create(vec.size());
            for (std::size_t i = 0; i < vec.size(); i++) { arr[i] = vec[i]; }
            uaVariant_.setFloatArray(arr);
        }


        /**
         * Set the variant to a double.
         *
         * @param val   New value.
         */
        void setDouble(double val) { uaVariant_.setDouble(val); }


        /**
         * Set the variant to a double array.
         *
         * @param vec   New value.
         */
        void setDoubleArray(const std::vector<double>& vec)
        {
            UaDoubleArray arr;
            arr.create(vec.size());
            for (std::size_t i = 0; i < vec.size(); i++) { arr[i] = vec[i]; }
            uaVariant_.setDoubleArray(arr);
        }


        /**
         * Set the variant to a string.
         *
         * @param val   New value.
         */
        void setString(const std::string& val) { uaVariant_.setString(UaString(val.c_str())); }


        /**
         * Set the variant to a bytestring.
         *
         * @param data      The data.
         * @param length    Lenght of the data.
         */
        void setByteString(uint8_t* data, int32_t length)
        {
            UaByteString byteString(length, data);
            uaVariant_.setByteString(byteString, OpcUa_True);
        }


        /**
         * Set the variant to a bytestring.
         *
         * @param val   New value
         */
        void setByteString(const uaf::ByteString& val)
        {
            UaByteString b;
            val.toSdk(b);
            uaVariant_.setByteString(b, OpcUa_True);
        }


        /**
         * Set the variant to a ByteString array.
         *
         * @param vec   New value.
         */
        void setByteStringArray(const std::vector<uaf::ByteString>& vec)
        {
            UaByteStringArray arr;
            arr.create(vec.size());
            for (std::size_t i = 0; i < vec.size(); i++) { vec[i].toSdk(&arr[i]); }
            uaVariant_.setByteStringArray(arr);
        }


        /**
         * Set the variant to a NodeId.
         *
         * @param val   New value.
         */
        void setNodeId(const uaf::NodeId& val)
        {
            UaNodeId uaNodeId;
            val.toSdk(uaNodeId);
            uaVariant_.setNodeId(uaNodeId);
        }


        /**
         * Set the variant to a NodeId array.
         *
         * @param vec   New value.
         */
        void setNodeIdArray(const std::vector<uaf::NodeId>& vec)
        {
            UaNodeIdArray arr;
            arr.create(vec.size());
            for (std::size_t i = 0; i < vec.size(); i++) { vec[i].toSdk(&arr[i]); }
            uaVariant_.setNodeIdArray(arr);
        }


        /**
         * Set the variant to an ExpandedNodeId.
         *
         * @param val   New value.
         */
        void setExpandedNodeId(const uaf::ExpandedNodeId& val)
        {
            UaExpandedNodeId uaExpandedNodeId;
            val.toSdk(uaExpandedNodeId);
            uaVariant_.setExpandedNodeId(uaExpandedNodeId);
        }


        /**
         * Set the variant to an ExpandedNodeId array.
         *
         * @param vec   New value.
         */
        void setExpandedNodeIdArray(const std::vector<uaf::ExpandedNodeId>& vec)
        {
            UaExpandedNodeIdArray arr;
            arr.create(vec.size());
            for (std::size_t i = 0; i < vec.size(); i++) { vec[i].toSdk(&arr[i]); }
            uaVariant_.setExpandedNodeIdArray(arr);
        }


        /**
         * Set the variant to an LocalizedText.
         *
         * @param val   New value.
         */
        void setLocalizedText(const uaf::LocalizedText& val)
        {
            UaLocalizedText uaLocalizedText;
            val.toSdk(uaLocalizedText);
            uaVariant_.setLocalizedText(uaLocalizedText);
        }


        /**
         * Set the variant to an LocalizedText array.
         *
         * @param vec   New value.
         */
        void setLocalizedTextArray(const std::vector<uaf::LocalizedText>& vec)
        {
            UaLocalizedTextArray arr;
            arr.create(vec.size());
            for (std::size_t i = 0; i < vec.size(); i++) { vec[i].toSdk(&arr[i]); }
            uaVariant_.setLocalizedTextArray(arr);
        }


        /**
         * Set the variant to a QualifiedName.
         *
         * @param val   New value.
         */
        void setQualifiedName(const uaf::QualifiedName& val)
        {
            UaQualifiedName uaQualifiedName;
            val.toSdk(uaQualifiedName);
            uaVariant_.setQualifiedName(uaQualifiedName);
        }


        /**
         * Set the variant to a QualifiedName array.
         *
         * @param vec   New value.
         */
        void setQualifiedNameArray(const std::vector<uaf::QualifiedName>& vec)
        {
            UaQualifiedNameArray arr;
            arr.create(vec.size());
            for (std::size_t i = 0; i < vec.size(); i++) { vec[i].toSdk(&arr[i]); }
            uaVariant_.setQualifiedNameArray(arr);
        }


        /**
         * Set the variant to a DateTime.
         *
         * @param val   New value.
         */
        void setDateTime(const uaf::DateTime& val)
        {
            UaDateTime uaDateTime;
            val.toSdk(uaDateTime);
            uaVariant_.setDateTime(uaDateTime);
        }


        /**
         * Set the variant to a DateTime array.
         *
         * @param vec   New value.
         */
        void setDateTimeArray(const std::vector<uaf::DateTime>& vec)
        {
            UaDateTimeArray arr;
            arr.create(vec.size());
            for (std::size_t i = 0; i < vec.size(); i++) { vec[i].toSdk(arr[i]); }
            uaVariant_.setDateTimeArray(arr);
        }


        /**
         * Set the variant to a string array.
         *
         * @param vec   New value.
         */
        void setStringArray(const std::vector<std::string>& vec)
        {
            UaStringArray arr;
            arr.create(vec.size());
            for (std::size_t i = 0; i < vec.size(); i++) { UaString(vec[i].c_str()).copyTo(&arr[i]); }
            uaVariant_.setStringArray(arr);
        }


        /**
         * Update an OpcUa_Variant stack object.
         *
         * @param destination   Stack object to modify.
         */
        void toSdk(OpcUa_Variant* destination) const { uaVariant_.copyTo(destination); }


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

        // internal SDK object
        UaVariant uaVariant_;


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
