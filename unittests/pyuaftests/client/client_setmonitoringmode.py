import pyuaf
import time
import _thread, threading
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

    return unittest.TestLoader().loadTestsFromTestCase(ClientSetMonitoringModeTest)



# define a TestClass with a callback
class TestClass:
    def __init__(self):
        self.noOfSuccessFullyReceivedNotifications = 0
        self.lock = threading.Lock()

    def myCallback(self, notification):
        self.lock.acquire()
        self.noOfSuccessFullyReceivedNotifications += 1
        self.lock.release()




class ClientSetMonitoringModeTest(unittest.TestCase):


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

        # First we create some random monitored items, which we will *always* want to receive
        t0 = TestClass()
        res = self.client.createMonitoredData([self.address_Double, self.address_Int64],
                                              notificationCallbacks=[t0.myCallback, t0.myCallback])

        # make sure there was no error
        self.assertTrue( res.overallStatus.isGood() )

        # Now we want to create some monitored items, of which we want to control the monitoring mode.

        t1 = TestClass()
        res = self.client.createMonitoredData([self.address_Byte, self.address_Int32, self.address_Float],
                                              notificationCallbacks=[t1.myCallback, t1.myCallback, t1.myCallback])

        # make sure there was no error
        self.assertTrue( res.overallStatus.isGood() )

        # we store the client handles:
        clientHandles = [ target.clientHandle for target in res.targets ]

        # after a few seconds we should AT LEAST have received some notifications of both subscriptions
        t_timeout = time.time() + 5.0
        while time.time() < t_timeout \
           and (t0.noOfSuccessFullyReceivedNotifications < 2 \
                or t1.noOfSuccessFullyReceivedNotifications < 2):
            time.sleep(0.01)

        self.assertGreaterEqual( t0.noOfSuccessFullyReceivedNotifications , 2 )
        self.assertGreaterEqual( t1.noOfSuccessFullyReceivedNotifications , 2 )

        # now set the monitoring of the second set of monitored items to "Sampling"

        self.client.setMonitoringMode(clientHandles, pyuaf.util.monitoringmodes.Sampling)

        # no more notifications should be received within the next few seconds for the second subscription,
        # but the first subscription should continue to publish notifications!

        noOfNotifications0 = t0.noOfSuccessFullyReceivedNotifications
        noOfNotifications1 = t1.noOfSuccessFullyReceivedNotifications

        time.sleep(2)

        self.assertGreater( t0.noOfSuccessFullyReceivedNotifications, noOfNotifications0 ) # first subscription should have received notifications!
        self.assertEqual( t1.noOfSuccessFullyReceivedNotifications, noOfNotifications1 ) # second subscription should NOT have received notifications!

        # enable the reporting again of the second set of monitored items

        self.client.setMonitoringMode(clientHandles, pyuaf.util.monitoringmodes.Reporting)

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
