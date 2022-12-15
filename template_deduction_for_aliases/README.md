# Template Deduction for Aliases

In `C++20` template parameter deduction works even if the type is an alias of another template type. In `C++17` alias template deduction was not supported:

```c++
template
   <
   typename T1,
   typename T2
   >
struct U
{
   U(T1 const &, T2 const &) { }
}
;

template
   <
   typename T1
   >
using V = U<T1, int>;

int main(int argc, char ** argv)
{
   V item( 1, 2. );
   
   return 0;
}
```
