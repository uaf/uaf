import pyuaf
import unittest
from pyuaf.util.unittesting import parseArgs, testVector

import os

ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(VersionTest)



class VersionTest(unittest.TestCase):
    
    def test_version(self):
      thisFile = os.path.realpath(__file__)  
      versionTxt = os.path.realpath(os.path.join(thisFile, "..", "..", "..", "..","version.txt"))
      
      self.assertTrue(os.path.exists(versionTxt))
      
      # read the version
      f = open(versionTxt, 'r')
      version = f.read()
      f.close()
      
      self.assertEqual(version, pyuaf.__version__)
          
        

if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())
