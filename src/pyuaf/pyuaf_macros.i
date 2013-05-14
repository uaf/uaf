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

#define COPY_NO         100
#define COPY_YES        101
#define TOSTRING_NO     200
#define TOSTRING_YES    201
#define COMP_NO         300
#define COMP_YES        301
#define VECTOR_NO       400
#define VECTOR_YES      401



// =================================================================================================
// MAKE_NON_DYNAMIC(NS, TYPE)
// =================================================================================================
// 
// Make a class non-dynamic (so that you cannot add attributes in certain languages).
//
//   - argument CLASS : the fully qualified class name, e.g. uaf::LocalizedText
//
%define MAKE_NON_DYNAMIC(CLASS)
    #if defined(SWIGPYTHON)
        %feature("python:nondynamic", "1") NS::TYPE;
    #endif
%enddef



// =================================================================================================
// HANDLE_COMPARISON_OPERATORS(NS, TYPE)
// =================================================================================================
// 
// Handle the comparison operators ==, != and <.
//
//   - argument NS   : the namespace of the class, e.g. uaf or uafc
//   - argument TYPE : the type of the class, e.g. LocalizedText
//
// The macro assumes that the C++ class has defined:
//   - operator==
//   - operator!=
//   - operator<
// as friend functions.
//
// It will create the necessary equivalents in the required target language(s).
//
%define HANDLE_COMPARISON_OPERATORS(NS, TYPE)

    %ignore operator==(const TYPE&, const TYPE&);
    %ignore operator!=(const TYPE&, const TYPE&);
    %ignore operator< (const TYPE&, const TYPE&);

    #if defined(SWIGPYTHON)
    
        %extend NS::TYPE {
            bool __eq__(const TYPE& other) const { return (*$self == other);                      }
            bool __ne__(const TYPE& other) const { return (*$self != other);                      }
            bool __lt__(const TYPE& other) const { return (*$self <  other);                      }
            bool __gt__(const TYPE& other) const { return (*$self != other) && !(*$self < other); }
            bool __ge__(const TYPE& other) const { return (*$self == other) || !(*$self < other); }
            bool __le__(const TYPE& other) const { return (*$self == other) ||  (*$self < other); }
        }
        
    #endif

%enddef



// =================================================================================================
// HANDLE_TOSTRING(NS, TYPE, PYTHON_NS)
// =================================================================================================
// 
// Handle the toString() method.
//
//   - argument NS        : the namespace of the class, e.g. uaf or uafc
//   - argument TYPE      : the type of the class, e.g. LocalizedText
//   - argument PYTHON_NS : the namespace for the Python classes, e.g. pyuaf.util
//
// The macro assumes that the C++ class has defined a toString() function.
//
// It will create the necessary equivalents in the required target language(s).
//
%define HANDLE_TOSTRING(NS, TYPE, PYTHON_NS)

    #if defined(SWIGPYTHON)
    
        // rename toString() to __str__()
        %rename(__str__) NS::TYPE::toString const;
        
        // add a __repr__() method based on the toString() output 
        %extend NS::TYPE {
            std::string __repr__() const
            {  
                std::string s("<");
                s += #PYTHON_NS;
                s += ".";
                s += #TYPE;
                s += "(";
                
                std::size_t indent = s.length();
                
                std::stringstream ss($self->toString());
                std::string line;
                
                uint16_t noOfLines = 0;
        
                while ( std::getline(ss, line, '\n') )
                {
                    if (noOfLines > 0)
                    {
                        s += "\n";
                        for(std::size_t i=0; i<indent; i++)
                            s += " ";
                    }
                    s += line;
                    noOfLines++;
                }
                s += std::string(")>");
                return s;
            }
        }
        
    #endif

%enddef



// =================================================================================================
// ADD_COPY_CONSTRUCTOR()
// =================================================================================================
// 
// Add a copy constructor to a wrapped class.
//
%define ADD_COPY_CONSTRUCTOR()
    #if defined(SWIGPYTHON)
        %copyctor TYPE;
    #endif
%enddef




// =================================================================================================
// UAF_WRAP_CLASS(HEADERTOINCLUDE, NS, TYPE, DO_COPY, DO_TOSTRING, DO_COMPARISON, PYTHON_NS, VECTORNAME)
// =================================================================================================
// 
// Wrap a class in a convenient way.
//
//   - argument HEADERTOINCLUDE : the header that contains the class, e.g. "uaf/util/localizedtext.h"
//   - argument NS              : the namespace of the class, e.g. uaf
//   - argument TYPE            : the type of the class, e.g. LocalizedText
//   - argument PYTHON_NS       : the namespace for the Python classes, e.g. pyuaf.util
//   - argument DO_COPY         : COPY_YES to create a copy constructor, COPY_NO to not create one
//   - argument DO_TOSTRING     : TOSTRING_YES to handle the toString() function, TOSTRING_NO to not handle it
//   - argument DO_COMPARISON   : COMP_YES to handle the comparison operators, COMP_NO to not handle them
//   - argument VECTORNAME      : VECTOR_NO to not create a vector for the class, or the name of the vector to create the vector
//
%define UAF_WRAP_CLASS(HEADERTOINCLUDE, NS, TYPE, DO_COPY, DO_TOSTRING, DO_COMPARISON, PYTHON_NS, VECTORNAME)
   
    #if DO_COPY == COPY_YES
        %copyctor TYPE;
    #elif DO_COPY == COPY_NO
        // do nothing
    #else
        #error Only "COPY_YES" or "COPY_NO" are allowed: see line __LINE__!
    #endif
   
    #if DO_TOSTRING == TOSTRING_YES
        HANDLE_TOSTRING(NS, TYPE, PYTHON_NS)
    #elif DO_TOSTRING == TOSTRING_NO
        // do nothing
    #else
        #error Only "TOSTRING_YES" or "TOSTRING_NO" are allowed: see line __LINE__!
    #endif

    #if DO_COMPARISON == COMP_YES
        HANDLE_COMPARISON_OPERATORS(NS, TYPE)
    #elif DO_COMPARISON == COMP_NO
        // do nothing
    #else
        #error Only "COMP_YES" or "COMP_NO" are allowed: see line __LINE__!
    #endif

    %include HEADERTOINCLUDE
   
    #if VECTORNAME == VECTOR_NO
        // do nothing
    #else
        %template(VECTORNAME) std::vector<NS::TYPE>;
    #endif
   
%enddef

