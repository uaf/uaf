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
 
%module variant_python
%{
#define SWIG_FILE_WITH_INIT
#include "uaf/util/variant.h"
#include "uaf/util/primitives.h"
#include "uaf/util/nodeid.h"
#include "uaf/util/expandednodeid.h"
#include "uaf/util/localizedtext.h"
#include "pyuaf/typemaps/util_variant_python_typemap.h"
%}


// include common definitions
%include "../pyuaf.i"


// import the MACROs that contain the type conversions
%import "../typemaps/util_variant_python_typemap.h"


%typemap(in, precedence=3000) uaf::Variant 
{
    PYOBJECT_TO_UAF_VARIANT($input, $1)
}

%typemap(typecheck, precedence=3001) const uaf::Variant&
{
    VARIANT_CHECK($input, $1)
}



%typemap(in) const uaf::Variant& (uaf::Variant temp) 
{
    PYOBJECT_TO_UAF_VARIANT($input, temp)
    $1 = &temp;
}

%typemap(out) uaf::Variant
{ 
    UAF_VARIANT_TO_PYOBJECT($1, $result); 
}


%typemap(out) const uaf::Variant& 
{
    UAF_VARIANT_TO_PYOBJECT((*$1), $result);
}





