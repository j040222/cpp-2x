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

#include <concepts>
#include <iostream>
#include <utility>

int main(int argc, char ** argv)
{
   auto
      generic_lambda =
         [] (auto first, auto second)
         {
            return
               first * second ;
         }
         ;
   
   {
   
   int
      input_0 = 1
         ,
      input_1 = 2;
   
   generic_lambda(input_0, input_1);
   
   }
   
   {
   
   unsigned
      input_0 = 1
         ,
      input_1 = 2;
   
   generic_lambda(input_0, input_1);
   
   }
   
   auto
      template_lambda =
         []
         <typename T>
         (T first, T second)
         {
            return
               first * second ;
         }
         ;
   
   {
   
   int
      input_0 = 1
         ,
      input_1 = 2;
   
   template_lambda(input_0, input_1);
   
   }
   
   auto
      template_lambda2 =
         []
         <typename T>
         (T first, auto second)
         {
            return
               first * second ;
         }
         ;
   
   {
   
   int
      input_0 = 1
         ,
      input_1 = 2;
   
   //
   // Has 2 template parameters:
   //
   
   template_lambda2 (input_0, input_1);
   
   }
   
   auto
      concept_lambda =
         []
         <::std::floating_point T>
         (T first, T second)
         {
            return
               first * second ;
         }
         ;
   
   auto
      concept_lambda2 =
         []
         <typename T>
            requires ::std::floating_point<T>
         (T first, T second)
         {
            return
               first * second ;
         }
         ;
   
   {
   
   double
      input_0 = 1.
         ,
      input_1 = 2.;
   
   concept_lambda(input_0, input_1);
   
   }
   
   {
   
   unsigned
      lambda_value = 2
         ;
   
   //
   // Note that you can also capture a variable as a
   // const reference:
   //
   
   auto
      const_capture_lambda =
         [&lambda_value = ::std::as_const(lambda_value)]
         (void)
         {
            return
               lambda_value ;
         }
         ;
   
   const_capture_lambda();
   
   }
   
   auto
      variadic_lambda =
         []
         <typename... T>
         (T&& ... args)
         {
            return
               (args * ...)   // A "fold expression"
                  ;
         }
         ;
   
   variadic_lambda(1, 2, 3);
   
   {
   
   unsigned
      lambda_value = 2
         ;
   
   //
   // By default, the lambda operator() is const:
   //
   
   auto
      nonconst_capture_lambda =
         [=]
         (void) mutable
         {
            ++lambda_value;   // A copy
            
            return
               lambda_value ;
         }
         ;
   
   nonconst_capture_lambda();
   
   ::std::cout << lambda_value << ::std::endl;  // Still 2
   
   }
   
   return 0
      ;
}
