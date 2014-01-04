import pyuaf
import time
import thread
import unittest
from pyuaf.util.unittesting import parseArgs


from pyuaf.util import NodeId, Address, ExpandedNodeId, BrowsePath, \
                       RelativePathElement, QualifiedName, opcuaidentifiers
from pyuaf.client.requests import MethodCallRequest, MethodCallRequestTarget
from pyuaf.client.results  import MethodCallResult,  MethodCallResultTarget
from pyuaf.util.primitives import Double, UInt32



ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(ClientMethodCallTest)




class ClientMethodCallTest(unittest.TestCase):
    
    
    def setUp(self):
        
        # create a new ClientSettings instance and add the localhost to the URLs to discover
        settings = pyuaf.client.settings.ClientSettings()
        settings.discoveryUrls.append(ARGS.demo_url)
        settings.applicationName = "client"
        settings.logToStdOutLevel = ARGS.loglevel
    
        self.client = pyuaf.client.Client(settings)

        
        serverUri    = ARGS.demo_server_uri
        demoNsUri    = ARGS.demo_ns_uri
        
        self.address_Demo     = Address(ExpandedNodeId("Demo", demoNsUri, serverUri))
        self.address_Method   = Address(self.address_Demo, [RelativePathElement(QualifiedName("Method", demoNsUri))] )
        self.address_Multiply = Address(self.address_Method, [RelativePathElement(QualifiedName("Multiply", demoNsUri))] )
        self.address_SetSimulationSpeed = Address(self.address_Demo, [RelativePathElement(QualifiedName("SetSimulationSpeed", demoNsUri))] )
        
    def test_client_Client_call_a_single_method(self):
        
        result = self.client.call(self.address_Method, self.address_Multiply, [Double(2.0), Double(3.0)])
        
        self.assertTrue( result.overallStatus.isGood() )
        self.assertAlmostEqual( result.targets[0].outputArguments[0].value , 6.0 )
    
    
    def test_client_Client_processRequest_some_method_call_request(self):
        
        request = MethodCallRequest(2)
        
        request.targets[0].objectAddress = self.address_Method
        request.targets[0].methodAddress = self.address_Multiply
        request.targets[0].inputArguments.append(Double(2.0))
        request.targets[0].inputArguments.append(Double(3.0))
        
        request.targets[1].objectAddress = self.address_Demo
        request.targets[1].methodAddress = self.address_SetSimulationSpeed
        request.targets[1].inputArguments.append(UInt32(20))
        
        result = self.client.processRequest(request)
        
        self.assertTrue( result.overallStatus.isGood() )
        self.assertAlmostEqual( result.targets[0].outputArguments[0].value , 6.0 )


    def tearDown(self):
        # delete the client instances manually (now!) instead of letting them be garbage collected 
        # automatically (which may happen during a another test, and which may cause logging output
        # of the destruction to be mixed with the logging output of the other test).
        del self.client




if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())
