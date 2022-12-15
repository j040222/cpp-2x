# Pointer To Member

Prior to `C++20`, `const&`-qualified member functions could not be used as function pointers on rvalue objects (`P0704R1`):

```c++
struct A final
{
   void function(void) const &
   {
      ::std::cout << "function" << ::std::endl;
   }
}
;

int main(int argc, char ** argv)
{
   void (A::* pointer) (void) const & = &A::function;
   
   ( ( A {} ).*pointer ) ();
   
   //
   // Technically this was not allowed prior to c++20:
   //
   
   ( ( A {} ).*&A::function ) ();
   
   ( ( A {} ).function() );
   
   return 0;
}
```
