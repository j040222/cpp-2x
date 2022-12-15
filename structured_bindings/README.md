# Structured Bindings

Structured bindings are similar to `::std::tie` except that (and unlike `::std::tie`) the arguments do not need to be declared first.

```c++
{

::std::pair
   <
   int
      ,
   ::std::string
   >
   item( 2u, "test" )
      ;

//
// To use ::std::tie, both of the arguments need to be
// declared first:
//

int
   first;
::std::string
   second;

::std::tie( first, second ) = item;

::std::cout << first                      // 2
            << ", "
            << second                     // "Test"
            << ::std::endl;

//
// This also works with tuples:
//

::std::tie( first, second ) =
   ::std::make_tuple
      (
      2u, "test"
      )
      ;

::std::cout << first
         << ", "
         << second
         << ::std::endl;

}
```

In `C++17` the arguments can both be declared at the same time. This is a 'structured binding':

```c++
auto
   tuple =
      ::std::make_tuple
         (
         2u, "test"
         )
         ;

//
// Note that this produces a copy of the tuple elements.
// use auto & to modify the original tuple:
//

auto [ first, second ] = tuple;
```

This also works with arrays, tuples (and types that support `::std::tuple_size` and `get<N>`), and for basic aggregate classes:

```c++
double
   values[3] = { 1., 2., 3. };

auto const
   [ first, second, third ] = values;
```

```c++
struct S0 final
{
   int
      first;
   
   ::std::string
      second;
}
;

S0 object;

auto &
   [ first, second ] = object;

first = 2;

assert( 2 == object.first );
```

Note that structured bindings can also be initialized in iterator loops:

```c++
::std::unordered_map
   <
   ::std::string
      ,
   unsigned
   >
   map;

for( auto const & [ key, value ] : map )
{
   continue;
}
```

In `C++20` structured bindings can be captured by lambdas by value and by reference. `C++20` also allows structured bindings to be declared `[[maybe_unused]]` and `thread_local`, and the structured binding itself can be static:

```c++20
S1 object;

auto const [ first, second ] = object;

auto
   function =
      [=]      // & also allowed
      (void) -> int
      {
         return ( first + second );
      }
      ;
```

