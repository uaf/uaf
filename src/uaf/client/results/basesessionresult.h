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

#ifndef UAFC_BASESESSIONRESULT_H_
#define UAFC_BASESESSIONRESULT_H_


// STD
#include <vector>
#include <string>
#include <sstream>
// SDK
// UAF
#include "uaf/util/status.h"
#include "uaf/util/mask.h"
#include "uaf/util/stringifiable.h"
#include "uaf/client/clientexport.h"
#include "uaf/client/clienthandles.h"
#include "uaf/client/results/basesessionresulttarget.h"

namespace uafc
{



    /*******************************************************************************************//**
    * A uafc::BaseSessionResult is the result of a uafc::BaseSessionRequest, i.e. the result of an
    * OPC UA service request that was handled at the Session level (and not at the Subscription
    * level).
    *
    * This is the template class which is implemented by uafc::ReadResult, uafc::WriteResult,
    * uafc::MethodCallResult, ...
    *
    * A result can hold multiple targets, one for each target of the corresponding request.
    *
    * @ingroup ClientResults
    ***********************************************************************************************/
    template<class _Target, bool _Async>
    class UAFC_EXPORT BaseSessionResult : public uaf::Stringifiable
    {
    public:

        /**
         * Construct an empty result.
         */
        BaseSessionResult()
        : requestHandle(0)
        {}


        /**
         * Construct a session result with the given status.
         *
         * @param status  Status of the result.
         */
        BaseSessionResult(const uaf::Status& status)
        : requestHandle(0),
          overallStatus(status)
        {}


        /** Public typedef for the type of the target (e.g. ReadResultTarget). */
        typedef _Target TargetType;

        /** The UAF handle assigned to the result (and its corresponding request). */
        uafc::RequestHandle requestHandle;

        /**
         * The overall status of the result.
         *
         * If this Status is Good, then you don't have to check the statuses of the individual
         * targets, because they're all Good. If this Status is Bad, then at least one of the
         * targets has a Bad status.
         */
        uaf::Status overallStatus;

        /** The targets. */
        typename std::vector<_Target> targets;


        /**
         * Get a string representation of the target.
         *
         * @return  String representation.
         */
        virtual std::string toString(const std::string& indent="", std::size_t colon=32) const;


        // comparison operators
        template<class R, bool A>
        friend bool operator==(
                const BaseSessionResult<R, A>& object1,
                const BaseSessionResult<R, A>& object2);

        template<class R, bool A>
        friend bool operator!=(
                const BaseSessionResult<R, A>& object1,
                const BaseSessionResult<R, A>& object2);

        template<class R, bool A>
        friend bool operator<(
                const BaseSessionResult<R, A>& object1,
                const BaseSessionResult<R, A>& object2);



    private:


        // befriend the Client and Resolver classes so they can call the private methods below
        friend class Client;
        friend class Resolver;


        /**
         * Get a mask indicating those targets with a Good status.
         *
         * @return The mask, size() of which equals the number of targets, setCount() of which
         *         equals the amount of "good" targets.
         */
        uaf::Mask getGoodTargetsMask() const;


        /**
         * Get a mask indicating those targets with a Bad status.
         *
         * @return The mask, size() of which equals the number of targets, setCount() of which
         *         equals the amount of "bad" targets.
         */
        uaf::Mask getBadTargetsMask() const;


        /**
         * Set the status of all targets indicated by the mask, to the given commonStatus.
         *
         * @param commonStatus  The status which should be given to each indicated target.
         * @param mask          The mask indicating (with mask[i] = true) the targets that need
         *                      their status to be changed.
         * @return              Good if the statuses could be set, Unexpected error if the input
         *                      parameters did not make sense.
         */
        uaf::Status setStatuses(const uaf::Status& commonStatus, const uaf::Mask& mask);


        /**
         * Set the status of all targets indicated by the mask, to the given statuses.
         *
         * The vector should contain as many statuses, as there are mask items that are set "true"
         * (so mask.setCount() must be equal to statuses.size(), and statuses[i] may correspond with
         * mask[j]).
         *
         * @param statuses  The statuses that need to be copied to the statuses of the targets
         *                  indicated by the mask.
         * @param mask      The mask indicating (with mask[i] = true) the targets that need
         *                  their status to be changed.
         * @return          Good if the statuses could be set, Unexpected error if the input
         *                  parameters did not make sense.
         */
        uaf::Status setStatuses(const std::vector<uaf::Status>& statuses, const uaf::Mask& mask);


        /**
         * Update the overall status by summarizing the target statuses.
         */
        void updateOverallStatus();

    };



    // Update the overall status
    // =============================================================================================
    template<class _Target, bool _Async>
    void BaseSessionResult<_Target, _Async>::updateOverallStatus()
    {
        // if the overall status is already erroneous, don't overwrite it
        if (overallStatus.isNotBad())
        {
            if (targets.size() == 0)
                overallStatus.setStatus(uaf::statuscodes::InvalidRequestError, "No targets given");
            else
            {
                std::vector<uaf::Status> statuses;
                statuses.reserve(targets.size());
                for (typename std::vector<_Target>::const_iterator it = targets.begin();
                     it != targets.end();
                     ++it)
                {
                    statuses.push_back(it->status);
                }

                overallStatus.summarize(statuses);
            }
        }
    }


    // Get a string representation
    // =============================================================================================
    template<class _Target, bool _Async>
    std::string BaseSessionResult<_Target, _Async>::toString(
            const std::string&  indent,
            std::size_t         colon) const
    {
        std::stringstream ss;

        ss << indent << " - overallStatus";
        ss << uaf::fillToPos(ss, colon);
        ss << ": " << overallStatus.toString() << "\n";

        ss << indent << " - requestHandle";
        ss << uaf::fillToPos(ss, colon);
        ss << ": " << requestHandle << "\n";

        ss << indent << " - targets[]\n";
        for (std::size_t i = 0; i < targets.size(); i++)
        {
            ss << indent << "    - targets[" << i << "]";

            // append the target description in a nice way (both for single and multi line strings)
            if (uaf::isMultiLine(targets[i].toString()))
            {
                ss << "\n";
                ss << targets[i].toString(indent + "      ", colon);
            }
            else
            {
                ss << uaf::fillToPos(ss, colon);
                ss << ": " << targets[i].toString();
            }
            // don't add a newline character to the last target:
            if (i < targets.size() - 1)
                ss << "\n";
        }

        return ss.str();
    }



    // operator==
    // =============================================================================================
    template<class R, bool A>
    bool operator==(
            const BaseSessionResult<R, A>& object1,
            const BaseSessionResult<R, A>& object2)
    {
        if (object1.targets.size() != object2.targets.size())
            return false;

        for (std::size_t i = 0; i < object1.targets.size(); i++)
            if (object1.targets[i] != object2.targets[i])
                return false;

        if (object1.status != object2.status)
            return false;

        return true;
    }



    // operator!=
    // =============================================================================================
    template<class R, bool A>
    bool operator!=(
            const BaseSessionResult<R, A>& object1,
            const BaseSessionResult<R, A>& object2)
    {
        return !(object1 == object2);
    }



    // operator!=
    // =============================================================================================
    template<class R, bool A>
    bool operator<(
            const BaseSessionResult<R, A>& object1,
            const BaseSessionResult<R, A>& object2)
    {
        if (object1.targets.size() != object2.targets.size())
            return object1.targets.size() < object2.targets.size();

        for (std::size_t i = 0; i < object1.targets.size(); i++)
            if (object1.targets[i] != object2.targets[i])
                return object1.targets[i] < object2.targets[i];

        if (object1.status != object2.status)
            return object1.status < object2.status;

        return false;
    }


    // Get a mask of the good targets
    // =============================================================================================
    template<class _Target, bool _Async>
    uaf::Mask BaseSessionResult<_Target, _Async>::getGoodTargetsMask() const
    {
        uaf::Mask mask(targets.size(), false);

        for (std::size_t i = 0; i < targets.size(); i++)
            if (targets[i].status.isGood())
                mask.set(i);

        return mask;
    }

    // Get a mask of the bad targets
    // =============================================================================================
    template<class _Target, bool _Async>
    uaf::Mask BaseSessionResult<_Target, _Async>::getBadTargetsMask() const
    {
        uaf::Mask mask(targets.size(), false);

        for (std::size_t i = 0; i < targets.size(); i++)
            if (targets[i].status.isNotGood())
                mask.set(i);

        return mask;
    }


    // Set the statuses of the targets
    // =============================================================================================
    template<class _Target, bool _Async>
    uaf::Status BaseSessionResult<_Target, _Async>::setStatuses(
            const uaf::Status& commonStatus,
            const uaf::Mask&   mask)
    {
        // declare the return Status
        uaf::Status ret;

        // declare the number of targets
        std::size_t noOfTargets = targets.size();

        // check the input arguments
        if (noOfTargets == mask.size())
            ret.setGood();
        else
            ret.setStatus(uaf::statuscodes::UnexpectedError,
                          "Mask size does not match number of targets");

        // if everything is OK, loop through the statuses and update the 'set' targets
        if (ret.isGood())
        {
            for (std::size_t i = 0; i < noOfTargets; i++)
            {
                if (mask.isSet(i))
                {
                    targets[i].status = commonStatus;
                }
            }
        }

        return ret;
    }


    // Set the statuses of the targets
    // =============================================================================================
    template<class _Target, bool _Async>
    uaf::Status BaseSessionResult<_Target, _Async>::setStatuses(
            const std::vector<uaf::Status>& statuses,
            const uaf::Mask&                mask)
    {
        // declare the return Status
        uaf::Status ret;

        // declare the number of targets
        std::size_t noOfTargets = targets.size();

        // check the input parameters
        if (mask.setCount() != statuses.size())
        {
            ret.setStatus(uaf::statuscodes::UnexpectedError,
                          "Mask does not match statuses");
        }
        // check if the mask corresponds to the number of targets
        else if (mask.size() != noOfTargets)
        {
            ret.setStatus(uaf::statuscodes::UnexpectedError,
                          "Mask size does not match number of targets");
        }
        // if everything is OK, loop through the statuses and update the 'set' targets
        else
        {
            for (std::size_t i = 0, j = 0; i < noOfTargets; i++)
            {
                if (mask.isSet(i))
                {
                    targets[i].status = statuses[j];
                    j++;
                }
            }
            ret.setGood();
        }

        return ret;
    }
}



#endif /* UAFC_SESSIONRESULT_H_ */
