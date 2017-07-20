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
#include "uaf/util/matrix.h"
#include "uaf/util/primitives.h"
#include "uaf/util/nodeid.h"
#include "uaf/util/guid.h"
#include "uaf/util/expandednodeid.h"
#include "uaf/util/localizedtext.h"
#include "uaf/util/extensionobject.h"
#include "uaf/util/datetime.h"
#include "uaf/util/primitives.h"
#include "pyuaf/typemaps/util_variant_python_typemap.h"
%}
// include common definitions
%include "../pyuaf.i"


%types(uaf::primitives::Boolean *, 
       uaf::primitives::SByte *,
       uaf::primitives::Byte *, 
       uaf::primitives::UInt16 *,
       uaf::primitives::Int16 *,
       uaf::primitives::UInt32 *,
       uaf::primitives::Int32 *,
       uaf::primitives::UInt64 *,
       uaf::primitives::Int64 *, 
       uaf::primitives::Float *,
       uaf::primitives::Double *,
       uaf::primitives::String *,
       uaf::primitives::ByteString *,
       uaf::NodeId *,
       uaf::Guid *,
       uaf::ExpandedNodeId *,
       uaf::LocalizedText *,
       uaf::DateTime *,
       uaf::QualifiedName *,
       uaf::ExtensionObject *,
       uaf::Matrix *,
       std::vector<uaf::Variant> *);


// import the MACROs that contain the type conversions
%import "../typemaps/util_variant_python_typemap.h"


%typemap(in, precedence=3000) uaf::Variant 
{
	bool typemapOK = pyObjectToUafVariant($input, $1);
    if (!typemapOK)
    	return NULL;
}

%typemap(typecheck, precedence=3001) const uaf::Variant&
{
    checkPyObject($input, $1);
}

%typemap(in) const uaf::Variant& (uaf::Variant temp) 
{
    
	bool typemapOK = pyObjectToUafVariant($input, temp);
    $1 = &temp;
    if (!typemapOK)
    	return NULL;
}

%typemap(out) uaf::Variant
{
	bool typemapOK = uafVariantToPyObject($1, $result);
    if (!typemapOK)
    	return NULL;
}

%typemap(out) uaf::Variant *
{ 
	bool typemapOK = uafVariantToPyObject($1, $result);
    if (!typemapOK)
    	return NULL;
}

%typemap(out) const uaf::Variant& 
{
	bool typemapOK;
    typemapOK = uafVariantToPyObject((*$1), $result);
    if (!typemapOK)
    	return NULL;
}
