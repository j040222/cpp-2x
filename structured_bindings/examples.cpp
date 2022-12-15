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
#include <utility>
#include <tuple>
#include <string>
#include <cassert>

#include <unordered_map>

struct S0 final
{
   int
      first;
   
   ::std::string
      second;
}
;

struct S1 final
{
   int
      first,
      second;
}
;

int main(int argc, char ** argv)
{
   {
   
   ::std::pair
      <
      int
         ,
      ::std::string
      >
      item( 2u, "test" )
         ;
   
   //
   // Note that, to use ::std::tie, both of the arguments
   // need to be declared first:
   //
   
   int
      first;
   ::std::string
      second;
   
   ::std::tie( first, second ) = item;
   
   ::std::cout << first
               << ", "
               << second
               << ::std::endl;
   
   //
   // This also works with tuples:
   //
   
   ::std::tie( first, second ) =
      ::std::make_tuple
         (
         2u, "test"
         )
         ;
   
   ::std::cout << first
            << ", "
            << second
            << ::std::endl;
   
   }
   
   {
   
   //
   // In C++17 the arguments can both be declared at the
   // same time. This is a 'structured binding':
   //
   
   auto
      tuple =
         ::std::make_tuple
            (
            2u, "test"
            )
            ;
   
   //
   // Note that this produces a copy of the tuple elements.
   // use auto & to modify the original tuple:
   //
   
   auto [ first, second ] = tuple;
   
   }
   
   {
   
   //
   // This also works with arrays, tuples (any type
   // supporting ::std::tuple_size and get<N>), and for
   // basic aggregate classes:
   //
   
   {
   
   double
      values[3] = { 1., 2., 3. };
   
   auto const
      [ first, second, third ] = values;
   
   }
   
   {
   
   S0 object;
   
   auto &
      [ first, second ] = object;
   
   first = 2;
   
   assert( 2 == object.first );
   
   }
   
   }
   
   {
   
   //
   // Structured bindings can also be initialized in
   // iterator loops:
   //
   
   ::std::unordered_map
      <
      ::std::string
         ,
      unsigned
      >
      map;
   
   for( auto const & [ key, value ] : map )
   {
      continue;
   }
   
   }
   
   //
   // In C++20 structured bindings can be captured by
   // lambdas by value and by reference. C++20 also allows
   // structured bindings to be declared [[maybe_unused]]
   // and thread_local, and the structured binding itself
   // can be static.
   //
   
   {
   
   S1 object;
   
   auto const [ first, second ] = object;
   
   auto
      function =
         [=]      // & also allowed
         (void) -> int
         {
            return ( first + second );
         }
         ;
   
   }
}
