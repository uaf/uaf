import pyuaf
import time
import thread

from .. import testresults


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


def test(args):
    
    print("client.client_discovery")
    
    client = pyuaf.client.Client()
    
    # create a new ClientSettings instance and add the localhost to the URLs to discover
    settings = pyuaf.client.settings.ClientSettings()
    settings.discoveryUrls.append(args.demo_url)
    settings.applicationName = "client"
    settings.logToStdOutLevel = args.loglevel
    
    
    print(" - testing pyuaf.client.Client().setClientSettings() with modified discoveryUrls")
    
    # update the settings of the client, and therefore provoke a new FindServers invocation
    client.setClientSettings(settings)
    
    print(" - testing pyuaf.client.Client().serversFound()")
    
    if args.verbose:
        print client.serversFound()
    
    # check the result
    #assert len(client.serversFound()) == 1
    #assert client.serversFound()[0].applicationUri == "urn:UnifiedAutomation:UaDemoserver"
    
    
    print(" - testing pyuaf.client.Client().findServers()")
    client.findServersNow()
    
    testResults = testresults.TestResults(100)
    
    print(" - testing pyuaf.client.Client().findServers() %d times in parallel, as a stress test" %testResults.total())
    if args.verbose:
        print("   (Expect many Error messages!)")
    
    for i in xrange(testResults.total()):
        thread.start_new_thread(testParallel, (client, testResults))
    
    # wait until all tests have finished
    t_timeout = time.time() + 5.0
    while time.time() < t_timeout and testResults.finished() < testResults.total():
        time.sleep(0.1)
    
    assert testResults.failed() == 0
    
    print(" - testing pyuaf.client.Client().setClientSettings() with 0 discoveryUrls")
    
    # now do the same with an empty list
    settings.discoveryUrls.clear()
    client.setClientSettings(settings)
    assert len(client.serversFound()) == 0
    
    # delete the client instances manually (now!) instead of letting them be garbage collected 
    # automatically (which may happen during a another test, and which may cause logging output
    # of the destruction to be mixed with the logging output of the other test).
    del client
    
