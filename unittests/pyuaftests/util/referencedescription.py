import pyuaf
import unittest
import time
from pyuaf.util.unittesting import parseArgs, testVector


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(ReferenceDescriptionTest)



class ReferenceDescriptionTest(unittest.TestCase):
    
    def setUp(self):
        self.desc0 = pyuaf.util.ReferenceDescription()
        
        self.desc1 = pyuaf.util.ReferenceDescription()
        self.desc1.browseName  = pyuaf.util.QualifiedName("browseName", "nsUri")
        self.desc1.displayName = pyuaf.util.LocalizedText("en", "displayName")
        self.desc1.isForward = True
        self.desc1.nodeClass = pyuaf.util.nodeclasses.Method
        self.desc1.nodeId = pyuaf.util.ExpandedNodeId("identifier", "nsUri", "serverUri")
        self.desc1.referenceTypeId = pyuaf.util.NodeId("identifier", "nsUri")
        self.desc1.typeDefinition = pyuaf.util.ExpandedNodeId("identifier", "nsUri", "serverUri")
        
    
    def test_util_ReferenceDescription_browseName(self):
        self.assertEqual( self.desc1.browseName , pyuaf.util.QualifiedName("browseName", "nsUri") )
    
    def test_util_ReferenceDescription_displayName(self):
        self.assertEqual( self.desc1.displayName , pyuaf.util.LocalizedText("en", "displayName") )
    
    def test_util_ReferenceDescription_isForward(self):
        self.assertEqual( self.desc1.isForward , True )
    
    def test_util_ReferenceDescription_nodeClass(self):
        self.assertEqual( self.desc1.nodeClass , pyuaf.util.nodeclasses.Method )
    
    def test_util_ReferenceDescription_nodeId(self):
        self.assertEqual( self.desc1.nodeId , pyuaf.util.ExpandedNodeId("identifier", "nsUri", "serverUri") )
    
    def test_util_ReferenceDescription_referenceTypeId(self):
        self.assertEqual( self.desc1.referenceTypeId , pyuaf.util.NodeId("identifier", "nsUri") )
    
    def test_util_ReferenceDescription_typeDefinition(self):
        self.assertEqual( self.desc1.typeDefinition , pyuaf.util.ExpandedNodeId("identifier", "nsUri", "serverUri") )
    
    def test_util_ReferenceDescriptionVector(self):
        testVector(self, pyuaf.util.ReferenceDescriptionVector, [self.desc0, self.desc1])
    


if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())

