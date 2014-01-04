import pyuaf
import unittest
from pyuaf.util.unittesting import parseArgs, TestResults
import thread, time


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(ClientDiscoveryTest)

    

def testParallel(c, results):
    try:
        c.findServersNow()
    except pyuaf.util.errors.DiscoveryError:
        pass
    except pyuaf.util.errors.InvalidRequestError:
        pass
    except Exception, e:
        print("Unexpected error for this test: %s %s" %(type(e), e))
        results.fail()
    finally:
        results.finish()


def isDemoServerFound(descriptions):
    for desc in descriptions:
        if desc.applicationUri == ARGS.demo_server_uri:
            return True
    
    return False


class ClientDiscoveryTest(unittest.TestCase):
    
    def setUp(self):
        self.client = pyuaf.client.Client()
        
        # create a new ClientSettings instance and add the localhost to the URLs to discover
        self.settings = pyuaf.client.settings.ClientSettings()
        self.settings.discoveryUrls.append(ARGS.demo_url)
        self.settings.applicationName = "client"
        self.settings.logToStdOutLevel = ARGS.loglevel
        
    def test_client_Client_serversFound_after_setClientSettings(self):
        # update the settings of the client, and therefore provoke a new FindServers invocation
        self.client.setClientSettings(self.settings)
        
        self.assertTrue( isDemoServerFound(self.client.serversFound()),
                         "The demo server (uaservercpp) could not be discovered! "
                         "Make sure that it's running and properly configured!")

    
    def test_client_Client_findServersNow_100_times_in_parallel(self):
        testResults = TestResults(100)
        
        for i in xrange(testResults.total()):
            thread.start_new_thread(testParallel, (self.client, testResults))
            
        # wait until all tests have finished
        t_timeout = time.time() + 5.0
        while time.time() < t_timeout and testResults.finished() < testResults.total():
            time.sleep(0.1)
            
        self.assertEqual( testResults.failed() , 0 )

    def test_client_Client_setClientSettings_without_discoveryUrls(self):
        self.assertFalse( isDemoServerFound(self.client.serversFound()) )
    
    
    def tearDown(self):
        # delete the client instances manually (now!) instead of letting them be garbage collected 
        # automatically (which may happen during a another test, and which may cause logging output
        # of the destruction to be mixed with the logging output of the other test).
        del self.client
        
if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())
