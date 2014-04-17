import pyuaf
import unittest
from pyuaf.util.unittesting import parseArgs, testVector


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(SubscriptionInformationTest)



class SubscriptionInformationTest(unittest.TestCase):
    
    def setUp(self):
        self.info0 = pyuaf.client.SubscriptionInformation()
        
        self.info1 = pyuaf.client.SubscriptionInformation()
        self.info1.clientConnectionId = 123
        self.info1.clientSubscriptionHandle = 456
        self.info1.subscriptionState = pyuaf.client.subscriptionstates.Created
    
    def test_client_SubscriptionInformation_clientConnectionId(self):
        self.assertEqual( self.info1.clientConnectionId , 123 )
    
    def test_client_SubscriptionInformation_clientSubscriptionHandle(self):
        self.assertEqual( self.info1.clientSubscriptionHandle , 456 )
    
    def test_client_SubscriptionInformation_subscriptionState(self):
        self.assertEqual( self.info1.subscriptionState , pyuaf.client.subscriptionstates.Created )
    
    def test_client_SubscriptionInformationVector(self):
        testVector(self, pyuaf.client.SubscriptionInformationVector, [self.info0, self.info1])
    


if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())

