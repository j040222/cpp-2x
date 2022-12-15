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

#include <memory>

//
// ::std::shared_ptr supports array types as of C++17.
// However, ::std::make_shared did not until C++20.
//

int main(int argc, char ** argv)
{
   //
   // This feature does not yet appear to be implemented
   // in g++-12 -std=c++20:
   //
   
   {
   
   ::std::shared_ptr
      <
      unsigned[][2]
      >
      array =
         ::std::make_shared
            <
            unsigned[][2]
            >
            ()
            ;
   
   }
   
   {
   
   ::std::shared_ptr
      <
      unsigned[3][2]
      >
      array =
         ::std::make_shared
            <
            unsigned[][2]
            >
            (3)
            ;
   
   }
}
