# examples/pyuaf/client/easiest_client_example.py

# Start the demo server ($SDK/bin/uaservercpp) of Unified Automation before running this script!

import pyuaf
from pyuaf.util             import Address, NodeId
from pyuaf.client           import Client
from pyuaf.client.settings  import ClientSettings

# create a client named "myClient", and provide the discovery URL of the server (uaservercpp):
myClient = Client(ClientSettings("myClient", ["opc.tcp://localhost:48010"]))

# specify the address of the node of which we would like to read its Value attribute:
# (here we're using an absolute address, i.e. a NodeId(<identifier>, <namespace URI>) and a <server URI>)
someAddress = Address(NodeId("Demo.SimulationSpeed",                         # NodeId identifier
                             "http://www.unifiedautomation.com/DemoServer"), # NodeId namespace URI
                      "urn:UnifiedAutomation:UaServerCpp")                   # server URI

# read the Value attribute of the node that we just addressed:
result = myClient.read( [someAddress] )

print("The value is %d" %result.targets[0].data.value)