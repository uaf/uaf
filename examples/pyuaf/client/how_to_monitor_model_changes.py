# examples/pyuaf/client/how_to_monitor_model_changes.py
"""
EXAMPLE: how to monitor model changes
====================================================================================================

To run the example, start the UaDemoServer of UnifiedAutomation first on the same machine. 
"""

import time, os

import pyuaf
from pyuaf.client           import Client
from pyuaf.client.settings  import ClientSettings
from pyuaf.util             import EventFilter
from pyuaf.util             import Address, NodeId, QualifiedName
from pyuaf.util             import ExtensionObject, ModelChangeStructureDataType
from pyuaf.util             import primitives
from pyuaf.util.errors      import UafError
from pyuaf.util             import opcuaidentifiers


# define the namespace URI and server URI of the UaDemoServer
demoNsUri     = "http://www.unifiedautomation.com/DemoServer"
demoServerUri = "urn:UnifiedAutomation:UaServerCpp"

# define some addresses which will be used later on
address_Server  = Address( NodeId(opcuaidentifiers.OpcUaId_Server      , 0), demoServerUri )
address_Dynamic = Address( NodeId("Demo.DynamicNodes"                  , demoNsUri), demoServerUri )
address_Create  = Address( NodeId("Demo.DynamicNodes.CreateDynamicNode", demoNsUri), demoServerUri )
address_Delete  = Address( NodeId("Demo.DynamicNodes.DeleteDynamicNode", demoNsUri), demoServerUri )

# define the ClientSettings:
settings = ClientSettings()
settings.applicationName = "MyClient"
settings.discoveryUrls.append("opc.tcp://localhost:48010")

# create the client
myClient = Client(settings)

# define the event filter to only receive the GeneralModelChangeEventType events
eventFilter = EventFilter()
eventFilter.selectClauses.resize(1)
eventFilter.selectClauses[0].attributeId = pyuaf.util.attributeids.Value
eventFilter.selectClauses[0].browsePath.append(QualifiedName("Changes", 0))
eventFilter.selectClauses[0].typeId = NodeId(opcuaidentifiers.OpcUaId_GeneralModelChangeEventType, 0)

# define a callback function to handle the events
def myCallback(notification):
    print("Notification received!")
    changes = notification.fields[0]
    print("Changes:")
    for i in xrange(len(changes)):
        change = changes[i]
        print("- change %d:" %i)
        print(change)
        # check if we received indeed an ExtensionObject:
        assert isinstance(change, pyuaf.util.ExtensionObject)
        # OK, we can now check that the ExtensionObject represents a ModelChangeStructureDataType instance
        assert change.dataTypeId == NodeId(opcuaidentifiers.OpcUaId_ModelChangeStructureDataType, 0)
        print("The same object, converted to a ModelChangeStructureDataType:")
        modelChange = ModelChangeStructureDataType(change)
        print modelChange
        
    


print("STEP 1: start monitoring the Server node for events")
print("===================================================")
print("")
result = myClient.createMonitoredEvents( addresses             = [address_Server], 
                                         eventFilter           = eventFilter, 
                                         notificationCallbacks = [myCallback] )
print("Result:")
print(result)
print("")

print("STEP 2: Dynamically create a Node and wait a second for events to arrive")
print("========================================================================")
print("")
result = myClient.call(address_Dynamic, address_Create)
print("Result:")
print(result)
print("")
time.sleep(1)

print("")
print("STEP 3: Dynamically delete the same Node and wait a second for events to arrive")
print("===============================================================================")
print("")
result = myClient.call(address_Dynamic, address_Delete)
print("Result:")
print(result)
print("")

time.sleep(1)