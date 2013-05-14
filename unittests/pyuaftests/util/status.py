import pyuaf


def test(args):
        
    print("util.status")
    
    
    print(" - testing pyuaf.util.Status()")
    s0  = pyuaf.util.Status()
    s1  = pyuaf.util.Status(pyuaf.util.statuscodes.Good)
    s2  = pyuaf.util.Status(pyuaf.util.statuscodes.InvalidRequestError)
    s3  = pyuaf.util.Status(pyuaf.util.statuscodes.ConnectionError, "Some connection error")
    s3_ = pyuaf.util.Status(pyuaf.util.statuscodes.ConnectionError, "Some connection error")
    s4  = pyuaf.util.Status(pyuaf.util.statuscodes.ConnectionError, "Some other connection error")
    s5  = pyuaf.util.Status(pyuaf.util.statuscodes.ResolutionError, "Some address resolution error")
    
    print(" - testing pyuaf.util.Status().isUncertain()")
    assert s0.isUncertain()
    assert not s1.isUncertain()
    assert not s2.isUncertain()
    
    print(" - testing pyuaf.util.Status().isNotUncertain()")
    assert not s0.isNotUncertain()
    assert s1.isNotUncertain()
    assert s2.isNotUncertain()
    
    print(" - testing pyuaf.util.Status().isGood()")
    assert not s0.isGood()
    assert s1.isGood()
    assert not s2.isGood()
    
    print(" - testing pyuaf.util.Status().isNotGood()")
    assert s0.isNotGood()
    assert not s1.isNotGood()
    assert s2.isNotGood()
    
    print(" - testing pyuaf.util.Status().isBad()")
    assert not s0.isBad()
    assert not s1.isBad()
    assert s2.isBad()
    
    print(" - testing pyuaf.util.Status().isNotBad()")
    assert s0.isNotBad()
    assert s1.isNotBad()
    assert not s2.isNotBad()
    
    
    print(" - testing pyuaf.util.Status().statusCode()")
    assert s2.statusCode() == pyuaf.util.statuscodes.InvalidRequestError
    
    print(" - testing pyuaf.util.Status().statusCodeName()")
    assert s2.statusCodeName() == "InvalidRequestError"
    
    print(" - testing pyuaf.util.Status().__eq__()")
    assert s3 == s3_
    
    print(" - testing pyuaf.util.Status().__ne__()")
    assert s3 != s4
    assert s3 != s5
    
    print(" - testing pyuaf.util.Status().__lt__()")
    assert s3 < s4
    assert s3 < s5
    
    print(" - testing pyuaf.util.Status().__gt__()")
    assert s4 > s3
    assert s5 > s3
    
