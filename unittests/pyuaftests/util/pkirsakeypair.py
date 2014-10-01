import pyuaf
import unittest
import os
from pyuaf.util.unittesting import parseArgs, testVector


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(PkiRsaKeyPairTest)



class PkiRsaKeyPairTest(unittest.TestCase):
    
    def setUp(self):
        self.pair0 = pyuaf.util.PkiRsaKeyPair()
        self.pair1 = pyuaf.util.PkiRsaKeyPair(2048)
        self.pair2 = pyuaf.util.PkiRsaKeyPair(0)
    
    def test_util_PkiRsaKeyPair_privateKey(self):
        self.assertTrue( type(self.pair0.privateKey()) == pyuaf.util.PkiPrivateKey )
    
    def test_util_PkiRsaKeyPair_publicKey(self):
        self.assertTrue( type(self.pair0.publicKey()) == pyuaf.util.PkiPublicKey )
    
    def test_util_PkiRsaKeyPair_toDER(self):
        self.assertTrue( type(self.pair0.toDER()) == bytearray )
        self.assertTrue( len(self.pair0.toDER()) > 0 )
    
    def test_util_PkiRsaKeyPair_checkKeyPair(self):
        self.assertTrue( pyuaf.util.PkiRsaKeyPair.checkKeyPair(self.pair0.publicKey(), self.pair0.privateKey()))
    
    def test_util_PkiRsaKeyPair_toPEMFile_without_password(self):
        path = "test_util_PkiRsaKeyPair_toPEMFile_without_password"
        self.pair0.toPEMFile(path)
        self.assertTrue( os.path.exists(path) )
        os.remove(path)
        
    def test_util_PkiRsaKeyPair_toPEMFile_with_password(self):
        path = "test_util_PkiRsaKeyPair_toPEMFile_with_password"
        self.pair0.toPEMFile(path, "password")
        self.assertTrue( os.path.exists(path) )
        os.remove(path)
        
    
    def test_util_PkiRsaKeyPair_fromPEMFile_without_password(self):
        path = "test_util_PkiRsaKeyPair_fromPEMFile_without_password"
        self.pair0.toPEMFile(path)
        self.assertTrue(os.path.exists(path))
        pair = pyuaf.util.PkiRsaKeyPair.fromPEMFile(path)
        self.assertTrue( pair.isValid() )
        os.remove(path)
        
    
    def test_util_PkiRsaKeyPair_fromPEMFile_with_valid_password(self):
        path = "test_util_PkiRsaKeyPair_fromPEMFile_without_password"
        self.pair0.toPEMFile(path, "password")
        self.assertTrue(os.path.exists(path))
        pair = pyuaf.util.PkiRsaKeyPair.fromPEMFile(path, "password")
        self.assertTrue( pair.isValid() )
        os.remove(path)
    
    def test_util_PkiRsaKeyPair_fromPEMFile_with_invalid_password(self):
        path = "test_util_PkiRsaKeyPair_fromPEMFile_with_invalid_password"
        self.pair0.toPEMFile(path, "password")
        self.assertTrue(os.path.exists(path))
        pair = pyuaf.util.PkiRsaKeyPair.fromPEMFile(path, "wrong_password")
        self.assertFalse( pair.isValid() )
        os.remove(path)
        
    
    def test_util_PkiRsaKeyPair_isValid(self):
        self.assertTrue( self.pair0.isValid() )
        self.assertTrue( self.pair1.isValid() )
        self.assertFalse( self.pair2.isValid() )
    
    def test_util_PkiRsaKeyPair_getErrors(self):
        errors = self.pair2.getErrors()
        self.assertTrue( len(errors) > 0 )
        for s in errors:
            self.assertEqual( type(s), str )

if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())

