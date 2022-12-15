# Non-Type Template Parameters

`C++20` allows some additional non-type template parameters. Non-type template parameters must be "structural types", which include lvalue references (to objects or functions), integral types, pointer types, pointer-to-member types, enumerations, and (since `C++20`) `nullptr_t`, floating-point numbers, and - broadly speaking - class types that consist of all-public base classes and all-public members all of which are structural types or arrays of the same.

```c++
template
   <
   auto T
   >
class A { };

struct B
{
   float
      value;
}
;

template
   <
   B T
   >
void
template_function(void)
{
   //
   // In C++20, T can be the type of a class object. The
   // address of the object can be taken, and it is the same
   // for equivalent types:
   //
   
   ::std::cout << &T << ::std::endl;
}
```

```c++
//
// Note that it is possible to interact with the template
// objcet:
//

template
   <
   ::std::array
      array
   >
constexpr
auto
sum(void)
{
   return
      ::std::accumulate
         (
         array.cbegin()
            ,
         array.cend()
            ,
         0
         )
         ;
}
```

Many other uses of template type parameters are allowed:

```c++
A <nullptr>
   a1;

{
A <1.02f>
   a2;

A <1.03f>
   a3;

static_assert
   (
   !::std::is_same_v <decltype(a2), decltype(a3)>
   )
   ;

}

struct T
{
   unsigned
      u;
   
   float
      f;
}
;

constexpr T const
   t { 0u, 1.0f };
```

In this example, `decltype(a4)` is the same as any other `A<T>` for which
`T::u` is `0u` and `T::f` is `1.0`

```c++
A <t>
   a4;
```

Template parameters can also be enums:

```c++
enum class E : unsigned
{
   FIRST = 0
      ,
   SECOND = 1
      ,
   THIRD = 1
}
;

A <E::FIRST>
   a5;

A <E::SECOND>
   a6;

static_assert
   (
   !::std::is_same_v <decltype(a5), decltype(a6)>
   )
   ;

//
// The template parameter is compared bitwise, so
// A <E::THIRD> is the same type as A <E::SECOND>:
//

A <E::THIRD>
   a7;

static_assert
   (
   ::std::is_same_v <decltype(a6), decltype(a7)>
   )
   ;
```

```c++
constexpr B
   b1 { 1 };

template_function
   <
   b1
   >
   ();
```

When using a union, the active member must be the same and the active members must be template-argument equivalent:

```c++
union Union
{
   unsigned
      first;
   
   unsigned
      second;
}
;

constexpr Union
   u1 { .first = 1u }
      ,
   u2 { .second = 1u }
      ;

static_assert
   (
   !
   ::std::is_same_v
      <
      A<u1>
         ,
      A<u2>
      >
   )
   ;
```

Array template parameters are also allowed:

```c++
static_assert
   (
      sum < { 1, 2, 3 } > () == 6
   )
   ;
```

And pointer template arguments are allowed:

```c++
{

struct C final
{
   int
      array[3] = { 1, 2, 3 };
}
;

constexpr
   int const
      (C::*p) [3] = &C::array;

A < p >  // Allowed
   a2;

}
```
