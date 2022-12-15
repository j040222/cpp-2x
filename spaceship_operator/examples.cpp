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

//
// The 'spaceship operator', <=>, is a class-based
// comparison operator that, for objects A and B, determines
// whether A < B, A == B or A > B. The spaceship operator
// works in much the same way as `strcmp`: <0 means "A < B",
// ==0 means "A == B" and >0 means "A > B".
//

#include <cassert>
#include <iostream>

//
// <compare> is required to declare operator <=>:
//

#include <compare>

//
// Related operators such as `operator==`, `!=`, `>`, `>=`,
// `<`, `<=` are automatically generated depending on what
// is explicitly defaulted:
//

struct Point
{
   int
      x,
      y
      ;
   
   //
   // If <=> is defaulted then ==, !=, >, >=, < and <=
   // are all automatically generated too.
   //
   // If <=> is not defaulted, == is not automatically
   // defaulted:
   //
   
   auto operator <=> (Point const & other) const = default;
   
   //
   // This is usually:
   //
   
   //
   // ::std::strong_ordering
   //    operator <=> (Point const & other) const = default;
   //
   
   //
   // Note that operator== = default was not allowed before
   // C++20.
   //
}
;

struct Point2
{
   int
      x,
      y
      ;
   
   bool operator== (Point2 const & other) const
   {
      return
         (
            ( this->x == other.x )
            
            and
            
            ( this->y == other.y )
         )
         ;
   }
   
   //
   // operator!= is automatically generated.
   //
}
;

struct Point3
{
   int
      x,
      y
      ;
   
   bool operator== (Point3 const & other) const
   {
      return
         (
            ( this->x == other.x )
            
            and
            
            ( this->y == other.y )
         )
         ;
   }
   
   //
   // Comparing unrelated types:
   //
   
   //
   // Automatically generates != and == for all combinations
   // (lhs/rhs) of Point3 and Point2:
   //
   
   bool operator== (Point2 const & other) const
   {
      return
         (
            ( this->x == other.x )
            
            and
            
            ( this->y == other.y )
         )
         ;
   }
}
;

struct Point4
{
   int
      x,
      y
      ;
   
   //
   // Explicit instantiation:
   //
   
   ::std::strong_ordering
      operator<=> (Point4 const & other) const
   {
      if ( auto cmp = y <=> other.y; cmp != 0 )
      {
         return
            cmp;
      }
      
      return ( x <=> other.x )
         ;
   }
}
;

int main(int argc, char ** argv)
{
   {
   
   Point const
      first { .x = 1, .y = 2 },
      second { .x = 2, .y = 3 }
         ;
   
   assert
      (
         //
         // Performs a lexicographical ordering with
         // Point::x taking precedence over Point::y:
         //
         
         first < second
      )
      ;
   
   //
   // <=> can also be used in this context. <=> returns
   // an object that can be compared with 0. If it is an
   // ordering -- if Point naturally supports < --then <=>
   // is an object that can be compared with 0 in 3 ways
   // as follows. Otherwise, <=> is an object that can be
   // compared with 0 ('equal' or 'equivalent') and 1
   // ('not equal' or 'not equivalent'):
   //
   
   auto
      compared = first <=> second
         ;
   
   if( compared < 0 )
   {
      //
      // first < second:
      //
   }
   else if( compared > 0 )
   {
      //
      // first > second:
      //
   }
   else
   {
      //
      // first and second compared equal:
      //
   }
   
   //
   // The type of (first <=> second) depends on the
   // structure of the Point class. In this case it is
   // a strong_ordering object.
   //
   
   }
   
   {
   
   Point2 const
      third { .x = 3, .y = 4 }
         ;
   
   assert
      (
         //
         // != is automatically generated:
         //
         
         ! ( third != third )
      )
      ;
   
   }
   
   //
   // In C++20 the compiler is allowed to rewrite and
   // synthesize equivalent expressions out of the
   // comparison operators. For example when searching for
   // operators that match
   //
   //    a < b
   //
   // the compiler also searches for operators that match:
   //
   //    ( a <=> b ) < 0      "rewritten"
   //
   // and:
   //
   //    0 < ( a <=> b )      "synthesized"
   //
   // == does not get rewritten in terms of <=>. If <=> is
   // defaulted then a separate (efficient) == is generated.
   // This is so that objects like strings can be
   // efficiently compared. When performing overload
   // resolution, in c++20, non-rewritten non-synthesized
   // expressions are preferred if they can be used.
   //
   // Rewritten expressions include the order of arguments
   // to ==, and !(==) instead of !=, if they are defaulted.
   //
   
   //
   // <=> returns something similar to an enum:
   //
   //    enum class weak_ordering
   //    {
   //       less = -1,
   //       equivalent = 0,
   //       greater = 1
   //    }
   //
   //    enum class strong_ordering
   //    {
   //       less = -1,
   //       equal = 0,
   //       equivalent = 0,
   //       greater = 1
   //    }
   //    
   //    enum class partial_ordering
   //    {
   //       less = -1,
   //       equal = 0,
   //       equivalent = 0,
   //       greater = 1
   //       and unordered
   //    }
   //
   //
   // plus comparison to 0.
   //
   // Note that floating-point comparison using <=> is
   // a partial ordering. This is because floats can be
   // (eg.) NaN.
   //
   
}
