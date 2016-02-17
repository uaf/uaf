# examples/pyuaf/client/how_to_browse_some_nodes.py
"""
EXAMPLE: how to read and write structures
====================================================================================================

To run the example, start the UaServerCPP of UnifiedAutomation first on the same machine. 
($SDK/bin/uaservercpp, this executable is part of the SDK).
"""

import time, os, sys

import pyuaf
from pyuaf.client           import Client
from pyuaf.client.settings  import ClientSettings, SessionSettings
from pyuaf.util             import Address, NodeId, ExtensionObject, GenericStructureValue
from pyuaf.util             import primitives
from pyuaf.util             import opcuaidentifiers, attributeids, opcuatypes
from pyuaf.util.errors      import UafError


# define the namespace URI and server URI of the UaServerCPP demo server
demoServerUri = "urn:UnifiedAutomation:UaServerCpp"
demoNamespaceUri = "http://www.unifiedautomation.com/DemoServer/"

# define the address of the Structure which we would like to read
address = Address( NodeId("Demo.Static.Scalar.Vector", demoNamespaceUri), demoServerUri )

# define the ClientSettings:
settings = ClientSettings()
settings.applicationName = "MyClient"
settings.discoveryUrls.append("opc.tcp://localhost:48010")

# create the client
myClient = Client(settings)

# try to read a structure
result = myClient.read( [address] )

# we're expecting an ExtensionObject. Let's check this:
if isinstance(result.targets[0].data, ExtensionObject):
    print("We received an ExtensionObject")
    print("")
else:
    raise Exception("Oops, we were expecting an ExtensionObject, but we received a: %s" %result.targets[0].data)

extensionObject = result.targets[0].data

# now let's find out the datatype of the ExtensionObject
result = myClient.read( [address] , attributeId = attributeids.DataType)

dataTypeId = result.targets[0].data # data represents a NodeId

print("The datatype of the ExtensionObject is: NodeId: %s" %dataTypeId)
print("")

# using the datatypeId, get the definition of the structure
definition = myClient.structureDefinition(dataTypeId)

print("The definition of the structure:")
print(str(definition))
print("")

# using the original ExtensionObject the StructureDefinition, we can now create the GenericStructureValue:
structureValue = GenericStructureValue(extensionObject, definition)

# print the structure:
print("So we can now print the full structure:")
for i in xrange(definition.childrenCount()):
    child = definition.child(i)
    value = structureValue.value(i)
    print("  * child %d:"               %i)
    print("     - name      = %s"       %child.name())
    print("     - valueType = %d (%s)"  %(child.valueType(), opcuatypes.toString(child.valueType())))
    print("     - value     = %s"       %(structureValue.value(i))) # a pyuaf.util.primitives.Double instance
print("")

# now change the value of the first child (i = 0):
structureValue.setField(0, primitives.Double(0.1))

# we can also change a field via its name:
structureValue.setField("Y", primitives.Double(0.2))

# write back the structure
newExtensionObject = ExtensionObject()
structureValue.toExtensionObject(newExtensionObject)

print("Now writing {structure}.X = 0.1 and {structure}.Y = 0.2")
print("")
try:
    result = myClient.write( [address], [newExtensionObject] )
    if result.overallStatus.isGood():
        print("OK, the new structure value has been written successfully")
        print("Run this example again to verify that the .X and .Y fields have indeed changed")
    else:
        print("Oops, some OPC UA problem occurred. Here's the result:\n%s" %result)
except UafError, e:
    print("Oops, some error occurred on the client side. Here's the error message: %s" %e)

