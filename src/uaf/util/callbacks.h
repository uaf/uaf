#ifndef UAF_CALLBACKS_H_
#define UAF_CALLBACKS_H_


// STD
#include <functional>
// SDK
// UAF


namespace uaf
{

    /**
	 * Callback template.
	 */
    template<class NotificationType> using Callback = std::function<void(NotificationType)>;

}



#endif /* UAF_CALLBACKS_H_ */
