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
#include <iostream>

//
// Free begin()/end() functions are now preferred to member
// function begin()/end() functions if at least one of the
// latter does not exist.
//

//
// A structure that contains a begin() iterator function
// but not an end() function:
//

struct Object final
{
   ::std::vector
      <
      int
      >
      items_;
   
   typedef
      decltype( items_ )
      Vector
         ;
   
   Object(void)
      :
      items_{ 1, 2, 3 }
      { }
   
   typename
      Object::Vector::iterator
   begin(Object & object)
   {
      return object.items_.begin();
   }
}
;

//
// Free begin()/end() functions:
//

typename Object::Vector::iterator
begin(Object & object)
{
   return object.items_.begin();
}

typename Object::Vector::iterator
end(Object & object)
{
   return object.items_.end();
}

int main(int argc, char ** argv)
{
   Object
      object;
   
   //
   // In this case, the free begin()/end() functions
   // are used. Object::begin does exist, but there is no
   // matching Object::end function, so the C++20 rule is
   // to select the free functions:
   //
   
   for( auto item : object )
   {
      ::std::cout << item << " ";
   }
   
   ::std::cout << ::std::endl;
   
   return 0;
}
