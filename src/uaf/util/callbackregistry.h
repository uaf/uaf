#ifndef UAF_CALLBACKREGISTRY_H_
#define UAF_CALLBACKREGISTRY_H_


// STD
#include <map>
#include <string>
#include <sstream>
// SDK
#include "uabase/uamutex.h"
// UAF
#include "uaf/util/logger.h"
#include "uaf/util/stringifiable.h"
#include "uaf/util/handles.h"
#include "uaf/util/constants.h"
#include "uaf/util/callbacks.h"
#include "uaf/client/subscriptions/datachangenotification.h"
#include "uaf/client/subscriptions/eventnotification.h"


namespace uaf
{


    /*******************************************************************************************//**
    * A uaf::CallbackRegistry is a registry for notification callbacks.
    *
    * @ingroup Util
    ***********************************************************************************************/
    template<class NotificationType> class UAF_EXPORT CallbackRegistry
    {
    public:

        /**
         * Construct a callback registry.
         */
        CallbackRegistry();

        /**
         * Register a callback for all notifications.
         */
        void RegisterCallback(uaf::Callback<NotificationType> callback);

        /**
         * Register a callback for a notification identified by clientHandle.
         */
        void RegisterCallback(uaf::ClientHandle clientHandle, uaf::Callback<NotificationType> callback);

        /**
         * Unregister all callbacks.
         */
        void UnregisterAllCallbacks();

        /**
         * Unregister all callbacks that are registered for all notifications.
         */
        void UnregisterCallbacks();

        /**
         * Unregister all callbacks for a notification identified by clientHandle.
         */
        void UnregisterCallbacks(uaf::ClientHandle clientHandle);

        /**
         * Emit a notification to registered callbacks.
         */
        void CallCallback(NotificationType notification);

    private:
        std::multimap<uaf::ClientHandle, uaf::Callback<NotificationType>> callbackMap_;

        UaMutex mapMutex_;
    };


}




#endif /* UAF_CALLBACKREGISTRY_H_ */
