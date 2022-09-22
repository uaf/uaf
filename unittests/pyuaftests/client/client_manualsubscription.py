import pyuaf
import time
import _thread, threading
import unittest
from pyuaf.util.unittesting import parseArgs, TestResults


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args

    return unittest.TestLoader().loadTestsFromTestCase(ClientManualSubscriptionTest)


class ClientManualSubscriptionTest(unittest.TestCase):

    def setUp(self):
        # create a new ClientSettings instance and add the localhost to the URLs to discover
        settings = pyuaf.client.settings.ClientSettings()
        settings.discoveryUrls.append(ARGS.demo_url)
        settings.applicationName = "client"
        settings.logToStdOutLevel = ARGS.loglevel

        self.client = pyuaf.client.Client(settings)

        # create new SessionSettings instances
        self.sessionSettings = pyuaf.client.settings.SessionSettings()

        # create new SubscriptionSettings instances
        self.subscriptionSettings0 = pyuaf.client.settings.SubscriptionSettings()

        self.clientConnectionId0 = -1
        self.clientSubscriptionHandle0 = -1

    def connect(self):
        self.clientConnectionId0 = self.client.manuallyConnect(ARGS.demo_server_uri, self.sessionSettings)

    def subscribe(self):
        self.clientSubscriptionHandle0 = self.client.manuallySubscribe(self.clientConnectionId0, self.subscriptionSettings0)

    def unsubscribe(self):
        self.client.manuallyUnsubscribe(self.clientConnectionId0, self.clientSubscriptionHandle0)


    def test_client_Client_manualsubscription(self):
        self.connect()
        self.assertEqual( self.clientConnectionId0 , 0 )

        self.subscribe()
        self.assertEqual( self.clientSubscriptionHandle0 , 0 )
        self.assertEqual( self.client.subscriptionInformation(0).subscriptionState , pyuaf.client.subscriptionstates.Created )

    def test_client_Client_manualunsubscription(self):
        self.connect()
        self.subscribe()
        self.assertEqual( len(self.client.allSubscriptionInformations()), 1 )

        self.unsubscribe()

        self.assertEqual( len(self.client.allSubscriptionInformations()), 0 )


    def tearDown(self):
        # delete the client instances manually (now!) instead of letting them be garbage collected
        # automatically (which may happen during a another test, and which may cause logging output
        # of the destruction to be mixed with the logging output of the other test).
        del self.client

if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())
