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

#include <coroutine>
#include <exception>
#include <iostream>

//
// Based on an example from
// https://www.scs.stanford.edu/~dm/blog/c++-coroutines.html:
//

//
// The class returned by a coroutine is referred to as a
// future. It is not the same as ::std::future. The returned
// type (call it 'Generator') must provide the following:
//
//    typename Generator::promise_type
//    
//       which is referred to as the 'promise' (and is not
//       the same as ::std::promise);
//    
//    Generator::promise_type::get_return_object(void)
//    
//       which returns an instance of Generator;
//    
//    Generator::promise_type::yield_value(object)
//    
//       which is called once whenever 'co_yield object' is
//       invoked by the coroutine;
//    
//    Generator::promise_type::return_value(object)
//    
//       which is called once whenever 'co_return object' is
//       invoked by the coroutine;
//    
//    Generator::promise_type::return_void(object)
//    
//       which is called once whenever 'co_return' (no
//       arguments) is invoked by the coroutine or if
//       control falls off the end of the function.
//

//
// co_yield and co_return modify the promise object.
//
// The coroutine state (which is on the heap) contains an
// instance of promise_type, P. So from inside P it is
// possible to construct a coroutine handle:
//
//    ::std::coroutine_handle
//       <
//       promise_type
//       >
//       ::
//       from_promise(*this)
//

//
// This is an illustrative implementation of a Generator of
// type T:
//

template
   <
   typename T
   >
class Generator
{
public:
   //
   // Types and type definitions:
   //
   
   struct
      promise_type
         ;
   
   using
      handle_type =
         ::std::coroutine_handle
            <
            promise_type
            >
            ;
   
   struct promise_type
   {
      T
         value_
            ;
      
      ::std::exception_ptr
         exception_
            ;
      
      //
      // Must return an instance of the 'future', Generator.
      // This is the object returned to the consumer.
      //
      
      Generator
         get_return_object()
      {
         return
            Generator
               (
               handle_type::from_promise(*this)
               )
               ;
      }
      
      //
      // Controls the behaviour of the coroutine on entry.
      // If initial_suspend returns ::std::suspend_always,
      // the coroutine is suspended as soon as control
      // enters it.
      //
      
      ::std::suspend_always
         initial_suspend()
      {
         return { } ;
      }
      
      //
      // Controls the behaviour of the coroutine when it
      // exits (runs out of instructions). If this function
      // returns ::std::suspend_always then the coroutine
      // implicitly co_awaits the object returned by this
      // function. In that case, code outside the coroutine
      // is responsible for calling co_await.
      //
      
      ::std::suspend_always
         final_suspend() noexcept
      {
         return { } ;
      }
      
      //
      // Called if the coroutine function body raises an
      // uncaught exception and if the initial await resume
      // is not called:
      //
      
      void
         unhandled_exception()
      {
         exception_ = ::std::current_exception();
      }
      
      //
      // Called once by whenever the coroutine uses an
      // expression "co_yield yield_value".
      //
      
      template
         <
         ::std::convertible_to <T> From
         >
      ::std::suspend_always
         yield_value(From && yield_value)
      {
         value_ = ::std::forward <From> (yield_value)
            ;
         
         return { } ;
      }
      
      //
      // Called once whenever the coroutine uses the
      // expression "co_return returned_value".
      //
      // Note that you can also provide:
      //
      //    return_value(void)
      //
      // in which case return_value() is called when the
      // coroutine uses the expression "co_return" (no
      // arguments) or when control falls of the end of the
      // coroutine function.
      //
      // You cannot declare both return_value functions:
      //
      
      template
         <
         ::std::convertible_to <T> From
         >
      void
         return_value(From && returned_value)
      {
         this->yield_value
            (
            ::std::forward <From> (returned_value)
            )
            ;
      }
   }
   ;
   
private:
   
   handle_type
      handle_
         ;
   
public:
   
   Generator
      (
      handle_type
         h
      )
      : handle_(h)
      { }
   
   ~Generator()
   {
      //
      // Destroy the state (on the heap) associated with
      // the coroutine:
      //
      
      handle_.destroy();
   }
   
   
   //
   // A boolean cast function, for use with (eg.) while
   // loops.
   //
   
   explicit operator bool()
   {
      get_value_from_promise()
         ;
      
      return
         !handle_.done()
            ;
   }
   
   //
   // Templated coroutine handles provide a function named
   // promise() which returns a reference to the promise
   // object on the heap:
   //
   
   T operator() ()
   {
      get_value_from_promise()
         ;
      
      is_complete_ = false
         ;
      
      return
         handle_.promise().value_
            ;
   }
   
private:
   bool
      is_complete_ = false
         ;
   
   void
      get_value_from_promise()
   {
      if ( !is_complete_ )
      {
         handle_()
            ;
         
         if (
               handle_.promise().exception_
            )
         {
            ::std::rethrow_exception
               (
               handle_.promise().exception_
               )
               ;
         }
         
         is_complete_ = true
            ;
      }
   }
}
;

//
// Awaitable objects (objects for use with co_await)
// should provide three functions as follows:
//
//    constexpr bool await_ready() const noexcept;
//    void await_suspend( ::std::coroutine_handle <> );
//    
//    and:
//    
//    constexpr await_resume() const noexcept;
//

//
// An illustrative example of an awaitable object is as
// follows:
//

struct Awaitable final
{
   ::std::coroutine_handle <>
      handle_
         ;
   
   mutable unsigned
      use_count_
         ;
   
   Awaitable(void)
      :
      use_count_(0u)
      { }
   
   //
   // If await_ready returns true, then co_await does not
   // suspend on instances of this class:
   //
  
   constexpr
      bool
      await_ready() const noexcept
   {
      return false;
   }
   
   void
      await_suspend
         (
         ::std::coroutine_handle <>
            h
         )
   {
      handle_ = h;
      
      return
         ;
   }
   
   //
   // The value, if any, returned by the co_await
   // expression. 
   //
   
   constexpr
      unsigned
      await_resume() const noexcept
   {
      ++use_count_;
      
      return
         use_count_
            ;
   }
}
;

//
// Only some types can be returned by coroutines. They must
// declare certain functions and typedefs. See notes
// associated with the class named Generator<T>:
//

Generator
   <
   unsigned
   >
counter_function()
{
   Awaitable
      await { };
   
   //
   // Use of await:
   //
   
   //
   // co_await saves the current state of this function on
   // the heap and then creates an instance of
   // ::std::coroutine_handle, which is the argument to
   // await_suspend.
   //
   // 'co_await await' is equivalent to:
   //
   //    await.await_suspend(coroutine_handle)
   //
   // with the newly-created coroutine_handle. Note that
   // Awaitable has such a function, which stores the
   // handle. You can use this to access the
   // coroutine_handle from inside the coroutine.
   //
   
   unsigned
      number_of_awaits(0u);
   
   number_of_awaits = co_await await;
   
   ::std::cout << number_of_awaits
               << " await"
               << ::std::endl
                  ;
   
   number_of_awaits = co_await await;
   
   ::std::cout << number_of_awaits
               << " awaits"
               << ::std::endl
                  ;
   
   //
   // The standard library also provides two awaitable
   // objects, ::std::suspend_always { } and
   // ::std::suspend_never{ }:
   //
   
   co_await ::std::suspend_never { };  // Does not suspend
   
   co_await ::std::suspend_always { };
   
   
   //
   // Use of co_yield:
   //
   
   for ( unsigned i = 0; i < 3; )
   {
      co_yield
         i++
            ;
   }
   
   co_return 3;
}

int
main(int argc, char ** argv)
{
   auto
      generator =
         counter_function()
            ;
   
   //
   // Step over the co_awaits:
   //
   
   generator(); generator(); generator();
   
   while (generator)
   {
      ::std::cout << "counter_function: "
                  << generator()
                  << std::endl
                     ;
   }
   
   ::std::cout << "counter_function (return value): "
               << generator()
               << std::endl
                     ;
   
   return 0;
}
