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

#include "uaf/util/matrix.h"


namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;
    using std::vector;
    using std::size_t;


    // Constructor
    // =============================================================================================
    Matrix::Matrix()
    : type(uaf::opcuatypes::Null),
      opcUaStatusCode_(0)
    {
    }


    // Clear the matrix
    // =============================================================================================
    void Matrix::clear()
    {
        uaVariant_.clear();
    }


    // Get the status
    // =============================================================================================
    SdkStatus Matrix::status() const
    {
        return SdkStatus(opcUaStatusCode_);
    }


    // Set the matrix element
    // =============================================================================================
    void Matrix::setElement(std::vector<int32_t> dimensionNumbers, const Variant& value)
    {
        int32_t i = getElementNumber(dimensionNumbers);
        if (i >= 0 && (uint32_t)i < elements.size())
        {
            elements[i] = value;
        }
    }

    // Get the matrix element
    // =============================================================================================
    uaf::Variant Matrix::getElement(std::vector<int32_t> dimensionNumbers) const
    {
        int32_t i = getElementNumber(dimensionNumbers);
        if (i >= 0 && (uint32_t)i < elements.size())
        {
            return elements[i];
        }
        else
        {
            return uaf::Variant();
        }
    }


    // Get a string representation
    // =============================================================================================
    string Matrix::toString(const string& indent, size_t colon) const
    {
        stringstream ss;


        if (uaVariant_.isMatrix())
        {
            std::vector<int32_t> counters(dimensions.size());
            for (std::size_t i = 0; i < counters.size(); i++)
                counters[i] = 0;

            // e.g. counters = [0,0,0]

            for (std::size_t elem = 0; elem < elements.size(); elem++)
            {
                // print the counters
                for (std::size_t dim = 0; dim < dimensions.size(); dim++)
                {
                    ss << '[' << counters[dim] << ']';
                }

                // increment the right counter
                for (std::size_t dim = dimensions.size() - 1; dim >= 0; dim--)
                {
                    if (counters[dim] + 1 < dimensions[dim])
                    {
                        counters[dim]++;
                        break;
                    }
                    else if (dim == 0)
                    {
                        break; // last element
                    }
                    else
                    {
                        counters[dim] = 0;
                    }
                }

                // print the element
                ss << " = " << elements[elem].toString().c_str() << '\n';

                std::cout << ss.str();
                ss.str("");
            }
        }
        else
        {
            ss << "ERROR: NOT A MATRIX";
        }

        return ss.str();
    }




#define MATRIX_FROMSDK_CASE(UATYPE, CPPTYPE, ITYPE, LENGTH)                \
                case OpcUaType_##UATYPE:                                    \
                { \
                    Ua##UATYPE##Array ar;                                   \
                    UaInt32Array uaDimensions;                                \
                    opcUaStatusCode_ = uaVariant_.to##CPPTYPE##Matrix(ar, uaDimensions);   \
                    for (ITYPE i = 0; i < ar.LENGTH(); i++)                 \
                    {                                                       \
                        UaVariant v;                                        \
                        v.set##CPPTYPE(ar[i]);                              \
                        elements[i].fromSdk(v);                             \
                    }                                                       \
                    dimensions.resize(uaDimensions.length());               \
                    for (uint32_t i = 0; i < uaDimensions.length(); i++)    \
                    {                                                       \
                        dimensions[i] = uaDimensions[i];                    \
                    }                                                       \
                    type = uaf::opcuatypes::UATYPE;                         \
                    break;                                                  \
                }


    // Copy from SDK
    // =============================================================================================
    void Matrix::fromSdk(const UaVariant& uaVariant)
    {
        uaVariant_ = uaVariant;
        type = uaf::opcuatypes::fromSdkToUaf(uaVariant.type());

        if (uaVariant_.noOfMatrixElements() > 0)
        {
            elements.resize(uaVariant_.noOfMatrixElements());

            switch (uaVariant_.type())
            {
                case OpcUaType_Null:
                    break;
                MATRIX_FROMSDK_CASE(Boolean, Bool, OpcUa_UInt32, length)
                MATRIX_FROMSDK_CASE(SByte, SByte, OpcUa_UInt32, length)
                MATRIX_FROMSDK_CASE(Byte, Byte, OpcUa_Int32, size)
                MATRIX_FROMSDK_CASE(UInt16, UInt16, OpcUa_UInt32, length)
                MATRIX_FROMSDK_CASE(Int16, Int16, OpcUa_UInt32, length)
                MATRIX_FROMSDK_CASE(UInt32, UInt32, OpcUa_UInt32, length)
                MATRIX_FROMSDK_CASE(Int32, Int32, OpcUa_UInt32, length)
                MATRIX_FROMSDK_CASE(UInt64, UInt64, OpcUa_UInt32, length)
                MATRIX_FROMSDK_CASE(Int64, Int64, OpcUa_UInt32, length)
                MATRIX_FROMSDK_CASE(Float, Float, OpcUa_UInt32, length)
                MATRIX_FROMSDK_CASE(Double, Double, OpcUa_UInt32, length)
                MATRIX_FROMSDK_CASE(String, String, OpcUa_UInt32, length)
                MATRIX_FROMSDK_CASE(DateTime, DateTime, OpcUa_UInt32, length)
                MATRIX_FROMSDK_CASE(Guid, Guid, OpcUa_UInt32, length)
                MATRIX_FROMSDK_CASE(NodeId, NodeId, OpcUa_UInt32, length)
                MATRIX_FROMSDK_CASE(ExpandedNodeId, ExpandedNodeId, OpcUa_UInt32, length)
                MATRIX_FROMSDK_CASE(QualifiedName, QualifiedName, OpcUa_UInt32, length)
                MATRIX_FROMSDK_CASE(LocalizedText, LocalizedText, OpcUa_UInt32, length)
                default:
                    break;

            }
        }

    }


#define MATRIX_TOSDK_CASE(UATYPE, CPPTYPE, ITYPE, LENGTH)                   \
            case OpcUaType_##UATYPE:                                        \
            {                                                               \
                Ua##UATYPE##Array uaElements;                               \
                uaElements.resize(elements.size());                         \
                for (std::size_t i = 0; i < elements.size(); i++)           \
                {                                                           \
                    elements[i].toSdk(uaElement);                           \
                    uaElement.to##UATYPE(uaElements[i]);                    \
                }                                                           \
                uaVariant_.set##CPPTYPE##Matrix(uaElements, uaDimensions);  \
                break;                                                      \
            }

#define MATRIX_TOSDK_CASE2(UATYPE, CPPTYPE, PTYPE, ITYPE, LENGTH)           \
            case OpcUaType_##UATYPE:                                        \
            {                                                               \
                Ua##UATYPE##Array uaElements;                               \
                uaElements.resize(elements.size());                         \
                for (std::size_t i = 0; i < elements.size(); i++)           \
                {                                                           \
                    elements[i].toSdk(uaElement);                           \
                    PTYPE p;                                                \
                    uaElement.to##UATYPE(p);                                \
                    p.copyTo(&uaElements[i]);                               \
                }                                                           \
                uaVariant_.set##CPPTYPE##Matrix(uaElements, uaDimensions);  \
                break;                                                      \
            }


    // Copy to SDK
    // =============================================================================================
    void Matrix::toSdk(UaVariant& uaVariant)
    {
        UaInt32Array uaDimensions;
        uaDimensions.resize(dimensions.size());
        for (std::size_t i = 0; i < dimensions.size(); i++)
            uaDimensions[i] = dimensions[i];

        UaVariant uaElement;

        switch (uaVariant_.type())
        {
            case OpcUaType_Null:
                uaVariant_.clear();
                break;
                MATRIX_TOSDK_CASE(Boolean, Bool, OpcUa_UInt32, length)
                MATRIX_TOSDK_CASE(SByte, SByte, OpcUa_UInt32, length)
                MATRIX_TOSDK_CASE(UInt16, UInt16, OpcUa_UInt32, length)
                MATRIX_TOSDK_CASE(Int16, Int16, OpcUa_UInt32, length)
                MATRIX_TOSDK_CASE(UInt32, UInt32, OpcUa_UInt32, length)
                MATRIX_TOSDK_CASE(Int32, Int32, OpcUa_UInt32, length)
                MATRIX_TOSDK_CASE(UInt64, UInt64, OpcUa_UInt32, length)
                MATRIX_TOSDK_CASE(Int64, Int64, OpcUa_UInt32, length)
                MATRIX_TOSDK_CASE(Float, Float, OpcUa_UInt32, length)
                MATRIX_TOSDK_CASE(Double, Double, OpcUa_UInt32, length)
                MATRIX_TOSDK_CASE2(DateTime, DateTime, UaDateTime, OpcUa_UInt32, length)
                MATRIX_TOSDK_CASE2(Guid, Guid, UaGuid, OpcUa_UInt32, length)
                MATRIX_TOSDK_CASE2(NodeId, NodeId, UaNodeId, OpcUa_UInt32, length)
                MATRIX_TOSDK_CASE2(ExpandedNodeId, ExpandedNodeId, UaExpandedNodeId, OpcUa_UInt32, length)
                MATRIX_TOSDK_CASE2(QualifiedName, QualifiedName, UaQualifiedName, OpcUa_UInt32, length)
                MATRIX_TOSDK_CASE2(LocalizedText, LocalizedText, UaLocalizedText, OpcUa_UInt32, length)
                case OpcUaType_Byte:
                {
                    UaByteArray uaElements;
                    uaElements.resize(elements.size());
                    int j = 0;
                    for (std::size_t i = 0; i < elements.size(); i++)
                    {
                        elements[i].toSdk(uaElement);
                        OpcUa_Byte b;
                        uaElement.toByte(b);
                        uaElements[j] = b;
                        j++;
                    }
                    uaVariant_.setByteMatrix(uaElements, uaDimensions);
                    break;
                }
                case OpcUaType_String:
                {
                    UaStringArray uaElements;
                    uaElements.resize(elements.size());
                    for (std::size_t i = 0; i < elements.size(); i++)
                    {
                        elements[i].toSdk(uaElement);
                        UaString s;
                        s = uaElement.toString();
                        s.copyTo(&uaElements[i]);
                    }
                    uaVariant_.setStringMatrix(uaElements, uaDimensions);
                    break;
                }
                default:
                    break;
        }
        uaVariant = uaVariant_;
    }


    // Calculate an element number
    // =============================================================================================
    int32_t Matrix::getElementNumber(std::vector<int32_t> dimensionNumbers) const
    {
        if (dimensionNumbers.size() != dimensions.size())
            return -1;

        if (dimensions.size() == 0)
            return -1;

        int32_t ret = 0;
        int32_t multiplicator = 1;
        for (std::size_t dim = 0; dim < dimensions.size(); dim++)
        {
            std::size_t i = dimensions.size() - 1 - dim;

            if (dimensionNumbers[i] >= dimensions[i])
                return -1;

            ret += multiplicator * dimensionNumbers[i];
            multiplicator *= dimensions[i];
        }

        return ret;
    }

}
