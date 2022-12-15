# Private Types in Specializations

In `C++20` private subtypes can be used to partly or fully specialize class templates. This was adjusted in `P0692R1`.

Many compilers did allow private subtypes to be used for full specialization before `C++20`.

```c++
class A final
{
private:
   class B;
}
;

template<typename T>
class C { } ;

template<>
class C<A::B> { } ;
```

However, partial specialization was not accepted by all compilers before `C++20`:

```c++
class A2 final
{
private:
   template<typename T>
   class B { } ;
}
;

template
   <
   typename T
   >
class C< A2::B<T> > { } ;
```
