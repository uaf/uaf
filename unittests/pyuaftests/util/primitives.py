import unittest
import pyuaf

from pyuaf.util.primitives import *
from pyuaf.util.unittesting import parseArgs


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args

    return unittest.TestLoader().loadTestsFromTestCase(PrimitivesTest)



def testNumber(testcase, primitive, signed, length):
    if signed:
        minValue = -(2** (length-1))
        maxValue = 2**(length-1) - 1
        randomGoodValue = -(2**(length/2))
    else:
        minValue = 0
        maxValue = 2**length - 1
        randomGoodValue = 2**(length/2)
    testcase.assertEqual( primitive.__call__(minValue).value , minValue )
    testcase.assertEqual( primitive.__call__(str(minValue)).value , minValue )
    testcase.assertEqual( primitive.__call__(maxValue).value , maxValue )
    testcase.assertEqual( primitive.__call__(str(maxValue)).value , maxValue )
    testcase.assertEqual( primitive.__call__(randomGoodValue).value , randomGoodValue )
    testcase.assertEqual( primitive.__call__(str(randomGoodValue)).value , randomGoodValue )

    # In SWIG 2.0.10, a NotImplementedError exception is raised.
    # in SWIG 4.0.2, a TypeError exception is raised.
    testcase.assertRaises(Exception, primitive , minValue - 1 )
    testcase.assertRaises(Exception, primitive , maxValue + 1 )



class PrimitivesTest(unittest.TestCase):

    def test_util_primitives_Bool(self):
        self.assertEqual( Boolean(True).value , True )
        self.assertEqual( Boolean("True").value , True )
        self.assertEqual( Boolean(1).value , True )
        self.assertEqual( Boolean("1").value , True )
        self.assertEqual( Boolean(False).value , False )
        self.assertEqual( Boolean(0).value , False )
        self.assertEqual( Boolean("anystring").value , True )

    def test_util_primitives_Byte(self):
        testNumber(self, Byte, False, 8 )

    def test_util_primitives_SByte(self):
        testNumber(self, SByte, True, 8 )

    def test_util_primitives_UInt16(self):
        testNumber(self, UInt16, False, 16 )

    def test_util_primitives_Int16(self):
        testNumber(self, Int16, True, 16 )

    def test_util_primitives_UInt32(self):
        testNumber(self, UInt32, False, 32 )

    def test_util_primitives_Int32(self):
        testNumber(self, Int32, True, 32 )

    def test_util_primitives_UInt64(self):
        testNumber(self, UInt64, False, 64 )

    def test_util_primitives_Int64(self):
        testNumber(self, Int64, True, 64 )

    def test_util_primitives_Float(self):
        self.assertTrue( Float(1.23).value - 1.23 < 0.000001 )
        self.assertTrue( Float("1.23").value - 1.23 < 0.000001)
        self.assertTrue( Float(-1.23).value + 1.23 < 0.000001 )
        self.assertTrue( Float("-1.23").value + 1.23 < 0.000001)
        self.assertTrue( Float(5).value - 5 < 0.000001 )
        self.assertTrue( Float("5").value - 5 < 0.000001 )

    def test_util_primitives_Double(self):
        self.assertTrue( Double(1.23).value - 1.23 < 0.000001 )
        self.assertTrue( Double("1.23").value - 1.23 < 0.000001)
        self.assertTrue( Double(-1.23).value + 1.23 < 0.000001 )
        self.assertTrue( Double("-1.23").value + 1.23 < 0.000001)
        self.assertTrue( Double(5).value - 5 < 0.000001 )
        self.assertTrue( Double("5").value - 5 < 0.000001 )

    def test_util_primitives_String(self):
        self.assertEqual( String("test").value, "test" )



if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())
