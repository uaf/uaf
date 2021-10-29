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

%module errors
%{
#define SWIG_FILE_WITH_INIT
#include "uaf/util/errors/uaferror.h"
#include "uaf/util/errors/connectionerrors.h"
#include "uaf/util/errors/invalidrequesterror.h"
#include "uaf/util/errors/configurationerrors.h"
#include "uaf/util/errors/discoveryerrors.h"
#include "uaf/util/errors/generalerrors.h"
#include "uaf/util/errors/resolutionerrors.h"
#include "uaf/util/errors/securityerrors.h"
#include "uaf/util/errors/serviceerrors.h"
#include "uaf/util/errors/subscriptionerrors.h"
#include "uaf/util/errors/unsupportederrors.h"
#include "uaf/util/errors/backwardscompatibilityerrors.h"
%}



// include common definitions
%include "../pyuaf.i"


// import the EXPORT macro and some numeric typedefs
%import "uaf/util/util.h"
%import "uaf/util/handles.h"


// also include the typemaps
#if defined(SWIGPYTHON)
    %include "pyuaf/util/util_bytestring_python.i"
    %include "pyuaf/util/util_variant_python.i"
#endif

// include the errors
// wrap the UafError and make sure it inherits from Exception
%exceptionclass UafError;
UAF_WRAP_CLASS("uaf/util/errors/uaferror.h", uaf , UafError, COPY_YES, TOSTRING_YES, COMP_NO, pyuaf.util, VECTOR_NO)

%include "uaf/util/errors/invalidrequesterror.h"
%include "uaf/util/errors/connectionerrors.h"
%include "uaf/util/errors/configurationerrors.h"
%include "uaf/util/errors/discoveryerrors.h"
%include "uaf/util/errors/generalerrors.h"
%include "uaf/util/errors/resolutionerrors.h"
%include "uaf/util/errors/securityerrors.h"
%include "uaf/util/errors/serviceerrors.h"
%include "uaf/util/errors/subscriptionerrors.h"
%include "uaf/util/errors/unsupportederrors.h"
%include "uaf/util/errors/backwardscompatibilityerrors.h"

%pythoncode %{ 
def evaluateArg(arg, argName, argType, allowedValues=[]):
    if type(arg) != argType:
        try:
            allowedValue = arg in allowedValues
        except:
            allowedValue = False
        if not allowedValue:
            raise TypeError("Argument '%s' must be of type %s.%s" %(argName, argType.__module__, argType.__name__))
%}
