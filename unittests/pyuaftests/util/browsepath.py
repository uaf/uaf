import unittest
import pyuaf

from pyuaf.util import QualifiedName, ExpandedNodeId, RelativePathElement, BrowsePath
from pyuaf.util.unittesting import parseArgs


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(BrowsePathTest)



class BrowsePathTest(unittest.TestCase):
    
    def setUp(self):
        self.nsUri = "someNameSpaceUri"
    
        self.startingExpandedNodeId = ExpandedNodeId("someId", self.nsUri, "someServerUri")
    
        self.element0 = RelativePathElement(QualifiedName("element0", self.nsUri))
        self.element1 = RelativePathElement(QualifiedName("element1", self.nsUri))
        
        self.b0 = BrowsePath()
        self.b1 = BrowsePath(self.startingExpandedNodeId, [self.element0, self.element1])
    
    def test_util_BrowsePath_startingExpandedNodeId(self):
        self.assertEqual( self.b0.startingExpandedNodeId , ExpandedNodeId() )
        self.assertEqual( self.b1.startingExpandedNodeId , self.startingExpandedNodeId )
    
    def test_util_BrowsePath_relativePath(self):
        self.assertEqual( len(self.b0.relativePath) , 0 )
        self.assertEqual( self.b1.relativePath[0] , self.element0 )
        self.assertEqual( self.b1.relativePath[1] , self.element1 )



if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())
