## struct `kln::point` {#structkln_1_1point}

```
struct kln::point
  : public kln::entity< 0b1000 >
```  

A point is represented as the multivector $x\mathbf{e}_{032} + y\mathbf{e}_{013} + z\mathbf{e}_{021} + \mathbf{e}_{123}$. The point has a trivector representation because it is the fixed point of 3 planar reflections (each of which is a grade-1 multivector). In practice, the coordinate mapping can be thought of as an implementation detail.

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  ` [`point`](#structkln_1_1point_1a4ea8cb4d3d80d9f50032061265ed32b6)`() = default`  | Default constructor leaves memory uninitialized.
`public  ` [`point`](#structkln_1_1point_1adc78c30fe71a140259dd7add02d36df8)`(float x,float y,float z) noexcept`  | Component-wise constructor (homogeneous coordinate is automatically initialized to 1)
`public  ` [`point`](#structkln_1_1point_1a9b3754f1b4479d862d026cf55b91f7be)`(` [`entity`](../../api/kln_entity#structkln_1_1entity)`< 0b1000 > const & e) noexcept`  | 
`public  explicit ` [`point`](#structkln_1_1point_1ad149cbbf9e9a7e77fc680b808e971ee0)`(` [`entity`](../../api/kln_entity#structkln_1_1entity)`< 0b1001 > const & e) noexcept`  | A point projected onto a line will have an extinguished partition-0, which necessitates this explicit cast when it is known to be safe.
`public void ` [`load`](#structkln_1_1point_1a805739dde6d772f5b228cce5b95ef13f)`(float * data) noexcept`  | Fast load from a pointer to an array of four floats with layout `(w, z, y, x)`  where `w`  occupies the lowest address in memory.
`public float ` [`x`](#structkln_1_1point_1a0c100888d1b7edc3fdb81f8b7c22feb1)`() const noexcept`  | 
`public float & ` [`x`](#structkln_1_1point_1a47e6deddfdd3939952ef80bb33236bfc)`() noexcept`  | 
`public float ` [`y`](#structkln_1_1point_1ae413703952e1a6e15b401d2620f6ae93)`() const noexcept`  | 
`public float & ` [`y`](#structkln_1_1point_1ab084befb980509d9a1322db14941c76d)`() noexcept`  | 
`public float ` [`z`](#structkln_1_1point_1aff266ae56b86d0598a0373ea222c2bee)`() const noexcept`  | 
`public float & ` [`z`](#structkln_1_1point_1a0ae90d70849cb8bcf24010d77248aad9)`() noexcept`  | 
`public float ` [`w`](#structkln_1_1point_1adfa0b3fa1bc85799e2a3916725b573c1)`() const noexcept`  | The homogeneous coordinate `w`  is exactly $1$ when normalized.
`public float & ` [`w`](#structkln_1_1point_1afa9214ca2840d596309c5c155eebd561)`() noexcept`  | 
`public void ` [`normalize`](#structkln_1_1point_1a3d1ba8e0c47d25c5b5d124d9b5ef8e04)`() noexcept`  | Normalize this point

### Members

####   [point](#structkln_1_1point_1a4ea8cb4d3d80d9f50032061265ed32b6)() = default  {#structkln_1_1point_1a4ea8cb4d3d80d9f50032061265ed32b6}

Default constructor leaves memory uninitialized.

####   [point](#structkln_1_1point_1adc78c30fe71a140259dd7add02d36df8)(float x,float y,float z) noexcept  {#structkln_1_1point_1adc78c30fe71a140259dd7add02d36df8}

Component-wise constructor (homogeneous coordinate is automatically initialized to 1)

####   [point](#structkln_1_1point_1a9b3754f1b4479d862d026cf55b91f7be)( [entity](../../api/kln_entity#structkln_1_1entity)< 0b1000 > const & e) noexcept  {#structkln_1_1point_1a9b3754f1b4479d862d026cf55b91f7be}

####  explicit  [point](#structkln_1_1point_1ad149cbbf9e9a7e77fc680b808e971ee0)( [entity](../../api/kln_entity#structkln_1_1entity)< 0b1001 > const & e) noexcept  {#structkln_1_1point_1ad149cbbf9e9a7e77fc680b808e971ee0}

A point projected onto a line will have an extinguished partition-0, which necessitates this explicit cast when it is known to be safe.

#### void  [load](#structkln_1_1point_1a805739dde6d772f5b228cce5b95ef13f)(float * data) noexcept  {#structkln_1_1point_1a805739dde6d772f5b228cce5b95ef13f}

Fast load from a pointer to an array of four floats with layout `(w, z, y, x)`  where `w`  occupies the lowest address in memory.

!!! tip 
    This load operation is more efficient that modifying individual
    components back-to-back.
    

!!! danger 
    Unlike the component-wise constructor, the load here requires the
    homogeneous coordinate `w` to be supplied as well in the lowest
    address pointed to by `data`.

#### float  [x](#structkln_1_1point_1a0c100888d1b7edc3fdb81f8b7c22feb1)() const noexcept  {#structkln_1_1point_1a0c100888d1b7edc3fdb81f8b7c22feb1}

#### float &  [x](#structkln_1_1point_1a47e6deddfdd3939952ef80bb33236bfc)() noexcept  {#structkln_1_1point_1a47e6deddfdd3939952ef80bb33236bfc}

#### float  [y](#structkln_1_1point_1ae413703952e1a6e15b401d2620f6ae93)() const noexcept  {#structkln_1_1point_1ae413703952e1a6e15b401d2620f6ae93}

#### float &  [y](#structkln_1_1point_1ab084befb980509d9a1322db14941c76d)() noexcept  {#structkln_1_1point_1ab084befb980509d9a1322db14941c76d}

#### float  [z](#structkln_1_1point_1aff266ae56b86d0598a0373ea222c2bee)() const noexcept  {#structkln_1_1point_1aff266ae56b86d0598a0373ea222c2bee}

#### float &  [z](#structkln_1_1point_1a0ae90d70849cb8bcf24010d77248aad9)() noexcept  {#structkln_1_1point_1a0ae90d70849cb8bcf24010d77248aad9}

#### float  [w](#structkln_1_1point_1adfa0b3fa1bc85799e2a3916725b573c1)() const noexcept  {#structkln_1_1point_1adfa0b3fa1bc85799e2a3916725b573c1}

The homogeneous coordinate `w`  is exactly $1$ when normalized.

#### float &  [w](#structkln_1_1point_1afa9214ca2840d596309c5c155eebd561)() noexcept  {#structkln_1_1point_1afa9214ca2840d596309c5c155eebd561}

#### void  [normalize](#structkln_1_1point_1a3d1ba8e0c47d25c5b5d124d9b5ef8e04)() noexcept  {#structkln_1_1point_1a3d1ba8e0c47d25c5b5d124d9b5ef8e04}

Normalize this point

!!! tip 
    Point normalization divides the coordinates by the homogeneous
    coordinate `w`. This is done using the `rcpps` instruction with a
    maximum relative error of $1.5\times 2^{-12}$.

