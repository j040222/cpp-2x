# Nested Inline Namespaces

In `C++20` the `inline` keyword is allowed in nested namespace definitions. Functions in `inline` namespaces are referenced as if they were declared in the nearest upward non-inlined namespace.

Inlined namespaces can be used for versioning purposes. For example, if you have two versions of a class in separate namespaces, then one of the classes can be made the 'default' version by inlining its enclosing namespace.

```c++
namespace A
{
namespace B
{
inline namespace C
{
inline namespace D
{

void function(void);

}
}
}
}

namespace A::B::inline C::inline D
{

void function(void) { }

}

int main(int argc, char ** argv)
{
   A::B::function();
   
   return 0;
}
```
