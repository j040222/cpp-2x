# Modules

Modules are an alternative to `#include`. `#included` files are pasted into the main translation unit as text and then parsed. Modules, on the other hand, are `#imported` as binary entities.

Stdlib headers can be imported if they have been compiled as modules. Use `g++ -std=c++20 -fmodules-ts -xc++-system-header (eg.) iostream` to compile a header before using it in this way:

```c++
import <iostream>;
```

The standard library will be modular in `C++23`. Some standard library headers are importable in `C++20`.

`#defines` in `#imported` modules are not available in the main body of the importing codefile. Conversely, any `#defines` in the main codefile do not affect `#imported` modules. This means that the order of `#imported` modules matters less than the order of `#included` modules. Modules are essentially binary-compiled header files. The main benefit is increased loading speed. At the time of writing, major compilers seem to have incomplete and variable support for modules.

Like header files and translation units, modules can consist of two parts: an interface (that declares the contents of the module) and a module implementation file. Module interfaces can import other module interfaces, and they use the `export` keyword to declare what parts of the file can be imported by others. Module implementation files should begin with `module module_name` and then define their exported and the private members.

Modules can be scoped (creating 'submodules') and partitionned. These are different concepts. A subscope for a module is a submodule, the name of which  should be delimited by period characters (.). A submodule can be imported just like a module can, and it can declare its own interface.

A module partition, on the other hand, separates a module (or a submodule) into multiple files. All of these files together define the contents of the module. Module partitions have names that begin with colons, for example `module_a:partition_0`. Partitions are implementation details: partitions cannot be imported by clients without importing the whole enclosing module.

A module can declare a template class or a template function (and the importing file can use it) just like an `#included` file can. Classes, structs, functions and namespaces can optionally be private to a module (Ie. not accessible to `#importing` modules). There are, however, some differences between module-imported code and header-included code. For example, member function definitions in class declarations in modules are not automatically inlined when imported. Forward-declarations of class names in modules are allowed and these can be imported before the class is defined.








