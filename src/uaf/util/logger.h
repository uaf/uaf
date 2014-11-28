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

#ifndef UAF_LOGGER_H_
#define UAF_LOGGER_H_


#define UAF_LOGGER_MAX_BUFFER_SIZE 4096


// STD
#include <sstream>
#include <string>
#include <stdio.h>
#include <cstdio>
#include <stdarg.h>

// SDK
// UAF
#include "uaf/util/util.h"
#include "uaf/util/loglevels.h"
#include "uaf/util/status.h"
#include "uaf/util/sdkstatus.h"
#include "uaf/util/logmessage.h"
#include "uaf/util/logginginterface.h"

namespace uaf
{


    /**
     * Get the current time formatted as "YYYY-MM-DD hh:mm:ss.sss".
     *
     * @return string formatted as "YYYY-MM-DD hh:mm:ss.sss"
     */
    std::string UAF_EXPORT NowTime();


    // forward declaration of the Logger class
    class Logger;


    /*******************************************************************************************//**
     * A LoggerFactory allows Loggers to send log messages to stdout, or a file, or the network if
     * implemented...
     *
     * @ingroup util
     **********************************************************************************************/
    class UAF_EXPORT LoggerFactory
    {
    public:

        /**
         * Construct a nameless LoggerFactory.
         */
        LoggerFactory();


        /**
         * Construct a LoggerFactory with a specified name.
         *
         * @param name   Name of the logger factory.
         */
        LoggerFactory(const std::string& name);


        /**
         * Destruct the LoggerFactory.
         */
        ~LoggerFactory();


        /**
         * Format and send the final message to the std::out.
         *
         * @param loggerName    The name of the logger.
         * @param level         The loglevel.
         * @param msg           The message.
         */
        void log(
                const std::string&          loggerName,
                uaf::loglevels::LogLevel    level,
                const char*                 msg);


        /**
         * Check if a message with the given level will either be logged to the stdout or the
         * callback interface;
         */
        bool checkLevel(uaf::loglevels::LogLevel level)
        {
            return     (level <= stdOutLevel_)
                    || (level <= callbackLevel_ && callbackInterfaceRegistered_);
        }


        /**
         * Register a logger interface for callbacks.
         */
        void registerCallbackInterface(uaf::LoggingInterface* callbackInterface)
        {
            callbackInterface_ = callbackInterface;
            callbackInterfaceRegistered_ = true;
        }

        /**
         * Unregister a logger interface for callbacks.
         */
        void unregisterCallbackInterface()
        {
            callbackInterface_ = 0;
            callbackInterfaceRegistered_ = false;
        }


        /**
         * Format and send the final message to the stream(s).
         *
         * @param message   The log message.
         */
        void logToStdOut(const uaf::LogMessage& message);


        /**
         * Set the minimum level which should be logged to the stdout.
         *
         * @param level         Minimum loglevel.
         */
        void setStdOutLevel(uaf::loglevels::LogLevel level);


        /**
         * Set the minimum level which should be logged to the callback.
         *
         * @param level         Minimum loglevel.
         */
        void setCallbackLevel(uaf::loglevels::LogLevel level);


        /**
         * Get the minimum level which should be logged to the stdout.
         *
         * @return  Current minimum loglevel.
         */
        uaf::loglevels::LogLevel stdOutLevel() const { return stdOutLevel_; }


        /**
         * Get the minimum level which should be logged to the callback interface.
         *
         * @return  Current minimum loglevel.
         */
        uaf::loglevels::LogLevel callbackLevel() const { return callbackLevel_; }


        /**
         * Factory to create loggers. Destruction of these Loggers is the responsibility of the
         * caller!
         *
         * @param loggerName    Name of the created Logger.
         * @return              Pointer to the created Logger.
         */
        Logger * createLogger(const std::string& loggerName);

    private:
        DISALLOW_COPY_AND_ASSIGN(LoggerFactory);

        // name of the logger factory
        std::string name_;

        /** When logging to the stdout, only log messages from at least this loglevel. */
        uaf::loglevels::LogLevel stdOutLevel_;

        /** When logging to the callback interface, only log messages from at least this loglevel.*/
        uaf::loglevels::LogLevel callbackLevel_;

        uaf::LoggingInterface* callbackInterface_;

        bool callbackInterfaceRegistered_;
    };


    /**
     * A Logger logs messages of various severities via a (shared) LoggerFactory instance.
     *
     * @ingroup util
     */
    class UAF_EXPORT Logger
    {
    public:
        /**
         * Construct a new Logger with a new LoggerFactory (having the same name as the logger).
         *
         * The logger will own the loggerFactory, so destructing the logger will destruct the
         * loggerFactory.
         *
         * @param loggerName    Name of the logger.
         */
        Logger(const std::string& loggerName);


        /**
         * Construct a new Logger with a new LoggerFactory (with a given name).
         *
         * The logger will own the loggerFactory, so destructing the logger will destruct the
         * loggerFactory.
         *
         * @param loggerName        Name of the logger.
         * @param applicationName   Name of the application.
         */
        Logger(const std::string& applicationName, const std::string& loggerName);


        /**
         * Construct a new Logger and attach it to an existing LoggerFactory.
         *
         * The logger will NOT own the loggerFactory, so destructing the logger will NOT destruct
         * the loggerFactory.
         *
         * @param loggerFactory     Pointer to the existing LoggerFactory.
         * @param loggerName        Name of the logger.
         */
        Logger(LoggerFactory *loggerFactory, const std::string& loggerName);


        /**
         * Get a pointer to the loggerFactory.
         *
         * Depending on how the Logger was constructed, this loggerFactory may be owned by the
         * logger itself, or not!
         *
         * @return Pointer to the LoggerFactory used by this Logger instance.
         */
        LoggerFactory* loggerFactory();


        /**
         * Destructor.
         *
         * Depending on how the Logger was constructed, destructing the logger may destruct the
         * associated loggerFactory, or not!
         */
        ~Logger();


        /**
         * Log the SDK status (Debug if Good, Warning if Uncertain, Error if Bad).
         */
        void log(const uaf::SdkStatus& sdkStatus);


        /**
         * Log a status object as an error.
         *
         * @param status    The status to print its message.
         * @return          The formatted message.
         */
        void error(const uaf::Status& status);


        /**
         * Log an error and return the formatted message.
         *
         * @param msg       The message, including string formatting tags such as %s, %d, etc.
         * @param ...       The values corresponding with the formatting tags.
         */
        void error(const char * msg, ...);

        /**
         * Log an error.
         *
         * @param msg       The message.
         */
        void error(const std::string& msg);


        /**
         * Log a warning.
         *
         * @param msg       The message, including string formatting tags such as %s, %d, etc.
         * @param ...       The values corresponding with the formatting tags.
         */
        void warning(const char * msg, ...);

        /**
         * Log a warning.
         *
         * @param msg       The message.
         */
        void warning(const std::string& msg);


        /**
         * Log important info.
         *
         * @param msg       The message, including string formatting tags such as %s, %d, etc.
         * @param ...       The values corresponding with the formatting tags.
         */
        void info(const char * msg, ...);

        /**
         * Log important info.
         *
         * @param msg       The message.
         */
        void info(const std::string& msg);


        /**
         * Log a debug message.
         *
         * @param msg       The message, including string formatting tags such as %s, %d, etc.
         * @param ...       The values corresponding with the formatting tags.
         */
        void debug(const char * msg, ...);


        /**
         * Log a debug message.
         *
         * @param msg       The message.
         */
        void debug(const std::string& msg);


    private:
        DISALLOW_COPY_AND_ASSIGN(Logger);

        // name of the logger
        std::string     name_;
        // pointer to the logger factory
        LoggerFactory*  loggerFactory_;
        // True if the logger factory is owned by the logger, False if not
        bool            ownsLoggerFactory_;

    };


}

#endif /* UAF_LOGGER_H_ */
