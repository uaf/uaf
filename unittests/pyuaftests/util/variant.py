import pyuaf
import unittest
from pyuaf.util.unittesting import parseArgs, testVector


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args

    return unittest.TestLoader().loadTestsFromTestCase(VariantTest)



class VariantTest(unittest.TestCase):

    def setUp(self):

        self.tester = pyuaf.util.__unittesthelper__.UnitTestHelper()



        ######## output typemaps ########

    def test_util_primitives_Boolean_outputtypemap(self):
        v = self.tester.testVariantTypemap_out(pyuaf.util.opcuatypes.Boolean)
        self.assertEqual( v.type() , pyuaf.util.opcuatypes.Boolean )
        self.assertEqual( v.value  , True )
        self.assertEqual( type(v)  , type(pyuaf.util.primitives.Boolean()) )

    def test_util_primitives_Byte_outputtypemap(self):
        v = self.tester.testVariantTypemap_out(pyuaf.util.opcuatypes.Byte)
        self.assertEqual( v.type() , pyuaf.util.opcuatypes.Byte )
        self.assertEqual( v.value , 3 )
        self.assertEqual( type(v) , type(pyuaf.util.primitives.Byte()) )

    def test_util_primitives_SByte_outputtypemap(self):
        v = self.tester.testVariantTypemap_out(pyuaf.util.opcuatypes.SByte)
        self.assertEqual( v.type() , pyuaf.util.opcuatypes.SByte )
        self.assertEqual( v.value , -3 )
        self.assertEqual( type(v) , type(pyuaf.util.primitives.SByte()) )

    def test_util_primitives_UInt16_outputtypemap(self):
        v = self.tester.testVariantTypemap_out(pyuaf.util.opcuatypes.UInt16)
        self.assertEqual( v.type() , pyuaf.util.opcuatypes.UInt16 )
        self.assertEqual( v.value , 3 )
        self.assertEqual( type(v) , type(pyuaf.util.primitives.UInt16()) )

    def test_util_primitives_Int16_outputtypemap(self):
        v = self.tester.testVariantTypemap_out(pyuaf.util.opcuatypes.Int16)
        self.assertEqual( v.type() , pyuaf.util.opcuatypes.Int16 )
        self.assertEqual( v.value , -3 )
        self.assertEqual( type(v) , type(pyuaf.util.primitives.Int16()) )

    def test_util_primitives_UInt32_outputtypemap(self):
        v = self.tester.testVariantTypemap_out(pyuaf.util.opcuatypes.UInt32)
        self.assertEqual( v.type() , pyuaf.util.opcuatypes.UInt32 )
        self.assertEqual( v.value , 3 )
        self.assertEqual( type(v) , type(pyuaf.util.primitives.UInt32()) )

    def test_util_primitives_Int32_outputtypemap(self):
        v = self.tester.testVariantTypemap_out(pyuaf.util.opcuatypes.Int32)
        self.assertEqual( v.type() , pyuaf.util.opcuatypes.Int32 )
        self.assertEqual( v.value , -3 )
        self.assertEqual( type(v) , type(pyuaf.util.primitives.Int32()) )

    def test_util_primitives_UInt64_outputtypemap(self):
        v = self.tester.testVariantTypemap_out(pyuaf.util.opcuatypes.UInt64)
        self.assertEqual( v.type() , pyuaf.util.opcuatypes.UInt64 )
        self.assertEqual( v.value , 3 )
        self.assertEqual( type(v) , type(pyuaf.util.primitives.UInt64()) )

    def test_util_primitives_Int64_outputtypemap(self):
        v = self.tester.testVariantTypemap_out(pyuaf.util.opcuatypes.Int64)
        self.assertEqual( v.type() , pyuaf.util.opcuatypes.Int64 )
        self.assertEqual( v.value , -3 )
        self.assertEqual( type(v) , type(pyuaf.util.primitives.Int64()) )

    def test_util_primitives_Float_outputtypemap(self):
        v = self.tester.testVariantTypemap_out(pyuaf.util.opcuatypes.Float)
        self.assertEqual( v.type() , pyuaf.util.opcuatypes.Float )
        self.assertTrue( 3.1399999 < v.value < 3.140001 )
        self.assertEqual( type(v) , type(pyuaf.util.primitives.Float()) )

    def test_util_primitives_Double_outputtypemap(self):
        v = self.tester.testVariantTypemap_out(pyuaf.util.opcuatypes.Double)
        self.assertEqual( v.type() , pyuaf.util.opcuatypes.Double )
        self.assertTrue( 3.1399999 < v.value < 3.140001 )
        self.assertEqual( type(v) , type(pyuaf.util.primitives.Double()) )

    def test_unicodeStr_outputtypemap(self):
        v = self.tester.testVariantTypemap_out(pyuaf.util.opcuatypes.String)
        self.assertEqual( v.value , (b"test \xc2\xb0".decode()) )
        self.assertEqual( type(v) , type(pyuaf.util.primitives.String()) )

    def test_bytearray_outputtypemap(self):
        v = self.tester.testVariantTypemap_out(pyuaf.util.opcuatypes.ByteString)
        self.assertEqual( type(v.value) , type(bytearray()) )
        self.assertEqual( len(v.value) , 3 )
        self.assertEqual( v.value[0] , 1 )
        self.assertEqual( v.value[1] , 2 )
        self.assertEqual( v.value[2] , 3 )

    def test_util_NodeId_outputtypemap(self):
        v = self.tester.testVariantTypemap_out(pyuaf.util.opcuatypes.NodeId)
        self.assertEqual( v , pyuaf.util.NodeId("SomeIdentifier", "nsUri", 42) )

    def test_util_ExpandedNodeId_outputtypemap(self):
        v = self.tester.testVariantTypemap_out(pyuaf.util.opcuatypes.ExpandedNodeId)
        self.assertEqual( v , pyuaf.util.ExpandedNodeId("SomeIdentifier", "nsUri", "svrUri") )

    def test_util_LocalizedText_outputtypemap(self):
        v = self.tester.testVariantTypemap_out(pyuaf.util.opcuatypes.LocalizedText)
        self.assertEqual( v , pyuaf.util.LocalizedText("en", "SomeText") )

    def test_util_QualifiedName_outputtypemap(self):
        v = self.tester.testVariantTypemap_out(pyuaf.util.opcuatypes.QualifiedName)
        self.assertEqual( v , pyuaf.util.QualifiedName("SomeName", "nsUri", 42) )

    def test_util_DateTime_outputtypemap(self):
        v = self.tester.testVariantTypemap_out(pyuaf.util.opcuatypes.DateTime)
        self.assertEqual( v , pyuaf.util.DateTime.fromString("2013-05-21T12:34:56.789Z") )

    def test_util_ExtensionObject_outputtypemap(self):
        v = self.tester.testVariantTypemap_out(pyuaf.util.opcuatypes.ExtensionObject)
        self.assertEqual( type(v) , pyuaf.util.ExtensionObject )

    def test_util_Guid_outputtypemap(self):
        v = self.tester.testVariantTypemap_out(pyuaf.util.opcuatypes.Guid)
        self.assertEqual( v , pyuaf.util.Guid("{cecf86f6-cad5-48d5-9b22-989f848acc9d}") )

    def test_util_primitives_Boolean_array_outputtypemap(self):
        v = self.tester.testVariantTypemap_out(pyuaf.util.opcuatypes.Boolean, True)
        self.assertEqual( v , [ pyuaf.util.primitives.Boolean(True),
                                pyuaf.util.primitives.Boolean(False),
                                pyuaf.util.primitives.Boolean(True) ] )

    def test_util_primitives_Byte_array_outputtypemap(self):
        v = self.tester.testVariantTypemap_out(pyuaf.util.opcuatypes.Byte, True)
        self.assertEqual( v , [ pyuaf.util.primitives.Byte(1),
                                pyuaf.util.primitives.Byte(2),
                                pyuaf.util.primitives.Byte(3) ] )

    def test_util_primitives_Byte_array_outputtypemap(self):
        v = self.tester.testVariantTypemap_out(pyuaf.util.opcuatypes.SByte, True)
        self.assertEqual( v , [ pyuaf.util.primitives.SByte(-1),
                                pyuaf.util.primitives.SByte(2),
                                pyuaf.util.primitives.SByte(-3) ] )

    def test_util_primitives_UInt16_array_outputtypemap(self):
        v = self.tester.testVariantTypemap_out(pyuaf.util.opcuatypes.UInt16, True)
        self.assertEqual( v , [ pyuaf.util.primitives.UInt16(1),
                                pyuaf.util.primitives.UInt16(2),
                                pyuaf.util.primitives.UInt16(3) ] )

    def test_util_primitives_Int16_array_outputtypemap(self):
        v = self.tester.testVariantTypemap_out(pyuaf.util.opcuatypes.Int16, True)
        self.assertEqual( v , [ pyuaf.util.primitives.Int16(-1),
                                pyuaf.util.primitives.Int16(2),
                                pyuaf.util.primitives.Int16(-3) ] )

    def test_util_primitives_UInt32_array_outputtypemap(self):
        v = self.tester.testVariantTypemap_out(pyuaf.util.opcuatypes.UInt32, True)
        self.assertEqual( v , [ pyuaf.util.primitives.UInt32(1),
                                pyuaf.util.primitives.UInt32(2),
                                pyuaf.util.primitives.UInt32(3) ] )

    def test_util_primitives_Int32_array_outputtypemap(self):
        v = self.tester.testVariantTypemap_out(pyuaf.util.opcuatypes.Int32, True)
        self.assertEqual( v , [ pyuaf.util.primitives.Int32(-1),
                                pyuaf.util.primitives.Int32(2),
                                pyuaf.util.primitives.Int32(-3) ] )

    def test_util_primitives_UInt64_array_outputtypemap(self):
        v = self.tester.testVariantTypemap_out(pyuaf.util.opcuatypes.UInt64, True)
        self.assertEqual( v , [ pyuaf.util.primitives.UInt64(1),
                                pyuaf.util.primitives.UInt64(2),
                                pyuaf.util.primitives.UInt64(3) ] )

    def test_util_primitives_Int64_array_outputtypemap(self):
        v = self.tester.testVariantTypemap_out(pyuaf.util.opcuatypes.Int64, True)
        self.assertEqual( v , [ pyuaf.util.primitives.Int64(-1),
                                pyuaf.util.primitives.Int64(2),
                                pyuaf.util.primitives.Int64(-3) ] )

    def test_util_primitives_Float_array_outputtypemap(self):
        v = self.tester.testVariantTypemap_out(pyuaf.util.opcuatypes.Float, True)
        self.assertTrue( -3.13999 > v[0].value > -3.14001 )
        self.assertTrue( 3.13999 < v[1].value < 3.14001   )
        self.assertTrue( -3.13999 > v[2].value > -3.14001 )

    def test_util_primitives_Double_array_outputtypemap(self):
        v = self.tester.testVariantTypemap_out(pyuaf.util.opcuatypes.Double, True)
        self.assertTrue( -3.13999 > v[0].value > -3.14001 )
        self.assertTrue( 3.13999 < v[1].value < 3.14001   )
        self.assertTrue( -3.13999 > v[2].value > -3.14001 )

    def test_util_primitives_String_array_outputtypemap(self):
        v = self.tester.testVariantTypemap_out(pyuaf.util.opcuatypes.String, True)
        self.assertEqual( v , [pyuaf.util.primitives.String("test1"),
                               pyuaf.util.primitives.String("test2"),
                               pyuaf.util.primitives.String("test3")] )

    def test_util_NodeId_array_outputtypemap(self):
        v = self.tester.testVariantTypemap_out(pyuaf.util.opcuatypes.NodeId, True)
        self.assertEqual( v , [pyuaf.util.NodeId("SomeIdentifier", 42),
                               pyuaf.util.NodeId("SomeIdentifier", "nsUri"),
                               pyuaf.util.NodeId("SomeIdentifier", "nsUri", 42)] )

    def test_util_ExpandedNodeId_array_outputtypemap(self):
        v = self.tester.testVariantTypemap_out(pyuaf.util.opcuatypes.ExpandedNodeId, True)
        self.assertEqual( v , [pyuaf.util.ExpandedNodeId("SomeIdentifier", 42, 21),
                               pyuaf.util.ExpandedNodeId("SomeIdentifier", "nsUri", 21),
                               pyuaf.util.ExpandedNodeId("SomeIdentifier", "nsUri", "svrUri")] )

    def test_util_LocalizedText_array_outputtypemap(self):
        v = self.tester.testVariantTypemap_out(pyuaf.util.opcuatypes.LocalizedText, True)
        self.assertEqual( v , [pyuaf.util.LocalizedText("en", "SomeText"),
                               pyuaf.util.LocalizedText("en", "SomeText"),
                               pyuaf.util.LocalizedText("en", "SomeText")] )

    def test_util_QualifiedName_array_outputtypemap(self):
        v = self.tester.testVariantTypemap_out(pyuaf.util.opcuatypes.QualifiedName, True)
        self.assertEqual( v , [pyuaf.util.QualifiedName("SomeName", 42),
                               pyuaf.util.QualifiedName("SomeName", "nsUri"),
                               pyuaf.util.QualifiedName("SomeName", "nsUri", 42)] )

    def test_util_DateTime_array_outputtypemap(self):
        v = self.tester.testVariantTypemap_out(pyuaf.util.opcuatypes.DateTime, True)
        self.assertEqual( v , [pyuaf.util.DateTime.fromString("2013-05-21T12:34:56.789Z"),
                               pyuaf.util.DateTime.fromString("2013-05-21T12:34:56.789Z"),
                               pyuaf.util.DateTime.fromString("2013-05-21T12:34:56.789Z")] )

    def test_util_ExtensionObject_array_outputtypemap(self):
        v = self.tester.testVariantTypemap_out(pyuaf.util.opcuatypes.ExtensionObject, True)
        self.assertEqual( type(v[0]) , pyuaf.util.ExtensionObject )
        self.assertEqual( type(v[1]) , pyuaf.util.ExtensionObject )
        self.assertEqual( type(v[2]) , pyuaf.util.ExtensionObject )

    def test_util_Guid_array_outputtypemap(self):
        v = self.tester.testVariantTypemap_out(pyuaf.util.opcuatypes.Guid, True)
        self.assertEqual( v , [pyuaf.util.Guid("{cecf86f6-cad5-48d5-9b22-989f848acc9d}"),
                               pyuaf.util.Guid("{cecf86f6-cad5-48d5-9b22-989f848acc9e}")] )

        ######## input typemaps ########


    def test_util_primitives_Boolean_inputtypemap(self):
        v = self.tester.testVariantTypemap_in(pyuaf.util.primitives.Boolean(True))
        self.assertEqual( v , pyuaf.util.primitives.Boolean(True) )

    def test_util_primitives_Byte_inputtypemap(self):
        v = self.tester.testVariantTypemap_in(pyuaf.util.primitives.Byte(3))
        self.assertEqual( v , pyuaf.util.primitives.Byte(3) )

    def test_util_primitives_SByte_inputtypemap(self):
        v = self.tester.testVariantTypemap_in(pyuaf.util.primitives.SByte(-3))
        self.assertEqual( v , pyuaf.util.primitives.SByte(-3) )

    def test_util_primitives_UInt16_inputtypemap(self):
        v = self.tester.testVariantTypemap_in(pyuaf.util.primitives.UInt16(3))
        self.assertEqual( v , pyuaf.util.primitives.UInt16(3) )

    def test_util_primitives_Int16_inputtypemap(self):
        v = self.tester.testVariantTypemap_in(pyuaf.util.primitives.Int16(-3))
        self.assertEqual( v , pyuaf.util.primitives.Int16(-3) )

    def test_util_primitives_UInt32_inputtypemap(self):
        v = self.tester.testVariantTypemap_in(pyuaf.util.primitives.UInt32(3))
        self.assertEqual( v , pyuaf.util.primitives.UInt32(3) )

    def test_util_primitives_Int32_inputtypemap(self):
        v = self.tester.testVariantTypemap_in(pyuaf.util.primitives.Int32(-3))
        self.assertEqual( v , pyuaf.util.primitives.Int32(-3) )

    def test_util_primitives_UInt64_inputtypemap(self):
        v = self.tester.testVariantTypemap_in(pyuaf.util.primitives.UInt64(3))
        self.assertEqual( v , pyuaf.util.primitives.UInt64(3) )

    def test_util_primitives_Int64_inputtypemap(self):
        v = self.tester.testVariantTypemap_in(pyuaf.util.primitives.Int64(-3))
        self.assertEqual( v , pyuaf.util.primitives.Int64(-3) )

    def test_util_primitives_Float_inputtypemap(self):
        v = self.tester.testVariantTypemap_in(pyuaf.util.primitives.Float(3.14))
        self.assertEqual( v , pyuaf.util.primitives.Float(3.14) )

    def test_util_primitives_Double_inputtypemap(self):
        v = self.tester.testVariantTypemap_in(pyuaf.util.primitives.Double(3.14))
        self.assertEqual( v , pyuaf.util.primitives.Double(3.14) )

    def test_util_primitives_String_inputtypemap(self):
        v = self.tester.testVariantTypemap_in("test")
        self.assertEqual( v , pyuaf.util.primitives.String("test") )

    def test_unicodeStr_inputtypemap(self):
        v = self.tester.testVariantTypemap_in("test \xc2\xb0")
        self.assertEqual( v , pyuaf.util.primitives.String("test \xc2\xb0") )

    def test_bytearray_inputtypemap(self):
        v = self.tester.testVariantTypemap_in(bytearray(b"abc"))
        self.assertEqual( v , pyuaf.util.primitives.ByteString(bytearray(b"abc")) )

    def test_util_NodeId_inputtypemap(self):
        v = self.tester.testVariantTypemap_in(pyuaf.util.NodeId("SomeIdentifier", 42))
        self.assertEqual( v , pyuaf.util.NodeId("SomeIdentifier", 42) )
        v = self.tester.testVariantTypemap_in(pyuaf.util.NodeId("SomeIdentifier", "nsUri"))
        self.assertEqual( v , pyuaf.util.NodeId("SomeIdentifier", "nsUri") )
        v = self.tester.testVariantTypemap_in(pyuaf.util.NodeId("SomeIdentifier", "nsUri", 42))
        self.assertEqual( v , pyuaf.util.NodeId("SomeIdentifier", "nsUri", 42) )

    def test_util_ExpandedNodeId_inputtypemap(self):
        v = self.tester.testVariantTypemap_in(pyuaf.util.ExpandedNodeId("SomeIdentifier", 42, 21))
        self.assertEqual( v , pyuaf.util.ExpandedNodeId("SomeIdentifier", 42, 21) )
        v = self.tester.testVariantTypemap_in(pyuaf.util.ExpandedNodeId("SomeIdentifier", "nsUri", 21))
        self.assertEqual( v , pyuaf.util.ExpandedNodeId("SomeIdentifier", "nsUri", 21) )
        v = self.tester.testVariantTypemap_in(pyuaf.util.ExpandedNodeId("SomeIdentifier", "nsUri", "svrUri"))
        self.assertEqual( v , pyuaf.util.ExpandedNodeId("SomeIdentifier", "nsUri", "svrUri") )

    def test_util_LocalizedText_inputtypemap(self):
        v = self.tester.testVariantTypemap_in(pyuaf.util.LocalizedText("en", "SomeText"))
        self.assertEqual( v , pyuaf.util.LocalizedText("en", "SomeText") )

    def test_util_QualifiedName_inputtypemap(self):
        v = self.tester.testVariantTypemap_in(pyuaf.util.QualifiedName("SomeName", 42))
        self.assertEqual( v , pyuaf.util.QualifiedName("SomeName", 42) )
        v = self.tester.testVariantTypemap_in(pyuaf.util.QualifiedName("SomeName", "nsUri"))
        self.assertEqual( v , pyuaf.util.QualifiedName("SomeName", "nsUri") )
        v = self.tester.testVariantTypemap_in(pyuaf.util.QualifiedName("SomeName", "nsUri", 42))
        self.assertEqual( v , pyuaf.util.QualifiedName("SomeName", "nsUri", 42) )

    def test_util_DateTime_inputtypemap(self):
        v = self.tester.testVariantTypemap_in(pyuaf.util.DateTime.fromString("2013-05-21T12:34:56.789Z"))
        self.assertEqual( v , pyuaf.util.DateTime.fromString("2013-05-21T12:34:56.789Z") )

    def test_util_ExtensionObject_inputtypemap(self):
        v = self.tester.testVariantTypemap_in(pyuaf.util.ExtensionObject())
        self.assertEqual( type(v) , pyuaf.util.ExtensionObject )

    def test_util_Guid_inputtypemap(self):
        v = self.tester.testVariantTypemap_in(pyuaf.util.Guid("{cecf86f6-cad5-48d5-9b22-989f848acc9d}"))
        self.assertEqual( v , pyuaf.util.Guid("{cecf86f6-cad5-48d5-9b22-989f848acc9d}") )

    def test_util_primitives_Boolean_array_inputtypemap(self):
        v = self.tester.testVariantTypemap_in( [pyuaf.util.primitives.Boolean(True),
                                                pyuaf.util.primitives.Boolean(False),
                                                pyuaf.util.primitives.Boolean(True) ])
        self.assertEqual( v , [pyuaf.util.primitives.Boolean(True),
                               pyuaf.util.primitives.Boolean(False),
                               pyuaf.util.primitives.Boolean(True) ] )

    def test_util_primitives_Byte_array_inputtypemap(self):
        v = self.tester.testVariantTypemap_in( [pyuaf.util.primitives.Byte(1),
                                                pyuaf.util.primitives.Byte(2),
                                                pyuaf.util.primitives.Byte(3) ])
        self.assertEqual( v , [pyuaf.util.primitives.Byte(1),
                               pyuaf.util.primitives.Byte(2),
                               pyuaf.util.primitives.Byte(3) ] )

    def test_util_primitives_SByte_array_inputtypemap(self):
        v = self.tester.testVariantTypemap_in( [pyuaf.util.primitives.SByte(-1),
                                                pyuaf.util.primitives.SByte(2),
                                                pyuaf.util.primitives.SByte(-3) ])
        self.assertEqual( v , [pyuaf.util.primitives.SByte(-1),
                               pyuaf.util.primitives.SByte(2),
                               pyuaf.util.primitives.SByte(-3) ] )

    def test_util_primitives_UInt16_array_inputtypemap(self):
        v = self.tester.testVariantTypemap_in( [pyuaf.util.primitives.UInt16(1),
                                                pyuaf.util.primitives.UInt16(2),
                                                pyuaf.util.primitives.UInt16(3) ])
        self.assertEqual( v , [pyuaf.util.primitives.UInt16(1),
                               pyuaf.util.primitives.UInt16(2),
                               pyuaf.util.primitives.UInt16(3) ] )

    def test_util_primitives_Int16_array_inputtypemap(self):
        v = self.tester.testVariantTypemap_in( [pyuaf.util.primitives.Int16(1),
                                                pyuaf.util.primitives.Int16(-2),
                                                pyuaf.util.primitives.Int16(3) ])
        self.assertEqual( v , [pyuaf.util.primitives.Int16(1),
                               pyuaf.util.primitives.Int16(-2),
                               pyuaf.util.primitives.Int16(3) ] )

    def test_util_primitives_UInt32_array_inputtypemap(self):
        v = self.tester.testVariantTypemap_in( [pyuaf.util.primitives.UInt32(1),
                                                pyuaf.util.primitives.UInt32(2),
                                                pyuaf.util.primitives.UInt32(3) ])
        self.assertEqual( v , [pyuaf.util.primitives.UInt32(1),
                               pyuaf.util.primitives.UInt32(2),
                               pyuaf.util.primitives.UInt32(3) ] )

    def test_util_primitives_Int32_array_inputtypemap(self):
        v = self.tester.testVariantTypemap_in( [pyuaf.util.primitives.Int32(1),
                                                pyuaf.util.primitives.Int32(-2),
                                                pyuaf.util.primitives.Int32(3) ])
        self.assertEqual( v , [pyuaf.util.primitives.Int32(1),
                               pyuaf.util.primitives.Int32(-2),
                               pyuaf.util.primitives.Int32(3) ] )

    def test_util_primitives_UInt64_array_inputtypemap(self):
        v = self.tester.testVariantTypemap_in( [pyuaf.util.primitives.UInt64(1),
                                                pyuaf.util.primitives.UInt64(2),
                                                pyuaf.util.primitives.UInt64(3) ])
        self.assertEqual( v , [pyuaf.util.primitives.UInt64(1),
                               pyuaf.util.primitives.UInt64(2),
                               pyuaf.util.primitives.UInt64(3) ] )

    def test_util_primitives_Int64_array_inputtypemap(self):
        v = self.tester.testVariantTypemap_in( [pyuaf.util.primitives.Int64(1),
                                                pyuaf.util.primitives.Int64(-2),
                                                pyuaf.util.primitives.Int64(3) ])
        self.assertEqual( v , [pyuaf.util.primitives.Int64(1),
                               pyuaf.util.primitives.Int64(-2),
                               pyuaf.util.primitives.Int64(3) ] )

    def test_util_primitives_Float_array_inputtypemap(self):
        v = self.tester.testVariantTypemap_in( [pyuaf.util.primitives.Float(-3.14),
                                                pyuaf.util.primitives.Float(3.14),
                                                pyuaf.util.primitives.Float(-3.14) ])
        self.assertTrue( -3.13999 > v[0].value > -3.14001 )
        self.assertTrue( 3.13999 < v[1].value < 3.14001 )
        self.assertTrue( -3.13999 > v[2].value > -3.14001 )

    def test_util_primitives_Double_array_inputtypemap(self):
        v = self.tester.testVariantTypemap_in( [pyuaf.util.primitives.Double(-3.14),
                                                pyuaf.util.primitives.Double(3.14),
                                                pyuaf.util.primitives.Double(-3.14) ])
        self.assertTrue( -3.13999 > v[0].value > -3.14001 )
        self.assertTrue( 3.13999 < v[1].value < 3.14001 )
        self.assertTrue( -3.13999 > v[2].value > -3.14001 )

    def test_util_primitives_String_array_inputtypemap(self):
        v = self.tester.testVariantTypemap_in([pyuaf.util.primitives.String("test1"),
                                               pyuaf.util.primitives.String("test2"),
                                               pyuaf.util.primitives.String("test3") ])
        self.assertEqual( v , [pyuaf.util.primitives.String("test1"),
                               pyuaf.util.primitives.String("test2"),
                               pyuaf.util.primitives.String("test3") ] )

    def test_unicodeStr_array_inputtypemap(self):
        v = self.tester.testVariantTypemap_in(["test1 \xc2\xb0", "test2 \xc2\xb0", "test3 \xc2\xb0"])
        self.assertEqual( v , [ pyuaf.util.primitives.String("test1 \xc2\xb0"),
                                pyuaf.util.primitives.String("test2 \xc2\xb0"),
                                pyuaf.util.primitives.String("test3 \xc2\xb0") ] )

    def test_util_NodeId_array_inputtypemap(self):
        v = self.tester.testVariantTypemap_in( [pyuaf.util.NodeId("SomeIdentifier", 42),
                                                pyuaf.util.NodeId("SomeIdentifier", 42),
                                                pyuaf.util.NodeId("SomeIdentifier", 42)] )
        self.assertEqual( v , [pyuaf.util.NodeId("SomeIdentifier", 42),
                               pyuaf.util.NodeId("SomeIdentifier", 42),
                               pyuaf.util.NodeId("SomeIdentifier", 42)] )

    def test_util_ExpandedNodeId_array_inputtypemap(self):
        v = self.tester.testVariantTypemap_in( [pyuaf.util.ExpandedNodeId("SomeIdentifier", 42, 21),
                                                pyuaf.util.ExpandedNodeId("SomeIdentifier", 42, 21),
                                                pyuaf.util.ExpandedNodeId("SomeIdentifier", 42, 21)] )
        self.assertEqual( v , [pyuaf.util.ExpandedNodeId("SomeIdentifier", 42, 21),
                               pyuaf.util.ExpandedNodeId("SomeIdentifier", 42, 21),
                               pyuaf.util.ExpandedNodeId("SomeIdentifier", 42, 21)] )

    def test_util_LocalizedText_array_inputtypemap(self):
        v = self.tester.testVariantTypemap_in( [pyuaf.util.LocalizedText("en", "SomeText"),
                                                pyuaf.util.LocalizedText("en", "SomeText"),
                                                pyuaf.util.LocalizedText("en", "SomeText")])
        self.assertEqual( v , [pyuaf.util.LocalizedText("en", "SomeText"),
                               pyuaf.util.LocalizedText("en", "SomeText"),
                               pyuaf.util.LocalizedText("en", "SomeText")] )

    def test_util_QualifiedName_array_inputtypemap(self):
        v = self.tester.testVariantTypemap_in( [pyuaf.util.QualifiedName("SomeName", 42),
                                                pyuaf.util.QualifiedName("SomeName", 43),
                                                pyuaf.util.QualifiedName("SomeName", 44)] )
        self.assertEqual( v , [pyuaf.util.QualifiedName("SomeName", 42),
                               pyuaf.util.QualifiedName("SomeName", 43),
                               pyuaf.util.QualifiedName("SomeName", 44)] )

    def test_util_DateTime_array_inputtypemap(self):
        v = self.tester.testVariantTypemap_in( [pyuaf.util.DateTime.fromString("2013-05-21T12:34:56.789Z"),
                                                pyuaf.util.DateTime.fromString("2013-05-21T12:34:56.789Z"),
                                                pyuaf.util.DateTime.fromString("2013-05-21T12:34:56.789Z")] )
        self.assertEqual( v , [pyuaf.util.DateTime.fromString("2013-05-21T12:34:56.789Z"),
                               pyuaf.util.DateTime.fromString("2013-05-21T12:34:56.789Z"),
                               pyuaf.util.DateTime.fromString("2013-05-21T12:34:56.789Z")] )


    def test_util_ExtensionObject_array_inputtypemap(self):
        v = self.tester.testVariantTypemap_in( [pyuaf.util.ExtensionObject(),
                                                pyuaf.util.ExtensionObject(),
                                                pyuaf.util.ExtensionObject()] )
        self.assertEqual( type(v[0]) , pyuaf.util.ExtensionObject )
        self.assertEqual( type(v[1]) , pyuaf.util.ExtensionObject )
        self.assertEqual( type(v[2]) , pyuaf.util.ExtensionObject )

    def test_util_DateTime_array_inputtypemap(self):
        v = self.tester.testVariantTypemap_in( [pyuaf.util.Guid("{cecf86f6-cad5-48d5-9b22-989f848acc9d}"),
                                                pyuaf.util.Guid("{cecf86f6-cad5-48d5-9b22-989f848acc9e}")] )
        self.assertEqual( v , [pyuaf.util.Guid("{cecf86f6-cad5-48d5-9b22-989f848acc9d}"),
                               pyuaf.util.Guid("{cecf86f6-cad5-48d5-9b22-989f848acc9e}")] )

    def test_util_VariantVector(self):
        testVector(self, pyuaf.util.VariantVector, [ pyuaf.util.primitives.UInt64(123132),
                                                     pyuaf.util.primitives.ByteString(bytearray(b"\x01\x02\x03")),
                                                     pyuaf.util.primitives.Double(1.2345),
                                                     pyuaf.util.primitives.String("s"),
                                                     pyuaf.util.NodeId("id", 3),
                                                     pyuaf.util.NodeId("id", "uri"),
                                                     pyuaf.util.NodeId("id", "uri", 3),
                                                     pyuaf.util.ExpandedNodeId("id", 4, 5),
                                                     pyuaf.util.ExpandedNodeId("id", "uri", 5),
                                                     pyuaf.util.ExpandedNodeId("id", "nsUri", "svrUri"),
                                                     pyuaf.util.DateTime(124567.8),
                                                     pyuaf.util.QualifiedName("name", 34),
                                                     pyuaf.util.QualifiedName("name", "uri"),
                                                     pyuaf.util.QualifiedName("name", "uri", 34),
                                                     pyuaf.util.LocalizedText("en", "text") ])

    def test_util_VariantVector_recursive(self):
        def isEqual(a, b):
            """Compare 2 floats."""
            return abs(a - b) < 0.00001

        vec1 = pyuaf.util.VariantVector()
        vec1.append(pyuaf.util.primitives.Float(2.3))
        vec1.append(pyuaf.util.primitives.UInt32(33))

        vec2 = pyuaf.util.VariantVector()
        vec2.append(vec1)
        vec2.append(pyuaf.util.primitives.UInt32(44))

        vec3 = pyuaf.util.VariantVector()
        vec3.append(vec2)
        vec3.append(pyuaf.util.primitives.UInt32(55))

        assert isEqual(vec3[0][0][0].value, 2.3)
        assert isEqual(vec3[0][0][1].value, 33)
        assert isEqual(vec3[0][1].value, 44)
        assert isEqual(vec3[1].value, 55)


if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())
