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

#include "uaf/client/database/database.h"


namespace uafc
{
    using namespace uaf;
    using namespace uafc;


    // Constructor
    // =============================================================================================
    Database::Database(LoggerFactory* loggerFactory)
    : createMonitoredEventsRequestStore (loggerFactory, "MonEvtsReqStore"),
      createMonitoredDataRequestStore   (loggerFactory, "MonDataReqStore"),
      addressCache                      (loggerFactory),
      nofiticationHandle_(0),
      clientConnectionId_(0),
      clientSubscriptionHandle_(0),
      clientMonitoredItemHandle_(0)
    {}


    // Create a unique NotificationHandle
    // =============================================================================================
    uafc::NotificationHandle Database::createUniqueNotificationHandle()
    {
        UaMutexLocker locker(&notificationHandleMutex_);
        return nofiticationHandle_++;
    }


    // Create a unique clientConnectionId
    // =============================================================================================
    uafc::ClientConnectionId Database::createUniqueClientConnectionId()
    {
        UaMutexLocker locker(&clientConnectionIdMutex_);
        return clientConnectionId_++;
    }


    // Create a unique ClientSubscriptionHandle
    //==============================================================================================
    uafc::ClientSubscriptionHandle Database::createUniqueClientSubscriptionHandle()
    {
        UaMutexLocker locker(&clientSubscriptionHandleMutex_); //auto-unlocks when out of scope
        return clientSubscriptionHandle_++;
    }


    // Create a unique client monitored item handle
    // =============================================================================================
    ClientMonitoredItemHandle Database::createUniqueClientMonitoredItemHandle()
    {
        UaMutexLocker locker(&clientMonitoredItemHandleMutex_);
        return clientMonitoredItemHandle_++;
    }

}






