import pyuaf
import unittest
from pyuaf.util.unittesting import parseArgs


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(ExpandedNodeIdTest)



class ExpandedNodeIdTest(unittest.TestCase):
    
    def setUp(self):
        self.n0  = pyuaf.util.ExpandedNodeId()
        self.n1  = pyuaf.util.ExpandedNodeId("SomeStringIdentifier", "SomeNameSpaceUri", "SomeServerUri")
        self.n2  = pyuaf.util.ExpandedNodeId("SomeStringIdentifier", 42, "SomeServerUri")
        self.n3  = pyuaf.util.ExpandedNodeId(21, "SomeNameSpaceUri", "SomeServerUri")
        self.n4  = pyuaf.util.ExpandedNodeId(21, 42, "SomeServerUri")
        self.n5  = pyuaf.util.ExpandedNodeId("SomeStringIdentifier", "SomeNameSpaceUri", 84)
        self.n6  = pyuaf.util.ExpandedNodeId("SomeStringIdentifier", 42, 84)
        self.n7  = pyuaf.util.ExpandedNodeId(21, "SomeNameSpaceUri", 84)
        self.n8  = pyuaf.util.ExpandedNodeId(21, 42, 84)
        self.n9  = pyuaf.util.ExpandedNodeId(pyuaf.util.NodeId(21, "SomeNameSpaceUri"), "SomeServerUri", 84)
        self.n10 = pyuaf.util.ExpandedNodeId(pyuaf.util.NodeId("SomeStringIdentifier", 42), "SomeServerUri", 84)
        
        self.n0_  = pyuaf.util.ExpandedNodeId()
        self.n1_  = pyuaf.util.ExpandedNodeId("SomeStringIdentifier", "SomeNameSpaceUri", "SomeServerUri")
        self.n2_  = pyuaf.util.ExpandedNodeId("SomeStringIdentifier", 42, "SomeServerUri")
        self.n3_  = pyuaf.util.ExpandedNodeId(21, "SomeNameSpaceUri", "SomeServerUri")
        self.n4_  = pyuaf.util.ExpandedNodeId(21, 42, "SomeServerUri")
        self.n5_  = pyuaf.util.ExpandedNodeId("SomeStringIdentifier", "SomeNameSpaceUri", 84)
        self.n6_  = pyuaf.util.ExpandedNodeId("SomeStringIdentifier", 42, 84)
        self.n7_  = pyuaf.util.ExpandedNodeId(21, "SomeNameSpaceUri", 84)
        self.n8_  = pyuaf.util.ExpandedNodeId(21, 42, 84)
        self.n9_  = pyuaf.util.ExpandedNodeId(pyuaf.util.NodeId(21, "SomeNameSpaceUri"), "SomeServerUri", 84)
        self.n10_ = pyuaf.util.ExpandedNodeId(pyuaf.util.NodeId("SomeStringIdentifier", 42), "SomeServerUri", 84)
        
    def test_util_ExpandedNodeId_hasServerIndex(self):
        self.assertEqual( self.n0.hasServerIndex()  , False )
        self.assertEqual( self.n1.hasServerIndex()  , False )
        self.assertEqual( self.n2.hasServerIndex()  , False )
        self.assertEqual( self.n3.hasServerIndex()  , False )
        self.assertEqual( self.n4.hasServerIndex()  , False )
        self.assertEqual( self.n5.hasServerIndex()  , True  )
        self.assertEqual( self.n6.hasServerIndex()  , True  )
        self.assertEqual( self.n7.hasServerIndex()  , True  )
        self.assertEqual( self.n8.hasServerIndex()  , True  )
        self.assertEqual( self.n9.hasServerIndex()  , True  )
        self.assertEqual( self.n10.hasServerIndex() , True  )
    
    def test_util_ExpandedNodeId_hasServerUri(self):
        self.assertEqual( self.n0.hasServerUri()  , False )
        self.assertEqual( self.n1.hasServerUri()  , True  )
        self.assertEqual( self.n2.hasServerUri()  , True  )
        self.assertEqual( self.n3.hasServerUri()  , True  )
        self.assertEqual( self.n4.hasServerUri()  , True  )
        self.assertEqual( self.n5.hasServerUri()  , False )
        self.assertEqual( self.n6.hasServerUri()  , False )
        self.assertEqual( self.n7.hasServerUri()  , False )
        self.assertEqual( self.n8.hasServerUri()  , False )
        self.assertEqual( self.n9.hasServerUri()  , True  )
        self.assertEqual( self.n10.hasServerUri() , True  )
    
    def test_util_ExpandedNodeId_serverIndex(self):
        self.assertEqual( self.n5.serverIndex() , 84 )
    
    def test_util_ExpandedNodeId_serverUri(self):
        self.assertEqual( self.n1.serverUri() , "SomeServerUri" )
    
    def test_util_ExpandedNodeId_nodeId(self):
        self.assertEqual( self.n1.nodeId() , pyuaf.util.NodeId("SomeStringIdentifier", "SomeNameSpaceUri") )
        self.assertEqual( self.n3.nodeId() , pyuaf.util.NodeId(21, "SomeNameSpaceUri") )
    
    def test_util_ExpandedNodeId___eq__(self):
        self.assertTrue( self.n0  == self.n0_ ) 
        self.assertTrue( self.n1  == self.n1_ )
        self.assertTrue( self.n2  == self.n2_ )
        self.assertTrue( self.n3  == self.n3_ )
        self.assertTrue( self.n4  == self.n4_ )
        self.assertTrue( self.n5  == self.n5_ )
        self.assertTrue( self.n6  == self.n6_ )
        self.assertTrue( self.n7  == self.n7_ )
        self.assertTrue( self.n8  == self.n8_ )
        self.assertTrue( self.n9  == self.n9_ )
        self.assertTrue( self.n10 == self.n10_ )
        
    def test_util_ExpandedNodeId___ne__(self):
        self.assertTrue( self.n0  != self.n1  )
        self.assertTrue( self.n1  != self.n2  )
        self.assertTrue( self.n2  != self.n3  )
        self.assertTrue( self.n3  != self.n4  )
        self.assertTrue( self.n4  != self.n5  )
        self.assertTrue( self.n5  != self.n6  )
        self.assertTrue( self.n6  != self.n7  )
        self.assertTrue( self.n7  != self.n8  )
        self.assertTrue( self.n8  != self.n9  )
        self.assertTrue( self.n9  != self.n10 )
        self.assertTrue( self.n10 != self.n0  )
        
    def test_util_ExpandedNodeId___lt__(self):
        self.assertTrue( self.n3 < self.n4 )
        self.assertTrue( self.n5 < self.n6 )
        
    def test_util_ExpandedNodeId___gt__(self):
        self.assertTrue( self.n1 > self.n0 )
        self.assertTrue( self.n2 > self.n0 )



if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())