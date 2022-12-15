# Ranges

Ranges is "STL v2". It is a drop-in replacement for many of the components of the STL library.

There are major differences between ranges and pre-ranges code. These include (but are not limited to):

   * Ranges use C++20 concepts to enforce conditions. This greatly improves the clarity of error messages in template code.
   * A range is itself a concept: it is a type that supports `::std::ranges::begin(object)` and `::std::ranges::end(object)`. The type of the end iterator need not be the same as the iterator type returned by `begin()` -- they need only be comparable. This allows, among other things, for infinite ranges: use `::std::unreachable_sentinel` for an iterator that never compares positively with another range iterator.
   * Many algorithms, eg. `::std::ranges::sort`, accept a reference to a range container, not just a pair of `begin`/`end` iterators.

Examples:

```c++
//
Sort a container:
//

::std::vector<int>
   items;

::std::ranges::sort( items );
```

The ranges sort function (like other functions in ranges) accepts a 'projection operator'. A projection operator is a unary invokable object. "invokable" in this context means either a univariate callable object, a pointer to a class/struct member, or a pointer to a getter function (accepting no arguments) in a class.

```c++
::std::vector
   <
   Person
   >
   items;

//
// Sort the container by ID string:
//

::std::ranges::sort( items, { }, &Person::id_ );

//
// Sort the container by salary:
//

::std::ranges::sort( items, { }, &Person::salary );

//
// Sort the container using a custom lambda expression:
//

::std::ranges::sort
   (
   items
      ,
   { }
      ,
   [] (auto const & item)
      {
         return
            item.id_.size() + item.salary_;
      }
   )
   ;
```

Views are an important aspect of ranges. Views are ranges that are cheap to copy and move. In general views do not own the elements they are viewing, so they can be moved and copied in constant time.

Views are composable. This example drops the last four elements of a range:

```c++
namespace views = ::std::ranges::views;

::std::vector<int>
   items { 1, 2, 3, 4, 5, 6, 7 };

{

//
// ::std::ranges::reverse_view can also be used in
// place of ::std::ranges::views::reverse, and likewise
// for drop:
//

auto
   view =
      views::reverse( views::drop( views::reverse( items ), 3 ) );

for( int v : view )
{
   ::std::cout << v << " ";
}

::std::cout << ::std::endl;

}
```

Note that the above is also equivalent to views::take:

```c++
{

auto
   view =
      views::take( items, 4 );

for( int v : view )
{
   ::std::cout << v << " ";
}

::std::cout << ::std::endl;

}
```

Views support an alternative pipe `|` syntax, as follows. Note that order is reversed when using the pipe operator:

```c++
auto
   view =
      items | views::reverse | views::drop(3) | views::reverse;

for( int v : view )
{
::std::cout << v << " ";
}

::std::cout << ::std::endl;
```

Since views generally don't own the range they refer to, views can generate the items that they are a view of:

```c++
auto
   view =
      views::iota(1, 8)
         | views::reverse
         | views::drop(3)
         | views::reverse
            ;

for( int v : view )
{
   ::std::cout << v << " ";
}

::std::cout << ::std::endl;
```

And, since ranges can be infinite, so can views:

```c++
auto
   view =
      views::iota(1)
         | views::take(7)
         | views::reverse
         | views::drop(3)
         | views::reverse
            ;

for( int v : view )
{
   ::std::cout << v << " ";
}

::std::cout << ::std::endl;
```

There are many other view types in the ranges library, for example:

Conditionally drop matching elements using a univariate function until the first non-matching element:

```c++
auto
   view =
      text | views::drop_while( ::isspace );

for( auto const & c : view )
{
   ::std::cout << c;
}

::std::cout << ::std::endl;
```

Transform elements using a univariate function:

```c++
auto
   view = text | views::transform( ::toupper );

for( char const & c : view )
{
   ::std::cout << c;
}

::std::cout << ::std::endl;
```

Conditionally extract matching elements using a univariate function until the first non-matching element:

```c++
auto
   view =
      text
         | views::drop_while( ::isspace )
         | views::take_while( ::isalnum )
            ;

for( auto const & c : view )
{
   ::std::cout << c;
}

::std::cout << ::std::endl;
```

Typically, views do not change the mutability of the objects that they are views of. So, in a range-for loop, the underlying data can be modified:

```c++
::std::vector<int>
   items { 1, 2, 3, 4, 5, 6, 7 };

auto
   view =
      items
         | views::filter([] (auto v) { return v % 2 == 1; } );

for( auto & v : view )
{
   v *= -v;
}

for( int v : items )
{
   ::std::cout << v << " ";
}

::std::cout << ::std::endl;
```

Views can also be used to join together multiple other ranges:

```c++
::std::vector <int> const
   elements[] { { 1, 2 }, { 3, 4 }, { 5, 6 } };

auto
   joined = views::join( elements );

for( int v : joined )
{
   ::std::cout << v << " ";
}

::std::cout << ::std::endl;
```

Views can also be used to split one view into members:

```c++
::std::vector <int>
   items { 1, 2, 3, 4, 3, 2, 1, 2, 3, 4, 3, 2, 1 };
      ;

auto
   separated = views::split( items, 2 );

for( auto const & subrange : separated )
{
   for( auto const & element : subrange )
   {
      ::std::cout << element << " ";
   }
}

::std::cout << ::std::endl;
```

Other applications include extracing the Nth element from a range of tuple-like elements:

```c++
::std::vector
   <
   ::std::tuple< int, char >
   >
   const
      items
         {
            { 1, 'a' },
            { 2, 'b' },
            { 3, 'c' }
         }
         ;
   
for( auto const & element : items | views::elements<1> )
{
   ::std::cout << element << " ";
}

::std::cout << ::std::endl;

//
// Alternatively:
//

for( auto const & element : items | views::values )
{
   ::std::cout << element << " ";
}

::std::cout << ::std::endl;

//
// And, for first tuple elements only:
//

for( auto const & element : items | views::keys )
{
   ::std::cout << element << " ";
}

::std::cout << ::std::endl;
```

