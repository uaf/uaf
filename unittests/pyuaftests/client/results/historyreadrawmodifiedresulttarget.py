import pyuaf
import unittest
from pyuaf.util.unittesting import parseArgs, testVector


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(HistoryReadRawModifiedResultTargetTest)



class HistoryReadRawModifiedResultTargetTest(unittest.TestCase):
    
    def setUp(self):
        self.target0 = pyuaf.client.results.HistoryReadRawModifiedResultTarget()
        
        self.target1 = pyuaf.client.results.HistoryReadRawModifiedResultTarget()
        self.target1.clientConnectionId = 3
        self.target1.status.setGood()
        self.target1.autoReadMore = 10
        self.target1.continuationPoint = bytearray("\01\02\03")
        self.target1.dataValues.resize(1)
        self.target1.dataValues[0].data = pyuaf.util.primitives.UInt16(42)
        self.target1.modificationInfos.resize(1)
        self.target1.modificationInfos[0].userName = "userName"
    
    def test_client_HistoryReadRawModifiedResultTarget_clientConnectionId(self):
        self.assertEqual( self.target1.clientConnectionId , 3 )
    
    def test_client_HistoryReadRawModifiedResultTarget_status(self):
        status = pyuaf.util.Status()
        status.setGood()
        self.assertEqual( self.target1.status , status )
    
    def test_client_HistoryReadRawModifiedResultTarget_autoReadMore(self):
        self.assertEqual( self.target1.autoReadMore , 10 )
    
    def test_client_HistoryReadRawModifiedResultTarget_continuationPoint(self):
        self.assertEqual( self.target1.continuationPoint , bytearray("\01\02\03") )
    
    def test_client_HistoryReadRawModifiedResultTarget_dataValues(self):
        self.assertEqual( self.target1.dataValues[0].data , pyuaf.util.primitives.UInt16(42) )
    
    def test_client_HistoryReadRawModifiedResultTarget_modificationInfos(self):
        self.assertEqual( self.target1.modificationInfos[0].userName , "userName" )
    
    
    def test_client_HistoryReadRawModifiedResultTargetVector(self):
        testVector(self, pyuaf.client.results.HistoryReadRawModifiedResultTargetVector, [self.target0, self.target1])
    


if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())

