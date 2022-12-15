# Addition of constinit

`constinit` can be used to initialize variables at compiletime:

```c++
int
function(void)
{
   //
   // Unlike 'static int', this is initialized at compile
   // time:
   //
   
   static constinit int
      value = 7;
   
   return
      value
         ;
}
```

`constexpr` classes can also be initialized at compile time:

```c++
struct Object
{
   int
      value_;
   
   constexpr
      Object(int value) :
      value_(value)
         { }
   
   ~Object(void) { }
}

Object
function2(void)
{
   //
   // Object::Object is constexpr, so this is also allowed:
   //
   
   static const constinit Object
       value(7);
   
   //
   // Note that const constinit is not the same as
   // constexpr, because constexpr requires constant
   // destruction.
   //
   
   //
   // Not allowed: ~Object is not constexpr:
   //
   
   // static constexpr Object
   //    value(7);
   
   return
      value
         ;
}
```

Note that non-const `constinit` objects can be modified:

```c++
Object
function3(void)
{
   static constinit Object
      value(7);
   
   ++value.value_;
   
   return
      value
         ;
}
```

```c++
int main(int argc, char ** argv)
{
   ::std::cout << function()
               << ::std::endl                // 7
                  ;
   
   ::std::cout << function2().value_
               << ::std::endl                // 7
                  ;
   
   ::std::cout << function3().value_
               << ::std::endl                // 8
                  ;
   
   return 0;
}
```
