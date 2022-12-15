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

#include <ranges>
#include <algorithm>
#include <vector>
#include <cctype>
#include <iomanip>
#include <tuple>

#include <iostream>

//
// Ranges is "STL v2". It is a drop-in replacement for many
// of the components of the STL library.
//
// There are major differences between ranges and pre-ranges
// code. These include but are not limited to:
//
//    1     Ranges use C++20 concepts to enforce conditions.
//          This greatly improves the clarity of error
//          messages in template code.
//    2.    A range is itself a concept: it is a type that
//          supports ::std::ranges::begin(object) and
//          ::std::ranges::end(object). The type of the end
//          iterator need not be the same as the iterator
//          type returned by end() -- they need only
//          be comparable. This allows, among other things,
//          for infinite ranges: use ::std::
//          unreachable_sentinel for an iterator that never
//          compares positively with another range iterator.
//    3     Many algorithms, eg. ::std::ranges::sort,
//          accept a reference to a range container not
//          just a pair of begin/end iterators.
//

struct Person final
{
   ::std::string
      id_;
   
   double
      salary_;
   
   double
      salary(void)
   {
      return
         salary_;
   }
}
;

int main(int argc, char ** argv)
{
   {
   
   //
   // Sort a container:
   //
   
   ::std::vector<int>
      items;
   
   ::std::ranges::sort( items );
   
   }
   
   {
   
   //
   // The ranges sort function, and other functions in
   // ranges, accept a projection operator. A projection
   // operator is a unary invokable object. "invokable"
   // in this context means either: a univariate callable
   // object, a pointer to a class/struct member, or a
   // pointer to a getter function (accepting no arguments)
   // in a class.
   //
   
   ::std::vector
      <
      Person
      >
      items;
   
   //
   // Sort the container by ID string:
   //
   
   ::std::ranges::sort( items, { }, &Person::id_ );
   
   //
   // Sort the container by salary:
   //
   
   ::std::ranges::sort( items, { }, &Person::salary );
   
   //
   // Sort the container using a custom lambda expression:
   //
   
   ::std::ranges::sort
      (
      items
         ,
      { }
         ,
      [] (auto const & item)
         {
            return
               item.id_.size() + item.salary_;
         }
      )
      ;
   
   }
   
   //
   // Views are important to ranges. Views are ranges that
   // are cheap to copy and move. In general, views do not
   // own the elements they are viewing so that they can be
   // moved and copied in constant time.
   //
   
   namespace views = ::std::ranges::views;
   
   {
   
   //
   // Views are composable. This example drops the last
   // four elements of a range:
   //
   
   ::std::vector<int>
      items { 1, 2, 3, 4, 5, 6, 7 };
   
   {
   
   //
   // ::std::ranges::reverse_view can also be used in
   // place of ::std::ranges::views::reverse, and likewise
   // for drop:
   //
   
   auto
      view =
         views::reverse( views::drop( views::reverse( items ), 3 ) );
   
   for( int v : view )
   {
      ::std::cout << v << " ";
   }
   
   ::std::cout << ::std::endl;
   
   }
   
   //
   // Note that the above is equivalent to views::take:
   //
   
   {
   
   auto
      view =
         views::take( items, 4 );
   
   for( int v : view )
   {
      ::std::cout << v << " ";
   }
   
   ::std::cout << ::std::endl;
   
   }
   
   //
   // Views support an alternative pipe | syntax as follows.
   // Note that the order is reversed when using the pipe
   // operator:
   //
   
   {
   
   auto
      view =
         items | views::reverse | views::drop(3) | views::reverse;
   
   for( int v : view )
   {
      ::std::cout << v << " ";
   }
   
   ::std::cout << ::std::endl;
   
   }
   
   //
   // Since views generally don't own the range they refer
   // to, views can generate the items they are a view of:
   //
   
   {
   
   auto
      view =
         views::iota(1, 8)
            | views::reverse
            | views::drop(3)
            | views::reverse
               ;
   
   for( int v : view )
   {
      ::std::cout << v << " ";
   }
   
   ::std::cout << ::std::endl;
   
   }
   
   //
   // And, since ranges can be infinite, so can views:
   //
   
   {
   
   auto
      view =
         views::iota(1)
            | views::take(7)
            | views::reverse
            | views::drop(3)
            | views::reverse
               ;
   
   for( int v : view )
   {
      ::std::cout << v << " ";
   }
   
   ::std::cout << ::std::endl;
   
   }
   
   }
   
   //
   // There are many other views in the ranges library:
   //
   
   {
   
   ::std::string
      text( "    remove spaces   " );
   
   //
   // Conditionally drop matching elements using a
   // univariate function until the first non-matching
   // element:
   //
   
   {
   
   auto
      view =
         text | views::drop_while( ::isspace );
   
   for( auto const & c : view )
   {
      ::std::cout << c;
   }
   
   ::std::cout << ::std::endl;
   
   }
   
   //
   // Transform elements using a univariate function:
   //
   
   {
   
   auto
      view = text | views::transform( ::toupper );
   
   for( char const & c : view )
   {
      ::std::cout << c;
   }
   
   ::std::cout << ::std::endl;
   
   }
   
   //
   // Conditionally extract matching elements using a
   // univariate function until the first non-matching
   // element:
   //
   
   {
   
   auto
      view =
         text
            | views::drop_while( ::isspace )
            | views::take_while( ::isalnum )
               ;
   
   for( auto const & c : view )
   {
      ::std::cout << c;
   }
   
   ::std::cout << ::std::endl;
   
   }
   
   }
   
   //
   // Views generally do not change the mutability of the
   // objects that they are views of. So, in a range-for
   // loop, the underlying data can be modified:
   //
   
   {
   
   ::std::vector<int>
      items { 1, 2, 3, 4, 5, 6, 7 };
   
   auto
      view =
         items
            | views::filter([] (auto v) { return v % 2 == 1; } );
   
   for( auto & v : view )
   {
      v *= -v;
   }
   
   for( int v : items )
   {
      ::std::cout << v << " ";
   }
   
   ::std::cout << ::std::endl;
   
   }
   
   //
   // Views can also be used to join multiple other ranges:
   //
   
   {
   
   ::std::vector <int> const
      elements[] { { 1, 2 }, { 3, 4 }, { 5, 6 } };
   
   auto
      joined = views::join( elements );
   
   for( int v : joined )
   {
      ::std::cout << v << " ";
   }
   
   ::std::cout << ::std::endl;
   
   }
   
   //
   // Views can also be used to split one view into members:
   //
   
   {
   
   ::std::vector <int>
      items { 1, 2, 3, 4, 3, 2, 1, 2, 3, 4, 3, 2, 1 };
         ;
   
   auto
      separated = views::split( items, 2 );
   
   for( auto const & subrange : separated )
   {
      for( auto const & element : subrange )
      {
         ::std::cout << element << " ";
      }
   }
   
   ::std::cout << ::std::endl;
   
   }
   
   //
   // Other applications include extracing the Nth element
   // from a range of tuple-like elements:
   //
   
   {
   
   ::std::vector
      <
      ::std::tuple< int, char >
      >
      const
         items
            {
               { 1, 'a' },
               { 2, 'b' },
               { 3, 'c' }
            }
            ;
      
   for( auto const & element : items | views::elements<1> )
   {
      ::std::cout << element << " ";
   }
   
   ::std::cout << ::std::endl;
   
   //
   // Alternatively:
   //
   
   for( auto const & element : items | views::values )
   {
      ::std::cout << element << " ";
   }
   
   ::std::cout << ::std::endl;
   
   //
   // And, for first tuple elements only:
   //
   
   for( auto const & element : items | views::keys )
   {
      ::std::cout << element << " ";
   }
   
   ::std::cout << ::std::endl;
   
   }
   
   return 0;
}
