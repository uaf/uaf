import pyuaf


def test(args):
        
    print("util.relativepathelement")
    
    
    print(" - testing pyuaf.util.RelativePathElement()")
    r0  = pyuaf.util.RelativePathElement()
    r0_ = pyuaf.util.RelativePathElement()
    r1  = pyuaf.util.RelativePathElement(pyuaf.util.QualifiedName("SomeName", 42))
    r1_ = pyuaf.util.RelativePathElement(pyuaf.util.QualifiedName("SomeName", 42))
    r2  = pyuaf.util.RelativePathElement(pyuaf.util.QualifiedName("SomeName", 42),
                                         pyuaf.util.NodeId("SomeIdentifier", 21),
                                         True,
                                         False)
    r2_ = pyuaf.util.RelativePathElement(pyuaf.util.QualifiedName("SomeName", 42),
                                         pyuaf.util.NodeId("SomeIdentifier", 21),
                                         True,
                                         False)
    
    print(" - testing pyuaf.util.RelativePathElement().targetName()")
    assert r0.targetName == pyuaf.util.QualifiedName()
    assert r1.targetName == pyuaf.util.QualifiedName("SomeName", 42)
    assert r2.targetName == pyuaf.util.QualifiedName("SomeName", 42)
    
    print(" - testing pyuaf.util.RelativePathElement().referenceType()")
    assert r0.referenceType == pyuaf.util.NodeId(pyuaf.util.opcuaidentifiers.OpcUaId_HierarchicalReferences, 0)
    assert r1.referenceType == pyuaf.util.NodeId(pyuaf.util.opcuaidentifiers.OpcUaId_HierarchicalReferences, 0)
    assert r2.referenceType == pyuaf.util.NodeId("SomeIdentifier", 21)
    
    print(" - testing pyuaf.util.RelativePathElement().isInverse()")
    assert r0.isInverse == False
    assert r1.isInverse == False
    assert r2.isInverse == True
    
    print(" - testing pyuaf.util.RelativePathElement().includeSubtypes()")
    assert r0.includeSubtypes == True
    assert r1.includeSubtypes == True
    assert r2.includeSubtypes == False
    
    print(" - testing pyuaf.util.RelativePathElement().__eq__()")
    assert r0 == r0_
    assert r1 == r1_
    assert r2 == r2_
    assert not (r0 == r1)
    
    print(" - testing pyuaf.util.RelativePathElement().__ne__()")
    assert r0 != r1
    assert r1 != r2
    assert r2 != r0
    assert not (r0 != r0)
    
    print(" - testing pyuaf.util.RelativePathElement().__lt__()")
    assert r0 < r1
    assert r1 < r2
    assert r0 < r2
    
    print(" - testing pyuaf.util.RelativePathElement().__gt__()")
    assert r1 > r0
    assert r2 > r1
    assert r2 > r0
    
