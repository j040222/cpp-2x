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

#include <span>

#include <iostream>
#include <vector>
#include <memory>
#include <numeric>
#include <cassert>
#include <string>

//
// Spans are objects that reference contiguous sequences
// of objects. They are sometimes called views. Spans have
// constant copy/move time complexity and do not own the
// data that they point to. You can modify the underlying
// data via a span.
//
// Spans contain information about the length of the array
// as well as a pointer to the array data. They support
// iteration (and reverse-iteration) and random access.
//
// Use span::size_bytes() to get the total size of the
// array in bytes. You can create a subspan (a span to
// part of the viewed array) using span::first (a subspan
// to the first N elements), span::last (a subspan to the
// last N elements) and span::subspan (for an arbitrary
// subspan).
//

void
size_of_array
   (
   ::std::span <unsigned> const &
      span
   )
{
   ::std::cout << span.size()
               << " elements starting at "
                     //
                     // to_address was also added in c++20.
                     // It accepts ray pointers (T*) and
                     // smart pointers:
                     //
               << ::std::to_address( span.data() )
               << ", total size "
               << span.size_bytes()
               << ::std::endl
                  ;
   
   return;
}

int main(int argc, char ** argv)
{
   {
   
   unsigned
      array[4u] { 1u, 2u, 3u, 4u };
   
   size_of_array( array );
   
   }
   
   {
   
   ::std::vector <unsigned>
      vector { 1u, 2u, 3u, 4u };
   
   size_of_array( vector );
   
   }
   
   {
   
   //
   // Span can also be initialized using a raw pointer
   // and an integer (the array length):
   //
   
   auto
      array = ::std::make_unique <unsigned[]> (4);
   
   array[0] = 1u;
   array[1] = 2u;
   array[2] = 3u;
   array[3] = 4u;
   
   ::std::span <unsigned>
      span( array.get(), 4u );
   
   size_of_array( span );
   
   
   //
   // The span data can be modified:
   //
   
   ::std::iota( span.begin(), span.end(), 2u );
   
   assert( span[0] == 2 );
   
   }
   
   {
   
   //
   // ::std::string_view (for strings) is similar to
   // ::std::span <char>, but the former doesn't allow the
   // string to be modified.
   //
   
   ::std::string const
      string( "a string" );
   
   ::std::string_view
      view( string );
   
   }
   
   return 0;
}
