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
// In C++17, constexpr-constructed objects must initialize
// all of their non-static data members. In C++20 this was
// relaxed. In c++20, not all members need to be initialized
// by the constructor, but reading (using) uninitialized
// members in constexpr contexts in an error.
//

struct WithDefaultInitialization
{
   unsigned
      value0 = 1u
         ,
      value1 = 2u
         ;
}
;

struct WithoutDefaultInitialization
{
   unsigned
      value0 = 1u
         ,
      value1
         ;
}
;

template
   <
   typename
      T
   >
constexpr
T
default_construct_object(void)
{
   //
   // constexpr-instantiating a class with default-
   // initialized members is allowed in C++20:
   //
   
   T t;
   
   return
      t;
}

template
   <
   typename
      T
   >
constexpr
auto
use_uninitialized_member(void)
{
   T object;
   
   //
   // object.value1 is uninitialized. In C++20 the compiler
   // can detect this and raises an error:
   //
   
   object.value0 = object.value1;
   
   return
         
         //
         // Contains whatever object.value1 contained, which
         // is uninitialized:
         //
         
      object.value0
         ;
}

int main(int argc, char ** argv)
{
   //
   // Error in C++17, but not in C++20, because
   // WithoutDefaultInitialization does not initialize all
   // of its members:
   //
   
   constexpr
      auto
         a =
            default_construct_object
               <
               WithoutDefaultInitialization
               >
               ()
               ;
   
   //
   // Not an error, even in C++17: WithDefaultInitialization
   // does initialize all of its members:
   //
   
   constexpr
      auto
         b =
            default_construct_object
               <
               WithDefaultInitialization
               >
               ()
               ;
   
   //
   // An error in C++20 because
   // WithoutDefaultInitialization::value1 is used
   // uninitialized:
   //
   
   {
   
   constexpr
      auto
         value =
            use_uninitialized_member
               <
               WithoutDefaultInitialization
               >
               ()
               ;
   
   }
   
   //
   // Not an error in c++20:
   //
   
   {
   
   constexpr
      auto
         value =
            use_uninitialized_member
               <
               WithDefaultInitialization
               >
               ()
               ;
   
   }
   
   return 0;
}
