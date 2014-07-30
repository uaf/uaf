import pyuaf
import time
import thread
import unittest
from pyuaf.util.unittesting import parseArgs

from pyuaf.util import NodeId, Address, ExpandedNodeId, BrowsePath, \
                       RelativePathElement, QualifiedName, opcuaidentifiers
from pyuaf.client.requests import ReadRequest, ReadRequestTarget
from pyuaf.client.results  import ReadResult,  ReadResultTarget



ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(ClientConnectionStatusTest)


class ConnectionStatusCallbackClass:
    def __init__(self):
        self.infoList = []
    
    def callback(self, info):
        self.infoList.append(info)
    
    def isCallbackCalled(self):
        return len(self.infoList) > 0


class MyClient(pyuaf.client.Client):

    def __init__(self, settings):
        pyuaf.client.Client.__init__(self, settings)
        self.infoList = []
    
    def connectionStatusChanged(self, info):
        self.infoList.append(info)
    
    def isCallbackCalled(self):
        return len(self.infoList) > 0


class ClientConnectionStatusTest(unittest.TestCase):
    
    
    def setUp(self):
        
        # create a new ClientSettings instance and add the localhost to the URLs to discover
        settings = pyuaf.client.settings.ClientSettings()
        settings.discoveryUrls.append(ARGS.demo_url)
        settings.applicationName = "client"
        settings.logToStdOutLevel = ARGS.loglevel
        
        self.client = MyClient(settings)
    
        self.serverUri = ARGS.demo_server_uri
        demoNsUri = ARGS.demo_ns_uri
        plcOpenNsUri = "http://PLCopen.org/OpcUa/IEC61131-3/"
        
        # define some nodeids
        self.id = NodeId(opcuaidentifiers.OpcUaId_Server_Auditing, 0)
        
        # define some addresses
        self.address = Address(ExpandedNodeId(self.id, self.serverUri))
    

    def test_client_Client_register_all_connectionstatuses_and_read_node(self):
        cbc = ConnectionStatusCallbackClass()
        self.client.registerConnectionStatusCallback(cbc.callback)
        
        result = self.client.read(self.address)
        self.assertTrue( result.targets[0].status.isGood() )
        # the callbacks should have been called once:
        for source in [self.client, cbc]:
            self.assertEqual( len(source.infoList), 1 )
            self.assertEqual( source.infoList[0].serverUri, self.serverUri)
            self.assertEqual( source.infoList[0].sessionState, pyuaf.client.sessionstates.Connected )
        

    def test_client_Client_register_all_connectionstatuses_and_manually_connect(self):
        cbc = ConnectionStatusCallbackClass()
        self.client.registerConnectionStatusCallback(cbc.callback)
        
        clientConnectionId = self.client.manuallyConnect(self.serverUri)
        
        # the callbacks may be dispatched in a separate Python thread, which may not be completed 
        # yet, so we must wait for them!
        t_end = time.time() + 1.0 # 1 sec timeout
        while time.time() < t_end and not (self.client.isCallbackCalled() and cbc.isCallbackCalled()):
            time.sleep(0.001) # do nothing, just wait
        
        for source in [self.client, cbc]:
            self.assertTrue( source.isCallbackCalled() )
            self.assertEqual( source.infoList[0].serverUri, self.serverUri)
            self.assertEqual( source.infoList[0].sessionState, pyuaf.client.sessionstates.Connected )
        

    def test_client_Client_register_connectionstatus_for_serveruri_and_read_node(self):
        cbc = ConnectionStatusCallbackClass()
        self.client.registerConnectionStatusCallback(cbc.callback, onlyServerUri = self.serverUri)
        
        result = self.client.read(self.address)
        self.assertTrue( result.targets[0].status.isGood() )
        
        # the callbacks may be dispatched in a separate Python thread, which may not be completed 
        # yet, so we must wait for them!
        t_end = time.time() + 1.0 # 1 sec timeout
        while time.time() < t_end and not (self.client.isCallbackCalled() and cbc.isCallbackCalled()):
            time.sleep(0.001) # do nothing, just wait
        
        for source in [self.client, cbc]:
            self.assertTrue( source.isCallbackCalled() )
            self.assertEqual( source.infoList[0].serverUri, self.serverUri)
            self.assertEqual( source.infoList[0].sessionState, pyuaf.client.sessionstates.Connected )
        

    def test_client_Client_register_connectionstatus_for_clientconnectionid_and_read_node(self):
        cbc = ConnectionStatusCallbackClass()
        # since we created a new client, the clientConnectionId will be 0:
        clientConnectionId = 0
        self.client.registerConnectionStatusCallback(cbc.callback, onlyClientConnectionId = clientConnectionId)
        
        result = self.client.read(self.address)
        self.assertTrue( result.targets[0].status.isGood() )
        
        # the callbacks may be dispatched in a separate Python thread, which may not be completed 
        # yet, so we must wait for them!
        t_end = time.time() + 1.0 # 1 sec timeout
        while time.time() < t_end and not (self.client.isCallbackCalled() and cbc.isCallbackCalled()):
            time.sleep(0.001) # do nothing, just wait
        
        for source in [self.client, cbc]:
            self.assertTrue( source.isCallbackCalled() )
            self.assertEqual( len(source.infoList), 1 )
            self.assertEqual( cbc.infoList[0].clientConnectionId, clientConnectionId)
            self.assertEqual( source.infoList[0].serverUri, self.serverUri)
            self.assertEqual( source.infoList[0].sessionState, pyuaf.client.sessionstates.Connected )
        

    def test_client_Client_register_connectionstatus_in_several_ways_and_manually_connect(self):
        cbc0 = ConnectionStatusCallbackClass()
        self.client.registerConnectionStatusCallback(cbc0.callback)
        cbc1 = ConnectionStatusCallbackClass()
        self.client.registerConnectionStatusCallback(cbc1.callback, onlyServerUri = self.serverUri)
        cbc2 = ConnectionStatusCallbackClass()
        # since we created a new client, the clientConnectionId will be 0:
        clientConnectionId = 0
        self.client.registerConnectionStatusCallback(cbc2.callback, onlyClientConnectionId = clientConnectionId)
        
        result = self.client.read(self.address)
        self.assertTrue( result.targets[0].status.isGood() )
        
        # the callbacks may be dispatched in a separate Python thread, which may not be completed 
        # yet, so we must wait for them!
        t_end = time.time() + 1.0 # 1 sec timeout
        while time.time() < t_end and not (self.client.isCallbackCalled() 
                                           and cbc0.isCallbackCalled() 
                                           and cbc1.isCallbackCalled() 
                                           and cbc2.isCallbackCalled()):
            time.sleep(0.001) # do nothing, just wait
        
        # the callbacks should have been called once:
        for source in [self.client, cbc0, cbc1, cbc2 ]:
            self.assertTrue( source.isCallbackCalled() )
            self.assertEqual( source.infoList[0].clientConnectionId, clientConnectionId)
            self.assertEqual( source.infoList[0].serverUri, self.serverUri)
            self.assertEqual( source.infoList[0].sessionState, pyuaf.client.sessionstates.Connected )
    
    
    def tearDown(self):
        # delete the client instances manually (now!) instead of letting them be garbage collected 
        # automatically (which may happen during a another test, and which may cause logging output
        # of the destruction to be mixed with the logging output of the other test).
        del self.client
        

if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())