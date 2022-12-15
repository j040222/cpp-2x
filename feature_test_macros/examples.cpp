/*

 This file is part of cpp-2x, a collection of c++20
 examples.
 Copyright (C) 2023

 This program is free software: you can redistribute it and/
 or modify it under the terms of the GNU General Public
 License as published by the Free Software Foundation,
 either version 3 of the License, or (at your option) any
 later version.

 This program is distributed in the hope that it will be
 useful, but WITHOUT ANY WARRANTY; without even the implied
 warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 PURPOSE. See the GNU General Public License for more
 details.

 You should have received a copy of the GNU General Public
 License along with this program.  If not, see
 <https://www.gnu.org/licenses/>.
 
 */

#include <iostream>

//
// C++20 added many macros that test for C++20 features.
// 
// If a macro is defined, eg. __cpp_using_enum, then its
// value represents the year and month that the attribute/
// feature was added to the working draft. If the value is
// 0 then the compiler (or the compiler and the C++ version
// it is compiling for) does not support the attribute/
// feature.
//

int main(int argc, char ** argv)
{
   //
   // Language and library features are generally tested
   // using macros prefixed with __cpp and __cpp_lib,
   // respectively:
   //
   
   ::std::cout << __cpp_using_enum << ::std::endl;
   
   //
   // Attributes are tested using __has_cpp_attribute,
   // which can itself be tested as a macro:
   //
   
#ifdef __has_cpp_attribute
   ::std::cout << __has_cpp_attribute(maybe_unused)
               << ::std::endl
                  ;
#endif
   
   return 0;
}
