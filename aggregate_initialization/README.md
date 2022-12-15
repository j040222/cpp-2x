# Aggregate Initialization

In `C++20`, aggregate class types cannot have user-declared constructors. This includes user-deleted constructors, constructors that are declared default, and any user-provided constructor.

In particular, none of the following classes are aggregates in `C++20`:

```c++
struct A1
{
   unsigned
      value[2];
   
   A1(void) = delete;
}
;

struct A2
{
   unsigned
      value[2];
   
   A2(void) = default;
}
;
```

This is also not an aggregate in `C++17`:

```c++
struct A3
{
   unsigned
      value[2];
   
   A3(void) { }
}
;
```

In `C++20`, aggregate initialization is not allowed for any of the above types. In `C++17`, aggregate initialization was allowed for the first two.

```c++
int main(int argc, char ** argv)
{
   {
   
   A1 const
      a1{ 1u, 2u };                       // c++20 error
   
   }
   
   {
   
   A2 const
      a2{ 1u, 2u };                       // c++20 error
   
   }
   
   return 0;
}
```

