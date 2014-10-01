import pyuaf
import unittest
import os
from pyuaf.util.unittesting import parseArgs, testVector


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(PkiCertificateTest)



class PkiCertificateTest(unittest.TestCase):
    
    def setUp(self):
        self.cert0 = pyuaf.util.PkiCertificate()
        
        keyPair = pyuaf.util.PkiRsaKeyPair(1024)
        self.issuerPrivateKey = keyPair.privateKey()
        self.subjectPublicKey = keyPair.publicKey()
        
        self.identity = pyuaf.util.PkiIdentity()
        self.identity.commonName         = "commonName"
        self.identity.organization       = "organization"
        self.identity.organizationUnit   = "organizationUnit"
        self.identity.locality           = "locality"
        self.identity.state              = "state"
        self.identity.country            = "BE"
        self.identity.domainComponent    = "domainComponent"
        
        self.info = pyuaf.util.PkiCertificateInfo()
        self.info.uri        = "uri"
        self.info.dns        = "dns"
        self.info.eMail      = "eMail"
        self.info.validTime  = 60*60*24*365*5
        self.info.ipAddresses.append("192.168.0.94")
        self.info.dnsNames.append("dns")
        
        self.cert1 = pyuaf.util.PkiCertificate(self.info, self.identity, self.subjectPublicKey,  self.identity, self.issuerPrivateKey)
        
    
    def test_util_PkiCertificate_publicKey(self):
        self.assertEqual( self.cert1.publicKey(), self.subjectPublicKey )
    
    def test_util_PkiCertificate_commonName(self):
        self.assertEqual( self.cert1.commonName(), "commonName" )
    
    def test_util_PkiCertificate_subject(self):
        self.assertEqual( self.cert1.subject(), self.identity )
    
    def test_util_PkiCertificate_issuer(self):
        self.assertEqual( self.cert1.issuer(), self.identity )
    
    def test_util_PkiCertificate_subjectNameHash(self):
        self.assertTrue( self.cert1.subjectNameHash() > 0 )
    
    def test_util_PkiCertificate_info(self):
        # note that validTime is not filled (see docs)! 
        # So we do assign it manually, in order to easily test the equality:
        info = self.cert1.info()
        info.validTime = self.info.validTime
        self.assertEqual( info, self.info )
    
    def test_util_PkiCertificate_validFrom(self):
        now = pyuaf.util.DateTime.now()
        self.assertTrue( type(self.cert1.validFrom()) == pyuaf.util.DateTime )
        self.assertTrue( self.cert1.validFrom().secsTo(now) < 2)
    
    def test_util_PkiCertificate_validTo(self):
        now = pyuaf.util.DateTime.now()
        self.assertTrue( type(self.cert1.validTo()) == pyuaf.util.DateTime )
        self.assertTrue(60*60*24*365*5 - now.secsTo(self.cert1.validTo()) < 2)
    
    def test_util_PkiCertificate_serialNumber(self):
        self.assertTrue( len(self.cert1.serialNumber()) > 0 )
    
    def test_util_PkiCertificate_signatureTypeNID(self):
        self.assertEqual( self.cert1.signatureTypeNID() , 65 )
    
    def test_util_PkiCertificate_signatureTypeString(self):
        self.assertEqual( self.cert1.signatureTypeString() , "RSA-SHA1" )
    
    def test_util_PkiCertificate_isNull(self):
        self.assertTrue( self.cert0.isNull() )
        self.assertFalse( self.cert1.isNull() )
    
    def test_util_PkiCertificate_isValid(self):
        self.assertFalse( self.cert0.isValid() )
        self.assertTrue( self.cert1.isValid() )
    
    def test_util_PkiCertificate_isSelfSigned(self):
        self.assertFalse( self.cert0.isSelfSigned() )
        self.assertTrue( self.cert1.isSelfSigned() )
    
    def test_util_PkiCertificate_hasExtension(self):
        self.assertTrue( self.cert1.hasExtension(pyuaf.util.PkiCertificate.Extension_SubjectKeyIdentifier))
    
    def test_util_PkiCertificate_extensionValue(self):
        self.assertTrue( len(self.cert1.extensionValue(pyuaf.util.PkiCertificate.Extension_SubjectKeyIdentifier)) > 0)
    
    def test_util_PkiCertificate_toDER(self):
        self.assertTrue( type(self.cert1.toDER()) == bytearray)
        self.assertTrue( len(self.cert1.toDER()) > 0)
        
    def test_util_PkiCertificate_toDERFile(self):
        path = "test_util_PkiCertificate_toDERFile"
        self.cert1.toDERFile(path)
        self.assertTrue( os.path.exists(path) )
        os.remove(path)
        
    def test_util_PkiCertificate_toPEMFile(self):
        path = "test_util_PkiCertificate_toPEMFile"
        self.cert1.toPEMFile(path)
        self.assertTrue( os.path.exists(path) )
        os.remove(path)
    
    def test_util_PkiCertificate_fromDER(self):
        der = self.cert1.toDER()
        cert = pyuaf.util.PkiCertificate.fromDER(der)
        self.assertEqual(cert.commonName(), "commonName")
    
    def test_util_PkiCertificate_fromPEMFile(self):
        path = "test_util_PkiCertificate_fromPEMFile"
        self.cert1.toPEMFile(path)
        self.assertTrue(os.path.exists(path))
        cert = pyuaf.util.PkiCertificate.fromPEMFile(path)
        self.assertTrue( cert.isValid() )
        os.remove(path)
    
    def test_util_PkiCertificate_fromDERFile(self):
        path = "test_util_PkiCertificate_fromDERFile"
        self.cert1.toDERFile(path)
        self.assertTrue(os.path.exists(path))
        cert = pyuaf.util.PkiCertificate.fromDERFile(path)
        self.assertTrue( cert.isValid() )
        os.remove(path)
        
    def test_util_PkiCertificate_thumbPrint(self):
        self.assertTrue( type(self.cert1.thumbPrint()) == bytearray)
        self.assertTrue( len(self.cert1.thumbPrint()) > 0)
    
    def test_util_PkiCertificate_getErrors(self):
        self.cert0.thumbPrint() # generates errors
        errors = self.cert0.getErrors()
        self.assertTrue( len(errors) > 0 )
        for s in errors:
            self.assertEqual( type(s), str )
    

    

if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())

