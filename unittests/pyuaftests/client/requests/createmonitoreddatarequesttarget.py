import pyuaf
import unittest
from pyuaf.util.unittesting import parseArgs, testVector


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(CreateMonitoredDataRequestTargetTest)



class CreateMonitoredDataRequestTargetTest(unittest.TestCase):
    
    def setUp(self):
        self.target0 = pyuaf.client.requests.CreateMonitoredDataRequestTarget()
        
        self.target1 = pyuaf.client.requests.CreateMonitoredDataRequestTarget()
        self.target1.browseDirection = pyuaf.util.browsedirections.Inverse
        self.target1.includeSubtypes = True
        self.target1.nodeClassMask = 4
        self.target1.referenceTypeId = pyuaf.util.NodeId("id", "ns")
        self.target1.resultMask = 5
        
        
        self.target1.address = pyuaf.util.Address( pyuaf.util.NodeId("id", "ns"), "svr" )
        self.target1.attributeId = pyuaf.util.attributeids.BrowseName
        self.target1.dataChangeFilter = pyuaf.util.DataChangeFilter( pyuaf.util.DataChangeFilter.DataChangeTrigger_StatusValue,
                                                                     pyuaf.util.DataChangeFilter.DeadBandType_Percent,
                                                                     0.90 )
        self.target1.discardOldest = True
        self.target1.indexRange = "indexRange"
        self.target1.monitoringMode = pyuaf.util.monitoringmodes.Sampling
        self.target1.queueSize = 4
        self.target1.samplingIntervalSec = 1.234
    
    
    def test_client_CreateMonitoredDataRequestTarget_browseDirection(self):
        self.assertEqual( self.target1.browseDirection , pyuaf.util.browsedirections.Inverse )
    
    def test_client_CreateMonitoredDataRequestTarget_includeSubtypes(self):
        self.assertEqual( self.target1.includeSubtypes , True )
    
    def test_client_CreateMonitoredDataRequestTarget_nodeClassMask(self):
        self.assertEqual( self.target1.nodeClassMask , 4 )
    
    def test_client_CreateMonitoredDataRequestTarget_referenceTypeId(self):
        self.assertEqual( self.target1.referenceTypeId , pyuaf.util.NodeId("id", "ns") )
    
    def test_client_CreateMonitoredDataRequestTarget_resultMask(self):
        self.assertEqual( self.target1.resultMask , 5 )
    
    def test_client_CreateMonitoredDataRequestTarget_address(self):
        self.assertEqual( self.target1.address , pyuaf.util.Address( pyuaf.util.NodeId("id", "ns"), "svr" ) )
    
    def test_client_CreateMonitoredDataRequestTarget_attributeId(self):
        self.assertEqual( self.target1.attributeId , pyuaf.util.attributeids.BrowseName )
    
    def test_client_CreateMonitoredDataRequestTarget_dataChangeFilter(self):
        self.assertEqual( self.target1.dataChangeFilter , pyuaf.util.DataChangeFilter(pyuaf.util.DataChangeFilter.DataChangeTrigger_StatusValue,
                                                                                      pyuaf.util.DataChangeFilter.DeadBandType_Percent,
                                                                                      0.90 ) )
    
    def test_client_CreateMonitoredDataRequestTarget_discardOldest(self):
        self.assertEqual( self.target1.discardOldest , True )
    
    def test_client_CreateMonitoredDataRequestTarget_indexRange(self):
        self.assertEqual( self.target1.indexRange , "indexRange" )
    
    def test_client_CreateMonitoredDataRequestTarget_monitoringMode(self):
        self.assertEqual( self.target1.monitoringMode , pyuaf.util.monitoringmodes.Sampling )
    
    def test_client_CreateMonitoredDataRequestTarget_queueSize(self):
        self.assertEqual( self.target1.queueSize , 4 )
    
    def test_client_CreateMonitoredDataRequestTarget_samplingIntervalSec(self):
        self.assertEqual( self.target1.samplingIntervalSec , 1.234 )
    
    def test_client_CreateMonitoredDataRequestTargetVector(self):
        testVector(self, pyuaf.client.requests.CreateMonitoredDataRequestTargetVector, [self.target0, self.target1])
    


if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())

