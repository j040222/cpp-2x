# Spaceship Operator

The 'spaceship operator', `<=>`, is a class-based comparison operator which, for objects `A` and `B`, determines whether `A < B`, `A == B` or `A > B`. The spaceship operator works in much the same way as `strcmp`: `< 0` means "`A < B`", `== 0` means "`A == B`" and `> 0` means "`A > B`". Related operators such as `operator==`, `!=`, `>`, `>=`, `<`, `<=` are automatically generated, depending on what is explicitly defaulted.

```c++
//
// <compare> is required to declare operator <=>:
//

#include <compare>

struct Point
{
   int
      x,
      y
      ;
   
   //
   // If <=> is defaulted then ==, !=, >, >=, < and <=
   // are all automatically generated too.
   //
   // If <=> is not defaulted, == is not automatically
   // defaulted:
   //
   
   auto operator <=> (Point const & other) const = default;
   
   //
   // The above is usually:
   //
   
   //
   // ::std::strong_ordering
   //    operator <=> (Point const & other) const = default;
   //
   
   //
   // Note that 'operator== = default' was not allowed
   // before C++20.
   //
}
;
```

```c++
struct Point2
{
   int
      x,
      y
      ;
   
   bool operator== (Point2 const & other) const
   {
      return
         (
            ( this->x == other.x )
            
            and
            
            ( this->y == other.y )
         )
         ;
   }
   
   //
   // operator!= is automatically generated.
   //
}
;
```

```c++
struct Point3
{
   int
      x,
      y
      ;
   
   bool operator== (Point3 const & other) const
   {
      return
         (
            ( this->x == other.x )
            
            and
            
            ( this->y == other.y )
         )
         ;
   }
   
   //
   // Comparing unrelated types:
   //
   
   //
   // Automatically generates != and == for all combinations
   // (lhs/rhs) of Point3 and Point2:
   //
   
   bool operator== (Point2 const & other) const
   {
      return
         (
            ( this->x == other.x )
            
            and
            
            ( this->y == other.y )
         )
         ;
   }
}
;
```

```c++
struct Point4
{
   int
      x,
      y
      ;
   
   //
   // Explicit instantiation:
   //
   
   ::std::strong_ordering
      operator<=> (Point4 const & other) const
   {
      if ( auto cmp = y <=> other.y; cmp != 0 )
      {
         return
            cmp;
      }
      
      return ( x <=> other.x )
         ;
   }
}
;
```

Usage examples are as follows:

```c++
Point const
   first { .x = 1, .y = 2 },
   second { .x = 2, .y = 3 }
      ;

assert
   (
      //
      // Performs a lexicographical ordering with
      // Point::x taking precedence over Point::y:
      //
      
      first < second
   )
   ;
```

`<=>` returns an object that can be compared with `0`. If it is an ordering -- if `Point` naturally supports `<` -- then `<=>` is an object that can be compared with 0 in 3 ways. Otherwise, `<=>` is an object that can be compared with 0 ('equal' or 'equivalent') and 1 ('not equal' or 'not equivalent'):

The type of (`first <=> second`) depends on the structure of the `Point` class. In this case it is a `strong_ordering` object.

```c++
auto
   compared = first <=> second
      ;

if( compared < 0 )
{
   //
   // first < second:
   //
}
else if( compared > 0 )
{
   //
   // first > second:
   //
}
else
{
   //
   // first and second compared equal:
   //
}

Point2 const
   third { .x = 3, .y = 4 }
   ;

assert
   (
      //
      // != is automatically generated:
      //
      
      ! ( third != third )
   )
;
```

In `C++20` the compiler is allowed to rewrite and synthesize equivalent expressions out of the comparison operators. For example, when searching for
operators that match

```c++
   a < b
```

the compiler also searches for operators that match:

```c++
   ( a <=> b ) < 0      "rewritten"
```

and:

```c++
   0 < ( a <=> b )      "synthesized"
```

`==` does not get rewritten in terms of `<=>`. If `<=>` is defaulted then a separate (efficient) `==` is generated. This is so that objects like strings can be efficiently compared. When performing overload resolution in `C++20`, non-rewritten non-synthesized expressions are preferred if they can be used.

Rewritten expressions include the order of arguments to `==`, and using `!(==)` instead of `!=`, if they are defaulted.

`<=>` returns something similar to an enum:

```c+++
    enum class weak_ordering
    {
       less = -1,
       equivalent = 0,
       greater = 1
    }

    enum class strong_ordering
    {
       less = -1,
       equal = 0,
       equivalent = 0,
       greater = 1
    }
    
    enum class partial_ordering
    {
       less = -1,
       equal = 0,
       equivalent = 0,
       greater = 1
       and unordered
    }
```

with comparison to 0.

Note that floating-point comparison using `<=>` is a partial ordering. This is because floats can be (eg.) `NaN`.


