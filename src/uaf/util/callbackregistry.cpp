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
    template<class NotificationType> void CallbackRegistry<NotificationType>::RegisterCallback(uaf::Callback<NotificationType>* pCallback)
    {
        RegisterCallback(uaf::constants::CLIENTHANDLE_NOT_ASSIGNED, pCallback);
    }

    // Register an associated Callback
    // =============================================================================================
    template<class NotificationType> void CallbackRegistry<NotificationType>::RegisterCallback(uaf::ClientHandle clientHandle, uaf::Callback<NotificationType>* pCallback)
    {
        UaMutexLocker locker(&mapMutex_);
        callbackMap_[clientHandle] = pCallback;
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
    template<class NotificationType> void CallbackRegistry<NotificationType>::CallCallback(const NotificationType& notification)
    {
        UaMutexLocker locker(&mapMutex_);

        typename std::map<uaf::ClientHandle, uaf::Callback<NotificationType>* >::const_iterator iter;

        for (iter = callbackMap_.begin(); iter != callbackMap_.end(); ++iter)
        {
            if (iter->first == uaf::constants::CLIENTHANDLE_NOT_ASSIGNED || iter->first == notification.clientHandle)
            {
                iter->second->operator()(notification);
            }
        }
    }

    template class CallbackRegistry<uaf::DataChangeNotification>;
    template class CallbackRegistry<uaf::EventNotification>;
}
