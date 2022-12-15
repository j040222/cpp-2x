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
// In C++20 private subtypes can be used to partly or
// fully specialize class templates. This was adjusted in
// P0692R1.
//
// Many compilers would allow private subtypes to be used
// for full specialization before C++20.
//

class A final
{
private:
   class B;
}
;

template<typename T>
class C { } ;

template<>
class C<A::B> { } ;

//
// Partial specialization was not accepted by all compilers
// before C++20, however:
//

class A2 final
{
private:
   template<typename T>
   class B { } ;
}
;

template
   <
   typename T
   >
class C< A2::B<T> > { } ;

int main(int argc, char ** argv)
{
   return 0;
}
