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

%module __init__
%{
#define SWIG_FILE_WITH_INIT
#include "uaf/util/util.h"
#include "uaf/util/bytestring.h"
#include "uaf/util/guid.h"
#include "uaf/util/datetime.h"
#include "uaf/util/handles.h"
#include "uaf/util/localizedtext.h"
#include "uaf/util/applicationdescription.h"
#include "uaf/util/datachangefilter.h"
#include "uaf/util/datavalue.h"
#include "uaf/util/endpointdescription.h"
#include "uaf/util/eventfilter.h"
#include "uaf/util/logmessage.h"
#include "uaf/util/logginginterface.h"
#include "uaf/util/usertokenpolicy.h"
#include "uaf/util/mask.h"
#include "uaf/util/modificationinfo.h"
#include "uaf/util/status.h"
#include "uaf/util/serverarray.h"
#include "uaf/util/simpleattributeoperand.h"
#include "uaf/util/nodeididentifier.h"
#include "uaf/util/nodeid.h"
#include "uaf/util/expandednodeid.h"
#include "uaf/util/qualifiedname.h"
#include "uaf/util/relativepathelement.h"
#include "uaf/util/browsepath.h"
#include "uaf/util/address.h"
#include "uaf/util/variant.h"
#include "uaf/util/viewdescription.h"
#include "uaf/util/referencedescription.h"
%}


// include common definitions
%include "../pyuaf.i"

// include some extras
#if defined(SWIGPYTHON)
    %include "pyuaf/util/init_extras.py"
#endif


// add some built-in type vectors to the pyuaf.util module
%template(StringVector) std::vector<std::string>;
%template(UInt32Vector) std::vector<uint32_t>;


// include the initializeUaf() function
%include "uaf/util/util.h"

// include the handles
%include "uaf/util/handles.h"

// include the ByteString typemap
#if defined(SWIGPYTHON)
    %include "pyuaf/util/util_bytestring_python.i"
#endif

// create a Vector that holds these ByteStrings!
%template(ByteStringVector) std::vector<uaf::ByteString>;

// import the submodules
%import "pyuaf/util/util_loglevels.i" 
%import "pyuaf/util/util_applicationtypes.i" 
%import "pyuaf/util/util_attributeids.i" 
%import "pyuaf/util/util_constants.i" 
%import "pyuaf/util/util_usertokentypes.i" 
%import "pyuaf/util/util_nodeididentifiertypes.i" 
%import "pyuaf/util/util_statuscodes.i" 
%import "pyuaf/util/util_opcuatypes.i"
%import "pyuaf/util/util_opcuaidentifiers.i"
%import "pyuaf/util/util_opcuastatuscodes.i"
%import "pyuaf/util/util_primitives.i" 
%import "pyuaf/util/util_securitypolicies.i" 
%import "pyuaf/util/util_messagesecuritymodes.i" 
%import "pyuaf/util/util_monitoringmodes.i" 
%import "pyuaf/util/util_browsedirections.i" 
%import "pyuaf/util/util_nodeclasses.i" 
%import "pyuaf/util/util_timestampstoreturn.i" 


// before including any classes in a generic way, specify the "special treatments" of certain classes:
%rename(__and__) uaf::Mask::operator&&;
%rename(__dispatch_logMessageReceived__) uaf::LoggingInterface::logMessageReceived;
%ignore extractServerUri(const Address& object, std::string& serverUri);
%ignore uaf::Address::operator=;
%ignore operator>(const DateTime&, const DateTime&);
%ignore uaf::DateTime::DateTime(const FILETIME& t);
%ignore uaf::StatusDiagnostics::operator=;


// now include all classes in a generic way
UAF_WRAP_CLASS("uaf/util/stringifiable.h"          , uaf , Stringifiable           , COPY_NO,  TOSTRING_YES, COMP_NO,  pyuaf.util, VECTOR_NO)
UAF_WRAP_CLASS("uaf/util/localizedtext.h"          , uaf , LocalizedText           , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, VECTOR_NO)
UAF_WRAP_CLASS("uaf/util/applicationdescription.h" , uaf , ApplicationDescription  , COPY_YES, TOSTRING_YES, COMP_NO,  pyuaf.util, ApplicationDescriptionVector)
UAF_WRAP_CLASS("uaf/util/guid.h"                   , uaf , Guid                    , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, VECTOR_NO)
UAF_WRAP_CLASS("uaf/util/datetime.h"               , uaf , DateTime                , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, DateTimeVector)
UAF_WRAP_CLASS("uaf/util/mask.h"                   , uaf , Mask                    , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, VECTOR_NO)
UAF_WRAP_CLASS("uaf/util/modificationinfo.h"       , uaf , ModificationInfo        , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, ModificationInfoVector)
UAF_WRAP_CLASS("uaf/util/status.h"                 , uaf , Status                  , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, StatusVector)
UAF_WRAP_CLASS("uaf/util/logmessage.h"             , uaf , LogMessage              , COPY_YES, TOSTRING_YES, COMP_NO,  pyuaf.util, VECTOR_NO)
UAF_WRAP_CLASS("uaf/util/logginginterface.h"       , uaf , LoggingInterface        , COPY_NO,  TOSTRING_NO,  COMP_NO,  pyuaf.util, VECTOR_NO)
UAF_WRAP_CLASS("uaf/util/guid.h"                   , uaf , Guid                    , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, VECTOR_NO)
UAF_WRAP_CLASS("uaf/util/nodeididentifier.h"       , uaf , NodeIdIdentifier        , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, VECTOR_NO)
UAF_WRAP_CLASS("uaf/util/nodeid.h"                 , uaf , NodeId                  , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, VECTOR_NO)
UAF_WRAP_CLASS("uaf/util/expandednodeid.h"         , uaf , ExpandedNodeId          , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, ExpandedNodeIdVector)
UAF_WRAP_CLASS("uaf/util/qualifiedname.h"          , uaf , QualifiedName           , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, QualifiedNameVector)
UAF_WRAP_CLASS("uaf/util/relativepathelement.h"    , uaf , RelativePathElement     , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, RelativePath)
UAF_WRAP_CLASS("uaf/util/browsepath.h"             , uaf , BrowsePath              , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, VECTOR_NO)
UAF_WRAP_CLASS("uaf/util/serverarray.h"            , uaf , ServerArray             , COPY_YES, TOSTRING_YES, COMP_NO,  pyuaf.util, VECTOR_NO)
UAF_WRAP_CLASS("uaf/util/simpleattributeoperand.h" , uaf , SimpleAttributeOperand  , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, SimpleAttributeOperandVector)
UAF_WRAP_CLASS("uaf/util/datachangefilter.h"       , uaf , DataChangeFilter        , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, VECTOR_NO)
UAF_WRAP_CLASS("uaf/util/eventfilter.h"            , uaf , EventFilter             , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, VECTOR_NO)
UAF_WRAP_CLASS("uaf/util/address.h"                , uaf , Address                 , COPY_NO,  TOSTRING_YES, COMP_YES, pyuaf.util, AddressVector)
UAF_WRAP_CLASS("uaf/util/usertokenpolicy.h"        , uaf , UserTokenPolicy         , COPY_YES, TOSTRING_YES, COMP_NO,  pyuaf.util, UserTokenPolicyVector)
UAF_WRAP_CLASS("uaf/util/endpointdescription.h"    , uaf , EndpointDescription     , COPY_YES, TOSTRING_YES, COMP_NO,  pyuaf.util, EndpointDescriptionVector)
UAF_WRAP_CLASS("uaf/util/viewdescription.h"        , uaf , ViewDescription         , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, VECTOR_NO)
UAF_WRAP_CLASS("uaf/util/referencedescription.h"   , uaf , ReferenceDescription    , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, ReferenceDescriptionVector)
UAF_WRAP_CLASS("uaf/util/statusdiagnostics.h"      , uaf , StatusDiagnostics       , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, VECTOR_NO)


// also include the Variant typemap(s)
#if defined(SWIGPYTHON)
    %include "pyuaf/util/util_variant_python.i"
#endif

// create a Vector that holds these variants!
%template(VariantVector) std::vector<uaf::Variant>;

// import the UnitTestHelper in case of Python
#if defined(SWIGPYTHON)
    %import "pyuaf/util/util___unittesthelper__.i"
#endif

// now include the classes that make use of the Variant typemap
UAF_WRAP_CLASS("uaf/util/datavalue.h"              , uaf , DataValue               , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, DataValueVector)

