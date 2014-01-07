import pyuaf
import time
import threading
import sys
import unittest
from pyuaf.util.unittesting import parseArgs


from pyuaf.util import NodeId, Address, ExpandedNodeId, BrowsePath, \
                       RelativePathElement, QualifiedName, opcuaidentifiers


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(ClientMonitorDataTest)



class MyClient(pyuaf.client.Client):

    def __init__(self, settings):
        pyuaf.client.Client.__init__(self, settings)
        self.noOfSuccessFullyReceivedNotifications = 0
        self.lock = threading.Lock()
            
    def dataChangesReceived(self, notifications):
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




class ClientMonitorDataTest(unittest.TestCase):
    
    
    def setUp(self):
        
        # create a new ClientSettings instance and add the localhost to the URLs to discover
        settings = pyuaf.client.settings.ClientSettings()
        settings.discoveryUrls.append(ARGS.demo_url)
        settings.applicationName = "client"
        settings.logToStdOutLevel = ARGS.loglevel
    
        self.client = MyClient(settings)

        
        serverUri    = ARGS.demo_server_uri
        demoNsUri    = ARGS.demo_ns_uri
        plcOpenNsUri = "http://PLCopen.org/OpcUa/IEC61131-3/"
        
        
        self.address_Demo            = Address(ExpandedNodeId("Demo", demoNsUri, serverUri))
        self.address_StartSimulation = Address(self.address_Demo, [RelativePathElement(QualifiedName("StartSimulation", demoNsUri))])
        self.address_StopSimulation  = Address(self.address_Demo, [RelativePathElement(QualifiedName("StopSimulation", demoNsUri))])
        self.address_Scalar          = Address(self.address_Demo, [RelativePathElement(QualifiedName("Dynamic", demoNsUri)),
                                                          RelativePathElement(QualifiedName("Scalar", demoNsUri))] )
        self.address_Byte            = Address(self.address_Scalar, [RelativePathElement(QualifiedName("Byte", demoNsUri))] )
        self.address_Int32           = Address(self.address_Scalar, [RelativePathElement(QualifiedName("Int32", demoNsUri))] )
        self.address_Float           = Address(self.address_Scalar, [RelativePathElement(QualifiedName("Float", demoNsUri))] )
        
        # start the simulation (otherwise the dynamic variables won't change)
        self.client.call(self.address_Demo, self.address_StartSimulation)
    
    
    def test_client_Client_createMonitoredData(self):
        self.client.createMonitoredData([self.address_Byte, self.address_Int32, self.address_Float])
        
        # after a few seconds we should AT LEAST have received 2 notifications
        t_timeout = time.time() + 5.0
        while time.time() < t_timeout and self.client.noOfSuccessFullyReceivedNotifications < 2:
            time.sleep(0.01)
    
        self.assertGreaterEqual( self.client.noOfSuccessFullyReceivedNotifications , 2 )

    
    
    def test_client_Client_createMonitoredData_with_callback(self):
        t = TestClass()
        
        result = self.client.createMonitoredData([self.address_Byte, self.address_Int32, self.address_Float], 
                                                 notificationCallbacks=[t.myCallback, t.myCallback, t.myCallback])
        
        # after a few seconds we should AT LEAST have received 2 notifications
        t_timeout = time.time() + 5.0
        while time.time() < t_timeout and t.noOfSuccessFullyReceivedNotifications < 2:
            time.sleep(0.01)
        
    
        self.assertGreaterEqual( t.noOfSuccessFullyReceivedNotifications , 2 )
    

    def tearDown(self):
        # stop the simulation
        self.client.call(self.address_Demo, self.address_StopSimulation)
        
        # delete the client instances manually (now!) instead of letting them be garbage collected 
        # automatically (which may happen during a another test, and which may cause logging output
        # of the destruction to be mixed with the logging output of the other test).
        del self.client




if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())
