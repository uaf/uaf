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
// SETUP_PRIMITIVE(TYPE, PYTHONTYPE)
// =================================================================================================
//
// Set-up a string primitive type from uaf::primitives.
//
//   - argument TYPE : the type of the class, e.g. String
//
// Note: in case of a ValueError, which occurs if args[0] contains a string, representing a float,
//  such as "123.0", we catch the ValueError, and try to cast to float first before casting to int.
//
%define SETUP_PRIMITIVE(TYPE, PYTHONTYPE)
    %feature("pythonprepend") uaf::primitives::TYPE::TYPE %{
        """
        Construct a primitive.
        """
        if len(args) == 1:
            try:
                args = (PYTHONTYPE(args[0]),)
            except ValueError as e:
                try:
                    args = (PYTHONTYPE(float(args[0])),)
                except:
                    raise e
            except:
                raise TypeError("'PYTHONTYPE' expected instead of %s instance" %type(args[0]))
        elif len(args) > 0:
            raise TypeError("Only one value can be provided")
    %}
    HANDLE_COMPARISON_OPERATORS(uaf::primitives, TYPE)
    HANDLE_TOSTRING(uaf::primitives, TYPE, pyuaf.util.primitives)

    %template(TYPE##Array) std::vector<uaf::primitives::TYPE>;
%enddef


// setup the primitives
SETUP_PRIMITIVE(Boolean    , bool)
SETUP_PRIMITIVE(SByte      , int)
SETUP_PRIMITIVE(Byte       , int)
SETUP_PRIMITIVE(Int16      , int)
SETUP_PRIMITIVE(UInt16     , int)
SETUP_PRIMITIVE(Int32      , int)
SETUP_PRIMITIVE(UInt32     , int)
// The long builtin type has been deprecated in Python3
SETUP_PRIMITIVE(Int64      , int)
SETUP_PRIMITIVE(UInt64     , int)
SETUP_PRIMITIVE(Float      , float)
SETUP_PRIMITIVE(Double     , float)
SETUP_PRIMITIVE(String     , str)
SETUP_PRIMITIVE(ByteString , bytearray)


%include "uaf/util/primitives.h"

