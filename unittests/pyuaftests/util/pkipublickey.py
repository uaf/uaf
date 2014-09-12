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
        self.key = pyuaf.util.PkiPublicKey()
        self.defaultDER = bytearray(b'0\x080\x03\x06\x01\x00\x03\x01\x00')
    
    def test_util_PkiPublicKey_keyType(self):
        self.assertEqual( self.key.keyType(), pyuaf.util.PkiPublicKey.Unknown )
    
    def test_util_PkiPublicKey_keySize(self):
        self.assertEqual( self.key.keySize(), -1 )
        
    def test_util_PkiPublicKey_toDER(self):
        self.assertEqual( self.key.toDER(), self.defaultDER )
    
    def test_util_PkiPublicKey_fromDER(self):
        self.assertEqual( pyuaf.util.PkiPublicKey.fromDER(self.defaultDER), self.key )
    
    def test_util_PkiPublicKey_getErrors(self):
        self.key.keySize() # generates errors
        errors = self.key.getErrors()
        self.assertTrue( len(errors) > 0 )
        for s in errors:
            self.assertEqual( type(s), str )
    

    

if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())

