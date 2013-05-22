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
 
%module bytestring_python
%{
#define SWIG_FILE_WITH_INIT
#include "uaf/util/bytestring.h"
#include "pyuaf/typemaps/util_bytestring_python_typemap.h"
%}


// include common definitions
%include "../pyuaf.i"


// import the MACROs that contain the type conversions
%import "../typemaps/util_bytestring_python_typemap.h"



%typemap(typecheck, precedence=2000) uaf::ByteString
{
    BYTESTRING_CHECK($input, $1)
}

%typemap(typecheck, precedence=2001) const uaf::ByteString&
{
    BYTESTRING_CHECK($input, $1)
}



%typemap(in) uaf::ByteString 
{
    PYOBJECT_TO_UAF_BYTESTRING($input, $1)
}



%typemap(in) const uaf::ByteString& (uaf::ByteString temp) 
{
    PYOBJECT_TO_UAF_BYTESTRING($input, temp)
    $1 = &temp;
}

%typemap(out) uaf::ByteString
{ 
    UAF_BYTESTRING_TO_PYOBJECT($1, $result); 
}


%typemap(out) const uaf::ByteString& 
{
    UAF_BYTESTRING_TO_PYOBJECT((*$1), $result);
}





