import pyuaf
import unittest
from pyuaf.util.unittesting import parseArgs


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args

    return unittest.TestLoader().loadTestsFromTestCase(NodeIdIdentifierTest)



class NodeIdIdentifierTest(unittest.TestCase):

    def setUp(self):
        self.n0  = pyuaf.util.NodeIdIdentifier("SomeStringIdentifier")
        self.n0_ = pyuaf.util.NodeIdIdentifier("SomeStringIdentifier")
        self.n1  = pyuaf.util.NodeIdIdentifier(42)
        self.n2  = pyuaf.util.NodeIdIdentifier("SomeOtherStringIdentifier")
        self.n3  = pyuaf.util.NodeIdIdentifier(pyuaf.util.Guid("{10000000-0000-0000-0000-000000000000}"))
        self.n4  = pyuaf.util.NodeIdIdentifier(bytearray("abcd".encode("utf-8")))

    def test_util_NodeIdIdentifier_type(self):
        self.assertEqual( self.n1.type , pyuaf.util.nodeididentifiertypes.Identifier_Numeric )
        self.assertEqual( self.n2.type , pyuaf.util.nodeididentifiertypes.Identifier_String  )
        self.assertEqual( self.n3.type , pyuaf.util.nodeididentifiertypes.Identifier_Guid    )
        self.assertEqual( self.n4.type , pyuaf.util.nodeididentifiertypes.Identifier_Opaque  )

    def test_util_NodeIdIdentifier_idString(self):
        self.assertEqual( self.n0.idString , "SomeStringIdentifier" )

    def test_util_NodeIdIdentifier_idNumeric(self):
        self.assertEqual( self.n1.idNumeric , 42 )

    def test_util_NodeIdIdentifier_idGuid(self):
        self.assertEqual( self.n3.idGuid , pyuaf.util.Guid("{10000000-0000-0000-0000-000000000000}") )

    def test_util_NodeIdIdentifier_idOpaque(self):
        self.assertEqual( self.n4.idOpaque , bytearray("abcd".encode("utf-8")) )

    def test_util_NodeIdIdentifier___eq__(self):
        self.assertTrue( self.n0 == self.n0_ )

    def test_util_NodeIdIdentifier___ne__(self):
        self.assertTrue( self.n0 != self.n1 )
        self.assertTrue( self.n0 != self.n2 )

    def test_util_NodeIdIdentifier___lt__(self):
        self.assertTrue( self.n1 < self.n0 )
        self.assertTrue( self.n2 < self.n0 )

    def test_util_NodeIdIdentifier___gt__(self):
        self.assertTrue( self.n0 > self.n1 )
        self.assertTrue( self.n0 > self.n2 )


if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())