import pyuaf
import unittest
from pyuaf.util.unittesting import parseArgs, testVector


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(ReadRequestTargetTest)



class ReadRequestTargetTest(unittest.TestCase):
    
    def setUp(self):
        self.target0 = pyuaf.client.requests.ReadRequestTarget()
        
        self.target1 = pyuaf.client.requests.ReadRequestTarget()
        self.target1.address = pyuaf.util.Address( pyuaf.util.NodeId("id", "ns"), "svr" )
        self.target1.browseDirection = pyuaf.util.browsedirections.Inverse
        self.target1.includeSubtypes = True
        self.target1.nodeClassMask = 4
        self.target1.referenceTypeId = pyuaf.util.NodeId("id", "ns")
        self.target1.resultMask = 5
        
        self.target1.attributeId = pyuaf.util.attributeids.ContainsNoLoops
    
    def test_client_ReadRequestTarget_address(self):
        self.assertEqual( self.target1.address , pyuaf.util.Address( pyuaf.util.NodeId("id", "ns"), "svr" ) )
    
    def test_client_ReadCallRequestTarget_browseDirection(self):
        self.assertEqual( self.target1.browseDirection , pyuaf.util.browsedirections.Inverse )
    
    def test_client_ReadRequestTarget_includeSubtypes(self):
        self.assertEqual( self.target1.includeSubtypes , True )
    
    def test_client_ReadRequestTarget_nodeClassMask(self):
        self.assertEqual( self.target1.nodeClassMask , 4 )
    
    def test_client_ReadRequestTarget_referenceTypeId(self):
        self.assertEqual( self.target1.referenceTypeId , pyuaf.util.NodeId("id", "ns") )
    
    def test_client_ReadRequestTarget_resultMask(self):
        self.assertEqual( self.target1.resultMask , 5 )
    
    def test_client_ReadRequestTarget_attributeId(self):
        self.assertEqual( self.target1.attributeId , pyuaf.util.attributeids.ContainsNoLoops )
    
    def test_client_ReadRequestTargetVector(self):
        testVector(self, pyuaf.client.requests.ReadRequestTargetVector, [self.target0, self.target1])
    


if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())

