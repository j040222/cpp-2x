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

#include <numeric>
#include <cmath>
#include <array>
#include <string>
#include <memory>

#include <iostream>
#include <cassert>

//
// C++20 adds functions for:
//
//    1     The midpoint of two integers/floats/doubles
//          (::std::midpoint in <numeric>).
//    2     A point along the linear interpolation of two
//          values (::std::lerp in <cmath>).
//    3     to_array, to convert raw arrays to ::std::array
//          objects.
//    4     ::std::make_shared of an array.
//    5     ::std::string has new member functions to test
//          whether it begins or ends with another
//          expression.
//

int main(int argc, char ** argv)
{
   //
   // midpoint and lerp:
   //
   
   //
   // Rounds toward zero:
   //
   
   {
   
   auto const
      midpoint = ::std::midpoint( 20, 30 );
   
   ::std::cout << midpoint << ::std::endl;      // 25
   
   }
   
   {
   
   double const
      interpolated = ::std::lerp( 20, 30, 0.5 );
   
   ::std::cout << interpolated << ::std::endl;   // 25
   
   }
   
   //
   // to_array:
   //
   
   {
   
   //
   // Create an array object from a raw array:
   //
   
   int
      raw_array[3] { 1, 2, 3 };
   
   auto const
      array = ::std::to_array ( raw_array );
   
   assert( array.size() == 3 );
   
   //
   // The array type can be cast if it is an initializer
   // list:
   //
   
   auto const
      array2 =
         ::std::to_array <unsigned long>
            (
               { 1, 2, 3 }
            )
            ;
   
   }
   
   //
   // make_shared:
   //
   
   {
   
   //
   // 100 integers initialized to 0:
   //
   
   //
   // Note: does not work with g++11, Ubuntu. It does work
   // with g++12:
   //
   
   ::std::shared_ptr
      <
      int[]
      >
      first = ::std::make_shared <int[]> (100);
   
   //
   // 101 integers initialized to 1:
   //
   
   ::std::shared_ptr
      <
      int[]
      >
      second = ::std::make_shared <int[]> (101, 1);
   
   }
   
   //
   // ::std::string provides new functions named starts_with
   // and ends_with:
   //
   
   {
   
   ::std::string const
      expression_to_search = "11 2 11";
   
   expression_to_search.starts_with( "11" );
   
   expression_to_search.ends_with( "11" );
   
   }
   
   return 0;
}



