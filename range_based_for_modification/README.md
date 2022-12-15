# Range-Based For Modification

An additional variable is allowed in `C++20` range-based for loops:

```c++
::std::vector <int> const
   container{ 1, 2, 3 }
      ;

for(
         //
         // An additional variable is allowed here in
         // c++20:
         //
      ::std::size_t
         counter(0u)
            ;
      auto const &
         p : container
   )
{
   ++counter;
   
   continue
      ;
}
```
