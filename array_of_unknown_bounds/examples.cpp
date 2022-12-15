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
// C++20 allows conversions from an array of known bounds to
// a reference to an array of unknown bounds. When doing
// overload resolution, arrays with matching bounds are
// selected over arrays of unknown or non-matching sizes.
//

void function( int const (& array) [] )
{
   ::std::cout << "0" << ::std::endl;
}

void function( int const (& array) [1] )
{
   ::std::cout << "1" << ::std::endl;
}

void function( int const (& array) [2] )
{
   ::std::cout << "2" << ::std::endl;
}

int main(int argc, char ** argv)
{
   int array[1] {};
   
   //
   // Overload matches array of known bound, so calls 1:
   //
   
   function(array);
   
   //
   // Overload matches array of known bound, so calls 2:
   //
   
   function( { 2, 3 } );
   
   {
   
   //
   // A reference to an array of unknown bound, so calls 0:
   //
   
   int (& cast) [] = array;
   
   function(cast);
   
   }
   
   //
   // Doesn't match any overload other than array of unknown
   // bound, so calls 0:
   //
   
   function( { 1, 2, 3 } );
   
   return 0;
}
