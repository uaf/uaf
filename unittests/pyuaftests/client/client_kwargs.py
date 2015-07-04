import pyuaf
import time
import thread
import unittest
from pyuaf.util.unittesting import parseArgs

from pyuaf.util import NodeId, Address, ExpandedNodeId, BrowsePath, \
                       RelativePathElement, QualifiedName, opcuaidentifiers
from pyuaf.client.requests import ReadRequest, ReadRequestTarget
from pyuaf.client.results  import ReadResult,  ReadResultTarget
from pyuaf.client.settings import ClientSettings, SessionSettings, SubscriptionSettings


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(ClientKwargsTest)


class ClientKwargsTest(unittest.TestCase):
    
    
    def setUp(self):
        
        # create a new ClientSettings instance and add the localhost to the URLs to discover
        settings = ClientSettings()
        settings.discoveryUrls.append(ARGS.demo_url)
        settings.applicationName = "client"
        settings.logToStdOutLevel = ARGS.loglevel
        
        self.client = pyuaf.client.Client(settings)
    
        self.serverUri = ARGS.demo_server_uri
        demoNsUri = ARGS.demo_ns_uri
        plcOpenNsUri = "http://PLCopen.org/OpcUa/IEC61131-3/"
        
        # define some addresses
        self.addresses = [ Address(NodeId("Demo.SimulationSpeed", demoNsUri), self.serverUri),
                           Address(NodeId("Demo.SimulationActive", demoNsUri), self.serverUri) ]
        

    def test_client_Client_kwargs_defaultSessionSettings(self):
        clientSettings = self.client.clientSettings()
        clientSettings.defaultSessionSettings.connectTimeoutSec = 4.0
        self.client.setClientSettings(clientSettings)
        result = self.client.read(self.addresses)
        self.assertTrue(result.overallStatus.isGood())
        allSessionInfos = self.client.allSessionInformations()
        self.assertEqual(len(allSessionInfos), 1)
        self.assertEqual(allSessionInfos[0].sessionSettings, clientSettings.defaultSessionSettings)
        # check if the session is reused
        result = self.client.read(self.addresses)
        self.assertTrue(result.overallStatus.isGood())
        self.assertEqual(len(allSessionInfos), 1)
        

    def test_client_Client_kwargs_specificSessionSettings(self):
        clientSettings = self.client.clientSettings()
        clientSettings.specificSessionSettings[self.serverUri] = SessionSettings()
        clientSettings.specificSessionSettings[self.serverUri].connectTimeoutSec = 6.0
        self.client.setClientSettings(clientSettings)
        result = self.client.read(self.addresses)
        self.assertTrue(result.overallStatus.isGood())
        allSessionInfos = self.client.allSessionInformations()
        self.assertEqual(len(allSessionInfos), 1)
        self.assertEqual(allSessionInfos[0].sessionSettings, clientSettings.specificSessionSettings[self.serverUri])
        self.assertNotEqual(allSessionInfos[0].sessionSettings, clientSettings.defaultSessionSettings)
        # check if the session is reused
        result = self.client.read(self.addresses)
        self.assertTrue(result.overallStatus.isGood())
        self.assertEqual(len(allSessionInfos), 1)

    def test_client_Client_kwargs_clientConnectionId_wrong(self):
        with self.assertRaises(pyuaf.util.errors.UnknownClientConnectionIdError):
            self.client.read(self.addresses, clientConnectionId = 0)
        
        
    def test_client_Client_kwargs_clientConnectionId(self):
        result1 = self.client.read(self.addresses)
        self.assertTrue(result1.overallStatus.isGood())
        result2 = self.client.read(self.addresses, clientConnectionId = 0)
        self.assertTrue(result2.overallStatus.isGood())
        with self.assertRaises(pyuaf.util.errors.UnknownClientConnectionIdError):
            self.client.read(self.addresses, clientConnectionId = 1)
        
        
    def test_client_Client_kwargs_sessionSettings(self):
        sessionSettings = SessionSettings()
        sessionSettings.connectTimeoutSec = 5.0
        
        result = self.client.read(self.addresses, sessionSettings = sessionSettings)
        self.assertTrue(result.overallStatus.isGood())
        allSessionInfos = self.client.allSessionInformations()
        self.assertEqual(len(allSessionInfos), 1)
        self.assertEqual(allSessionInfos[0].sessionSettings, sessionSettings)
        # check if the following session is reused
        result = self.client.read(self.addresses, sessionSettings = sessionSettings)
        self.assertTrue(result.overallStatus.isGood())
        allSessionInfos = self.client.allSessionInformations()
        self.assertEqual(len(allSessionInfos), 1)
        self.assertEqual(allSessionInfos[0].sessionSettings, sessionSettings)
        self.assertEqual(result.targets[0].clientConnectionId, 0)
        # check if the following session is not reused
        sessionSettings2 = SessionSettings()
        sessionSettings2.connectTimeoutSec = 6.0
        result = self.client.read(self.addresses, sessionSettings = sessionSettings2)
        self.assertTrue(result.overallStatus.isGood())
        allSessionInfos = self.client.allSessionInformations()
        self.assertEqual(len(allSessionInfos), 2)
        self.assertEqual(allSessionInfos[1].sessionSettings, sessionSettings2)
        self.assertEqual(result.targets[0].clientConnectionId, 1)
        # check if the following session is not reused
        sessionSettings.unique = True
        result = self.client.read(self.addresses, sessionSettings = sessionSettings)
        self.assertTrue(result.overallStatus.isGood())
        allSessionInfos = self.client.allSessionInformations()
        self.assertEqual(len(allSessionInfos), 3)
        self.assertEqual(allSessionInfos[2].sessionSettings, sessionSettings)
        self.assertEqual(result.targets[0].clientConnectionId, 2)
        # check if the following session is not reused
        result = self.client.read(self.addresses, sessionSettings = sessionSettings)
        self.assertTrue(result.overallStatus.isGood())
        allSessionInfos = self.client.allSessionInformations()
        self.assertEqual(len(allSessionInfos), 4)
        self.assertEqual(allSessionInfos[3].sessionSettings, sessionSettings)
        self.assertEqual(result.targets[0].clientConnectionId, 3)
        # check if a specific ClientConnectionId may be reused:
        result = self.client.read(self.addresses, clientConnectionId = 3)
        self.assertTrue(result.overallStatus.isGood())
        allSessionInfos = self.client.allSessionInformations()
        self.assertEqual(len(allSessionInfos), 4)
        self.assertEqual(result.targets[0].clientConnectionId, 3)
        
    
    
    
    def tearDown(self):
        # delete the client instances manually (now!) instead of letting them be garbage collected 
        # automatically (which may happen during a another test, and which may cause logging output
        # of the destruction to be mixed with the logging output of the other test).
        del self.client
        

if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())