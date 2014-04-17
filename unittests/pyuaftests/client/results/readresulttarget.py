import pyuaf
import unittest
from pyuaf.util.unittesting import parseArgs, testVector


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(ReadResultTargetTest)



class ReadResultTargetTest(unittest.TestCase):
    
    def setUp(self):
        self.target0 = pyuaf.client.results.ReadResultTarget()
        
        self.target1 = pyuaf.client.results.ReadResultTarget()
        self.target1.clientConnectionId = 3
        self.target1.status.setGood()
        self.target1.data = pyuaf.util.primitives.UInt16(42)
        self.target1.serverPicoseconds = 123
        self.target1.sourcePicoseconds = 456
        self.target1.serverTimestamp = pyuaf.util.DateTime(1.23)
        self.target1.sourceTimestamp = pyuaf.util.DateTime(4.56)
    
    def test_client_ReadResultTarget_clientConnectionId(self):
        self.assertEqual( self.target1.clientConnectionId , 3 )
    
    def test_client_ReadResultTarget_status(self):
        status = pyuaf.util.Status()
        status.setGood()
        self.assertEqual( self.target1.status , status )
    
    def test_client_ReadResultTarget_data(self):
        self.assertEqual( self.target1.data , pyuaf.util.primitives.UInt16(42) )
    
    def test_client_ReadResultTarget_serverPicoseconds(self):
        self.assertEqual( self.target1.serverPicoseconds , 123 )
    
    def test_client_ReadResultTarget_sourcePicoseconds(self):
        self.assertEqual( self.target1.sourcePicoseconds , 456 )
    
    def test_client_ReadResultTarget_serverTimestamp(self):
        self.assertEqual( self.target1.serverTimestamp , pyuaf.util.DateTime(1.23) )
    
    def test_client_ReadResultTarget_sourceTimestamp(self):
        self.assertEqual( self.target1.sourceTimestamp , pyuaf.util.DateTime(4.56) )
    
    def test_client_ReadResultTargetVector(self):
        testVector(self, pyuaf.client.results.ReadResultTargetVector, [self.target0, self.target1])
    


if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())

