# Bitfields

`C++20` provides a new syntax for initializing bitfields without using constructors:

```c++
struct Bitfield0
{
   int
      a_ : 2,
      b_ : 2;
   
   Bitfield0(void)
      :
      a_{ 2 },
      b_{ 3 }
      { }
}
;
```

The following (`Bitfield1`) has the same default values as `Bitfield0`, without using a constructor:

```c++
struct Bitfield1
{
   int
      a_ : 2 { 2 },
      b_ : 2 = 3;
}
;

#include <cassert>

int main(int argc, char ** argv)
{
   Bitfield0
      first;
   
   Bitfield1
      second;
   
   assert( first.a_ == second.a_ );
   
   assert( first.b_ == second.b_ );
   
   return 0;
}
```


