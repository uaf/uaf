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

#ifndef UTIL_VARIANT_PYTHON_TYPEMAP_H_
#define UTIL_VARIANT_PYTHON_TYPEMAP_H_




#define UAFTYPE_CONDITION(IN, TYPE)   SWIG_ConvertPtr(IN, (void **) &ptr, SWIGTYPE_p_uaf__##TYPE,             SWIG_POINTER_EXCEPTION) == 0
#define PRIMITIVE_CONDITION(IN, TYPE) SWIG_ConvertPtr(IN, (void **) &ptr, SWIGTYPE_p_uaf__primitives__##TYPE, SWIG_POINTER_EXCEPTION) == 0

#define CONVERTIBLE_CONDITION(IN)               \
    PRIMITIVE_CONDITION(IN, Boolean)            \
    || PRIMITIVE_CONDITION(IN, SByte)           \
    || PRIMITIVE_CONDITION(IN, Byte)            \
    || PRIMITIVE_CONDITION(IN, UInt16)          \
    || PRIMITIVE_CONDITION(IN, Int16)           \
    || PRIMITIVE_CONDITION(IN, UInt32)          \
    || PRIMITIVE_CONDITION(IN, Int32)           \
    || PRIMITIVE_CONDITION(IN, UInt64)          \
    || PRIMITIVE_CONDITION(IN, Int64)           \
    || PRIMITIVE_CONDITION(IN, Float)           \
    || PRIMITIVE_CONDITION(IN, Double)          \
    || PRIMITIVE_CONDITION(IN, String)          \
    || PRIMITIVE_CONDITION(IN, ByteString)      \
    || UAFTYPE_CONDITION(IN, NodeId)            \
    || UAFTYPE_CONDITION(IN, Guid)              \
    || UAFTYPE_CONDITION(IN, ExpandedNodeId)    \
    || UAFTYPE_CONDITION(IN, LocalizedText)     \
    || UAFTYPE_CONDITION(IN, DateTime)          \
    || UAFTYPE_CONDITION(IN, QualifiedName)     \
    || UAFTYPE_CONDITION(IN, ExtensionObject)



#define VARIANT_CHECK(INPUT, RESULT)                                                               \
        if (PyBool_Check(INPUT))                                                                   \
            RESULT = 1;                                                                            \
        else if (PyString_Check(INPUT))                                                            \
            RESULT = 1;                                                                            \
        else if (PyUnicode_Check(INPUT))                                                           \
            RESULT = 1;                                                                            \
        else if (PyByteArray_Check(INPUT))                                                         \
            RESULT = 1;                                                                            \
        else if (PySequence_Check(INPUT))                                                          \
        {                                                                                          \
            bool allGood = true;                                                                   \
            Py_ssize_t length = PySequence_Size(INPUT);                                            \
            for (Py_ssize_t i = 0; i < length && allGood; i++)                                     \
            {                                                                                      \
                void *ptr;                                                                         \
                PyObject* currentObject = PySequence_GetItem(INPUT, i);                            \
                if (!(CONVERTIBLE_CONDITION(currentObject)))                                       \
                 {                                                                                 \
                    allGood = false;                                                               \
                    break;                                                                         \
                 }                                                                                 \
            }                                                                                      \
            if (allGood)                                                                           \
                RESULT = 1;                                                                        \
            else                                                                                   \
                RESULT = 0;                                                                        \
        }                                                                                          \
        else                                                                                       \
        {                                                                                          \
            void *ptr;                                                                             \
            if (CONVERTIBLE_CONDITION(INPUT))                                                      \
                RESULT = 1;                                                                        \
            else                                                                                   \
                RESULT = 0;                                                                        \
        }



#define CONVERT_PRIMITIVE(IN, TYPE, OBJECT)                 \
    uaf::primitives::TYPE* primitive;                       \
    SWIG_ConvertPtr(IN,                                     \
                    (void **) &primitive,                   \
                    $descriptor(uaf::primitives::TYPE *),   \
                    SWIG_POINTER_EXCEPTION);                \
    OBJECT.set##TYPE(primitive->value);



#define PYUAF_CONVERT_UAFTYPE(IN, TYPE, OBJECT)             \
    uaf::TYPE* uafObject;                                   \
    SWIG_ConvertPtr(IN,                                     \
                    (void **) &uafObject,                   \
                    $descriptor(uaf::TYPE *),               \
                    SWIG_POINTER_EXCEPTION);                \
    OBJECT.set##TYPE(*uafObject);



#define CONVERT_PRIMITIVE_ARRAY(IN, TYPE, CTYPE, LENGTH, OBJECT)                            \
    std::vector<CTYPE> array;                                                               \
    array.resize(LENGTH);                                                                   \
    for (Py_ssize_t i = 0; i < LENGTH; i++)                                                 \
    {                                                                                       \
        PyObject* currentPyObject = PySequence_GetItem(IN, i);                              \
        if (currentPyObject == 0)                                                           \
        {                                                                                   \
            PyErr_SetString(PyExc_TypeError, "Unsupported type!");                          \
            return NULL;                                                                    \
        }                                                                                   \
        else if (PRIMITIVE_CONDITION(currentPyObject, TYPE))                                \
        {                                                                                   \
            uaf::primitives::TYPE* primitive;                                               \
            SWIG_ConvertPtr(currentPyObject,                                                \
                            (void **) &primitive,                                           \
                            $descriptor(uaf::primitives::TYPE *),                           \
                            SWIG_POINTER_EXCEPTION);                                        \
            array[i] = primitive->value;                                                    \
        }                                                                                   \
        else                                                                                \
        {                                                                                   \
            PyErr_SetString(PyExc_TypeError, "Sequence contains inconsistent types!");      \
            return NULL;                                                                    \
        }                                                                                   \
    }                                                                                       \
    OBJECT.set##TYPE##Array(array);





#define PYUAF_CONVERT_UAFTYPE_ARRAY(IN, TYPE, LENGTH, OBJECT)                               \
    std::vector<uaf::TYPE> array;                                                           \
    array.resize(LENGTH);                                                                   \
    for (Py_ssize_t i = 0; i < LENGTH; i++)                                                 \
    {                                                                                       \
        PyObject* currentPyObject = PySequence_GetItem(IN, i);                              \
        if (currentPyObject == 0)                                                           \
        {                                                                                   \
            PyErr_SetString(PyExc_TypeError, "Unsupported type!");                          \
            return NULL;                                                                    \
        }                                                                                   \
        else if (UAFTYPE_CONDITION(currentPyObject, TYPE))                                  \
        {                                                                                   \
            uaf::TYPE* uafObject;                                                           \
            SWIG_ConvertPtr(currentPyObject,                                                \
                            (void **) &uafObject,                                           \
                            $descriptor(uaf::TYPE *),                                       \
                            SWIG_POINTER_EXCEPTION);                                        \
            array[i] = *uafObject;                                                          \
        }                                                                                   \
        else                                                                                \
        {                                                                                   \
            PyErr_SetString(PyExc_TypeError, "Sequence contains inconsistent types!");      \
            return NULL;                                                                    \
        }                                                                                   \
    }                                                                                       \
    OBJECT.set##TYPE##Array(array);



#define STRING_OR_UNICODE_CONDITION(INPUT) PyString_Check(INPUT) || PyUnicode_Check(INPUT)


#define CONVERT_STRING_ARRAY(IN, LENGTH, OBJECT)                                                   \
    std::vector<std::string> array;                                                                \
    array.resize(LENGTH);                                                                          \
    for (Py_ssize_t i = 0; i < LENGTH; i++)                                                        \
    {                                                                                              \
        PyObject* currentPyObject = PySequence_GetItem(IN, i);                                     \
        if (currentPyObject == 0)                                                                  \
        {                                                                                          \
            PyErr_SetString(PyExc_TypeError, "Unsupported type!");                                 \
            return NULL;                                                                           \
        }                                                                                          \
        else if (PyString_Check(currentPyObject))                                                  \
        {                                                                                          \
            array[i] = std::string(PyString_AsString(currentPyObject));                            \
        }                                                                                          \
        else if (PyUnicode_Check(currentPyObject))                                                 \
        {                                                                                          \
            PyObject* pyString = PyUnicode_AsUTF8String(currentPyObject);                          \
            if (pyString == 0) {                                                                   \
                PyErr_SetString(PyExc_TypeError,                                                   \
                                "Could not encode the given unicode string as UTF-8");             \
                return NULL; }                                                                     \
            array[i] = std::string(PyString_AsString(pyString));                                   \
        }                                                                                          \
        else                                                                                       \
        {                                                                                          \
            PyErr_SetString(PyExc_TypeError, "Sequence contains inconsistent types!");             \
            return NULL;                                                                           \
        }                                                                                          \
    }                                                                                              \
    OBJECT.setStringArray(array);



#define PYUAF_CONVERT_ARRAYOBJECT(FIRSTOBJECT, PYOBJECT, LENGTH, VARIANT)                           \
    if (FIRSTOBJECT == 0)                                                                           \
    {                                                                                               \
        PyErr_SetString(PyExc_TypeError, "Could not determine the type of the array!");             \
        return NULL;                                                                                \
    }                                                                                               \
    else if (PRIMITIVE_CONDITION(FIRSTOBJECT, Boolean))      { CONVERT_PRIMITIVE_ARRAY(PYOBJECT, Boolean,    bool,              length,   VARIANT) } \
    else if (PRIMITIVE_CONDITION(FIRSTOBJECT, SByte))        { CONVERT_PRIMITIVE_ARRAY(PYOBJECT, SByte,      int8_t,            length,   VARIANT) } \
    else if (PRIMITIVE_CONDITION(FIRSTOBJECT, Byte))         { CONVERT_PRIMITIVE_ARRAY(PYOBJECT, Byte,       uint8_t,           length,   VARIANT) } \
    else if (PRIMITIVE_CONDITION(FIRSTOBJECT, UInt16))       { CONVERT_PRIMITIVE_ARRAY(PYOBJECT, UInt16,     uint16_t,          length,   VARIANT) } \
    else if (PRIMITIVE_CONDITION(FIRSTOBJECT, Int16))        { CONVERT_PRIMITIVE_ARRAY(PYOBJECT, Int16,      int16_t,           length,   VARIANT) } \
    else if (PRIMITIVE_CONDITION(FIRSTOBJECT, UInt32))       { CONVERT_PRIMITIVE_ARRAY(PYOBJECT, UInt32,     uint32_t,          length,   VARIANT) } \
    else if (PRIMITIVE_CONDITION(FIRSTOBJECT, Int32))        { CONVERT_PRIMITIVE_ARRAY(PYOBJECT, Int32,      int32_t,           length,   VARIANT) } \
    else if (PRIMITIVE_CONDITION(FIRSTOBJECT, UInt64))       { CONVERT_PRIMITIVE_ARRAY(PYOBJECT, UInt64,     uint64_t,          length,   VARIANT) } \
    else if (PRIMITIVE_CONDITION(FIRSTOBJECT, Int64))        { CONVERT_PRIMITIVE_ARRAY(PYOBJECT, Int64,      int64_t,           length,   VARIANT) } \
    else if (PRIMITIVE_CONDITION(FIRSTOBJECT, Float))        { CONVERT_PRIMITIVE_ARRAY(PYOBJECT, Float,      float,             length,   VARIANT) } \
    else if (PRIMITIVE_CONDITION(FIRSTOBJECT, Double))       { CONVERT_PRIMITIVE_ARRAY(PYOBJECT, Double,     double,            length,   VARIANT) } \
    else if (PRIMITIVE_CONDITION(FIRSTOBJECT, String))       { CONVERT_PRIMITIVE_ARRAY(PYOBJECT, String,     std::string,       length,   VARIANT) } \
    else if (PRIMITIVE_CONDITION(FIRSTOBJECT, ByteString))   { CONVERT_PRIMITIVE_ARRAY(PYOBJECT, ByteString, uaf::ByteString,   length,   VARIANT) } \
    else if (UAFTYPE_CONDITION(FIRSTOBJECT, NodeId))         { PYUAF_CONVERT_UAFTYPE_ARRAY(PYOBJECT, NodeId,         length,   VARIANT) } \
    else if (UAFTYPE_CONDITION(FIRSTOBJECT, Guid))           { PYUAF_CONVERT_UAFTYPE_ARRAY(PYOBJECT, Guid,           length,   VARIANT) } \
    else if (UAFTYPE_CONDITION(FIRSTOBJECT, ExpandedNodeId)) { PYUAF_CONVERT_UAFTYPE_ARRAY(PYOBJECT, ExpandedNodeId, length,   VARIANT) } \
    else if (UAFTYPE_CONDITION(FIRSTOBJECT, LocalizedText))  { PYUAF_CONVERT_UAFTYPE_ARRAY(PYOBJECT, LocalizedText,  length,   VARIANT) } \
    else if (UAFTYPE_CONDITION(FIRSTOBJECT, QualifiedName))  { PYUAF_CONVERT_UAFTYPE_ARRAY(PYOBJECT, QualifiedName,  length,   VARIANT) } \
    else if (UAFTYPE_CONDITION(FIRSTOBJECT, DateTime))       { PYUAF_CONVERT_UAFTYPE_ARRAY(PYOBJECT, DateTime,       length,   VARIANT) } \
    else if (UAFTYPE_CONDITION(FIRSTOBJECT, ExtensionObject)){ PYUAF_CONVERT_UAFTYPE_ARRAY(PYOBJECT, ExtensionObject,length,   VARIANT) } \
    else if (STRING_OR_UNICODE_CONDITION(FIRSTOBJECT))       { CONVERT_STRING_ARRAY(PYOBJECT, length, VARIANT) } \
    else { PyErr_SetString(PyExc_TypeError, "Unsupported type!"); return NULL; }


#define CONVERT_OBJECT(PYOBJECT, VARIANT)                                                                          \
    if      (PRIMITIVE_CONDITION(PYOBJECT, Boolean))      { CONVERT_PRIMITIVE(PYOBJECT, Boolean,        VARIANT) } \
    else if (PRIMITIVE_CONDITION(PYOBJECT, SByte))        { CONVERT_PRIMITIVE(PYOBJECT, SByte,          VARIANT) } \
    else if (PRIMITIVE_CONDITION(PYOBJECT, Byte))         { CONVERT_PRIMITIVE(PYOBJECT, Byte,           VARIANT) } \
    else if (PRIMITIVE_CONDITION(PYOBJECT, UInt16))       { CONVERT_PRIMITIVE(PYOBJECT, UInt16,         VARIANT) } \
    else if (PRIMITIVE_CONDITION(PYOBJECT, Int16))        { CONVERT_PRIMITIVE(PYOBJECT, Int16,          VARIANT) } \
    else if (PRIMITIVE_CONDITION(PYOBJECT, UInt32))       { CONVERT_PRIMITIVE(PYOBJECT, UInt32,         VARIANT) } \
    else if (PRIMITIVE_CONDITION(PYOBJECT, Int32))        { CONVERT_PRIMITIVE(PYOBJECT, Int32,          VARIANT) } \
    else if (PRIMITIVE_CONDITION(PYOBJECT, UInt64))       { CONVERT_PRIMITIVE(PYOBJECT, UInt64,         VARIANT) } \
    else if (PRIMITIVE_CONDITION(PYOBJECT, Int64))        { CONVERT_PRIMITIVE(PYOBJECT, Int64,          VARIANT) } \
    else if (PRIMITIVE_CONDITION(PYOBJECT, Float))        { CONVERT_PRIMITIVE(PYOBJECT, Float,          VARIANT) } \
    else if (PRIMITIVE_CONDITION(PYOBJECT, Double))       { CONVERT_PRIMITIVE(PYOBJECT, Double,         VARIANT) } \
    else if (PRIMITIVE_CONDITION(PYOBJECT, String))       { CONVERT_PRIMITIVE(PYOBJECT, String,         VARIANT) } \
    else if (PRIMITIVE_CONDITION(PYOBJECT, ByteString))   { CONVERT_PRIMITIVE(PYOBJECT, ByteString,     VARIANT) } \
    else if (UAFTYPE_CONDITION(PYOBJECT, NodeId))         { PYUAF_CONVERT_UAFTYPE(PYOBJECT, NodeId,           VARIANT) } \
    else if (UAFTYPE_CONDITION(PYOBJECT, Guid))           { PYUAF_CONVERT_UAFTYPE(PYOBJECT, Guid,             VARIANT) } \
    else if (UAFTYPE_CONDITION(PYOBJECT, ExpandedNodeId)) { PYUAF_CONVERT_UAFTYPE(PYOBJECT, ExpandedNodeId,   VARIANT) } \
    else if (UAFTYPE_CONDITION(PYOBJECT, LocalizedText))  { PYUAF_CONVERT_UAFTYPE(PYOBJECT, LocalizedText,    VARIANT) } \
    else if (UAFTYPE_CONDITION(PYOBJECT, QualifiedName))  { PYUAF_CONVERT_UAFTYPE(PYOBJECT, QualifiedName,    VARIANT) } \
    else if (UAFTYPE_CONDITION(PYOBJECT, DateTime))       { PYUAF_CONVERT_UAFTYPE(PYOBJECT, DateTime,         VARIANT) } \
    else if (UAFTYPE_CONDITION(PYOBJECT, ExtensionObject)){ PYUAF_CONVERT_UAFTYPE(PYOBJECT, ExtensionObject,  VARIANT) } \
    else \
    { \
        PyErr_SetString(PyExc_TypeError, "Unsupported type!"); \
        return NULL; \
    }


#define PYOBJECT_TO_UAF_VARIANT(PYOBJECT, VARIANT)                                                 \
    if (PYOBJECT == Py_None)                                                                       \
    {    VARIANT.clear();    }                                                                     \
    else if (PyBool_Check(PYOBJECT))                                                               \
    {   VARIANT.setBoolean(PyInt_AsLong(PYOBJECT));    }                                           \
    else if (PyString_Check(PYOBJECT))                                                             \
    {                                                                                              \
        VARIANT.setString(PyString_AsString(PYOBJECT));                                            \
    }                                                                                              \
    else if (PyUnicode_Check(PYOBJECT))                                                            \
    {                                                                                              \
        PyObject* pyString = PyUnicode_AsUTF8String(PYOBJECT);                                     \
        if (pyString == 0) {                                                                       \
            PyErr_SetString(PyExc_TypeError, "Could not encode the given unicode string as UTF-8");\
            return NULL; }                                                                         \
        VARIANT.setString(PyString_AsString(pyString));                                            \
    }                                                                                              \
    else if (PyByteArray_Check(PYOBJECT))                                                          \
    {                                                                                              \
        char* data = PyByteArray_AsString(PYOBJECT);                                               \
        Py_ssize_t length = PyByteArray_Size(PYOBJECT);                                            \
        VARIANT.setByteString((uint8_t*)data, length);                                             \
    }                                                                                              \
    else if (PySequence_Check(PYOBJECT))                                                           \
    {                                                                                              \
        Py_ssize_t length = PySequence_Size(PYOBJECT);                                             \
        if (length > 0)                                                                            \
        {                                                                                          \
            void *ptr;                                                                             \
            PyObject* firstPyObject = PySequence_GetItem(PYOBJECT, 0);                             \
            PYUAF_CONVERT_ARRAYOBJECT(firstPyObject, PYOBJECT, length, VARIANT)                    \
        }                                                                                          \
        else                                                                                       \
        {                                                                                          \
            PyErr_SetString(PyExc_TypeError, "Could not determine the array type, empty array!");  \
            return NULL;                                                                           \
        }                                                                                          \
    }                                                                                              \
    else                                                                                           \
    {                                                                                              \
        void *ptr;                                                                                 \
        CONVERT_OBJECT(PYOBJECT, VARIANT)                                                          \
    }





#define CREATE_PRIMITIVE(TYPE, VARIANT, PYRESULT)                                                  \
    uaf::primitives::TYPE* primitive = new uaf::primitives::TYPE;                                  \
    VARIANT.to##TYPE(primitive->value);                                                            \
    PYRESULT = SWIG_NewPointerObj(primitive, $descriptor(uaf::primitives::TYPE *), SWIG_POINTER_OWN);


#define CREATE_UAFTYPE(TYPE, VARIANT, PYRESULT)                                                    \
    uaf::TYPE* uafObject = new uaf::TYPE;                                                          \
    VARIANT.to##TYPE(*uafObject);                                                                  \
    PYRESULT = SWIG_NewPointerObj(uafObject, $descriptor(uaf::TYPE *) , SWIG_POINTER_OWN);




#define CREATE_PRIMITIVE_ARRAY(TYPE, CTYPE, VARIANT, PYRESULT)                                  \
    std::vector<CTYPE> vec;                                                                     \
    VARIANT.to##TYPE##Array(vec);                                                               \
    PYRESULT = PyList_New(VARIANT.arraySize());                                                 \
    for (Py_ssize_t i = 0; i < VARIANT.arraySize(); i++)                                        \
    {                                                                                           \
        uaf::primitives::TYPE* primitive = new uaf::primitives::TYPE;                           \
        primitive->value = vec[i];                                                              \
        PyObject* newItem = SWIG_NewPointerObj(primitive,                                       \
                                               $descriptor(uaf::primitives::TYPE *),            \
                                               SWIG_POINTER_OWN);                               \
        PyList_SetItem(PYRESULT, i, newItem);                                                   \
    }


#define CREATE_UAFTYPE_ARRAY(TYPE, VARIANT, PYRESULT)                                           \
    std::vector<uaf::TYPE> vec;                                                                 \
    uaf::Status conversionStatus = VARIANT.to##TYPE##Array(vec);                                \
    if (conversionStatus.isNotGood())                                                           \
    {                                                                                           \
        PyErr_SetString(PyExc_TypeError, conversionStatus.toString().c_str());                  \
        return NULL;                                                                            \
    }                                                                                           \
    PYRESULT = PyList_New(VARIANT.arraySize());                                                 \
    for (Py_ssize_t i = 0; i < VARIANT.arraySize(); i++)                                        \
    {                                                                                           \
        uaf::TYPE* newObject = new uaf::TYPE(vec[i]);                                           \
        PyObject* newItem = SWIG_NewPointerObj(newObject,                                       \
                                               $descriptor(uaf::TYPE *),                        \
                                               SWIG_POINTER_OWN);                               \
        PyList_SetItem(PYRESULT, i, newItem);                                                   \
    }


#define CREATE_ARRAYOBJECT(VARIANT, PYOBJECT)  \
    if (VARIANT.type() == uaf::opcuatypes::Boolean)              { CREATE_PRIMITIVE_ARRAY(Boolean,    bool, VARIANT, PYOBJECT)     } \
    else if (VARIANT.type() == uaf::opcuatypes::SByte)           { CREATE_PRIMITIVE_ARRAY(SByte,      int8_t, VARIANT, PYOBJECT)   } \
    else if (VARIANT.type() == uaf::opcuatypes::Byte)            { CREATE_PRIMITIVE_ARRAY(Byte,       uint8_t, VARIANT, PYOBJECT)  } \
    else if (VARIANT.type() == uaf::opcuatypes::Int16)           { CREATE_PRIMITIVE_ARRAY(Int16,      int16_t, VARIANT, PYOBJECT)  } \
    else if (VARIANT.type() == uaf::opcuatypes::UInt16)          { CREATE_PRIMITIVE_ARRAY(UInt16,     uint16_t, VARIANT, PYOBJECT) } \
    else if (VARIANT.type() == uaf::opcuatypes::Int32)           { CREATE_PRIMITIVE_ARRAY(Int32,      int32_t, VARIANT, PYOBJECT)  } \
    else if (VARIANT.type() == uaf::opcuatypes::UInt32)          { CREATE_PRIMITIVE_ARRAY(UInt32,     uint32_t, VARIANT, PYOBJECT) } \
    else if (VARIANT.type() == uaf::opcuatypes::Int64)           { CREATE_PRIMITIVE_ARRAY(Int64,      int64_t, VARIANT, PYOBJECT)  } \
    else if (VARIANT.type() == uaf::opcuatypes::UInt64)          { CREATE_PRIMITIVE_ARRAY(UInt64,     uint64_t, VARIANT, PYOBJECT) } \
    else if (VARIANT.type() == uaf::opcuatypes::Float)           { CREATE_PRIMITIVE_ARRAY(Float,      float, VARIANT, PYOBJECT)    } \
    else if (VARIANT.type() == uaf::opcuatypes::Double)          { CREATE_PRIMITIVE_ARRAY(Double,     double, VARIANT, PYOBJECT)   } \
    else if (VARIANT.type() == uaf::opcuatypes::String)          { CREATE_PRIMITIVE_ARRAY(String,     std::string, VARIANT, PYOBJECT)   } \
    else if (VARIANT.type() == uaf::opcuatypes::ByteString)      { CREATE_PRIMITIVE_ARRAY(ByteString, uaf::ByteString, VARIANT, PYOBJECT)   } \
    else if (VARIANT.type() == uaf::opcuatypes::NodeId)          { CREATE_UAFTYPE_ARRAY(NodeId, VARIANT, PYOBJECT)         } \
    else if (VARIANT.type() == uaf::opcuatypes::Guid)            { CREATE_UAFTYPE_ARRAY(Guid, VARIANT, PYOBJECT)         } \
    else if (VARIANT.type() == uaf::opcuatypes::ExpandedNodeId)  { CREATE_UAFTYPE_ARRAY(ExpandedNodeId, VARIANT, PYOBJECT) } \
    else if (VARIANT.type() == uaf::opcuatypes::LocalizedText)   { CREATE_UAFTYPE_ARRAY(LocalizedText, VARIANT, PYOBJECT)  } \
    else if (VARIANT.type() == uaf::opcuatypes::QualifiedName)   { CREATE_UAFTYPE_ARRAY(QualifiedName, VARIANT, PYOBJECT)  } \
    else if (VARIANT.type() == uaf::opcuatypes::DateTime)        { CREATE_UAFTYPE_ARRAY(DateTime, VARIANT, PYOBJECT)       } \
    else if (VARIANT.type() == uaf::opcuatypes::ExtensionObject) { CREATE_UAFTYPE_ARRAY(ExtensionObject, VARIANT, PYOBJECT)} \
    else                                                                                           \
    {                                                                                              \
        PyErr_SetString(PyExc_TypeError, "Unsupported type!");                                     \
        return NULL;                                                                               \
    }



#define CREATE_OBJECT(VARIANT, PYOBJECT)  \
    if (VARIANT.type() == uaf::opcuatypes::Boolean)              { CREATE_PRIMITIVE(Boolean, VARIANT, PYOBJECT)      }  \
    else if (VARIANT.type() == uaf::opcuatypes::SByte)           { CREATE_PRIMITIVE(SByte, VARIANT, PYOBJECT)        }  \
    else if (VARIANT.type() == uaf::opcuatypes::Byte)            { CREATE_PRIMITIVE(Byte, VARIANT, PYOBJECT)         }  \
    else if (VARIANT.type() == uaf::opcuatypes::Int16)           { CREATE_PRIMITIVE(Int16, VARIANT, PYOBJECT)        }  \
    else if (VARIANT.type() == uaf::opcuatypes::UInt16)          { CREATE_PRIMITIVE(UInt16, VARIANT, PYOBJECT)       }  \
    else if (VARIANT.type() == uaf::opcuatypes::Int32)           { CREATE_PRIMITIVE(Int32, VARIANT, PYOBJECT)        }  \
    else if (VARIANT.type() == uaf::opcuatypes::UInt32)          { CREATE_PRIMITIVE(UInt32, VARIANT, PYOBJECT)       }  \
    else if (VARIANT.type() == uaf::opcuatypes::Int64)           { CREATE_PRIMITIVE(Int64, VARIANT, PYOBJECT)        }  \
    else if (VARIANT.type() == uaf::opcuatypes::UInt64)          { CREATE_PRIMITIVE(UInt64, VARIANT, PYOBJECT)       }  \
    else if (VARIANT.type() == uaf::opcuatypes::Float)           { CREATE_PRIMITIVE(Float, VARIANT, PYOBJECT)        }  \
    else if (VARIANT.type() == uaf::opcuatypes::Double)          { CREATE_PRIMITIVE(Double, VARIANT, PYOBJECT)       }  \
    else if (VARIANT.type() == uaf::opcuatypes::String)          { CREATE_PRIMITIVE(String, VARIANT, PYOBJECT)       }  \
    else if (VARIANT.type() == uaf::opcuatypes::ByteString)      { CREATE_PRIMITIVE(ByteString, VARIANT, PYOBJECT)   }  \
    else if (VARIANT.type() == uaf::opcuatypes::NodeId)          { CREATE_UAFTYPE(NodeId, VARIANT, PYOBJECT)         }  \
    else if (VARIANT.type() == uaf::opcuatypes::Guid)            { CREATE_UAFTYPE(Guid, VARIANT, PYOBJECT)           }  \
    else if (VARIANT.type() == uaf::opcuatypes::ExpandedNodeId)  { CREATE_UAFTYPE(ExpandedNodeId, VARIANT, PYOBJECT) }  \
    else if (VARIANT.type() == uaf::opcuatypes::LocalizedText)   { CREATE_UAFTYPE(LocalizedText, VARIANT, PYOBJECT)  }  \
    else if (VARIANT.type() == uaf::opcuatypes::QualifiedName)   { CREATE_UAFTYPE(QualifiedName, VARIANT, PYOBJECT)  }  \
    else if (VARIANT.type() == uaf::opcuatypes::DateTime)        { CREATE_UAFTYPE(DateTime, VARIANT, PYOBJECT)       }  \
    else if (VARIANT.type() == uaf::opcuatypes::ExtensionObject) { CREATE_UAFTYPE(ExtensionObject, VARIANT, PYOBJECT)}  \
    else                                                                                           \
    {                                                                                              \
        PyErr_SetString(PyExc_TypeError, "Unsupported type!");                                     \
        return NULL;                                                                               \
    }


#define UAF_VARIANT_TO_PYOBJECT(VARIANT, PYOBJECT)                                                 \
    if (VARIANT.isNull())                                                                          \
    {                                                                                              \
        Py_INCREF(Py_None);                                                                        \
        PYOBJECT = Py_None;                                                                        \
    }                                                                                              \
    else if (VARIANT.isArray())                                                                    \
    {                                                                                              \
        CREATE_ARRAYOBJECT(VARIANT, PYOBJECT)                                                      \
    }                                                                                              \
    else                                                                                           \
    {                                                                                              \
        CREATE_OBJECT(VARIANT, PYOBJECT)                                                           \
    }


#endif /* UTIL_VARIANT_PYTHON_TYPEMAP_H_ */
