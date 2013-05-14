import pyuaf
import time
import threading
import sys

from .. import testresults

from pyuaf.util import NodeId, Address, ExpandedNodeId, BrowsePath, \
                       RelativePathElement, QualifiedName
from pyuaf.util import opcuaidentifiers
from pyuaf.util import attributeids
from pyuaf.util import EventFilter, SimpleAttributeOperand
from pyuaf.util.primitives import Int32


class MyClient(pyuaf.client.Client):

    def __init__(self, settings, verbose):
        pyuaf.client.Client.__init__(self, settings)
        self.verbose = verbose
        self.noOfSuccessFullyReceivedNotifications = 0
        self.lock = threading.Lock()
            
    def eventsReceived(self, notifications):
        self.lock.acquire()
        self.noOfSuccessFullyReceivedNotifications += len(notifications)
        
        if self.verbose:
            print("***** eventsReceived started *****")
            for i in xrange(len(notifications)):
                print("Notification %d:" %i)
                print(notifications[i])
            print("***** eventsReceived finished *****")
        
        self.lock.release()



def test(args):
    
    
    print("client.client_monitorevents")
    
    serverUri = args.demo_server_uri
    demoNsUri = args.demo_ns_uri
    plcOpenNsUri = "http://PLCopen.org/OpcUa/IEC61131-3/"
    
    myDemoObject = Address(ExpandedNodeId("MyDemoObject", demoNsUri, serverUri))
    setAllValues = Address(myDemoObject, [RelativePathElement(QualifiedName("SetAllValues", demoNsUri))])
    
    
    
    # create a new ClientSettings instance and add the localhost to the URLs to discover
    mySettings = pyuaf.client.settings.ClientSettings()
    mySettings.applicationName = "myClient"
    mySettings.discoveryUrls.append(args.demo_url)
    mySettings.logToStdOutLevel = args.loglevel
    myClient = MyClient(mySettings, args.verbose)
    
    
    eventFilter = EventFilter()
    eventFilter.selectClauses.resize(3)
    eventFilter.selectClauses[0].attributeId = attributeids.Value
    eventFilter.selectClauses[0].browsePath.append(QualifiedName("Message", 0))
    eventFilter.selectClauses[0].typeId = NodeId(opcuaidentifiers.OpcUaId_BaseEventType, 0)
    eventFilter.selectClauses[1].attributeId = attributeids.Value
    eventFilter.selectClauses[1].browsePath.append(QualifiedName("SourceName", 0))
    eventFilter.selectClauses[1].typeId = NodeId(opcuaidentifiers.OpcUaId_BaseEventType, 0)
    eventFilter.selectClauses[2].attributeId = attributeids.Value
    eventFilter.selectClauses[2].browsePath.append(QualifiedName("Severity", 0))
    eventFilter.selectClauses[2].typeId = NodeId(opcuaidentifiers.OpcUaId_BaseEventType, 0)
    
    
    print(" - testing pyuaf.client.Client().createMonitoredEvents()")
    
    myClient.createMonitoredEvents([myDemoObject], eventFilter)
    
    
    if args.verbose:
        print("Now calling a method that triggers events, and waiting for some notifications")
    
    myClient.call(myDemoObject, setAllValues, [Int32(123456)])
    
    # after a few seconds we should AT LEAST have received 2 notifications
    
    t_timeout = time.time() + 5.0
    while time.time() < t_timeout and myClient.noOfSuccessFullyReceivedNotifications < 2:
        time.sleep(0.01)
    
    assert myClient.noOfSuccessFullyReceivedNotifications >= 2
    
    
    print(" - testing pyuaf.client.Client().createMonitoredData(..., [<callbackFunction>, <callbackFunction>])")
    
    settings = pyuaf.client.settings.ClientSettings()
    settings.applicationName = "client"
    settings.discoveryUrls.append(args.demo_url)
    settings.logToStdOutLevel = args.loglevel
    client = pyuaf.client.Client(settings)
    
    # define a TestClass with a callback
    class TestClass:
        def __init__(self):
            self.noOfSuccessFullyReceivedNotifications = 0
            self.lock = threading.Lock() 
        
        def someCallback(self, notification):
            self.lock.acquire()
            self.noOfSuccessFullyReceivedNotifications += 1
            
            if args.verbose:
                print("--- Callback started ---")
                print(notification)
                print("--- Callback finished ---")
            
            self.lock.release()
    
    
    t = TestClass()
    
    result = client.createMonitoredEvents([myDemoObject], eventFilter, notificationCallbacks=[t.someCallback])
    
    if args.verbose:
        print("Now calling a method that triggers events, and waiting for some notifications")
    
    client.call(myDemoObject, setAllValues, [Int32(500)])
    
    # after a few seconds we should AT LEAST have received 2 notifications
    
    t_timeout = time.time() + 5.0
    while time.time() < t_timeout and t.noOfSuccessFullyReceivedNotifications < 2:
        time.sleep(0.01)
    
    assert t.noOfSuccessFullyReceivedNotifications >= 2
    
    # delete the client instances manually (now!) instead of letting them be garbage collected 
    # automatically (which may happen during a another test, and which may cause logging output
    # of the destruction to be mixed with the logging output of the other test).
    del myClient
    del client
    