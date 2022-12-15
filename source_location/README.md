# ::std::source_location

`C++20` adds the function `::std::source_location::current()` which provides information about the source line, column and enclosing function at the call site:

```c++
void
log_location
   (
      //
      // Note, the source location of this expression
      // is the call site, not this function:
      //
   ::std::source_location
      where = ::std::source_location::current()
   )
{
   ::std::cout << "filename: "
               << where.file_name()
               << ", line "
               << where.line()
               << ", character "
               << where.column()
               << ", function: "
               << where.function_name()
               << ::std::endl
                  ;
   
   return;
}

int main(int argc, char ** argv)
{
   //
   // Prints "filename: ./examples.cpp, line 37, character
   // 16, function: int main(int, char**)":
   //
   
   log_location();
   
   return 0;
}
```
