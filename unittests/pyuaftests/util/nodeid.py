import pyuaf
import unittest
from pyuaf.util.unittesting import parseArgs


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(NodeIdTest)



class NodeIdTest(unittest.TestCase):
    
    def setUp(self):
        self.n0  = pyuaf.util.NodeId()
        self.n0_ = pyuaf.util.NodeId()
        self.n1  = pyuaf.util.NodeId("SomeStringIdentifier", "SomeNameSpaceUri")
        self.n1_ = pyuaf.util.NodeId("SomeStringIdentifier", "SomeNameSpaceUri")
        self.n1a = pyuaf.util.NodeId("SomeOtherStringIdentifier", "SomeNameSpaceUri")
        self.n1b = pyuaf.util.NodeId("SomeStringIdentifier", "SomeOtherNameSpaceUri")
        self.n1c = pyuaf.util.NodeId("SomeOtherStringIdentifier", "SomeOtherNameSpaceUri")
        self.n2  = pyuaf.util.NodeId("SomeStringIdentifier", "SomeNameSpaceUri", 42)
        self.n2_ = pyuaf.util.NodeId("SomeStringIdentifier", "SomeNameSpaceUri", 42)
        self.n3  = pyuaf.util.NodeId("SomeStringIdentifier", 42)
        self.n3_ = pyuaf.util.NodeId("SomeStringIdentifier", 42)
        self.n4  = pyuaf.util.NodeId(21, "SomeNameSpaceUri")
        self.n4_ = pyuaf.util.NodeId(21, "SomeNameSpaceUri")
        self.n5  = pyuaf.util.NodeId(21, "SomeNameSpaceUri", 42)
        self.n5_ = pyuaf.util.NodeId(21, "SomeNameSpaceUri", 42)
        self.n6  = pyuaf.util.NodeId(21, 42)
        self.n6_ = pyuaf.util.NodeId(21, 42)
        self.n7  = pyuaf.util.NodeId(pyuaf.util.Guid("{00000000-0000-0000-0000-000000000001}"), "SomeNameSpaceUri")
        self.n7_ = pyuaf.util.NodeId(pyuaf.util.Guid("{00000000-0000-0000-0000-000000000001}"), "SomeNameSpaceUri")
        self.n8  = pyuaf.util.NodeId(pyuaf.util.Guid("{00000000-0000-0000-0000-000000000001}"), "SomeNameSpaceUri", 42)
        self.n8_ = pyuaf.util.NodeId(pyuaf.util.Guid("{00000000-0000-0000-0000-000000000001}"), "SomeNameSpaceUri", 42)
        self.n9  = pyuaf.util.NodeId(pyuaf.util.Guid("{00000000-0000-0000-0000-000000000001}"), 42)
        self.n9_ = pyuaf.util.NodeId(pyuaf.util.Guid("{00000000-0000-0000-0000-000000000001}"), 42)
        self.n10  = pyuaf.util.NodeId(pyuaf.util.NodeIdIdentifier("SomeStringIdentifier"), "SomeNameSpaceUri")
        self.n10_ = pyuaf.util.NodeId(pyuaf.util.NodeIdIdentifier("SomeStringIdentifier"), "SomeNameSpaceUri")
        self.n11  = pyuaf.util.NodeId(pyuaf.util.NodeIdIdentifier("SomeStringIdentifier"), "SomeNameSpaceUri", 42)
        self.n11_ = pyuaf.util.NodeId(pyuaf.util.NodeIdIdentifier("SomeStringIdentifier"), "SomeNameSpaceUri", 42)
        self.n12  = pyuaf.util.NodeId(pyuaf.util.NodeIdIdentifier("SomeStringIdentifier"), 42)
        self.n12_ = pyuaf.util.NodeId(pyuaf.util.NodeIdIdentifier("SomeStringIdentifier"), 42)
    
    def test_util_NodeId_hasNameSpaceIndex(self):
        self.assertEquals( self.n0.hasNameSpaceIndex() , False )
        self.assertEquals( self.n1.hasNameSpaceIndex() , False )
        self.assertEquals( self.n2.hasNameSpaceIndex() , True  )
        self.assertEquals( self.n3.hasNameSpaceIndex() , True  )
        self.assertEquals( self.n4.hasNameSpaceIndex() , False )
        self.assertEquals( self.n5.hasNameSpaceIndex() , True  )
        self.assertEquals( self.n6.hasNameSpaceIndex() , True  )
        self.assertEquals( self.n7.hasNameSpaceIndex() , False )
        self.assertEquals( self.n8.hasNameSpaceIndex() , True  )
        self.assertEquals( self.n9.hasNameSpaceIndex() , True  )
        self.assertEquals( self.n7.hasNameSpaceIndex() , False )
        self.assertEquals( self.n8.hasNameSpaceIndex() , True  )
        self.assertEquals( self.n9.hasNameSpaceIndex() , True  )
        self.assertEquals( self.n10.hasNameSpaceIndex() , False )
        self.assertEquals( self.n11.hasNameSpaceIndex() , True  )
        self.assertEquals( self.n12.hasNameSpaceIndex() , True  )
    
    def test_util_NodeId_hasNameSpaceUri(self):
        self.assertEquals( self.n0.hasNameSpaceUri() , False )
        self.assertEquals( self.n1.hasNameSpaceUri() , True  )
        self.assertEquals( self.n2.hasNameSpaceUri() , True  )
        self.assertEquals( self.n3.hasNameSpaceUri() , False )
        self.assertEquals( self.n4.hasNameSpaceUri() , True  )
        self.assertEquals( self.n5.hasNameSpaceUri() , True  )
        self.assertEquals( self.n6.hasNameSpaceUri() , False )
        self.assertEquals( self.n7.hasNameSpaceUri() , True  )
        self.assertEquals( self.n8.hasNameSpaceUri() , True  )
        self.assertEquals( self.n9.hasNameSpaceUri() , False )
        self.assertEquals( self.n10.hasNameSpaceUri() , True  )
        self.assertEquals( self.n11.hasNameSpaceUri() , True  )
        self.assertEquals( self.n12.hasNameSpaceUri() , False )
        
    def test_util_NodeId_nameSpaceIndex(self):
        self.assertEquals( self.n2.nameSpaceIndex() , 42 )
        
    def test_util_NodeId_nameSpaceUri(self):
        self.assertEquals( self.n1.nameSpaceUri() , "SomeNameSpaceUri" )
        
    def test_util_NodeId_setNameSpaceIndex(self):
        n = pyuaf.util.NodeId(self.n2)
        n.setNameSpaceIndex(43)
        self.assertEquals( n.nameSpaceIndex() , 43 )
        
    def test_util_NodeId_setNameSpaceUri(self):
        n = pyuaf.util.NodeId(self.n2)
        n.setNameSpaceUri("SomeOtherNameSpaceUri")
        self.assertEquals( n.nameSpaceUri() , "SomeOtherNameSpaceUri" )
        
    def test_util_NodeId_identifier(self):
        self.assertEquals( self.n1.identifier() , pyuaf.util.NodeIdIdentifier("SomeStringIdentifier") )
        self.assertEquals( self.n4.identifier() , pyuaf.util.NodeIdIdentifier(21) )
        
    def test_util_NodeId___eq__(self):
        self.assertTrue( self.n0 == self.n0_ )
        self.assertTrue( self.n1 == self.n1_ )
        self.assertTrue( self.n2 == self.n2_ )
        self.assertTrue( self.n3 == self.n3_ )
        self.assertTrue( self.n4 == self.n4_ )
        self.assertTrue( self.n5 == self.n5_ )
        self.assertTrue( self.n6 == self.n6_ )
        self.assertTrue( self.n7 == self.n7_ )
        self.assertTrue( self.n8 == self.n8_ )
        self.assertTrue( self.n9 == self.n9_ )
        self.assertTrue( self.n10 == self.n10_ )
        self.assertTrue( self.n11 == self.n11_ )
        self.assertTrue( self.n12 == self.n12_ )
        self.assertTrue( self.n10 == self.n1 )
        self.assertTrue( self.n11 == self.n2 )
        self.assertTrue( self.n12 == self.n3 )
        
    def test_util_NodeId___ne__(self):
        self.assertTrue( self.n0 != self.n1  )
        self.assertTrue( self.n1 != self.n1a )
        self.assertTrue( self.n1 != self.n1b )
        self.assertTrue( self.n1 != self.n1c )
        self.assertTrue( self.n1 != self.n2  )
        self.assertTrue( self.n2 != self.n3  )
        self.assertTrue( self.n3 != self.n4  )
        self.assertTrue( self.n5 != self.n6  )
        self.assertTrue( self.n6 != self.n7  )
        self.assertTrue( self.n7 != self.n8  )
        self.assertTrue( self.n8 != self.n9  )
        self.assertTrue( self.n9 != self.n10  )
        self.assertTrue( self.n10 != self.n11  )
        self.assertTrue( self.n11 != self.n12  )
        
    def test_util_NodeId___lt__(self):
        self.assertTrue( self.n4 < self.n3 )
        self.assertTrue( self.n6 < self.n5 )
        self.assertTrue( self.n7 < self.n8 )
        
    def test_util_NodeId___gt__(self):
        self.assertTrue( self.n1 > self.n0 )
        self.assertTrue( self.n2 > self.n0 )
        self.assertTrue( self.n8 > self.n9 )


if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())