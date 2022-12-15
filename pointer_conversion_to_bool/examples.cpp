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
// Conversions from pointer (or nullptr) to bool are now
// narrowing. nullptr can only be used with direct { }
// initialization:
//

int main(int argc, char ** argv)
{
   void * pointer;
   
   {
   
   //
   // Initializations in { } braces produce warnings if the
   // conversion is narrowing:
   //
   
   bool boolean0 { pointer } ;
   
   bool boolean1 = { pointer } ;
   
   //
   // The following are not warnings:
   //
   
   bool boolean2 ( pointer ) ;
   
   bool boolean3 = ( pointer ) ;
   
   bool boolean4 = pointer;
   
   }
   
   {
   
   bool boolean0 { nullptr } ;
   
   //
   // Error: conversion to bool from nullptr requires
   // direct initialization:
   //
   
   // bool boolean1 = nullptr ;
   
   // bool boolean2 = { nullptr };
   
   }
   
   return 0;
}
