import pyuaf
import time
import _thread, threading
import unittest
from pyuaf.util.unittesting import parseArgs

from pyuaf.util import NodeId, Address, ExpandedNodeId, BrowsePath, \
                       RelativePathElement, QualifiedName, opcuaidentifiers
from pyuaf.util.opcuaidentifiers import OpcUaId_RootFolder, OpcUaId_ObjectsFolder
from pyuaf.client.requests import BrowseRequest, BrowseRequestTarget
from pyuaf.client.results  import BrowseResult,  BrowseResultTarget


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args

    return unittest.TestLoader().loadTestsFromTestCase(BrowseTest)




class BrowseTest(unittest.TestCase):


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

        self.address_Demo          = Address(ExpandedNodeId("Demo"               , demoNsUri, serverUri))
        self.address_StaticScalar  = Address(ExpandedNodeId("Demo.Static.Scalar" , demoNsUri, serverUri))
        self.address_DynamicScalar = Address(ExpandedNodeId("Demo.Dynamic.Scalar", demoNsUri, serverUri))


    def test_client_Client_browse_some_addresses(self):

        result = self.client.browse([self.address_Demo, self.address_StaticScalar, self.address_DynamicScalar])

        self.assertTrue( result.overallStatus.isGood() )
        self.assertGreaterEqual( len(result.targets[0].references) , 5 )
        self.assertGreaterEqual( len(result.targets[1].references) , 5 )
        self.assertGreaterEqual( len(result.targets[2].references) , 5 )

    def test_client_Client_processRequest_some_browse_request(self):

        request = BrowseRequest(3)

        request.targets[0].address = self.address_Demo
        request.targets[1].address = self.address_StaticScalar
        request.targets[2].address = self.address_DynamicScalar
        request.serviceSettingsGiven = True
        browseSettings = pyuaf.client.settings.BrowseSettings()
        browseSettings.maxReferencesToReturn = 3 # ridiculously low, to force automatic BrowseNext calls
        browseSettings.maxAutoBrowseNext = 100
        request.serviceSettings = browseSettings

        result = self.client.processRequest(request)

        self.assertTrue( result.overallStatus.isGood() )
        self.assertGreaterEqual( len(result.targets[0].references) , 5 )
        self.assertGreaterEqual( len(result.targets[1].references) , 5 )
        self.assertGreaterEqual( len(result.targets[2].references) , 5 )


    def tearDown(self):
        # delete the client instances manually (now!) instead of letting them be garbage collected
        # automatically (which may happen during a another test, and which may cause logging output
        # of the destruction to be mixed with the logging output of the other test).
        del self.client




if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())
