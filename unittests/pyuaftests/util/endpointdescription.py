import pyuaf
import unittest
import time
from pyuaf.util.unittesting import parseArgs, testVector


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(EndpointDescriptionTest)



class EndpointDescriptionTest(unittest.TestCase):
    
    def setUp(self):
        self.desc0 = pyuaf.util.EndpointDescription()
        
        self.desc1 = pyuaf.util.EndpointDescription()
        self.desc1.endpointUrl = "endpointUrl"
        self.desc1.securityLevel = 3
        self.desc1.securityMode = pyuaf.util.messagesecuritymodes.Mode_SignAndEncrypt
        self.desc1.securityPolicyUri = pyuaf.util.securitypolicies.UA_Basic128Rsa15
        self.desc1.server.applicationUri = "applicationUri"
        self.desc1.transportProfileUri = "transportProfileUri"
        self.desc1.userIdentityTokens.append( pyuaf.util.UserTokenPolicy("policyId", 
                                                                         pyuaf.util.usertokentypes.Certificate,
                                                                         "issuedTokenType",
                                                                         "issuerEndpointUrl",
                                                                         "securityPolicyUri") )
        
        
    def test_util_EndpointDescription_endpointUrl(self):
        self.assertEqual( self.desc1.endpointUrl , "endpointUrl" )
        
    def test_util_EndpointDescription_securityLevel(self):
        self.assertEqual( self.desc1.securityLevel , 3 )
        
    def test_util_EndpointDescription_securityMode(self):
        self.assertEqual( self.desc1.securityMode , pyuaf.util.messagesecuritymodes.Mode_SignAndEncrypt )
        
    def test_util_EndpointDescription_securityPolicyUri(self):
        self.assertEqual( self.desc1.securityPolicyUri , pyuaf.util.securitypolicies.UA_Basic128Rsa15 )
        
    def test_util_EndpointDescription_server(self):
        self.assertEqual( self.desc1.server.applicationUri , "applicationUri" )
        
    def test_util_EndpointDescription_transportProfileUri(self):
        self.assertEqual( self.desc1.transportProfileUri , "transportProfileUri" )
        
    def test_util_EndpointDescription_userIdentityTokens(self):
        self.assertEqual( self.desc1.userIdentityTokens[0] , pyuaf.util.UserTokenPolicy("policyId", 
                                                                                        pyuaf.util.usertokentypes.Certificate,
                                                                                        "issuedTokenType",
                                                                                        "issuerEndpointUrl",
                                                                                        "securityPolicyUri") )
    
    def test_util_EndpointDescriptionVector(self):
        testVector(self, pyuaf.util.EndpointDescriptionVector, [self.desc0, self.desc1])
    


if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())

