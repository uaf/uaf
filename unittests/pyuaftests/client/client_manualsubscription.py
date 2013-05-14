import pyuaf
import time
import thread

from .. import testresults

def test(args):
    
    print("client.client_manualsubscription")
    
    
    # create a new ClientSettings instance and add the localhost to the URLs to discover
    settings = pyuaf.client.settings.ClientSettings()
    settings.discoveryUrls.append(args.demo_url)
    settings.applicationName = "client"
    settings.logToStdOutLevel = args.loglevel
    
    client = pyuaf.client.Client(settings)

    serverUri = args.demo_server_uri
    
    # create a new SessionSettings instance
    sessionSettings = pyuaf.client.settings.SessionSettings()
    
    # create new SubscriptionSettings instances
    subscriptionSettings0 = pyuaf.client.settings.SubscriptionSettings()
    
    
    print(" - testing pyuaf.client.Client().manuallySubscribe()")
    
    clientConnectionId0 = client.manuallyConnect(serverUri, sessionSettings)
    
    assert clientConnectionId0 == 0
    
    clientSubscriptionHandle0 = client.manuallySubscribe(clientConnectionId0, subscriptionSettings0)
    
    if args.verbose:
        print(client.allSubscriptionInformations())
    
    assert clientSubscriptionHandle0 == 0
    
    assert client.subscriptionInformation(0).subscriptionState == pyuaf.client.subscriptionstates.Created
    
    client.manuallyUnsubscribe(clientConnectionId0, clientSubscriptionHandle0)
    
    
    # delete the client instances manually (now!) instead of letting them be garbage collected 
    # automatically (which may happen during a another test, and which may cause logging output
    # of the destruction to be mixed with the logging output of the other test).
    del client
    