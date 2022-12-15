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

#include <type_traits>
#include <string>

template
   <
   typename
      T
   >
class Object final
{
public:
   
      //
      // In C++20 constructors can be conditionally
      // explicit:
      //
   
   explicit
      (
      not ::std::is_convertible_v <T, ::std::string>
      )
      Object
         (
         T value
         )
      { }
      ;
}
;

int main(int argc, char ** argv)
{
   {
   
   char
      string[7] = "string";
   
   Object <char [7]>
      object = string
         ;
   
   }
   
   {
   
   Object <::std::string>
      object = ::std::string("string")
         ;
   
   }
   
   {
   
   //
   // Not allowed: int is not convertible to ::std::string,
   // so the constructor is explicit:
   //
   
   //
   // Object
   //   object = 1
   //      ;
   //
   
   Object <int>
      object2( 1 )
         ;
   
   }
   
   return 0;
}
