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
#include <cassert>

//
// `C++20` adds several new attributes, including
// [[likely]], [[unlikely]] and [[no_unique_address]].
//

struct EmptyObject
   { }
;

//
// [[no_unique_address]] can be used to modify the bytes
// occupied by class members:
//

struct First final
{
   char
      c;
   EmptyObject
      e;
}
;

struct Second final
{
   char
      c;
   [[no_unique_address]] EmptyObject
      e;
}
;

struct Third final
{
   char
      c[2];
   [[no_unique_address]] EmptyObject
      e1, e2;
}
;

//
// An example of a function that uses "likely" and "unlikely"
// code pathways:
//

int
factorial(int n)
{
   if( n > 0 ) [[likely]]
   {
      return n * factorial(n - 1);
   }
   else [[unlikely]]
   {
      return 1;
   }
}

//
// In C++20, [[nodiscard]] also accepts an optional message
// (which is generally displayed by the compiler in
// warnings):
//

[[nodiscard("Do not discard return value")]]
int
no_discard_function(void)
{
   return 1;
}

int main(int argc, char ** argv)
{
   //
   // In this case First::e receives a unique address even
   // though it's empty, which means that sizeof(First) !=
   // sizeof(First::c)
   //
   
   static_assert
      (
         sizeof(First)
         
         >=
         
         sizeof(First::c) + sizeof(First::e)
      )
      ;
   
   //
   // In this case the compiler is allowed to overlap
   // the addresses of c and e, 
   //
   
   static_assert
      (
         sizeof(Second)
         
         ==
         
         sizeof(Second::c)
      )
      ;
   
   {
   
   Second
      object{ }
         ;
   
   assert
      (
         static_cast <void*> (&object.c)
         
         ==
         
         static_cast <void*> (&object.e)
      )
      ;
   
   }
   
   //
   // In this case e1 and e2 are not allowed to share the
   // same address because they have the same type. e1
   // can however share an address with c[0] and e2 can (but
   // may not) share an address with c[1].
   //
   
   static_assert
      (
         sizeof(Second)
         
         ==
         
         sizeof(Second::c)
      )
      ;
   
   {
   
   Third
      object{ }
         ;
   
   static_assert
      (
         sizeof(Third) >= 2
      )
      ;
   
   }
   
   no_discard_function();
   
   return 0;
}
