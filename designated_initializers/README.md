# Designated Initializers

`C++20` adds named initializers for structs, classes and unions.

```c++
struct Time
{
   unsigned
      hour
         ;
   
   unsigned
      minute
         ;
   
   double
      seconds
         ;
}
;

enum class Month : unsigned
{
   JANUARY,
   FEBRUARY,
   MARCH
      
      //
      // ..
      //
}
;

enum class Day : unsigned
{
   MONDAY,
   TUESDAY,
   WEDNESDAY
      
      //
      // ..
      //
}
;

struct Date
{
   Time
      time
         ;
   
   Month
      month
         ;
   
   Day
      day
         ;
}
;

union Union
{
   int
      first
         ;
   
   ::std::size_t
      second
         ;
}
;
```

When instantiating, the initialization order must be the same as the declaration order:

```c++
{

Date const
   date
      {
      .time { .hour = 15, .minute = 32, .seconds = 12 }
         ,
         //
         // = and { } are both valid:
         //
      .month = Month::FEBRUARY
         ,
      .day { Day::MONDAY }
      }
      ;

}

//
// Designated initializers can also initialize unions:
//

Union const
   object
      {
      .second = ::std::size_t(1)
      }
      ;

{

Date const
   date
      {
         //
         // hour is 
         //
      .time { .minute = 32 }
         ,
      .month = Month::FEBRUARY
         ,
      .day { Day::MONDAY }
      }
      ;

}
```
