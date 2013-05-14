import pyuaf


def test(args):
        
    print("util.nodeid")
    
    print(" - testing pyuaf.util.NodeId()")
    n0  = pyuaf.util.NodeId()
    n0_ = pyuaf.util.NodeId()
    n1  = pyuaf.util.NodeId("SomeStringIdentifier", "SomeNameSpaceUri")
    n1_ = pyuaf.util.NodeId("SomeStringIdentifier", "SomeNameSpaceUri")
    n1a = pyuaf.util.NodeId("SomeOtherStringIdentifier", "SomeNameSpaceUri")
    n1b = pyuaf.util.NodeId("SomeStringIdentifier", "SomeOtherNameSpaceUri")
    n1c = pyuaf.util.NodeId("SomeOtherStringIdentifier", "SomeOtherNameSpaceUri")
    n2  = pyuaf.util.NodeId("SomeStringIdentifier", "SomeNameSpaceUri", 42)
    n2_ = pyuaf.util.NodeId("SomeStringIdentifier", "SomeNameSpaceUri", 42)
    n3  = pyuaf.util.NodeId("SomeStringIdentifier", 42)
    n3_ = pyuaf.util.NodeId("SomeStringIdentifier", 42)
    n4  = pyuaf.util.NodeId(21, "SomeNameSpaceUri")
    n4_ = pyuaf.util.NodeId(21, "SomeNameSpaceUri")
    n5  = pyuaf.util.NodeId(21, "SomeNameSpaceUri", 42)
    n5_ = pyuaf.util.NodeId(21, "SomeNameSpaceUri", 42)
    n6  = pyuaf.util.NodeId(21, 42)
    n6_ = pyuaf.util.NodeId(21, 42)
    
    print(" - testing pyuaf.util.NodeId().hasNameSpaceIndex()")
    assert n0.hasNameSpaceIndex() == False
    assert n1.hasNameSpaceIndex() == False
    assert n2.hasNameSpaceIndex() == True
    assert n3.hasNameSpaceIndex() == True
    assert n4.hasNameSpaceIndex() == False
    assert n5.hasNameSpaceIndex() == True
    assert n6.hasNameSpaceIndex() == True
    
    print(" - testing pyuaf.util.NodeId().hasNameSpaceUri()")
    assert n0.hasNameSpaceUri() == False
    assert n1.hasNameSpaceUri() == True
    assert n2.hasNameSpaceUri() == True
    assert n3.hasNameSpaceUri() == False
    assert n4.hasNameSpaceUri() == True
    assert n5.hasNameSpaceUri() == True
    assert n6.hasNameSpaceUri() == False
    
    print(" - testing pyuaf.util.NodeId().nameSpaceIndex()")
    assert n2.nameSpaceIndex() == 42
    
    print(" - testing pyuaf.util.NodeId().nameSpaceUri()")
    assert n1.nameSpaceUri() == "SomeNameSpaceUri"
    
    print(" - testing pyuaf.util.NodeId().setNameSpaceIndex()")
    n = pyuaf.util.NodeId(n2)
    n.setNameSpaceIndex(43)
    assert n.nameSpaceIndex() == 43
    
    print(" - testing pyuaf.util.NodeId().setNameSpaceUri()")
    n = pyuaf.util.NodeId(n2)
    n.setNameSpaceUri("SomeOtherNameSpaceUri")
    assert n.nameSpaceUri() == "SomeOtherNameSpaceUri"
    
    print(" - testing pyuaf.util.NodeId().identifier()")
    assert n1.identifier() == pyuaf.util.NodeIdIdentifier("SomeStringIdentifier")
    assert n4.identifier() == pyuaf.util.NodeIdIdentifier(21)
    
    print(" - testing pyuaf.util.NodeId().__eq__()")
    assert n0 == n0_ 
    assert n1 == n1_ 
    assert n2 == n2_ 
    assert n3 == n3_ 
    assert n4 == n4_ 
    assert n5 == n5_ 
    assert n6 == n6_
    
    print(" - testing pyuaf.util.NodeId().__ne__()")
    assert n0 != n1 
    assert n1 != n1a 
    assert n1 != n1b 
    assert n1 != n1c 
    assert n1 != n2  
    assert n2 != n3 
    assert n3 != n4 
    assert n5 != n6
    
    print(" - testing pyuaf.util.NodeId().__lt__()")
    assert n4 < n3
    assert n6 < n5
    
    print(" - testing pyuaf.util.NodeId().__gt__()")
    assert n1 > n0
    assert n2 > n0
