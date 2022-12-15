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

enum class Colour : unsigned
{
   RED,
   GREEN,
   BLUE
}
;

int main(int argc, char ** argv)
{
   Colour const
      colour = Colour::BLUE
         ;
   
   //
   // In C++20 "using enum" is allowed. Enum values do not
   // need to be prefixed with the enum class name in the
   // same block as this instruction:
   //
   
   using enum Colour;
   
   switch( colour )
   {
   case( RED ):
      ::std::cout << "red" << ::std::endl
         ;
      break;
   case( GREEN ):
      ::std::cout << "green" << ::std::endl
         ;
      break;
   case( BLUE ):
      ::std::cout << "blue" << ::std::endl
         ;
      break;
   }
   
   return 0;
}
