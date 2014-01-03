import pyuaf
import unittest
from pyuaf.util.unittesting import parseArgs


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(RelativePathElementTest)



class RelativePathElementTest(unittest.TestCase):
    
    def setUp(self):
        self.r0  = pyuaf.util.RelativePathElement()
        self.r0_ = pyuaf.util.RelativePathElement()
        self.r1  = pyuaf.util.RelativePathElement(pyuaf.util.QualifiedName("SomeName", 42))
        self.r1_ = pyuaf.util.RelativePathElement(pyuaf.util.QualifiedName("SomeName", 42))
        self.r2  = pyuaf.util.RelativePathElement(pyuaf.util.QualifiedName("SomeName", 42),
                                                  pyuaf.util.NodeId("SomeIdentifier", 21),
                                                  True,
                                                  False)
        self.r2_ = pyuaf.util.RelativePathElement(pyuaf.util.QualifiedName("SomeName", 42),
                                                  pyuaf.util.NodeId("SomeIdentifier", 21),
                                                  True,
                                                  False)
    
    def test_util_RelativePathElement_targetName(self):
        self.assertEqual( self.r0.targetName , pyuaf.util.QualifiedName() )
        self.assertEqual( self.r1.targetName , pyuaf.util.QualifiedName("SomeName", 42) )
        self.assertEqual( self.r2.targetName , pyuaf.util.QualifiedName("SomeName", 42) )
    
    def test_util_RelativePathElement_referenceType(self):
        self.assertEqual( self.r0.referenceType , pyuaf.util.NodeId(pyuaf.util.opcuaidentifiers.OpcUaId_HierarchicalReferences, 0) )
        self.assertEqual( self.r1.referenceType , pyuaf.util.NodeId(pyuaf.util.opcuaidentifiers.OpcUaId_HierarchicalReferences, 0) )
        self.assertEqual( self.r2.referenceType , pyuaf.util.NodeId("SomeIdentifier", 21) )
    
    def test_util_RelativePathElement_isInverse(self):
        self.assertEqual( self.r0.isInverse , False )
        self.assertEqual( self.r1.isInverse , False )
        self.assertEqual( self.r2.isInverse , True )
    
    def test_util_RelativePathElement_includeSubtypes(self):
        self.assertEqual( self.r0.includeSubtypes , True )
        self.assertEqual( self.r1.includeSubtypes , True )
        self.assertEqual( self.r2.includeSubtypes , False )
    
    def test_util_RelativePathElement___eq__(self):
        self.assertTrue( self.r0 == self.r0_ )
        self.assertTrue( self.r1 == self.r1_ )
        self.assertTrue( self.r2 == self.r2_ )
        self.assertFalse( self.r0 == self.r1 )
    
    def test_util_RelativePathElement___ne__(self):
        self.assertTrue( self.r0 != self.r1 )
        self.assertTrue( self.r1 != self.r2 )
        self.assertTrue( self.r2 != self.r0 )
        self.assertFalse( self.r0 != self.r0 )
    
    def test_util_RelativePathElement___lt__(self):
        self.assertTrue( self.r0 < self.r1 )
        self.assertTrue( self.r1 < self.r2 )
        self.assertTrue( self.r0 < self.r2 )
    
    def test_util_RelativePathElement___gt__(self):
        self.assertTrue( self.r1 > self.r0 )
        self.assertTrue( self.r2 > self.r1 )
        self.assertTrue( self.r2 > self.r0 )
        


if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())
