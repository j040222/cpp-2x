# Pointer Conversion to Boolean

Conversions from pointer (or `nullptr`) to `bool` are now narrowing. `nullptr` can only be used with direct { } initialization:

```c++
void * pointer;

{

//
// Initializations in { } braces produce warnings if the
// conversion is narrowing:
//

bool boolean0 { pointer } ;

bool boolean1 = { pointer } ;

//
// The following are not warnings:
//

bool boolean2 ( pointer ) ;

bool boolean3 = ( pointer ) ;

bool boolean4 = pointer;

}

{

bool boolean0 { nullptr } ;

//
// Error: conversion to bool from nullptr requires direct
// initialization:
//

// bool boolean1 = nullptr ;

// bool boolean2 = { nullptr };

}
```
