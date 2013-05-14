import pyuaf
    

def test(args):
    
    print("client.client_client")
    
    print(" - testing pyuaf.client.Client()")
    c0 = pyuaf.client.Client()
    c1 = pyuaf.client.Client("c1")
    
    settings = pyuaf.client.settings.ClientSettings()
    settings.applicationName = "c2"
    settings.logToStdOut = True
    settings.logToStdOutLevel = args.loglevel
    c2 = pyuaf.client.Client(settings)
    
    
    print(" - testing pyuaf.client.~Client()")
    # delete the client instances manually (now!) instead of letting them be garbage collected 
    # automatically (which may happen during a another test, and which may cause logging output
    # of the destruction to be mixed with the logging output of the other test).
    del c0
    del c1
    del c2