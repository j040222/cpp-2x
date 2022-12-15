# Newed Array Size Deduction

In `C++20` the size of newed arrays is deduced, in the same
way that arrays on the stack have deduced sizes:

```c++
int main(int argc, char ** argv)
{
   int p0[] { 1, 2, 3 };
   
   int * p1 = new int[3] { 1, 2, 3 };
   int * p2 = new int[] { 1, 2, 3 };            // Deduced
   
   //
   // Alternatively:
   //
   
   int * p1_b = new int[3] ( 1, 2, 3 );
   int * p2_b = new int[] ( 1, 2, 3 );          // Deduced
   
   //
   // This also works with strings:
   //
   
   char * p3 = new char[5] { "test" };
   char * p4 = new char[] { "test" };           // Deduced
   
   return 0;
}
```

