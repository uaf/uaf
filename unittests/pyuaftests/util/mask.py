import pyuaf
import unittest
from pyuaf.util.unittesting import parseArgs


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(MaskTest)



class MaskTest(unittest.TestCase):
    
    def setUp(self):
        self.m0 = pyuaf.util.Mask(5, True)
        self.m1 = pyuaf.util.Mask(7, False)
        self.m0.unset(1)
        self.m0.unset(2)
        self.m1.set(2)
        self.m1.set(3)
    
    def test_util_Mask_size(self):
        self.assertEqual( self.m0.size() , 5 )
        self.assertEqual( self.m1.size() , 7 )
    
    def test_util_Mask_setCount(self):
        self.assertEqual( self.m0.setCount() , 3 )
        self.assertEqual( self.m1.setCount() , 2 )
    
    def test_util_Mask_unsetCount(self):
        self.assertEqual( self.m0.unsetCount() , 2 )
        self.assertEqual( self.m1.unsetCount() , 5 )
    
    def test_util_Mask_isSet(self):
        self.assertEqual( self.m0.isSet(0) , True  )
        self.assertEqual( self.m0.isSet(1) , False )
    
    def test_util_Mask_isUnset(self):
        self.assertEqual( self.m0.isUnset(0) , False )
        self.assertEqual( self.m0.isUnset(1) , True  )
    
    def test_util_Mask___and__(self):
        logicalAndResult = pyuaf.util.Mask(5, False)
        logicalAndResult.set(3)
        self.assertEqual( (self.m0 & self.m1) , logicalAndResult    )
        self.assertEqual( (self.m1 & self.m0) , (self.m0 & self.m1) )
    


if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())
