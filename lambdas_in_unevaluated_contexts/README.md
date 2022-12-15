# Lambdas in Unevaluated Contexts

Declaring typedef of a stateless lambda is allowed in `C++20` (this is a lambda in an 'unevaluated context'):

```c++
typedef
   decltype
      (
      []
         (
         auto const &
            first
               ,
         auto const &
            second
         )
         -> bool
         {
            return first.size() < second.size();
         }
      )
   lambda_type
      ;

::std::cout << typeid(lambda_type).name()
            << ::std::endl
               ;
```

Lambdas can now also be default-constructed, (eg. by a multiset, which uses it for comparison purposes):

```c++
using
   custom_set =
      ::std::multiset
         <
         ::std::string
            ,
         lambda_type
         >
         ;

custom_set const
   set { "first", "second", "third" }
      ;

for( auto const & p : set )
{
   ::std::cout << p << ::std::endl
      ;
   
   continue
      ;
}
```

A stateless lambda can also be copy assigned:

```c++
typedef
   decltype
      (
      []
         (
         ::std::string const &
            first
               ,
         ::std::string const &
            second
         )
         -> bool
         {
            return
               true
                  ;
         }
      )
   lambda_type_1
      ;

lambda_type_1
   assigned_lambda_1{ }
      ,
   assigned_lambda_2 = assigned_lambda_1
      ,
   assigned_lambda_3( assigned_lambda_2 )
      ;
```
