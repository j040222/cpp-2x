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

//
// In C++20 the size of newed arrays is deduced, in the same
// way that arrays on the stack have deduced sizes:
//

int main(int argc, char ** argv)
{
   int p0[] { 1, 2, 3 };
   
   int * p1 = new int[3] { 1, 2, 3 };
   int * p2 = new int[] { 1, 2, 3 };            // Deduced
   
   //
   // Alternatively:
   //
   
   int * p1_b = new int[3] ( 1, 2, 3 );
   int * p2_b = new int[] ( 1, 2, 3 );          // Deduced
   
   //
   // This also works with strings:
   //
   
   char * p3 = new char[5] { "test" };
   char * p4 = new char[] { "test" };           // Deduced
   
   return 0;
}
