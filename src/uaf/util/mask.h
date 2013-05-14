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

#ifndef UAF_MASK_H_
#define UAF_MASK_H_

// STD
#include <deque>
#include <algorithm>
#include <string>
#include <sstream>
// SDK
// UAF
#include "uaf/util/util.h"

namespace uaf
{


    /**
     * A boolean mask.
     *
     * The mask keeps track of the number of 'set' (boolean true) and 'unset' (boolean false)
     * values. This means you can very efficiently call countSet() and countUnset().
     *
     * @ingroup Util
     */
    class UAF_EXPORT Mask
    {
    public:


        /**
         * Create a new empty mask.
         */
        Mask()
        : noOfTrue(0)
        {}


        /**
         * Create a new mask with the given initial size, each item of the mask being 'false'.
         */
        Mask(std::size_t initialSize)
        : deq_(initialSize, false),
          noOfTrue(0)
        {}


        /**
         * Create a new mask with the given initial size, each item having the given initial value.
         *
         * @param initialSize   Initial size of the mask.
         * @param initialValue  Initial value of the items of the mask ('set'=true or 'unset'=false).
         */
        Mask(std::size_t initialSize, bool initialValue)
        : deq_(initialSize, initialValue)
        {
              if (initialValue)
                  noOfTrue = initialSize;
              else
                  noOfTrue = 0;
        }


        /**
         * Resize the mask.
         *
         * If the mask grows bigger, the newly appended mask items will be 'unset' (false).
         *
         * @param n The new size of the mask.
         */
        void resize(std::size_t n)
        {
            bool setCountMayChange = (n < deq_.size());
            deq_.resize(n, false);
            if (setCountMayChange)
                noOfTrue = std::count(deq_.begin(), deq_.end(), true);
        }


        /**
         * Get the size of the mask.
         *
         * @return The actual number of items of the mask.
         */
        std::size_t size() const { return deq_.size(); }


        /**
         * Get the number of 'set' (true) items.
         *
         * @return The actual number of 'set' items of the mask.
         */
        std::size_t setCount()   const { return noOfTrue;             }


        /**
         * Get the number of 'unset' (false) items.
         *
         * @return The actual number of 'unset' items of the mask.
         */
        std::size_t unsetCount() const { return size() - setCount();  }


        /**
         * Is an item 'set' (true)?
         *
         * @param i The index of the item.
         * @return  True if the item is 'set' (true), false if not.
         */
        bool isSet(std::size_t i)   const   { return deq_[i]; }


        /**
         * Is an item 'unset' (false)?
         *
         * @param i The index of the item.
         * @return  True if the item is 'unset' (false), false if not.
         */
        bool isUnset(std::size_t i) const   { return !deq_[i]; }


        /**
         * 'Set' an item (meaning: make it true).
         *
         * @param i The index of the item.
         */
        void set(std::size_t i)
        {
            if (i >= deq_.size())
            {
                resize(i+1);
                set(i);
            }
            else
            {
                if (isUnset(i))
                {
                    deq_[i] = 1;
                    noOfTrue++;
                }
            }
        }


        /**
         * 'Unset' an item (meaning: make it false).
         *
         * @param i The index of the item.
         */
        void unset(std::size_t i)
        {
            if (i >= deq_.size())
            {
                resize(i+1);
                unset(i);
            }
            else
            {
                if (isSet(i))
                {
                    deq_[i] = 0;
                    noOfTrue--;
                }
            }
        }


        /**
         * Get a string representation of the mask.
         *
         * @return The string representation, e.g. "01" for a mask with two items
         *         (the first one being false, so-called "unset",
         *         the second one being true, so-called "set").
         */
        std::string toString() const
        {
            std::stringstream ss;
            ss << "[";
            for (std::deque<bool>::const_iterator it = deq_.begin(); it != deq_.end(); ++it)
                ss << *it;
            ss << "]";
            return ss.str();
        }


        /**
         * Perform a logical AND between this mask and the other.
         *
         * @param other Other mask.
         * @return      Resulting mask = (this mask) AND (other mask).
         */
        Mask operator&& (const Mask& other) const
        {
            // we don't use std::min because it interferes with the 'min' macro in <windows.h>
            std::size_t minSize;
            if (size() < other.size())
                minSize = size();
            else
                minSize = other.size();

            Mask ret(minSize);

            for(std::size_t i = 0; i < minSize; i++)
                ret.deq_[i] = deq_[i] && other.deq_[i];

            return ret;
        }

        // comparison operators
        friend UAF_EXPORT bool operator==(const Mask& object1, const Mask& object2)
        { return object1.deq_ == object2.deq_; }

        friend UAF_EXPORT bool operator!=(const Mask& object1, const Mask& object2)
        { return !(object1 == object2);}

        friend UAF_EXPORT bool operator<(const Mask& object1, const Mask& object2)
        { return object1.deq_ < object2.deq_; }


    private:

        /** The number of 'set' (true) items. */
        std::size_t noOfTrue;

        /** The deque to store the boolean mask items. */
        std::deque<bool> deq_;

    };

}


#endif /* UAF_MASK_H_ */
