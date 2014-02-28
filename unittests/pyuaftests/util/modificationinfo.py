import pyuaf
import unittest
import time
from pyuaf.util.unittesting import parseArgs, testVector


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(ModificationInfoTest)



class ModificationInfoTest(unittest.TestCase):
    
    def setUp(self):
        self.now = time.time()
        
        self.mod0 = pyuaf.util.ModificationInfo()
        
        self.mod1 = pyuaf.util.ModificationInfo()
        self.mod1.historyUpdateType = pyuaf.util.ModificationInfo.HistoryUpdateType_Update
        self.mod1.modificationTime = pyuaf.util.DateTime(self.now)
        self.mod1.userName = "userName"
        
        
    def test_util_ModificationInfo_historyUpdateType(self):
        self.assertEqual( self.mod1.historyUpdateType , pyuaf.util.ModificationInfo.HistoryUpdateType_Update )
        
    def test_util_ModificationInfo_modificationTime(self):
        self.assertEqual( self.mod1.modificationTime , pyuaf.util.DateTime(self.now) )
        
    def test_util_ModificationInfo_userName(self):
        self.assertEqual( self.mod1.userName , "userName" )
    
    def test_util_ModificationInfoVector(self):
        testVector(self, pyuaf.util.ModificationInfoVector, [self.mod0, self.mod1])
    


if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())

