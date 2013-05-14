import pyuaf


def test(args):
    
    print("util.browsepath")
    
    print(" - testing pyuaf.util.BrowsePath()")
    
    nsUri = "someNameSpaceUri"
    
    startingExpandedNodeId = pyuaf.util.ExpandedNodeId("someId", nsUri, "someServerUri")
    
    element0 = pyuaf.util.RelativePathElement(pyuaf.util.QualifiedName("element0", nsUri))
    element1 = pyuaf.util.RelativePathElement(pyuaf.util.QualifiedName("element1", nsUri))
    
    b0 = pyuaf.util.BrowsePath()
    b1 = pyuaf.util.BrowsePath(startingExpandedNodeId, [element0, element1])
    
    assert b0.startingExpandedNodeId == pyuaf.util.ExpandedNodeId()
    assert len(b0.relativePath) == 0
    
    assert b1.startingExpandedNodeId == startingExpandedNodeId
    assert b1.relativePath[0] == element0
    assert b1.relativePath[1] == element1
    
    
    