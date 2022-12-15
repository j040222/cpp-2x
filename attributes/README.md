# New Attributes

`C++20` adds several new attributes including `[[likely]]`, `[[unlikely]]` and 
`[[no_unique_address]]`.

An example of a function that uses "likely" and "unlikely" code pathways:

```c++
int
factorial(int n)
{
   if( n > 0 ) [[likely]]
   {
      return n * factorial(n - 1);
   }
   else [[unlikely]]
   {
      return 1;
   }
}
```

In `C++20`, `[[nodiscard]]` also accepts an optional message (which is generally displayed by the compiler in warnings):

```c++
[[nodiscard("Do not discard return value")]]
int
no_discard_function(void)
{
   return 1;
}
```

`[[no_unique_address]]` can be used to modify the bytes occupied by class members:

```c++
struct First final
{
   char
      c;
   EmptyObject
      e;
}
;

struct Second final
{
   char
      c;
   [[no_unique_address]] EmptyObject
      e;
}
;

struct Third final
{
   char
      c[2];
   [[no_unique_address]] EmptyObject
      e1, e2;
}
;
```

In the above examples `First::e` receives a unique address even though it's empty, which means that `sizeof(First) != sizeof(First::c)`:

```c++
static_assert
   (
      sizeof(First)
      
      >=
      
      sizeof(First::c) + sizeof(First::e)
   )
   ;
```

And the compiler is allowed to overlap the addresses of `c` and `e`:

```c++
static_assert
   (
      sizeof(Second)
      
      ==
      
      sizeof(Second::c)
   )
   ;

{

Second
   object{ }
      ;

assert
   (
      static_cast <void*> (&object.c)
      
      ==
      
      static_cast <void*> (&object.e)
   )
   ;

}
```

In this case `e1` and `e2` are not allowed to share the same address because they have the same type. `e1` can however share an address with `c[0]` and `e2` can (but may not) share an address with `c[1]`.

```c++
static_assert
   (
      sizeof(Second)
      
      ==
      
      sizeof(Second::c)
   )
   ;

{

Third
   object{ }
      ;

static_assert
   (
      sizeof(Third) >= 2
   )
   ;

}
```



