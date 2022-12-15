# Operator Delete

`C++20` adds an alternative overload for class member delete. The overload accepts a tag, `::std::destroying_delete_t`, as its second argument. If the
overload exists then it is responsible for calling the class destructor (unlike the previous version without the tag, which is not required to call the destructor).

```c++
struct U final
{
   ~U(void)
   {
      ::std::cout << "~U()" << ::std::endl;
   }
   
   void operator delete (void * p)
   {
      ::std::cout << "U::operator delete" << ::std::endl;
      
      ::operator delete(p);
   }
}
;

struct V final
{
   ~V(void)
   {
      ::std::cout << "~V()" << ::std::endl;
   }
   
   void operator delete(V * p, ::std::destroying_delete_t)
   {
      ::std::cout << "V::operator delete" << ::std::endl;
      
      ::operator delete(p);
   }
}
;
```

This calls `~U` then calls `U::operator delete` (because it exists), which in turn calls `::operator delete`:

```c++
delete new U;
```

Note that "delete new" is not the same as `::delete new`. The latter does not call the member function:

```c++
::delete new U;
```

This does not call `~V` unless `V::operator delete` does:

```c++
delete new V;
```
