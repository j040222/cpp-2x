# Implicit Lambda Capture

In `C++20`, lambda functions can be used in default-initialized class members. Some compilers would accept this in `C++17`.

```c++
struct A
{
   int
      x{1};
   
   int
      y = [this] { return (x + 1); } ();
}
;
```

```c++
A
   object;

::std::cout << object.y << ::std::endl;         // 2
```

Some variables are also implicitly captured even in constexpr contexts:

```c++
auto
   p = ::std::make_unique <unsigned> ();

auto
   lamda =
      [=] (void)
      {
         //
         // p is captured in this context despite
         // the constexpr and the typeid. sizeof(p),
         // however, doesn't capture p.
         //
      
         if constexpr (false)
         {
            typeid( p );
         }
      }
      ;

lamda();
```
