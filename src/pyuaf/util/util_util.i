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

%module util
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
#include "uaf/util/pkiidentity.h"
#include "uaf/util/expandednodeid.h"
#include "uaf/util/qualifiedname.h"
#include "uaf/util/relativepathelement.h"
#include "uaf/util/browsepath.h"
#include "uaf/util/address.h"
#include "uaf/util/variant.h"
#include "uaf/util/matrix.h"
#include "uaf/util/viewdescription.h"
#include "uaf/util/referencedescription.h"
#include "uaf/util/enumvalue.h"
#include "uaf/util/extensionobject.h"
#include "uaf/util/modelchangestructuredatatype.h"
#include "uaf/util/pkicertificateinfo.h"
#include "uaf/util/pkipublickey.h"
#include "uaf/util/pkiprivatekey.h"
#include "uaf/util/pkirsakeypair.h"
#include "uaf/util/pkicertificate.h"
#include "uaf/util/primitives.h"
#include "uaf/util/sdkstatus.h"
#include "uaf/util/structurefield.h"
#include "uaf/util/structuredefinition.h"
#include "uaf/util/genericstructurevalue.h"
#include "uaf/util/genericunionvalue.h"
#include "uaf/util/serveronnetwork.h"
%}

//#define SWIG_NO_EXPORT_ITERATOR_METHODS 1

// include common definitions
%include "../pyuaf.i"

// include some extras
#if defined(SWIGPYTHON)
    %include "pyuaf/util/init_extras.py"
#endif


// add some built-in type vectors to the pyuaf.util module
%template(StringVector) std::vector<std::string>;
%template(UInt32Vector) std::vector<uint32_t>;
%template(Int32Vector) std::vector<int32_t>;


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
%import "pyuaf/util/util_serverstates.i" 
%import "pyuaf/util/util_structurefielddatatypes.i" 


// before including any classes in a generic way, specify the "special treatments" of certain classes:
%rename(__and__) uaf::Mask::operator&&;
%rename(__dispatch_logMessageReceived__) uaf::LoggingInterface::logMessageReceived;
%ignore extractServerUri(const Address& object, std::string& serverUri);
%ignore operator>(const DateTime&, const DateTime&);
%ignore uaf::DateTime::DateTime(const FILETIME& t);

// The default SWIG output returned by uaf::Status::opcUaStatusCode() is a signed representation (Long) of an unsigned 32-bit integer.
// The returned value (a Long which can only be positive) does not correspond bit-to-bit to the original OPC UA status codes, e.g. as found in
// pyuaf.util.opcuastatuscodes (which may appear to be negative ints because Python interprets the unsigned value as a signed value).
// We therefore manually convert the output of the opcUaStatusCode() method, so that the result can be compared to pyuaf.util.opcuastatuscodes.
// (Note that the convert_uint32_to_int32() function is defined in src/pyuaf/util/init_extras.py)
%extend uaf::Status {
  %pythoncode {
    def test(self):
        if self.isBad():
            raise getattr(self, "raisedBy_%s" %self.statusCodeName())
  }
}

// now include all classes in a generic way
UAF_WRAP_CLASS("uaf/util/localizedtext.h"          , uaf , LocalizedText           , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, LocalizedTextVector)
UAF_WRAP_CLASS("uaf/util/applicationdescription.h" , uaf , ApplicationDescription  , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, ApplicationDescriptionVector)
UAF_WRAP_CLASS("uaf/util/guid.h"                   , uaf , Guid                    , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, GuidVector)
UAF_WRAP_CLASS("uaf/util/datetime.h"               , uaf , DateTime                , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, DateTimeVector)
UAF_WRAP_CLASS("uaf/util/mask.h"                   , uaf , Mask                    , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, VECTOR_NO)
UAF_WRAP_CLASS("uaf/util/modificationinfo.h"       , uaf , ModificationInfo        , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, ModificationInfoVector)
UAF_WRAP_CLASS("uaf/util/status.h"                 , uaf , Status                  , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, StatusVector)
UAF_WRAP_CLASS("uaf/util/logmessage.h"             , uaf , LogMessage              , COPY_YES, TOSTRING_YES, COMP_NO,  pyuaf.util, VECTOR_NO)
UAF_WRAP_CLASS("uaf/util/logginginterface.h"       , uaf , LoggingInterface        , COPY_NO,  TOSTRING_NO,  COMP_NO,  pyuaf.util, VECTOR_NO)
UAF_WRAP_CLASS("uaf/util/nodeididentifier.h"       , uaf , NodeIdIdentifier        , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, VECTOR_NO)
UAF_WRAP_CLASS("uaf/util/nodeid.h"                 , uaf , NodeId                  , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, NodeIdVector)
UAF_WRAP_CLASS("uaf/util/expandednodeid.h"         , uaf , ExpandedNodeId          , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, ExpandedNodeIdVector)
UAF_WRAP_CLASS("uaf/util/qualifiedname.h"          , uaf , QualifiedName           , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, QualifiedNameVector)
UAF_WRAP_CLASS("uaf/util/relativepathelement.h"    , uaf , RelativePathElement     , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, RelativePath)
UAF_WRAP_CLASS("uaf/util/browsepath.h"             , uaf , BrowsePath              , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, VECTOR_NO)
UAF_WRAP_CLASS("uaf/util/serverarray.h"            , uaf , ServerArray             , COPY_YES, TOSTRING_YES, COMP_NO,  pyuaf.util, VECTOR_NO)
UAF_WRAP_CLASS("uaf/util/simpleattributeoperand.h" , uaf , SimpleAttributeOperand  , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, SimpleAttributeOperandVector)
UAF_WRAP_CLASS("uaf/util/datachangefilter.h"       , uaf , DataChangeFilter        , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, VECTOR_NO)
UAF_WRAP_CLASS("uaf/util/eventfilter.h"            , uaf , EventFilter             , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, VECTOR_NO)
UAF_WRAP_CLASS("uaf/util/address.h"                , uaf , Address                 , COPY_NO,  TOSTRING_YES, COMP_YES, pyuaf.util, AddressVector)
UAF_WRAP_CLASS("uaf/util/usertokenpolicy.h"        , uaf , UserTokenPolicy         , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, UserTokenPolicyVector)
UAF_WRAP_CLASS("uaf/util/endpointdescription.h"    , uaf , EndpointDescription     , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, EndpointDescriptionVector)
UAF_WRAP_CLASS("uaf/util/viewdescription.h"        , uaf , ViewDescription         , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, VECTOR_NO)
UAF_WRAP_CLASS("uaf/util/referencedescription.h"   , uaf , ReferenceDescription    , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, ReferenceDescriptionVector)
UAF_WRAP_CLASS("uaf/util/pkiidentity.h"            , uaf , PkiIdentity             , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, VECTOR_NO)
UAF_WRAP_CLASS("uaf/util/enumvalue.h"              , uaf , EnumValue               , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, VECTOR_NO)
UAF_WRAP_CLASS("uaf/util/extensionobject.h"        , uaf , ExtensionObject         , COPY_YES, TOSTRING_YES, COMP_NO,  pyuaf.util, ExtensionObjectVector)
UAF_WRAP_CLASS("uaf/util/modelchangestructuredatatype.h", uaf , ModelChangeStructureDataType, COPY_YES, TOSTRING_YES, COMP_YES,  pyuaf.util, VECTOR_NO)
UAF_WRAP_CLASS("uaf/util/pkipublickey.h"           , uaf , PkiPublicKey            , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, VECTOR_NO)
UAF_WRAP_CLASS("uaf/util/pkiprivatekey.h"          , uaf , PkiPrivateKey           , COPY_YES, TOSTRING_NO,  COMP_NO,  pyuaf.util, VECTOR_NO)
UAF_WRAP_CLASS("uaf/util/pkicertificateinfo.h"     , uaf , PkiCertificateInfo      , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, VECTOR_NO)
UAF_WRAP_CLASS("uaf/util/pkirsakeypair.h"          , uaf , PkiRsaKeyPair           , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, VECTOR_NO)
UAF_WRAP_CLASS("uaf/util/pkicertificate.h"         , uaf , PkiCertificate          , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, VECTOR_NO)
UAF_WRAP_CLASS("uaf/util/sdkstatus.h"              , uaf , SdkStatus               , COPY_YES, TOSTRING_YES, COMP_NO,  pyuaf.util, VECTOR_NO)
UAF_WRAP_CLASS("uaf/util/structurefield.h"         , uaf , StructureField          , COPY_YES, TOSTRING_YES, COMP_NO,  pyuaf.util, VECTOR_NO)
UAF_WRAP_CLASS("uaf/util/structuredefinition.h"    , uaf , StructureDefinition     , COPY_YES, TOSTRING_YES, COMP_NO,  pyuaf.util, VECTOR_NO)
UAF_WRAP_CLASS("uaf/util/serveronnetwork.h"        , uaf , ServerOnNetwork         , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, ServerOnNetworkVector)


// also include the Variant typemap(s)
#if defined(SWIGPYTHON)
    %include "pyuaf/util/util_variant_python.i"
#endif


// SWIG iterators don't work well for our vectors (probably SWIG bug),
// so therefore we create our own iterators:
%pythoncode %{
class VectorIterator(object):
   
    def __init__(self, pointerToVector):
        self.pointerToVector = pointerToVector
        self.index = -1
    
    def next(self):
        self.index += 1
        if self.index < len(self.pointerToVector):
            return self.pointerToVector[self.index]
        else:
            raise StopIteration
%}

%rename(__cpp_iterator) std::vector<uaf::Variant>::iterator;
%rename(__cpp_insert) std::vector<uaf::Variant>::insert;

%extend std::vector<uaf::Variant> {
%pythoncode {
    def iterator(self):
        return VectorIterator(self)
    def insert(self, i, x):
        if isinstance(i, int): # "insert" is used as if the vector is a Python list
            _util.VariantVector___cpp_insert(self, self.begin() + i, x)
        else: # "insert" is used as if the vector is a native C++ container
            return _util.VariantVector___cpp_insert(self, i, x)
   }
}

// create a Vector that holds these variants!
%template(VariantVector) std::vector<uaf::Variant>;


// import the UnitTestHelper in case of Python
#if defined(SWIGPYTHON)
    %import "pyuaf/util/util___unittesthelper__.i"
#endif

// now include the classes that make use of the Variant typemap
UAF_WRAP_CLASS("uaf/util/datavalue.h"              , uaf , DataValue               , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.util, DataValueVector)
UAF_WRAP_CLASS("uaf/util/genericstructurevalue.h"  , uaf , GenericStructureValue   , COPY_YES, TOSTRING_YES, COMP_NO,  pyuaf.util, GenericStructureVector)
UAF_WRAP_CLASS("uaf/util/genericunionvalue.h"  	   , uaf , GenericUnionValue   	   , COPY_YES, TOSTRING_YES, COMP_NO,  pyuaf.util, GenericUnionVector)
UAF_WRAP_CLASS("uaf/util/matrix.h"                 , uaf , Matrix                  , COPY_YES, TOSTRING_YES, COMP_NO,  pyuaf.util, VECTOR_NO)

//UAF_WRAP_CLASS("uaf/util/variant.h"                 , uaf , Variant                  , COPY_YES, TOSTRING_YES, COMP_NO,  pyuaf.util, VECTOR_NO)
