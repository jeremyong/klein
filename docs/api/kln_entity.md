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
`public template<>`  <br/>`constexpr ` [`entity`](#structkln_1_1entity)` & ` [`operator+=`](#structkln_1_1entity_1a32233162722a6cf9a621e08b4f4579f7)`(` [`entity`](#structkln_1_1entity)`< P > const & other) noexcept`  | 
`public template<>`  <br/>`constexpr auto ` [`operator-`](#structkln_1_1entity_1a801c3a9ed167ccb21f02b90d89d68d83)`(` [`entity`](#structkln_1_1entity)`< P > const & other) const noexcept`  | Subtraction.
`public template<>`  <br/>`constexpr ` [`entity`](#structkln_1_1entity)` & ` [`operator-=`](#structkln_1_1entity_1a6927a4b416adc298f48b0a45bec1919a)`(` [`entity`](#structkln_1_1entity)`< P > const & other) noexcept`  | 
`public ` [`entity`](#structkln_1_1entity)` & ` [`operator*=`](#structkln_1_1entity_1ace5d947cc7251834ee705b3c71ae7bd3)`(float scalar) noexcept`  | Scale the multivector by a scalar constant in-place.
`public ` [`entity`](#structkln_1_1entity)` ` [`operator*`](#structkln_1_1entity_1a6e6631d9a3ebc3292f637e744220dae0)`(float scalar) const noexcept`  | Scale the multivector by a scalar constant and return the result.
`public ` [`entity`](#structkln_1_1entity)` & ` [`operator/=`](#structkln_1_1entity_1ac86920ece406ef01975a88ce7170b3d9)`(float s) noexcept`  | Divide the multivector by a scalar constant in-place.
`public ` [`entity`](#structkln_1_1entity)` ` [`operator/`](#structkln_1_1entity_1a36664c9061251afbfa23c55dd47b943e)`(float s) const noexcept`  | Divide the multivector by a scalar constant and return the result.
`public constexpr ` [`entity`](#structkln_1_1entity)` ` [`operator~`](#structkln_1_1entity_1ad009244ee075ab1ee8fd566ff3ec9e21)`() const noexcept`  | Reversion operator
`public template<>`  <br/>`auto ` [`operator\|`](#structkln_1_1entity_1ae0087eca49bc5fceb83d1c73a7b47ddb)`(` [`entity`](#structkln_1_1entity)`< PMask2 > const & rhs) const noexcept`  | Symmetric Inner Product
`public template<>`  <br/>`auto ` [`operator^`](#structkln_1_1entity_1ad596afe1ef56faf4f66d96311afa21cd)`(` [`entity`](#structkln_1_1entity)`< PMask2 > const & rhs) const noexcept`  | Exterior Product
`public constexpr auto ` [`operator!`](#structkln_1_1entity_1ad433523ab00b8c3b1f7ed493761ae39f)`() const noexcept`  | Poincaré Dual
`public template<>`  <br/>`constexpr auto ` [`operator&`](#structkln_1_1entity_1a868f3551cb95294532100c4a21b9315e)`(` [`entity`](#structkln_1_1entity)`< PMask2 > const & rhs) const noexcept`  | Regressive Product
`public template<>`  <br/>`auto ` [`operator*`](#structkln_1_1entity_1ac948d3ba57bbeb6dd041e49cecadf4af)`(` [`entity`](#structkln_1_1entity)`< PMask2 > const & rhs) const noexcept`  | Geometric Product
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
`public constexpr __m128 const  & ` [`p0`](#structkln_1_1entity_1a05fbc1442b4eb5ef827d9acc472f0aef)`() const noexcept`  | 
`public constexpr __m128 const  & ` [`p1`](#structkln_1_1entity_1a1c908fb8a68bddea4885ccedaf1b65d8)`() const noexcept`  | 
`public constexpr __m128 const  & ` [`p2`](#structkln_1_1entity_1a3e8fe3506b588f11cd37b4d60c397c4b)`() const noexcept`  | 
`public constexpr __m128 const  & ` [`p3`](#structkln_1_1entity_1a20fd929a4ae39ad6017379e9a3c48bb5)`() const noexcept`  | 
`public constexpr float const  * ` [`p0f`](#structkln_1_1entity_1a40251842147e636f9c158e29011038c9)`() const noexcept`  | 
`public constexpr float const  * ` [`p1f`](#structkln_1_1entity_1aa46e307668c0fe255d83360a043c3b11)`() const noexcept`  | 
`public constexpr float const  * ` [`p2f`](#structkln_1_1entity_1a7e230462d2be4ac5e21699d6b644fe21)`() const noexcept`  | 
`public constexpr float const  * ` [`p3f`](#structkln_1_1entity_1ae0a258682c81938ebd500df87c1d2ad8)`() const noexcept`  | 
`public constexpr __m128 & ` [`p0`](#structkln_1_1entity_1a1cbd9e5ada4bb576f42f94ac4babb8e4)`() noexcept`  | 
`public constexpr __m128 & ` [`p1`](#structkln_1_1entity_1ac1738c1afc34ec2d32d162b145e3fd62)`() noexcept`  | 
`public constexpr __m128 & ` [`p2`](#structkln_1_1entity_1ae5da7f4d3dbec74bff9b8b1b4022cf50)`() noexcept`  | 
`public constexpr __m128 & ` [`p3`](#structkln_1_1entity_1a11244fde748ffb72b84d614c5416351a)`() noexcept`  | 
`protected ` [`partition`](../../api/kln_entity::partition#unionkln_1_1entity_1_1partition)` ` [`parts`](#structkln_1_1entity_1accb4153a7732f7f3649c016b87210b23) | 

### Members

####   [entity](#structkln_1_1entity_1a5b24d28db8dd4146409bfb6167039be0)()  {#structkln_1_1entity_1a5b24d28db8dd4146409bfb6167039be0}

Default constructor. The contents of the entity are left uninitialized.

####   [entity](#structkln_1_1entity_1ac2804bf484d645466da79b1dbf47ecaa)( [entity](#structkln_1_1entity) const & other)  {#structkln_1_1entity_1ac2804bf484d645466da79b1dbf47ecaa}

Copy constructor.

#### template<>  <br/>auto  [operator+](#structkln_1_1entity_1a7288ef4e2f601719f2c8e83359b44570)( [entity](#structkln_1_1entity)< P > const & other) const noexcept  {#structkln_1_1entity_1a7288ef4e2f601719f2c8e83359b44570}

Addition.

Returns the sum of this entity and another. The partition mask of the result will be the union of the two addends.

#### template<>  <br/> [entity](#structkln_1_1entity) &  [operator+=](#structkln_1_1entity_1a32233162722a6cf9a621e08b4f4579f7)( [entity](#structkln_1_1entity)< P > const & other) noexcept  {#structkln_1_1entity_1a32233162722a6cf9a621e08b4f4579f7}

#### template<>  <br/>auto  [operator-](#structkln_1_1entity_1a801c3a9ed167ccb21f02b90d89d68d83)( [entity](#structkln_1_1entity)< P > const & other) const noexcept  {#structkln_1_1entity_1a801c3a9ed167ccb21f02b90d89d68d83}

Subtraction.

Returns the difference of this entity and another. The partition mask of the result will be the union of the two operands.

#### template<>  <br/> [entity](#structkln_1_1entity) &  [operator-=](#structkln_1_1entity_1a6927a4b416adc298f48b0a45bec1919a)( [entity](#structkln_1_1entity)< P > const & other) noexcept  {#structkln_1_1entity_1a6927a4b416adc298f48b0a45bec1919a}

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

#### template<>  <br/>auto  [operator|](#structkln_1_1entity_1ae0087eca49bc5fceb83d1c73a7b47ddb)( [entity](#structkln_1_1entity)< PMask2 > const & rhs) const noexcept  {#structkln_1_1entity_1ae0087eca49bc5fceb83d1c73a7b47ddb}

Symmetric Inner Product

The symmetric inner product takes two arguments and contracts the lower graded element to the greater graded element. If lower graded element spans an index that is not contained in the higher graded element, the result is annihilated. Otherwise, the result is the part of the higher graded element "most unlike" the lower graded element. Thus, the symmetric inner product can be thought of as a bidirectional contraction operator.

There is some merit in providing both a left and right contraction operator for explicitness. However, when using Klein, it's generally clear what the interpretation of the symmetric inner product is with respect to the projection on various entities.

#### template<>  <br/>auto  [operator^](#structkln_1_1entity_1ad596afe1ef56faf4f66d96311afa21cd)( [entity](#structkln_1_1entity)< PMask2 > const & rhs) const noexcept  {#structkln_1_1entity_1ad596afe1ef56faf4f66d96311afa21cd}

Exterior Product

The exterior product between two basis elements extinguishes if the two operands share any common index. Otherwise, the element produced is equivalent to the union of the subspaces. A sign flip is introduced if the concatenation of the element indices is an odd permutation of the cyclic basis representation.

The exterior product extends to general multivectors by linearity.

Ex: The exterior product $e_1 \wedge \mathbf{e}_{32}$ is $-\mathbf{e}_{123}$.

#### auto  [operator!](#structkln_1_1entity_1ad433523ab00b8c3b1f7ed493761ae39f)() const noexcept  {#structkln_1_1entity_1ad433523ab00b8c3b1f7ed493761ae39f}

Poincaré Dual

The Poincaré Dual of an element is the "subspace complement" of the argument with respect to the pseudoscalar in the exterior algebra. In practice, it is a relabeling of the coordinates to their dual-coordinates and is used most often to implement a "join" operation in terms of the exterior product of the duals of each operand.

Ex: The dual of the point $\mathbf{e}_{123} + 3\mathbf{e}_{013} - 2\mathbf{e}_{021}$ (the point at $(0, 3, -2)$) is the plane $e_0 + 3e_2 - 2e_3$.

#### template<>  <br/>auto  [operator&](#structkln_1_1entity_1a868f3551cb95294532100c4a21b9315e)( [entity](#structkln_1_1entity)< PMask2 > const & rhs) const noexcept  {#structkln_1_1entity_1a868f3551cb95294532100c4a21b9315e}

Regressive Product

The regressive product is implemented in terms of the exterior product. Given multivectors $\mathbf{a}$ and $\mathbf{b}$, the regressive product $\mathbf{a}\vee\mathbf{b}$ is equivalent to $J(J(\mathbf{a})\wedge J(\mathbf{b}))$. Thus, both meets and joins reside in the same algebraic structure.

#### template<>  <br/>auto  [operator*](#structkln_1_1entity_1ac948d3ba57bbeb6dd041e49cecadf4af)( [entity](#structkln_1_1entity)< PMask2 > const & rhs) const noexcept  {#structkln_1_1entity_1ac948d3ba57bbeb6dd041e49cecadf4af}

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

#### __m128 const  &  [p0](#structkln_1_1entity_1a05fbc1442b4eb5ef827d9acc472f0aef)() const noexcept  {#structkln_1_1entity_1a05fbc1442b4eb5ef827d9acc472f0aef}

#### __m128 const  &  [p1](#structkln_1_1entity_1a1c908fb8a68bddea4885ccedaf1b65d8)() const noexcept  {#structkln_1_1entity_1a1c908fb8a68bddea4885ccedaf1b65d8}

#### __m128 const  &  [p2](#structkln_1_1entity_1a3e8fe3506b588f11cd37b4d60c397c4b)() const noexcept  {#structkln_1_1entity_1a3e8fe3506b588f11cd37b4d60c397c4b}

#### __m128 const  &  [p3](#structkln_1_1entity_1a20fd929a4ae39ad6017379e9a3c48bb5)() const noexcept  {#structkln_1_1entity_1a20fd929a4ae39ad6017379e9a3c48bb5}

#### float const  *  [p0f](#structkln_1_1entity_1a40251842147e636f9c158e29011038c9)() const noexcept  {#structkln_1_1entity_1a40251842147e636f9c158e29011038c9}

#### float const  *  [p1f](#structkln_1_1entity_1aa46e307668c0fe255d83360a043c3b11)() const noexcept  {#structkln_1_1entity_1aa46e307668c0fe255d83360a043c3b11}

#### float const  *  [p2f](#structkln_1_1entity_1a7e230462d2be4ac5e21699d6b644fe21)() const noexcept  {#structkln_1_1entity_1a7e230462d2be4ac5e21699d6b644fe21}

#### float const  *  [p3f](#structkln_1_1entity_1ae0a258682c81938ebd500df87c1d2ad8)() const noexcept  {#structkln_1_1entity_1ae0a258682c81938ebd500df87c1d2ad8}

#### __m128 &  [p0](#structkln_1_1entity_1a1cbd9e5ada4bb576f42f94ac4babb8e4)() noexcept  {#structkln_1_1entity_1a1cbd9e5ada4bb576f42f94ac4babb8e4}

#### __m128 &  [p1](#structkln_1_1entity_1ac1738c1afc34ec2d32d162b145e3fd62)() noexcept  {#structkln_1_1entity_1ac1738c1afc34ec2d32d162b145e3fd62}

#### __m128 &  [p2](#structkln_1_1entity_1ae5da7f4d3dbec74bff9b8b1b4022cf50)() noexcept  {#structkln_1_1entity_1ae5da7f4d3dbec74bff9b8b1b4022cf50}

#### __m128 &  [p3](#structkln_1_1entity_1a11244fde748ffb72b84d614c5416351a)() noexcept  {#structkln_1_1entity_1a11244fde748ffb72b84d614c5416351a}

#### protected  [partition](../../api/kln_entity::partition#unionkln_1_1entity_1_1partition)  [parts](#structkln_1_1entity_1accb4153a7732f7f3649c016b87210b23) {#structkln_1_1entity_1accb4153a7732f7f3649c016b87210b23}

