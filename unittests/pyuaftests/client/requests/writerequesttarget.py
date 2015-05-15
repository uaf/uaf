import pyuaf
import unittest
from pyuaf.util.unittesting import parseArgs, testVector


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(WriteRequestTargetTest)



class WriteRequestTargetTest(unittest.TestCase):
    
    def setUp(self):
        self.target0 = pyuaf.client.requests.WriteRequestTarget()
        
        self.target1 = pyuaf.client.requests.WriteRequestTarget()
        self.target1.address = pyuaf.util.Address( pyuaf.util.NodeId("id", "ns"), "svr" )
        self.target1.browseDirection = pyuaf.util.browsedirections.Inverse
        self.target1.includeSubtypes = True
        self.target1.nodeClassMask = 4
        self.target1.referenceTypeId = pyuaf.util.NodeId("id", "ns")
        self.target1.resultMask = 5
        self.target1.attributeId = pyuaf.util.attributeids.DisplayName
        self.target1.data = pyuaf.util.LocalizedText("en", "text")
        self.target1.indexRange = "indexRange"
        self.target1.serverPicoseconds = 123
        self.target1.serverTimestamp = pyuaf.util.DateTime(123.45)
        self.target1.sourcePicoseconds = 456
        self.target1.sourceTimestamp = pyuaf.util.DateTime(456.78)
        self.target1.opcUaStatusCode = pyuaf.util.opcuastatuscodes.OpcUa_Good
    
    def test_client_WriteRequestTarget_address(self):
        self.assertEqual( self.target1.address , pyuaf.util.Address( pyuaf.util.NodeId("id", "ns"), "svr" ) )
    
    def test_client_WriteCallRequestTarget_browseDirection(self):
        self.assertEqual( self.target1.browseDirection , pyuaf.util.browsedirections.Inverse )
    
    def test_client_WriteRequestTarget_includeSubtypes(self):
        self.assertEqual( self.target1.includeSubtypes , True )
    
    def test_client_WriteRequestTarget_nodeClassMask(self):
        self.assertEqual( self.target1.nodeClassMask , 4 )
    
    def test_client_WriteRequestTarget_referenceTypeId(self):
        self.assertEqual( self.target1.referenceTypeId , pyuaf.util.NodeId("id", "ns") )
    
    def test_client_WriteRequestTarget_resultMask(self):
        self.assertEqual( self.target1.resultMask , 5 )
    
    def test_client_WriteRequestTarget_attributeId(self):
        self.assertEqual( self.target1.attributeId , pyuaf.util.attributeids.DisplayName )
    
    def test_client_WriteRequestTarget_data(self):
        self.assertEqual( self.target1.data , pyuaf.util.LocalizedText("en", "text") )
    
    def test_client_WriteRequestTarget_indexRange(self):
        self.assertEqual( self.target1.indexRange , "indexRange" )
    
    def test_client_WriteRequestTarget_serverPicoseconds(self):
        self.assertEqual( self.target1.serverPicoseconds , 123 )
    
    def test_client_WriteRequestTarget_serverTimestamp(self):
        self.assertEqual( self.target1.serverTimestamp , pyuaf.util.DateTime(123.45) )
    
    def test_client_WriteRequestTarget_sourcePicoseconds(self):
        self.assertEqual( self.target1.sourcePicoseconds , 456 )
    
    def test_client_WriteRequestTarget_sourceTimestamp(self):
        self.assertEqual( self.target1.sourceTimestamp , pyuaf.util.DateTime(456.78) )
    
    def test_client_WriteRequestTarget_opcUaStatusCode(self):
        self.assertEqual( self.target1.opcUaStatusCode , pyuaf.util.opcuastatuscodes.OpcUa_Good )
    
    def test_client_WriteRequestTargetVector(self):
        testVector(self, pyuaf.client.requests.WriteRequestTargetVector, [self.target0, self.target1])
    


if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())

