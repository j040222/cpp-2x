# ::std::shared_ptr

The control block of a `::std::shared_ptr` object is thread safe.
(because a `::std::shared_ptr` object should be deleted only once). Accessing the `shared_ptr` resource is, however, not thread-safe.

This is an example of a data race. The value referenced by the `shared_ptr` is assigned by multiple threads:

```c++
auto
   p = ::std::make_shared <unsigned> (0)
      ;

for(
   ::std::size_t
      i(0u)
      ;
   i< 5u
      ;
   ++i
   )
{
   ::std::thread
      (
         [&p, &i]
         {
            auto
               new_p =
                  ::std::make_shared <unsigned>
                     (
                     i + 1u
                     )
                     ;
            
               //
               // This would cause a data race because
               // only the shared_ptr control block is
               // thread safe, not the resource that it
               // points to:
               //
            
            // p = new_p
            
               //
               // This, however, is thread safe: the
               // standard library provides atomic
               // functions for modifying shared_ptr:
               //
            
            ::std::atomic_store( &p, new_p );
         }
      )
      .detach();
         ;
   
   continue
      ;
}
```

In `C++20` you can create an atomic `shared_ptr`. `operator=` (and store), the cast operator (`::std::shared_ptr`) and exchange are all atomic operations too:

```c++
auto
   regular_p = ::std::make_shared <unsigned> (1)
      ;

::std::atomic
   <
   ::std::shared_ptr
      <
      unsigned
      >
   >
      //
      // Works in g++-12 :
      //
   p( regular_p )
      ;

//
// Get the underlying shared_ptr:
//

::std::shared_ptr <unsigned>
   p2 = p.load()
      ;
```

