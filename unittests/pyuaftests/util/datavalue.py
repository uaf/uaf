import pyuaf
import unittest
from pyuaf.util.unittesting import parseArgs, testVector


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(DataValueTest)



class DataValueTest(unittest.TestCase):
    
    def setUp(self):
        self.d0  = pyuaf.util.DataValue()
        self.d1  = pyuaf.util.DataValue(pyuaf.util.primitives.UInt16(123))
        
        self.d2  = pyuaf.util.DataValue(pyuaf.util.primitives.Int64(456), pyuaf.util.opcuastatuscodes.OpcUa_BadArgumentsMissing)
        self.d2_ = pyuaf.util.DataValue(pyuaf.util.primitives.Int64(456), pyuaf.util.opcuastatuscodes.OpcUa_BadArgumentsMissing)
        
        self.d3 = pyuaf.util.DataValue()
        self.d3.data = pyuaf.util.LocalizedText("en", "some text")
        self.d3.serverPicoseconds = 123
        self.d3.serverTimestamp = pyuaf.util.DateTime(1.23)
        self.d3.sourcePicoseconds = 456
        self.d3.sourceTimestamp = pyuaf.util.DateTime(4.56)
        self.d3.opcUaStatusCode = pyuaf.util.opcuastatuscodes.OpcUa_BadDataLost
    
    def test_util_DataValue_data(self):
        self.assertEqual( self.d0.data , None )
        self.assertEqual( self.d1.data , pyuaf.util.primitives.UInt16(123) )
        self.assertEqual( self.d2.data , pyuaf.util.primitives.Int64(456) )
        self.assertEqual( self.d3.data , pyuaf.util.LocalizedText("en", "some text") )
    
    def test_util_DataValue_serverPicoseconds(self):
        self.assertEqual( self.d0.serverPicoseconds, 0 )
        self.assertEqual( self.d1.serverPicoseconds, 0 )
        self.assertEqual( self.d2.serverPicoseconds, 0 )
        self.assertEqual( self.d3.serverPicoseconds, 123 )
    
    def test_util_DataValue_serverTimestamp(self):
        self.assertEqual( self.d0.serverTimestamp, pyuaf.util.DateTime() )
        self.assertEqual( self.d1.serverTimestamp, pyuaf.util.DateTime() )
        self.assertEqual( self.d2.serverTimestamp, pyuaf.util.DateTime() )
        self.assertEqual( self.d3.serverTimestamp, pyuaf.util.DateTime(1.23) )
    
    def test_util_DataValue_sourcePicoseconds(self):
        self.assertEqual( self.d0.sourcePicoseconds, 0 )
        self.assertEqual( self.d1.sourcePicoseconds, 0 )
        self.assertEqual( self.d2.sourcePicoseconds, 0 )
        self.assertEqual( self.d3.sourcePicoseconds, 456 )
    
    def test_util_DataValue_sourceTimestamp(self):
        self.assertEqual( self.d0.sourceTimestamp, pyuaf.util.DateTime() )
        self.assertEqual( self.d1.sourceTimestamp, pyuaf.util.DateTime() )
        self.assertEqual( self.d2.sourceTimestamp, pyuaf.util.DateTime() )
        self.assertEqual( self.d3.sourceTimestamp, pyuaf.util.DateTime(4.56) )
    
    def test_util_DataValue_status(self):
        self.assertEqual( self.d0.opcUaStatusCode, pyuaf.util.opcuastatuscodes.OpcUa_Good )
        self.assertEqual( self.d1.opcUaStatusCode, pyuaf.util.opcuastatuscodes.OpcUa_Good )
        self.assertEqual( self.d2.opcUaStatusCode, pyuaf.util.opcuastatuscodes.OpcUa_BadArgumentsMissing )
        
        self.assertEqual( self.d3.opcUaStatusCode, pyuaf.util.opcuastatuscodes.OpcUa_BadDataLost )
    
    def test_util_DataValue___eq__(self):
        self.assertTrue( self.d2 == self.d2_ )
    
    def test_util_DataValue___ne__(self):
        self.assertTrue( self.d0 != self.d1 )
        self.assertTrue( self.d1 != self.d2 )
        self.assertTrue( self.d2 != self.d3 )
    
    def test_util_DataValue___lt__(self):
        self.assertTrue( self.d2 < self.d3 )
    
    def test_util_DataValue___gt__(self):
        self.assertTrue( self.d3 > self.d2 )
    
    def test_util_DataValueVector(self):
        testVector(self, pyuaf.util.DataValueVector, [self.d0, self.d1, self.d2, self.d3])
        


if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())
        
