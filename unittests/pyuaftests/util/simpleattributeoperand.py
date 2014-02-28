import pyuaf
import unittest
import time
from pyuaf.util.unittesting import parseArgs, testVector


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(SimpleAttributeOperandTest)



class SimpleAttributeOperandTest(unittest.TestCase):
    
    def setUp(self):
        self.op0 = pyuaf.util.SimpleAttributeOperand()
        
        self.op1 = pyuaf.util.SimpleAttributeOperand()
        self.op1.attributeId = pyuaf.util.attributeids.DisplayName
        self.op1.browsePath.append( pyuaf.util.QualifiedName("name", "nsUri", 3) )
        self.op1.indexRange = "indexRange"
        self.op1.typeId = pyuaf.util.NodeId("identifier", "nsUri")
        
        
    def test_util_SimpleAttributeOperand_attributeId(self):
        self.assertEqual( self.op1.attributeId , pyuaf.util.attributeids.DisplayName )
        
    def test_util_SimpleAttributeOperand_browsePath(self):
        self.assertEqual( self.op1.browsePath[0] , pyuaf.util.QualifiedName("name", "nsUri", 3) )
        
    def test_util_SimpleAttributeOperand_indexRange(self):
        self.assertEqual( self.op1.indexRange , "indexRange" )
        
    def test_util_SimpleAttributeOperand_typeId(self):
        self.assertEqual( self.op1.typeId , pyuaf.util.NodeId("identifier", "nsUri") )
        
    def test_util_SimpleAttributeOperandVector(self):
        testVector(self, pyuaf.util.SimpleAttributeOperandVector, [self.op0, self.op1])
    


if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())

