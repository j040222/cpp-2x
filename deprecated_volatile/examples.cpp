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
// C++20 deprecates some uses of volatile, and some uses
// of volatile variables. In particular, the following are
// deprecated:
//
//    1     Compound assignment and pre/post increment
//          (decrement) operators;
//    2     volatile qualification of function parameters
//          and returned types.
//
// 'volatile' is a hint the implementation to avoid
// aggressive optimization (involving volatile objects)
// because the affected objects might be changed in ways
// that the implementation can't detect. If you load twice
// from a volatile variable you cannot assume the value to
// be the same both times. And if a volatile object is
// large, you can observe 'memory tearing': another thread
// can observe half of a store occuring.
//
// Colloquially, volatile also means that operations are not
// guaranteed to be synchronized: volatile instructions may
// occur in order in function assembly, but another thread
// may not observe them in that order because the hardware
// does not guarantee it.
//
// The idea behind volatile is that expressions like this:
//
//    int a = x; int b = x;
//
// should load twice from x, not (eg.) load x once into a
// register and then use that register twice.
//
// Volatile is also used where a thread sets the value of a
// variable which another thread waits for. If the variable
// isn't declared volatile, then the compiler may make an
// adverse optimization that assumes the variable is
// unchanged by the running thread:
//
// For example, if this code is compiled with -O3, the
// compiler *might* assume that "finished" is never assigned
// to by the parent thread, so thes loop is "optimized" to:
// while( true ) { }, and the program never exits. Something
// very similar can with happen signal handlers.
//

/*

bool finished = false;

void function(void)
{
   finished = true;
   
   return;
}

int main(int argc, char ** argv)
{
   ::std::thread
      thread( &function );
   
   while( not finished )
   {
      continue;
   }
   
   thread.join();
   
   return 0;
}

*/

//

void motivating_examples(void)
{
   //
   // Volatile does not always do what you expect. For
   // example, does this touch the (volatile) first member
   // of the struct? Most hardware does not have the ability
   // to do bitwise addressing.
   //
   
   struct Bitfield
   {
      volatile int first : 4;
      int second : 4;
   }
   ;
   
   Bitfield
      bitfield;
   
   bitfield.second = 1;
   
   //
   // Does this load and then store, or does it only
   // modify the memory once:
   //
   
   {
   
   volatile
      int i;
   
   i += 1;
   
   //
   // Ie. is it atomic, or is it equivalent to:
   //
   
   int temporary = i;
   temporary = temporary + 1;
   i = temporary;
   
   }
   
   //
   // What does this do?
   //
   
   {
   
   volatile int x = 1;
   
   //
   // If the compiler has an atomic increment instruction
   // on a memory location, this might be unaffected by
   // volatile. Most compilers load x into a register,
   // increment x there and then write x back again:
   //
   
   x++;
   
   }
   
   //
   // If you have a function with a volatile parameter (or
   // a volatile return value) it means literally nothing.
   // The manged function name is exactly the same without
   // the volatile keyword.
   //
}

//
// Volatile was therefore deprecated for function return
// types and parameter types. Note that volatile parameters
// only apply within the function, they don't express
// anything to the caller.
//

volatile int function(volatile int input)
{
   return
      input;
}

int main(int argc, char ** argv)
{
   function(1);
   
   {
   
   volatile int
      p = 1;
   
   int q = 0, q2 = 0;
   
   //
   // Deprecated actions:
   //
   
   ++p; p++; p += 1; q = p = q2;
   
   //
   // And compound expressions, such as clearing bits in
   // registers:
   //
   
   p |= 0x3; p &= 0x3;
   
   }
   
   return 0;
}
