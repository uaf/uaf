import pyuaf
from pyuaf.util import DateTime
import unittest
from pyuaf.util.unittesting import parseArgs, testVector
import time


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args

    return unittest.TestLoader().loadTestsFromTestCase(DateTimeTest)



class DateTimeTest(unittest.TestCase):


    def setUp(self):
        self.dt0 = pyuaf.util.DateTime()

        self.now  = time.time()
        self.dt1  = DateTime(self.now)
        self.dt1_ = DateTime(self.dt1)
        self.dt2  = DateTime(self.now + 3.0) # 3 seconds later
        self.dt3  = DateTime(self.now + 60*60*24*3) # 3 days later

    def test_util_DateTime_isNull(self):
        self.assertEqual( self.dt0.isNull() , True  )
        self.assertEqual( self.dt1.isNull() , False )

    def test_util_DateTime_ctime(self):
        # check if the difference is smaller than 1 msec
        self.assertTrue( self.now - self.dt1.ctime() <= 0.001 )

    def test_util_DateTime_setCtime(self):
        dt = DateTime()
        dt.setCtime(self.now)
        # check if the difference is smaller than 1 msec
        self.assertTrue( self.now - dt.ctime() <= 0.001 )

    def test_util_DateTime_toTime_t(self):
        self.assertEqual( int(self.now) , self.dt1.toTime_t() )

    def test_util_DateTime_msec(self):
        self.assertLessEqual( (self.now % 1) * 1000 - self.dt1.msec() , 1 )

    def test_util_DateTime_daysTo(self):
        self.assertEqual( self.dt1.daysTo(self.dt3) , 3 )

    def test_util_DateTime_secsTo(self):
        self.assertEqual( self.dt1.secsTo(self.dt2) , 3 )

    def test_util_DateTime_msecsTo(self):
        self.assertEqual( self.dt1.msecsTo(self.dt2) , 3000 )

    def test_util_DateTime_addSecs(self):
        dt = DateTime(self.dt1)
        dt.addSecs(3)
        self.assertEqual( dt , self.dt2 )

    def test_util_DateTime_addMilliSecs(self):
        dt = DateTime(self.dt1)
        dt.addMilliSecs(3000)
        self.assertEqual( dt , self.dt2 )

    def test_util_DateTime___eq__(self):
        self.assertTrue( self.dt1 == self.dt1_ )
        self.assertFalse( self.dt1 == self.dt2 )

    def test_util_DateTime___ne__(self):
        self.assertTrue(  self.dt1 != self.dt2 )
        self.assertFalse( self.dt1 != self.dt1_)

    def test_util_DateTime___lt__(self):
        self.assertTrue( self.dt1 < self.dt2 )

    def test_util_DateTime___gt__(self):
        self.assertTrue( self.dt3 > self.dt2 )

    def test_util_DateTimeVector(self):
        testVector(self, pyuaf.util.DateTimeVector, [self.dt0, self.dt1, self.dt2, self.dt3])


if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())