import pyuaf
import unittest
from pyuaf.util.unittesting import parseArgs, TestResults
import time
import _thread, threading



ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args

    return unittest.TestLoader().loadTestsFromTestCase(ClientManualConnectionTest)



def connect(c, uri, i, unique, results):
    try:
        sessionSettings = pyuaf.client.settings.SessionSettings()
        # create a session settings which is a unique for a given 'i' parameter
        if unique:
            sessionSettings.sessionTimeoutSec = 1 + 0.01 * i

        # connect the session
        id = c.manuallyConnect(uri, sessionSettings)

        # store the id
        results.appendToList("id", id)

    except Exception as e:
        results.fail()
    finally:
        results.finish()

def disconnect(c, id, results):
    try:
        c.manuallyDisconnect(id)
        results.removeFromList("id", id)

    except Exception as e:
        results.fail()
    finally:
        results.finish()


class ClientManualConnectionTest(unittest.TestCase):

    def setUp(self):
        # create a new ClientSettings instance and add the localhost to the URLs to discover
        settings = pyuaf.client.settings.ClientSettings()
        settings.discoveryUrls.append(ARGS.demo_url)
        settings.applicationName = "client"
        settings.logToStdOutLevel = ARGS.loglevel

        self.client = pyuaf.client.Client(settings)

        # create new SessionSettings instances
        self.sessionSettings0 = pyuaf.client.settings.SessionSettings()
        self.sessionSettings1 = pyuaf.client.settings.SessionSettings()
        self.sessionSettings1.sessionTimeoutSec = 0.12345
        self.sessionSettings1.lastConnectionAttemptTime = pyuaf.util.DateTime()
        self.sessionSettings1.lastConnectionAttemptStatus = pyuaf.util.Status()


    def help_manuallyConnect(self):
        self.clientConnectionId0 = self.client.manuallyConnect(ARGS.demo_server_uri, self.sessionSettings0)
        self.clientConnectionId1 = self.client.manuallyConnect(ARGS.demo_server_uri, self.sessionSettings1)

    def test_client_Client_manualconnection(self):
        self.help_manuallyConnect()
        self.assertEqual( self.clientConnectionId0 , 0 )
        self.assertEqual( self.clientConnectionId1 , 1 )

    def test_client_Client_sessionInformation(self):
        self.help_manuallyConnect()
        info0 = self.client.sessionInformation(self.clientConnectionId0)
        info1 = self.client.sessionInformation(self.clientConnectionId1)

        self.assertEqual( info0 , pyuaf.client.SessionInformation(self.clientConnectionId0, pyuaf.client.sessionstates.Connected, pyuaf.util.serverstates.Running, ARGS.demo_server_uri, self.sessionSettings0, pyuaf.client.connectionsteps.ActivateSession, info0.lastConnectionAttemptStatus) )
        self.assertEqual( info1 , pyuaf.client.SessionInformation(self.clientConnectionId1, pyuaf.client.sessionstates.Connected , pyuaf.util.serverstates.Running, ARGS.demo_server_uri, self.sessionSettings1, pyuaf.client.connectionsteps.ActivateSession, info1.lastConnectionAttemptStatus) )

    def test_client_Client_allSessionInformations(self):
        self.help_manuallyConnect()
        info0 = self.client.sessionInformation(self.clientConnectionId0)
        info1 = self.client.sessionInformation(self.clientConnectionId1)

        self.assertEqual( self.client.allSessionInformations() , [info0, info1] )

    def test_client_Client_manuallyDisconnect(self):
        self.help_manuallyConnect()

        self.client.manuallyDisconnect(self.clientConnectionId0)

        self.assertEqual( len(self.client.allSessionInformations()) , 1 )

        self.client.manuallyDisconnect(self.clientConnectionId1)

        self.assertEqual( len(self.client.allSessionInformations()) , 0 )

    def test_client_Client_manuallyConnect_and_manuallyDisconnect_many_times_in_a_row(self):
        testResults = TestResults(30)
        testResults.initializeList("id")

        for i in range(testResults.total()):
            clientConnectionId = self.client.manuallyConnect(ARGS.demo_server_uri, self.sessionSettings0)
            self.assertEqual( self.client.sessionInformation(clientConnectionId).clientConnectionId , clientConnectionId )
            self.client.manuallyDisconnect(clientConnectionId)


    def help_createManySessions(self, res):
        for i in range(res.total()):
            _thread.start_new_thread(connect, (self.client, ARGS.demo_server_uri, i, True, res))

        t_timeout = time.time() + 10.0
        while time.time() < t_timeout and res.finished() < res.total():
            time.sleep(0.01)


    def test_client_Client_manuallyConnect_many_times_in_parallel_unique(self):
        testResults = TestResults(30)
        testResults.initializeList("id")

        self.help_createManySessions(testResults)

        # check if no error occurred during the connection
        self.assertEqual( testResults.failed() , 0 )

        # check if we now have sufficient unique sessions
        self.assertEqual( len(self.client.allSessionInformations()) , testResults.total() )

        # check if the ids list has the correct number of ids
        self.assertEqual( len(testResults.getListCopy("id")) , testResults.total() )

    def test_client_Client_manuallyDisconnect_many_times_in_parallel_unique(self):
        testResults = TestResults(30)
        testResults.initializeList("id")

        self.help_createManySessions(testResults)

        # make sure testResults.finished() is reset (i.e. 0 again)
        testResults.clear()

        idsCopy = testResults.getListCopy("id")

        for id in idsCopy:
            _thread.start_new_thread(disconnect, (self.client, id, testResults))

        t_timeout = time.time() + 10.0
        while time.time() < t_timeout and testResults.finished() < testResults.total():
            time.sleep(0.01)

        # check if no error occurred during the connection
        self.assertEqual( testResults.failed() , 0 )

        # check if we now have 0 sessions
        self.assertEqual( len(self.client.allSessionInformations()) , 0 )


        # the ids list should also be empty:
        self.assertEqual( testResults.getListCopy("id") , [] )

    def test_client_Client_manuallyConnect_many_times_in_parallel_non_unique(self):
        testResults = TestResults(30)
        testResults.initializeList("id")

        for i in range(testResults.total()):
            _thread.start_new_thread(connect, (self.client, ARGS.demo_server_uri, i, False, testResults))

        t_timeout = time.time() + 10.0
        while time.time() < t_timeout and testResults.finished() < testResults.total():
            time.sleep(0.01)

        # check if no error occurred during the connection
        self.assertEqual( testResults.failed() , 0 )

        # check if we now have 1 session
        self.assertEqual( len(self.client.allSessionInformations()) , 1 )

    def tearDown(self):
        # delete the client instances manually (now!) instead of letting them be garbage collected
        # automatically (which may happen during a another test, and which may cause logging output
        # of the destruction to be mixed with the logging output of the other test).
        del self.client

if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())
