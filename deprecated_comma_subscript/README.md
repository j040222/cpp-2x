# Deprecated Comma Subscript

Comma operators in subscript expressions were deprecated in C++20:

```c++
struct A
{
   /*
   
   //
   // In future the [] operator may be extended as follows:
   //
   
   int operator[] (int first, int second, int third)
   {
      return
         (
            first * second * third
         )
         ;
   }
   
   */
   
   int operator[] (int value)
   {
      ::std::cout << value << ::std::endl;
      
      return value;
   }
}
;
```

```c++
int main(int argc, char ** argv)
{
   A
      object;
   
   object[ 0, 1, 2 ];   // object[2] in C++17, deprecated in
                        // C++20
   
   object[ (0, 1, 2) ]; // object[2] in both cases
   
   return 0;
}
```
