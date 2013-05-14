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

#include "uaf/util/helperfunctions.h"

namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;
    using std::transform;
    using std::replace;
    using std::size_t;
    using std::pair;


    // Replace some known keywords
    // =============================================================================================
    string replaceVariables(const string& s)
    {
        string ret = s;

        // declare the first found character
        size_t found;

        // create a lowercase copy of s
        string lowerS = s;
        transform(lowerS.begin(), lowerS.end(), lowerS.begin(), ::tolower);

        // try to replace [hostname]
        found = lowerS.find("[hostname]");
        if(found != string::npos)
            ret.replace(found, string("[hostname]").length(), HOST_NAME);

        // try to replace [applicationpath]
        found = lowerS.find("[applicationpath]");
        if(found != string::npos)
            ret.replace(found, string("[applicationpath]").length(), APPLICATION_PATH);

        return ret;
    }


    // Replace path separators corresponding to the platform
    // =============================================================================================
    string replacePathSeparators(const string& s)
    {
#ifdef _WIN32
        string ret = s;
        replace(ret.begin(), ret.end(), '/', '\\');
        return ret;
#else
        return s;
#endif
    }




    // Get the hostname
    // =============================================================================================
    string getHostName()
    {
        // get the hostname
        char hostName[1024];
        // end with a string termination character
        hostName[1023] = '\0';
        // use the gethostname function defined on Windows and Linux
        ::gethostname(hostName, 1023);
        // return a std::string copy of the buffer
        return string(hostName);
    }


    // Get the application path
    // =============================================================================================
    std::string getApplicationPath()
    {
#ifdef _WIN32
        char buffer[MAX_PATH];
        // in Windows, we can use GetModuleFileName to get the name of the current executable
        GetModuleFileNameA(NULL, buffer, MAX_PATH);
        std::string slash = "\\/";
#else
        char buffer[PATH_MAX];
        // in linux, we can use /proc/self/exe to get the name of the current executable
        ssize_t len = ::readlink("/proc/self/exe", buffer, sizeof(buffer)-1);
        // make sure the buffer is terminated with the string termination character
        buffer[len] = '\0';
        std::string slash = "/";
//        // try to find the last slash, in order to cut off the application name
//        char* slash = ::strrchr(buffer, '/');
//        // if a slash was found, replace the slash with the string termination character
//        if (slash)
//            *slash = '\0';
//        // if a slash was not found, some error occurred, so we create an empty string
//        else
//            buffer[0] = '\0';
//        return string(buffer);
#endif

        // try to find the last-slash, in order to cut off the application name
        std::string::size_type pos = std::string(buffer).find_last_of(slash);
        return std::string(buffer).substr(0, pos);
    }



}
