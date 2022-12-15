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
// Comma operators in subscript expressions were deprecated
// in C++20:
//

struct A
{
   /*
   
   //
   // In future the [] operator may be extended as follows:
   //
   
   int operator[] (int first, int second, int third)
   {
      return
         (
            first * second * third
         )
         ;
   }
   
   */
   
   int operator[] (int value)
   {
      ::std::cout << value << ::std::endl;
      
      return value;
   }
}
;

int main(int argc, char ** argv)
{
   A
      object;
   
   object[ 0, 1, 2 ];   // object[2] in C++17, deprecated in
                        // C++20
   
   object[ (0, 1, 2) ]; // object[2] in both cases
   
   return 0;
}
