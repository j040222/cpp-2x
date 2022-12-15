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

#include <cassert>

//
// C++20 provides a new syntax for initializing bitfields
// without using constructors:
//

struct Bitfield0
{
   int
      a_ : 2,
      b_ : 2;
   
   Bitfield0(void)
      :
      a_{ 2 },
      b_{ 3 }
      { }
}
;

struct Bitfield1
{
   //
   // This has the same default values as Bitfield0, without
   // using a constructor:
   //
   
   int
      a_ : 2 { 2 },
      b_ : 2 = 3;
}
;

int main(int argc, char ** argv)
{
   Bitfield0
      first;
   
   Bitfield1
      second;
   
   assert( first.a_ == second.a_ );
   
   assert( first.b_ == second.b_ );
   
   return 0;
}
