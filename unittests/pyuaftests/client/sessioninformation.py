import pyuaf
import unittest
from pyuaf.util.unittesting import parseArgs, testVector


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(SessionInformationTest)



class SessionInformationTest(unittest.TestCase):
    
    def setUp(self):
        self.now = pyuaf.util.DateTime.now()
        
        self.info0 = pyuaf.client.SessionInformation()
        
        self.info1 = pyuaf.client.SessionInformation()
        self.info1.clientConnectionId = 123
        self.info1.serverUri = "test"
        self.info1.sessionState = pyuaf.client.sessionstates.NewSessionCreated
        self.info1.serverState = pyuaf.util.serverstates.Running
        self.info1.lastConnectionAttemptStatus.setGood();
        self.info1.lastConnectionAttemptTime = self.now
    
    def test_client_SessionInformation_clientConnectionId(self):
        self.assertEqual( self.info1.clientConnectionId , 123 )
    
    def test_client_SessionInformation_serverUri(self):
        self.assertEqual( self.info1.serverUri , "test" )
    
    def test_client_SessionInformation_sessionState(self):
        self.assertEqual( self.info1.sessionState , pyuaf.client.sessionstates.NewSessionCreated )
    
    def test_client_SessionInformation_serverState(self):
        self.assertEqual( self.info1.serverState , pyuaf.util.serverstates.Running )
    
    def test_client_SessionInformation_lastConnectionAttemptTime(self):
        self.assertEqual( self.info1.lastConnectionAttemptTime , self.now )
    
    def test_client_SessionInformation_lastConnectionAttemptStatus(self):
        self.assertTrue( self.info1.lastConnectionAttemptStatus.isGood() )
    
    def test_client_SessionInformationVector(self):
        testVector(self, pyuaf.client.SessionInformationVector, [self.info0, self.info1])
    


if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())

