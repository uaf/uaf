import pyuaf
import unittest
from pyuaf.util.unittesting import parseArgs, testVector


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(QualifiedNameTest)



class QualifiedNameTest(unittest.TestCase):
    
    def setUp(self):
        self.q0  = pyuaf.util.QualifiedName()
        self.q0_ = pyuaf.util.QualifiedName()
        self.q1  = pyuaf.util.QualifiedName("SomeName", 42)
        self.q1_ = pyuaf.util.QualifiedName("SomeName", 42)
        self.q2  = pyuaf.util.QualifiedName("SomeName", "SomeUri")
        self.q2_ = pyuaf.util.QualifiedName("SomeName", "SomeUri")
        self.q3  = pyuaf.util.QualifiedName("SomeName", "SomeUri", 42)
        self.q3_ = pyuaf.util.QualifiedName("SomeName", "SomeUri", 42)
    
    def test_util_QualifiedName_hasNameSpaceIndex(self):
        self.assertEqual( self.q0.hasNameSpaceIndex() , False )
        self.assertEqual( self.q1.hasNameSpaceIndex() , True  )
        self.assertEqual( self.q2.hasNameSpaceIndex() , False )
        self.assertEqual( self.q3.hasNameSpaceIndex() , True  )
    
    def test_util_QualifiedName_hasNameSpaceUri(self):
        self.assertEqual( self.q0.hasNameSpaceUri() , False )
        self.assertEqual( self.q1.hasNameSpaceUri() , False )
        self.assertEqual( self.q2.hasNameSpaceUri() , True  )
        self.assertEqual( self.q3.hasNameSpaceUri() , True  )
    
    def test_util_QualifiedName_nameSpaceUri(self):
        self.assertEqual( self.q2.nameSpaceUri() , "SomeUri" )
        self.assertEqual( self.q3.nameSpaceUri() , "SomeUri" )
    
    def test_util_QualifiedName_nameSpaceIndex(self):
        self.assertEqual( self.q1.nameSpaceIndex() , 42 )
        self.assertEqual( self.q3.nameSpaceIndex() , 42 )
    
    def test_util_QualifiedName_setNameSpaceIndex(self):
        self.q0.setNameSpaceIndex(43)
        self.q1.setNameSpaceIndex(43)
        self.q2.setNameSpaceIndex(43)
        self.q3.setNameSpaceIndex(43)
        self.assertEqual( self.q0.hasNameSpaceIndex() , True )
        self.assertEqual( self.q0.nameSpaceIndex() , 43 )
        self.assertEqual( self.q1.hasNameSpaceIndex() , True )
        self.assertEqual( self.q1.nameSpaceIndex() , 43 )
        self.assertEqual( self.q2.hasNameSpaceIndex() , True )
        self.assertEqual( self.q2.nameSpaceIndex() , 43 )
        self.assertEqual( self.q3.hasNameSpaceIndex() , True )
        self.assertEqual( self.q3.nameSpaceIndex() , 43 )
    
    def test_util_QualifiedName___eq__(self):
        self.assertTrue( self.q0 == self.q0_ )
        self.assertTrue( self.q1 == self.q1_ )
        self.assertTrue( self.q2 == self.q2_ )
        self.assertTrue( self.q3 == self.q3_ )
    
    def test_util_QualifiedName___ne__(self):
        self.assertFalse( self.q0 != self.q0_ )
        self.assertTrue( self.q0 != self.q1 )
        self.assertTrue( self.q1 != self.q2 )
        self.assertTrue( self.q2 != self.q3 )
        self.assertTrue( self.q3 != self.q0 )
    
    def test_util_QualifiedName___lt__(self):
        self.assertTrue( self.q0 < self.q1 )
        self.assertTrue( self.q2 < self.q1 )
        self.assertTrue( self.q2 < self.q3 )
        self.assertTrue( self.q0 < self.q3 )
    
    def test_util_QualifiedName___gt__(self):
        self.assertTrue( self.q1 > self.q0 )
        self.assertTrue( self.q1 > self.q2 )
        self.assertTrue( self.q3 > self.q2 )
        self.assertTrue( self.q3 > self.q0 )
    
    def test_util_QualifiedNameVector(self):
        testVector(self, pyuaf.util.QualifiedNameVector, [self.q0, self.q1, self.q2, self.q3])


if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())