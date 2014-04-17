import pyuaf
import unittest
from pyuaf.util.unittesting import parseArgs, testVector


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(SessionSecuritySettingsTest)



class SessionSecuritySettingsTest(unittest.TestCase):
    
    def setUp(self):
        self.info0 = pyuaf.client.settings.SessionSecuritySettings()
        
        self.info1 = pyuaf.client.settings.SessionSecuritySettings()
        self.info1.messageSecurityMode = pyuaf.util.messagesecuritymodes.Mode_SignAndEncrypt
        self.info1.securityPolicy = pyuaf.util.securitypolicies.UA_Basic128
        self.info1.userCertificateFileName = "userCertificateFileName"
        self.info1.userName = "userName"
        self.info1.userPassword = "userPassword"
        self.info1.userPrivateKeyFileName = "userPrivateKeyFileName"
        self.info1.userTokenType = pyuaf.util.usertokentypes.Anonymous
    
    def test_client_SessionSecuritySettings_messageSecurityMode(self):
        self.assertEqual( self.info1.messageSecurityMode , pyuaf.util.messagesecuritymodes.Mode_SignAndEncrypt )
    
    def test_client_SessionSecuritySettings_securityPolicy(self):
        self.assertEqual( self.info1.securityPolicy , pyuaf.util.securitypolicies.UA_Basic128 )
    
    def test_client_SessionSecuritySettings_userCertificateFileName(self):
        self.assertEqual( self.info1.userCertificateFileName , "userCertificateFileName" )
    
    def test_client_SessionSecuritySettings_userName(self):
        self.assertEqual( self.info1.userName , "userName" )
    
    def test_client_SessionSecuritySettings_userPassword(self):
        self.assertEqual( self.info1.userPassword , "userPassword" )
    
    def test_client_SessionSecuritySettings_userPrivateKeyFileName(self):
        self.assertEqual( self.info1.userPrivateKeyFileName , "userPrivateKeyFileName" )
    
    def test_client_SessionSecuritySettings_userTokenType(self):
        self.assertEqual( self.info1.userTokenType , pyuaf.util.usertokentypes.Anonymous )
    
    def test_client_SessionSecuritySettingsVector(self):
        testVector(self, pyuaf.client.settings.SessionSecuritySettingsVector, [self.info0, self.info1])
    


if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())

