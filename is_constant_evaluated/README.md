# ::std::is_constant_evaluated

`::std::is_constant_evaluated()` was added in `C++20`. In some use cases - but not all - it evaluates to true if the enclosing function is constant-evaluated.

```c++
constexpr
unsigned
function(unsigned argument)
{
   //
   // Note that this should not be:
   //
   //    if constexpr ( ::std::is_constant_evaluated() )
   //
   // because the compiler considers
   // ::std::is_constant_evaluated() to be within the
   // constexpr, so it is always true in the above case.
   // 
   // This also happens if you use is_constant_evaluated
   // in array subscripts, template argument lists and
   // in other contexts, such as static_assert.
   //
   
   if ( ::std::is_constant_evaluated() )
   {
      return
         argument
            ;
   }
   else
   {
      return
         ( argument + 1u );
   }
}
```

```c++
constexpr static unsigned
   value0 = function(1);

static const unsigned
   value1 = function(1);

//
// Initialization of a non-const non-static variable is
// not constexpr-evaluated:
//

unsigned
   value2 = function(1);

//
// Initialization of a const non-static variable is
// constexpr-evaluated:
//

unsigned const
   value3 = function(1);

//
// value2 is not constant evaluated, so neither is
// value4:
//

unsigned
   value4 = function(value0);

::std::cout << value0                     // 1
            << " "
            << value1                     // 1
            << " "
            << value2                     // 2
            << " "
            << value3                     // 1
            << " "
            << value4                     // 2
            << ::std::endl
               ;
```
