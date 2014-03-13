import pyuaf
import unittest
from pyuaf.util.unittesting import parseArgs, testVector


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(EventNotificationTest)



class EventNotificationTest(unittest.TestCase):
    
    def setUp(self):
        self.notif0 = pyuaf.client.EventNotification()
        
        self.notif1 = pyuaf.client.EventNotification()
        self.notif1.clientHandle = 123
        self.notif1.fields.append( pyuaf.util.primitives.UInt16(456) )
        self.notif1.fields.append( pyuaf.util.primitives.Double(7.89) )
    
    def test_client_EventNotification_clientHandle(self):
        self.assertEqual( self.notif1.clientHandle , 123 )
    
    def test_client_EventNotification_fields(self):
        self.assertEqual( self.notif1.fields[0] , pyuaf.util.primitives.UInt16(456) )
        self.assertEqual( self.notif1.fields[1] , pyuaf.util.primitives.Double(7.89) )
    
    def test_client_EventNotificationVector(self):
        testVector(self, pyuaf.client.EventNotificationVector, [self.notif0, self.notif1])
    


if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())

