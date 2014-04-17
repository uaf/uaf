import pyuaf
import unittest
from pyuaf.util.unittesting import parseArgs, testVector


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(MethodCallRequestTargetTest)



class MethodCallRequestTargetTest(unittest.TestCase):
    
    def setUp(self):
        self.target0 = pyuaf.client.requests.MethodCallRequestTarget()
        
        self.target1 = pyuaf.client.requests.MethodCallRequestTarget()
        self.target1.address = pyuaf.util.Address( pyuaf.util.NodeId("id", "ns"), "svr" )
        self.target1.browseDirection = pyuaf.util.browsedirections.Inverse
        self.target1.includeSubtypes = True
        self.target1.nodeClassMask = 4
        self.target1.referenceTypeId = pyuaf.util.NodeId("id", "ns")
        self.target1.resultMask = 5
        
        self.target1.inputArguments.resize(2)
        self.target1.inputArguments[0] = pyuaf.util.primitives.UInt16(8)
        self.target1.inputArguments[1] = pyuaf.util.LocalizedText("en", "test")
        self.target1.methodAddress = pyuaf.util.Address( pyuaf.util.NodeId("id0", "ns"), "svr" )
        self.target1.objectAddress = pyuaf.util.Address( pyuaf.util.NodeId("id1", "ns"), "svr" )
    
    def test_client_MethodCallRequestTarget_address(self):
        self.assertEqual( self.target1.address , pyuaf.util.Address( pyuaf.util.NodeId("id", "ns"), "svr" ) )
    
    def test_client_MethodCallRequestTarget_browseDirection(self):
        self.assertEqual( self.target1.browseDirection , pyuaf.util.browsedirections.Inverse )
    
    def test_client_MethodCallRequestTarget_includeSubtypes(self):
        self.assertEqual( self.target1.includeSubtypes , True )
    
    def test_client_MethodCallRequestTarget_nodeClassMask(self):
        self.assertEqual( self.target1.nodeClassMask , 4 )
    
    def test_client_MethodCallRequestTarget_referenceTypeId(self):
        self.assertEqual( self.target1.referenceTypeId , pyuaf.util.NodeId("id", "ns") )
    
    def test_client_MethodCallRequestTarget_resultMask(self):
        self.assertEqual( self.target1.resultMask , 5 )
    
    def test_client_MethodCallRequestTarget_methodAddress(self):
        self.assertEqual( self.target1.methodAddress , pyuaf.util.Address( pyuaf.util.NodeId("id0", "ns"), "svr" ) )
    
    def test_client_MethodCallRequestTarget_objectAddress(self):
        self.assertEqual( self.target1.objectAddress , pyuaf.util.Address( pyuaf.util.NodeId("id1", "ns"), "svr" ) )
    
    def test_client_MethodCallRequestTarget_inputArguments(self):
        self.assertEqual( self.target1.inputArguments[0] , pyuaf.util.primitives.UInt16(8) )
        self.assertEqual( self.target1.inputArguments[1] , pyuaf.util.LocalizedText("en", "test") )
    
    def test_client_MethodCallRequestTargetVector(self):
        testVector(self, pyuaf.client.requests.MethodCallRequestTargetVector, [self.target0, self.target1])
    


if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())

