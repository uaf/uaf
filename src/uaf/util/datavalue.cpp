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

#include "uaf/util/datavalue.h"

namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;
    using std::size_t;


    // Constructor
    // =============================================================================================
    DataValue::DataValue()
    : status(statuscodes::Good),
      sourcePicoseconds(0),
      serverPicoseconds(0)
    {
        status.setOpcUaStatusCode(OpcUa_Good);
    }


    // Constructor
    // =============================================================================================
    DataValue::DataValue(const Variant& data)
    : status(statuscodes::Good),
      data(data),
      sourcePicoseconds(0),
      serverPicoseconds(0)
    {
        status.setOpcUaStatusCode(OpcUa_Good);
    }


    // Constructor
    // =============================================================================================
    DataValue::DataValue(const Variant& data, const Status& status)
    : status(status),
      data(data),
      sourcePicoseconds(0),
      serverPicoseconds(0)
    {}


    // Get a string representation
    // =============================================================================================
    string DataValue::toString(const string& indent, size_t colon) const
    {
        stringstream ss;

        ss << indent << " - status";
        ss << fillToPos(ss, colon);
        ss << ": " << status.toString() << "\n";

        ss << indent << " - data";
        ss << fillToPos(ss, colon);
        ss << ": " << data.toString() << "\n";

        ss << indent << " - sourceTimestamp";
        ss << fillToPos(ss, colon);
        ss << ": " << sourceTimestamp.toString() << "\n";

        ss << indent << " - serverTimestamp";
        ss << fillToPos(ss, colon);
        ss << ": " << serverTimestamp.toString() << "\n";

        ss << indent << " - sourcePicoseconds";
        ss << fillToPos(ss, colon);
        ss << ": " << int(sourcePicoseconds) << "\n";

        ss << indent << " - serverPicoseconds";
        ss << fillToPos(ss, colon);
        ss << ": " << int(serverPicoseconds);

        return ss.str();
    }


    // Get the contents from a UaDataValue instance
    // =============================================================================================
    void DataValue::fromSdk(const UaDataValue& uaDataValue)
    {
        status.fromSdk(uaDataValue.statusCode(), "");
        data = Variant(*uaDataValue.value());
        sourceTimestamp.fromSdk(uaDataValue.sourceTimestamp());
        serverTimestamp.fromSdk(uaDataValue.serverTimestamp());
        sourcePicoseconds = uaDataValue.sourcePicoseconds();
        serverPicoseconds = uaDataValue.serverPicoseconds();
    }


    // Copy the contents to a UaDataValue instance
    // =============================================================================================
    void DataValue::toSdk(UaDataValue& uaDataValue) const
    {
        if (!data.isNull())
        {
            OpcUa_Variant uaValue;
            data.toSdk(&uaValue);
            uaDataValue.setValue(uaValue, OpcUa_False, OpcUa_False);
        }

        uaDataValue.setStatusCode(status.opcUaStatusCode());

        if (!sourceTimestamp.isNull())
        {
            OpcUa_DateTime uaSourceTimestamp;
            sourceTimestamp.toSdk(uaSourceTimestamp);
            uaDataValue.setSourceTimestamp(uaSourceTimestamp);
            uaDataValue.setSourcePicoseconds(sourcePicoseconds);
        }

        if (!serverTimestamp.isNull())
        {
            OpcUa_DateTime uaServerTimestamp;
            serverTimestamp.toSdk(uaServerTimestamp);
            uaDataValue.setServerTimestamp(uaServerTimestamp);
            uaDataValue.setServerPicoseconds(serverPicoseconds);
        }
    }


    // Copy the contents to a OpcUa_DataValue instance
    // =============================================================================================
    void DataValue::toSdk(OpcUa_DataValue* dest) const
    {
        UaDataValue v;
        toSdk(v);
        v.copyTo(dest);
    }


    // Comparison operator ==
    // =============================================================================================
    bool operator==(const DataValue& object1, const DataValue& object2)
    {
        return    object1.status == object2.status
               && object1.data == object2.data
               && object1.sourceTimestamp == object2.sourceTimestamp
               && object1.serverTimestamp == object2.serverTimestamp
               && object1.sourcePicoseconds == object2.sourcePicoseconds
               && object1.serverPicoseconds == object2.serverPicoseconds;
    }


    // Comparison operator !=
    // =============================================================================================
    bool operator!=(const DataValue& object1, const DataValue& object2)
    {
        return !(object1 == object2);
    }


    // comparison operator <
    // =============================================================================================
    bool operator<(const DataValue& object1, const DataValue& object2)
    {
        if (object1.status != object2.status)
            return object1.status < object2.status;
        else if (object1.data != object2.data)
            return object1.data < object2.data;
        else if (object1.sourceTimestamp != object2.sourceTimestamp)
            return object1.sourceTimestamp < object2.sourceTimestamp;
        else if (object1.serverTimestamp != object2.serverTimestamp)
            return object1.serverTimestamp < object2.serverTimestamp;
        else if (object1.sourcePicoseconds != object2.sourcePicoseconds)
            return object1.sourcePicoseconds < object2.sourcePicoseconds;
        else if (object1.serverPicoseconds != object2.serverPicoseconds)
            return object1.serverPicoseconds < object2.serverPicoseconds;
    }

}


