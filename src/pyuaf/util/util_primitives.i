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
 
%module primitives
%{
#define SWIG_FILE_WITH_INIT
#include "uaf/util/primitives.h"
#include "uaf/util/variant.h"
%}


// include common definitions
%include "../pyuaf.i"


// import the EXPORT macro
%import "uaf/util/util.h"
%import "uaf/util/opcuatypes.h"

// include the ByteString typemap
#if defined(SWIGPYTHON)
    %include "pyuaf/util/util_bytestring_python.i"
#endif


// =================================================================================================
// SETUP_INT_OR_LONG_PRIMITIVE(TYPE)
// =================================================================================================
// 
// Set-up an int or a long primitive type from uaf::primitives.
//
//   - argument TYPE : the type of the class, e.g. UInt32
//
%define SETUP_INT_OR_LONG_PRIMITIVE(TYPE)
    %feature("pythonprepend") uaf::primitives::TYPE::TYPE %{
        """
        Construct a primitive.
        """
        if len(args) == 1:
            if not isinstance(args[0], (bool, int, long)):
                raise TypeError("'int' or 'long' expected instead of %s instance" %type(args[0]))
        elif len(args) > 0:
            raise TypeError("Only one value can be provided")
    %}
    HANDLE_COMPARISON_OPERATORS(uaf::primitives, TYPE)
    HANDLE_TOSTRING(uaf::primitives, TYPE, pyuaf.util.primitives)
%enddef



// =================================================================================================
// SETUP_FLOAT_PRIMITIVE(TYPE)
// =================================================================================================
// 
// Set-up a float primitive type from uaf::primitives.
//
//   - argument TYPE : the type of the class, e.g. Double
//
%define SETUP_FLOAT_PRIMITIVE(TYPE)
    %feature("pythonprepend") uaf::primitives::TYPE::TYPE %{
        """
        Construct a primitive.
        """
        if len(args) == 1:
            if not isinstance(args[0], (bool, int, long, float)):
                raise TypeError("'float' expected instead of %s instance" %type(args[0]))
        elif len(args) > 0:
            raise TypeError("Only one value can be provided")
    %}
    HANDLE_COMPARISON_OPERATORS(uaf::primitives, TYPE)
    HANDLE_TOSTRING(uaf::primitives, TYPE, pyuaf.util.primitives)
%enddef



// =================================================================================================
// SETUP_OTHER_PRIMITIVE(TYPE, PYTHONTYPE)
// =================================================================================================
// 
// Set-up a string primitive type from uaf::primitives.
//
//   - argument TYPE : the type of the class, e.g. String
//
%define SETUP_OTHER_PRIMITIVE(TYPE, PYTHONTYPE)
    %feature("pythonprepend") uaf::primitives::TYPE::TYPE %{
        """
        Construct a primitive.
        """
        if len(args) == 1:
            if not isinstance(args[0], PYTHONTYPE):
                raise TypeError("'PYTHONTYPE' expected instead of %s instance" %type(args[0]))
        elif len(args) > 0:
            raise TypeError("Only one value can be provided")
    %}
    HANDLE_COMPARISON_OPERATORS(uaf::primitives, TYPE)
    HANDLE_TOSTRING(uaf::primitives, TYPE, pyuaf.util.primitives)
%enddef


// setup the primitives
SETUP_INT_OR_LONG_PRIMITIVE(Boolean)
SETUP_INT_OR_LONG_PRIMITIVE(SByte)
SETUP_INT_OR_LONG_PRIMITIVE(Byte)
SETUP_INT_OR_LONG_PRIMITIVE(Int16)
SETUP_INT_OR_LONG_PRIMITIVE(UInt16)
SETUP_INT_OR_LONG_PRIMITIVE(Int32)
SETUP_INT_OR_LONG_PRIMITIVE(UInt32)
SETUP_INT_OR_LONG_PRIMITIVE(Int64)
SETUP_INT_OR_LONG_PRIMITIVE(UInt64)
SETUP_FLOAT_PRIMITIVE(Float)
SETUP_FLOAT_PRIMITIVE(Double)
SETUP_OTHER_PRIMITIVE(String, str)
SETUP_OTHER_PRIMITIVE(ByteString, bytearray)


%include "uaf/util/primitives.h"

