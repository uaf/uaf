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
 
%module __unittesthelper__
%{
#define SWIG_FILE_WITH_INIT
#include "uaf/util/opcuatypes.h"
#include "uaf/util/variant.h"
#include "uaf/util/nodeid.h"
#include "uaf/util/expandednodeid.h"
#include "uaf/util/localizedtext.h"
#include "uaf/util/extensionobject.h"
#include <stdio.h>
%}

// import the necessary headers
%import "uaf/util/util.h"
%import "uaf/util/opcuatypes.h"
%import "uaf/util/nodeid.h"
%import "uaf/util/expandednodeid.h"
%import "uaf/util/localizedtext.h"
%import "uaf/util/qualifiedname.h"
%import "uaf/util/extensionobject.h"


// we'll test the python typemaps, so include them here
%include "pyuaf/util/util_variant_python.i"


// add the C++ UnitTestHelper class
%inline %{


    class UnitTestHelper
    {
    public:
        
        uint8_t* someBytes;
        
        uaf::NodeId someNodeId0;
        uaf::NodeId someNodeId1;
        uaf::NodeId someNodeId2;
        uaf::ExpandedNodeId someExpandedNodeId0;
        uaf::ExpandedNodeId someExpandedNodeId1;
        uaf::ExpandedNodeId someExpandedNodeId2;
        uaf::QualifiedName someQualifiedName0;
        uaf::QualifiedName someQualifiedName1;
        uaf::QualifiedName someQualifiedName2;
        uaf::LocalizedText someLocalizedText;
        uaf::DateTime someDateTime;
        uaf::ExtensionObject someExtensionObject;
        
        UnitTestHelper() 
        {
            someBytes = new uint8_t[3];
            someBytes[0] = 1;
            someBytes[1] = 2;
            someBytes[2] = 3;
            
            // create a NodeId but don't include a NameSpaceURI because the OPC UA NodeId type
            // only contains a NameSpaceIndex (in contrast to the UAF NodeId, which can contain 
            // both)
            someNodeId0 = uaf::NodeId("SomeIdentifier", 42);
            someNodeId1 = uaf::NodeId("SomeIdentifier", "nsUri");
            someNodeId2 = uaf::NodeId("SomeIdentifier", "nsUri", 42);
            someExpandedNodeId0 = uaf::ExpandedNodeId("SomeIdentifier", 42, 21);
            someExpandedNodeId1 = uaf::ExpandedNodeId("SomeIdentifier", "nsUri", 21);
            someExpandedNodeId2 = uaf::ExpandedNodeId("SomeIdentifier", "nsUri", "svrUri");
            someQualifiedName0 = uaf::QualifiedName("SomeName", 42);
            someQualifiedName1 = uaf::QualifiedName("SomeName", "nsUri");
            someQualifiedName2 = uaf::QualifiedName("SomeName", "nsUri", 42);
            someLocalizedText = uaf::LocalizedText("en", "SomeText");
            someDateTime = uaf::DateTime::fromString("2013-05-21T12:34:56.789Z");
        }

        virtual ~UnitTestHelper()
        {
            delete[] someBytes;
        }
        
        
        uaf::Variant testVariantTypemap_out(uaf::opcuatypes::OpcUaType type, bool array=false)
        {
            // declare the variant to return
            uaf::Variant v;
    
            // for each type, create an example variant
            if (array)
            {
                switch (type)
                {
                    case uaf::opcuatypes::Boolean:
                    { 
                        std::vector<bool> array;
                        array.push_back(true);
                        array.push_back(false);
                        array.push_back(true);
                        v.setBooleanArray(array);
                        break;
                    }
                    case uaf::opcuatypes::Byte:
                    { 
                        std::vector<uint8_t> array;
                        array.push_back(1);
                        array.push_back(2);
                        array.push_back(3);
                        v.setByteArray(array);
                        break; 
                    }
                    case uaf::opcuatypes::SByte:
                    { 
                        std::vector<int8_t> array;
                        array.push_back(-1);
                        array.push_back(2);
                        array.push_back(-3);
                        v.setSByteArray(array);
                        break; 
                    }
                    case uaf::opcuatypes::UInt16:
                    { 
                        std::vector<uint16_t> array;
                        array.push_back(1);
                        array.push_back(2);
                        array.push_back(3);
                        v.setUInt16Array(array);
                        break; 
                    }
                    case uaf::opcuatypes::Int16:
                    {
                        std::vector<int16_t> array;
                        array.push_back(-1);
                        array.push_back(2);
                        array.push_back(-3);
                        v.setInt16Array(array);
                        break; 
                    }
                    case uaf::opcuatypes::UInt32:
                    {
                        std::vector<uint32_t> array;
                        array.push_back(1);
                        array.push_back(2);
                        array.push_back(3);
                        v.setUInt32Array(array);
                        break;
                    }
                    case uaf::opcuatypes::Int32:
                    {
                        std::vector<int32_t> array;
                        array.push_back(-1);
                        array.push_back(2);
                        array.push_back(-3);
                        v.setInt32Array(array);
                        break;
                    }
                    case uaf::opcuatypes::UInt64:
                    {
                        std::vector<uint64_t> array;
                        array.push_back(1);
                        array.push_back(2);
                        array.push_back(3);
                        v.setUInt64Array(array);
                        break;
                    }
                    case uaf::opcuatypes::Int64:
                    {
                        std::vector<int64_t> array;
                        array.push_back(-1);
                        array.push_back(2);
                        array.push_back(-3);
                        v.setInt64Array(array);
                        break;
                    }
                    case uaf::opcuatypes::Float:
                    {
                        std::vector<float> array;
                        array.push_back(-3.14);
                        array.push_back(3.14);
                        array.push_back(-3.14);
                        v.setFloatArray(array);
                        break;
                    }
                    case uaf::opcuatypes::Double:
                    {
                        std::vector<double> array;
                        array.push_back(-3.14);
                        array.push_back(3.14);
                        array.push_back(-3.14);
                        v.setDoubleArray(array);
                        break;
                    }
                    case uaf::opcuatypes::String:
                    {
                        std::vector<std::string> array;
                        array.push_back(std::string("test1"));
                        array.push_back(std::string("test2"));
                        array.push_back(std::string("test3"));
                        v.setStringArray(array);
                        break;
                    }
                    case uaf::opcuatypes::NodeId:
                    {
                        std::vector<uaf::NodeId> array;
                        array.push_back(someNodeId0);
                        array.push_back(someNodeId1);
                        array.push_back(someNodeId2);
                        v.setNodeIdArray(array);
                        break;
                    }
                    case uaf::opcuatypes::ExpandedNodeId:
                    {
                        std::vector<uaf::ExpandedNodeId> array;
                        array.push_back(someExpandedNodeId0);
                        array.push_back(someExpandedNodeId1);
                        array.push_back(someExpandedNodeId2);
                        v.setExpandedNodeIdArray(array);
                        break;
                    }
                    case uaf::opcuatypes::LocalizedText:
                    {
                        std::vector<uaf::LocalizedText> array;
                        array.push_back(someLocalizedText);
                        array.push_back(someLocalizedText);
                        array.push_back(someLocalizedText);
                        v.setLocalizedTextArray(array);
                        break;
                    }
                    case uaf::opcuatypes::QualifiedName:
                    {
                        std::vector<uaf::QualifiedName> array;
                        array.push_back(someQualifiedName0);
                        array.push_back(someQualifiedName1);
                        array.push_back(someQualifiedName2);
                        v.setQualifiedNameArray(array);
                        break;
                    }
                    case uaf::opcuatypes::DateTime:
                    {
                        std::vector<uaf::DateTime> array;
                        array.push_back(someDateTime);
                        array.push_back(someDateTime);
                        array.push_back(someDateTime);
                        v.setDateTimeArray(array);
                        break;
                    }
                    case uaf::opcuatypes::ExtensionObject:
                    {
                        std::vector<uaf::ExtensionObject> array;
                        array.push_back(someExtensionObject);
                        array.push_back(someExtensionObject);
                        array.push_back(someExtensionObject);
                        v.setExtensionObjectArray(array);
                        break;
                    }
                    default:
                    {
                        v.clear();
                        break;
                    }
                }
            }
            else
            {
                switch (type)
                {
                    case uaf::opcuatypes::Boolean:         { v.setBoolean(true);                        break; }
                    case uaf::opcuatypes::Byte:            { v.setByte(3);                              break; }
                    case uaf::opcuatypes::SByte:           { v.setSByte(-3);                            break; }
                    case uaf::opcuatypes::UInt16:          { v.setUInt16(3);                            break; }
                    case uaf::opcuatypes::Int16:           { v.setInt16(-3);                            break; }
                    case uaf::opcuatypes::UInt32:          { v.setUInt32(3);                            break; }
                    case uaf::opcuatypes::Int32:           { v.setInt32(-3);                            break; }
                    case uaf::opcuatypes::UInt64:          { v.setUInt64(3);                            break; }
                    case uaf::opcuatypes::Int64:           { v.setInt64(-3);                            break; }
                    case uaf::opcuatypes::Float:           { v.setFloat(3.14);                          break; }
                    case uaf::opcuatypes::Double:          { v.setDouble(3.14);                         break; }
                    case uaf::opcuatypes::String:          { v.setString("test \xc2\xb0");              break; } // \u00B0 only works for GCC
                    case uaf::opcuatypes::ByteString:      { v.setByteString(someBytes, 3);             break; }
                    case uaf::opcuatypes::NodeId:          { v.setNodeId(someNodeId2);                  break; }
                    case uaf::opcuatypes::ExpandedNodeId:  { v.setExpandedNodeId(someExpandedNodeId2);  break; }
                    case uaf::opcuatypes::LocalizedText:   { v.setLocalizedText(someLocalizedText);     break; }
                    case uaf::opcuatypes::QualifiedName:   { v.setQualifiedName(someQualifiedName2);    break; }
                    case uaf::opcuatypes::DateTime:        { v.setDateTime(someDateTime);               break; }
                    case uaf::opcuatypes::ExtensionObject: { v.setExtensionObject(someExtensionObject); break; }
                    default:                               { v.clear();                                 break; }
                }
            }
    
            return v;
        }
        
        uaf::Variant testVariantTypemap_in(const uaf::Variant& v)
        {
            return uaf::Variant(v);
        }
    };
%}
