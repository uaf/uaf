import pyuaf
import time
import threading
import sys
import unittest
from pyuaf.util.unittesting import parseArgs


from pyuaf.util import NodeId, Address, ExpandedNodeId, BrowsePath, \
                       RelativePathElement, QualifiedName
from pyuaf.util import opcuaidentifiers
from pyuaf.util import attributeids
from pyuaf.util import EventFilter, SimpleAttributeOperand
from pyuaf.util.primitives import Double


class MyClient(pyuaf.client.Client):

    def __init__(self, settings):
        pyuaf.client.Client.__init__(self, settings)
        self.noOfSuccessFullyReceivedNotifications = 0
        self.lock = threading.Lock()
            
    def eventsReceived(self, notifications):
        self.lock.acquire()
        self.noOfSuccessFullyReceivedNotifications += len(notifications)
        self.lock.release()


# define a TestClass with a callback
class TestClass:
    def __init__(self):
        self.noOfSuccessFullyReceivedNotifications = 0
        self.lock = threading.Lock() 
    
    def myCallback(self, notification):
        self.lock.acquire()
        self.noOfSuccessFullyReceivedNotifications += 1
        self.lock.release()


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(ClientMonitorEventsTest)



class ClientMonitorEventsTest(unittest.TestCase):
    
    
    def setUp(self):
        
        # create a new ClientSettings instance and add the localhost to the URLs to discover
        settings = pyuaf.client.settings.ClientSettings()
        settings.discoveryUrls.append(ARGS.demo_url)
        settings.applicationName = "client"
        settings.logToStdOutLevel = ARGS.loglevel
    
        self.client = MyClient(settings)

        
        serverUri    = ARGS.demo_server_uri
        demoNsUri    = ARGS.demo_ns_uri
        opcUaNsIndex = 0 # the namespace index of nodes defined by the OPC UA specs is always 0  
        
        
        self.address_Demo      = Address(ExpandedNodeId("Demo", demoNsUri, serverUri))
        self.address_Events    = Address(self.address_Demo,   [RelativePathElement(QualifiedName("Events"                    , demoNsUri))])
        self.address_Alarms    = Address(self.address_Events, [RelativePathElement(QualifiedName("AlarmsWithNodes"           , demoNsUri))] )
        self.address_Alarm     = Address(self.address_Alarms, [RelativePathElement(QualifiedName("ExclusiveLevelAlarm"       , demoNsUri))] )
        self.address_Trigger   = Address(self.address_Alarms, [RelativePathElement(QualifiedName("ExclusiveLevelAlarmTrigger", demoNsUri))] )
        self.address_LowLow    = Address(self.address_Alarm,  [RelativePathElement(QualifiedName("LowLowLimit"               , opcUaNsIndex))] )
        self.address_Low       = Address(self.address_Alarm,  [RelativePathElement(QualifiedName("LowLimit"                  , opcUaNsIndex))] )
        self.address_High      = Address(self.address_Alarm,  [RelativePathElement(QualifiedName("HighLimit"                 , opcUaNsIndex))] )
        self.address_HighHigh  = Address(self.address_Alarm,  [RelativePathElement(QualifiedName("HighHighLimit"             , opcUaNsIndex))] )
        
        
        # start the simulation (otherwise the dynamic variables won't change)
        res = self.client.read( [self.address_LowLow, self.address_Low, self.address_High, self.address_HighHigh] )
        
        self.assertTrue(res.overallStatus.isGood())
        
        self.lowLowLimit   = res.targets[0].data.value
        self.lowLimit      = res.targets[1].data.value
        self.highLimit     = res.targets[2].data.value
        self.highHighLimit = res.targets[3].data.value
    
        self.eventFilter = EventFilter()
        self.eventFilter.selectClauses.resize(3)
        self.eventFilter.selectClauses[0].attributeId = attributeids.Value
        self.eventFilter.selectClauses[0].browsePath.append(QualifiedName("Message", 0))
        self.eventFilter.selectClauses[0].typeId = NodeId(opcuaidentifiers.OpcUaId_BaseEventType, 0)
        self.eventFilter.selectClauses[1].attributeId = attributeids.Value
        self.eventFilter.selectClauses[1].browsePath.append(QualifiedName("SourceName", 0))
        self.eventFilter.selectClauses[1].typeId = NodeId(opcuaidentifiers.OpcUaId_BaseEventType, 0)
        self.eventFilter.selectClauses[2].attributeId = attributeids.Value
        self.eventFilter.selectClauses[2].browsePath.append(QualifiedName("Severity", 0))
        self.eventFilter.selectClauses[2].typeId = NodeId(opcuaidentifiers.OpcUaId_BaseEventType, 0)
        
        # make sure the trigger has a default value
        result = self.client.write([self.address_Trigger], [Double(50.0)])
        # Check if the write failed due to a BadUserAccessDenied failure
        # This appears to be the case for the UaServerCpp shipped with the Windows MSVS2008 demo SDK,
        # probably a bug in the UaServerCpp.
        try:
            result.targets[0].status.test()
        except pyuaf.util.errors.ServerCouldNotWriteError, e:
            if e.sdkStatus.statusCode == pyuaf.util.opcuastatuscodes.OpcUa_BadUserAccessDenied:
                self.skipTest("Some old versions of the UaServerCpp have non-writeable triggers (bug in UaServerCpp?)")
    
    def test_client_Client_createMonitoredEvents(self):
        
        # create the items
        self.client.createMonitoredEvents([self.address_Alarms], self.eventFilter)
        
        # now write a trigger so that an event will be generated
        self.client.write([self.address_Trigger], [Double(self.highHighLimit + 1.0)])
        
        # after a few seconds we should at least have received 1 notification
        t_timeout = time.time() + 5.0
        while time.time() < t_timeout and self.client.noOfSuccessFullyReceivedNotifications == 0:
            time.sleep(0.01)
        
        self.assertGreaterEqual( self.client.noOfSuccessFullyReceivedNotifications , 1 )
    

    def test_client_Client_createMonitoredEvents_with_callback(self):
        t = TestClass()
        
        # create the items
        self.client.createMonitoredEvents([self.address_Alarms], self.eventFilter, notificationCallbacks=[t.myCallback])
        
        # now write a trigger so that an event will be generated
        self.client.write([self.address_Trigger], [Double(self.highHighLimit + 1.0)])
        
        # after a few seconds we should at least have received 1 notification
        t_timeout = time.time() + 5.0
        while time.time() < t_timeout and t.noOfSuccessFullyReceivedNotifications == 0:
            time.sleep(0.01)
        
        self.assertGreaterEqual( t.noOfSuccessFullyReceivedNotifications , 1 )
    

    
    
    def tearDown(self):
        # make sure the trigger has its default value again
        self.client.write([self.address_Trigger], [Double(50.0)])
        
        # delete the client instances manually (now!) instead of letting them be garbage collected 
        # automatically (which may happen during a another test, and which may cause logging output
        # of the destruction to be mixed with the logging output of the other test).
        del self.client


if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())
