import pyuaf
import unittest
from pyuaf.util.unittesting import parseArgs, testVector


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args

    return unittest.TestLoader().loadTestsFromTestCase(BrowseResultTargetTest)



class BrowseResultTargetTest(unittest.TestCase):

    def setUp(self):
        self.target0 = pyuaf.client.results.BrowseResultTarget()

        self.target1 = pyuaf.client.results.BrowseResultTarget()
        self.target1.clientConnectionId = 3
        self.target1.status.setGood()
        self.target1.autoBrowsedNext = 10
        self.target1.continuationPoint = bytearray(b"\01\02\03")
        self.target1.references.resize(1)
        self.target1.references[0].browseName = pyuaf.util.QualifiedName("browseName", "nsUri")

    def test_client_BrowseResultTarget_clientConnectionId(self):
        self.assertEqual( self.target1.clientConnectionId , 3 )

    def test_client_BrowseResultTarget_status(self):
        status = pyuaf.util.Status()
        status.setGood()
        self.assertEqual( self.target1.status , status )

    def test_client_BrowseResultTarget_autoBrowsedNext(self):
        self.assertEqual( self.target1.autoBrowsedNext , 10 )

    def test_client_BrowseResultTarget_continuationPoint(self):
        self.assertEqual( self.target1.continuationPoint , bytearray(b"\01\02\03") )

    def test_client_BrowseResultTarget_references(self):
        self.assertEqual( self.target1.references[0].browseName , pyuaf.util.QualifiedName("browseName", "nsUri") )

    def test_client_BrowseResultTargetVector(self):
        testVector(self, pyuaf.client.results.BrowseResultTargetVector, [self.target0, self.target1])



if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())

