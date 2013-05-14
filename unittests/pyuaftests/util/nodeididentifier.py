import pyuaf


def test(args):
        
    print("util.nodeididentifier")
    
    print(" - testing pyuaf.util.NodeIdIdentifier()")
    n0  = pyuaf.util.NodeIdIdentifier("SomeStringIdentifier")
    n0_ = pyuaf.util.NodeIdIdentifier("SomeStringIdentifier")
    n1  = pyuaf.util.NodeIdIdentifier(42)
    n2  = pyuaf.util.NodeIdIdentifier("SomeOtherStringIdentifier")
    
    print(" - testing pyuaf.util.NodeIdIdentifier().type")
    assert n0.type == pyuaf.util.nodeididentifiertypes.String
    assert n1.type == pyuaf.util.nodeididentifiertypes.Numeric
    
    print(" - testing pyuaf.util.NodeIdIdentifier().idString")
    assert n0.idString == "SomeStringIdentifier"
    
    print(" - testing pyuaf.util.NodeIdIdentifier().idInt")
    assert n1.idNumeric == 42
    
    print(" - testing pyuaf.util.NodeIdIdentifier().__eq__()")
    assert n0 == n0_
    
    print(" - testing pyuaf.util.NodeIdIdentifier().__ne__()")
    assert n0 != n1
    assert n0 != n2
    
    print(" - testing pyuaf.util.NodeIdIdentifier().__lt__()")
    assert n1 < n0
    assert n2 < n0
    
    print(" - testing pyuaf.util.NodeIdIdentifier().__gt__()")
    assert n0 > n1
    assert n0 > n2
