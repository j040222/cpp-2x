# Lambda Functions

`C++20` allows lambda functions with `auto` parameters, template lambdas (including template lambdas with concept constraints), and lambdas with variadic template parameters:

Generic lambdas, with `auto` parameters:

```c++
auto
   generic_lambda =
      [] (auto first, auto second)
      {
         return
            first * second ;
      }
      ;

{

int
   input_0 = 1
      ,
   input_1 = 2;

generic_lambda(input_0, input_1);

}

{

unsigned
   input_0 = 1
      ,
   input_1 = 2;

generic_lambda(input_0, input_1);

}
```

Template lambdas:

```c++
auto
   template_lambda =
      []
      <typename T>
      (T first, T second)
      {
         return
            first * second ;
      }
      ;

{

int
   input_0 = 1
      ,
   input_1 = 2;

template_lambda(input_0, input_1);

}

auto
   template_lambda2 =
      []
      <typename T>
      (T first, auto second)
      {
         return
            first * second ;
      }
      ;

{

int
   input_0 = 1
      ,
   input_1 = 2;

//
// Has 2 template parameters:
//

template_lambda2 (input_0, input_1);

}
```

Template lambdas with concept constraints:

```c++
auto
   concept_lambda =
      []
      <::std::floating_point T>
      (T first, T second)
      {
         return
            first * second ;
      }
      ;

auto
   concept_lambda2 =
      []
      <typename T>
         requires ::std::floating_point<T>
      (T first, T second)
      {
         return
            first * second ;
      }
      ;

{

double
   input_0 = 1.
      ,
   input_1 = 2.;

concept_lambda(input_0, input_1);

}
```

Lambdas with const reference capture:

```c++
auto
   const_capture_lambda =
      [&lambda_value = ::std::as_const(lambda_value)]
      (void)
      {
         return
            lambda_value ;
      }
      ;

const_capture_lambda();
```

Variadic lambdas:

```c++
auto
   variadic_lambda =
      []
      <typename... T>
      (T&& ... args)
      {
         return
            (args * ...)   // A "fold expression"
               ;
      }
      ;

variadic_lambda(1, 2, 3);
```

And mutable lambdas:

```c++
unsigned
   lambda_value = 2
      ;

//
// By default, the lambda operator() is const:
//

auto
   nonconst_capture_lambda =
      [=]
      (void) mutable
      {
         ++lambda_value;   // A copy
         
         return
            lambda_value ;
      }
      ;

nonconst_capture_lambda();

::std::cout << lambda_value << ::std::endl;  // Still 2
```
