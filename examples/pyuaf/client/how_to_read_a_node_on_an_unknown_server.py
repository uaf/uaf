# examples/pyuaf/client/how_to_read_a_node_on_an_unknown_server.py

# !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
# !!! Start the demo server ($SDK/bin/uaservercpp) of Unified Automation before running this script !!!!
# !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

# When trying to interact with a third-party server (i.e. any server of which you don't know all details
# from), you must dynamically discover some "details".
# This example will show you how to connect and interact with such an "unknown" server.
#
# In general, what you *do* know is the IP address and port of the server. Together they are known as
# the "discoveryURL".
# You can provide a discovery URL like this:

import pyuaf
from pyuaf.util             import Address, NodeId
from pyuaf.util             import opcuaidentifiers
from pyuaf.client           import Client
from pyuaf.client.settings  import ClientSettings

# create a client named "myClient", and provide the discovery URL of the server (uaservercpp):
myClient = Client(ClientSettings("myClient", ["opc.tcp://localhost:48010"]))

# The client now discovers the "opc.tcp://localhost:48010", and fetches the application description
# of the UaServerCpp demo server.
# Let's print out what the client discovered:
listOfApplicationDescriptions = myClient.serversFound()
print(listOfApplicationDescriptions)

# It's a list of one server description (the demo server). It tells us the application URI, or in
# this case, the server uri:
SERVER_URI = listOfApplicationDescriptions[0].applicationUri

# Okay now that we know the server URI of the demo server, we can connect to it.
# We'll just dynamically browse the address space, and let the UAF do the connection for us:

rootNode = Address( NodeId(opcuaidentifiers.OpcUaId_RootFolder, 0), SERVER_URI )
firstLevelBrowseResult = myClient.browse([rootNode])
print("BROWSE RESULT:")
print(firstLevelBrowseResult)

# Note that the 0 is the namespace index for the OPC UA standard. It always corresponds to the
# OPC UA standard URI 'http://opcfoundation.org/UA/'
# Instead of the above, we therefore could have also specified the namespace URI:
#rootNode = Address(NodeId(opcuaidentifiers.OpcUaId_RootFolder,
#                          'http://opcfoundation.org/UA/'),
#                   SERVER_URI)
# It woulnd't make a difference, as the UAF will automatically "translate" the namespace URI
# 'http://opcfoundation.org/UA/' to the namespace index 0 for you.
# The mapping between namespace URIs and namespace indexes is called the NamespaceArray.
# Let's print this mapping:
result = myClient.read(Address(NodeId(opcuaidentifiers.OpcUaId_Server_NamespaceArray,
                                      pyuaf.util.constants.OPCUA_NAMESPACE_URI), # same as 'http://opcfoundation.org/UA/'
                               SERVER_URI ))

NAMESPACE_ARRAY = result.targets[0].data

print("NamespaceArray:")
for i in range(len(NAMESPACE_ARRAY)):
    print("NamespaceIndex %d corresponds to NamespaceURI '%s'" %(i, NAMESPACE_ARRAY[i].value))

# Indeed, we can see above that namespace index 0 corresponds
# to namespace URI 'http://opcfoundation.org/UA/'!

# Now that you know the ServerURI and the namespace URIs, you still need to figure out the NodeId
# details for each node that you want to read/write/monitor/... You can use the browse functionality
# of PyUAF for this (see the how_to_browse_some_nodes.py example), or you can simply use UaExpert
# to know the details of the nodes.
#
# For instance, UaExpert tells us that the "Demo.SimulationSpeed" node has namespace index 2, and
# identifier "Demo.SimulationSpeed". So we can read this node easily:

address = Address(NodeId("Demo.SimulationSpeed",            # NodeId identifier
                         2),                                # NodeId namespace index
                  SERVER_URI)                               # server URI

result = myClient.read([address])
print("Read result:")
print(result)

# Since the namespace array may change over time, it is however much preferred that you
# identify the namespace via the URI instead of the namespace index.
# Looking at the printed NamespaceArray above, we see that namespace index 2 corresponds
# to namespace URI 'http://www.unifiedautomation.com/DemoServer/'.
# So we can read the node like this instead:
address = Address(NodeId("Demo.SimulationSpeed",                            # NodeId identifier
                         'http://www.unifiedautomation.com/DemoServer/'),   # NodeId namespace URI
                  SERVER_URI)                                               # server URI

result = myClient.read([address])
print("Read result:")
print(result)

