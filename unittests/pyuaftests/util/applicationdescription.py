import pyuaf
import unittest
from pyuaf.util.unittesting import parseArgs, testVector


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(ApplicationDescriptionTest)



class ApplicationDescriptionTest(unittest.TestCase):
    
    def setUp(self):
        self.desc0 = pyuaf.util.ApplicationDescription()
        
        self.desc1 = pyuaf.util.ApplicationDescription()
        self.desc1.applicationName     = pyuaf.util.LocalizedText("en", "applicationName")
        self.desc1.applicationType     = pyuaf.util.applicationtypes.DiscoveryServer
        self.desc1.applicationUri      = "applicationUri"
        self.desc1.discoveryProfileUri = "discoveryProfileUri"
        self.desc1.discoveryUrls.append("discoveryUrl0")
        self.desc1.discoveryUrls.append("discoveryUrl1")
        self.desc1.gatewayServerUri    = "gatewayServerUri"
        
    def test_util_ApplicationDescription_isEmpty(self):
        self.assertTrue( self.desc0.isEmpty() )
        self.assertFalse( self.desc1.isEmpty() )
    
    def test_util_ApplicationDescription_applicationName(self):
        self.assertEqual( self.desc1.applicationName , pyuaf.util.LocalizedText("en", "applicationName") )
    
    def test_util_ApplicationDescription_applicationType(self):
        self.assertEqual( self.desc1.applicationType , pyuaf.util.applicationtypes.DiscoveryServer )
    
    def test_util_ApplicationDescription_applicationUri(self):
        self.assertEqual( self.desc1.applicationUri , "applicationUri" )
    
    def test_util_ApplicationDescription_discoveryProfileUri(self):
        self.assertEqual( self.desc1.discoveryProfileUri , "discoveryProfileUri" )
    
    def test_util_ApplicationDescription_discoveryUrls(self):
        self.assertEqual( self.desc1.discoveryUrls[0] , "discoveryUrl0" )
        self.assertEqual( self.desc1.discoveryUrls[1] , "discoveryUrl1" )
    
    def test_util_ApplicationDescription_gatewayServerUri(self):
        self.assertEqual( self.desc1.gatewayServerUri , "gatewayServerUri" )
    
    def test_util_ApplicationDescriptionVector(self):
        testVector(self, pyuaf.util.ApplicationDescriptionVector, [self.desc0, self.desc1])
    


if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())

