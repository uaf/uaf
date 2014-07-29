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
    
    return unittest.TestLoader().loadTestsFromTestCase(ClientSubscriptionStatusTest)


class CallbackClass:
    def __init__(self):
        self.infoList = []
    
    def callback(self, info):
        self.infoList.append(info)


class MyClient(pyuaf.client.Client):

    def __init__(self, settings):
        pyuaf.client.Client.__init__(self, settings)
        self.infoList = []
        self.previousSeqNumbers = []
        self.newSeqNumbers = []
    
    def notificationsMissing(self, info, previousSeqNumber, newSeqNumber):
        self.infoList.append(info)
        self.previousSeqNumbers.append(previousSeqNumber)
        self.newSeqNumbers.append(newSeqNumber)


class ClientSubscriptionStatusTest(unittest.TestCase):
    
    
    def setUp(self):
        
        # create a new ClientSettings instance and add the localhost to the URLs to discover
        settings = pyuaf.client.settings.ClientSettings()
        settings.discoveryUrls.append(ARGS.demo_url)
        settings.applicationName = "client"
        settings.logToStdOutLevel = ARGS.loglevel
        
        self.client = MyClient(settings)
    
        serverUri = ARGS.demo_server_uri
        demoNsUri = ARGS.demo_ns_uri
        plcOpenNsUri = "http://PLCopen.org/OpcUa/IEC61131-3/"
        
        # define some addresses
        self.address_Demo            = Address(ExpandedNodeId("Demo", demoNsUri, serverUri))
        self.address_StartSimulation = Address(self.address_Demo, [RelativePathElement(QualifiedName("StartSimulation", demoNsUri))])
        self.address_StopSimulation  = Address(self.address_Demo, [RelativePathElement(QualifiedName("StopSimulation", demoNsUri))])
        self.address_Scalar          = Address(self.address_Demo, [RelativePathElement(QualifiedName("Dynamic", demoNsUri)),
                                                                   RelativePathElement(QualifiedName("Scalar", demoNsUri))] )
        self.address_Byte            = Address(self.address_Scalar, [RelativePathElement(QualifiedName("Byte", demoNsUri))] )
    
        # start the simulation (otherwise the dynamic variables won't change)
        self.client.call(self.address_Demo, self.address_StartSimulation)
    
    
    def test_client_Client_register_missingnotificationscallback_and_monitor_node(self):
        cbc = CallbackClass()
        self.client.registerNotificationsMissingCallback(cbc.callback)
        
        # create a request that will certainly result in missing notifications
        # (as the variable of the UaServerCpp change about once per second)
        publishingIntervalSec = 3.0
        request = pyuaf.client.requests.CreateMonitoredDataRequest(1)
        request.targets[0].address = self.address_Byte
        request.targets[0].queueSize = 1
        request.targets[0].samplingIntervalSec = 1.0
        request.targets[0].discardOldest = False
        request.subscriptionConfig.defaultSubscriptionSettings.maxNotificationsPerPublish = 1
        request.subscriptionConfig.defaultSubscriptionSettings.publishingIntervalSec = publishingIntervalSec
        
        result = self.client.processRequest(request)
        self.assertTrue( result.targets[0].status.isGood() )
        
        # wait some time
        time.sleep(publishingIntervalSec + 5.0)
        
        # the callbacks should have been called at least once:
        for source in [self.client, cbc]:
            self.assertTrue( len(source.infoList) >= 1 )
            self.assertEqual( source.infoList[0].subscriptionState, pyuaf.client.subscriptionstates.Created )
            self.assertNotEqual(source.previousSeqNumbers[0], source.newSeqNumbers[0]  )
     

    def tearDown(self):
        # delete the client instances manually (now!) instead of letting them be garbage collected 
        # automatically (which may happen during a another test, and which may cause logging output
        # of the destruction to be mixed with the logging output of the other test).
        del self.client
        

if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())