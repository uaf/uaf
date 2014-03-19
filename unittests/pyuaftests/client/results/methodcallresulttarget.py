import pyuaf
import unittest
from pyuaf.util.unittesting import parseArgs, testVector


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(MethodCallResultTargetTest)



class MethodCallResultTargetTest(unittest.TestCase):
    
    def setUp(self):
        self.target0 = pyuaf.client.results.MethodCallResultTarget()
        
        self.target1 = pyuaf.client.results.MethodCallResultTarget()
        self.target1.clientConnectionId = 3
        self.target1.status.setGood()
        self.target1.inputArgumentStatuses.resize(1)
        self.target1.inputArgumentStatuses[0].setGood()
        self.target1.outputArguments.resize(1)
        self.target1.outputArguments[0] = pyuaf.util.primitives.UInt64(42)
    
    def test_client_MethodCallResultTarget_clientConnectionId(self):
        self.assertEqual( self.target1.clientConnectionId , 3 )
    
    def test_client_MethodCallResultTarget_status(self):
        status = pyuaf.util.Status()
        status.setGood()
        self.assertEqual( self.target1.status , status )
    
    def test_client_MethodCallResultTarget_inputArgumentStatuses(self):
        status = pyuaf.util.Status()
        status.setGood()
        self.assertEqual( self.target1.inputArgumentStatuses[0] , status )
    
    def test_client_MethodCallResultTarget_outputArguments(self):
        self.assertEqual( self.target1.outputArguments[0] , pyuaf.util.primitives.UInt64(42) )
    
    def test_client_MethodCallResultTargetVector(self):
        testVector(self, pyuaf.client.results.MethodCallResultTargetVector, [self.target0, self.target1])
    


if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())

