import unittest
from pyuaf.util.unittesting import parseArgs


ARGS = parseArgs()



def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
        
    suite = unittest.TestSuite()
    
    from pyuaftests import all_util_tests
    suite.addTest(all_util_tests.suite(args))
    
    from pyuaftests import all_client_tests
    suite.addTest(all_client_tests.suite(args))
    
    return suite


if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())