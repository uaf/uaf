import pyuaf


def test(args):
        
    
    print "util.variant"
    
    tester = pyuaf.util.__unittesthelper__.UnitTestHelper()
    
    ######## output typemaps ########
    
    
    print(" - testing output typemap for pyuaf.util.primitives.Boolean")
    v = tester.testVariantTypemap_out(pyuaf.util.opcuatypes.Boolean)
    assert v.type() == pyuaf.util.opcuatypes.Boolean
    assert v.value == True
    assert type(v) == type(pyuaf.util.primitives.Boolean())
    
    print(" - testing output typemap for pyuaf.util.primitives.Byte")
    v = tester.testVariantTypemap_out(pyuaf.util.opcuatypes.Byte)
    assert v.type() == pyuaf.util.opcuatypes.Byte
    assert v.value == 3
    assert type(v) == type(pyuaf.util.primitives.Byte())
    
    print(" - testing output typemap for pyuaf.util.primitives.SByte")
    v = tester.testVariantTypemap_out(pyuaf.util.opcuatypes.SByte)
    assert v.type() == pyuaf.util.opcuatypes.SByte
    assert v.value == -3
    assert type(v) == type(pyuaf.util.primitives.SByte())
    
    print(" - testing output typemap for pyuaf.util.primitives.UInt16")
    v = tester.testVariantTypemap_out(pyuaf.util.opcuatypes.UInt16)
    assert v.type() == pyuaf.util.opcuatypes.UInt16
    assert v.value == 3
    assert type(v) == type(pyuaf.util.primitives.UInt16())
    
    print(" - testing output typemap for pyuaf.util.primitives.Int16")
    v = tester.testVariantTypemap_out(pyuaf.util.opcuatypes.Int16)
    assert v.type() == pyuaf.util.opcuatypes.Int16
    assert v.value == -3
    assert type(v) == type(pyuaf.util.primitives.Int16())
    
    print(" - testing output typemap for pyuaf.util.primitives.UInt32")
    v = tester.testVariantTypemap_out(pyuaf.util.opcuatypes.UInt32)
    assert v.type() == pyuaf.util.opcuatypes.UInt32
    assert v.value == 3
    assert type(v) == type(pyuaf.util.primitives.UInt32())
    
    print(" - testing output typemap for pyuaf.util.primitives.Int32")
    v = tester.testVariantTypemap_out(pyuaf.util.opcuatypes.Int32)
    assert v.type() == pyuaf.util.opcuatypes.Int32
    assert v.value == -3
    assert type(v) == type(pyuaf.util.primitives.Int32())
    
    print(" - testing output typemap for pyuaf.util.primitives.UInt64")
    v = tester.testVariantTypemap_out(pyuaf.util.opcuatypes.UInt64)
    assert v.type() == pyuaf.util.opcuatypes.UInt64
    assert v.value == 3
    assert type(v) == type(pyuaf.util.primitives.UInt64())
    
    print(" - testing output typemap for pyuaf.util.primitives.Int64")
    v = tester.testVariantTypemap_out(pyuaf.util.opcuatypes.Int64)
    assert v.type() == pyuaf.util.opcuatypes.Int64
    assert v.value == -3
    assert type(v) == type(pyuaf.util.primitives.Int64())
    
    print(" - testing output typemap for pyuaf.util.primitives.Float")
    v = tester.testVariantTypemap_out(pyuaf.util.opcuatypes.Float)
    assert v.type() == pyuaf.util.opcuatypes.Float
    assert 3.1399999 < v.value < 3.140001
    assert type(v) == type(pyuaf.util.primitives.Float())
    
    print(" - testing output typemap for pyuaf.util.primitives.Double")
    v = tester.testVariantTypemap_out(pyuaf.util.opcuatypes.Double)
    assert v.type() == pyuaf.util.opcuatypes.Double
    assert 3.1399999 < v.value < 3.140001
    assert type(v) == type(pyuaf.util.primitives.Double())
    
    print(" - testing output typemap for unicode string")
    v = tester.testVariantTypemap_out(pyuaf.util.opcuatypes.String)
    assert v == (u"test \u00B0").encode("UTF-8")
    assert type(v) == str
    
    print(" - testing output typemap for bytearray")
    v = tester.testVariantTypemap_out(pyuaf.util.opcuatypes.ByteString)
    assert type(v) == type(bytearray())
    assert len(v) == 3
    assert v[0] == 1
    assert v[1] == 2
    assert v[2] == 3
    
    print(" - testing output typemap for pyuaf.util.NodeId")
    v = tester.testVariantTypemap_out(pyuaf.util.opcuatypes.NodeId)
    assert v == pyuaf.util.NodeId("SomeIdentifier", 42)
    
    print(" - testing output typemap for pyuaf.util.ExpandedNodeId")
    v = tester.testVariantTypemap_out(pyuaf.util.opcuatypes.ExpandedNodeId)
    assert v == pyuaf.util.ExpandedNodeId("SomeIdentifier", 42, 21)
    
    print(" - testing output typemap for pyuaf.util.LocalizedText")
    v = tester.testVariantTypemap_out(pyuaf.util.opcuatypes.LocalizedText)
    assert v == pyuaf.util.LocalizedText("en", "SomeText")
    
    print(" - testing output typemap for pyuaf.util.QualifiedName")
    v = tester.testVariantTypemap_out(pyuaf.util.opcuatypes.QualifiedName)
    assert v == pyuaf.util.QualifiedName("SomeName", 42)
    
    print(" - testing output typemap for pyuaf.util.primitives.Boolean array")
    v = tester.testVariantTypemap_out(pyuaf.util.opcuatypes.Boolean, True)
    assert v == [ pyuaf.util.primitives.Boolean(True), 
                  pyuaf.util.primitives.Boolean(False), 
                  pyuaf.util.primitives.Boolean(True) ]
    
    print(" - testing output typemap for pyuaf.util.primitives.Byte array")
    v = tester.testVariantTypemap_out(pyuaf.util.opcuatypes.Byte, True)
    assert v == [ pyuaf.util.primitives.Byte(1), 
                  pyuaf.util.primitives.Byte(2), 
                  pyuaf.util.primitives.Byte(3) ]
    
    print(" - testing output typemap for pyuaf.util.primitives.Byte array")
    v = tester.testVariantTypemap_out(pyuaf.util.opcuatypes.SByte, True)
    assert v == [ pyuaf.util.primitives.SByte(-1), 
                  pyuaf.util.primitives.SByte(2), 
                  pyuaf.util.primitives.SByte(-3) ]
    
    print(" - testing output typemap for pyuaf.util.primitives.UInt16 array")
    v = tester.testVariantTypemap_out(pyuaf.util.opcuatypes.UInt16, True)
    assert v == [ pyuaf.util.primitives.UInt16(1), 
                  pyuaf.util.primitives.UInt16(2), 
                  pyuaf.util.primitives.UInt16(3) ]
    
    print(" - testing output typemap for pyuaf.util.primitives.Int16 array")
    v = tester.testVariantTypemap_out(pyuaf.util.opcuatypes.Int16, True)
    assert v == [ pyuaf.util.primitives.Int16(-1), 
                  pyuaf.util.primitives.Int16(2), 
                  pyuaf.util.primitives.Int16(-3) ]
    
    print(" - testing output typemap for pyuaf.util.primitives.UInt32 array")
    v = tester.testVariantTypemap_out(pyuaf.util.opcuatypes.UInt32, True)
    assert v == [ pyuaf.util.primitives.UInt32(1), 
                  pyuaf.util.primitives.UInt32(2), 
                  pyuaf.util.primitives.UInt32(3) ]
    
    print(" - testing output typemap for pyuaf.util.primitives.Int32 array")
    v = tester.testVariantTypemap_out(pyuaf.util.opcuatypes.Int32, True)
    assert v == [ pyuaf.util.primitives.Int32(-1), 
                  pyuaf.util.primitives.Int32(2), 
                  pyuaf.util.primitives.Int32(-3) ]
    
    print(" - testing output typemap for pyuaf.util.primitives.UInt64 array")
    v = tester.testVariantTypemap_out(pyuaf.util.opcuatypes.UInt64, True)
    assert v == [ pyuaf.util.primitives.UInt64(1), 
                  pyuaf.util.primitives.UInt64(2), 
                  pyuaf.util.primitives.UInt64(3) ]
    
    print(" - testing output typemap for pyuaf.util.primitives.Int64 array")
    v = tester.testVariantTypemap_out(pyuaf.util.opcuatypes.Int64, True)
    assert v == [ pyuaf.util.primitives.Int64(-1), 
                  pyuaf.util.primitives.Int64(2), 
                  pyuaf.util.primitives.Int64(-3) ]
    
    print(" - testing output typemap for pyuaf.util.primitives.Float array")
    v = tester.testVariantTypemap_out(pyuaf.util.opcuatypes.Float, True)
    assert -3.13999 > v[0].value > -3.14001
    assert 3.13999 < v[1].value < 3.14001
    assert -3.13999 > v[2].value > -3.14001
    
    print(" - testing output typemap for pyuaf.util.primitives.Double array")
    v = tester.testVariantTypemap_out(pyuaf.util.opcuatypes.Double, True)
    assert -3.13999 > v[0].value > -3.14001
    assert 3.13999 < v[1].value < 3.14001
    assert -3.13999 > v[2].value > -3.14001
    
    print(" - testing output typemap for pyuaf.util.primitives.String array")
    v = tester.testVariantTypemap_out(pyuaf.util.opcuatypes.String, True)
    assert v == ["test1", "test2", "test3"]
    
    print(" - testing output typemap for pyuaf.util.NodeId array")
    v = tester.testVariantTypemap_out(pyuaf.util.opcuatypes.NodeId, True)
    assert v == [pyuaf.util.NodeId("SomeIdentifier", 42), 
                 pyuaf.util.NodeId("SomeIdentifier", 42),
                 pyuaf.util.NodeId("SomeIdentifier", 42)]
    
    print(" - testing output typemap for pyuaf.util.ExpandedNodeId array")
    try:
        v = tester.testVariantTypemap_out(pyuaf.util.opcuatypes.ExpandedNodeId, True)
        assert v == [pyuaf.util.ExpandedNodeId("SomeIdentifier", 42, 21), 
                     pyuaf.util.ExpandedNodeId("SomeIdentifier", 42, 21),
                     pyuaf.util.ExpandedNodeId("SomeIdentifier", 42, 21)]
    except TypeError:
        print("*** warning: bug in SDK <= v1.3.2 present (in uavariant.cpp, see forum Unified Automation) ***")
    
    
    print(" - testing output typemap for pyuaf.util.LocalizedText array")
    v = tester.testVariantTypemap_out(pyuaf.util.opcuatypes.LocalizedText, True)
    assert v == [pyuaf.util.LocalizedText("en", "SomeText"), 
                 pyuaf.util.LocalizedText("en", "SomeText"),
                 pyuaf.util.LocalizedText("en", "SomeText")]
    
    
    print(" - testing output typemap for pyuaf.util.QualifiedName array")
    v = tester.testVariantTypemap_out(pyuaf.util.opcuatypes.QualifiedName, True)
    assert v == [pyuaf.util.QualifiedName("SomeName", 42), 
                 pyuaf.util.QualifiedName("SomeName", 42),
                 pyuaf.util.QualifiedName("SomeName", 42)]
    
    
    
    ######## input typemaps ########
    
    
    print(" - testing input typemap for pyuaf.util.primitives.Boolean")
    v = tester.testVariantTypemap_in(pyuaf.util.primitives.Boolean(True))
    assert v == pyuaf.util.primitives.Boolean(True)
    
    print(" - testing input typemap for pyuaf.util.primitives.Byte")
    v = tester.testVariantTypemap_in(pyuaf.util.primitives.Byte(3))
    assert v == pyuaf.util.primitives.Byte(3)
    
    print(" - testing input typemap for pyuaf.util.primitives.SByte")
    v = tester.testVariantTypemap_in(pyuaf.util.primitives.SByte(-3))
    assert v == pyuaf.util.primitives.SByte(-3)
    
    print(" - testing input typemap for pyuaf.util.primitives.UInt16")
    v = tester.testVariantTypemap_in(pyuaf.util.primitives.UInt16(3))
    assert v == pyuaf.util.primitives.UInt16(3)
    
    print(" - testing input typemap for pyuaf.util.primitives.Int16")
    v = tester.testVariantTypemap_in(pyuaf.util.primitives.Int16(-3))
    assert v == pyuaf.util.primitives.Int16(-3)
    
    print(" - testing input typemap for pyuaf.util.primitives.UInt32")
    v = tester.testVariantTypemap_in(pyuaf.util.primitives.UInt32(3))
    assert v == pyuaf.util.primitives.UInt32(3)
    
    print(" - testing input typemap for pyuaf.util.primitives.Int32")
    v = tester.testVariantTypemap_in(pyuaf.util.primitives.Int32(-3))
    assert v == pyuaf.util.primitives.Int32(-3)
    
    print(" - testing input typemap for pyuaf.util.primitives.UInt64")
    v = tester.testVariantTypemap_in(pyuaf.util.primitives.UInt64(3))
    assert v == pyuaf.util.primitives.UInt64(3)
    
    print(" - testing input typemap for pyuaf.util.primitives.Int64")
    v = tester.testVariantTypemap_in(pyuaf.util.primitives.Int64(-3))
    assert v == pyuaf.util.primitives.Int64(-3)
    
    print(" - testing input typemap for pyuaf.util.primitives.Float")
    v = tester.testVariantTypemap_in(pyuaf.util.primitives.Float(3.14))
    assert v == pyuaf.util.primitives.Float(3.14)
    
    print(" - testing input typemap for pyuaf.util.primitives.Double")
    v = tester.testVariantTypemap_in(pyuaf.util.primitives.Double(3.14))
    assert v == pyuaf.util.primitives.Double(3.14)
    
    print(" - testing input typemap for non-unicode string")
    v = tester.testVariantTypemap_in("test")
    assert v == "test"
    
    print(" - testing input typemap for unicode string")
    v = tester.testVariantTypemap_in(u"test \u00B0")
    assert v == (u"test \u00B0").encode("UTF-8")
    
    print(" - testing input typemap for bytearray")
    v = tester.testVariantTypemap_in(bytearray(b"abc"))
    assert v == bytearray(b"abc")
    
    print(" - testing input typemap for pyuaf.util.NodeId")
    v = tester.testVariantTypemap_in(pyuaf.util.NodeId("SomeIdentifier", 42))
    assert v == pyuaf.util.NodeId("SomeIdentifier", 42)
    
    print(" - testing input typemap for pyuaf.util.ExpandedNodeId")
    v = tester.testVariantTypemap_in(pyuaf.util.ExpandedNodeId("SomeIdentifier", 42, 21))
    assert v == pyuaf.util.ExpandedNodeId("SomeIdentifier", 42, 21)
    
    print(" - testing input typemap for pyuaf.util.LocalizedText")
    v = tester.testVariantTypemap_in(pyuaf.util.LocalizedText("en", "SomeText"))
    assert v == pyuaf.util.LocalizedText("en", "SomeText")
    
    print(" - testing input typemap for pyuaf.util.QualifiedName")
    v = tester.testVariantTypemap_in(pyuaf.util.QualifiedName("SomeName", 42))
    assert v == pyuaf.util.QualifiedName("SomeName", 42)

    print(" - testing input typemap for pyuaf.util.primitives.Boolean array")
    v = tester.testVariantTypemap_in( [pyuaf.util.primitives.Boolean(True),
                                       pyuaf.util.primitives.Boolean(False),
                                       pyuaf.util.primitives.Boolean(True) ])
    assert v == [pyuaf.util.primitives.Boolean(True),
                 pyuaf.util.primitives.Boolean(False),
                 pyuaf.util.primitives.Boolean(True) ]

    print(" - testing input typemap for pyuaf.util.primitives.Byte array")
    v = tester.testVariantTypemap_in( [pyuaf.util.primitives.Byte(1),
                                       pyuaf.util.primitives.Byte(2),
                                       pyuaf.util.primitives.Byte(3) ])
    assert v == [pyuaf.util.primitives.Byte(1),
                 pyuaf.util.primitives.Byte(2),
                 pyuaf.util.primitives.Byte(3) ]

    print(" - testing input typemap for pyuaf.util.primitives.SByte array")
    v = tester.testVariantTypemap_in( [pyuaf.util.primitives.SByte(-1),
                                       pyuaf.util.primitives.SByte(2),
                                       pyuaf.util.primitives.SByte(-3) ])
    assert v == [pyuaf.util.primitives.SByte(-1),
                 pyuaf.util.primitives.SByte(2),
                 pyuaf.util.primitives.SByte(-3) ]

    print(" - testing input typemap for pyuaf.util.primitives.UInt16 array")
    v = tester.testVariantTypemap_in( [pyuaf.util.primitives.UInt16(1),
                                       pyuaf.util.primitives.UInt16(2),
                                       pyuaf.util.primitives.UInt16(3) ])
    assert v == [pyuaf.util.primitives.UInt16(1),
                 pyuaf.util.primitives.UInt16(2),
                 pyuaf.util.primitives.UInt16(3) ]

    print(" - testing input typemap for pyuaf.util.primitives.Int16 array")
    v = tester.testVariantTypemap_in( [pyuaf.util.primitives.Int16(1),
                                       pyuaf.util.primitives.Int16(-2),
                                       pyuaf.util.primitives.Int16(3) ])
    assert v == [pyuaf.util.primitives.Int16(1),
                 pyuaf.util.primitives.Int16(-2),
                 pyuaf.util.primitives.Int16(3) ]

    print(" - testing input typemap for pyuaf.util.primitives.UInt32 array")
    v = tester.testVariantTypemap_in( [pyuaf.util.primitives.UInt32(1),
                                       pyuaf.util.primitives.UInt32(2),
                                       pyuaf.util.primitives.UInt32(3) ])
    assert v == [pyuaf.util.primitives.UInt32(1),
                 pyuaf.util.primitives.UInt32(2),
                 pyuaf.util.primitives.UInt32(3) ]

    print(" - testing input typemap for pyuaf.util.primitives.Int32 array")
    v = tester.testVariantTypemap_in( [pyuaf.util.primitives.Int32(1),
                                       pyuaf.util.primitives.Int32(-2),
                                       pyuaf.util.primitives.Int32(3) ])
    assert v == [pyuaf.util.primitives.Int32(1),
                 pyuaf.util.primitives.Int32(-2),
                 pyuaf.util.primitives.Int32(3) ]

    print(" - testing input typemap for pyuaf.util.primitives.UInt64 array")
    v = tester.testVariantTypemap_in( [pyuaf.util.primitives.UInt64(1),
                                       pyuaf.util.primitives.UInt64(2),
                                       pyuaf.util.primitives.UInt64(3) ])
    assert v == [pyuaf.util.primitives.UInt64(1),
                 pyuaf.util.primitives.UInt64(2),
                 pyuaf.util.primitives.UInt64(3) ]

    print(" - testing input typemap for pyuaf.util.primitives.Int64 array")
    v = tester.testVariantTypemap_in( [pyuaf.util.primitives.Int64(1),
                                       pyuaf.util.primitives.Int64(-2),
                                       pyuaf.util.primitives.Int64(3) ])
    assert v == [pyuaf.util.primitives.Int64(1),
                 pyuaf.util.primitives.Int64(-2),
                 pyuaf.util.primitives.Int64(3) ]

    print(" - testing input typemap for pyuaf.util.primitives.Float array")
    v = tester.testVariantTypemap_in( [pyuaf.util.primitives.Float(-3.14),
                                       pyuaf.util.primitives.Float(3.14),
                                       pyuaf.util.primitives.Float(-3.14) ])
    assert -3.13999 > v[0].value > -3.14001
    assert 3.13999 < v[1].value < 3.14001
    assert -3.13999 > v[2].value > -3.14001

    print(" - testing input typemap for pyuaf.util.primitives.Double array")
    v = tester.testVariantTypemap_in( [pyuaf.util.primitives.Double(-3.14),
                                       pyuaf.util.primitives.Double(3.14),
                                       pyuaf.util.primitives.Double(-3.14) ])
    assert -3.13999 > v[0].value > -3.14001
    assert 3.13999 < v[1].value < 3.14001
    assert -3.13999 > v[2].value > -3.14001

    print(" - testing input typemap for string array")
    v = tester.testVariantTypemap_in(["test1", "test2", "test3"])
    assert v == ["test1", "test2", "test3"]

    print(" - testing input typemap for unicode objects array")
    v = tester.testVariantTypemap_in([u"test1 \u00B0", u"test2 \u00B0", u"test3 \u00B0"])
    assert v == [ (u"test1 \u00B0").encode("UTF-8"), 
                  (u"test2 \u00B0").encode("UTF-8"), 
                  (u"test3 \u00B0").encode("UTF-8") ]
    
    print(" - testing input typemap for pyuaf.util.NodeId array")
    v = tester.testVariantTypemap_in( [pyuaf.util.NodeId("SomeIdentifier", 42), 
                                       pyuaf.util.NodeId("SomeIdentifier", 42),
                                       pyuaf.util.NodeId("SomeIdentifier", 42)] )
    assert v == [pyuaf.util.NodeId("SomeIdentifier", 42), 
                 pyuaf.util.NodeId("SomeIdentifier", 42),
                 pyuaf.util.NodeId("SomeIdentifier", 42)]
    
    print(" - testing input typemap for pyuaf.util.ExpandedNodeId array")
    
    try:
        v = tester.testVariantTypemap_in( [pyuaf.util.ExpandedNodeId("SomeIdentifier", 42, 21), 
                                           pyuaf.util.ExpandedNodeId("SomeIdentifier", 42, 21),
                                           pyuaf.util.ExpandedNodeId("SomeIdentifier", 42, 21)] )
        assert v == [pyuaf.util.ExpandedNodeId("SomeIdentifier", 42, 21), 
                     pyuaf.util.ExpandedNodeId("SomeIdentifier", 42, 21),
                     pyuaf.util.ExpandedNodeId("SomeIdentifier", 42, 21)]
    except TypeError:
        print("*** warning: bug in SDK <= v1.3.2 present (in uavariant.cpp, see forum Unified Automation) ***")
    
    
    print(" - testing input typemap for pyuaf.util.LocalizedText array")
    v = tester.testVariantTypemap_in( [pyuaf.util.LocalizedText("en", "SomeText"), 
                                       pyuaf.util.LocalizedText("en", "SomeText"),
                                       pyuaf.util.LocalizedText("en", "SomeText")])
    assert v == [pyuaf.util.LocalizedText("en", "SomeText"), 
                 pyuaf.util.LocalizedText("en", "SomeText"),
                 pyuaf.util.LocalizedText("en", "SomeText")]
    
    print(" - testing input typemap for pyuaf.util.QualifiedName array")
    v = tester.testVariantTypemap_in( [pyuaf.util.QualifiedName("SomeName", 42), 
                                       pyuaf.util.QualifiedName("SomeName", 43),
                                       pyuaf.util.QualifiedName("SomeName", 44)] )

