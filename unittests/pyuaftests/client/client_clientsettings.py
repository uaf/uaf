import pyuaf
import unittest
from pyuaf.util.unittesting import parseArgs


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
    
    return unittest.TestLoader().loadTestsFromTestCase(ClientSettingsTest)


class ClientSettingsTest(unittest.TestCase):
    
    def setUp(self):
        settings = pyuaf.client.settings.ClientSettings()
        settings.applicationName = "c2"
        settings.logToStdOutLevel = ARGS.loglevel
    
        self.c0 = pyuaf.client.Client()
        self.c1 = pyuaf.client.Client("c1")
        self.c2 = pyuaf.client.Client(settings)
        
        self.cs0 = pyuaf.client.settings.ClientSettings()
        self.cs1 = pyuaf.client.settings.ClientSettings()
        self.cs2 = pyuaf.client.settings.ClientSettings()
        self.cs2.logToStdOutLevel = ARGS.loglevel
        
        self.cs1.applicationName = "c1"
        self.cs2.applicationName = "c2"
    
    def test_client_Client_clientSettings(self):
        self.assertEqual( self.c0.clientSettings() , self.cs0 )
        self.assertEqual( self.c1.clientSettings() , self.cs1 )
        self.assertEqual( self.c2.clientSettings() , self.cs2 )
        
    def test_client_Client_setClientSettings(self):
        cs0_ = pyuaf.client.settings.ClientSettings()
        cs1_ = pyuaf.client.settings.ClientSettings()
        cs2_ = pyuaf.client.settings.ClientSettings()
        
        cs0_.applicationName = "aaa"
        cs1_.applicationName = "bbb"
        cs2_.applicationName = "ccc"
        
        self.c0.setClientSettings(cs0_)
        self.c1.setClientSettings(cs1_)
        self.c2.setClientSettings(cs2_)
        
        self.assertEqual( self.c0.clientSettings() , cs0_ )
        self.assertEqual( self.c1.clientSettings() , cs1_ )
        self.assertEqual( self.c2.clientSettings() , cs2_ )
    
    def tearDown(self):
        # delete the client instances manually (now!) instead of letting them be garbage collected 
        # automatically (which may happen during a another test, and which may cause logging output
        # of the destruction to be mixed with the logging output of the other test).
        del self.c0
        del self.c1
        del self.c2


if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())
