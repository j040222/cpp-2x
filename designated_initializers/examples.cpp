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

#include <string>

struct Time
{
   unsigned
      hour
         ;
   
   unsigned
      minute
         ;
   
   double
      seconds
         ;
}
;

enum class Month : unsigned
{
   JANUARY,
   FEBRUARY,
   MARCH
      
      //
      // ..
      //
}
;

enum class Day : unsigned
{
   MONDAY,
   TUESDAY,
   WEDNESDAY
      
      //
      // ..
      //
}
;

struct Date
{
   Time
      time
         ;
   
   Month
      month
         ;
   
   Day
      day
         ;
}
;

union Union
{
   int
      first
         ;
   
   ::std::size_t
      second
         ;
}
;

//
// c++20 adds named initializers for structs, classes and
// unions:
//

int main(int argc, char ** argv)
{
   {
   
   Date const
      date
         {
            //
            // The initialization order must be the same
            // as the declaration order:
            //
         .time { .hour = 15, .minute = 32, .seconds = 12 }
            ,
            //
            // = and { } are both valid:
            //
         .month = Month::FEBRUARY
            ,
         .day { Day::MONDAY }
         }
         ;
   
   }
   
   //
   // Designated initializers can also initialize unions:
   //
   
   Union const
      object
         {
         .second = ::std::size_t(1)
         }
         ;
   
   {
   
   Date const
      date
         {
            //
            // hour is 
            //
         .time { .minute = 32 }
            ,
         .month = Month::FEBRUARY
            ,
         .day { Day::MONDAY }
         }
         ;
   
   }
   
   return 0
      ;
}
