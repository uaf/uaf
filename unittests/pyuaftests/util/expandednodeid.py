import pyuaf


def test(args):
    
    print("util.expandednodeid")
    
    print(" - testing pyuaf.util.ExpandedNodeId()")
    
    n0  = pyuaf.util.ExpandedNodeId()
    n1  = pyuaf.util.ExpandedNodeId("SomeStringIdentifier", "SomeNameSpaceUri", "SomeServerUri")
    n2  = pyuaf.util.ExpandedNodeId("SomeStringIdentifier", 42, "SomeServerUri")
    n3  = pyuaf.util.ExpandedNodeId(21, "SomeNameSpaceUri", "SomeServerUri")
    n4  = pyuaf.util.ExpandedNodeId(21, 42, "SomeServerUri")
    n5  = pyuaf.util.ExpandedNodeId("SomeStringIdentifier", "SomeNameSpaceUri", 84)
    n6  = pyuaf.util.ExpandedNodeId("SomeStringIdentifier", 42, 84)
    n7  = pyuaf.util.ExpandedNodeId(21, "SomeNameSpaceUri", 84)
    n8  = pyuaf.util.ExpandedNodeId(21, 42, 84)
    n9  = pyuaf.util.ExpandedNodeId(pyuaf.util.NodeId(21, "SomeNameSpaceUri"), "SomeServerUri", 84)
    n10 = pyuaf.util.ExpandedNodeId(pyuaf.util.NodeId("SomeStringIdentifier", 42), "SomeServerUri", 84)
    
    n0_  = pyuaf.util.ExpandedNodeId()
    n1_  = pyuaf.util.ExpandedNodeId("SomeStringIdentifier", "SomeNameSpaceUri", "SomeServerUri")
    n2_  = pyuaf.util.ExpandedNodeId("SomeStringIdentifier", 42, "SomeServerUri")
    n3_  = pyuaf.util.ExpandedNodeId(21, "SomeNameSpaceUri", "SomeServerUri")
    n4_  = pyuaf.util.ExpandedNodeId(21, 42, "SomeServerUri")
    n5_  = pyuaf.util.ExpandedNodeId("SomeStringIdentifier", "SomeNameSpaceUri", 84)
    n6_  = pyuaf.util.ExpandedNodeId("SomeStringIdentifier", 42, 84)
    n7_  = pyuaf.util.ExpandedNodeId(21, "SomeNameSpaceUri", 84)
    n8_  = pyuaf.util.ExpandedNodeId(21, 42, 84)
    n9_  = pyuaf.util.ExpandedNodeId(pyuaf.util.NodeId(21, "SomeNameSpaceUri"), "SomeServerUri", 84)
    n10_ = pyuaf.util.ExpandedNodeId(pyuaf.util.NodeId("SomeStringIdentifier", 42), "SomeServerUri", 84)
    
    
    print(" - testing pyuaf.util.ExpandedNodeId().hasServerIndex()")
    assert (    n0.hasServerIndex()  == False
            and n1.hasServerIndex()  == False
            and n2.hasServerIndex()  == False
            and n3.hasServerIndex()  == False
            and n4.hasServerIndex()  == False
            and n5.hasServerIndex()  == True
            and n6.hasServerIndex()  == True
            and n7.hasServerIndex()  == True
            and n8.hasServerIndex()  == True
            and n9.hasServerIndex()  == True
            and n10.hasServerIndex() == True)
    
    print(" - testing pyuaf.util.ExpandedNodeId().hasNameSpaceUri()")
    assert (    n0.hasServerUri()  == False
            and n1.hasServerUri()  == True
            and n2.hasServerUri()  == True
            and n3.hasServerUri()  == True
            and n4.hasServerUri()  == True
            and n5.hasServerUri()  == False
            and n6.hasServerUri()  == False
            and n7.hasServerUri()  == False
            and n8.hasServerUri()  == False
            and n9.hasServerUri()  == True
            and n10.hasServerUri() == True)
    
    print(" - testing pyuaf.util.ExpandedNodeId().serverIndex()")
    assert n5.serverIndex() == 84
    
    print(" - testing pyuaf.util.ExpandedNodeId().serverUri()")
    assert n1.serverUri() == "SomeServerUri"
    
    print(" - testing pyuaf.util.ExpandedNodeId().nodeId()")
    assert n1.nodeId() == pyuaf.util.NodeId("SomeStringIdentifier", "SomeNameSpaceUri")
    assert n3.nodeId() == pyuaf.util.NodeId(21, "SomeNameSpaceUri")
    
    print(" - testing pyuaf.util.ExpandedNodeId().__eq__()")
    assert (    n0  == n0_ 
            and n1  == n1_ 
            and n2  == n2_ 
            and n3  == n3_ 
            and n4  == n4_ 
            and n5  == n5_ 
            and n6  == n6_ 
            and n7  == n7_ 
            and n8  == n8_ 
            and n9  == n9_ 
            and n10 == n10_)
    
    print(" - testing pyuaf.util.ExpandedNodeId().__ne__()")
    assert (    n0  != n1 
            and n1  != n2  
            and n2  != n3 
            and n3  != n4 
            and n4  != n5 
            and n5  != n6 
            and n6  != n7 
            and n7  != n8 
            and n8  != n9 
            and n9  != n10 
            and n10 != n0)
    
    print(" - testing pyuaf.util.ExpandedNodeId().__lt__()")
    assert n3 < n4
    assert n5 < n6
    
    print(" - testing pyuaf.util.ExpandedNodeId().__gt__()")
    assert n1 > n0
    assert n2 > n0
