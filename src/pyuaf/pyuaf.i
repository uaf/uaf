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


// include some standard interface files:
#if defined(SWIGPYTHON)
    %include "python/typemaps.i"
#endif



%include "std_string.i"
%include "std_vector.i"
%include "std_pair.i"
%include "std_map.i"
%include "stdint.i"
%include "std_except.i"



// don't wrap the following methods, since they only make sense for the (internal) C++ UAF code:
%ignore fromSdkToUaf;
%ignore fromUafToSdk;
%ignore fromSdk;
%ignore toSdk;


// import some macros
%import "pyuaf_macros.i"


// typemap for time_t
%typemap(in)  time_t { $1 = (time_t) PyLong_AsLong($input); }
%typemap(out) time_t { $result = PyLong_FromLong((long)$1); }


