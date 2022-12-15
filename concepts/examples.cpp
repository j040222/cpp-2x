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

#include <concepts>
#include <string>
#include <iostream>

//
// C++20 adds Concepts. Concepts constrain template types
// and the properties that template types may -and many not-
// have.
//

//
// For example, every statement in the following block
// (delimited by semicolons) must be valid for types T that
// satisfy the IsClock concept:
//

template <typename T>
concept IsClock = requires(T object, double parameter)
{
   //
   // Check for the existence of member functions:
   //
   
   object.start();
   object.stop();
   object.reset();
   
   //
   // Check for the existence of operators:
   //
   
   ++object;
   --object;
   object += parameter;
   
   //
   // To test and constrain the types returned by
   // expressions use { } -> . Some qualifiers such as
   // noexcept can be used too:
   //
   
   { object.time_now() } noexcept
      ->
         ::std::convertible_to
            <
            ::std::string
            >
            ;
   
   //
   // Test for a static member function:
   //
   
   //
   // Note, you cannot write { } -> float.
   //
   
   { T::resolution() }
      ->
         ::std::same_as
            <
            float
            >
            ;
   
   //
   // Check for the existence of a typedef:
   //
   
   typename T::ClockResolutionType;
   
   //
   // A statement can also be a predefined concept:
   //
   
   requires ::std::default_initializable<T>;
   
   //
   // Or a combination of predefined concepts:
   //
   
   requires
      
      ::std::default_initializable<T>
      
      and
      
      ::std::copy_constructible<T>
         ;
   
   //
   // Use requires () to test boolean expressions:
   //
   
   requires
      (
         sizeof( decltype( T::resolution() ) )
         
         <=
         
         sizeof( double )
      )
      ;
}
;

//
// Functions can be used to test whether or not a template
// type satisfies a concept:
//

template<typename T>
constexpr bool is_clock()
{
   //
   // Clock<T> is actually an expression of type bool.
   //
   
   return IsClock<T> ;
}

//
// An example of a class that satisfies IsClock:
//

class Clock
{
public:
   Clock(void) = default;
   
   Clock(Clock const &) = default;
   
   Clock(Clock &&) = default;
   
   Clock & operator= (Clock const &) = default;
   
   Clock & operator= (Clock &&) = default;
   
   virtual ~Clock(void) = default;
   
   typedef
      float
      ClockResolutionType
         ;
   
   void start() { }
   
   void stop() { }
   
   void reset() { }
   
   ::std::string time_now(void) const noexcept
   {
      return "";
   }
   
   Clock & operator++ (void) { return *this; }
   
   Clock & operator-- (void) { return *this; }
   
   Clock & operator+= (ClockResolutionType)
   {
      return *this;
   }
   
   static
      ClockResolutionType
      resolution(void) { return 1.; }
         ;
   
   operator ::std::string () const
   {
      return this->time_now();
   }
}
;

//
// Concepts can be used to restrict templates in many ways:
//

//
// In the template parameter list:
//

template
   <
   IsClock T
   >
void
reset_clock(T & clock)
{
   clock.reset();
}

//
// After the template parameter list:
//

template
   <
   typename T
   >
   requires IsClock <T>
void
reset_clock_1(T & clock)
{
   clock.reset();
}

//
// After the function parameter list:
//

template
   <
   typename T
   >
void
reset_clock_2(T & clock) requires IsClock <T>
{
   clock.reset();
}

//
// Using auto:
//

void
reset_clock_3( IsClock auto clock )
{
   clock.reset();
}

//
// If a concept template has multiple parameters then the
// last parameter is substituted when the concept is used as
// a type constraint:
//

template
   <
   class T
      ,
   class U
   >
concept
   Derived = ::std::is_base_of<U, T>::value;

template
   <
   Derived<Clock> T
   >
void
only_derived_from_clock(T const & clock)
   { }

//
// Alternatively:
//

template
   <
   typename T
   >
   requires Derived<T, Clock>
void
only_derived_from_clock_1(T const & clock)
   { }

void
only_derived_from_clock_2
   (
   Derived<Clock> auto const & clock
   )
   { }

struct DerivedClock final : Clock
{
   virtual ~DerivedClock(void) = default
      ;
}
;

//
// Concepts can also constrain function return values using
// `auto`:
//

IsClock auto make_clock(void)
{
   return Clock();
}

Derived< Clock > auto make_derived_clock(void)
{
   return DerivedClock();
}

//
// Since requires() is a boolean, it can be used with
// constexpr if:
//

template
   <
   typename T
   >
void
variable_behaviour(T && object)
{
   constexpr bool is_clock_type = IsClock<T> ;
   
   if constexpr ( is_clock_type )
   {
      ::std::cout << "A clock type"
                  << ::std::endl
                     ;
      
      object.reset();
   }
   else
   {
      ::std::cout << "Not a clock type"
                  << ::std::endl
                     ;
      
      // Do nothing:
   }
   
   return
      ;
}

//
// Concepts can constrain member functions in template
// classes using requires():
//

template
   <
   typename T
   >
struct AnotherDerivedClock final : Clock
{
   virtual ~AnotherDerivedClock(void) = default
      ;
   
   //
   // Causes an error when * is used if T is not a
   // pointer:
   //
   
   T operator* (void) requires ::std::is_pointer_v<T>
   {
      return T();
   }
}
;


//
// Concepts differ from types. Types describe a memory
// layout. Concepts describe how a type can be used,
// operations it can perform or be part of, and relations
// to other types.
//

int main(int argc, char ** argv)
{
   static_assert
      (
         IsClock< Clock >
      )
      ;
   
   //
   // Alternatively:
   //
   
   static_assert
      (
         is_clock< Clock > ()
      )
      ;
   
   Clock
      clock;
   
   reset_clock( clock );
   reset_clock_1( clock );
   reset_clock_2( clock );
   reset_clock_3( clock );
   reset_clock_4( clock );
   
   {
   
   DerivedClock
      derived_clock;
   
   only_derived_from_clock( derived_clock );
   only_derived_from_clock_1( derived_clock );
   only_derived_from_clock_2( derived_clock );
   
   }
   
   //
   // Concepts can be used as a compiler check:
   //
   
   {
   
   IsClock auto
      derived_clock = DerivedClock();
   
   }
   
   {
   
   Derived< Clock > auto
      derived_clock = DerivedClock();
   
   }
   
   {
   
   variable_behaviour( Clock() );
   
   variable_behaviour( 1 );
   
   }
   
   {
   
   AnotherDerivedClock <int> t;
   *t;
   
   }
   
   return 0
      ;
}
