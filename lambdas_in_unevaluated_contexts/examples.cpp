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

#include <set>
#include <string>
#include <iostream>

int main(int argc, char ** argv)
{
   {
   
   //
   // Declaring a typedef of a stateless lambda is allowed
   // in c++20 (this is a lambda in an 'unevaluated
   // context'):
   //
   
   typedef
      decltype
         (
         []
            (
            auto const &
               first
                  ,
            auto const &
               second
            )
            -> bool
            {
               return first.size() < second.size();
            }
         )
      lambda_type
         ;
   
   ::std::cout << typeid(lambda_type).name()
               << ::std::endl
                  ;
   
   //
   // Lambdas can now also be default-constructed, (eg. by
   // a multiset, that uses it for comparison purposes):
   //
   
   using
      custom_set =
         ::std::multiset
            <
            ::std::string
               ,
            lambda_type
            >
            ;
   
   custom_set const
      set { "first", "second", "third" }
         ;
   
   for( auto const & p : set )
   {
      ::std::cout << p << ::std::endl
         ;
      
      continue
         ;
   }
   
   }
   
   {
   
   //
   // A stateless lambda can be default-constructed and
   // copy assigned:
   //
   
   typedef
      decltype
         (
         []
            (
            ::std::string const &
               first
                  ,
            ::std::string const &
               second
            )
            -> bool
            {
               return
                  true
                     ;
            }
         )
      lambda_type_1
         ;
   
   lambda_type_1
      assigned_lambda_1{ }
         ,
      assigned_lambda_2 = assigned_lambda_1
         ,
      assigned_lambda_3( assigned_lambda_2 )
         ;
   
   }
   
   return 0;
}
