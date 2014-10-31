import pyuaf
from pyuaf.client           import Client
from pyuaf.client.settings  import ClientSettings, SessionSettings, SessionSecuritySettings
from pyuaf.util             import Address, NodeId
from pyuaf.util             import PkiRsaKeyPair, PkiIdentity, PkiCertificateInfo, PkiCertificate
from pyuaf.util.errors      import UafError, ConnectionError
from pyuaf.util             import securitypolicies, messagesecuritymodes
import socket
import shutil
import os
import subprocess

DISCOVERY_URL     = "opc.tcp://localhost:48010"
SERVER_URI        = "urn:UnifiedAutomation:UaServerCpp"
DEMOSERVER_NS_URI = "http://www.unifiedautomation.com/DemoServer"

# define a folder where we will store the Public Key Infrastructure files (i.e. certificates and keys)
PKI_FOLDER = "./securityexample/PKI"





description = """
To run this example, start the UaServerCpp demo server first.
If you use the evaluation SDK, you can find thCliente executable here (e.g. on Windows):
   C:/Program Files/UnifiedAutomation/UaSdkCppBundleEval/bin/uaservercpp.exe
Note that all paths below must ALWAYS be specified using '/' separators, also on Windows!
This means you cannot use e.g. os.path.join or similar, since those functions may
introduce platform-dependent path separators.

Here's how the UAF Client handles certificates:
1) first the server certificate is verified. 
   This server certificate was automatically received and kept in memory by the UAF
   client in the background during the discovery process, so you don't have to take 
   care of it yourself. (Note, that if you use ``manuallyConnectToEndpoint`` to avoid 
   discovery for some reason, you may provide the server certificate manually). 
   If the server certificate is not trusted (e.g. because it's invalid or because 
   it's not in the trust list), then the ``untrustedServerCertificateReceived`` 
   will be called. This is done **regardless** of whether or not you want to sign or
   encrypt your communication! In this step you're **only** checking if you're trying
   to connect to the right server. In principle you should always override the 
   ``untrustedServerCertificateReceived`` method for this purpose (or register
   your own callback via ``registerUntrustedServerCertificateCallback``). 
   By default pyuaf will simply assume that you trust the server to which you're
   trying to connect (i.e. ``untrustedServerCertificateReceived`` returns 
   ``Action_AcceptTemporarily`` unless you override it). 
2) then both the client and server certificates are sent around again:
   - so that the server can decide to accept or reject the session
   - and so that the actual communication data can be encrypted and/or signed, 
     if needed.
   All of this is handled by the UAF and SDK behind the scenes, so you don't have to 
   take care of it yourself. Basically you only have to configure the client
   settings and session settings. 
   
"""
print(description)

print("")
print("===========================================================================================")
print(" STEP 0: Cleanup and files and directories in the securityexample/ folder, if you want")
print("===========================================================================================")
print("")

if os.path.exists(PKI_FOLDER):
    print("Remove the %s folder and all of its contents?" %PKI_FOLDER)
    answer = raw_input("Enter your choice (y/n) [n] : ")
    
    if answer.upper() in ["Y", "YES"]:
        shutil.rmtree(PKI_FOLDER)


print("")
print("===========================================================================================")
print("STEP 1: Create a client Certificate")
print("===========================================================================================")
print("")

# we will create a self-signed certificate, which means that the subject and issuer are the same!

keyPair = PkiRsaKeyPair(1024)
issuerPrivateKey = keyPair.privateKey()
subjectPublicKey = keyPair.publicKey()

identity = PkiIdentity()
identity.commonName         = "Wim Pessemier"
identity.organization       = "KU Leuven"
identity.organizationUnit   = "Institute of Astronomy"
identity.locality           = "Leuven"
identity.country            = "BE"

info = PkiCertificateInfo()
info.uri        = "urn:%s:InstituteOfAstronomy::MyExampleCode" %socket.gethostname() # must be unique!
info.dns        = socket.gethostname()
info.eMail      = "Wxx.Pxxxxxxxx@ster.kuleuven.be"
info.validTime  = 60*60*24*365*5 # 5 years

certificate = PkiCertificate(info, identity, subjectPublicKey,  identity, issuerPrivateKey)

# note: we will store the certificate and private key in STEP 3

print("")
print("===========================================================================================")
print("STEP 2: Create a Client instance")
print("===========================================================================================")
print("")


# define the settings
settings = ClientSettings()
settings.applicationName  = "MyClient"
settings.applicationUri   = info.uri # Certificate info URI and application URI must be the same !!!
#settings.logToStdOutLevel = pyuaf.util.loglevels.Debug # uncomment if needed
settings.discoveryUrls.append(DISCOVERY_URL)

# We configure the PKI folder structure (set the PKI_FOLDER to 'PKI' and you get the defaults).
# Note that paths must ALWAYS be specified using '/', also on Windows! 
# You cannot use os.path.join or similar, since these will introduce platform-dependent separators!
settings.clientCertificate                 = PKI_FOLDER + '/client/certs/client.der'
settings.clientPrivateKey                  = PKI_FOLDER + '/client/private/client.pem'
settings.certificateTrustListLocation      = PKI_FOLDER + '/trusted/certs/'
settings.certificateRevocationListLocation = PKI_FOLDER + '/trusted/crl/'
settings.issuersCertificatesLocation       = PKI_FOLDER + '/issuers/certs/'
settings.issuersRevocationListLocation     = PKI_FOLDER + '/issuers/crl/'

# make sure the above directories are created
settings.createSecurityLocations()

# create the client
myClient = Client(settings)

print("")
print("===========================================================================================")
print("STEP 3: Store the client certificate and private key")
print("===========================================================================================")
print("")

# store the certificate 
result = certificate.toDERFile(settings.clientCertificate)
if result == -1:
    raise Exception("Could not save the client certificate!")

# store the private key:
result = keyPair.toPEMFile(settings.clientPrivateKey)
if result == -1:
    raise Exception("Could not save the client private key!")


print("")
print("===========================================================================================")
print("STEP 4: Copy the client certificate to the trust list of the demo server")
print("===========================================================================================")
print("")

# for convenience, let's try to find out the path of the uaservercpp demo server,
# so that the user doesn't have to type this path manually
if os.name == "posix":
    # in linux we can do the following trick: since the uaservercpp process should be running, 
    # we can extract the uaservercpp path from there
    uaservercpp = subprocess.Popen("ps ax -o cmd | grep uaservercpp", 
                                   shell=True, 
                                   stdout=subprocess.PIPE).stdout.read().split('\n')[0]
    suggestion = os.path.dirname(uaservercpp) + "/pkiserver/trusted/certs/pyuafexample.der"
elif os.name == "nt":
    suggestion = "C:/Documents and Settings/All Users/Application Data/UnifiedAutomation/UaSdkCppBundleEval/pkiserver/trusted/certs/pyuafexample.der"
else:
    suggestion = ""

print("Enter the path to copy the client certificate to,")
print(" or leave blank to accept the following suggestion:")
print(" '%s'" %suggestion)
answer = raw_input("Enter your choice: ")

if answer == "":
    answer = suggestion

# store the certificate 
result = certificate.toDERFile(answer)
if result == -1:
    raise Exception("Could not save the client certificate to %s" %answer)



print("")
print("===========================================================================================")
print("STEP 5: Configure the session to be created")
print("===========================================================================================")
print("")

# WARNING: THIS API MAY CHANGE WHEN UAF v2.0.0 WILL BE RELEASED !!!

# suppose we want Basic128Rsa15 encryption + signed communication:
sessionSettings = SessionSettings()
sessionSettings.securitySettingsList[0].securityPolicy      = securitypolicies.UA_Basic128Rsa15
sessionSettings.securitySettingsList[0].messageSecurityMode = messagesecuritymodes.Mode_Sign


print("")
print("===========================================================================================")
print("STEP 6: Register a callback function to handle the server certificate")
print("===========================================================================================")
print("")


def myCallback(certificate, cause):
    print("The following server certificate was not found in the trust list:")
    print(certificate)
    print("")
    print("Choose one of the following options:")
    print(" [r] : Reject the certificate")
    print(" [t] : Accept the certificate Temporarily (i.e. don't store it inside the trust list)")
    print(" [p] : Accept the certificate Permanently (i.e. store it inside the trust list)")
    answer = raw_input("Enter your choice (r/t/p) [r] : ")
    
    if answer.upper() == "R":
        return PkiCertificate.Action_Reject
    elif answer.upper() == "T":
        return PkiCertificate.Action_AcceptTemporarily
    elif answer.upper() == "P":
        return PkiCertificate.Action_AcceptPermanently
    else:
        print("INVALID CHOICE")
        print("The certificate will be rejected.")
        return PkiCertificate.Action_Reject


myClient.registerUntrustedServerCertificateCallback(myCallback)



print("")
print("===========================================================================================")
print("STEP 7: Read some variable using the configured secure session")
print("===========================================================================================")
print("")

# define the address of a node which we would like to read:
someAddress = Address(NodeId("Demo.SimulationSpeed", DEMOSERVER_NS_URI), SERVER_URI)

cfg = pyuaf.client.configs.SessionConfig()
cfg.defaultSessionSettings = sessionSettings

result = myClient.read( [someAddress], sessionConfig = cfg )

print("")
print("Read result:")
print(result)
print("")


# check the session that was used to read this address:
if result.overallStatus.isGood():
    print("Information about the session:")
    print(myClient.sessionInformation(result.targets[0].clientConnectionId))


