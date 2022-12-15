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

#include <memory>
#include <thread>

//
// The control block of a ::std::shared_ptr object is thread
// safe. (because ::std::shared_ptr must be deleted only
// once). Accessing the shared_ptr resource is however not
// thread-safe.
//

int main(int argc, char ** argv)
{
   //
   // An example of a data race. The value referenced by the
   // shared_ptr is assigned by multiple threads:
   //
   
   {
   
   auto
      p = ::std::make_shared <unsigned> (0)
         ;
   
   for(
      ::std::size_t
         i(0u)
         ;
      i< 5u
         ;
      ++i
      )
   {
      ::std::thread
         (
            [&p, &i]
            {
               auto
                  new_p =
                     ::std::make_shared <unsigned>
                        (
                        i + 1u
                        )
                        ;
               
                  //
                  // This would cause a data race because
                  // only the shared_ptr control block is
                  // thread safe, not the resource that it
                  // points to:
                  //
               
               // p = new_p
               
                  //
                  // This, however, is thread safe: the
                  // standard library provides atomic
                  // functions for modifying shared_ptr:
                  //
               
               ::std::atomic_store( &p, new_p );
            }
         )
         .detach();
            ;
      
      continue
         ;
   }
   
   
   {
   
   //
   // Create an atomic shared_ptr. operator= (and store),
   // the cast operator (::std::shared_ptr) and exchange
   // are all atomic operations too:
   //
   
   auto
      regular_p = ::std::make_shared <unsigned> (1)
         ;
   
   ::std::atomic
      <
      ::std::shared_ptr
         <
         unsigned
         >
      >
         //
         // Works in g++-12 :
         //
      p( regular_p )
         ;
   
   //
   // Get the underlying shared_ptr:
   //
   
   ::std::shared_ptr <unsigned>
      p2 = p.load()
         ;
   
   }
   
   
   }
}
