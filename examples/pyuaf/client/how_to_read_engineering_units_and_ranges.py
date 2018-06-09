# examples/pyuaf/client/how_to_read_engineering_units_and_ranges.py
"""
EXAMPLE: how to read engineering units and ranges
====================================================================================================

To run the example, start the UaServerCPP of UnifiedAutomation first on the same machine. 
($SDK/bin/uaservercpp, this executable is part of the SDK).
"""


import time, os, sys

import pyuaf
from pyuaf.client           import Client
from pyuaf.client.settings  import ClientSettings, SessionSettings
from pyuaf.util             import Address, NodeId, ExtensionObject, SdkStatus
from pyuaf.util             import Range, EUInformation
from pyuaf.util             import primitives
from pyuaf.util             import opcuaidentifiers, attributeids, opcuatypes, structurefielddatatypes
from pyuaf.util.errors      import UafError


# define the namespace URI and server URI of the UaServerCPP demo server
demoServerUri = "urn:UnifiedAutomation:UaServerCpp"
demoNamespaceUri = "urn:UnifiedAutomation:CppDemoServer:BuildingAutomation"

# define the ClientSettings:
settings = ClientSettings()
settings.applicationName = "MyClient"
settings.discoveryUrls.append("opc.tcp://localhost:48010")

# create the client
myClient = Client(settings)

# define the address of the Structure which we would like to read
units_address = Address( NodeId("AirConditioner_1.Temperature.EngineeringUnits", demoNamespaceUri), demoServerUri )
range_address = Address( NodeId("AirConditioner_1.Temperature.EURange", demoNamespaceUri), demoServerUri )

# try to read a structure
result = myClient.read( [units_address, range_address] )

# we're expecting ExtensionObjects. Let's check this:

for i in xrange(2):
    if isinstance(result.targets[i].data, ExtensionObject):
        print("We received an ExtensionObject")
    else:
        raise Exception("Oops, we were expecting an ExtensionObject, but we received a: %s" %result.targets[0].data)

units_extensionObject = result.targets[0].data
range_extensionObject = result.targets[1].data

# analyze the engineering units
units_object = EUInformation(units_extensionObject)
print("")
print("Engineering Units")
print("=================")
print(units_object)
print("UNIT ID = %d" % units_object.getUnitId())
print("NAMESPACE URI = %s" % units_object.getNamespaceUri())
print("DISPLAY NAME = %s" % units_object.getDisplayName())
print("DESCRIPTION = %s" % units_object.getDescription())

# analyze the range
range_object = Range(range_extensionObject)
print("")
print("Range")
print("=====")
print(range_object)
print("LOW = %d" % range_object.getLow())
print("HIGH = %d" % range_object.getHigh())


