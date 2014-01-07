import pyuaf
import unittest
from pyuaf.util.unittesting import parseArgs


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(AddressTest)



class AddressTest(unittest.TestCase):
    
    def setUp(self):
        self.nodeId          = pyuaf.util.ExpandedNodeId("SomeStringIdentifier", "SomeNameSpaceUri", "SomeServerUri")
        self.e1              = pyuaf.util.RelativePathElement(pyuaf.util.QualifiedName("SomeName", 42))
        self.e2              = pyuaf.util.RelativePathElement(pyuaf.util.QualifiedName("SomeOtherName", 42))
        self.relativePath    = [self.e1, self.e2]
        
        self.a0  = pyuaf.util.Address()
        self.a0_ = pyuaf.util.Address()
        self.a1  = pyuaf.util.Address(self.nodeId)
        self.a1_ = pyuaf.util.Address(self.nodeId)
        self.a2  = pyuaf.util.Address(self.a1, self.relativePath)
        self.a2_ = pyuaf.util.Address(self.a1, self.relativePath)
        self.a3  = pyuaf.util.Address(self.a2, self.relativePath)
        self.a3_ = pyuaf.util.Address(self.a2, self.relativePath)
    
    def test_util_Address_isExpandedNodeId(self):
        self.assertEqual( self.a0.isExpandedNodeId() , True  )
        self.assertEqual( self.a1.isExpandedNodeId() , True  )
        self.assertEqual( self.a2.isExpandedNodeId() , False )
        self.assertEqual( self.a3.isExpandedNodeId() , False )
    
    def test_util_Address_isRelativePath(self):
        self.assertEqual( self.a0.isRelativePath() , False )
        self.assertEqual( self.a1.isRelativePath() , False )
        self.assertEqual( self.a2.isRelativePath() , True  )
        self.assertEqual( self.a3.isRelativePath() , True  )
    
    def test_util_Address_getRelativePath(self):
        self.assertEqual( self.a2.getRelativePath() , (self.e1, self.e2) )
        self.assertEqual( self.a3.getRelativePath() , (self.e1, self.e2) )
    
    def test_util_Address_getStartingAddress(self):
        self.assertEqual( self.a2.getStartingAddress() , self.a1 )
        self.assertEqual( self.a3.getStartingAddress() , self.a2 )
    
    def test_util_Address___eq__(self):
        self.assertTrue( self.a0 == self.a0_ )
        self.assertTrue( self.a1 == self.a1_ )
        self.assertTrue( self.a2 == self.a2_ )
        self.assertTrue( self.a3 == self.a3_ )
    
    def test_util_Address___ne__(self):
        self.assertTrue( self.a0 != self.a1 )
        self.assertTrue( self.a1 != self.a2 ) 
        self.assertTrue( self.a2 != self.a3 )
        self.assertTrue( self.a3 != self.a1 )
    
    def test_util_Address___lt__(self):
        self.assertTrue( self.a0 < self.a1 )
        self.assertTrue( self.a2 < self.a1 )
        self.assertTrue( self.a3 < self.a2 )
        self.assertTrue( self.a3 < self.a0 )
    
    def test_util_Address___gt__(self):
        self.assertTrue( self.a1 > self.a0 )
        self.assertTrue( self.a1 > self.a2 )
        self.assertTrue( self.a2 > self.a3 )
        self.assertTrue( self.a0 > self.a3 )


if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())

