# Utility Functions

`C++20` adds functions for:

* The midpoint of two integers/floats/doubles (`::std::midpoint`, in <numeric>);
* A point along the linear interpolation of two values (`::std::lerp`, in <cmath>);
* `to_array`, to convert raw arrays to `::std::array` objects;
* `make_shared` an array, and:
* `::std::string` has new member functions to test whether it begins or ends with another expression.

Midpoint and lerp:

```c++
//
// Rounds toward zero:
//

{

auto const
   midpoint = ::std::midpoint( 20, 30 );

::std::cout << midpoint << ::std::endl;      // 25

}

{

double const
   interpolated = ::std::lerp( 20, 30, 0.5 );

::std::cout << interpolated << ::std::endl;   // 25

}
```

to_array:

```c++
//
// Create an array object from a raw array:
//

int
   raw_array[3] { 1, 2, 3 };

auto const
   array = ::std::to_array ( raw_array );

assert( array.size() == 3 );

//
// The array type can be cast if it is an initializer
// list:
//

auto const
   array2 =
      ::std::to_array <unsigned long>
         (
            { 1, 2, 3 }
         )
         ;
```

make_shared:

```
//
// 100 integers initialized to 0:
//

//
// Note: does not work with g++11 for Ubuntu. Does work
// with g++12:
//

::std::shared_ptr
   <
   int[]
   >
   first = ::std::make_shared <int[]> (100);

//
// 101 integers initialized to 1:
//

::std::shared_ptr
   <
   int[]
   >
   second = ::std::make_shared <int[]> (101, 1);
```

`::std::string` provides new functions named `starts_with` and `ends_with`:

```c++
::std::string const
   expression_to_search = "11 2 11";

expression_to_search.starts_with( "11" );

expression_to_search.ends_with( "11" );
```

