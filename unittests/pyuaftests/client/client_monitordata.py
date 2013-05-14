import pyuaf
import time
import threading
import sys

from .. import testresults

from pyuaf.util import NodeId, Address, ExpandedNodeId, BrowsePath, \
                       RelativePathElement, QualifiedName, opcuaidentifiers


class MyClient(pyuaf.client.Client):

    def __init__(self, settings, verbose):
        pyuaf.client.Client.__init__(self, settings)
        self.verbose = verbose
        self.noOfSuccessFullyReceivedNotifications = 0
        self.lock = threading.Lock()
            
    def dataChangesReceived(self, notifications):
        self.lock.acquire()
        self.noOfSuccessFullyReceivedNotifications += len(notifications)
        
        if self.verbose:
            print("***** dataChangesReceived started *****")
            for i in xrange(len(notifications)):
                print("Notification %d:" %i)
                print(notifications[i])
            print("***** dataChangesReceived finished *****")
        
        self.lock.release()


def test(args):
    
    print("client.client_monitordata")
    
    # create a new ClientSettings instance and add the localhost to the URLs to discover
    settings = pyuaf.client.settings.ClientSettings()
    settings.discoveryUrls.append(args.demo_url)
    settings.applicationName = "client"
    settings.logToStdOutLevel = args.loglevel
    
    client   = pyuaf.client.Client(settings)
    myClient = MyClient(settings, args.verbose)


    serverUri = args.demo_server_uri
    demoNsUri = args.demo_ns_uri
    plcOpenNsUri = "http://PLCopen.org/OpcUa/IEC61131-3/"
    
    address0 = Address(ExpandedNodeId("MyDemoObject.Counter", demoNsUri, serverUri))
    address1 = Address(ExpandedNodeId("MyDemoObject.Temperature", demoNsUri, serverUri))
    
    print(" - testing pyuaf.client.Client().createMonitoredData()")
    
    myClient.createMonitoredData([address0, address1])
    
    if args.verbose:
        print("Now waiting for some notifications")
    
    # after a few seconds we should AT LEAST have received 2 notifications
    
    t_timeout = time.time() + 5.0
    while time.time() < t_timeout and myClient.noOfSuccessFullyReceivedNotifications < 2:
        time.sleep(0.01)
    
    assert myClient.noOfSuccessFullyReceivedNotifications >= 2


    print(" - testing pyuaf.client.Client().createMonitoredData(..., [<callbackFunction>, <callbackFunction>])")
    
    # define a TestClass with a callback
    class TestClass:
        def __init__(self):
            self.noOfSuccessFullyReceivedNotifications = 0
            self.lock = threading.Lock() 
        
        def myCallback(self, notification):
            self.lock.acquire()
            self.noOfSuccessFullyReceivedNotifications += 1
            
            if args.verbose:
                print("--- Callback started ---")
                print(notification)
                print("--- Callback finished ---")
            
            self.lock.release()
    
    
    t = TestClass()
    
    # check if the argument are checked correctly
    try:
        e = None
        result = client.createMonitoredData([address0, address1], [t.myCallback, t.myCallback]) # wrong way of specifying the callbacks!!!
    except Exception, e:
        pass
    finally:
        assert type(e) == TypeError
    
    # check if the argument are checked correctly
    
    try:
        e = None
        result = client.createMonitoredData([address0, address1], notificationCallbacks=[t.myCallback]) # wrong: 2 callbacks required!!!
    except Exception, e:
        pass
    finally:
        assert type(e) == TypeError
    
    
    # now try again with the correct specification of the arguments
    
    result = client.createMonitoredData([address0, address1], notificationCallbacks=[t.myCallback, t.myCallback])
    
    if args.verbose:
        print("Now wait for some notifications")
    
    # after a few seconds we should AT LEAST have received 2 notifications
    
    t_timeout = time.time() + 5.0
    while time.time() < t_timeout and t.noOfSuccessFullyReceivedNotifications < 2:
        time.sleep(0.01)
    
    
    # delete the client instances manually (now!) instead of letting them be garbage collected 
    # automatically (which may happen during a another test, and which may cause logging output
    # of the destruction to be mixed with the logging output of the other test).
    del myClient
    del client
    