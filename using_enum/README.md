# Using Enum

In `C++20` `using enum` is allowed. Enum values do not need to be prefixed with the enum class name in the same block as `using enum`:

```c++
enum class Colour : unsigned
{
   RED,
   GREEN,
   BLUE
}
;

int main(int argc, char ** argv)
{
   Colour const
      colour = Colour::BLUE
         ;
   
   using enum Colour;
   
   switch( colour )
   {
   case( RED ):
      ::std::cout << "red" << ::std::endl
         ;
      break;
   case( GREEN ):
      ::std::cout << "green" << ::std::endl
         ;
      break;
   case( BLUE ):
      ::std::cout << "blue" << ::std::endl
         ;
      break;
   }
   
   return 0;
}
```
