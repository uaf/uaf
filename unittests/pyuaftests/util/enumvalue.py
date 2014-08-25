import pyuaf
import unittest
from pyuaf.util.unittesting import parseArgs


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(EnumValueTest)



class EnumValueTest(unittest.TestCase):
    
    def setUp(self):
        self.e0 = pyuaf.util.EnumValue()
        self.e1 = pyuaf.util.EnumValue(3)
        self.e2 = pyuaf.util.EnumValue(4, "name")
        self.e3 = pyuaf.util.EnumValue(5, "name", pyuaf.util.LocalizedText("en", "Some text"))
    
    def test_util_EnumValue_name(self):
        self.assertEqual( self.e1.name() , "" )
        self.assertEqual( self.e3.name() , "name" )
    
    def test_util_EnumValue_setName(self):
        e = pyuaf.util.EnumValue()
        e.setName("name")
        self.assertEqual( e.name() , "name" )
    
    def test_util_EnumValue_value(self):
        self.assertEqual( self.e0.value() , 0 )
        self.assertEqual( self.e1.value() , 3 )
    
    def test_util_EnumValue_setValue(self):
        e = pyuaf.util.EnumValue()
        e.setValue(42)
        self.assertEqual( e.value() , 42 )
    
    def test_util_EnumValue_documentation(self):
        self.assertEqual( self.e0.documentation() , pyuaf.util.LocalizedText() )
        self.assertEqual( self.e3.documentation() , pyuaf.util.LocalizedText("en", "Some text") )
    
    def test_util_EnumValue_setDocumentation(self):
        e = pyuaf.util.EnumValue()
        e.setDocumentation(pyuaf.util.LocalizedText("en", "Some text"))
        self.assertEqual( e.documentation() , pyuaf.util.LocalizedText("en", "Some text") )
    
    def test_util_EnumValue___eq__(self):
        self.assertTrue( self.e0 == pyuaf.util.EnumValue() )
        self.assertTrue( self.e1 == pyuaf.util.EnumValue(3) )
        self.assertTrue( self.e2 == pyuaf.util.EnumValue(4, "name") )
        self.assertTrue( self.e3 == pyuaf.util.EnumValue(5, "name", pyuaf.util.LocalizedText("en", "Some text")) )
        self.assertFalse( self.e0 == self.e1  )
    
    def test_util_EnumValue___ne__(self):
        self.assertTrue(  self.e0 != self.e1 )
        self.assertTrue( self.e0 != self.e2 )
        self.assertTrue( self.e0 != self.e3 )
        self.assertTrue( self.e1 != self.e2 )
        self.assertTrue( self.e1 != self.e3 )
        self.assertTrue( self.e2 != self.e3 )
    
    def test_util_EnumValue___lt__(self):
        self.assertTrue( self.e0 < self.e1 )
        self.assertTrue( self.e0 < self.e2 )
        self.assertTrue( self.e0 < self.e3 )
        self.assertTrue( self.e1 < self.e2 )
        self.assertTrue( self.e1 < self.e3 )
        self.assertTrue( self.e2 < self.e3 )
    
    def test_util_EnumValue___gt__(self):
        self.assertTrue( self.e3 > self.e0 )
        self.assertTrue( self.e3 > self.e1 )
        self.assertTrue( self.e3 > self.e2 )
        self.assertTrue( self.e2 > self.e0 )
        self.assertTrue( self.e2 > self.e1 )
        self.assertTrue( self.e1 > self.e0 )


if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())