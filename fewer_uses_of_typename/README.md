# Fewer uses of Typename

In `C++20` the keyword `typename` is no longer required in many cases, including:

When defaulting a template parameter, and in the return type of a function declaration or definition:

```c++
struct U
{
   static constexpr int name = 1;
   
   typedef int type;
}
;

template
   <
   typename V = U::type
   >
U::type
function
   (
   U::type
      argument = U::name
   )
{
   return argument;
}
```

In class scoped function definitions and class-scoped typedefs:

```c++
struct S
{
   U::type function(U::type = U::name)
   {
      return U::name;
   }
   
   U::type object;
   
   typedef U::type type;
}
;
```

In `static_cast <>`, and similar (eg. `cont_cast`):

```c++
static_cast < U::type > (1);
```

In using directives:

```c++
using Type0 = U::type;

typedef U::type Type1;
```

and in lambda function arguments:

```c++
auto
   lambda =
      []
      < typename V >
      (V::U argument = V::name)
      -> V::U
      {
         return
            V::name;
      }
      ;
```

