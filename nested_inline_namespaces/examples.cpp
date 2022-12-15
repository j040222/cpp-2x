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
// In C++20 the 'inline' keyword is allowed to appear in
// nested namespace definitions. Functions in inline
// namespaces are referenced as if they were declared in
// the nearest non-inlined upward namespace.
//
// Inline namespaces can be used for versioning purposes.
// For example, if you have two versions of a class in
// separate namespaces, then one of the classes can be made
// the 'default' version by inlining its enclosing
// namespace.
//

namespace A
{
namespace B
{
inline namespace C
{
inline namespace D
{

void function(void);

}
}
}
}

namespace A::B::inline C::inline D
{

void function(void) { }

}

int main(int argc, char ** argv)
{
   A::B::function();
   
   return 0;
}
