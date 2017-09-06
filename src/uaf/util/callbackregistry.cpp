#include "uaf/util/callbackregistry.h"

namespace uaf
{
    using namespace uaf;


    // Constructor
    // =============================================================================================
    template<class NotificationType> CallbackRegistry<NotificationType>::CallbackRegistry()
    {}

    // Register a catchall Callback
    // =============================================================================================
    template<class NotificationType> void CallbackRegistry<NotificationType>::RegisterCallback(uaf::Callback<NotificationType> callback)
    {
        RegisterCallback(uaf::constants::CLIENTHANDLE_NOT_ASSIGNED, callback);
    }

    // Register an associated Callback
    // =============================================================================================
    template<class NotificationType> void CallbackRegistry<NotificationType>::RegisterCallback(uaf::ClientHandle clientHandle, uaf::Callback<NotificationType> callback)
    {
        UaMutexLocker locker(&mapMutex_);
        callbackMap_.emplace(clientHandle, callback);
    }

    // Unregister all Callbacks
    // =============================================================================================
    template<class NotificationType> void CallbackRegistry<NotificationType>::UnregisterAllCallbacks()
    {
        UaMutexLocker locker(&mapMutex_);
        callbackMap_.clear();
    }

    // Unregister all catchall Callbacks
    // =============================================================================================
    template<class NotificationType> void CallbackRegistry<NotificationType>::UnregisterCallbacks()
    {
        UnregisterCallbacks(uaf::constants::CLIENTHANDLE_NOT_ASSIGNED);
    }

    // Unregister all Callbacks for a clientHandle
    // =============================================================================================
    template<class NotificationType> void CallbackRegistry<NotificationType>::UnregisterCallbacks(uaf::ClientHandle clientHandle)
    {
        UaMutexLocker locker(&mapMutex_);
        callbackMap_.erase(clientHandle);
    }

    // Call all Callbacks associated with the clientHandle of notification or
    // with no association.
    // =============================================================================================
    template<class NotificationType> void CallbackRegistry<NotificationType>::CallCallback(NotificationType notification)
    {
        UaMutexLocker locker(&mapMutex_);
        // Calling catchall callbacks
        auto range = callbackMap_.equal_range(uaf::constants::CLIENTHANDLE_NOT_ASSIGNED);
        for (auto i = range.first; i != range.second; ++i)
        {
            i->second(notification);
        }

        // Calling callbacks associated to the clientHandle
        range = callbackMap_.equal_range(notification.clientHandle);
        for (auto i = range.first; i != range.second; ++i)
        {
            i->second(notification);
        }
    }

    template class CallbackRegistry<uaf::DataChangeNotification>;
    template class CallbackRegistry<uaf::EventNotification>;
}
