// examples/uaf/src/client/how_to_read_some_historical_data.cpp
/*
 * EXAMPLE: how to read some historical data
 * =================================================================================================
 *
 * A UAF Client can read historical data in two ways:
 *   - either using the "convenience" methods: historyReadRaw() and historyReadModified()
 *   - or using the "generic" method: processRequest()
 *
 * The "convenience" methods (such as read(), write(), call(), ...) are conveniently to use
 *  (since they accept the most frequently used parameters directly),
 * but they are less powerful than the "generic" processRequest() method
 *  (since this method accepts ReadRequests, WriteRequests, etc. that can be fully configured).
 *
 * In this example, we will use both ways to read historical data.
 *
 * As will be shown in this example, the UAF can automatically take care of subsequent
 * history reading calls, when the first call returned a continuation point (because either the server
 * or the client restricted the number of results that were passed in one OPC UA message).
 * With this "automatic" UAF feature, you don't have to worry about incomplete results anymore!
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
    string demoNsUri("DemoNodeManager");
    string dataNsUri("http://opcfoundation.org/UA/DI/");
    string demoServerUri("urn:UnifiedAutomation:UaDemoserver");

    // define the address of the node that provides the historical data
    Address counterAddress( NodeId("CounterWithHistory", demoNsUri), demoServerUri );
    vector<Address> allAddresses;
    allAddresses.push_back(counterAddress);

    // define the ClientSettings:
    ClientSettings settings;
    settings.applicationName = "MyClient";
    settings.discoveryUrls.push_back("opc.tcp://localhost:4841");

    // create the client
    Client myClient(settings);

    // apparently, the counter of the demo server starts only to keep history after we read it once
    ReadResult initialReadResult;
    uint32_t uint32Value;
    Status status;

    status = myClient.read(allAddresses,
                           attributeids::Value,
                           ReadConfig(),
                           SessionConfig(),
                           initialReadResult);
    if (initialReadResult.overallStatus.isGood())
    {
        initialReadResult.targets[0].data.toUInt32(uint32Value);
        cout << "The counter was read (value: " << int(uint32Value) << ")\n";
    }

    // now wait a bit more than a second, so that we have at least one second of historical data
    DateTime::msleep(1500);

    cout << "\n";
    cout << "First option: use the convenience functions historyReadRaw() and historyReadModified()\n";
    cout << "======================================================================================\n";

    // Read the raw historical data
    //   - that is provided by the counter node,
    //   - that was recorded during the past second
    //   - with a maximum of a 100 returned values
    //     (we expect around 10 values, so 100 is a very safe margin)
    //   - and let the UAF invoke at most 10 "continuation calls"
    //     (we expect that all data can be returned by a single call, so a maximum of 10
    //      additional calls is again a very safe margin)
    HistoryReadRawModifiedResult result;
    DateTime endTime   = DateTime::now();
    DateTime startTime = DateTime(endTime.ctime() - 1.0);

    status = myClient.historyReadRaw(allAddresses,                   // addresses
                                     startTime,                      // startTime
                                     endTime,                        // endTime
                                     100,                            // numValuesPerNode
                                     10,                             // maxAutoReadMore
                                     vector<ByteString>(),           // continuationPoints
                                     HistoryReadRawModifiedConfig(), // serviceConfig
                                     SessionConfig(),                // sessionConfig
                                     result);                        // result

    // print the result:
    cout << "First example:\n";
    cout << "--------------\n";
    cout << result.toString() << "\n";

    // do some processing on the result
    if (result.targets[0].status.isNotGood())
    {
        cout << "Could not read historical data from the counter: ";
        cout << result.targets[0].status.toString() << "\n";
    }
    else
    {
        if (result.targets[0].dataValues.size() == 0)
        {
            // Strange, we didn't receive any historical data.
            // Check if this is expected behavior:
            if (result.targets[0].status.opcUaStatusCode() == OpcUa_GoodNoData)
                cout << "OK, no data could be received because he server reports that there is "
                        "no data that matches your request";
        }
        else
        {
            vector<Status>   allStatuses;
            vector<uint32_t> allIntValues;
            vector<DateTime> allSourceTimes;

            for (vector<DataValue>::const_iterator it = result.targets[0].dataValues.begin();
                 it != result.targets[0].dataValues.end();
                 ++it)
            {
                // check the data type
                if (it->data.type() == opcuatypes::UInt32)
                {
                    allStatuses.push_back(it->status);
                    allSourceTimes.push_back(it->sourceTimestamp);
                    it->data.toUInt32(uint32Value);
                    allIntValues.push_back(uint32Value);
                }
            }

            // now print the lists
            cout << "\n";
            cout << "The results are:\n";

            for (size_t i = 0; i < allStatuses.size(); i++)
            {
                cout << "Code=" << int(allStatuses[i].statusCode());
                cout << " Value=" << int(allIntValues[i]);
                cout << " Time=" << allSourceTimes[i].toTimeString();
                cout << "\n";
            }
        }
    }

    cout << "\n";
    cout << "Second example:\n";
    cout << "---------------\n";
    // Now do the same, but this time get the modifications of the data of the last second.
    // Since we didn't do any modifications, none will be reported!

    status = myClient.historyReadModified(allAddresses,                   // addresses
                                          startTime,                      // startTime
                                          endTime,                        // endTime
                                          100,                            // numValuesPerNode
                                          10,                             // maxAutoReadMore
                                          vector<ByteString>(),           // continuationPoints
                                          HistoryReadRawModifiedConfig(), // serviceConfig
                                          SessionConfig(),                // sessionConfig
                                          result);                        // result

    // print the result:
    cout << result.toString() << "\n";


    cout << "\n";
    cout << "Third example:\n";
    cout << "--------------\n";

    // Now suppose we want to use the continuation points manually,
    // instead of letting the UAF handle them.
    // We therefore put
    //   - numValuesPerNode to a very low value, so that not all results will be retrieved at once
    //   - maxAutoReadMore to 0, so that the UAF may not invoke "continuation request" automatically

    status = myClient.historyReadRaw(allAddresses,                   // addresses
                                     startTime,                      // startTime
                                     endTime,                        // endTime
                                     3,                              // numValuesPerNode
                                     0,                              // maxAutoReadMore
                                     vector<ByteString>(),           // continuationPoints
                                     HistoryReadRawModifiedConfig(), // serviceConfig
                                     SessionConfig(),                // sessionConfig
                                     result);                        // result

    // append all DataValues to the following vector:
    vector<DataValue> allDataValues;

    allDataValues.insert(allDataValues.end(),
                         result.targets[0].dataValues.begin(),
                         result.targets[0].dataValues.end());

    // as long as we get continuation points, we must continue to read the data
    while ( ! result.targets[0].continuationPoint.isNull() )
    {
        vector<ByteString> continuationPoints;
        continuationPoints.push_back(result.targets[0].continuationPoint);

        status = myClient.historyReadRaw(allAddresses,                   // addresses
                                         startTime,                      // startTime
                                         endTime,                        // endTime
                                         3,                              // numValuesPerNode
                                         0,                              // maxAutoReadMore
                                         continuationPoints,             // continuationPoints
                                         HistoryReadRawModifiedConfig(), // serviceConfig
                                         SessionConfig(),                // sessionConfig
                                         result);                        // result


        allDataValues.insert(allDataValues.end(),
                             result.targets[0].dataValues.begin(),
                             result.targets[0].dataValues.end());

    }

    cout << "The following values were received:\n";
    for (vector<DataValue>::const_iterator it = allDataValues.begin(); it != allDataValues.end(); ++it)
        cout << " - " << it->toCompactString() << "\n";



    cout << "\n";
    cout << "Second option: use the generic method processRequest()\n";
    cout << "======================================================\n";


    cout << "\n";
    cout << "Fourth example:\n";
    cout << "---------------\n";

    // create a request with 1 target
    HistoryReadRawModifiedRequest request(1);
    request.targets[0].address = counterAddress;

    // configure the request:
    request.serviceConfig.serviceSettings.startTime                = startTime;
    request.serviceConfig.serviceSettings.endTime                  = endTime;
    request.serviceConfig.serviceSettings.callTimeoutSec           = 2.0;       // optional of course
    request.serviceConfig.serviceSettings.numValuesPerNode         = 100;
    request.serviceConfig.serviceSettings.maxAutoReadMore          = 10;
    request.serviceConfig.serviceSettings.isReadModified           = false;     // we want raw historical data
    request.sessionConfig.defaultSessionSettings.sessionTimeoutSec = 600.0;     // optional of course

    // process the request
    status = myClient.processRequest(request, result);

    // print the result:
    cout << result.toString() << "\n";

    // process the result in the same way as before

    // don't worry about disconnecting sessions etc., these things will be done automatically
    // when the client is destroyed.

    return 0;
}
