import pyuaf


def test(args):
    
    print("util.mask")
    
    print(" - testing pyuaf.util.Mask()")
    
    m0 = pyuaf.util.Mask(5, True)
    m1 = pyuaf.util.Mask(7, False)
    
    print(" - testing pyuaf.util.Mask().size()")
    assert m0.size() == 5
    assert m1.size() == 7
    
    print(" - testing pyuaf.util.Mask().unset()")
    m0.unset(1)
    m0.unset(2)
    
    print(" - testing pyuaf.util.Mask().set()")
    m1.set(2)
    m1.set(3)
    
    print(" - testing pyuaf.util.Mask().setCount()")
    assert m0.setCount() == 3
    assert m1.setCount() == 2
    
    print(" - testing pyuaf.util.Mask().unsetCount()")
    assert m0.unsetCount() == 2
    assert m1.unsetCount() == 5
    
    print(" - testing pyuaf.util.Mask().isSet()")
    assert m0.isSet(0) == True
    assert m0.isSet(1) == False
    
    print(" - testing pyuaf.util.Mask().isUnset()")
    assert m0.isUnset(0) == False
    assert m0.isUnset(1) == True
    
    print(" - testing pyuaf.util.Mask().__and__()")
    logicalAndResult = pyuaf.util.Mask(5, False)
    logicalAndResult.set(3)
    assert((m0 & m1) == logicalAndResult)
    assert((m1 & m0) == (m0 & m1))

