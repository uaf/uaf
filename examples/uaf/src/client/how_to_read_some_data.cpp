// examples/uaf/src/client/how_to_read_some_data.cpp
/*
 * EXAMPLE: how to read some data
 * =================================================================================================

 * A UAF Client can read data in two ways:
 *   - either using the "convenience" method: read()
 *   - or using the "generic" method: processRequest()
 *
 * The "convenience" methods (such as read(), write(), call(), ...) are conveniently to use
 *  (since they accept the most frequently used parameters directly),
 * but they are less powerful than the "generic" processRequest() method
 *  (since this method accepts ReadRequests, WriteRequests, etc. that can be fully configured).
 *
 * In this example, we will use both ways to read data.
 *
 * To run the example, start the UaServerCPP of UnifiedAutomation first on the same machine.
 */

#include "uaf/client/client.h"

using namespace uaf;
using std::string;
using std::cout;
using std::vector;
using std::size_t;



// define a function to print the readResult (which is of type pyuaf.client.results.ReadResult)
void printResult(const ReadResult& readResult)
{
    // overall result
    cout << "The overall status is: " << readResult.overallStatus.toString() << "\n";

    Status status;
    Variant data;

    // target 0:
    status = readResult.targets[0].status;
    data  = readResult.targets[0].data;
    double value0;
    if (status.isGood() && data.toDouble(value0).isGood())
        cout << "The double is: " << value0 << "\n";

    // target 1:
    status = readResult.targets[1].status;
    data   = readResult.targets[1].data;
    uint32_t value1;
    if (status.isGood() && data.toUInt32(value1).isGood())
        cout << "The uint32 is: " << int(value1) << "\n";

    // target 2:
    status = readResult.targets[2].status;
    data   = readResult.targets[2].data;
    string value2;
    if (status.isGood() && data.toString(value2).isGood())
        cout << "The string is: " << value2 << "\n";

    // target 3:
    status = readResult.targets[3].status;
    data   = readResult.targets[3].data;
    LocalizedText value3;
    if (status.isGood() && data.toLocalizedText(value3).isGood())
        cout << "The locale is: '" << value3.locale() << "', the text is: '" << value3.text() << "'\n";

    // target 4:
    status = readResult.targets[4].status;
    data   = readResult.targets[4].data;
    vector<int8_t> value4;
    if (status.isGood() && data.toSByteArray(value4).isGood())
    {
        cout << "The array is:\n";
        for (size_t i = 0; i < value4.size(); i++)
            cout << " - array[" << int(i) << "] = " << int(value4[i]) << "\n";
    }
}


int main(int argc, char* argv[])
{
    // always initialize the framework first!
    initializeUaf();

    // define the namespace URI and server URI of the UaServerCPP
    string demoNsUri("http://www.unifiedautomation.com/DemoServer");
    string demoServerUri("urn:UnifiedAutomation:UaServerCpp");

    // define some addresses of nodes of which we will read the Value attribute
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
    Client myClient(settings);


    cout << "\n";
    cout << "First option: use the convenience function \"read()\"\n";
    cout << "===================================================\n";

    // OPTIONAL: You could also provide a ReadSettings instance to configure a call timeout,
    //           or maximum age of the values, or ...
    ReadSettings serviceSettings;
    serviceSettings.callTimeoutSec = 0.5;
    serviceSettings.maxAgeSec = 1.0;

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

    ReadResult readResult;
    Status status = myClient.read(
            addresses,
            attributeids::Value,
            constants::CLIENTHANDLE_NOT_ASSIGNED, // don't specify an existing session, but let the UAF create new sessions (and assign handles to them) or re-use existing ones
            NULL,                                      // default settings for the Read service
            NULL,                                      // default settings for the Translate service
            NULL,                                      // default session settings
            readResult);

    // print the result using the function we defined before
    if (status.isGood())
        printResult(readResult);
    else
        cout << "Could not read the data: " << status.toString() << "\n";

    cout << "\n";
    cout << "Second option: use the generic function \"processRequest()\"\n";
    cout << "==========================================================\n";

    // create a request with 5 targets
    ReadRequest readRequest(5);
    readRequest.targets[0].address = someDoubleNode;
    readRequest.targets[1].address = someUInt32Node;
    readRequest.targets[2].address = someStringNode;
    readRequest.targets[3].address = someLocalizedTextNode;
    readRequest.targets[4].address = someSByteArrayNode;

    // we could also add a 6th node, of which we want to read the DisplayName (= of type LocalizedText)
    readRequest.targets.resize(6);
    readRequest.targets[5].address     = someDoubleNode;
    readRequest.targets[5].attributeId = attributeids::DisplayName;

    // the attributeId of the other targets is attributeids::Value by default

    // OPTIONAL: let's also specify a small call timeout, since the UaDemoServer is running
    //           on the local machine anyway
    readRequest.serviceSettings.callTimeoutSec = 0.5;
    // OPTIONAL: let's also specify that the values cannot be older than 1 second
    readRequest.serviceSettings.maxAgeSec = 1.0;
    // OPTIONAL: and finally let's also specify that sessions should have a timeout of 600 seconds
    //           For more info about SessionConfigs, see the sessionconfig_example
    readRequest.sessionSettings.sessionTimeoutSec = 600.0;

    // process the request
    status = myClient.processRequest(readRequest, readResult);

    // print the result
    if (status.isGood())
        printResult(readResult);
    else
        cout << "Could not read the data: " << status.toString() << "\n";

    // also print the display name of the 6th node:
    Status  status5 = readResult.targets[5].status;
    Variant data5   = readResult.targets[5].data;
    LocalizedText value5;
    if (status.isGood() && data5.toLocalizedText(value5).isGood())
        cout << "The DisplayName locale is: '" << value5.locale() << "', the DisplayName text is: '" << value5.text() << "'\n";


    // don't worry about disconnecting sessions etc., these things will be done automatically
    // when the client is destroyed.

    return 0;
}
