import pyuaf
import time
import _thread, threading
import unittest
from pyuaf.util.unittesting import parseArgs

from pyuaf.util import NodeId, Address, ExpandedNodeId, BrowsePath, \
                       RelativePathElement, QualifiedName, opcuaidentifiers, attributeids, EventFilter
from pyuaf.util.primitives import Boolean, UInt32, Double
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
        self.address_Method   = Address(ExpandedNodeId("Demo.Method", demoNsUri, self.serverUri))
        self.address_Multiply = Address(ExpandedNodeId("Demo.Method.Multiply", demoNsUri, self.serverUri))
        self.address_Alarms = Address(ExpandedNodeId("AlarmsWithNodes", demoNsUri, self.serverUri))

        readResult = self.client.read(self.addresses)
        self.values = [readResult.targets[0].data, readResult.targets[1].data]

        del self.client
        self.client = pyuaf.client.Client(settings)



    def test_Client_kwargs_read(self):
        self.doAllTests("read")

    def test_Client_kwargs_beginRead(self):
        self.doAllTests("beginRead")

    def test_Client_kwargs_write(self):
        self.doAllTests("write")

    def test_Client_kwargs_beginWrite(self):
        self.doAllTests("beginWrite")

    def test_Client_kwargs_call(self):
        self.doAllTests("call")

    def test_Client_kwargs_beginCall(self):
        self.doAllTests("beginCall")

    def test_Client_kwargs_browse(self):
        self.doAllTests("browse")

    def test_Client_kwargs_createMonitoredData(self):
        self.doAllTests("createMonitoredData")

    def test_Client_kwargs_createMonitoredEvents(self):
        self.doAllTests("createMonitoredEvents")

    def doAllTests(self, service):
        self.do_test_client_Client_kwargs_defaultSessionSettings(service)
        self.tearDown()
        self.setUp()
        self.do_test_client_Client_kwargs_specificSessionSettings(service)
        self.tearDown()
        self.setUp()
        self.do_test_client_Client_kwargs_clientConnectionId_wrong(service)
        self.tearDown()
        self.setUp()
        self.do_test_client_Client_kwargs_clientConnectionId(service)
        self.tearDown()
        self.setUp()
        self.do_test_client_Client_kwargs_sessionSettings(service)
        if service in [ "createMonitoredData", "createMonitoredEvents" ]:
            self.tearDown()
            self.setUp()
            self.do_test_client_Client_kwargs_defaultSubscriptionSettings(service)
            self.tearDown()
            self.setUp()
            self.do_test_client_Client_kwargs_clientSubscriptionHandle_wrong(service)
            self.tearDown()
            self.setUp()
            self.do_test_client_Client_kwargs_clientSubscriptionHandle(service)
            self.tearDown()
            self.setUp()
            self.do_test_client_Client_kwargs_subscriptionSettings(service)

    def doService(self, service, **kwargs):
        if service == "read":
            return self.client.read(self.addresses, **kwargs)
        elif service == "beginRead":
            result = self.client.beginRead(self.addresses, **kwargs)
            time.sleep(0.1) # wait for async responses
            return result
        elif service == "write":
            return self.client.write(self.addresses, self.values, **kwargs)
        elif service == "beginWrite":
            result = self.client.beginWrite(self.addresses, self.values, **kwargs)
            time.sleep(0.1) # wait for async responses
            return result
        elif service == "call":
            return self.client.call(self.address_Method, self.address_Multiply, [Double(2.0), Double(3.0)], **kwargs)
        elif service == "beginCall":
            result = self.client.beginCall(self.address_Method, self.address_Multiply, [Double(2.0), Double(3.0)], **kwargs)
            time.sleep(0.1) # wait for async responses
            return result
        elif service == "browse":
            return self.client.browse(self.addresses, **kwargs)
        elif service == "createMonitoredData":
            return self.client.createMonitoredData(self.addresses, **kwargs)
        elif service == "createMonitoredEvents":
            return self.client.createMonitoredEvents([self.address_Alarms], **kwargs)



    def do_test_client_Client_kwargs_defaultSessionSettings(self, service):
        clientSettings = self.client.clientSettings()
        clientSettings.defaultSessionSettings.connectTimeoutSec = 4.0
        self.client.setClientSettings(clientSettings)
        result = self.doService(service)
        self.assertTrue(result.overallStatus.isGood())
        allSessionInfos = self.client.allSessionInformations()
        self.assertEqual(len(allSessionInfos), 1)
        self.assertEqual(allSessionInfos[0].sessionSettings, clientSettings.defaultSessionSettings)
        # check if the session is reused
        result = self.doService(service)
        self.assertTrue(result.overallStatus.isGood())
        self.assertEqual(len(allSessionInfos), 1)


    def do_test_client_Client_kwargs_defaultSubscriptionSettings(self, service):
        clientSettings = self.client.clientSettings()
        clientSettings.defaultSubscriptionSettings.connectTimeoutSec = 4.0
        self.client.setClientSettings(clientSettings)
        result = self.doService(service)
        self.assertTrue(result.overallStatus.isGood())
        allSubscriptionInfos = self.client.allSubscriptionInformations()
        self.assertEqual(len(allSubscriptionInfos), 1)
        self.assertEqual(allSubscriptionInfos[0].subscriptionSettings, clientSettings.defaultSubscriptionSettings)
        # check if the subscription is reused
        result = self.doService(service)
        self.assertTrue(result.overallStatus.isGood())
        self.assertEqual(len(allSubscriptionInfos), 1)


    def do_test_client_Client_kwargs_specificSessionSettings(self, service):
        clientSettings = self.client.clientSettings()
        clientSettings.specificSessionSettings[self.serverUri] = SessionSettings()
        clientSettings.specificSessionSettings[self.serverUri].connectTimeoutSec = 6.0
        self.client.setClientSettings(clientSettings)
        result = self.doService(service)
        self.assertTrue(result.overallStatus.isGood())
        allSessionInfos = self.client.allSessionInformations()
        self.assertEqual(len(allSessionInfos), 1)
        self.assertEqual(allSessionInfos[0].sessionSettings, clientSettings.specificSessionSettings[self.serverUri])
        self.assertNotEqual(allSessionInfos[0].sessionSettings, clientSettings.defaultSessionSettings)
        # check if the session is reused
        result = self.doService(service)
        self.assertTrue(result.overallStatus.isGood())
        self.assertEqual(len(allSessionInfos), 1)

    def do_test_client_Client_kwargs_clientConnectionId_wrong(self, service):
        try:
            raised = False
            result = self.doService(service, clientConnectionId = 0)
        except pyuaf.util.errors.UnknownClientConnectionIdError:
            raised = True
        except pyuaf.util.errors.CreateMonitoredItemsError:
            raised = True
        self.assertTrue(raised)

    def do_test_client_Client_kwargs_clientSubscriptionHandle_wrong(self, service):
        try:
            result1 = self.doService(service)
            raised = False
            result = self.doService(service, clientConnectionId = 0, clientSubscriptionHandle = 1)
        except pyuaf.util.errors.CreateMonitoredItemsError:
            raised = True
        self.assertTrue(raised)


    def do_test_client_Client_kwargs_clientConnectionId(self, service):
        result1 = self.doService(service)
        self.assertTrue(result1.overallStatus.isGood())
        result2 = self.doService(service, clientConnectionId = 0)
        self.assertTrue(result2.overallStatus.isGood())
        try:
            raised = False
            self.doService(service, clientConnectionId = 1)
        except pyuaf.util.errors.UnknownClientConnectionIdError:
            raised = True
        except pyuaf.util.errors.CreateMonitoredItemsError:
            raised = True
        self.assertTrue(raised)


    def do_test_client_Client_kwargs_clientSubscriptionHandle(self, service):
        result1 = self.doService(service)
        self.assertTrue(result1.overallStatus.isGood())
        result2 = self.doService(service, clientConnectionId = 0, clientSubscriptionHandle = 0)
        self.assertTrue(result2.overallStatus.isGood())
        try:
            raised = False
            self.doService(service, clientConnectionId = 0, clientSubscriptionHandle = 1)
        except pyuaf.util.errors.CreateMonitoredItemsError:
            raised = True
        self.assertTrue(raised)


    def do_test_client_Client_kwargs_sessionSettings(self, service):
        sessionSettings = SessionSettings()
        sessionSettings.connectTimeoutSec = 5.0

        result = self.doService(service, sessionSettings = sessionSettings)
        self.assertTrue(result.overallStatus.isGood())
        allSessionInfos = self.client.allSessionInformations()
        self.assertEqual(len(allSessionInfos), 1)
        self.assertEqual(allSessionInfos[0].sessionSettings, sessionSettings)
        # check if the following session is reused
        result = self.doService(service, sessionSettings = sessionSettings)
        self.assertTrue(result.overallStatus.isGood())
        allSessionInfos = self.client.allSessionInformations()
        self.assertEqual(len(allSessionInfos), 1)
        self.assertEqual(allSessionInfos[0].sessionSettings, sessionSettings)
        self.assertEqual(result.targets[0].clientConnectionId, 0)
        # check if the following session is not reused
        sessionSettings2 = SessionSettings()
        sessionSettings2.connectTimeoutSec = 6.0
        result = self.doService(service, sessionSettings = sessionSettings2)
        self.assertTrue(result.overallStatus.isGood())
        allSessionInfos = self.client.allSessionInformations()
        self.assertEqual(len(allSessionInfos), 2)
        self.assertEqual(allSessionInfos[1].sessionSettings, sessionSettings2)
        self.assertEqual(result.targets[0].clientConnectionId, 1)
        # check if the following session is not reused
        sessionSettings.unique = True
        result = self.doService(service, sessionSettings = sessionSettings)
        self.assertTrue(result.overallStatus.isGood())
        allSessionInfos = self.client.allSessionInformations()
        self.assertEqual(len(allSessionInfos), 3)
        self.assertEqual(allSessionInfos[2].sessionSettings, sessionSettings)
        self.assertEqual(result.targets[0].clientConnectionId, 2)
        # check if the following session is not reused
        result = self.doService(service, sessionSettings = sessionSettings)
        self.assertTrue(result.overallStatus.isGood())
        allSessionInfos = self.client.allSessionInformations()
        self.assertEqual(len(allSessionInfos), 4)
        self.assertEqual(allSessionInfos[3].sessionSettings, sessionSettings)
        self.assertEqual(result.targets[0].clientConnectionId, 3)
        # check if a specific ClientConnectionId may be reused:
        result = self.doService(service, clientConnectionId = 3)
        self.assertTrue(result.overallStatus.isGood())
        allSessionInfos = self.client.allSessionInformations()
        self.assertEqual(len(allSessionInfos), 4)
        self.assertEqual(result.targets[0].clientConnectionId, 3)


    def do_test_client_Client_kwargs_subscriptionSettings(self, service):
        subscriptionSettings = SubscriptionSettings()
        subscriptionSettings.maxNotificationsPerPublish = 111
        result = self.doService(service, subscriptionSettings = subscriptionSettings)
        self.assertTrue(result.overallStatus.isGood())
        allSubscriptionInfos = self.client.allSubscriptionInformations()
        self.assertEqual(len(allSubscriptionInfos), 1)
        self.assertEqual(allSubscriptionInfos[0].subscriptionSettings, subscriptionSettings)
        # check if the following subscription is reused
        result = self.doService(service, subscriptionSettings = subscriptionSettings)
        self.assertTrue(result.overallStatus.isGood())
        allSubscriptionInfos = self.client.allSubscriptionInformations()
        self.assertEqual(len(allSubscriptionInfos), 1)
        self.assertEqual(allSubscriptionInfos[0].subscriptionSettings, subscriptionSettings)
        self.assertEqual(result.targets[0].clientSubscriptionHandle, 0)
        # check if the following subscription is not reused
        subscriptionSettings2 = SubscriptionSettings()
        subscriptionSettings2.connectTimeoutSec = 6.0
        result = self.doService(service, subscriptionSettings = subscriptionSettings2)
        self.assertTrue(result.overallStatus.isGood())
        allSubscriptionInfos = self.client.allSubscriptionInformations()
        self.assertEqual(len(allSubscriptionInfos), 2)
        self.assertEqual(allSubscriptionInfos[1].subscriptionSettings, subscriptionSettings2)
        self.assertEqual(result.targets[0].clientSubscriptionHandle, 1)
        # check if the following subscription is not reused
        subscriptionSettings.unique = True
        result = self.doService(service, subscriptionSettings = subscriptionSettings)
        self.assertTrue(result.overallStatus.isGood())
        allSubscriptionInfos = self.client.allSubscriptionInformations()
        self.assertEqual(len(allSubscriptionInfos), 3)
        self.assertEqual(allSubscriptionInfos[2].subscriptionSettings, subscriptionSettings)
        self.assertEqual(result.targets[0].clientSubscriptionHandle, 2)
        # check if the following subscription is not reused
        result = self.doService(service, subscriptionSettings = subscriptionSettings)
        self.assertTrue(result.overallStatus.isGood())
        allSubscriptionInfos = self.client.allSubscriptionInformations()
        self.assertEqual(len(allSubscriptionInfos), 4)
        self.assertEqual(allSubscriptionInfos[3].subscriptionSettings, subscriptionSettings)
        self.assertEqual(result.targets[0].clientSubscriptionHandle, 3)
        # check if a specific clientSubscriptionHandle may be reused:
        result = self.doService(service, clientSubscriptionHandle = 3)
        self.assertTrue(result.overallStatus.isGood())
        allSubscriptionInfos = self.client.allSubscriptionInformations()
        self.assertEqual(len(allSubscriptionInfos), 4)
        self.assertEqual(result.targets[0].clientSubscriptionHandle, 3)




    def tearDown(self):
        # delete the client instances manually (now!) instead of letting them be garbage collected
        # automatically (which may happen during a another test, and which may cause logging output
        # of the destruction to be mixed with the logging output of the other test).
        del self.client


if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())