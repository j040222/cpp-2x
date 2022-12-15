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

#include <source_location>
#include <iostream>

//
// C++20 adds the function ::std::source_location::current()
// which contains information about the source line, column
// and enclosing function at the call site:
//

void
log_location
   (
      //
      // Note, the source location of this expression
      // is the caller site, not this function:
      //
   ::std::source_location
      where = ::std::source_location::current()
   )
{
   ::std::cout << "filename: "
               << where.file_name()
               << ", line "
               << where.line()
               << ", character "
               << where.column()
               << ", function: "
               << where.function_name()
               << ::std::endl
                  ;
   
   return;
}

int main(int argc, char ** argv)
{
   //
   // Prints "filename: ./examples.cpp, line 37, character
   // 16, function: int main(int, char**)":
   //
   
   log_location();
   
   return 0;
}
