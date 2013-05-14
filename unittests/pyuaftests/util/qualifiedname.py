import pyuaf

    
def test(args):
    
    print "util.qualifiedname"
    
    print(" - testing pyuaf.util.QualifiedName()")
    q0  = pyuaf.util.QualifiedName()
    q0_ = pyuaf.util.QualifiedName()
    q1  = pyuaf.util.QualifiedName("SomeName", 42)
    q1_ = pyuaf.util.QualifiedName("SomeName", 42)
    q2  = pyuaf.util.QualifiedName("SomeName", "SomeUri")
    q2_ = pyuaf.util.QualifiedName("SomeName", "SomeUri")
    q3  = pyuaf.util.QualifiedName("SomeName", "SomeUri", 42)
    q3_ = pyuaf.util.QualifiedName("SomeName", "SomeUri", 42)
    
    print(" - testing pyuaf.util.QualifiedName().hasNameSpaceIndex()")
    assert q0.hasNameSpaceIndex() == False
    assert q1.hasNameSpaceIndex() == True
    assert q2.hasNameSpaceIndex() == False
    assert q3.hasNameSpaceIndex() == True
    
    print(" - testing pyuaf.util.QualifiedName().hasNameSpaceUri()")
    assert q0.hasNameSpaceUri() == False
    assert q1.hasNameSpaceUri() == False
    assert q2.hasNameSpaceUri() == True
    assert q3.hasNameSpaceUri() == True
    
    print(" - testing pyuaf.util.QualifiedName().nameSpaceUri()")
    assert q2.nameSpaceUri() == "SomeUri"
    assert q3.nameSpaceUri() == "SomeUri"
    
    print(" - testing pyuaf.util.QualifiedName().nameSpaceIndex()")
    assert q1.nameSpaceIndex() == 42
    assert q3.nameSpaceIndex() == 42
    
    print(" - testing pyuaf.util.QualifiedName().setNameSpaceIndex()")
    q0like = pyuaf.util.QualifiedName()
    q1like = pyuaf.util.QualifiedName("SomeName", 42)
    q2like = pyuaf.util.QualifiedName("SomeName", "SomeUri")
    q3like = pyuaf.util.QualifiedName("SomeName", "SomeUri", 42)
    q0like.setNameSpaceIndex(43)
    q1like.setNameSpaceIndex(43)
    q2like.setNameSpaceIndex(43)
    q3like.setNameSpaceIndex(43)
    assert q0like.hasNameSpaceIndex() and q0like.nameSpaceIndex() == 43
    assert q1like.hasNameSpaceIndex() and q1like.nameSpaceIndex() == 43
    assert q2like.hasNameSpaceIndex() and q2like.nameSpaceIndex() == 43
    assert q3like.hasNameSpaceIndex() and q3like.nameSpaceIndex() == 43
    
    print(" - testing pyuaf.util.QualifiedName().__eq__()")
    assert q0 == q0_
    assert q1 == q1_
    assert q2 == q2_
    assert q3 == q3_
    
    print(" - testing pyuaf.util.QualifiedName().__ne__()")
    assert (q0 != q0_) == False
    assert q0 != q1
    assert q1 != q2
    assert q2 != q3
    assert q3 != q0
    
    print(" - testing pyuaf.util.QualifiedName().__lt__()")
    assert q0 < q1
    assert q2 < q1
    assert q2 < q3
    assert q0 < q3
    
    print(" - testing pyuaf.util.QualifiedName().__gt__()")
    assert q1 > q0
    assert q1 > q2
    assert q3 > q2
    assert q3 > q0
    
