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

#include <iostream>

//
// C++20 adds an alternative overload for class member
// delete. The overload accepts a tag, ::std::
// destroying_delete_t, as its second argument. If the
// overload exists then it is responsible for calling
// the class destructor (unlike the previous version without
// the tag, which is not required to call the destructor).
//

struct U final
{
   ~U(void)
   {
      ::std::cout << "~U()" << ::std::endl;
   }
   
   void operator delete (void * p)
   {
      ::std::cout << "U::operator delete" << ::std::endl;
      
      ::operator delete(p);
   }
}
;

struct V final
{
   ~V(void)
   {
      ::std::cout << "~V()" << ::std::endl;
   }
   
   void operator delete(V * p, ::std::destroying_delete_t)
   {
      ::std::cout << "V::operator delete" << ::std::endl;
      
      ::operator delete(p);
   }
}
;

int main(int argc, char ** argv)
{
   {
   
   //
   // Calls ~U then calls U::operator delete (because it 
   // exists), which in turn calls ::operator delete:
   //
   
   delete new U;
   
   //
   // Note that "delete new" is not the same as
   // "::delete new". The latter does not call the member
   // function:
   //
   
   ::delete new U;
   
   }
   
   {
   
   //
   // Does not call ~V unless V::operator delete does:
   //
   
   delete new V;
   
   }
   
   return 0;
}
