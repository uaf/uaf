import pyuaf
import time
import thread
import unittest
from pyuaf.util.unittesting import parseArgs

from pyuaf.util import NodeId, Address, ExpandedNodeId, BrowsePath, \
                       RelativePathElement, QualifiedName, opcuaidentifiers
from pyuaf.util.opcuaidentifiers import OpcUaId_RootFolder, OpcUaId_ObjectsFolder
from pyuaf.client.requests import BrowseRequest, BrowseRequestTarget
from pyuaf.client.requests import BrowseNextRequest, BrowseNextRequestTarget
from pyuaf.client.results  import BrowseResult,  BrowseResultTarget



ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(BrowseNextTest)




class BrowseNextTest(unittest.TestCase):
    
    
    def setUp(self):
        
        # create a new ClientSettings instance and add the localhost to the URLs to discover
        settings = pyuaf.client.settings.ClientSettings()
        settings.discoveryUrls.append(ARGS.demo_url)
        settings.applicationName = "client"
        settings.logToStdOutLevel = ARGS.loglevel
    
        self.client = pyuaf.client.Client(settings)
        
        serverUri    = ARGS.demo_server_uri
        demoNsUri    = ARGS.demo_ns_uri
        
        self.address_Demo          = Address(ExpandedNodeId("Demo"               , demoNsUri, serverUri))
        self.address_StaticScalar  = Address(ExpandedNodeId("Demo.Static.Scalar" , demoNsUri, serverUri))
        self.address_DynamicScalar = Address(ExpandedNodeId("Demo.Dynamic.Scalar", demoNsUri, serverUri))
    
    
    def test_client_Client_browseNext(self):
        
        originalRequest = BrowseRequest(1) 
        
        originalRequest.targets[0].address = self.address_StaticScalar
        originalRequest.serviceConfig.serviceSettings.maxReferencesToReturn = 3 # ridiculously low, to force continuationPoints
        originalRequest.serviceConfig.serviceSettings.maxAutoBrowseNext = 0     # meaning: no automatic BrowseNext
        
        result = self.client.processRequest(originalRequest)
        
        self.assertTrue( result.overallStatus.isGood() )
        
        self.assertTrue( len(result.targets[0].continuationPoint) > 0 )
        
        noOfManualBrowseNext = 0
        
        while len(result.targets[0].continuationPoint) > 0:
        
            result = self.client.browseNext([originalRequest.targets[0].address], [result.targets[0].continuationPoint])
            
            self.assertTrue( result.overallStatus.isGood() )
            
            noOfManualBrowseNext += 1
        
        self.assertGreaterEqual( noOfManualBrowseNext , 3 )
    
    
    def test_client_Client_processRequest_some_browseNext_request(self):
        
        originalRequest = BrowseRequest(1) 
        
        originalRequest.targets[0].address = self.address_StaticScalar
        originalRequest.serviceConfig.serviceSettings.maxReferencesToReturn = 3 # ridiculously low, to force continuationPoints
        originalRequest.serviceConfig.serviceSettings.maxAutoBrowseNext = 0     # meaning: no automatic BrowseNext
        
        result = self.client.processRequest(originalRequest)
        
        self.assertTrue( result.overallStatus.isGood() )
        
        self.assertTrue( len(result.targets[0].continuationPoint) > 0 )
        
        noOfManualBrowseNext = 0
        
        while len(result.targets[0].continuationPoint) > 0:
            
            nextRequest = BrowseNextRequest(1)
            nextRequest.targets[0].address           = originalRequest.targets[0].address
            nextRequest.targets[0].continuationPoint = result.targets[0].continuationPoint
                
            result = self.client.processRequest(nextRequest)
            
            self.assertTrue( result.overallStatus.isGood() )
            
            noOfManualBrowseNext += 1
        
        self.assertGreaterEqual( noOfManualBrowseNext , 3 )
    
    
    def tearDown(self):
        # delete the client instances manually (now!) instead of letting them be garbage collected 
        # automatically (which may happen during a another test, and which may cause logging output
        # of the destruction to be mixed with the logging output of the other test).
        del self.client




if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())
