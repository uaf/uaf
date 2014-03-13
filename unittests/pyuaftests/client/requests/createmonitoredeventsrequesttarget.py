import pyuaf
import unittest
from pyuaf.util.unittesting import parseArgs, testVector


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(CreateMonitoredEventsRequestTargetTest)



class CreateMonitoredEventsRequestTargetTest(unittest.TestCase):
    
    def setUp(self):
        self.target0 = pyuaf.client.requests.CreateMonitoredEventsRequestTarget()
        
        self.target1 = pyuaf.client.requests.CreateMonitoredEventsRequestTarget()
        self.target1.browseDirection = pyuaf.util.browsedirections.Inverse
        self.target1.includeSubtypes = True
        self.target1.nodeClassMask = 4
        self.target1.referenceTypeId = pyuaf.util.NodeId("id", "ns")
        self.target1.resultMask = 5
        
        self.target1.address = pyuaf.util.Address( pyuaf.util.NodeId("id", "ns"), "svr" )
        self.target1.attributeId = pyuaf.util.attributeids.BrowseName
        self.target1.eventFilter.selectClauses.resize(1)
        self.target1.eventFilter.selectClauses[0].indexRange = "indexRange"
        
        self.target1.discardOldest = True
        self.target1.indexRange = "indexRange"
        self.target1.monitoringMode = pyuaf.util.monitoringmodes.Sampling
        self.target1.queueSize = 4
        self.target1.samplingIntervalSec = 1.234
    
    
    def test_client_CreateMonitoredEventsRequestTarget_browseDirection(self):
        self.assertEqual( self.target1.browseDirection , pyuaf.util.browsedirections.Inverse )
    
    def test_client_CreateMonitoredEventsRequestTarget_includeSubtypes(self):
        self.assertEqual( self.target1.includeSubtypes , True )
    
    def test_client_CreateMonitoredEventsRequestTarget_nodeClassMask(self):
        self.assertEqual( self.target1.nodeClassMask , 4 )
    
    def test_client_CreateMonitoredEventsRequestTarget_referenceTypeId(self):
        self.assertEqual( self.target1.referenceTypeId , pyuaf.util.NodeId("id", "ns") )
    
    def test_client_CreateMonitoredEventsRequestTarget_resultMask(self):
        self.assertEqual( self.target1.resultMask , 5 )
    
    def test_client_CreateMonitoredEventsRequestTarget_address(self):
        self.assertEqual( self.target1.address , pyuaf.util.Address( pyuaf.util.NodeId("id", "ns"), "svr" ) )
    
    def test_client_CreateMonitoredEventsRequestTarget_attributeId(self):
        self.assertEqual( self.target1.attributeId , pyuaf.util.attributeids.BrowseName )
    
    def test_client_CreateMonitoredEventsRequestTarget_dataChangeFilter(self):
        eventFilter = pyuaf.util.EventFilter()
        eventFilter.selectClauses.resize(1)
        eventFilter.selectClauses[0].indexRange = "indexRange"
        
        self.assertEqual( self.target1.eventFilter , eventFilter )
    
    def test_client_CreateMonitoredEventsRequestTarget_discardOldest(self):
        self.assertEqual( self.target1.discardOldest , True )
    
    def test_client_CreateMonitoredEventsRequestTarget_indexRange(self):
        self.assertEqual( self.target1.indexRange , "indexRange" )
    
    def test_client_CreateMonitoredEventsRequestTarget_monitoringMode(self):
        self.assertEqual( self.target1.monitoringMode , pyuaf.util.monitoringmodes.Sampling )
    
    def test_client_CreateMonitoredEventsRequestTarget_queueSize(self):
        self.assertEqual( self.target1.queueSize , 4 )
    
    def test_client_CreateMonitoredEventsRequestTarget_samplingIntervalSec(self):
        self.assertEqual( self.target1.samplingIntervalSec , 1.234 )
    
    def test_client_CreateMonitoredEventsRequestTargetVector(self):
        testVector(self, pyuaf.client.requests.CreateMonitoredEventsRequestTargetVector, [self.target0, self.target1])
    


if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())

