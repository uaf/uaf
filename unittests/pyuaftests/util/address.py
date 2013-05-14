import pyuaf


def test(args):
        
    print "util.address"
    
    
    nodeId = pyuaf.util.ExpandedNodeId("SomeStringIdentifier", "SomeNameSpaceUri", "SomeServerUri")
    
    e1  = pyuaf.util.RelativePathElement(pyuaf.util.QualifiedName("SomeName", 42))
    e2  = pyuaf.util.RelativePathElement(pyuaf.util.QualifiedName("SomeOtherName", 42))
    relativePath    = [e1, e2]
    startingAddress = pyuaf.util.Address(nodeId)
    
    print(" - testing pyuaf.util.Address()")
    a0  = pyuaf.util.Address()
    a0_ = pyuaf.util.Address()
    a1  = pyuaf.util.Address(nodeId)
    a1_ = pyuaf.util.Address(nodeId)
    a2  = pyuaf.util.Address(startingAddress, relativePath)
    a2_ = pyuaf.util.Address(startingAddress, relativePath)
    a3  = pyuaf.util.Address(a2, relativePath)
    a3_ = pyuaf.util.Address(a2, relativePath)
    
    print(" - testing pyuaf.util.Address().isExpandedNodeId()")
    assert a0.isExpandedNodeId() == True
    assert a1.isExpandedNodeId() == True
    assert a2.isExpandedNodeId() == False
    assert a3.isExpandedNodeId() == False
    
    print(" - testing pyuaf.util.Address().isRelativePath()")
    assert a0.isRelativePath() == False
    assert a1.isRelativePath() == False
    assert a2.isRelativePath() == True
    assert a3.isRelativePath() == True
    
    print(" - testing pyuaf.util.Address().getRelativePath()")
    assert a2.getRelativePath() == (e1, e2)
    assert a3.getRelativePath() == (e1, e2)
    
    print(" - testing pyuaf.util.Address().getStartingAddress()")
    assert a2.getStartingAddress() == startingAddress
    assert a3.getStartingAddress() == a2
    
    print(" - testing pyuaf.util.Address().__eq__()")
    assert a0 == a0_ 
    assert a1 == a1_ 
    assert a2 == a2_ 
    assert a3 == a3_
    
    print(" - testing pyuaf.util.Address().__ne__()")
    assert a0 != a1 
    assert a1 != a2 
    assert a2 != a3 
    assert a3 != a1
    
    print(" - testing pyuaf.util.Address().__lt__()")
    assert a0 < a1
    assert a2 < a1
    assert a3 < a2
    assert a3 < a0
    
    print(" - testing pyuaf.util.Address().__gt__()")
    assert a1 > a0
    assert a1 > a2
    assert a2 > a3
    assert a0 > a3
