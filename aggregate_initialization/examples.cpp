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
// In C++20, aggregate class types cannot have user-declared
// constructors. This includes:
//
//    1     User-deleted constructors,
//    2     constructors that are declared "default",
//    3     any user-provided constructor.
//
// In particular, none of these classes are aggregates
// in c++20:
//

struct A1
{
   unsigned
      value[2];
   
   A1(void) = delete;
}
;

struct A2
{
   unsigned
      value[2];
   
   A2(void) = default;
}
;

//
// This is also not an aggregate in C++17:
//

struct A3
{
   unsigned
      value[2];
   
   A3(void) { }
}
;

int main(int argc, char ** argv)
{
   //
   // In C++20, aggregate initialization is not allowed for
   // any of the above types. In C++17, aggregate
   // initialization was allowed for the first two.
   //
   
   {
   
   A1 const
      a1{ 1u, 2u };                       // C++20 error
   
   }
   
   {
   
   A2 const
      a2{ 1u, 2u };                       // C++20 error
   
   }
   
   return 0;
}
