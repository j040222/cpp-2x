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

#include <cstdint>
#include <type_traits>
#include <iostream>

//
// C++20 adds a type named char8_t.
//

//
// char8_t has an underlying representation that matches
// unsigned char, but it is not the same type. It has
// the same size and alignment as unsigned char.
//
// Note that the underlying types of the (existing) types
// char16_­t and char32_­t were also uint_­least16_­t and
// uint_­least32_­t, respectively:
//

static_assert
   (
      not
      ::std::is_same_v <unsigned char, char8_t>
   )
   ;

//
// char may have the same range and underlying
// representation as char8_t, but it is still a distinct
// type:
//

static_assert
   (
      not
      ::std::is_same_v <char, char8_t>
   )
   ;

//
// In fact, in c++:
//

//
// All of the following are true:
//

static_assert
   (
      not
      ::std::is_same_v <char, signed char>
   )
   ;
static_assert
   (
      not
      ::std::is_same_v <char, unsigned char>
   )
   ;
static_assert
   (
      not
      ::std::is_same_v <char, char8_t>
   )
   ;

void
is_it_utf8(char const * data)
{
   ::std::cout << "is not UTF8" << ::std::endl;
}

void
is_it_utf8(char8_t const * data)
{
   ::std::cout << "is UTF8" << ::std::endl;
}

void
utf8_argument(char const * data)
{
}

int main(int argc, char ** argv)
{
   //
   // char8_t provides a distinct type for UTF8 encoded
   // data, so overloading for UTF8 string literals vs.
   // ordinary string literals is possible:
   //
   
   is_it_utf8("test");
   
   is_it_utf8(u8"test");
   
   //
   // char8_t was also added to ensure that UTF8 data
   // has an unsigned type, because char is signed or
   // unsigned depending on the implementation:
   // https://stackoverflow.com/questions/57402464/
   //
   
   /*
   
   utf8_argument(u8"test"); // Error in C++20,
                            // allowed in C++17
   
   */
   
   return 0;
}
