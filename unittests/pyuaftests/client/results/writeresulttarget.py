import pyuaf
import unittest
from pyuaf.util.unittesting import parseArgs, testVector


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(WriteResultTargetTest)



class WriteResultTargetTest(unittest.TestCase):
    
    def setUp(self):
        self.target0 = pyuaf.client.results.WriteResultTarget()
        
        self.target1 = pyuaf.client.results.WriteResultTarget()
        self.target1.clientConnectionId = 3
        self.target1.status.setGood()
    
    def test_client_WriteResultTarget_clientConnectionId(self):
        self.assertEqual( self.target1.clientConnectionId , 3 )
    
    def test_client_WriteCallResultTarget_status(self):
        status = pyuaf.util.Status()
        status.setGood()
        self.assertEqual( self.target1.status , status )
    
    def test_client_WriteResultTargetVector(self):
        testVector(self, pyuaf.client.results.WriteResultTargetVector, [self.target0, self.target1])
    


if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())

