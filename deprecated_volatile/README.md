# (Partially) Deprecated Volatile

`C++20` deprecates some uses of `volatile`, and some uses of volatile variables. In particular, the following are deprecated:

   * Compound assignment and pre/post increment (decrement) operators;
   * volatile qualification of function parameters and returned types.

`volatile` is a hint the implementation to avoid aggressive optimizations (involving volatile objects) because the affected objects might be changed in ways that the implementation can't detect. If you load twice from a volatile variable you cannot assume the value to be the same both times. If a volatile object is large, you can also observe 'memory tearing': another thread can
observe half of a store occuring.

Colloquially, volatile also means that operations are not guaranteed to be
synchronized: volatile instructions may occur in order in function assembly, but another thread may not observe them in that order because the hardware does not guarantee it.

The idea behind volatile is that expressions like this:

   `int a = x; int b = x;`

should load twice from `x`, not (eg.) load `x` once into a register and then use that register twice.

Volatile is also used where a thread sets the value of a variable which another thread waits for. If the variable isn't declared volatile, then the compiler may make an adverse optimization that assumes the variable is
unchanged on the running thread. For example, if this code is compiled with `-O3`, the compiler *might* assume that "finished" is never assigned to by the parent thread, so thes loop is "optimized" to: `while( true ) { }`, and the program never exits. Something very similar can with happen signal handlers.

```c++
bool finished = false;

void function(void)
{
   finished = true;
   
   return;
}

int main(int argc, char ** argv)
{
   ::std::thread
      thread( &function );
   
   while( not finished )
   {
      continue;
   }
   
   thread.join();
   
   return 0;
}
```

Volatile does not always do what you expect. For example, does this touch the (volatile) first member of the struct? Most hardware does not have the ability to do bitwise addressing:

```c++
struct Bitfield
{
   volatile int first : 4;
   int second : 4;
}
;

Bitfield
   bitfield;

bitfield.second = 1;
```

Does this load and then store, or does it only modify the memory once:

```c++
volatile
   int i;

i += 1;
```

Ie. is it atomic, or is it equivalent to:

```c++
int temporary = i;
temporary = temporary + 1;
i = temporary;
```

And what does this do?

```c++
volatile int x = 1;

x++;
```

If the compiler has an atomic increment instruction on a memory location, this might be unaffected by volatile. Most compilers load x into a register, increment x there and then write x back again.

If you have a function with a volatile parameter (or a volatile return value) it means literally nothing. The mangled function name is exactly the same without the volatile keyword. Volatile was therefor deprecated for function return type and parameter types. Note that volatile parameters only apply within the function, they don't express anything to the caller:

```c++
volatile int function(volatile int input)
{
   return
      input;
}
```

The following actions on volatile variables are also deprecated:

```c++
volatile int
   p = 1;

int q = 0, q2 = 0;

//
// Deprecated actions:
//

++p; p++; p += 1; q = p = q2;

//
// And compound expressions, such as clearing bits in
// registers:
//

p |= 0x3; p &= 0x3;
```

