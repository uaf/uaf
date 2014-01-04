// examples/uaf/src/client/how_to_browse_some_nodes.cpp
/*
 * EXAMPLE: how to browse some nodes
 * =================================================================================================
 *
 * A UAF Client can browse nodes in two ways:
 *   - either using the "convenience" method: browse()
 *   - or using the "generic" method: processRequest()
 *
 * The "convenience" methods (such as read(), write(), call(), ...) are conveniently to use
 *  (since they accept the most frequently used parameters directly),
 * but they are less powerful than the "generic" processRequest() method
 *  (since this method accepts ReadRequests, WriteRequests, etc. that can be fully configured).
 *
 * In this example, we will use both ways to browse nodes.
 *
 * As will be shown in this example, the UAF can automatically take care of BrowseNext calls,
 * so as a user you don't have to worry about incomplete Browse results!
 *
 * To run the example, start the UaDemoServer of UnifiedAutomation first on the same machine.
 */

#include "uaf/client/client.h"

using namespace uaf;
using namespace uafc;
using std::string;
using std::cout;
using std::vector;
using std::size_t;



int main(int argc, char* argv[])
{
    // always initialize the framework first!
    initializeUaf();

    // define the namespace URI and server URI of the UaDemoServer
    string demoServerUri("urn:UnifiedAutomation:UaServerCpp");

    // define the address of the Root node which we would like to start browsing
    Address rootNode( NodeId(OpcUaId_RootFolder, 0), demoServerUri );

    // define the ClientSettings:
    ClientSettings settings;
    settings.applicationName = "MyClient";
    settings.discoveryUrls.push_back("opc.tcp://localhost:48010");

    // create the client
    Client myClient(settings);


    cout << "\n";
    cout << "First option: use the convenience function \"browse()\"\n";
    cout << "====================================================\n";

    // OPTIONAL: You could also provide a BrowseConfig to configure a call timeout
    BrowseConfig serviceConfig;
    serviceConfig.serviceSettings.callTimeoutSec = 0.5;

    // OPTIONAL: And you could also provide a SessionConfig to configure the sessions
    //           (e.g. set the timeout to 600.0 seconds)
    //           For more info about SessionConfigs, see the sessionconfig example
    SessionConfig sessionConfig;
    sessionConfig.defaultSessionSettings.sessionTimeoutSec = 600.0;

    // now browse the root node
    // (notice that there is also an argument called 'maxAutoBrowseNext', which we put at a high
    // value (100), to make sure that BrowseNext is automatically being called for us as much as
    // needed!)
    vector<Address> addresses;
    addresses.push_back(rootNode);

    BrowseResult firstLevelBrowseResult;
    Status status = myClient.browse(addresses, 100, serviceConfig, sessionConfig, firstLevelBrowseResult);

    // print the result
    cout << "\n";
    cout << " - Browse result of the first level:\n";
    cout << "   ---------------------------------\n";
    // print the result
    if (status.isGood())
        cout << firstLevelBrowseResult.toString() << "\n";
    else
        cout << "Could not browse the node: " << status.toString() << "\n";

    // we don't expect that "manual" BrowseNext calls are still needed, as the UAF will
    // have done the BrowseNext calls up to 100 times automatically for us! If there would still be
    // some continuation points left, then we surely have some unexpected problem!
    if (firstLevelBrowseResult.targets[0].continuationPoint.length() > 0)
        cout << "Unexpected error! Still a continuation point left even if the UAF was allowed to "
                "invoke 100 BrowseNext calls!\n";


    // we can now continue browsing the other nodes that we discovered, all simultaneously!!!
    size_t noOfFoundReferences = firstLevelBrowseResult.targets[0].references.size();
    vector<Address> newNodesToBeBrowsed;
    for (size_t i = 0; i < noOfFoundReferences; i++)
        newNodesToBeBrowsed.push_back( Address(firstLevelBrowseResult.targets[0].references[i].nodeId) );

    BrowseResult secondLevelBrowseResult;
    status = myClient.browse(newNodesToBeBrowsed, 100, serviceConfig, sessionConfig, secondLevelBrowseResult);

    // print the result
    cout << "\n";
    cout << " - Browse result of the second level:\n";
    cout << "   ----------------------------------\n";
    // print the result
    if (status.isGood())
        cout << secondLevelBrowseResult.toString() << "\n";
    else
        cout << "Could not browse the nodes: " << status.toString() << "\n";

    cout << "\n";
    cout << "Second option: use the generic function \"processRequest()\"\n";
    cout << "==========================================================\n";

    // create a request with 1 target
    BrowseRequest firstLevelBrowseRequest(1);
    firstLevelBrowseRequest.targets[0].address = rootNode;

    // OPTIONAL: let's also specify a small call timeout, since the UaDemoServer is running
    //           on the local machine anyway
    firstLevelBrowseRequest.serviceConfig.serviceSettings.callTimeoutSec = 2.0;

    // OPTIONAL: and finally let's also specify that sessions should have a timeout of 600 seconds
    //           For more info about SessionConfigs, see the sessionconfig example
    firstLevelBrowseRequest.sessionConfig.defaultSessionSettings.sessionTimeoutSec = 600.0;

    // process the request
    status = myClient.processRequest(firstLevelBrowseRequest, firstLevelBrowseResult);

    // print the result
    cout << "\n";
    cout << " - Browse result of the first level:\n";
    cout << "   ---------------------------------\n";
    // print the result
    if (status.isGood())
        cout << firstLevelBrowseResult.toString() << "\n";
    else
        cout << "Could not browse the node: " << status.toString() << "\n";

    // we don't expect that "manual" BrowseNext calls are still needed, as the UAF will
    // have done the BrowseNext calls up to 100 times automatically for us! If there would still be
    // some continuation points left, then we surely have some unexpected problem!
    if (firstLevelBrowseResult.targets[0].continuationPoint.length() > 0)
        cout << "Unexpected error! Still a continuation point left even if the UAF was allowed to "
                "invoke 100 BrowseNext calls!\n";

    // we can now continue browsing the other nodes that we discovered, all simultaneously!!!
    noOfFoundReferences = firstLevelBrowseResult.targets[0].references.size();
    BrowseRequest secondLevelBrowseRequest(noOfFoundReferences);
    for (size_t i = 0; i < noOfFoundReferences; i++)
        secondLevelBrowseRequest.targets[i].address = Address(firstLevelBrowseResult.targets[0].references[i].nodeId);

    status = myClient.processRequest(secondLevelBrowseRequest, secondLevelBrowseResult);

    // print the result
    cout << "\n";
    cout << " - Browse result of the second level:\n";
    cout << "   ----------------------------------\n";
    // print the result
    if (status.isGood())
        cout << secondLevelBrowseResult.toString() << "\n";
    else
        cout << "Could not browse the nodes: " << status.toString() << "\n";



    // don't worry about disconnecting sessions etc., these things will be done automatically
    // when the client is destroyed.

    return 0;
}
