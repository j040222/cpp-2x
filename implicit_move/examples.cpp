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
#include <iostream>

//
// Moves, rather than copies, are used more often in C++20
// than in C++17:
//

//
// Return values can be moved rather than copied:
//

::std::unique_ptr <int>
function0( ::std::unique_ptr <int> && p )
{
   //
   // This is a copy in c++17:
   //
   
   return p;
}

//
// So can thrown objects:
//

void
function1( ::std::unique_ptr <int> && p )
{
   //
   // This is a copy in c++17:
   //
   
   throw p;
}

struct Object final
{
   ::std::unique_ptr <int>
      p_
         ;
   
   Object( ::std::unique_ptr <int> && p )
      :
      p_( ::std::move(p) )
      { }
   
   Object( Object const & ) = delete;
}
;

Object
function2(void)
{
   auto
      p = ::std::make_unique <int> (1);
   
   //
   // Moves an object of type Object:
   //
   
   return p;
}

struct AnotherObject final
{
   ::std::unique_ptr <int>
      p_
         ;
   
   AnotherObject
      (
      ::std::unique_ptr <int> && p
      )
      :
      p_( ::std::move(p) )
      { }
   
   operator Object() &&
   {
      return
         Object( ::std::move(p_) );
   }
   
   operator Object() const & = delete;
}
;

Object
function3(void)
{
   AnotherObject
      object
         (
            ::std::make_unique <int> (1)
         )
         ;
   
   //
   // Calls AnotherObject::operator Object() && (a move):
   //
   
   return object;
}

struct Empty final { } ;

struct Object2 final
{
   Object2(Empty const &) = delete;
   
   Object2(Empty &&) { }
}
;

Object2
function4(void)
{
   Empty
      empty
         ;
   
   //
   // Moved:
   //
   
   return
      empty;
}

int main(int argc, char ** argv)
{
   function0( ::std::make_unique <int> (1) );
   
   try
   {
      function1
         (
         ::std::make_unique <int> (1)
         )
         ;
   }
   catch(...) { }
   
   function2();
   
   function3();
   
   function4();
   
   return 0;
}
