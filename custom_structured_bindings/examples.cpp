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

#include <type_traits>
#include <string>
#include <utility>
#include <iostream>

//
// Defining the functions necessary for a custom structured
// binding for a class named 'S' requires the following:
//
//    1     ::std::tuple_size <S>
//    2     ::std::tuple_element <S>, for as many elements
//          as there are in S, and:
//    3     get<N>(object) or object.get<N>(), where object
//          is an instance of S.
//
// A change to this was introduced in C++20: typically
// object.get<N>() has priority over get<N>(object), but if
// object has an (unrelated) member named "get" (eg. 
// ::std::shared_ptr) then this will not work. So in C++20
// this was changed: the object.get<N>() form is preferred
// only if it's a template function and if the first
// template parameter is is a non-type template parameter.
//

//
// To declare structured bindings for a simple class with
// getters (and no setters) for an integer and a string, do
// as follows:
//

class S final
{
private:
   int
      first_;
   
   ::std::string
      second_;
   
public:
   S(int first, ::std::string const & second)
      :
      first_(first),
      second_(second)
      { }
   
   int const &
      first(void) const
   {
      return
         first_;
   }
   
   int &
      first(void)
   {
      return
         const_cast <int &>
            (
            static_cast
               <
               S const &
               >
               (*this).first()
            )
            ;
   }
   
   ::std::string const &
      second(void) const
   {
      return
         second_;
   }
   
   ::std::string &
      second(void)
   {
      return
         const_cast <::std::string &>
            (
            static_cast
               <
               S const &
               >
               (*this).second()
            )
            ;
   }
}
;

//
// Unfortunately the required functions, eg. tuple_size,
// must be in namespace std:
//

namespace std {

template<>
struct tuple_size< ::S >
   :
   public integral_constant< ::std::size_t, 2u >
   { }
   ;

template<>
struct tuple_element< 0, ::S >
{
   typedef int type;
}
;

template<>
struct tuple_element< 1, ::S >
{
   typedef ::std::string type;
}
;

}

//
// The other functions can be in custom namespaces:
//

namespace detail {

//
// A helper function that removes some duplicate code using
// universal references:
//

template
   <
   ::std::size_t
      Index
         ,
   typename T
   >
auto &&
__get(T && object)
{
   static_assert( Index < 2 );
   
   if constexpr (Index == 0)
   {
      return
         ::std::forward<T>( object ).first();
   }
   
   if constexpr (Index == 1)
   {
      return
         ::std::forward<T>( object ).second();
   }
}

}

//
// 4 get() functions with different reference and move
// types. 'S const &' is required by structured bindings of
// type 'auto const & []'. 'S &' is required by structured
// bindings of type 'auto & []'.
//

template<::std::size_t Index>
typename ::std::tuple_element<Index, ::S>::type &
get(::S & object)
{
   return
      detail::__get <Index> (object);
}

template<::std::size_t Index>
typename ::std::tuple_element<Index, ::S>::type const &
get(::S const & object)
{
   return
      detail::__get <Index> (object);
}

template<::std::size_t Index>
typename ::std::tuple_element<Index, ::S>::type &
get(::S && object)
{
   return
      detail::__get <Index> ( ::std::move(object) );
}

template<::std::size_t Index>
typename ::std::tuple_element<Index, ::S>::type const &
get(::S const && object)
{
   return
      detail::__get <Index> ( ::std::move(object) );
}

int main(int argc, char ** argv)
{
   {
   
   S object{ 1, "test" };
   
   //
   // Binding qualifiers on the auto keyword in structured
   // bindings apply to how the source is bound, not how the
   // destination object(s) is (are) bound:
   //
   
   auto & [ first, second ] = object;
   
   //
   // The structured binding is auto &, so this modifies
   // the original object:
   //
   
   first = 2;
   
   ::std::cout << object.first()
               << ::std::endl;
   
   }
   
   {
   
   S object( 1, "test" );
   
   //
   // Note: not what you think. This form refers to
   // get( S && ), not get ( S & ):
   //
   
   auto [ first, second ] = object;
   
   }
   
   {
   
   S const object{ 1, "test" };
   
   auto const & [ first, second ] = object;
   
   }
   
   {
   
   S const object{ 1, "test" };
   
   auto && [ first, second ] = object;
   
   }
   
   return 0;
}
