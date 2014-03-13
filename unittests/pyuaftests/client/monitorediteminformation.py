import pyuaf
import unittest
from pyuaf.util.unittesting import parseArgs, testVector


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(MonitoredItemInformationTest)



class MonitoredItemInformationTest(unittest.TestCase):
    
    def setUp(self):
        self.info0 = pyuaf.client.MonitoredItemInformation()
        
        self.info1 = pyuaf.client.MonitoredItemInformation()
        self.info1.clientConnectionId = 123
        self.info1.clientSubscriptionHandle = 456
        self.info1.clientHandle = 789
        self.info1.monitoredItemState = pyuaf.client.monitoreditemstates.Created
    
    def test_client_MonitoredItemInformation_clientConnectionId(self):
        self.assertEqual( self.info1.clientConnectionId , 123 )
    
    def test_client_MonitoredItemInformation_clientSubscriptionHandle(self):
        self.assertEqual( self.info1.clientSubscriptionHandle , 456 )
    
    def test_client_MonitoredItemInformation_clientHandle(self):
        self.assertEqual( self.info1.clientHandle , 789 )
    
    def test_client_MonitoredItemInformation_subscriptionState(self):
        self.assertEqual( self.info1.monitoredItemState , pyuaf.client.monitoreditemstates.Created )
    
    def test_client_MonitoredItemInformationVector(self):
        testVector(self, pyuaf.client.MonitoredItemInformationVector, [self.info0, self.info1])
    


if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())

