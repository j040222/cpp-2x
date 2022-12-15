# Arrays of Unknown Bounds

`C++20` allows conversions from an array of known bounds to a reference to an array of unknown bounds. When doing overload resolution, arrays with matching bounds are selected over arrays of unknown or non-matching sizes.

```c++
void function( int const (& array) [] )
{
   ::std::cout << "0" << ::std::endl;
}

void function( int const (& array) [1] )
{
   ::std::cout << "1" << ::std::endl;
}

void function( int const (& array) [2] )
{
   ::std::cout << "2" << ::std::endl;
}

int main(int argc, char ** argv)
{
   int array[1] {};
   
   //
   // Overload matches array of known bound, so calls 1:
   //
   
   function(array);
   
   //
   // Overload matches array of known bound, so calls 2:
   //
   
   function( { 2, 3 } );
   
   {
   
   //
   // A reference to an array of unknown bound, so calls 0:
   //
   
   int (& cast) [] = array;
   
   function(cast);
   
   }
   
   //
   // Doesn't match any overload other than array of
   // unknown bounds, so calls 0:
   //
   
   function( { 1, 2, 3 } );
   
   return 0;
}
```

