import pyuaf
import unittest
from pyuaf.util.unittesting import parseArgs, testVector


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(PkiCertificateInfoTest)



class PkiCertificateInfoTest(unittest.TestCase):
    
    def setUp(self):
        self.info0 = pyuaf.util.PkiCertificateInfo()
        
        self.info1 = pyuaf.util.PkiCertificateInfo()
        self.info1.uri = "uri"
        self.info1.ipAddresses.append("address_0")
        self.info1.ipAddresses.append("address_1")
        self.info1.dnsNames.append("name_0")
        self.info1.dnsNames.append("name_1")
        self.info1.eMail = "eMail"
        
    
    def test_util_PkiCertificateInfo_uri(self):
        self.assertEqual( self.info1.uri , "uri" )
    
    def test_util_PkiCertificateInfo_ipAddresses(self):
        i = 0
        for address in self.info1.ipAddresses:
            self.assertEqual( address , "address_%d" %i )
            i += 1
    
    def test_util_PkiCertificateInfo_dnsNames(self):
        i = 0
        for name in self.info1.dnsNames:
            self.assertEqual( name , "name_%d" %i )
            i += 1
    
    def test_util_PkiCertificateInfo_eMail(self):
        self.assertEqual( self.info1.eMail , "eMail" )
    

if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())

