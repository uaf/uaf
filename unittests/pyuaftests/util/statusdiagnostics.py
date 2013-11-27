import pyuaf


def test(args):
        
    print("util.statusdiagnostics")
    
    
    print(" - testing pyuaf.util.StatusDiagnostics()")
    s0  = pyuaf.util.StatusDiagnostics()
    
    print(" - testing pyuaf.util.StatusDiagnostics().setDescription() and getDescription()")
    s0.setDescription("test")
    assert s0.getDescription() == "test"
    
    print(" - testing pyuaf.util.StatusDiagnostics().hasDescription()")
    assert s0.hasDescription() == True
    
    print(" - testing pyuaf.util.StatusDiagnostics().setNotificationHandles() and getNotificationHandles()")
    s0.setNotificationHandles([1,2,3])
    assert s0.getNotificationHandles() == (1,2,3)
    
    print(" - testing pyuaf.util.StatusDiagnostics().hasNotificationHandles()")
    assert s0.hasNotificationHandles() == True
    
    print(" - testing pyuaf.util.StatusDiagnostics().__eq__()")
    s0_ = pyuaf.util.StatusDiagnostics()
    s0_.setDescription("test")
    s0_.setNotificationHandles([1,2,3])
    
    assert s0 == s0_
    
    print(" - testing pyuaf.util.StatusDiagnostics().__ne__()")
    s1  = pyuaf.util.StatusDiagnostics()
    s1.setDescription("somethingElse")
    s2  = pyuaf.util.StatusDiagnostics()
    s2.setNotificationHandles([4,5,6,7])
    assert s0 != s1
    assert s0 != s2
    assert s1 != s2
    
    print(" - testing pyuaf.util.StatusDiagnostics().__lt__()")
    assert s1 < s0
    assert s2 < s0
    assert s2 < s1
    
    print(" - testing pyuaf.util.StatusDiagnostics().__gt__()")
    assert s0 > s1
    assert s0 > s2
    assert s1 > s2
    
    
