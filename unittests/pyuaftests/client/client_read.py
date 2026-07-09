import pyuaf
import time
import _thread, threading
import unittest
from pyuaf.util.unittesting import parseArgs

from pyuaf.util import NodeId, Address, ExpandedNodeId, BrowsePath, \
                       RelativePathElement, QualifiedName, opcuaidentifiers
from pyuaf.client.requests import ReadRequest, ReadRequestTarget
from pyuaf.client.results  import ReadResult,  ReadResultTarget



ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args

    return unittest.TestLoader().loadTestsFromTestCase(ClientReadTest)


class ClientReadTest(unittest.TestCase):


    def setUp(self):

        # create a new ClientSettings instance and add the localhost to the URLs to discover
        settings = pyuaf.client.settings.ClientSettings()
        settings.discoveryUrls.append(ARGS.demo_url)
        settings.applicationName = "client"
        settings.logToStdOutLevel = ARGS.loglevel

        self.client = pyuaf.client.Client(settings)

        serverUri = ARGS.demo_server_uri
        demoNsUri = ARGS.demo_ns_uri
        plcOpenNsUri = "http://PLCopen.org/OpcUa/IEC61131-3/"

        # define some nodeids
        self.id0 = NodeId(opcuaidentifiers.OpcUaId_Server_Auditing, 0)
        self.id1 = NodeId(opcuaidentifiers.OpcUaId_Server_ServerCapabilities_MaxHistoryContinuationPoints, 0)
        self.id2 = NodeId("Demo.SimulationSpeed", 2)
        self.id3 = NodeId("Demo.SimulationActive", demoNsUri)
        self.id4 = NodeId(opcuaidentifiers.OpcUaId_Server_ServerArray, 0)

        # define some nodeids
        self.address0 = Address(ExpandedNodeId(self.id0, serverUri))
        self.address1 = Address(ExpandedNodeId(self.id1, serverUri))
        self.address2 = Address(ExpandedNodeId(self.id2, serverUri))
        self.address3 = Address(ExpandedNodeId(self.id3, serverUri))
        self.address4 = Address(ExpandedNodeId(self.id4, serverUri))

        # create some relative paths
        self.id5      = NodeId("Demo.BoilerDemo.Boiler1", demoNsUri)
        self.start5   = Address(ExpandedNodeId(self.id5, serverUri))
        self.name5    = QualifiedName("TemperatureSetPoint", demoNsUri)
        self.elem5    = RelativePathElement(self.name5)
        self.path5    = [self.elem5]
        self.address5 = Address(self.start5, self.path5)

        self.start6   = Address(ExpandedNodeId("Demo", demoNsUri, serverUri))
        self.elem6a   = RelativePathElement(QualifiedName("BoilerDemo", demoNsUri))
        self.elem6b   = RelativePathElement(QualifiedName("Boiler1", demoNsUri))
        self.path6    = [self.elem6a, self.elem6b]
        self.address6 = Address(self.start6, self.path6)

        self.elem7a   = RelativePathElement(QualifiedName("TemperatureSensor", demoNsUri))
        self.elem7b   = RelativePathElement(QualifiedName("Temperature", demoNsUri))
        self.path7    = [self.elem7a, self.elem7b]
        self.address7 = Address(self.address6, self.path7)

    def test_client_Client_read_single_standard_node_with_nodeid(self):
        res0 = self.client.read(self.address0)
        self.assertEqual( res0.targets[0].data.value , False )
        res1 = self.client.read(self.address1)
        self.assertTrue( res1.targets[0].status.isGood() )

    def test_client_Client_read_some_standard_nodes_with_nodeid(self):
        res0res1 = self.client.read([self.address0, self.address1])
        self.assertEqual( res0res1.targets[0].data.value , False )
        self.assertTrue( res0res1.targets[1].status.isGood() )

    def test_client_Client_read_some_non_standard_nodes_with_nodeid(self):
        res2res3 = self.client.read([self.address2, self.address3])
        self.assertTrue( res2res3.overallStatus.isGood() )

    def test_client_Client_read_the_serverarray(self):
        res4 = self.client.read([self.address4])
        self.assertTrue( res4.overallStatus.isGood() )

    def test_client_Client_read_node_with_relative_path(self):
        res5 = self.client.read(self.address5)
        self.assertEqual( res5.targets[0].data.type() , pyuaf.util.opcuatypes.Double )
        self.assertTrue( res5.targets[0].status.isGood() )
        self.assertTrue( res5.overallStatus.isGood() )

    def test_client_Client_read_node_with_complex_relative_path(self):
        res7 = self.client.read(self.address7)

        self.assertEqual( res7.targets[0].data.type() , pyuaf.util.opcuatypes.Double )
        self.assertTrue( res7.targets[0].status.isGood() )
        self.assertTrue( res7.overallStatus.isGood() )

    def test_client_Client_processRequest_for_a_read_request(self):
        # create some targets to be read
        target8a = ReadRequestTarget(self.address6, pyuaf.util.attributeids.DisplayName)
        target8b = ReadRequestTarget(self.address7, pyuaf.util.attributeids.Historizing)

        # create the request
        req8 = ReadRequest([target8a, target8b])

        # process the request
        res8 = self.client.processRequest(req8)

        # assert the result
        self.assertTrue( res8.targets[0].status.isGood() )
        self.assertEqual( res8.targets[0].data , pyuaf.util.LocalizedText("", "Boiler1") )
        self.assertEqual( res8.targets[1].data.value , False )

    def tearDown(self):
        # delete the client instances manually (now!) instead of letting them be garbage collected
        # automatically (which may happen during a another test, and which may cause logging output
        # of the destruction to be mixed with the logging output of the other test).
        del self.client


if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())