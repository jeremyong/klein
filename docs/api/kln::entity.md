## struct `kln::entity` {#structkln_1_1entity}

The full $\mathbf{P}(\mathbb{R}^*_{3, 0, 1})$ graded-algebra requires 16 floats to represent a general multivector. However, it is very common to perform computation on either the odd or even subalgebras. For example, motor composition lives entirely within the even subalgebra, while entities such as planes, and points exist in the odd subalgebra.

The `entity`  struct is the base class for all geometric entities in Klein and encapsulates their multivector representations. The `plane` , `line` , and `point`  class are some examples of geometric entities. Geometric *actions* such as the `rotor` , `translator` , and `motor`  also have multivector representations and are implemented as `entity`  subclasses as well. Note that while inheritance is used, there *is no virtual dispatch* occurring at any point. Inheritance is used here strictly because all the entities above have the same underlying representation, and all operations implemented here are valid for each one.

To compute PGA elements using SSE, we partition the basis into four partitions corresponding to the following scheme:

```cpp
    LSB --> MSB
p0: (e_0, e_1, e_2, e_3)
p1: (1, e_12, e_31, e_23)
p2: (e_0123, e_01, e_02, e_03)
p3: (e_123, e_021, e_013, e_032)
```

The scalar and pseudoscalar are packed in partitions $p_1$ and $p_2$ along with the 6 bivector elements. The scheme groups, for the most part, elements of similar grade and the presence of the degenerate generator. When non-uniformity exists within a partition (mixed degenerate and non-degenerate components, or mixed grade), the "exception" is housed in the first component so that the same swizzle masks can be used.

All partitions contain 4 packed single-precision floating point values. An entity's memory layout is specified based on which partitions are present. The least significant bit in the mask corresponds to the presence of P0, and the 4th least significant bit corresponds to the presence of P3.

!!! danger 
    For performance, the single-element accessors such as `e0`
    should be used sparingly or coalesced together in code so that the
    entity data remains in packed SSE registers for as long as possible
    without any dependent load.
    

#### Parameters
* `PMask` The `PMask`  template parameter is a bitmask corresponding to the partitions present in the entity. The size of the entity will be `popcnt(PMask) * 4 * sizeof(float)`  since each partition contains 4 floats.

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  ` [`entity`](#structkln_1_1entity_1a5b24d28db8dd4146409bfb6167039be0)`()`  | Default constructor. The contents of the entity are left uninitialized.
`public  ` [`entity`](#structkln_1_1entity_1ac2804bf484d645466da79b1dbf47ecaa)`(` [`entity`](#structkln_1_1entity)` const & other)`  | Copy constructor.
`public template<>`  <br/>`constexpr auto ` [`operator+`](#structkln_1_1entity_1a7288ef4e2f601719f2c8e83359b44570)`(` [`entity`](#structkln_1_1entity)`< P > const & other) const noexcept`  | Addition.
`public template<>`  <br/>`constexpr auto ` [`operator-`](#structkln_1_1entity_1a801c3a9ed167ccb21f02b90d89d68d83)`(` [`entity`](#structkln_1_1entity)`< P > const & other) const noexcept`  | Subtraction.
`public ` [`entity`](#structkln_1_1entity)` & ` [`operator*=`](#structkln_1_1entity_1ace5d947cc7251834ee705b3c71ae7bd3)`(float scalar) noexcept`  | Scale the multivector by a scalar constant in-place.
`public ` [`entity`](#structkln_1_1entity)` ` [`operator*`](#structkln_1_1entity_1a6e6631d9a3ebc3292f637e744220dae0)`(float scalar) const noexcept`  | Scale the multivector by a scalar constant and return the result.
`public ` [`entity`](#structkln_1_1entity)` & ` [`operator/=`](#structkln_1_1entity_1ac86920ece406ef01975a88ce7170b3d9)`(float s) noexcept`  | Divide the multivector by a scalar constant in-place.
`public ` [`entity`](#structkln_1_1entity)` ` [`operator/`](#structkln_1_1entity_1a36664c9061251afbfa23c55dd47b943e)`(float s) const noexcept`  | Divide the multivector by a scalar constant and return the result.
`public constexpr ` [`entity`](#structkln_1_1entity)` ` [`operator~`](#structkln_1_1entity_1ad009244ee075ab1ee8fd566ff3ec9e21)`() const noexcept`  | Reversion operator
`public template<>`  <br/>`constexpr auto ` [`operator^`](#structkln_1_1entity_1ad6bf5dca8f4c0bdcbd687483af95ce1b)`(` [`entity`](#structkln_1_1entity)`< PMask2 > const & rhs) const noexcept`  | Exterior Product
`public constexpr auto ` [`operator!`](#structkln_1_1entity_1ad433523ab00b8c3b1f7ed493761ae39f)`() const noexcept`  | Poincaré Dual
`public template<>`  <br/>`constexpr auto ` [`operator&`](#structkln_1_1entity_1a868f3551cb95294532100c4a21b9315e)`(` [`entity`](#structkln_1_1entity)`< PMask2 > const & rhs) const noexcept`  | Regressive Product
`public template<>`  <br/>`constexpr auto ` [`operator*`](#structkln_1_1entity_1a65767f7c9fe6a5ef8d76863e9526429b)`(` [`entity`](#structkln_1_1entity)`< PMask2 > const & rhs) const noexcept`  | Geometric Product
`public constexpr float ` [`scalar`](#structkln_1_1entity_1a21d43c5ba9879c5a467710a5f9595a04)`() const noexcept`  | 
`public constexpr float ` [`e0`](#structkln_1_1entity_1ac9ec7b5b5fee7a87c7cb4fbe937eedfd)`() const noexcept`  | 
`public constexpr float ` [`e1`](#structkln_1_1entity_1a64065edeb9501df5a07b17b219ab4289)`() const noexcept`  | 
`public constexpr float ` [`e2`](#structkln_1_1entity_1aade01dacf2b720cb8bf57d0282c017e6)`() const noexcept`  | 
`public constexpr float ` [`e3`](#structkln_1_1entity_1a3f4ac3d5aca043f44cb37d7b5c975d57)`() const noexcept`  | 
`public constexpr float ` [`e12`](#structkln_1_1entity_1a6ea826a0579b5e3af406b3bdf469bb6c)`() const noexcept`  | 
`public constexpr float ` [`e21`](#structkln_1_1entity_1ad0019d3f02141fe76bae8b3ce9774b5d)`() const noexcept`  | 
`public constexpr float ` [`e31`](#structkln_1_1entity_1a00065a1b6bc1f1532876940d3de0d2e4)`() const noexcept`  | 
`public constexpr float ` [`e13`](#structkln_1_1entity_1a69446b73fcaef24b744b2a14e31861fd)`() const noexcept`  | 
`public constexpr float ` [`e23`](#structkln_1_1entity_1a4c9bba50265256e6e01b2ea8b0cf3ffa)`() const noexcept`  | 
`public constexpr float ` [`e32`](#structkln_1_1entity_1a94f099f3e5dd4ff8d663396715c370a6)`() const noexcept`  | 
`public constexpr float ` [`e01`](#structkln_1_1entity_1a030e60fa0c4ff7b1dafeca081acdfec5)`() const noexcept`  | 
`public constexpr float ` [`e10`](#structkln_1_1entity_1a54ea443de00d60b6b16cb7fb7dc52870)`() const noexcept`  | 
`public constexpr float ` [`e02`](#structkln_1_1entity_1a0f2957262d809cdf5294ef770468070b)`() const noexcept`  | 
`public constexpr float ` [`e20`](#structkln_1_1entity_1a9a90ade68fc6975d7ad02e1fd736e53b)`() const noexcept`  | 
`public constexpr float ` [`e03`](#structkln_1_1entity_1ae695df1c64e3803c8f67673b09023ffe)`() const noexcept`  | 
`public constexpr float ` [`e30`](#structkln_1_1entity_1a8cfb7fb8d4f93d9674c399b7956ae367)`() const noexcept`  | 
`public constexpr float ` [`e123`](#structkln_1_1entity_1a89a079a5b10a1bcaf49105bb8a0d7cd5)`() const noexcept`  | 
`public constexpr float ` [`e021`](#structkln_1_1entity_1a3045a22eb3f141eaf1567f49503b9480)`() const noexcept`  | 
`public constexpr float ` [`e013`](#structkln_1_1entity_1af59505260510fbb1556d1c859a59936c)`() const noexcept`  | 
`public constexpr float ` [`e032`](#structkln_1_1entity_1a9fb409176fc8e3caf1e198f678947b56)`() const noexcept`  | 
`public constexpr float ` [`e0123`](#structkln_1_1entity_1af600ee5cb17611634372db3ee224e2b7)`() const noexcept`  | 
`public __m128 const  & ` [`p0`](#structkln_1_1entity_1a5ce7f65ed2f1ab3a36614248d77676c6)`() const noexcept`  | 
`public __m128 const  & ` [`p1`](#structkln_1_1entity_1a292759d6bad720e2ea4853af25ef6f4c)`() const noexcept`  | 
`public __m128 const  & ` [`p2`](#structkln_1_1entity_1a1ee3801d6acb2599c93d3cf17b291f30)`() const noexcept`  | 
`public __m128 const  & ` [`p3`](#structkln_1_1entity_1a8fad5254df7d3d62dfdb43fa4c2b5e0a)`() const noexcept`  | 
`public float const  * ` [`p0f`](#structkln_1_1entity_1af19fce68b106f2ada71e6b9810fe3109)`() const noexcept`  | 
`public float const  * ` [`p1f`](#structkln_1_1entity_1ade8c1899ca84e55f9ddf263c676f3909)`() const noexcept`  | 
`public float const  * ` [`p2f`](#structkln_1_1entity_1aa196667401be670635b16dec03ae2a11)`() const noexcept`  | 
`public float const  * ` [`p3f`](#structkln_1_1entity_1a4957d08f0100cfcbaa76a6e5104f9afd)`() const noexcept`  | 
`public __m128 & ` [`p0`](#structkln_1_1entity_1a6934b623020ecda2603d9a5a2efb9490)`() noexcept`  | 
`public __m128 & ` [`p1`](#structkln_1_1entity_1aea4868647c6e9d51b95edfe06f07f1e0)`() noexcept`  | 
`public __m128 & ` [`p2`](#structkln_1_1entity_1a22a629ae59cdc412a1f8939e3de15057)`() noexcept`  | 
`public __m128 & ` [`p3`](#structkln_1_1entity_1a352c9ba8605a356d7f79a66390b26fc6)`() noexcept`  | 
`protected ` [`partition`](/Klein/api/kln::entity::partition#unionkln_1_1entity_1_1partition)` ` [`parts`](#structkln_1_1entity_1accb4153a7732f7f3649c016b87210b23) | 

### Members

####   [entity](#structkln_1_1entity_1a5b24d28db8dd4146409bfb6167039be0)()  {#structkln_1_1entity_1a5b24d28db8dd4146409bfb6167039be0}

Default constructor. The contents of the entity are left uninitialized.

####   [entity](#structkln_1_1entity_1ac2804bf484d645466da79b1dbf47ecaa)( [entity](#structkln_1_1entity) const & other)  {#structkln_1_1entity_1ac2804bf484d645466da79b1dbf47ecaa}

Copy constructor.

#### template<>  <br/>auto  [operator+](#structkln_1_1entity_1a7288ef4e2f601719f2c8e83359b44570)( [entity](#structkln_1_1entity)< P > const & other) const noexcept  {#structkln_1_1entity_1a7288ef4e2f601719f2c8e83359b44570}

Addition.

Returns the sum of this entity and another. The partition mask of the result will be the union of the two addends.

#### template<>  <br/>auto  [operator-](#structkln_1_1entity_1a801c3a9ed167ccb21f02b90d89d68d83)( [entity](#structkln_1_1entity)< P > const & other) const noexcept  {#structkln_1_1entity_1a801c3a9ed167ccb21f02b90d89d68d83}

Subtraction.

Returns the difference of this entity and another. The partition mask of the result will be the union of the two operands.

####  [entity](#structkln_1_1entity) &  [operator*=](#structkln_1_1entity_1ace5d947cc7251834ee705b3c71ae7bd3)(float scalar) noexcept  {#structkln_1_1entity_1ace5d947cc7251834ee705b3c71ae7bd3}

Scale the multivector by a scalar constant in-place.

####  [entity](#structkln_1_1entity)  [operator*](#structkln_1_1entity_1a6e6631d9a3ebc3292f637e744220dae0)(float scalar) const noexcept  {#structkln_1_1entity_1a6e6631d9a3ebc3292f637e744220dae0}

Scale the multivector by a scalar constant and return the result.

####  [entity](#structkln_1_1entity) &  [operator/=](#structkln_1_1entity_1ac86920ece406ef01975a88ce7170b3d9)(float s) noexcept  {#structkln_1_1entity_1ac86920ece406ef01975a88ce7170b3d9}

Divide the multivector by a scalar constant in-place.

####  [entity](#structkln_1_1entity)  [operator/](#structkln_1_1entity_1a36664c9061251afbfa23c55dd47b943e)(float s) const noexcept  {#structkln_1_1entity_1a36664c9061251afbfa23c55dd47b943e}

Divide the multivector by a scalar constant and return the result.

####  [entity](#structkln_1_1entity)  [operator~](#structkln_1_1entity_1ad009244ee075ab1ee8fd566ff3ec9e21)() const noexcept  {#structkln_1_1entity_1ad009244ee075ab1ee8fd566ff3ec9e21}

Reversion operator

Given a basis element $e_S$, the reverse is given as $\mathbf{e}_{\widetilde{S}}$ where the sequence $\widetilde{S}$ is the reverse of the indices in $S$. For a given basis element, $e_S\widetilde{e}_S = 1$. The operator extends linearly to general multivectors.

Ex: The reverse of $\mathbf{e}_{12} + 3\mathbf{e}_{021}$ is $\mathbf{e}_{21} + 3\mathbf{e}_{120}$. Signs will be flipped to reexpress the result in the cyclic basis as $-\mathbf{e}_{12} - 3\mathbf{e}_{021}$.

#### template<>  <br/>auto  [operator^](#structkln_1_1entity_1ad6bf5dca8f4c0bdcbd687483af95ce1b)( [entity](#structkln_1_1entity)< PMask2 > const & rhs) const noexcept  {#structkln_1_1entity_1ad6bf5dca8f4c0bdcbd687483af95ce1b}

Exterior Product

The exterior product between two basis elements extinguishes if the two operands share any common index. Otherwise, the element produced is equivalent to the union of the subspaces. A sign flip is introduced if the concatenation of the element indices is an odd permutation of the cyclic basis representation.

The exterior product extends to general multivectors by linearity.

Ex: The exterior product $e_1 \wedge \mathbf{e}_{32}$ is $-\mathbf{e}_{123}$.

#### auto  [operator!](#structkln_1_1entity_1ad433523ab00b8c3b1f7ed493761ae39f)() const noexcept  {#structkln_1_1entity_1ad433523ab00b8c3b1f7ed493761ae39f}

Poincaré Dual

The Poincaré Dual of an element is the "subspace complement" of the argument with respect to the pseudoscalar. In practice, it is a relabeling of the coordinates to their dual-coordinates and is used most often to implement a "join" operation in terms of the exterior product of the duals of each operand.

Ex: The dual of the point $\mathbf{e}_{123} + 3\mathbf{e}_{013} - 2\mathbf{e}_{021}$ (the point at $(0, 3, -2)$) is the plane $e_0 + 3e_2 - 2e_3$.

#### template<>  <br/>auto  [operator&](#structkln_1_1entity_1a868f3551cb95294532100c4a21b9315e)( [entity](#structkln_1_1entity)< PMask2 > const & rhs) const noexcept  {#structkln_1_1entity_1a868f3551cb95294532100c4a21b9315e}

Regressive Product

The regressive product is implemented in terms of the exterior product. Given multivectors $\mathbf{a}$ and $\mathbf{b}$, the regressive product $\mathbf{a}\vee\mathbf{b}$ is equivalent to $J(J(\mathbf{a})\wedge J(\mathbf{b}))$. Thus, both meets and joins reside in the same algebraic structure.

#### template<>  <br/>auto  [operator*](#structkln_1_1entity_1a65767f7c9fe6a5ef8d76863e9526429b)( [entity](#structkln_1_1entity)< PMask2 > const & rhs) const noexcept  {#structkln_1_1entity_1a65767f7c9fe6a5ef8d76863e9526429b}

Geometric Product

The geometric product extends the exterior product with a notion of a metric. When the subspace intersection of the operands of two basis elements is non-zero, instead of the product extinguishing, the grade collapses and a scalar weight is included in the final result according to the metric. The geometric product can be used to build rotations, and by extension, rotations and translations in projective space.

#### float  [scalar](#structkln_1_1entity_1a21d43c5ba9879c5a467710a5f9595a04)() const noexcept  {#structkln_1_1entity_1a21d43c5ba9879c5a467710a5f9595a04}

#### float  [e0](#structkln_1_1entity_1ac9ec7b5b5fee7a87c7cb4fbe937eedfd)() const noexcept  {#structkln_1_1entity_1ac9ec7b5b5fee7a87c7cb4fbe937eedfd}

#### float  [e1](#structkln_1_1entity_1a64065edeb9501df5a07b17b219ab4289)() const noexcept  {#structkln_1_1entity_1a64065edeb9501df5a07b17b219ab4289}

#### float  [e2](#structkln_1_1entity_1aade01dacf2b720cb8bf57d0282c017e6)() const noexcept  {#structkln_1_1entity_1aade01dacf2b720cb8bf57d0282c017e6}

#### float  [e3](#structkln_1_1entity_1a3f4ac3d5aca043f44cb37d7b5c975d57)() const noexcept  {#structkln_1_1entity_1a3f4ac3d5aca043f44cb37d7b5c975d57}

#### float  [e12](#structkln_1_1entity_1a6ea826a0579b5e3af406b3bdf469bb6c)() const noexcept  {#structkln_1_1entity_1a6ea826a0579b5e3af406b3bdf469bb6c}

#### float  [e21](#structkln_1_1entity_1ad0019d3f02141fe76bae8b3ce9774b5d)() const noexcept  {#structkln_1_1entity_1ad0019d3f02141fe76bae8b3ce9774b5d}

#### float  [e31](#structkln_1_1entity_1a00065a1b6bc1f1532876940d3de0d2e4)() const noexcept  {#structkln_1_1entity_1a00065a1b6bc1f1532876940d3de0d2e4}

#### float  [e13](#structkln_1_1entity_1a69446b73fcaef24b744b2a14e31861fd)() const noexcept  {#structkln_1_1entity_1a69446b73fcaef24b744b2a14e31861fd}

#### float  [e23](#structkln_1_1entity_1a4c9bba50265256e6e01b2ea8b0cf3ffa)() const noexcept  {#structkln_1_1entity_1a4c9bba50265256e6e01b2ea8b0cf3ffa}

#### float  [e32](#structkln_1_1entity_1a94f099f3e5dd4ff8d663396715c370a6)() const noexcept  {#structkln_1_1entity_1a94f099f3e5dd4ff8d663396715c370a6}

#### float  [e01](#structkln_1_1entity_1a030e60fa0c4ff7b1dafeca081acdfec5)() const noexcept  {#structkln_1_1entity_1a030e60fa0c4ff7b1dafeca081acdfec5}

#### float  [e10](#structkln_1_1entity_1a54ea443de00d60b6b16cb7fb7dc52870)() const noexcept  {#structkln_1_1entity_1a54ea443de00d60b6b16cb7fb7dc52870}

#### float  [e02](#structkln_1_1entity_1a0f2957262d809cdf5294ef770468070b)() const noexcept  {#structkln_1_1entity_1a0f2957262d809cdf5294ef770468070b}

#### float  [e20](#structkln_1_1entity_1a9a90ade68fc6975d7ad02e1fd736e53b)() const noexcept  {#structkln_1_1entity_1a9a90ade68fc6975d7ad02e1fd736e53b}

#### float  [e03](#structkln_1_1entity_1ae695df1c64e3803c8f67673b09023ffe)() const noexcept  {#structkln_1_1entity_1ae695df1c64e3803c8f67673b09023ffe}

#### float  [e30](#structkln_1_1entity_1a8cfb7fb8d4f93d9674c399b7956ae367)() const noexcept  {#structkln_1_1entity_1a8cfb7fb8d4f93d9674c399b7956ae367}

#### float  [e123](#structkln_1_1entity_1a89a079a5b10a1bcaf49105bb8a0d7cd5)() const noexcept  {#structkln_1_1entity_1a89a079a5b10a1bcaf49105bb8a0d7cd5}

#### float  [e021](#structkln_1_1entity_1a3045a22eb3f141eaf1567f49503b9480)() const noexcept  {#structkln_1_1entity_1a3045a22eb3f141eaf1567f49503b9480}

#### float  [e013](#structkln_1_1entity_1af59505260510fbb1556d1c859a59936c)() const noexcept  {#structkln_1_1entity_1af59505260510fbb1556d1c859a59936c}

#### float  [e032](#structkln_1_1entity_1a9fb409176fc8e3caf1e198f678947b56)() const noexcept  {#structkln_1_1entity_1a9fb409176fc8e3caf1e198f678947b56}

#### float  [e0123](#structkln_1_1entity_1af600ee5cb17611634372db3ee224e2b7)() const noexcept  {#structkln_1_1entity_1af600ee5cb17611634372db3ee224e2b7}

#### __m128 const  &  [p0](#structkln_1_1entity_1a5ce7f65ed2f1ab3a36614248d77676c6)() const noexcept  {#structkln_1_1entity_1a5ce7f65ed2f1ab3a36614248d77676c6}

#### __m128 const  &  [p1](#structkln_1_1entity_1a292759d6bad720e2ea4853af25ef6f4c)() const noexcept  {#structkln_1_1entity_1a292759d6bad720e2ea4853af25ef6f4c}

#### __m128 const  &  [p2](#structkln_1_1entity_1a1ee3801d6acb2599c93d3cf17b291f30)() const noexcept  {#structkln_1_1entity_1a1ee3801d6acb2599c93d3cf17b291f30}

#### __m128 const  &  [p3](#structkln_1_1entity_1a8fad5254df7d3d62dfdb43fa4c2b5e0a)() const noexcept  {#structkln_1_1entity_1a8fad5254df7d3d62dfdb43fa4c2b5e0a}

#### float const  *  [p0f](#structkln_1_1entity_1af19fce68b106f2ada71e6b9810fe3109)() const noexcept  {#structkln_1_1entity_1af19fce68b106f2ada71e6b9810fe3109}

#### float const  *  [p1f](#structkln_1_1entity_1ade8c1899ca84e55f9ddf263c676f3909)() const noexcept  {#structkln_1_1entity_1ade8c1899ca84e55f9ddf263c676f3909}

#### float const  *  [p2f](#structkln_1_1entity_1aa196667401be670635b16dec03ae2a11)() const noexcept  {#structkln_1_1entity_1aa196667401be670635b16dec03ae2a11}

#### float const  *  [p3f](#structkln_1_1entity_1a4957d08f0100cfcbaa76a6e5104f9afd)() const noexcept  {#structkln_1_1entity_1a4957d08f0100cfcbaa76a6e5104f9afd}

#### __m128 &  [p0](#structkln_1_1entity_1a6934b623020ecda2603d9a5a2efb9490)() noexcept  {#structkln_1_1entity_1a6934b623020ecda2603d9a5a2efb9490}

#### __m128 &  [p1](#structkln_1_1entity_1aea4868647c6e9d51b95edfe06f07f1e0)() noexcept  {#structkln_1_1entity_1aea4868647c6e9d51b95edfe06f07f1e0}

#### __m128 &  [p2](#structkln_1_1entity_1a22a629ae59cdc412a1f8939e3de15057)() noexcept  {#structkln_1_1entity_1a22a629ae59cdc412a1f8939e3de15057}

#### __m128 &  [p3](#structkln_1_1entity_1a352c9ba8605a356d7f79a66390b26fc6)() noexcept  {#structkln_1_1entity_1a352c9ba8605a356d7f79a66390b26fc6}

#### protected  [partition](/Klein/api/kln::entity::partition#unionkln_1_1entity_1_1partition)  [parts](#structkln_1_1entity_1accb4153a7732f7f3649c016b87210b23) {#structkln_1_1entity_1accb4153a7732f7f3649c016b87210b23}

