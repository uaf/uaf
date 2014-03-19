import pyuaf
import unittest
from pyuaf.util.unittesting import parseArgs, testVector


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(TranslateBrowsePathsToNodeIdsResultTargetTest)



class TranslateBrowsePathsToNodeIdsResultTargetTest(unittest.TestCase):
    
    def setUp(self):
        self.target0 = pyuaf.client.results.TranslateBrowsePathsToNodeIdsResultTarget()
        
        self.target1 = pyuaf.client.results.TranslateBrowsePathsToNodeIdsResultTarget()
        self.target1.clientConnectionId = 3
        self.target1.status.setGood()
        self.target1.expandedNodeIds.resize(1)
        self.target1.expandedNodeIds[0] = pyuaf.util.ExpandedNodeId("id", "nsUri", "serverUri")
        self.target1.remainingPathIndexes.resize(1)
        self.target1.remainingPathIndexes[0] = 5
    
    def test_client_TranslateBrowsePathsToNodeIdsResultTarget_clientConnectionId(self):
        self.assertEqual( self.target1.clientConnectionId , 3 )
    
    def test_client_TranslateBrowsePathsToNodeIdsResultTarget_status(self):
        status = pyuaf.util.Status()
        status.setGood()
        self.assertEqual( self.target1.status , status )
    
    def test_client_TranslateBrowsePathsToNodeIdsResultTarget_expandedNodeIds(self):
        self.assertEqual( self.target1.expandedNodeIds[0] , pyuaf.util.ExpandedNodeId("id", "nsUri", "serverUri") )
    
    def test_client_TranslateBrowsePathsToNodeIdsResultTarget_remainingPathIndexes(self):
        self.assertEqual( self.target1.remainingPathIndexes[0] , 5 )
    
    def test_client_TranslateBrowsePathsToNodeIdsResultTargetVector(self):
        testVector(self, pyuaf.client.results.TranslateBrowsePathsToNodeIdsResultTargetVector, [self.target0, self.target1])
    


if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())

