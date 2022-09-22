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

    return unittest.TestLoader().loadTestsFromTestCase(ClientSubscriptionStatusTest)


class CallbackClass:
    def __init__(self):
        self.infoList = []

    def callback(self, info):
        self.infoList.append(info)

    def isCallbackCalled(self):
        return len(self.infoList) > 0


class MyClient(pyuaf.client.Client):

    def __init__(self, settings):
        pyuaf.client.Client.__init__(self, settings)
        self.infoList = []

    def subscriptionStatusChanged(self, info):
        self.infoList.append(info)

    def isCallbackCalled(self):
        return len(self.infoList) > 0


class ClientSubscriptionStatusTest(unittest.TestCase):


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


    def test_client_Client_register_all_subscriptionstatuses_and_monitor_node(self):
        cbc = CallbackClass()
        self.client.registerSubscriptionStatusCallback(cbc.callback)

        result = self.client.createMonitoredData(self.address)

        self.assertTrue( result.targets[0].status.isGood() )

        # the callbacks may be dispatched in a separate Python thread, which may not be completed
        # yet, so we must wait for them!
        t_end = time.time() + 1.0 # 1 sec timeout
        while time.time() < t_end and not (self.client.isCallbackCalled() and cbc.isCallbackCalled()):
            time.sleep(0.001) # do nothing, just wait

        for source in [self.client, cbc]:
            self.assertTrue( source.isCallbackCalled() )
            self.assertEqual( source.infoList[0].subscriptionState, pyuaf.client.subscriptionstates.Created )


    def test_client_Client_register_all_subscriptionstatuses_and_manually_subscribe(self):
        cbc = CallbackClass()
        self.client.registerSubscriptionStatusCallback(cbc.callback)

        clientConnectionId = self.client.manuallyConnect(self.serverUri)
        clientSubscriptionHandle = self.client.manuallySubscribe(clientConnectionId)

        # the callbacks may be dispatched in a separate Python thread, which may not be completed
        # yet, so we must wait for them!
        t_end = time.time() + 1.0 # 1 sec timeout
        while time.time() < t_end and not (self.client.isCallbackCalled() and cbc.isCallbackCalled()):
            time.sleep(0.001) # do nothing, just wait

        for source in [self.client, cbc]:
            self.assertTrue( source.isCallbackCalled() )
            self.assertEqual( source.infoList[0].subscriptionState, pyuaf.client.subscriptionstates.Created )


    def test_client_Client_register_subscriptionstatus_for_clientsubscriptionhandle_and_monitor_node(self):
        cbc = CallbackClass()
        # since we created a new client, the clientSubscriptionHandle will be 0:
        clientSubscriptionHandle = 0
        self.client.registerSubscriptionStatusCallback(cbc.callback, onlyClientSubscriptionHandle = clientSubscriptionHandle)

        result = self.client.createMonitoredData(self.address)
        self.assertTrue( result.targets[0].status.isGood() )

        # the callbacks may be dispatched in a separate Python thread, which may not be completed
        # yet, so we must wait for them!
        t_end = time.time() + 1.0 # 1 sec timeout
        while time.time() < t_end and not (self.client.isCallbackCalled() and cbc.isCallbackCalled()):
            time.sleep(0.001) # do nothing, just wait

        for source in [self.client, cbc]:
            self.assertTrue( source.isCallbackCalled() )
            self.assertEqual( source.infoList[0].clientSubscriptionHandle, clientSubscriptionHandle)
            self.assertEqual( source.infoList[0].subscriptionState, pyuaf.client.subscriptionstates.Created )


    def tearDown(self):
        # delete the client instances manually (now!) instead of letting them be garbage collected
        # automatically (which may happen during a another test, and which may cause logging output
        # of the destruction to be mixed with the logging output of the other test).
        del self.client


if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())