// examples/uaf/src/client/how_to_write_some_data_asynchronously.cpp
/*
 * EXAMPLE: how to write some data asynchronously
 * =================================================================================================

 * A UAF Client can write data asynchronously in two ways:
 *   - either using the "convenience" method: beginWrite()
 *   - or using the "generic" method: processRequest()
 *
 * The "convenience" methods (such as read(), write(), beginWrite(), ...) are conveniently to use
 *  (since they accept the most frequently used parameters directly),
 * but they are less powerful than the "generic" processRequest() method
 *  (since this method accepts ReadRequests, WriteRequests, etc. that can be fully configured).
 *
 * To run the example, start the UaServerCPP of UnifiedAutomation first on the same machine.
 */

#include "uaf/client/client.h"

using namespace uaf;
using std::string;
using std::cout;
using std::vector;
using std::size_t;


class MyClient : public Client
{
public:
    MyClient(const ClientSettings& settings) : Client(settings) {}
    void writeComplete(const uaf::WriteResult& result) {
        cout << "writeComplete result:\n";
        cout << result.toString().c_str();
        cout << "\n";
    }

};


int main(int argc, char* argv[])
{
    // always initialize the framework first!
    initializeUaf();

    // define the namespace URI and server URI of the UaServerCPP
    string demoNsUri("http://www.unifiedautomation.com/DemoServer");
    string demoServerUri("urn:UnifiedAutomation:UaServerCpp");

    // define some addresses of nodes of which we will write the Value attribute
    // (you could also define addresses as Relative Paths to other addresses,
    //  see the example that shows you how to define addresses)
    Address someDoubleNode(        NodeId("Demo.Static.Scalar.Double"        , demoNsUri), demoServerUri );
    Address someUInt32Node(        NodeId("Demo.Static.Scalar.UInt32"        , demoNsUri), demoServerUri );
    Address someStringNode(        NodeId("Demo.Static.Scalar.String"        , demoNsUri), demoServerUri );
    Address someLocalizedTextNode( NodeId("Demo.Static.Scalar.LocalizedText" , demoNsUri), demoServerUri );
    Address someSByteArrayNode(    NodeId("Demo.Static.Arrays.SByte"         , demoNsUri), demoServerUri );

    // define the ClientSettings:
    ClientSettings settings;
    settings.applicationName = "MyClient";
    settings.discoveryUrls.push_back("opc.tcp://localhost:48010");

    // create the client
    MyClient myClient(settings);

    // OPTIONAL: You could also provide a WriteSettings instance to configure a call timeout
    WriteSettings serviceSettings;
    serviceSettings.callTimeoutSec = 0.5;

    // OPTIONAL: And you could also provide a SessionSettings instance to configure the sessions
    //           (e.g. set the timeout to 600.0 seconds)
    SessionSettings sessionSettings;
    sessionSettings.sessionTimeoutSec = 600.0;

    // now read the node attributes
    vector<Address> addresses;
    addresses.push_back(someDoubleNode);
    addresses.push_back(someUInt32Node);
    addresses.push_back(someStringNode);
    addresses.push_back(someLocalizedTextNode);
    addresses.push_back(someSByteArrayNode);

    vector<Variant> data(5);
    data[0].setDouble(3.14);
    data[1].setUInt32(4);
    data[2].setString("test");
    data[3].setLocalizedText(LocalizedText("en", "Some english text"));

    vector<int8_t> sbyteArray(3);
    sbyteArray[0] = 0x01;
    sbyteArray[1] = 0x02;
    sbyteArray[2] = 0x03;
    data[4].setSByteArray(sbyteArray);

    AsyncWriteResult result;
    Status status = myClient.beginWrite(
            addresses,
            data,
            attributeids::Value,
            constants::CLIENTHANDLE_NOT_ASSIGNED,   // don't specify an existing session, but let the UAF create new sessions (and assign handles to them) or re-use existing ones
            &serviceSettings,
            NULL,                                   // default settings for the Translate service
            &sessionSettings,
            result);

    // wait for the async result
    DateTime::msleep(1000);

    // print the result using the function we defined before
    if (status.isNotGood())
        cout << "Could not write the data: " << status.toString() << "\n";

    // don't worry about disconnecting sessions etc., these things will be done automatically
    // when the client is destroyed.

    return 0;
}
