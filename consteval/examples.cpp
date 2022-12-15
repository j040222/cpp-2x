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
// Consteval functions can be called in C++ code where
// all of the arguments are constant expressions, but not
// if any of the arguments are non-constant. They are called
// 'immediate functions': every call to the function must
// produce a compile-time constant expression. Variables
// cannot be declared consteval.
//

consteval
int
consteval_factorial(int n)
{
   if(n <= 0)
   {
      return 1;
   }
   
      //
      // Note that consteval_factorial is technically being
      // using with a non-const argument here, but in this
      // context the expression is allowed:
      //
   
   return
      n * consteval_factorial(n - 1);
}

constexpr
int
constexpr_factorial(int n)
{
   if(n <= 0)
   {
      return 1;
   }
   
   return
      n * constexpr_factorial(n - 1);
}

int main(int argc, char ** argv)
{
   {
   
   static constexpr int
      value = constexpr_factorial(5)
         ;
   
   ::std::cout << value
               << ::std::endl
                  ;
   
   }
   
   consteval_factorial(5);   // Allowed
   
   //
   // Consteval and constexpr functions can both be used
   // with static_assert:
   //
   
   static_assert
      (
         consteval_factorial(5) == 120
      )
      ;
   
   /*
   
   {
   
   int
      arg = 0
         ;
   
   consteval_factorial(arg); // Not allowed: arg is not
                             // const
   
   }
   
   */
   
   {
   
   //
   // Calling a constexpr function with non-const runtime
   // arguments is however allowed:
   //
   
   int
      arg = 0
         ;
   
   constexpr_factorial(arg); // Allowed
   
   }
   
   return 0;
}
