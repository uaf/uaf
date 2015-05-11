import pyuaf
import unittest
from pyuaf.util.unittesting import parseArgs, testVector


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(PkiPublicKeyTest)



class PkiPublicKeyTest(unittest.TestCase):
    
    def setUp(self):
        #self.key = pyuaf.util.PkiPublicKey()
        
        self.pair = pyuaf.util.PkiRsaKeyPair(1024)
        self.key = self.pair.publicKey()
    
    def test_util_PkiPublicKey_keyType(self):
        self.assertEqual( self.key.keyType(), pyuaf.util.PkiPublicKey.RSA )
    
    def test_util_PkiPublicKey_keySize(self):
        self.assertEqual( self.key.keySize(), 1024 )
        
    def test_util_PkiPublicKey_toDER(self):
        self.assertTrue( type(self.key.toDER()) == bytearray )
        self.assertTrue( len(self.key.toDER()) > 0 )
    
    def test_util_PkiPublicKey_fromDER(self):
        self.assertEqual( pyuaf.util.PkiPublicKey.fromDER(self.key.toDER()), self.key )
    
    def test_util_PkiPublicKey_getErrors(self):
        key = pyuaf.util.PkiPublicKey()
        key.keySize() # generates errors
        errors = key.getErrors()
        self.assertTrue( len(errors) > 0 )
        for s in errors:
            self.assertEqual( type(s), str )
    

    

if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())

