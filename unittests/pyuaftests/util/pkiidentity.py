import pyuaf
import unittest
from pyuaf.util.unittesting import parseArgs, testVector


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(PkiIdentityTest)



class PkiIdentityTest(unittest.TestCase):
    
    def setUp(self):
        self.id0 = pyuaf.util.PkiIdentity()
        
        self.id1 = pyuaf.util.PkiIdentity()
        self.id1.organization = "organization"
        self.id1.organizationUnit = "organizationUnit"
        self.id1.locality = "locality"
        self.id1.state = "state"
        self.id1.country = "country"
        self.id1.commonName = "commonName"
        self.id1.domainComponent = "domainComponent"
        
    
    def test_util_PkiIdentity_isEmpty(self):
        self.assertTrue( self.id0.isEmpty() )
        self.assertFalse( self.id1.isEmpty() )
    
    def test_util_ApplicationDescription_organization(self):
        self.assertEqual( self.id1.organization , "organization" )
    
    def test_util_ApplicationDescription_organizationUnit(self):
        self.assertEqual( self.id1.organizationUnit , "organizationUnit" )
    
    def test_util_ApplicationDescription_locality(self):
        self.assertEqual( self.id1.locality , "locality" )
    
    def test_util_ApplicationDescription_state(self):
        self.assertEqual( self.id1.state , "state" )
    
    def test_util_ApplicationDescription_country(self):
        self.assertEqual( self.id1.country , "country" )
    
    def test_util_ApplicationDescription_commonName(self):
        self.assertEqual( self.id1.commonName , "commonName" )
    
    def test_util_ApplicationDescription_domainComponent(self):
        self.assertEqual( self.id1.domainComponent , "domainComponent" )

    

if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())

