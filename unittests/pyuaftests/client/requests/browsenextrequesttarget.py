import pyuaf
import unittest
from pyuaf.util.unittesting import parseArgs, testVector


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args

    return unittest.TestLoader().loadTestsFromTestCase(BrowseNextRequestTargetTest)



class BrowseNextRequestTargetTest(unittest.TestCase):

    def setUp(self):
        self.target0 = pyuaf.client.requests.BrowseNextRequestTarget()

        self.target1 = pyuaf.client.requests.BrowseNextRequestTarget()
        self.target1.address = pyuaf.util.Address( pyuaf.util.NodeId("id", "ns"), "svr" )
        self.target1.browseDirection = pyuaf.util.browsedirections.Inverse
        self.target1.continuationPoint = bytearray(b"\x00\x01\x02")
        self.target1.includeSubtypes = True
        self.target1.nodeClassMask = 4
        self.target1.referenceTypeId = pyuaf.util.NodeId("id", "ns")
        self.target1.resultMask = 5

    def test_client_BrowseRequestTarget_address(self):
        self.assertEqual( self.target1.address , pyuaf.util.Address( pyuaf.util.NodeId("id", "ns"), "svr" ) )

    def test_client_BrowseRequestTarget_browseDirection(self):
        self.assertEqual( self.target1.browseDirection , pyuaf.util.browsedirections.Inverse )

    def test_client_BrowseRequestTarget_continuationPoint(self):
        self.assertEqual( self.target1.continuationPoint , bytearray(b"\x00\x01\x02") )

    def test_client_BrowseRequestTarget_includeSubtypes(self):
        self.assertEqual( self.target1.includeSubtypes , True )

    def test_client_BrowseRequestTarget_nodeClassMask(self):
        self.assertEqual( self.target1.nodeClassMask , 4 )

    def test_client_BrowseRequestTarget_referenceTypeId(self):
        self.assertEqual( self.target1.referenceTypeId , pyuaf.util.NodeId("id", "ns") )

    def test_client_BrowseRequestTarget_resultMask(self):
        self.assertEqual( self.target1.resultMask , 5 )

    def test_client_BrowseRequestTargetVector(self):
        testVector(self, pyuaf.client.requests.BrowseNextRequestTargetVector, [self.target0, self.target1])



if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())

