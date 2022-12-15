# Addition of consteval

Consteval functions can be called in `C++` code where all of the arguments are constant expressions, but not if any of the arguments are non-constant. They are called 'immediate functions': every call to the function must produce a compile-time constant expression. Variables cannot be declared consteval.


```c++
//
// Examples of consteval and constexpr functions:
//

consteval
int
consteval_factorial(int n)
{
   if(n <= 0)
   {
      return 1;
   }
   
      //
      // Note that consteval_factorial is technically being
      // using with a non-const argument here, but in this
      // context the expression is allowed:
      //
   
   return
      n * consteval_factorial(n - 1);
}

constexpr
int
constexpr_factorial(int n)
{
   if(n <= 0)
   {
      return 1;
   }
   
   return
      n * constexpr_factorial(n - 1);
}
```

`consteval` differs from `constexpr` in that `consteval` must evaluate at compile time. The arguments of a `consteval` function must all be constants. `constexpr` functions, on the other hand, can be evaluated at runtime.

```c++
int main(int argc, char ** argv)
{
   {
   
   static constexpr int
      value = constexpr_factorial(5)
         ;
   
   ::std::cout << value
               << ::std::endl
                  ;
   
   }
   
   consteval_factorial(5);   // Allowed
   
   //
   // Consteval and constexpr functions can both be used
   // with static_assert:
   //
   
   static_assert
      (
         consteval_factorial(5) == 120
      )
      ;
   
   /*
   
   {
   
   int
      arg = 0
         ;
   
   consteval_factorial(arg); // Not allowed: arg is not
                             // const
   
   }
   
   */
   
   {
   
   //
   // Calling a constexpr function with non-const runtime
   // arguments is however allowed:
   //
   
   int
      arg = 0
         ;
   
   constexpr_factorial(arg); // Allowed
   
   }
   
   return 0;
}
```


