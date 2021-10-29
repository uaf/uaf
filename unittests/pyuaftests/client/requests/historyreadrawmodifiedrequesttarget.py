import pyuaf
import unittest
from pyuaf.util.unittesting import parseArgs, testVector


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args

    return unittest.TestLoader().loadTestsFromTestCase(HistoryReadRawModifiedRequestTargetTest)



class HistoryReadRawModifiedRequestTargetTest(unittest.TestCase):

    def setUp(self):
        self.target0 = pyuaf.client.requests.HistoryReadRawModifiedRequestTarget()

        self.target1 = pyuaf.client.requests.HistoryReadRawModifiedRequestTarget()
        self.target1.address = pyuaf.util.Address( pyuaf.util.NodeId("id", "ns"), "svr" )
        self.target1.browseDirection = pyuaf.util.browsedirections.Inverse
        self.target1.includeSubtypes = True
        self.target1.nodeClassMask = 4
        self.target1.referenceTypeId = pyuaf.util.NodeId("id", "ns")
        self.target1.resultMask = 5

        self.target1.attributeId = pyuaf.util.attributeids.ContainsNoLoops
        self.target1.continuationPoint = bytearray(b"\01\02\03")
        self.target1.dataEncoding = pyuaf.util.QualifiedName("name", "uri")
        self.target1.indexRange = "indexRange"


    def test_client_HistoryReadRawModifiedRequestTarget_address(self):
        self.assertEqual( self.target1.address , pyuaf.util.Address( pyuaf.util.NodeId("id", "ns"), "svr" ) )

    def test_client_HistoryReadRawModifiedCallRequestTarget_browseDirection(self):
        self.assertEqual( self.target1.browseDirection , pyuaf.util.browsedirections.Inverse )

    def test_client_HistoryReadRawModifiedRequestTarget_includeSubtypes(self):
        self.assertEqual( self.target1.includeSubtypes , True )

    def test_client_HistoryReadRawModifiedRequestTarget_nodeClassMask(self):
        self.assertEqual( self.target1.nodeClassMask , 4 )

    def test_client_HistoryReadRawModifiedRequestTarget_referenceTypeId(self):
        self.assertEqual( self.target1.referenceTypeId , pyuaf.util.NodeId("id", "ns") )

    def test_client_HistoryReadRawModifiedRequestTarget_resultMask(self):
        self.assertEqual( self.target1.resultMask , 5 )

    def test_client_HistoryReadRawModifiedRequestTarget_attributeId(self):
        self.assertEqual( self.target1.attributeId , pyuaf.util.attributeids.ContainsNoLoops )

    def test_client_HistoryReadRawModifiedRequestTarget_continuationPoint(self):
        self.assertEqual( self.target1.continuationPoint , bytearray(b"\01\02\03") )

    def test_client_HistoryReadRawModifiedRequestTarget_dataEncoding(self):
        self.assertEqual( self.target1.dataEncoding , pyuaf.util.QualifiedName("name", "uri") )

    def test_client_HistoryReadRawModifiedRequestTarget_indexRange(self):
        self.assertEqual( self.target1.indexRange , "indexRange" )

    def test_client_HistoryReadRawModifiedRequestTargetVector(self):
        testVector(self, pyuaf.client.requests.HistoryReadRawModifiedRequestTargetVector, [self.target0, self.target1])



if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())

