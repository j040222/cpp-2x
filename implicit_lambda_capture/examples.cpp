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
#include <memory>

//
// In C++20, lambda functions can now be used in default-
// initialized class members. Note that some compilers would
// accept this in c++17:
//

struct A
{
   int
      x{1};
   
   int
      y = [this] { return (x + 1); } ();
}
;

int main(int argc, char ** argv)
{
   A
      object;
   
   ::std::cout << object.y << ::std::endl;
   
   
   {
   
   auto
      p = ::std::make_unique <unsigned> ();
   
   auto
      lamda =
         [=] (void)
         {
            //
            // p is captured in this context despite
            // the constexpr and the typeid. sizeof(p),
            // however, doesn't capture p.
            //
         
            if constexpr (false)
            {
               typeid( p );
            }
         }
         ;
   
   lamda();
   
   }
   
   return 0;
}
