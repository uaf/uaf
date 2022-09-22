import pyuaf
import time
import _thread, threading
import unittest
from pyuaf.util.unittesting import parseArgs

from pyuaf.util import NodeId, Address, ExpandedNodeId, BrowsePath, \
                       RelativePathElement, QualifiedName, opcuaidentifiers
from pyuaf.client.requests import WriteRequest, WriteRequestTarget
from pyuaf.client.results  import WriteResult,  WriteResultTarget
from pyuaf.util.primitives import Byte, Int32, Float

ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args

    return unittest.TestLoader().loadTestsFromTestCase(ClientWriteTest)



class ClientWriteTest(unittest.TestCase):


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

        self.address_Scalar = Address(ExpandedNodeId("Demo.Static.Scalar", demoNsUri, serverUri))
        self.address_Byte   = Address(self.address_Scalar, [RelativePathElement(QualifiedName("Byte", demoNsUri))] )
        self.address_Int32  = Address(self.address_Scalar, [RelativePathElement(QualifiedName("Int32", demoNsUri))] )
        self.address_Float  = Address(self.address_Scalar, [RelativePathElement(QualifiedName("Float", demoNsUri))] )

    def test_client_Client_write_some_nodes(self):

        result = self.client.write([self.address_Byte, self.address_Int32, self.address_Float],
                                   [Byte(2), Int32(-123), Float(1.2)])

        self.assertTrue( result.overallStatus.isGood() )

    def test_client_Client_processRequest_some_write_request(self):

        request = WriteRequest(3)
        request.targets[0].address = self.address_Byte
        request.targets[0].data    = Byte(2)
        request.targets[1].address = self.address_Int32
        request.targets[1].data    = Int32(-123)
        request.targets[2].address = self.address_Float
        request.targets[2].data    = Float(1.2)

        result = self.client.processRequest(request)

        self.assertTrue( result.overallStatus.isGood() )


    def tearDown(self):
        # delete the client instances manually (now!) instead of letting them be garbage collected
        # automatically (which may happen during a another test, and which may cause logging output
        # of the destruction to be mixed with the logging output of the other test).
        del self.client




if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())
