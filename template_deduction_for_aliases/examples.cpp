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
// In C++20 template parameter deduction works even if the
// type is an alias of another template type, unlike in
// C++17, where alias template deduction is not supported:
//

template
   <
   typename T1,
   typename T2
   >
struct U
{
   U(T1 const &, T2 const &) { }
}
;

template
   <
   typename T1
   >
using V = U<T1, int>;

int main(int argc, char ** argv)
{
   V item( 1, 2. );
   
   return 0;
}
