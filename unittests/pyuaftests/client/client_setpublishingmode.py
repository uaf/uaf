import pyuaf
import time
import threading
import sys
import unittest
from pyuaf.util.unittesting import parseArgs


from pyuaf.util import NodeId, Address, ExpandedNodeId, BrowsePath, \
                       RelativePathElement, QualifiedName, opcuaidentifiers


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(ClientSetPublishingModeTest)



# define a TestClass with a callback
class TestClass:
    def __init__(self):
        self.noOfSuccessFullyReceivedNotifications = 0
        self.lock = threading.Lock() 
    
    def myCallback(self, notification):
        self.lock.acquire()
        self.noOfSuccessFullyReceivedNotifications += 1
        self.lock.release()




class ClientSetPublishingModeTest(unittest.TestCase):
    
    
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
        
        
        self.address_Demo            = Address(ExpandedNodeId("Demo", demoNsUri, serverUri))
        self.address_StartSimulation = Address(self.address_Demo, [RelativePathElement(QualifiedName("StartSimulation", demoNsUri))])
        self.address_StopSimulation  = Address(self.address_Demo, [RelativePathElement(QualifiedName("StopSimulation", demoNsUri))])
        self.address_Scalar          = Address(self.address_Demo, [RelativePathElement(QualifiedName("Dynamic", demoNsUri)),
                                                          RelativePathElement(QualifiedName("Scalar", demoNsUri))] )
        self.address_Byte            = Address(self.address_Scalar, [RelativePathElement(QualifiedName("Byte", demoNsUri))] )
        self.address_Int32           = Address(self.address_Scalar, [RelativePathElement(QualifiedName("Int32", demoNsUri))] )
        self.address_Int64           = Address(self.address_Scalar, [RelativePathElement(QualifiedName("Int64", demoNsUri))] )
        self.address_Float           = Address(self.address_Scalar, [RelativePathElement(QualifiedName("Float", demoNsUri))] )
        self.address_Double          = Address(self.address_Scalar, [RelativePathElement(QualifiedName("Double", demoNsUri))] )
        
        # start the simulation (otherwise the dynamic variables won't change)
        self.client.call(self.address_Demo, self.address_StartSimulation)
    
    
    def test_client_Client_setPublishingMode(self):
        
        # First we create some random monitored items, to make it the UAF a little bit more difficult.
        # (Because the UAF must now increase the subscription handle.)
        t0 = TestClass()
        res = self.client.createMonitoredData([self.address_Double, self.address_Int64], 
                                              notificationCallbacks=[t0.myCallback, t0.myCallback])
        
        # make sure there was no error
        self.assertTrue( res.overallStatus.isGood() )
        
        # store the clientSubscriptionHandle
        clientSubscriptionHandle0 = res.targets[0].clientSubscriptionHandle
        
        # Now we want to create some monitored items, of which we want to control the subscription mode.
        # We explicitly request the subscription to be unique (if we don't, then the subscription 
        # we previously created will be re-used!).
        subSettings = pyuaf.client.settings.SubscriptionSettings()
        subSettings.unique = True
        
        t1 = TestClass()
        res = self.client.createMonitoredData([self.address_Byte, self.address_Int32, self.address_Float],
                                              subscriptionSettings = subSettings,
                                              notificationCallbacks=[t1.myCallback, t1.myCallback, t1.myCallback])
        
        # make sure there was no error
        self.assertTrue( res.overallStatus.isGood() )
        
        # we expect that the clientSubscriptionHandle is now increased by one:
        for i in xrange(len(res.targets)):
            clientSubscriptionHandle1 = clientSubscriptionHandle0 + 1
            self.assertEqual( res.targets[i].clientSubscriptionHandle, clientSubscriptionHandle1 )
        
        # after a few seconds we should AT LEAST have received some notifications of both subscriptions
        t_timeout = time.time() + 5.0
        while time.time() < t_timeout \
           and (t0.noOfSuccessFullyReceivedNotifications < 2 \
                or t1.noOfSuccessFullyReceivedNotifications < 2):
            time.sleep(0.01)
        
        self.assertGreaterEqual( t0.noOfSuccessFullyReceivedNotifications , 2 )
        self.assertGreaterEqual( t1.noOfSuccessFullyReceivedNotifications , 2 )
        
        # verify the monitored item information of the items of the second subscription
        for i in xrange(len(res.targets)):
            info = self.client.monitoredItemInformation(res.targets[i].clientHandle)
            self.assertEqual(info.monitoredItemState, pyuaf.client.monitoreditemstates.Created)
            self.assertEqual(info.clientSubscriptionHandle, clientSubscriptionHandle1)
        
        # now disable the publishing of the second subscription
        
        self.client.setPublishingMode(clientSubscriptionHandle1, False)
        
        # no more notifications should be received within the next few seconds for the second subscription,
        # but the first subscription should continue to publish notifications!
        
        noOfNotifications0 = t0.noOfSuccessFullyReceivedNotifications
        noOfNotifications1 = t1.noOfSuccessFullyReceivedNotifications
        
        time.sleep(2)
        
        self.assertGreater( t0.noOfSuccessFullyReceivedNotifications, noOfNotifications0 ) # first subscription should have received notifications!
        self.assertEqual( t1.noOfSuccessFullyReceivedNotifications, noOfNotifications1 ) # second subscription should NOT have received notifications!
        
        # enable the publishing again of the second subscription
        
        self.client.setPublishingMode(clientSubscriptionHandle1, True)
        
        # notifications should again be received by BOTH subscriptions within the next few seconds!
        
        noOfNotifications0 = t0.noOfSuccessFullyReceivedNotifications
        noOfNotifications1 = t1.noOfSuccessFullyReceivedNotifications
        
        t_timeout = time.time() + 5.0
        while time.time() < t_timeout \
           and (t0.noOfSuccessFullyReceivedNotifications <= noOfNotifications0 \
                or t1.noOfSuccessFullyReceivedNotifications <= noOfNotifications1):
            time.sleep(0.01)
        
        self.assertGreater( t0.noOfSuccessFullyReceivedNotifications , noOfNotifications0 )
        self.assertGreater( t1.noOfSuccessFullyReceivedNotifications , noOfNotifications1 )
        
        
        
        

    def tearDown(self):
        # stop the simulation
        self.client.call(self.address_Demo, self.address_StopSimulation)
        
        # delete the client instances manually (now!) instead of letting them be garbage collected 
        # automatically (which may happen during a another test, and which may cause logging output
        # of the destruction to be mixed with the logging output of the other test).
        del self.client




if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())
