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

#ifndef UTIL_BYTESTRING_PYTHON_TYPEMAP_H_
#define UTIL_BYTESTRING_PYTHON_TYPEMAP_H_
//WIGTYPE_p_uaf__ByteString,         \

#define BYTESTRING_CHECK(INPUT, RESULT) RESULT = (PyByteArray_Check(INPUT) ? 1 : 0);


#define PYOBJECT_TO_UAF_BYTESTRING(PYOBJECT, BYTESTRING)                                           \
    if (PyByteArray_Check(PYOBJECT))                                                               \
    {                                                                                              \
        char* data = PyByteArray_AsString(PYOBJECT);                                               \
        Py_ssize_t length = PyByteArray_Size(PYOBJECT);                                            \
        BYTESTRING = uaf::ByteString(length, (uint8_t*)data);                                      \
    }                                                                                              \
    else                                                                                           \
    {                                                                                              \
        PyErr_SetString(PyExc_TypeError, "Not a byte array!");                                     \
        return NULL;                                                                               \
    }


#define UAF_BYTESTRING_TO_PYOBJECT(BYTESTRING, PYOBJECT)                                           \
    Py_ssize_t size = (BYTESTRING.length() > 0 ? BYTESTRING.length() : 0);                         \
    PYOBJECT = PyByteArray_FromStringAndSize((char*) BYTESTRING.data(), size);


#endif /* UTIL_BYTESTRING_PYTHON_TYPEMAP_H_ */
