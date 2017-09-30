// examples/uaf/src/client/how_to_monitor_data.cpp
/*
 * EXAMPLE: how to monitor data
 * =================================================================================================
 *
 * A UAF Client can register callbacks to data change notifications:
 *   - using a callback handler handling all data change notifications
 *   - registering a callback handler for one clientHandle
 *
 * We will try both in this example.
 *
 * To run the example, start the UaDemoServer of UnifiedAutomation first on the same machine.
 */

#include "uaf/client/client.h"
#include "uaf/util/callbacks.h"
#include <iostream>


class DataChanged : public uaf::DataChangeCallback
{
    void operator() (const uaf::DataChangeNotification& notification)
    {
        uaf::Status status = notification.status;
        uaf::Variant data  = notification.data;
        double value0;
        if (status.isGood() && data.toDouble(value0).isGood())
            std::cout << "A double changed to: " << value0 << "\n";
        else
            std::cout << "No good double: " << status.toString() << "\n";
    }
};


class StaticDataChanged : public uaf::DataChangeCallback
{
    void operator() (const uaf::DataChangeNotification& notification)
    {
        uaf::Status status = notification.status;
        uaf::Variant data  = notification.data;
        double value0;
        if (status.isGood() && data.toDouble(value0).isGood())
            std::cout << "The static double changed to: " << value0 << "\n";
        else
            std::cout << "The static double turned bad: " << status.toString() << "\n";
    }
};


class DynamicDataChanged : public uaf::DataChangeCallback
{
    void operator() (const uaf::DataChangeNotification& notification)
    {
        uaf::Status status = notification.status;
        uaf::Variant data  = notification.data;
        double value0;
        if (status.isGood() && data.toDouble(value0).isGood())
            std::cout << "The dynamic double changed to: " << value0 << "\n";
        else
            std::cout << "The dynamic double turned bad: " << status.toString() << "\n";
    }
};


int main(int argc, char* argv[])
{
    // always initialize the framework first!
    uaf::initializeUaf();

    // define the namespace URI and server URI of the UaDemoServer
    std::string demoServerUri("urn:UnifiedAutomation:UaServerCpp");
    std::string demoNsUri("http://www.unifiedautomation.com/DemoServer");

    // define addresses of nodes we want to monitor
    uaf::Address staticDoubleNode(uaf::NodeId("Demo.Static.Scalar.Double" , demoNsUri), demoServerUri);
    uaf::Address dynamicDoubleNode(uaf::NodeId("Demo.Dynamic.Scalar.Double", demoNsUri), demoServerUri);

    // define the ClientSettings:
    uaf::ClientSettings settings;
    settings.applicationName = "MyClient";
    settings.discoveryUrls.push_back("opc.tcp://localhost:48010");
    // settings.logToStdOutLevel = uaf::loglevels::Debug; // uncomment for enabling logging

    // create the client
    uaf::Client myClient(settings);

    // prepare our address vector
    std::vector<uaf::Address> myMonitoredData;
    myMonitoredData.push_back(staticDoubleNode);
    myMonitoredData.push_back(dynamicDoubleNode);

    // create the monitoring
    uaf::CreateMonitoredDataResult myCreateMonitoredDataResult;
    uaf::Status status  = myClient.createMonitoredData(myMonitoredData,
            uaf::constants::CLIENTHANDLE_NOT_ASSIGNED, // don't specify an existing session, but let the UAF create new sessions (and assign handles to them) or re-use existing ones
            NULL,
            NULL,
            NULL,
            uaf::constants::CLIENTHANDLE_NOT_ASSIGNED,
            NULL,
            myCreateMonitoredDataResult);

    std::cout << "CreateMonitoredData Status: " << status.toString() << "\n";

    // register our callbacks
    StaticDataChanged staticDataChanged;
    DynamicDataChanged dynamicDataChanged;
    DataChanged dataChanged;

    myClient.registerDataChangeCallback(myCreateMonitoredDataResult.targets[0].clientHandle, &staticDataChanged);
    myClient.registerDataChangeCallback(myCreateMonitoredDataResult.targets[1].clientHandle, &dynamicDataChanged);
    myClient.registerDataChangeCallback(&dataChanged);

    // wait for some data
    std::cout << "Waiting for notifications. Press Enter to exit.\n";
    std::cin.get();

    // don't worry about disconnecting sessions etc., these things will be done automatically
    // when the client is destroyed.

    return 0;
}
