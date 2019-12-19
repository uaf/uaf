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

#include "uaf/util/namespacearray.h"


namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;
    using std::vector;


    // Constructor
    // =============================================================================================
    NamespaceArray::NamespaceArray() {}


    // Destructor
    // =============================================================================================
    NamespaceArray::~NamespaceArray() {}


    // Read the contents of a data value as returned when a client reads the NamespaceArray NodeId.
    // =============================================================================================
    Status NamespaceArray::fromSdk(const OpcUa_DataValue& value)
    {
        Status ret;

        // check if the status of the value is good:
        if (OpcUa_IsGood(value.StatusCode))
        {
            OpcUa_StatusCode uaConversionStatusCode;

            // convert the value to a StringArray
            uaConversionStatusCode = UaVariant(value.Value).toStringArray(namespaceArray_);

            // if the conversion succeeded, fill the map with simplified URIs
            if (OpcUa_IsGood(uaConversionStatusCode))
            {
                for (uint16_t i=0; i<namespaceArray_.length(); i++)
                {
                    nameSpaceMap_[i] = NamespaceArray::getSimplifiedUri(
                            string(UaString(&namespaceArray_[i]).toUtf8()));
                }
            }
            else
            {
                ret = NamespaceArrayConversionError();
            }

        }
        // if the status of the value was not good, just update the return status
        else
        {
            ret = BadNamespaceArrayError();
        }

        return ret;
    }


    // Look up the NamespaceURI for a given NamespaceIndex
    // =============================================================================================
    bool NamespaceArray::findNamespaceUri(NameSpaceIndex namespaceIndex, string& namespaceUri) const
    {
        // find the NamespaceIndex
        NameSpaceMap::const_iterator iter = nameSpaceMap_.find(namespaceIndex);

        bool found = (iter != nameSpaceMap_.end());

        // if the NamespaceIndex was found, assign the URI
        if (found)
            namespaceUri = iter->second;

        return found;
    }


    // Look up the NamespaceIndex for a given NamespaceURI
    // =============================================================================================
    bool NamespaceArray::findNamespaceIndex(
            const string&   namespaceUri,
            NameSpaceIndex& namespaceIndex) const
    {
        // We need to do a "reverse" lookup, by iterating over the key:value pairs until we have
        // found the correct value.

        // get a simplified URI
        string simplifiedUri = NamespaceArray::getSimplifiedUri(namespaceUri);

        // iterate over the key:value pairs
        NameSpaceMap::const_iterator iter;
        for (iter = nameSpaceMap_.begin(); iter != nameSpaceMap_.end(); ++iter)
        {
            // if the NamespaceURI was found, assign the NamespaceIndex, update the status,
            // and return
            if (iter->second == simplifiedUri)
            {
                namespaceIndex = iter->first;

                // we found the URI, so we can return!
                return true;
            }
        }

        // we haven't returned yet, so the URI was not found...
        return false;
    }


    // Get a string representation of the NamespaceArray (one line per index:URI pair)
    // =============================================================================================
    string NamespaceArray::toString() const
    {
        stringstream ss;

        // iterate over the map to print each key:value pair
        NameSpaceMap::const_iterator iter;
        for (iter = nameSpaceMap_.begin(); iter != nameSpaceMap_.end(); ++iter)
        {
            ss << " " << iter->first << ": " << iter->second << "\n";
        }

        return ss.str();
    }


    // static function!
    // Create a simplified (plain) URI
    // =============================================================================================
    string NamespaceArray::getSimplifiedUri(const string& uri)
    {
        string ret(uri);

        if (ret.size() > 0)
        {
            // transform to lower case
            transform(ret.begin(), ret.end(), ret.begin(), toLower );
            // remove a trailing '/' character
            if (ret.substr(ret.length()-1, 1) == string("/"))
            {
                ret = ret.substr(0, ret.length()-1);
            }
        }
        return ret;
    }


    // Convert a uaf::Address to a OpcUa_NodeId
    // =============================================================================================
    Status NamespaceArray::fillOpcUaNodeId(
            const Address&  address,
            OpcUa_NodeId&   opcUaNodeId) const
    {
        if (address.isExpandedNodeId())
            return fillOpcUaNodeId(address.getExpandedNodeId().nodeId(), opcUaNodeId);
        else
            return InvalidAddressError();
    }


    // Convert a uaf::NodeId to a OpcUa_NodeId
    // =============================================================================================
    Status NamespaceArray::fillOpcUaNodeId(
            const NodeId& nodeId,
            OpcUa_NodeId& opcUaNodeId) const
    {
        Status ret;

        // we need to get a valid namespace index
        NameSpaceIndex nameSpaceIndex;

        // check if the browse name has a namespace URI for which we can find an index
        if (nodeId.hasNameSpaceUri())
        {

            if (findNamespaceIndex(nodeId.nameSpaceUri(), nameSpaceIndex))
                ret = statuscodes::Good;
            else
                ret = UnknownNamespaceUriError(
                        nodeId.nameSpaceUri(),
                        nameSpaceMap_,
                        toString(nameSpaceMap_));
        }
        else if (nodeId.hasNameSpaceIndex())
        {
            // OK we don't have a namespace URI but we do have a namespace index
            nameSpaceIndex = nodeId.nameSpaceIndex();
            ret = statuscodes::Good;
        }
        else
        {
            // we have no possible means to get the namespace index
            ret = NoNamespaceIndexOrUriGivenError();
        }


        // if the namespace index was found, update the OpcUa_NodeId
        if (ret.isGood())
        {
            UaNodeId uaNodeId;
            // update the NodeId identifier
            if (nodeId.identifier().type == nodeididentifiertypes::Identifier_Numeric)
            {
                uaNodeId.setNodeId(nodeId.identifier().idNumeric, nameSpaceIndex);
                uaNodeId.copyTo(&opcUaNodeId);
            }
            else if (nodeId.identifier().type == nodeididentifiertypes::Identifier_String)
            {
                uaNodeId.setNodeId(UaString(nodeId.identifier().idString.c_str()), nameSpaceIndex);
                uaNodeId.copyTo(&opcUaNodeId);
            }
            else if (nodeId.identifier().type == nodeididentifiertypes::Identifier_Guid)
            {
                UaGuid uaGuid;
                nodeId.identifier().idGuid.toSdk(uaGuid);
                uaNodeId.setNodeId(uaGuid, nameSpaceIndex);
                uaNodeId.copyTo(&opcUaNodeId);
            }
            else if (nodeId.identifier().type == nodeididentifiertypes::Identifier_Opaque)
            {
                UaByteString uaByteString;
                nodeId.identifier().idOpaque.toSdk(uaByteString);
                uaNodeId.setNodeId(uaByteString, nameSpaceIndex);
                uaNodeId.copyTo(&opcUaNodeId);
            }
            else
            {
                ret = UnsupportedNodeIdIdentifierTypeError();
            }
        }

        return ret;
    }


    // Convert a uaf::ExpandedNodeId to a OpcUa_ExpandedNodeId
    // =============================================================================================
    Status NamespaceArray::fillOpcUaExpandedNodeId(
            const ExpandedNodeId& expandedNodeId,
            OpcUa_ExpandedNodeId& opcUaExpandedNodeId) const
    {
        Status ret;

        // first copy all known information
        expandedNodeId.toSdk(&opcUaExpandedNodeId);

        // now create a OpcUa_NodeId and fill it
        OpcUa_NodeId opcUaNodeId;
        ret = fillOpcUaNodeId(expandedNodeId.nodeId(), opcUaNodeId);

        if (ret.isGood())
        {
            // now also copy the new NodeId contents
            UaNodeId uaNodeId(opcUaNodeId);
            uaNodeId.copyTo(&opcUaExpandedNodeId.NodeId);
        }

        return ret;
    }



    // Convert a uaf::QualifiedName to a OpcUa_QualifiedName
    // =============================================================================================
    Status NamespaceArray::fillOpcUaQualifiedName(
            const QualifiedName& qualifiedName,
            OpcUa_QualifiedName& opcUaQualifiedName) const
    {
        Status ret;

        // check if the browse name has a namespace URI for which we can find an index
        if (qualifiedName.hasNameSpaceUri())
        {
            // we need to get a valid namespace index
            NameSpaceIndex nameSpaceIndex;

            if (findNamespaceIndex(qualifiedName.nameSpaceUri(), nameSpaceIndex))
            {
                // copy the contents from the qualified name to the SDK object
                // (except the namespaceUri because that's not relevant for the SDK object anyway)
                QualifiedName(qualifiedName.name(), nameSpaceIndex).toSdk(&opcUaQualifiedName);
                ret = statuscodes::Good;
            }
            else
            {
                ret = UnknownNamespaceUriError();
            }
        }
        else if (qualifiedName.hasNameSpaceIndex())
        {
            // OK we don't have a namespace URI but we do have a namespace index
            qualifiedName.toSdk(&opcUaQualifiedName);
            ret = statuscodes::Good;
        }
        else
        {
            // we have no possible means to get the namespace index
            ret = NoNamespaceIndexOrUriGivenError();
        }

        return ret;
    }


    // Convert a uaf::RelativePathElement to a OpcUa_RelativePathElement
    // =============================================================================================
    Status NamespaceArray::fillOpcUaRelativePathElement(
            const RelativePathElement& element,
            OpcUa_RelativePathElement& uaElement) const
    {
        Status status;

        // update the target name
        status = fillOpcUaQualifiedName(element.targetName, uaElement.TargetName);

        // update the reference type (unless the target name updating failed)
        if (status.isGood())
            status = fillOpcUaNodeId(element.referenceType, uaElement.ReferenceTypeId);

        // update the other properties of the uaElement (unless something has failed already)
        if (status.isGood())
        {
            // also update the uaRelativePathElements
            if (element.includeSubtypes)
                uaElement.IncludeSubtypes = OpcUa_True;
            else
                uaElement.IncludeSubtypes = OpcUa_False;
            if (element.isInverse)
                uaElement.IsInverse = OpcUa_True;
            else
                uaElement.IsInverse = OpcUa_False;
        }

        return status;
    }


    // Fill out a NodeId
    // =============================================================================================
    Status NamespaceArray::fillNodeId(const OpcUa_NodeId& opcUaNodeId, NodeId& nodeId) const
    {
        Status ret;

        string namespaceUri;

        if (findNamespaceUri(opcUaNodeId.NamespaceIndex, namespaceUri))
            ret = nodeId.fromSdk(opcUaNodeId, namespaceUri);
        else
            ret = UnknownNamespaceIndexError(opcUaNodeId.NamespaceIndex);

        return ret;
    }


    // Fill out an ExpandedNodeId
    // =============================================================================================
    Status NamespaceArray::fillExpandedNodeId(
            const OpcUa_ExpandedNodeId& opcUaExpandedNodeId,
            ExpandedNodeId&             expandedNodeId) const
    {
        Status ret;

        string namespaceUri;

        // according to the OPC UA specs, if the opcUaExpandedNodeId contains a namespaceUri,
        // then the namespaceIndex should be ignored.

        // So, if a non-empty namespace URI is already given, then we use that one.
        // Else, we try to find the namespace URI that corresponds to the given namespace index.
        if (!UaString(&opcUaExpandedNodeId.NamespaceUri).isEmpty())
        {
            // bugfix: added the following line: also in this situation the attributes from the SDK need to be copied!
            expandedNodeId.fromSdk(opcUaExpandedNodeId);

            NodeId nodeId = expandedNodeId.nodeId();
            nodeId.setNameSpaceUri(string(UaString(&opcUaExpandedNodeId.NamespaceUri).toUtf8()));
            expandedNodeId.setNodeId(nodeId);
            ret.setGood();
        }
        else if (findNamespaceUri(opcUaExpandedNodeId.NodeId.NamespaceIndex, namespaceUri))
        {
            ret = expandedNodeId.fromSdk(opcUaExpandedNodeId, namespaceUri);
        }
        else
        {
            ret = EmptyServerUriAndUnknownNamespaceIndexError(
                    opcUaExpandedNodeId.NodeId.NamespaceIndex);
        }

        return ret;
    }


    // Fill out a QualifiedName
    // =============================================================================================
    Status NamespaceArray::fillQualifiedName(
            const OpcUa_QualifiedName&  opcUaQualfiedName,
            QualifiedName&              qualifiedName) const
    {
        Status ret;

        string namespaceUri;

        if (findNamespaceUri(opcUaQualfiedName.NamespaceIndex, namespaceUri))
        {
            qualifiedName.fromSdk(opcUaQualfiedName, namespaceUri);
            ret = statuscodes::Good;
        }
        else
        {
            ret = UnknownNamespaceIndexError(opcUaQualfiedName.NamespaceIndex);
        }

        return ret;
    }

    // Fill out an ExtensionObject
    // =============================================================================================
    Status NamespaceArray::fillExtensionObject(
            const OpcUa_ExtensionObject&  opcUaExtensionObject,
            ExtensionObject&              extensionObject) const
    {
        Status ret;

        UaExtensionObject uaExtensionObject(opcUaExtensionObject);

        OpcUa_NodeId opcUaNodeId;

        if (uaExtensionObject.dataTypeId().isNull())
        {
        	uaExtensionObject.dataTypeId(namespaceArray_).copyTo(&opcUaNodeId);
        }
        else
        {
        	uaExtensionObject.dataTypeId().copyTo(&opcUaNodeId);
        }

        ret = fillNodeId(opcUaNodeId, extensionObject.dataTypeId);

        if (ret.isGood())
        {
            uaExtensionObject.encodingTypeId().copyTo(&opcUaNodeId);
            ret = fillNodeId(opcUaNodeId, extensionObject.encodingTypeId);
        }

        return ret;
    }


#define FILL_OPCUA_VARIANT_NSURI(TYPE)                                                              \
        if (variant.isArray())                                                                      \
        {                                                                                           \
            vector<TYPE> vec;                                                                       \
            variant.to##TYPE##Array(vec);                                                           \
                                                                                                    \
            if (vec.size() == 0) ret = statuscodes::Good;                                           \
                                                                                                    \
            for (std::size_t i = 0; i < vec.size() && ret.isNotBad(); i++)                          \
            {                                                                                       \
                OpcUa_##TYPE opcUaObject;                                                           \
                vec[i].toSdk(&opcUaObject);                                                         \
                ret = fill##TYPE(opcUaObject, vec[i]);                                              \
            }                                                                                       \
                                                                                                    \
            if (ret.isGood()) variant.set##TYPE##Array(vec);                                        \
        }                                                                                           \
        else                                                                                        \
        {                                                                                           \
            TYPE value;                                                                             \
            variant.to##TYPE(value);                                                                \
                                                                                                    \
            OpcUa_##TYPE opcUaObject;                                                               \
            value.toSdk(&opcUaObject);                                                              \
            ret = fill##TYPE(opcUaObject, value);                                                   \
                                                                                                    \
            if (ret.isGood()) variant.set##TYPE(value);                                             \
        }

    // Fill out a Variant
    // =============================================================================================
    Status NamespaceArray::fillVariant(Variant& variant) const
    {
        Status ret;

        // only types with a namespace URI/index need to be filled:

        if (variant.type() == uaf::opcuatypes::NodeId)
        {
            FILL_OPCUA_VARIANT_NSURI(NodeId)
        }
        else if (variant.type() == uaf::opcuatypes::ExpandedNodeId)
        {
            FILL_OPCUA_VARIANT_NSURI(ExpandedNodeId)
        }
        else if (variant.type() == uaf::opcuatypes::QualifiedName)
        {
            FILL_OPCUA_VARIANT_NSURI(QualifiedName)
        }
        else if (variant.type() == uaf::opcuatypes::ExtensionObject)
        {
            FILL_OPCUA_VARIANT_NSURI(ExtensionObject)
        }
        else
        {
            ret = statuscodes::Good;
        }

        return ret;
    }


    // static function!
    // Create a simplified (plain) URI
    // =============================================================================================
    string NamespaceArray::toString(const NameSpaceMap& map)
    {
        stringstream ss;

        for (NameSpaceMap::const_iterator it = map.begin(); it != map.end(); ++it)
        {
            if (it != map.begin())
                ss << std::endl;

            ss << it->first << " : " << it->second;
        }

        return ss.str();
    }



}





