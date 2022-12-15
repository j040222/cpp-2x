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
// Prior to C++20, const&-qualified member functions
// could not be used as function pointers on rvalue objects
// (P0704R1):
//

struct A final
{
   void function(void) const &
   {
      ::std::cout << "function" << ::std::endl;
   }
}
;

int main(int argc, char ** argv)
{
   void (A::* pointer) (void) const & = &A::function;
   
   ( ( A {} ).*pointer ) ();
   
   //
   // Technically this was not allowed prior to c++20:
   //
   
   ( ( A {} ).*&A::function ) ();
   
   ( ( A {} ).function() );
   
   return 0;
}
