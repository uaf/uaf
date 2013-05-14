import pyuaf
import time
import thread, threading

from .. import testresults


def testConnection(c, uri, i, unique, results):
    try:
        sessionSettings = pyuaf.client.settings.SessionSettings()
        # create a session settings which is a unique for a given 'i' parameter
        if unique:
            sessionSettings.sessionTimeoutSec = 1 + 0.01 * i
            
        # connect the session
        id = c.manuallyConnect(uri, sessionSettings)
        
        # check if the session information is correct
        assert c.sessionInformation(id).clientConnectionId == id
        
        # store the id
        results.appendToList("id", id)
        
    except Exception, e:
        print("Unexpected error for the connection: %s" %e)
        results.fail()
    finally:
        results.finish()

def testDisconnection(c, id, results):
    try:
        c.manuallyDisconnect(id)
        
        results.removeFromList("id", id)
        
    except Exception, e:
        print("Unexpected error for the disconnection: %s" %e)
        results.fail()
    finally:
        results.finish()
        

            
def test(args):
    
    print("client.client_manualconnection")
    
    # create a new ClientSettings instance and add the localhost to the URLs to discover
    settings = pyuaf.client.settings.ClientSettings()
    settings.discoveryUrls.append(args.demo_url)
    settings.applicationName = "client"
    settings.logToStdOutLevel = args.loglevel
    
    client = pyuaf.client.Client(settings)

    # create new SessionSettings instances
    sessionSettings0 = pyuaf.client.settings.SessionSettings()
    sessionSettings1 = pyuaf.client.settings.SessionSettings()
    sessionSettings1.sessionTimeoutSec = 0.12345
    
    print(" - testing pyuaf.client.Client().manuallyConnect() with modified discoveryUrls")
    
    URI = "urn:UnifiedAutomation:UaDemoserver"
    
    clientConnectionId0 = client.manuallyConnect(URI, sessionSettings0)
    
    assert clientConnectionId0 == 0
    
    clientConnectionId1 = client.manuallyConnect(URI, sessionSettings1)
    
    assert clientConnectionId1 == 1
    
    print(" - testing pyuaf.client.Client().sessionInformation()")
    
    
    info0 = client.sessionInformation(clientConnectionId0)
    
    if args.verbose:
        print("info0: ")
        print(info0)
    
    assert info0 == pyuaf.client.SessionInformation(clientConnectionId0, pyuaf.client.sessionstates.Connected, URI)
    
    info1 = client.sessionInformation(clientConnectionId1)
    
    if args.verbose:
        print("info1: ")
        print(info1)
    
    assert info1 == pyuaf.client.SessionInformation(pyuaf.client.sessionstates.Connected, clientConnectionId1, URI)
    
    print(" - testing pyuaf.client.Client().allSessionInformations()")
    
    assert client.allSessionInformations() == [info0, info1]
    
    if args.verbose:
        print client.allSessionInformations()
    
    
    print(" - testing pyuaf.client.Client().manuallyDisconnect()")
    
    client.manuallyDisconnect(clientConnectionId0)
    
    assert client.allSessionInformations() == [info1]
    
    client.manuallyDisconnect(clientConnectionId1)
    
    assert client.allSessionInformations() == []
    
    
    testResults = testresults.TestResults(30)
    testResults.initializeList("id")
    
    
    print(" - testing pyuaf.client.Client().manuallyConnect() and manuallyDisconnect() %d times in a row" %testResults.total())
    for i in xrange(testResults.total()):
        clientConnectionId = client.manuallyConnect(URI, sessionSettings0)
        assert client.sessionInformation(clientConnectionId).clientConnectionId == clientConnectionId
        client.manuallyDisconnect(clientConnectionId)
    
    print(" - testing pyuaf.client.Client().manuallyConnect() %d times in parallel (only unique sessions)" %testResults.total())
    
    testResults.clear()
    
    for i in xrange(testResults.total()):
        thread.start_new_thread(testConnection, (client, URI, i, True, testResults))
    
    t_timeout = time.time() + 10.0
    while time.time() < t_timeout and testResults.finished() < testResults.total():
        time.sleep(0.01)
    
    # check if no error occurred during the connection
    assert testResults.failed() == 0
    
    # check if we now have sufficient unique sessions
    assert len(client.allSessionInformations()) == testResults.total()
    
    # check if the ids list has the correct number of ids
    assert len(testResults.getListCopy("id")) == testResults.total()
    
    print(" - testing pyuaf.client.Client().manuallyDisconnect() %d times in parallel (only unique sessions)" %testResults.total())
    
    testResults.clear()
    
    idsCopy = testResults.getListCopy("id")
    
    for id in idsCopy:
        thread.start_new_thread(testDisconnection, (client, id, testResults))
    
    t_timeout = time.time() + 10.0
    while time.time() < t_timeout and testResults.finished() < testResults.total():
        time.sleep(0.01)
    
    # check if no error occurred during the connection
    assert testResults.failed() == 0
    
    # check if we now have 0 sessions
    assert len(client.allSessionInformations()) == 0
    
    # the ids list should also be empty:
    assert testResults.getListCopy("id") == []
    
    print(" - testing pyuaf.client.Client().manuallyConnect() %d times in parallel (non-unique sessions)" %testResults.total())
    
    testResults.clear()
    
    for i in xrange(testResults.total()):
        thread.start_new_thread(testConnection, (client, URI, i, False, testResults))
    
    t_timeout = time.time() + 10.0
    while time.time() < t_timeout and testResults.finished() < testResults.total():
        time.sleep(0.01)
    
    # check if no error occurred during the connection
    assert testResults.failed() == 0
    
    # check if we now have 1 session
    assert len(client.allSessionInformations()) == 1
    
    # delete the client instances manually (now!) instead of letting them be garbage collected 
    # automatically (which may happen during a another test, and which may cause logging output
    # of the destruction to be mixed with the logging output of the other test).
    del client
    