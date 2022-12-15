# `constexpr` Default Initialization

In `C++17`, `constexpr`-constructed objects must initialize all of their non-static data members. In `C++20` this was relaxed. In `C++20`, not all members need to be initialized by the constructor, but reading (using) uninitialized members in constexpr contexts in an error.

```c++
struct WithDefaultInitialization
{
   unsigned
      value0 = 1u
         ,
      value1 = 2u
         ;
}
;

struct WithoutDefaultInitialization
{
   unsigned
      value0 = 1u
         ,
      value1
         ;
}
;

template
   <
   typename
      T
   >
constexpr
T
default_construct_object(void)
{
   //
   // constexpr-instantiating a class with default-
   // initialized members is allowed in C++20:
   //
   
   T t;
   
   return
      t;
}
```

This is an error in `C++17`, but not in `C++20`, because `WithoutDefaultInitialization` does not initialize all of its members:

```c++
constexpr
   auto
      a =
         default_construct_object
            <
            WithoutDefaultInitialization
            >
            ()
            ;
```

This is not an error, even in `C++17`: `WithDefaultInitialization` initializes all of its members:

```c++
constexpr
   auto
      b =
         default_construct_object
            <
            WithDefaultInitialization
            >
            ()
            ;
```

```c++
template
   <
   typename
      T
   >
constexpr
auto
use_uninitialized_member(void)
{
   T object;
   
   //
   // object.value1 is uninitialized. In C++20 the compiler
   // can detect this and raises an error:
   //
   
   object.value0 = object.value1;
   
   return
         
         //
         // Contains whatever object.value1 contained, which
         // is uninitialized:
         //
         
      object.value0
         ;
}
```

An error in `C++20` because `WithoutDefaultInitialization::value1` is used uninitialized:

```c++
constexpr
   auto
      value =
         use_uninitialized_member
            <
            WithoutDefaultInitialization
            >
            ()
            ;
```

Whereas this is not an error in `C++20`:

```c++
constexpr
   auto
      value =
         use_uninitialized_member
            <
            WithDefaultInitialization
            >
            ()
            ;
```
