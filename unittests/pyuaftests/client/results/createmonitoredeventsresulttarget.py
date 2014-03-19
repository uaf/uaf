import pyuaf
import unittest
from pyuaf.util.unittesting import parseArgs, testVector


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(CreateMonitoredEventsResultTargetTest)



class CreateMonitoredEventsResultTargetTest(unittest.TestCase):
    
    def setUp(self):
        self.target0 = pyuaf.client.results.CreateMonitoredEventsResultTarget()
        
        self.target1 = pyuaf.client.results.CreateMonitoredEventsResultTarget()
        self.target1.clientConnectionId = 3
        self.target1.status.setGood()
        self.target1.clientHandle = 4
        self.target1.clientSubscriptionHandle = 5
        self.target1.monitoredItemId = 6
        self.target1.revisedQueueSize = 7
        self.target1.revisedSamplingIntervalSec = 8.0
        
    
    def test_client_CreateMonitoredEventsResultTarget_clientConnectionId(self):
        self.assertEqual( self.target1.clientConnectionId , 3 )
    
    def test_client_CreateMonitoredEventsResultTarget_status(self):
        status = pyuaf.util.Status()
        status.setGood()
        self.assertEqual( self.target1.status , status )
    
    def test_client_CreateMonitoredEventsResultTarget_clientHandle(self):
        self.assertEqual( self.target1.clientHandle , 4 )
    
    def test_client_CreateMonitoredEventsResultTarget_clientSubscriptionHandle(self):
        self.assertEqual( self.target1.clientSubscriptionHandle , 5 )
    
    def test_client_CreateMonitoredEventsResultTarget_monitoredItemId(self):
        self.assertEqual( self.target1.monitoredItemId , 6 )
    
    def test_client_CreateMonitoredEventsResultTarget_revisedQueueSize(self):
        self.assertEqual( self.target1.revisedQueueSize , 7 )
    
    def test_client_CreateMonitoredEventsResultTarget_revisedSamplingIntervalSec(self):
        self.assertEqual( self.target1.revisedSamplingIntervalSec , 8.0 )
    
    def test_client_CreateMonitoredEventsResultTargetVector(self):
        testVector(self, pyuaf.client.results.CreateMonitoredEventsResultTargetVector, [self.target0, self.target1])
    


if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())

