/* This file is part of the UAF (Unified Architecture Framework) project.
 *
 * Copyright (C) 2012 Wim Pessemier (Institute of Astronomy, KULeuven)
 *
 * Project website: http://www.ster.kuleuven.be/uaf
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef UAFC_BASESUBSCRIPTIONRESULT_H_
#define UAFC_BASESUBSCRIPTIONRESULT_H_


// STD
// SDK
// UAF
#include "uaf/util/status.h"
#include "uaf/client/clientexport.h"
#include "uaf/client/results/basesessionresult.h"
#include "uaf/client/results/basesessionresulttarget.h"
#include "uaf/client/results/basesubscriptionresulttarget.h"

namespace uafc
{

    /*******************************************************************************************//**
    * A uafc::BaseSubscriptionResult is the result of a uafc::BaseSubscriptionRequest, i.e. the
    * result of an OPC UA service request that was handled at the Subscription level
    * (and not at the Session level).
    *
    * This is the template class which is implemented by uafc::CreateMonitoredDataResult,
    * uafc::CreateMonitoredEventsResult, ...
    *
    * A result can hold multiple targets, one for each target of the corresponding request.
    *
    * @ingroup ClientResults
    ***********************************************************************************************/
    template<class _Target, bool _Async>
    class UAFC_EXPORT BaseSubscriptionResult : public uafc::BaseSessionResult<_Target, _Async>
    {
    public:


        /**
         * Construct an default result.
         */
        BaseSubscriptionResult()
        : uafc::BaseSessionResult<_Target, _Async>()
        {}


        /**
         * Construct a subscription result with the given status.
         *
         * @param status  Status of the result.
         */
        BaseSubscriptionResult(const uaf::Status& status)
        : uafc::BaseSessionResult<_Target, _Async>(status)
        {}


        // comparison operators
        friend bool operator==(
                const BaseSubscriptionResult<_Target, _Async>& object1,
                const BaseSubscriptionResult<_Target, _Async>& object2)
        {
            return     (uafc::BaseSessionResult<_Target, _Async>&)object1
                    == (uafc::BaseSessionResult<_Target, _Async>&)object2;
        }


        friend bool operator!=(
                const BaseSubscriptionResult<_Target, _Async>& object1,
                const BaseSubscriptionResult<_Target, _Async>& object2)
        {
            return !(object1 == object2);
        }


        friend bool operator<(
                const BaseSubscriptionResult<_Target, _Async>& object1,
                const BaseSubscriptionResult<_Target, _Async>& object2)
        {
            return   (uafc::BaseSessionResult<_Target, _Async>&)object1
                   < (uafc::BaseSessionResult<_Target, _Async>&)object2;
        }
    };




}



#endif /* UAFC_BASESUBSCRIPTIONRESULT_H_ */
