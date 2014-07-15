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

#include "logger.h"


namespace uaf
{
    using namespace uaf;



    /***********************************************************************************************
     *                                                                                             *
     *                                          LoggerFactory                                      *
     *                                                                                             *
     **********************************************************************************************/


    // Constructor
    // =============================================================================================
    LoggerFactory::LoggerFactory()
    : stdOutLevel_(loglevels::Disabled),
      callbackLevel_(loglevels::Disabled),
      callbackInterface_(0),
      callbackInterfaceRegistered_(false)
    {}


    // Constructor
    // =============================================================================================
    LoggerFactory::LoggerFactory(const std::string& name)
    : name_(name),
      stdOutLevel_(loglevels::Disabled),
      callbackLevel_(loglevels::Disabled),
      callbackInterface_(0),
      callbackInterfaceRegistered_(false)
    {}


    // Destructor
    // =============================================================================================
    LoggerFactory::~LoggerFactory()
    {
        log("LoggerFactory", loglevels::Info, "The logger factory was destructed");
    }


    // Set the log level
    // =============================================================================================
    void LoggerFactory::setStdOutLevel(loglevels::LogLevel level)
    {
        if (level != stdOutLevel_)
        {
            stdOutLevel_ = level;
            log("LoggerFactory", loglevels::Info,
                (std::string("Changing stdout log level to ") + loglevels::toString(level)).c_str());
        }
    }


    // Set the log level
    // =============================================================================================
    void LoggerFactory::setCallbackLevel(loglevels::LogLevel level)
    {
        if (level != callbackLevel_)
        {
            callbackLevel_ = level;
            log("LoggerFactory", loglevels::Info,
                (std::string("Changing callback log level to ") + loglevels::toString(level)).c_str());
        }
    }


    // Log the message
    // =============================================================================================
    void LoggerFactory::log(
            const std::string&  loggerName,
            loglevels::LogLevel level,
            const char*         msg)
    {
        LogMessage message(level, name_, loggerName, msg);

        if (level <= stdOutLevel_)
            logToStdOut(message);

        if (level <= callbackLevel_ && callbackInterfaceRegistered_)
            callbackInterface_->logMessageReceived(message);
    }


    // Format and print the message
    // =============================================================================================
    void LoggerFactory::logToStdOut(const LogMessage& message)
    {
        std::stringstream ss(message.toString());
        std::string line;

        while (std::getline(ss, line, '\n'))
        {
            line += "\n";
            // BUGFIX: never do std::printf(line), because it will try to parse embedded
            // '%' characters as formatting characters, which leads to memory violations!!
            std::printf("%s", line.c_str());
        }
    }


    // Create a logger and return a pointer to it
    // =============================================================================================
    Logger* LoggerFactory::createLogger(const std::string& loggerName)
    {
        Logger* ret = new Logger(this, loggerName);
        return ret;
    }



    /***********************************************************************************************
     *                                                                                             *
     *                                             Logger                                          *
     *                                                                                             *
     **********************************************************************************************/


    // Constructor
    //==============================================================================================
    Logger::Logger(const std::string& loggerName)
    : name_(loggerName)
    {
        // create a new LoggerFactory
        loggerFactory_ = new LoggerFactory(loggerName);
        ownsLoggerFactory_ = true;
    }


    // Constructor
    //==============================================================================================
    Logger::Logger(LoggerFactory *loggerFactory, const std::string& loggerName)
    : name_(loggerName)
    {
        // store a pointer to the loggerFactory
        loggerFactory_ = loggerFactory;
        ownsLoggerFactory_ = false;
    }


    // Constructor
    //==============================================================================================
    Logger::Logger(const std::string& applicationName, const std::string& loggerName)
    : name_(loggerName)
    {
        // create a new LoggerFactory
        loggerFactory_ = new LoggerFactory(applicationName);
        ownsLoggerFactory_ = true;
    }


    // Destructor
    //==============================================================================================
    Logger::~Logger()
    {
        debug("Now destructing the logger");

        if (ownsLoggerFactory_)
        {
            delete loggerFactory_;
            loggerFactory_ = NULL;
        }
    }


    //==============================================================================================
    LoggerFactory * Logger::loggerFactory()
    {
        return loggerFactory_;
    }


    // Log a status object as an error
    //==============================================================================================
    void Logger::error(const Status& status)
    {
        error(status.toString().c_str());
    }


    // Log an error
    //==============================================================================================
    void Logger::error(const char* msg, ...)
    {
        if (loggerFactory_->checkLevel(loglevels::Error))
        {
            va_list args;
            va_start(args, msg);
            char buffer[UAF_LOGGER_MAX_BUFFER_SIZE];
            vsprintf(buffer, msg, args);
            va_end(args);
            loggerFactory_->log(name_, loglevels::Error, buffer);
        }
    }


    // Log an error
    //==============================================================================================
    void Logger::error(const std::string& msg)
    {
        if (loggerFactory_->checkLevel(loglevels::Error))
            loggerFactory_->log(name_, loglevels::Error, msg.c_str());
    }


    // Log a warning
    //==============================================================================================
    void Logger::warning(const char* msg, ...)
    {
        if (loggerFactory_->checkLevel(loglevels::Warning))
        {
            va_list args;
            va_start(args, msg);
            char buffer[UAF_LOGGER_MAX_BUFFER_SIZE];
            vsprintf(buffer, msg, args);
            va_end(args);
            loggerFactory_->log(name_, loglevels::Warning, buffer);
        }
    }


    // Log a warning
    //==============================================================================================
    void Logger::warning(const std::string& msg)
    {
        if (loggerFactory_->checkLevel(loglevels::Warning))
            loggerFactory_->log(name_, loglevels::Warning, msg.c_str());
    }


    // Log an important info message
    //==============================================================================================
    void Logger::info(const char* msg, ...)
    {
        if (loggerFactory_->checkLevel(loglevels::Info))
        {
            va_list args;
            va_start(args, msg);
            char buffer[UAF_LOGGER_MAX_BUFFER_SIZE];
            vsprintf(buffer, msg, args);
            va_end(args);
            loggerFactory_->log(name_, loglevels::Info, buffer);
        }
    }


    // Log an important info message
    //==============================================================================================
    void Logger::info(const std::string& msg)
    {
        if (loggerFactory_->checkLevel(loglevels::Info))
            loggerFactory_->log(name_, loglevels::Info, msg.c_str());
    }


    // Log a debug message
    //==============================================================================================
    void Logger::debug(const char* msg, ...)
    {
        if (loggerFactory_->checkLevel(loglevels::Debug))
        {
            va_list args;
            va_start(args, msg);
            char buffer[UAF_LOGGER_MAX_BUFFER_SIZE];
            vsprintf(buffer, msg, args);
            va_end(args);
            loggerFactory_->log(name_, loglevels::Debug, buffer);
        }
    }


    // Log a debug message
    //==============================================================================================
    void Logger::debug(const std::string& msg)
    {
        if (loggerFactory_->checkLevel(loglevels::Debug))
            loggerFactory_->log(name_, loglevels::Debug, msg.c_str());
    }


}




