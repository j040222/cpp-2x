# Feature Test Macros

`C++20` added many macros that test for `C++11` features.

If a macro is defined (eg. `__cpp_using_enum`) then its value represents the year and month the attribute/feature was added to the working draft. If the value is 0 then the compiler (or the compiler and the `C++` version it is compiling for) does not support the attribute/feature.

```c++
//
// Language and library features are generally tested
// using macros prefixed with __cpp and __cpp_lib,
// respectively:
//

::std::cout << __cpp_using_enum << ::std::endl;

//
// Attributes are tested using __has_cpp_attribute,
// which can itself be tested as a macro:
//

#ifdef __has_cpp_attribute
::std::cout << __has_cpp_attribute(maybe_unused)
            << ::std::endl
               ;
#endif
```
