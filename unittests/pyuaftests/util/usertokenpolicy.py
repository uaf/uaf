import pyuaf
import unittest
import time
from pyuaf.util.unittesting import parseArgs, testVector


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(UserTokenPolicyTest)



class UserTokenPolicyTest(unittest.TestCase):
    
    def setUp(self):
        self.pol0 = pyuaf.util.UserTokenPolicy()
        
        self.pol1 = pyuaf.util.UserTokenPolicy()
        self.pol1.issuedTokenType = "issuedTokenType"
        self.pol1.issuerEndpointUrl = "issuerEndpointUrl"
        self.pol1.policyId = "policyId"
        self.pol1.securityPolicyUri = "securityPolicyUri"
        self.pol1.tokenType = pyuaf.util.usertokentypes.Certificate
        
        
    def test_util_UserTokenPolicy_issuedTokenType(self):
        self.assertEqual( self.pol1.issuedTokenType , "issuedTokenType" )
        
    def test_util_UserTokenPolicy_issuerEndpointUrl(self):
        self.assertEqual( self.pol1.issuerEndpointUrl , "issuerEndpointUrl" )
        
    def test_util_UserTokenPolicy_policyId(self):
        self.assertEqual( self.pol1.policyId , "policyId" )
        
    def test_util_UserTokenPolicy_securityPolicyUri(self):
        self.assertEqual( self.pol1.securityPolicyUri , "securityPolicyUri" )
        
    def test_util_UserTokenPolicy_tokenType(self):
        self.assertEqual( self.pol1.tokenType , pyuaf.util.usertokentypes.Certificate )
    
    def test_util_UserTokenPolicyVector(self):
        testVector(self, pyuaf.util.UserTokenPolicyVector, [self.pol0, self.pol1])
    


if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())

