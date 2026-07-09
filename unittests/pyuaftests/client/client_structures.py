import pyuaf
import time
import _thread, threading
import sys
import unittest
from pyuaf.util.unittesting import parseArgs

import pyuaf
from pyuaf.client           import Client
from pyuaf.client.settings  import ClientSettings, SessionSettings
from pyuaf.util             import Address, NodeId, ExtensionObject, SdkStatus, RelativePathElement, BrowsePath, ExpandedNodeId
from pyuaf.util             import GenericStructureValue, GenericStructureVector, GenericUnionValue
from pyuaf.util             import primitives
from pyuaf.util             import opcuaidentifiers, attributeids, opcuatypes, structurefielddatatypes
from pyuaf.util.errors      import UafError

ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args

    return unittest.TestLoader().loadTestsFromTestCase(ClientStructuresTest)






class ClientStructuresTest(unittest.TestCase):


    def setUp(self):

        # create a new ClientSettings instance and add the localhost to the URLs to discover
        settings = pyuaf.client.settings.ClientSettings()
        settings.discoveryUrls.append(ARGS.demo_url)
        settings.applicationName = "client"
        settings.logToStdOutLevel = ARGS.loglevel

        self.client = pyuaf.client.Client(settings)


        serverUri    = ARGS.demo_server_uri
        demoNsUri    = ARGS.demo_ns_uri
        plcOpenNsUri = "http://PLCopen.org/OpcUa/IEC61131-3/"


        self.address_vector    = Address( NodeId("Demo.Static.Scalar.Vector", demoNsUri), serverUri )
        self.address_union = Address( NodeId("Demo.Static.Scalar.Structures.AnalogMeasurement", demoNsUri), serverUri )



    def test_client_Client_structures(self):

        # read the structure
        result = self.client.read( [self.address_vector] )

        self.assertTrue( isinstance(result.targets[0].data, ExtensionObject) )
        extensionObject = result.targets[0].data

        result = self.client.read( [self.address_vector] , attributeId = attributeids.DataType)

        dataTypeId = result.targets[0].data

        self.assertEqual( dataTypeId.identifier().idNumeric, 3002 )

        # using the datatypeId, get the definition of the structure
        definition = self.client.structureDefinition(dataTypeId)
        self.assertEqual( definition.isUnion(), False )
        self.assertEqual( definition.child(0).name(), 'X' )
        self.assertEqual( definition.child(1).valueType(), opcuatypes.Double )

        # using the original ExtensionObject the StructureDefinition, we can now create the GenericStructureValue:
        structureValue = GenericStructureValue(extensionObject, definition)

        # verify the structure:
        fieldType, opcUaStatusCode  = structureValue.valueType(0)
        self.assertEqual( fieldType, structurefielddatatypes.Variant )
        value, statuscode = structureValue.value(0)
        self.assertTrue( isinstance(value, primitives.Double ) )
        self.assertEquals(statuscode, 0)
        # now change the value of the first child (i = 0):
        structureValue.setField(0, primitives.Double(0.1) )

        # write back the structure
        newExtensionObject = ExtensionObject()
        structureValue.toExtensionObject(newExtensionObject)

        result = self.client.write( [self.address_vector], [newExtensionObject] )
        self.assertTrue( result.overallStatus.isGood() )

        result          = self.client.read( [self.address_vector] )
        extensionObject = result.targets[0].data
        structureValue  = GenericStructureValue(extensionObject, definition)
        value, statuscode = structureValue.value(0)
        self.assertEqual( value, primitives.Double(0.1) )
        self.assertEqual( statuscode, 0 )


    def test_client_Client_unions(self):
        # read the structure
        result = self.client.read( [self.address_union] )

        self.assertTrue( isinstance(result.targets[0].data, ExtensionObject) )
        extensionObject = result.targets[0].data

        result = self.client.read( [self.address_union] , attributeId = attributeids.DataType)

        dataTypeId = result.targets[0].data

        self.assertEqual( dataTypeId.identifier().idNumeric, 543213)

        # using the datatypeId, get the definition of the structure
        definition = self.client.structureDefinition(dataTypeId)
        self.assertEqual( definition.isUnion(), True )
        self.assertEqual( definition.child(0).name(), 'Temperature' )
        self.assertEqual( definition.child(0).valueType(), opcuatypes.Float )

        # using the original ExtensionObject the StructureDefinition, we can now create the union value:
        union = GenericUnionValue(extensionObject, definition)

        # verify the union
        switchValue = union.switchValue()
        field       = union.field()

        self.assertEquals(switchValue, 1)

        # now change the active value
        union.setValue(union.field().name(), primitives.Float(111.222))

        # write back the union
        newExtensionObject = ExtensionObject()
        union.toExtensionObject(newExtensionObject)

        result = self.client.write( [self.address_union], [newExtensionObject] )
        self.assertTrue( result.overallStatus.isGood() )

        result          = self.client.read( [self.address_union] )
        extensionObject = result.targets[0].data
        union           = GenericUnionValue(extensionObject, definition)

        self.assertEquals(union.value(), primitives.Float(111.222))





    def tearDown(self):
        # delete the client instances manually (now!) instead of letting them be garbage collected
        # automatically (which may happen during a another test, and which may cause logging output
        # of the destruction to be mixed with the logging output of the other test).
        del self.client




if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())
