// examples/uaf/src/client/how_to_change_the_default_subscription_behavior.cpp
/*
 * EXAMPLE: how to change the default subscription behavior
 * =================================================================================================
 *
 * A SubscriptionConfig instance can be used to configure one or more subscriptions that need to be
 * created, e.g. in order to successfully create some MonitoredItems.
 *
 * This is an example to show you some more advanced feature of the UAF, you can skip it if you're
 * happy with the default subscription behavior of the UAF!
 *
 * As always, in the UAF terminology, a "config" object holds one or more "settings" objects.
 *
 * In this case, a SubscriptionConfig holds
 *  - one SubscriptionSettings object to specify "default" settings for subscriptions that need to
 *    be created
 *  - and optionally some particular SubscriptionSettings objects for subscriptions to particular
 *    servers.
 *
 * Because a SubscriptionConfig can contain settings for many different servers, you can create and
 * configure one SubscriptionConfig, and then re-use this SubscriptionConfig for multiple service
 * calls.
 */

#include "uaf/client/client.h"

using namespace uaf;


int main(int argc, char* argv[])
{
    // always initialize the framework first!
    initializeUaf();

    printf("This example will fail when executed, since it tries to connect to non-existing servers\n");

    // Create a client settings object, to change the default behaviour of the client
    ClientSettings clientSettings;

    // configure the default settings for the sessions that will be created
    clientSettings.defaultSubscriptionSettings.publishingIntervalSec = 1.0;
    clientSettings.defaultSubscriptionSettings.priority = 50;

    // Now we can use the same config for many different service calls.
    // Subscriptions will be created silently in the background by the UAF, based on the
    // settings we provided via the 'subscriptionCfg' object.
    // If subscriptions need to be created to the embedded device or the fast PLC, they will be
    // created according to the specified settings.
    // If subscriptions need to be created to other servers, they will be created according to the
    // defaultSubscriptionSettings settings.

    // First of all, configure a client ...
    ClientSettings clientSettings;
    clientSettings.applicationName = "MyClient";
    clientSettings.discoveryUrls.push_back("opc.tcp://10.133.78.42");
    clientSettings.discoveryUrls.push_back("opc.tcp://10.133.78.81");
    clientSettings.discoveryUrls.push_back("opc.tcp://10.134.25.16");

    // ... and create the client
    Client myClient(clientSettings);

    // define the addresses of some nodes
    Address temperature1(NodeId("temperature1" , "MyCompanyNamespace"), "Some/OPCUA/Server");
    Address temperature2(NodeId("temperature2" , "MyCompanyNamespace"), "Some/OPCUA/Server");
    Address pressure0005(NodeId("pressure0005" , "MyCompanyNamespace"), "My/Slow/Device/Server");
    Address motorStatus3(NodeId("motorStatus3" , "MyCompanyNamespace"), "My/Fast/PLC/Server");
    Address safetyValve5(NodeId("safetyValve5" , "MyCompanyNamespace"), "My/Fast/PLC/Server");

    // now we can monitor any variables or events without worrying about the settings of the subscriptions!

    // monitor the 4 variables
    std::vector<Address> myMonitoredData;
    myMonitoredData.push_back(temperature1);
    myMonitoredData.push_back(temperature2);
    myMonitoredData.push_back(pressure0005);
    myMonitoredData.push_back(motorStatus3);
    CreateMonitoredDataResult myCreateMonitoredDataResult;
    Status status  = myClient.createMonitoredData(myMonitoredData,
                                                  uaf::CreateMonitoredDataConfig(),
                                                  uaf::SessionConfig(),
                                                  subscriptionCfg,
                                                  myCreateMonitoredDataResult);

    std::cout << "Status: " << status.toString() << "\n";

    // monitor the valve object that may send events
    // Note that the previous call already resulted in the creation of a "fast" subscription to
    // our fast PLC server. So in the next call, this subscription will be re-used (so no new
    // subscription will be created).
    std::vector<Address> myMonitoredEvents;
    myMonitoredEvents.push_back(safetyValve5);
    CreateMonitoredEventsResult myCreateMonitoredEventsResult;
    status = myClient.createMonitoredEvents(myMonitoredEvents,
                                            uaf::EventFilter(),                  // default event filter
                                            uaf::CreateMonitoredEventsConfig(), // default service settings
                                            uaf::SessionConfig(),               // default session settings
                                            subscriptionCfg,
                                            myCreateMonitoredEventsResult);

    std::cout << "Status: " << status.toString() << "\n";

    // do some other stuff, each time using the same SubscriptionConfig object ('subscriptionCfg')
    // ...

    // don't worry about disconnecting sessions etc., these things will be done automatically
    // when the client is destroyed.

    return 0;
}
