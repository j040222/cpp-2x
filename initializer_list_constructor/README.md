# Initializer List Constructors

In `C++20` this expression is an instance of `::std::vector<int>`. In `C++17`, technically, it could be a vector defined by an initializer list consisting of one vector, in which case the type would be `::std::vector<::std::vector<int>>`.

The copy constructor is preferred to the list constructor in `C++20` if the initialization consists of a single element compatible with the class type:

```c++
auto
   vector{ ::std::vector { 2, 4, 6, 8 } };

::std::cout << typeid( vector ).name() << ::std::endl;
```
