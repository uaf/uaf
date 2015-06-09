import pyuaf
import time
import thread
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
    
    return unittest.TestLoader().loadTestsFromTestCase(ClientKeepAliveTest)


class CallbackClass:
    def __init__(self):
        self.notificationList = []
    
    def callback(self, notification):
        self.notificationList.append(notification)


class MyClient(pyuaf.client.Client):

    def __init__(self, settings):
        pyuaf.client.Client.__init__(self, settings)
        self.notificationList = []
    
    def keepAliveReceived(self, notification):
        self.notificationList.append(notification)


class ClientKeepAliveTest(unittest.TestCase):
    
    
    def setUp(self):
        
        # create a new ClientSettings instance and add the localhost to the URLs to discover
        settings = pyuaf.client.settings.ClientSettings()
        settings.discoveryUrls.append(ARGS.demo_url)
        settings.applicationName = "client"
        settings.logToStdOutLevel = ARGS.loglevel
        
        self.client = MyClient(settings)
    
        self.serverUri = ARGS.demo_server_uri
        demoNsUri = ARGS.demo_ns_uri
        plcOpenNsUri = "http://PLCopen.org/OpcUa/IEC61131-3/"
        
        # define some nodeids
        self.node_id = NodeId(opcuaidentifiers.OpcUaId_Server_Auditing, 0)
        
        # define some addresses
        self.address = Address(ExpandedNodeId(self.node_id, self.serverUri))
    
    
    def test_client_Client_register_keepalivecallback_and_monitor_static_node(self):
        cbc = CallbackClass()
        self.client.registerKeepAliveCallback(cbc.callback)
        
        # create a request that will certainly result in KeepAlive notifications
        # It seems that we cannot force the UaServerCpp demo server to send KeepAlive messages
        # faster than once every 5 seconds, so we keep it at that: 
        request = pyuaf.client.requests.CreateMonitoredDataRequest(1)
        request.targets[0].address = self.address
        request.subscriptionConfig.defaultSubscriptionSettings.publishingIntervalSec = 1.0
        request.subscriptionConfig.defaultSubscriptionSettings.maxKeepAliveCount = 5
        
        result = self.client.processRequest(request)
        self.assertTrue( result.targets[0].status.isGood() )
        
        # wait some time
        time.sleep(7.0)
        
        # the callbacks should have been called at least once:
        for source in [self.client, cbc]:
            self.assertTrue( len(source.notificationList) >= 1 )
            self.assertEqual( source.notificationList[0].subscriptionState, pyuaf.client.subscriptionstates.Created )
     

    def tearDown(self):
        # delete the client instances manually (now!) instead of letting them be garbage collected 
        # automatically (which may happen during a another test, and which may cause logging output
        # of the destruction to be mixed with the logging output of the other test).
        del self.client
        

if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())