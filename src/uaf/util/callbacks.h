#ifndef UAF_CALLBACKS_H_
#define UAF_CALLBACKS_H_


// STD
//#include <functional>
// SDK
#include "uaf/client/subscriptions/datachangenotification.h"
#include "uaf/client/subscriptions/eventnotification.h"
// UAF


namespace uaf
{

    /**
	 * Callback template.
	 */
    template<class NotificationType> class Callback
    {
    public:
        virtual ~Callback() {}
        virtual void operator() (const NotificationType& notification) = 0;
    };

    typedef Callback<uaf::DataChangeNotification> DataChangeCallback;
    typedef Callback<uaf::EventNotification> EventCallback;


}



#endif /* UAF_CALLBACKS_H_ */
