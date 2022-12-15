
# Examples of language features added in `C++20`

Examples of many `C++` language features added in `C++20`. Click on any header for more details.

## [Aggregate Initialization](./aggregate_initialization/README.md)

Aggregate initialization is no longer allowed for structs with explicitly defaulted or deleted constructors. [examples](./aggregate_initialization/examples.cpp)

## [Arrays of Unknown Bounds](./array_of_unknown_bounds/README.md)

Allows conversions from an array of known bounds to a reference to an array of unknown bounds. When doing overload resolution, arrays with matching bounds are  selected over arrays of unknown or non-matching sizes. [examples](./array_of_unknown_bounds/examples.cpp)

## [Newed Array Size Deduction](./array_size_deduction/README.md)

The size of newed arrays is now deduced, in the same way that arrays on the stack have deduced sizes. [examples](./array_size_deduction/examples.cpp)

## [New Attributes](./attributes/README.md)

Addition of several new attributes, including [[likely]], [[unlikely]] and [[no_unique_address]]. [examples](./attributes/examples.cpp)

## [Bitfields](./bitfields/README.md)

A new syntax for initializing bitfields without using constructors. [examples](./bitfields/examples.cpp)

## [Addition of char8_t](./char8_t/README.md)

Addition of a new type named `char8_t`. [examples](./char8_t/examples.cpp)

## [Concepts](./concepts/README.md)

Concepts are a new language feature that constrain template types and the properties that template types may (and many not) have. [examples](./concepts/examples.cpp)

## [Conditionally Explicit Constructors](./conditional_explicit/README.md)

Constructors can now be conditionally explicit. [examples](./conditional_explicit/examples.cpp)

## [Addition of consteval](./consteval/README.md)

Consteval functions can be called where all of their arguments are constant expressions, but not if any of the arguments are non-constant. They are called  'immediate functions': every call to a consteval function must produce a compile-time constant expression. Variables cannot be declared consteval. [examples](./consteval/examples.cpp)

## [constexpr Default Initialization](./constexpr_default_initialization/README.md)

Not all class members need to be initialized by constexpr constructors, but reading (using) uninitialized members in constexpr contexts in an error. [examples](./constexpr_default_initialization/examples.cpp)

## [Addition of constinit](./constinit/README.md)

Initialize variables at compiletime. [examples](./constinit/examples.cpp)

## [Coroutines](./coroutines/README.md)

Functions that can suspend exection (storing their state in a object on the heap) and be resumed later. [examples](./coroutines/examples.cpp)

## [Custom Structured Bindings](./custom_structured_bindings/README.md)

Allows structured bindings for custom classes and structs, not just for pairs and tuples. [examples](./custom_structured_bindings/examples.cpp)

## [Deprecated Comma Subscript](./deprecated_comma_subscript/README.md)

Comma operators in subscript expressions are deprecated. [examples](./deprecated_comma_subscript/examples.cpp)

## [(Partially) Deprecated Volatile](./deprecated_volatile/README.md)

Deprecates some uses of volatile, and some uses of volatile variables. [examples](./deprecated_volatile/examples.cpp)

## [Designated Initializers](./designated_initializers/README.md)

A new syntax for named initializers for struct, class and union members. [examples](./designated_initializers/examples.cpp)

## [Feature Test Macros](./feature_test_macros/README.md)

Many macros have been added which test for `C++` features. [examples](./feature_test_macros/examples.cpp)

## [Fewer uses of Typename](./fewer_uses_of_typename/README.md)

The keyword 'typename' is no longer required in many cases, including in the default value of a template parameter, in the return type of a function declaration or definition, in class scoped function definitions and class-scoped typedefs, among others. [examples](./fewer_uses_of_typename/examples.cpp)

## [Implicit Lambda Capture](./implicit_lambda_capture/README.md)

Lambda functions can now be used in default-initialized class members. [examples](./implicit_lambda_capture/examples.cpp)

## [Implicit Moves](./implicit_move/README.md)

Moves, rather than copies, are used more often. [examples](./implicit_move/examples.cpp)

## [Initializer List Constructors](./initializer_list_constructor/README.md)

Prefer the copy constructor when initializing a variable with an initializer list if the list consists of a single element compatible with the deduced type. [examples](./initializer_list_constructor/examples.cpp)

## [::std::is_constant_evaluated](./is_constant_evaluated/README.md)

In some use cases (but not all), ::std::is_constant_evaluated evaluates to true if the enclosing function is constant-evaluated. [examples](./is_constant_evaluated/examples.cpp)

## [Lambda Functions](./lambda_functions/README.md)

Addition of generic lambda functions (using auto parameters), lambda functions with template parameters, concept-constrained template parameters and variadic templates. [examples](./lambda_functions/examples.cpp)

## [Lambdas in Unevaluated Contexts](./lambdas_in_unevaluated_contexts/README.md)

Declaring a typedef of a stateless lambda is allowed, lambdas can now be default-constructed, and a stateless lambda can be default-constructed and copy assigned. [examples](./lambdas_in_unevaluated_contexts/examples.cpp)

## [::std::make_shared](./make_shared/README.md)

`::std::make_shared` supports array types. [examples](./make_shared/examples.cpp)

## [Utility Functions](./misc_utility_functions/README.md)

Adds functions for: 
   *. The midpoint of two integers/floats/doubles (`::std::midpoint` in <numeric>);
   * A point along the linear interpolation of two values (`::std::lerp` in <cmath>);
   * `to_array`, to convert raw arrays to  `::std::array` objects;
   * `make_shared` an array;
   * `::std::string` has new member functions to test whether it begins or ends with another expression.

[examples](./misc_utility_functions/examples.cpp)

## [Modules](./modules/README.md)

Modules are an alternative to `#include`. `#included` files are pasted into the main translation unit as text and then parsed. Modules, on the other hand, are `#imported` as binary entities.

## [Nested Inline Namespaces](./nested_inline_namespaces/README.md)

The `inline` keyword is now allowed to appear in nested namespace definitions. Functions in `inline` namespaces are referenced as if they were declared in the nearest upward non-inlined namespace. [examples](./nested_inline_namespaces/examples.cpp)

## [Non-Type Template Parameters](./non_type_template_parameters/README.md)

Some additional non-type template parameters are now allowed. [examples](./non_type_template_parameters/examples.cpp)

## [Operator Delete](./operator_delete/README.md)

An alternative overload for class member `delete`. If the
overload exists then it is responsible for calling the class destructor. [examples](./operator_delete/examples.cpp)

## [Pointer Conversion to Boolean](./pointer_conversion_to_bool/README.md)

Conversions from pointer (or nullptr) to `bool` are now narrowing. [examples](./pointer_conversion_to_bool/examples.cpp)

## [Pointer To Member](./pointer_to_members/README.md)

Prior to `C++20`, `const&`-qualified member functions could not be used as function pointers on rvalue objects. [examples](./pointer_to_members/examples.cpp)

## [Private Types in Specializations](./private_types_in_specializations/README.md)

Private subtypes (subclasses) can be used to partly or fully specialize class templates. [examples](./private_types_in_specializations/examples.cpp)

## [Range-Based For Loops](./range_based_for_loop/README.md)

Free begin()/end() functions are now preferred to member begin/end functions if at least one of the latter does not exist. [examples](./range_based_for_loop/examples.cpp)

## [Range-Based For Modification](./range_based_for_modification/README.md)

An additional variable is allowed in range-based for loops. [examples](./range_based_for_modification/examples.cpp)

## [Ranges](./ranges/README.md)

Ranges is "STL v2". It is a drop-in replacement for many of the components of the STL library.

There are major differences between ranges and pre-ranges code. These include (but are not limited to):

   * Ranges use `C++20` concepts to enforce conditions. This greatly improves the clarity of error messages in template code.
   * A range is itself a concept: it is a type that supports `::std::ranges::begin(object)` and `::std::ranges::end(object)`. The type of the end iterator need not be the same as the iterator type returned by `begin()` - they need only be comparable. This allows, among other things, for infinite ranges: use `::std::unreachable_sentinel` for an iterator that never compares positively with another range iterator.
   * Many algorithms, eg. `::std::ranges::sort`, accept a reference to a range container, not just a pair of `begin`/`end` iterators.

[examples](./ranges/examples.cpp)

## [::std::shared_ptr](./shared_ptr/README.md)

Addition of atomic shared pointers. [examples](./shared_ptr/examples.cpp)

## [::std::source_location](./source_location/README.md)

Adds the function `::std::source_location::current()` which contains information about the source line, column and enclosing function at the call site. [examples](./source_location/examples.cpp)

## [Spaceship Operator](./spaceship_operator/README.md)

The "spaceship operator", `<=>`, is a class-based comparison operator that, for objects `A` and `B`, determines whether `A < B`, `A == B` or `A > B`. The spaceship operator works in much the same way as `strcmp`: `< 0` means "`A < B`", `== 0` means "`A == B`" and `> 0` means "`A > B`". [examples](./spaceship_operator/examples.cpp)

## [Span](./span/README.md)

Spans are objects that reference contiguous sequences of objects. Spans have constant copy/move time complexity and do not own the data that they point to. You can modify the underlying data via a span. [examples](./span/examples.cpp)

## [Structured Bindings](./structured_bindings/README.md)

Structured bindings can be captured by lambdas by value and by reference. [examples](./structured_bindings/examples.cpp)

## [Template Deduction for Aliases](./template_deduction_for_aliases/README.md)

Template parameter deduction works even if the type is an alias of another template type. [examples](./template_deduction_for_aliases/examples.cpp)

## [Using Enum](./using_enum/README.md)

Addition of `using enum`. Enum values do not need to be prefixed with the enum class name in the same block as this instruction. [examples](./using_enum/examples.cpp)

# License

All of the code in this repository (including in documentation and in README.md files) is licensed under the GNU General Public License, version 3. See [https://www.gnu.org/licenses/](https://www.gnu.org/licenses/).


