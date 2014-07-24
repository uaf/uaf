import pyuaf
from pyuaf.client           import Client
from pyuaf.client.settings  import ClientSettings, SessionSettings, SessionSecuritySettings
from pyuaf.util             import Address, NodeId
from pyuaf.util.errors      import UafError, ConnectionError


DISCOVERY_URL = "opc.tcp://localhost:48010"
SERVER_URI   = "urn:UnifiedAutomation:UaServerCpp"




# define the ClientSettings (note that we do NOT provide a discoveryUrl!!!):
settings = ClientSettings()
settings.applicationName = "MyClient"
settings.logToStdOutLevel = pyuaf.util.loglevels.Debug
settings.discoveryUrls.append(DISCOVERY_URL)

<<<<<<< HEAD
settings.certificateTrustAbsoluteDirectory = "/opt/unifiedautomation/sdk/bin/pkiserver/trusted"
settings.certificateRevocationListAbsoluteFileName = ""
settings.clientCertificateAbsoluteFileName = "/opt/unifiedautomation/sdk/bin/pkiserver/own/certs/uaservercpp.der"
settings.clientPrivateKeyAbsoluteFileName = "/opt/unifiedautomation/sdk/bin/pkiserver/own/private/uaservercpp.pem"
=======
settings.clientCertificateAbsoluteFileName = "dsds"
>>>>>>> 032a7dc7ed18e835ff8b31b7dcd3771a98f41990

# create the client
myClient = Client(settings)


sess = SessionSettings()

secu = SessionSecuritySettings()
secu.securityPolicy      = pyuaf.util.securitypolicies.UA_Basic128Rsa15
secu.messageSecurityMode = pyuaf.util.messagesecuritymodes.Mode_Sign

<<<<<<< HEAD
sess.securitySettingsList[0] = secu


=======


sess.securitySettingsList[0] = secu

>>>>>>> 032a7dc7ed18e835ff8b31b7dcd3771a98f41990

id = myClient.manuallyConnect(SERVER_URI, sess)
info = myClient.sessionInformation(id)
print myClient.sessionInformation(id)

print myClient.serversFound()

assert info.sessionState == pyuaf.client.sessionstates.Connected

#someAddress = Address(NodeId("Demo.SimulationSpeed",                         # NodeId identifier
#                             "http://www.unifiedautomation.com/DemoServer"), # NodeId namespace URI
#                      "urn:UnifiedAutomation:UaServerCpp")                   # server URI
#
#result = myClient.read( [someAddress] )
#
#print result