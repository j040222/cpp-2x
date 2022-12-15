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

#include <vector>

#include <iostream>

int main(int argc, char ** argv)
{
   //
   // In C++20 this is an instance of ::std::vector<int>.
   // 
   // In C++17, technically, it could be a vector defined by
   // an initializer list consisting of one vector, in which
   // case the type would be ::std::vector<::std::vector<int
   // >>.
   //
   // The copy constructor is prefered to the list
   // constructor in C++20 if the initialization consists of
   // a single element compatible with the class type:
   //
   
   auto
      vector{ ::std::vector { 2, 4, 6, 8 } };
   
   ::std::cout << typeid( vector ).name() << ::std::endl;
   
   return 0;
}
