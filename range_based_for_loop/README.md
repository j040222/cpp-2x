# Range-Based For Loops

Free `begin()`/`end()` functions are now preferred to member function `begin()`/`end()` functions if at least one of the latter does not exist.

```c++
//
// A structure that contains a begin() iterator function
// but not an end() function:
//

struct Object final
{
   ::std::vector
      <
      int
      >
      items_;
   
   typedef
      decltype( items_ )
      Vector
         ;
   
   Object(void)
      :
      items_{ 1, 2, 3 }
      { }
   
   typename
      Object::Vector::iterator
   begin(Object & object)
   {
      return object.items_.begin();
   }
}
;

//
// Free begin()/end() functions:
//

typename Object::Vector::iterator
begin(Object & object)
{
   return object.items_.begin();
}

typename Object::Vector::iterator
end(Object & object)
{
   return object.items_.end();
}

Object
   object;

//
// In this case, the free begin()/end() functions
// are used. Object::begin does exist, but there is no
// matching Object::end function, so the C++20 rule is
// to select the free functions:
//

for( auto item : object )
{
   ::std::cout << item << " ";
}

::std::cout << ::std::endl;
```
