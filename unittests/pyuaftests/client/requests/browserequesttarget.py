import pyuaf
import unittest
from pyuaf.util.unittesting import parseArgs, testVector


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(BrowseRequestTargetTest)



class BrowseRequestTargetTest(unittest.TestCase):
    
    def setUp(self):
        self.target0 = pyuaf.client.requests.BrowseRequestTarget()
        
        self.target1 = pyuaf.client.requests.BrowseRequestTarget()
        self.target1.address = pyuaf.util.Address( pyuaf.util.NodeId("id", "ns"), "svr" )
        self.target1.browseDirection = pyuaf.util.browsedirections.Inverse
        self.target1.includeSubtypes = True
        self.target1.nodeClassMask = pyuaf.util.Mask()
        self.target1.referenceTypeId = pyuaf.util.Address( pyuaf.util.NodeId("id", "ns"), "svr" )
        self.target1.resultMask = pyuaf.util.Mask()
    
    def test_client_DataChangeNotification_clientHandle(self):
        self.assertEqual( self.notif1.clientHandle , 123 )
    
    def test_client_DataChangeNotification_data(self):
        self.assertEqual( self.notif1.data , pyuaf.util.primitives.UInt16(456) )
    
    def test_client_DataChangeNotification_status(self):
        status = pyuaf.util.Status()
        status.setStatus(pyuaf.util.statuscodes.DiscoveryError, "some error")
        self.assertEqual( self.notif1.status , status )
    
    def test_client_DataChangeNotificationVector(self):
        testVector(self, pyuaf.client.DataChangeNotificationVector, [self.notif0, self.notif1])
    


if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())

