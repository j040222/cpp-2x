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
// ::std::is_constant_evaluated() was added in C++20. In
// some use cases -but not all- it evaluates to true if the
// enclosing function is constant-evaluated.
//

constexpr
unsigned
function(unsigned argument)
{
   //
   // Note that this should not be:
   //
   //    if constexpr ( ::std::is_constant_evaluated() )
   //
   // because the compiler considers
   // ::std::is_constant_evaluated() to be within the
   // constexpr, so it is always true in the above case.
   // 
   // This also happens if you use is_constant_evaluated
   // in array subscripts, template argument lists and
   // in other contexts, such as static_assert.
   //
   
   if ( ::std::is_constant_evaluated() )
   {
      return
         argument
            ;
   }
   else
   {
      return
         ( argument + 1u );
   }
}

int main(int argc, char ** argv)
{
   constexpr static unsigned
      value0 = function(1);
   
   static const unsigned
      value1 = function(1);
   
   //
   // Initialization of a non-const non-static variable is
   // not constexpr-evaluated:
   //
   
   unsigned
      value2 = function(1);
   
   //
   // Initialization of a const non-static variable is
   // constexpr-evaluated:
   //
   
   unsigned const
      value3 = function(1);
   
   //
   // value2 is not constant evaluated, so neither is
   // value4:
   //
   
   unsigned
      value4 = function(value0);
   
   ::std::cout << value0
               << " "
               << value1
               << " "
               << value2
               << " "
               << value3
               << " "
               << value4
               << ::std::endl
                  ;
   
   return 0;
}
