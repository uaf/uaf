import pyuaf
from pyuaf.util import DateTime
import time

def test(args):
    
    print("util.datetime")
    
    print(" - testing pyuaf.util.DateTime()")
    
    dt0 = pyuaf.util.DateTime()
    
    now  = time.time()
    dt1  = DateTime(now)
    dt1_ = DateTime(dt1)
    dt2  = DateTime(now + 3.0) # 3 seconds later
    dt3  = DateTime(now + 60*60*24*3) # 3 days later
    
    print(" - testing pyuaf.util.DateTime().isNull()")
    assert dt0.isNull() == True
    assert dt1.isNull() == False
    
    print(" - testing pyuaf.util.DateTime().ctime()")
    # check if the difference is smaller than 1 msec    
    assert now - dt1.ctime() <= 0.001
    
    print(" - testing pyuaf.util.DateTime().setCtime()")
    dt = DateTime()
    dt.setCtime(now) 
    assert now - dt.ctime() <= 0.001
    
    print(" - testing pyuaf.util.DateTime().toTime_t()")
    assert long(now) == dt1.toTime_t()
    
    print(" - testing pyuaf.util.DateTime().msec()")
    assert (now % 1) * 1000 - dt1.msec() <= 1
    
    print(" - testing pyuaf.util.DateTime().daysTo()")
    assert dt1.daysTo(dt3) == 3
    
    print(" - testing pyuaf.util.DateTime().secsTo()")
    assert dt1.secsTo(dt2) == 3
    
    print(" - testing pyuaf.util.DateTime().msecsTo()")
    assert dt1.msecsTo(dt2) == 3000
    
    print(" - testing pyuaf.util.DateTime().addSecs()")
    dt = DateTime(dt1)
    dt.addSecs(3)
    assert dt == dt2
    
    print(" - testing pyuaf.util.DateTime().addMilliSecs()")
    dt = DateTime(dt1)
    dt.addMilliSecs(3000)
    assert dt == dt2
    
    print(" - testing pyuaf.util.DateTime().__eq__()")
    assert dt1 == dt1_
    assert not (dt1 == dt2)
    
    print(" - testing pyuaf.util.DateTime().__ne__()")
    assert dt1 != dt2
    assert not (dt1 != dt1_)
    
    print(" - testing pyuaf.util.DateTime().__lt__()")
    assert dt1 < dt2
    
    print(" - testing pyuaf.util.DateTime().__gt__()")
    assert dt3 > dt2

