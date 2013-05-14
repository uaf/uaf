// examples/uaf/src/client/how_to_change_the_default_session_behavior.cpp
/*
 * EXAMPLE: how to change the default session behavior
 * =================================================================================================
 *
 * A SessionConfig instance can be used to configure one or more sessions that need to be created,
 * in order to successfully invoke an OPC UA service.
 *
 * This is an example to show you some more advanced feature of the UAF, you can skip it if you're
 * happy with the default session behavior of the UAF!
 *
 * As always, in the UAF terminology, a "config" object holds one or more "settings" objects.
 *
 * In this case, a SessionConfig holds
 *  - one SessionSettings object to specify "default" settings for sessions that need to be created
 *    during the service call
 *  - and optionally some particular SessionSettings objects for sessions to particular servers.
 *
 * Because a SessionConfig can contain settings for many different servers, you can create and
 * configure one SessionConfig, and then re-use this SessionConfig for multiple service calls.
 */

#include "uaf/client/client.h"

using namespace uaf;
using namespace uafc;


int main(int argc, char* argv[])
{
    // always initialize the framework first!
    initializeUaf();

    printf("This example will fail when executed, since it tries to connect to non-existing servers\n");

    // create a single SessionConfig object that we will use for all our service calls
    SessionConfig sessionCfg;

    // configure the default settings for the sessions that will be created
    sessionCfg.defaultSessionSettings.sessionTimeoutSec = 100.0;
    sessionCfg.defaultSessionSettings.connectTimeoutSec = 2.0;

    // for a particular server (an embedded device) we expect an unreliable connection,
    // so we specify some settings that are more suitable for this particular server
    sessionCfg.specificSessionSettings["My/Unreliable/Device/Server"].sessionTimeoutSec = 200.0;
    sessionCfg.specificSessionSettings["My/Unreliable/Device/Server"].connectTimeoutSec = 5.0;

    // we also have a particular very reliable and fast server (some PLC), for which we want to
    // specify other settings:
    sessionCfg.specificSessionSettings["My/Reliable/PLC/Server"].connectTimeoutSec = 0.5;

    // Now we can use the same config for many different service calls.
    // Sessions will be created silently in the background by the UAF, based on the
    // settings we provided via the 'sessionCfg' object.
    // If sessions need to be created to the "My/Unreliable/Device/Uri" or "My/Reliable/PLC/Uri"
    // servers, they will be created according to the specified settings.
    // If sessions need to be created to other servers, they will be created according to the
    // defaultSessionSettings settings.

    // configure a client ...
    ClientSettings clientSettings;
    clientSettings.applicationName = "MyClient";
    clientSettings.discoveryUrls.push_back("opc.tcp://10.133.78.42");
    clientSettings.discoveryUrls.push_back("opc.tcp://10.133.78.81");
    clientSettings.discoveryUrls.push_back("opc.tcp://10.134.25.16");

    // ... and create the client
    Client myClient(clientSettings);

    // define some addresses
    Address temperature1(NodeId("temperature1" , "MyCompanyNamespace"), "Some/OPCUA/Server");
    Address temperature2(NodeId("temperature2" , "MyCompanyNamespace"), "Some/OPCUA/Server");
    Address pressure0005(NodeId("pressure0005" , "MyCompanyNamespace"), "My/Unreliable/Device/Server");
    Address motorStatus3(NodeId("motorStatus3" , "MyCompanyNamespace"), "My/Reliable/PLC/Server");

    // now we can read, write, ... any address(es) without worrying about the settings of the sessions!

    // read the Value attribute of the 4 nodes that we just addressed
    std::vector<Address> myReadNodes;
    myReadNodes.push_back(temperature1);
    myReadNodes.push_back(temperature2);
    myReadNodes.push_back(pressure0005);
    myReadNodes.push_back(motorStatus3);
    ReadResult myReadResult;
    Status readStatus  = myClient.read(myReadNodes,
                                       uaf::attributeids::Value, // read the Value attribute
                                       uafc::ReadConfig(),       // default settings for the Read service
                                       sessionCfg,
                                       myReadResult);

    std::cout << "Read status: " << readStatus.toString() << "\n";

    // write a new motor status (notice that you use the same 'sessionCfg' object!)
    std::vector<Address> myWriteNodes;
    myWriteNodes.push_back(motorStatus3);
    std::vector<Variant> myData(1);
    myData[0].setByte(0x3);
    WriteResult myWriteResult;
    Status writeStatus = myClient.write(myWriteNodes,
                                        myData,
                                        uaf::attributeids::Value, // write the Value attribute
                                        uafc::WriteConfig(),      // default settings for the Write service
                                        sessionCfg,
                                        myWriteResult);

    std::cout << "Write status: " << writeStatus.toString() << "\n";

    // do some other stuff like monitoring variables, calling methods, ... all using
    // the same SessionConfig object ('sessionCfg')
    // ...

    // don't worry about disconnecting sessions etc., these things will be done automatically
    // when the client is destroyed.

    return 0;
}
