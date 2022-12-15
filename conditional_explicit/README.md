# Conditionally Explicit Constructors

In `C++20` constructors can be conditionally explicit:

```c++
template
   <
   typename
      T
   >
class Object final
{
public:
   
      //
      // Explicit if T is convertible to ::std::string,
      // otherwise not:
      //
   
   explicit
      (
      not ::std::is_convertible_v <T, ::std::string>
      )
      Object
         (
         T value
         )
      { }
      ;
}
;

int main(int argc, char ** argv)
{
   {
   
   char
      string[7] = "string";
   
   Object <char [7]>
      object = string
         ;
   
   }
   
   {
   
   Object <::std::string>
      object = ::std::string("string")
         ;
   
   }
   
   {
   
   //
   // Not allowed: int is not convertible to ::std::string,
   // the constructor is explicit:
   //
   
   //
   // Object
   //   object = 1
   //      ;
   //
   
   Object <int>
      object2( 1 )
         ;
   
   }
   
   return 0;
}
```


