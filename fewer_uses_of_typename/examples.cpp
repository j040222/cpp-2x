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

#include <string>

//
// In C++20 the keyword 'typename' is no longer required
// in many cases, including:
//

//
// When defaulting a template parameter, and in the return
// type of a function declaration or definition:
//

struct U
{
   static constexpr int name = 1;
   
   typedef int type;
}
;

template
   <
   typename V = U::type
   >
U::type
function
   (
   U::type
      argument = U::name
   )
{
   return argument;
}

//
// In class scoped function definitions and class-scoped
// typedefs:
//

struct S
{
   U::type function(U::type = U::name)
   {
      return U::name;
   }
   
   U::type object;
   
   typedef U::type type;
}
;

int main(int argc, char ** argv)
{
   function<> (1);
   
   //
   // In static_cast <>, and similar (eg. cont_cast):
   //
   
   static_cast < U::type > (1);
   
   //
   // In using directives:
   //
   
   {
   
   using Type0 = U::type;
   
   typedef U::type Type1;
   
   }
   
   //
   // and in lambda function arguments:
   //
   
   auto
      lambda =
         []
         < typename V >
         (V::U argument = V::name)
         -> V::U
         {
            return
               V::name;
         }
         ;
   
   return 0;
}
