import pyuaf
import unittest
from pyuaf.util.unittesting import parseArgs, testVector


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(DataChangeNotificationTest)



class DataChangeNotificationTest(unittest.TestCase):
    
    def setUp(self):
        self.notif0 = pyuaf.client.DataChangeNotification()
        
        self.notif1 = pyuaf.client.DataChangeNotification()
        self.notif1.clientHandle = 123
        self.notif1.data = pyuaf.util.primitives.UInt16(456)
        self.notif1.status.setStatus(pyuaf.util.statuscodes.DiscoveryError, "some error")
    
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

