# examples/pyuaf/util/how_to_define_addresses.py
"""
Example: how to define addresses
====================================================================================================

An OPC UA address space consists of Nodes, connected to each other by References. 

In the UAF, these Nodes can be addressed in two ways:
  1) by their ExpandedNodeId (or NodeId and a server URI)
  2) by a RelativePath relative to another address

1) An ExpandedNodeId is like an "absolute address" of a Node. It contains 
 - a server URI : information about the server that hosts the Node 
 - a NodeId     : information to locate the Node within the address space of that server.

2) A RelativePath on the other hand is like a "relative address" of a Node. Since
an address space of a server is a sort of "web" of Nodes and References, you 
can follow a path of references and nodes to locate a particular Node. This path contains:
 - a starting node: the node from which the relative path starts
 - a relative path: the path that leads to the node of our interest.
                    This path consists of one or more elements, 
                    and each element consists of a BrowseName and some other properties.

Either way, the node is defined within a certain namespace (a sort of "context") because they 
consist of elements that have an associated namespace URI. This URI (a Uniform Resource Identifier)
is in fact just a string that fully defines the namespace. For instance, the standard OPC UA
namespace has the namespace URI "http://opcfoundation.org/UA/". This means that all NodeIds 
and BrowseNames defined by the OPC UA standard are all qualified by this OPC UA namespace URI. 
If you define your own nodes, you should define them within your own namespace, which could have
the following URI for example: "http://www.myorganization.org/mymachines/".

While namespaces are defined by a URI, they can also be referred to by an integer: the namespace 
index. OPC UA servers expose a NamespaceArray that map these namespace indexes to URIs.
So all identifiers and qualified names exposed by a server can simply refer to a namespace index, 
and it is the responsibility of the client to read the NamespaceArray and use it to convert the 
namespace indexes into URIs. Fortunately, a UAF Client will do this conversion for you, behind the
scenes. Namespace indexes therefore do NOT suffice to qualify an identifier or a name, since they
depend on a mapping (the NamespaceArray), and this mapping depends on the server and may change
over time. One notable exception is namespace index 0 (zero). This index is reserved for the 
standard OPC UA namespace, so it ALWAYS (!) refers to namespace URI "http://opcfoundation.org/UA/".
""" 

import pyuaf
from pyuaf.client                   import Client
from pyuaf.client.settings          import ClientSettings
from pyuaf.util                     import Address, ExpandedNodeId, RelativePathElement, QualifiedName, LocalizedText
from pyuaf.util.opcuaidentifiers    import OpcUaId_RootFolder, OpcUaId_ObjectsFolder, OpcUaId_ObjectsFolder
from pyuaf.util.constants           import OPCUA_NAMESPACE_URI, OPCUA_NAMESPACE_ID

#========================================================#
#                     standard nodes                     #
#========================================================#

# First we define some standard OPC UA nodes. 
# Standard nodes have NodeIds that are fully defined by the OPC UA standard.
# For instance, the Root node that is present on all servers, has a
#   - namespace URI "http://opcfoundation.org/UA/" --> defined as pyuaf.util.constants.OPCUA_NAMESPACE_URI
#   - namespace index 0                            --> defined as pyuaf.util.constants.OPCUA_NAMESPACE_ID
#                                                      (note that index 0 is ALWAYS reserved for the OPC UA namespace!) 
#   - the numeric NodeId identifier 84             --> defined as pyuaf.util.opcuaidentifiers.OpcUaId_RootFolder
# 
# So here are all valid ways to define the Root node: 
Root_NodeId = NodeId(84, 0)
Root_NodeId = NodeId(OpcUaId_RootFolder, OPCUA_NAMESPACE_ID)                      # same as the previous, but with symbols
Root_NodeId = NodeId(OpcUaId_RootFolder, OPCUA_NAMESPACE_URI)                     # namespace URI instead of namespace index
Root_NodeId = NodeId(OpcUaId_RootFolder, OPCUA_NAMESPACE_URI, OPCUA_NAMESPACE_ID) # redundant namespace info, but valid

# NodeIds don't contain info about the server they are hosted by.
# If you specifically want to refer to a NodeId within a particular server, you need to
# use an ExpandedNodeId, which contains
#   - a NodeId
#   - and a serverUri
# Assume from now on that the particular nodes we want to refer to, are hosted by a server defined
# by the server URI "urn:UnifiedAutomation:UaDemoserver":
serverUri = "urn:UnifiedAutomation:UaDemoserver" 
# Then we can refer to the Root node like this:
Root_Node = Address( Root_NodeId, serverUri )
# An absolute address can also be created directly from an ExpandedNodeId:
Root_Node = Address( ExpandedNodeId(OpcUaId_RootFolder, OPCUA_NAMESPACE_ID, serverUri) )

# within the Root folder, there is another standard node called the Objects folder:
Objects_Node = Address( NodeId(OpcUaId_ObjectsFolder, OPCUA_NAMESPACE_ID), serverUri )

# we could also refer to the Objects node via a relative path!
# We can do this, since the standard Object node has a standard BrowseName. 
# The following are all valid ways to define the BrowseName of the Objects node 
Objects_BrowseName = QualifiedName("Objects", OPCUA_NAMESPACE_ID)
Objects_BrowseName = QualifiedName("Objects", OPCUA_NAMESPACE_URI)                      # namespace URI instead of index
Objects_BrowseName = QualifiedName("Objects", OPCUA_NAMESPACE_URI, OPCUA_NAMESPACE_ID)  # redundant namespace info, but valid
# we can now create a path from the Root node to the Objects node, using a path of one element:
Objects_Node = Address( Root_Node, [ RelativePathElement(Objects_BrowseName) ] )
# The Objects_Node that we just created, refers to the exact same node as the Objects_Node that we previously created.

# within the Objects node, there is a standard node called Server, which represents a sort 
# of object that contains all kinds of information about the server. 
# The following are all equally valid ways to define this node:
Server_Node = Address( ExpandedNodeId( NodeId(OpcUaId_Server, OPCUA_NAMESPACE_ID), serverUri) )
Server_Node = Address( ExpandedNodeId( OpcUaId_Server, OPCUA_NAMESPACE_ID, serverUri) )
Server_Node = Address( Root_Node   , [ RelativePathElement(QualifiedName("Objects", OPCUA_NAMESPACE_ID)), 
                                       RelativePathElement(QualifiedName("Server" , OPCUA_NAMESPACE_ID)) ] )
Server_Node = Address( Objects_Node, [ RelativePathElement(QualifiedName("Server" , OPCUA_NAMESPACE_ID)) ] )
# note that all Server_Node instances are equally valid, even the last one 
# (which is a "relative path to a relative path to an ExpandedNodeId") 



