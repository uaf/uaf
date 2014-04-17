import pyuaf
import unittest
from pyuaf.util.unittesting import parseArgs, testVector


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(StatusTest)



class StatusTest(unittest.TestCase):
    
    def setUp(self):
        self.s0  = pyuaf.util.Status()
        self.s1  = pyuaf.util.Status(pyuaf.util.statuscodes.Good)
        self.s2  = pyuaf.util.Status(pyuaf.util.statuscodes.InvalidRequestError)
        self.s3  = pyuaf.util.Status(pyuaf.util.statuscodes.ConnectionError, "Some connection error")
        self.s3_ = pyuaf.util.Status(pyuaf.util.statuscodes.ConnectionError, "Some connection error")
        self.s4  = pyuaf.util.Status(pyuaf.util.statuscodes.ConnectionError, "Some other connection error")
        self.s5  = pyuaf.util.Status(pyuaf.util.statuscodes.ResolutionError, "Some address resolution error")
    
    def test_util_Status_isUncertain(self):
        self.assertTrue( self.s0.isUncertain() )
        self.assertFalse( self.s1.isUncertain() )
        self.assertFalse( self.s2.isUncertain() )
    
    def test_util_Status_isNotUncertain(self):
        self.assertFalse( self.s0.isNotUncertain() )
        self.assertTrue( self.s1.isNotUncertain() )
        self.assertTrue( self.s2.isNotUncertain() )
    
    def test_util_Status_isGood(self):
        self.assertFalse( self.s0.isGood() )
        self.assertTrue( self.s1.isGood() )
        self.assertFalse( self.s2.isGood() )
    
    def test_util_Status_isNotGood(self):
        self.assertTrue( self.s0.isNotGood() )
        self.assertFalse( self.s1.isNotGood() )
        self.assertTrue( self.s2.isNotGood() )
    
    def test_util_Status_isBad(self):
        self.assertFalse( self.s0.isBad() )
        self.assertFalse( self.s1.isBad() )
        self.assertTrue( self.s2.isBad() )
    
    def test_util_Status_isNotBad(self):
        self.assertTrue( self.s0.isNotBad() )
        self.assertTrue( self.s1.isNotBad() )
        self.assertFalse( self.s2.isNotBad() )
    
    def test_util_Status_statusCode(self):
        self.assertEqual( self.s2.statusCode() , pyuaf.util.statuscodes.InvalidRequestError )
    
    def test_util_Status_statusCodeName(self):
        self.assertEqual( self.s2.statusCodeName() , "InvalidRequestError" )
    
    def test_util_Status_addDiagnostic(self):
        self.s0.addDiagnostic("test")
        self.assertEqual( self.s0.additionalDiagnostics().hasDescription() , True   )
        self.assertEqual( self.s0.additionalDiagnostics().getDescription() , "test" )
    
    def test_util_Status___eq__(self):
        self.assertTrue( self.s3 == self.s3_ )
    
    def test_util_Status___ne__(self):
        self.assertTrue( self.s3 != self.s4 )
        self.assertTrue( self.s3 != self.s5 )
    
    def test_util_Status___lt__(self):
        self.assertTrue( self.s3 < self.s4 )
        self.assertTrue( self.s3 < self.s5 )
    
    def test_util_Status___gt__(self):
        self.assertTrue( self.s4 > self.s3 )
        self.assertTrue( self.s5 > self.s3 )
    
    def test_util_StatusVector(self):
        testVector(self, pyuaf.util.StatusVector, [self.s0, self.s1, self.s2, self.s3, self.s4, self.s5])
        


if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())
        
