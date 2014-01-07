import pyuaf
import unittest
from pyuaf.util.unittesting import parseArgs


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(ClientConstructorTest)


class ClientConstructorTest(unittest.TestCase):
    
    
    def test_client_Client___init__(self):
        c0 = pyuaf.client.Client()
        c1 = pyuaf.client.Client("c1")
        
        settings = pyuaf.client.settings.ClientSettings()
        settings.applicationName = "c2"
        settings.logToStdOut = True
        settings.logToStdOutLevel = ARGS.loglevel
        c2 = pyuaf.client.Client(settings)
        # delete the client instances manually (now!) instead of letting them be garbage collected 
        # automatically (which may happen during a another test, and which may cause logging output
        # of the destruction to be mixed with the logging output of the other test).
        del c0
        del c1
        del c2


if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())