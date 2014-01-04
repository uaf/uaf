import pyuaf
import unittest
from pyuaf.util.unittesting import parseArgs


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(LocalizedTextTest)



class LocalizedTextTest(unittest.TestCase):
    
    def setUp(self):
        self.l0  = pyuaf.util.LocalizedText("en", "Some Text")
        self.l0_ = pyuaf.util.LocalizedText("en", "Some Text")
        self.l1  = pyuaf.util.LocalizedText("en", "Some Other Text")
    
    def test_util_LocalizedText_locale(self):
        self.assertEqual( self.l0.locale() , "en" )
    
    def test_util_LocalizedText_text(self):
        self.assertEqual( self.l0.text() , "Some Text" )
    
    def test_util_LocalizedText___eq__(self):
        self.assertTrue(  self.l0 == self.l0_ )
        self.assertFalse( self.l0 == self.l1  )
    
    def test_util_LocalizedText___ne__(self):
        self.assertTrue(  self.l0 != self.l1  )
        self.assertFalse( self.l0 != self.l0_ )
    
    def test_util_LocalizedText___lt__(self):
        self.assertTrue( self.l1 < self.l0 )
    
    def test_util_LocalizedText___gt__(self):
        self.assertTrue( self.l0 > self.l1 )


if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())