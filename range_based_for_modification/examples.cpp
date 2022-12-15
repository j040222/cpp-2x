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

//
// An additional variable is now allowed in range-based for
// loops
//

int main(int argc, char ** argv)
{
   ::std::vector <int> const
      container{ 1, 2, 3 }
         ;
   
   for(
            //
            // An additional variable is allowed here in
            // C++20:
            //
         ::std::size_t
            counter(0u)
               ;
         auto const &
            p : container
      )
   {
      ++counter;
      
      continue
         ;
   }
   
   return 0;
}
