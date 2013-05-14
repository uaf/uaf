import pyuaf


def test(args):
    
    print("client.client_clientsettings")
    
    settings = pyuaf.client.settings.ClientSettings()
    settings.applicationName = "c2"
    settings.logToStdOutLevel = args.loglevel
    
    c0 = pyuaf.client.Client()
    c1 = pyuaf.client.Client("c1")
    c2 = pyuaf.client.Client(settings)
    
    print(" - testing pyuaf.client.Client().clientSettings()")
    cs0 = pyuaf.client.settings.ClientSettings()
    cs1 = pyuaf.client.settings.ClientSettings()
    cs2 = pyuaf.client.settings.ClientSettings()
    cs2.logToStdOutLevel = args.loglevel
    
    cs1.applicationName = "c1"
    cs2.applicationName = "c2"
    
    assert c0.clientSettings() == cs0
    assert c1.clientSettings() == cs1
    assert c2.clientSettings() == cs2
    
    print(" - testing pyuaf.client.Client().setClientSettings()")
    
    cs0_ = pyuaf.client.settings.ClientSettings()
    cs1_ = pyuaf.client.settings.ClientSettings()
    cs2_ = pyuaf.client.settings.ClientSettings()
    
    cs0_.applicationName = "aaa"
    cs1_.applicationName = "bbb"
    cs2_.applicationName = "ccc"
    
    c0.setClientSettings(cs0_)
    c1.setClientSettings(cs1_)
    c2.setClientSettings(cs2_)
    
    assert c0.clientSettings() == cs0_
    assert c1.clientSettings() == cs1_
    assert c2.clientSettings() == cs2_
    
    # delete the client instances manually (now!) instead of letting them be garbage collected 
    # automatically (which may happen during a another test, and which may cause logging output
    # of the destruction to be mixed with the logging output of the other test).
    del c0
    del c1
    del c2

