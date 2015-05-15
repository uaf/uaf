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

#ifndef UAF_UTIL_H_
#define UAF_UTIL_H_

/**
 *
 * @defgroup Util util
 * The util group bundles all utility code.
 *
 *
 * @namespace uaf
 * uaf contains the common utility code used by the code from other namespaces.
 */



/**
 * @mainpage  UAF - the Unified Architecture Framework
 *
 * <p>
 * The Unified Architecture Framework is an open source software framework to simplify
 * the development of OPC UA applications on Linux or Microsoft Windows, in C++ or Python.
 * </p>
 *
 * <p>
 * Project website: http://github.com/uaf
 * </p>
 *
 * <p>
 * Version: \verbinclude version.txt
 * </p>
 *
 * <p>
 * It is based on the commercial C++ Software Developers Kit from Unified Automation.
 * A demo version of this SDK can be downloaded from their website for free: <br>
 * http://www.unified-automation.com/downloads/opc-ua-development.html
 * </p>
 *
 * <p>
 * A simple example:
 * \include examples/uaf/src/client/easiest_client_example.cpp
 * </p>
 *
 * <p>
 * Additional information can be found in the Related Pages:
 *    - <a href="readme.html">README</a>: General information
 *    - <a href="dependencies.html">Dependencies</a>: dependencies of the framework
 *    - <a href="installation_linux.html">Installation instructions (Linux)</a>:
 *      how to install the framework on Linux
 *    - <a href="installation_windows.html">Installation instructions (Windows)</a>:
 *      how to install the framework on Microsoft Windows
 * </p>
 *
 * <p>
 * Author: Wim Pessemier<br>
 * Organization: <a href="http://www.ster.kuleuven.be">Institute of Astronomy, KULeuven</a><br>
 * </p>
 *
 * <hr>
 *
 * \image html anti_spam_contact.png
 *
 */



// STD
#include <stdint.h>
// SDK
#include "uabase/uaplatformlayer.h"

// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)


// Microsoft Visual Studio needs the following declaration in order to export a .lib file.
// See http://www.cmake.org/Wiki/BuildingWinDLL for more info.
#ifdef _MSC_VER
    #define UAF_EXPORT __declspec(dllexport)
#else
    #define UAF_EXPORT 
#endif



namespace uaf
{

    /** Define the OPC UA StatusCode type (a 32-bit unsigned integer, see Specs Part 4). */
    typedef uint32_t OpcUaStatusCode;

    /**
     * Initialize the framework (must be done before anything else!).
     *
     * @ingroup Util
     *
     * @return  True means initialized, false means that there was a problem
     */
    static bool initializeUaf() { return UaPlatformLayer::init() == 0; }


}

#endif /* UAF_UTIL_H_ */
