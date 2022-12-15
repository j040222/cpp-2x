# Implicit Moves

Moves, rather than copies, are used more often in `C++20` than in `C++17`.

Return values can be moved rather than copied:

```c++
::std::unique_ptr <int>
function0( ::std::unique_ptr <int> && p )
{
   //
   // This is a copy in C++17:
   //
   
   return p;
}
```

So can thrown objects:

```c++
void
function1( ::std::unique_ptr <int> && p )
{
   //
   // This is a copy in C++17:
   //
   
   throw p;
}
```

And implicitly constructed function return values:

```c++
struct Object final
{
   ::std::unique_ptr <int>
      p_
         ;
   
   Object( ::std::unique_ptr <int> && p )
      :
      p_( ::std::move(p) )
      { }
   
   Object( Object const & ) = delete;
}
;

Object
function2(void)
{
   auto
      p = ::std::make_unique <int> (1);
   
   //
   // Moves an object of type Object:
   //
   
   return p;
}
```

And some casts:

```c++
struct AnotherObject final
{
   ::std::unique_ptr <int>
      p_
         ;
   
   AnotherObject
      (
      ::std::unique_ptr <int> && p
      )
      :
      p_( ::std::move(p) )
      { }
   
   operator Object() &&
   {
      return
         Object( ::std::move(p_) );
   }
   
   operator Object() const & = delete;
}
;

Object
function3(void)
{
   AnotherObject
      object
         (
            ::std::make_unique <int> (1)
         )
         ;
   
   //
   // Calls AnotherObject::operator Object() && (a move):
   //
   
   return object;
}
```

And some objects constructed from rvalue references:

```c++
struct Empty final { } ;

struct Object2 final
{
   Object2(Empty const &) = delete;
   
   Object2(Empty &&) { }
}
;

Object2
function4(void)
{
   Empty
      empty
         ;
   
   //
   // Moved:
   //
   
   return
      empty;
}
```
