# ::std::make_shared

`::std::shared_ptr` supports array types as of `C++17`. However, `::std::make_shared` did not until `C++20`.

```c++
//
// This feature does not yet appear to be implemented
// in g++ -std=c++20:
//

{

::std::shared_ptr
   <
   unsigned[][2]
   >
   array =
      ::std::make_shared
         <
         unsigned[][2]
         >
         ()
         ;

}

{

::std::shared_ptr
   <
   unsigned[3][2]
   >
   array =
      ::std::make_shared
         <
         unsigned[][2]
         >
         (3)
         ;

}
```
