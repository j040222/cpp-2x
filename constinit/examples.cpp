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
// constinit can be used to initialize variables at
// compiletime:
//

int
function(void)
{
   //
   // Unlike just 'static int', this is initialized at
   // compile time:
   //
   
   static constinit int
      value = 7;
   
   return
      value
         ;
}

//
// constexpr classes can also be initialized at compile
// time:
//

struct Object
{
   int
      value_;
   
   constexpr
      Object(int value) :
      value_(value)
         { }
   
   ~Object(void) { }
}
;

Object
function2(void)
{
   //
   // Object::Object is constexpr, so this is also allowed:
   //
   
   static const constinit Object
       value(7);
   
   //
   // Note that const constinit is not the same as
   // constexpr, because constexpr requires constant
   // destruction.
   //
   
   //
   // Not allowed: ~Object is not constexpr:
   //
   
   // static constexpr Object
   //    value(7);
   
   return
      value
         ;
}

Object
function3(void)
{
   //
   // Note that non-const constinit objects can be modified:
   //
   
   static constinit Object
      value(7);
   
   ++value.value_;
   
   return
      value
         ;
}


int main(int argc, char ** argv)
{
   ::std::cout << function()
               << ::std::endl
                  ;
   
   ::std::cout << function2().value_
               << ::std::endl
                  ;
   
   ::std::cout << function3().value_
               << ::std::endl
                  ;
   
   return 0;
}
