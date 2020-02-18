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
`public template<>`  <br/>`constexpr KLN_INLINE auto ` [`operator+`](#structkln_1_1entity_1a8e360a40492c2a7a6731e9c6b5bc1ecb)`(` [`entity`](#structkln_1_1entity)`< P > const & other) const noexcept`  | Addition.
`public template<>`  <br/>`constexpr KLN_INLINE ` [`entity`](#structkln_1_1entity)` & ` [`operator+=`](#structkln_1_1entity_1ac6c390c05ea533f2ff95a6579d9d38b3)`(` [`entity`](#structkln_1_1entity)`< P > const & other) noexcept`  | 
`public template<>`  <br/>`constexpr KLN_INLINE auto ` [`operator-`](#structkln_1_1entity_1ae2cdb3c51c8a54cd95f53f8902e6e2d7)`(` [`entity`](#structkln_1_1entity)`< P > const & other) const noexcept`  | Subtraction.
`public template<>`  <br/>`constexpr KLN_INLINE ` [`entity`](#structkln_1_1entity)` & ` [`operator-=`](#structkln_1_1entity_1afd4c26191264b10c2959fc0f3466ae9f)`(` [`entity`](#structkln_1_1entity)`< P > const & other) noexcept`  | 
`public KLN_INLINE ` [`entity`](#structkln_1_1entity)` & ` [`operator*=`](#structkln_1_1entity_1abc3d7c16ce1c1484ce756fb76097a49a)`(float scalar) noexcept`  | Scale the multivector by a scalar constant in-place.
`public KLN_INLINE ` [`entity`](#structkln_1_1entity)` ` [`operator*`](#structkln_1_1entity_1a33986ac860118e521e25ff6e907f19d3)`(float scalar) const noexcept`  | Scale the multivector by a scalar constant and return the result.
`public KLN_INLINE ` [`entity`](#structkln_1_1entity)` & ` [`operator/=`](#structkln_1_1entity_1a7282fd0b07e44ed6b6f3a60432800251)`(float s) noexcept`  | Divide the multivector by a scalar constant in-place.
`public KLN_INLINE ` [`entity`](#structkln_1_1entity)` ` [`operator/`](#structkln_1_1entity_1a6d5de5a07546bbb274cecd5d60fdbd29)`(float s) const noexcept`  | Divide the multivector by a scalar constant and return the result.
`public constexpr KLN_INLINE ` [`entity`](#structkln_1_1entity)` ` [`operator~`](#structkln_1_1entity_1a080f2750e9f4a871df78333f612e8f45)`() const noexcept`  | Reversion operator
`public template<>`  <br/>`constexpr KLN_INLINE auto ` [`operator\|`](#structkln_1_1entity_1ac3f81a6633e42d2cc9ffc2c597c44d5c)`(` [`entity`](#structkln_1_1entity)`< PMask2 > const & rhs) const noexcept`  | Symmetric Inner Product
`public template<>`  <br/>`constexpr KLN_INLINE auto ` [`operator^`](#structkln_1_1entity_1af55e7d089149e4d1781c13c5110991c5)`(` [`entity`](#structkln_1_1entity)`< PMask2 > const & rhs) const noexcept`  | Exterior Product
`public constexpr KLN_INLINE auto ` [`operator!`](#structkln_1_1entity_1adfd82048030dab3923a936764ba0bebc)`() const noexcept`  | Poincaré Dual
`public template<>`  <br/>`constexpr KLN_INLINE auto ` [`operator&`](#structkln_1_1entity_1a91f91384b86bd2816cdebf3c366a0127)`(` [`entity`](#structkln_1_1entity)`< PMask2 > const & rhs) const noexcept`  | Regressive Product
`public template<>`  <br/>`constexpr KLN_INLINE auto ` [`operator*`](#structkln_1_1entity_1a208c1d169995e533ceadc8a33828e148)`(` [`entity`](#structkln_1_1entity)`< PMask2 > const & rhs) const noexcept`  | Geometric Product
`public constexpr KLN_INLINE float ` [`scalar`](#structkln_1_1entity_1a566913263d5b478360fd73a5b24e7672)`() const noexcept`  | 
`public constexpr KLN_INLINE float ` [`e0`](#structkln_1_1entity_1a92cf5ab25f53d6c697a82d2841ade541)`() const noexcept`  | 
`public constexpr KLN_INLINE float ` [`e1`](#structkln_1_1entity_1a0b6542f7f228c740c64ca9e92b0a1c55)`() const noexcept`  | 
`public constexpr KLN_INLINE float ` [`e2`](#structkln_1_1entity_1a1211965c1130241734bfdb9798c68817)`() const noexcept`  | 
`public constexpr KLN_INLINE float ` [`e3`](#structkln_1_1entity_1a560d5ecb1676831f68eba0ea328e3cde)`() const noexcept`  | 
`public constexpr KLN_INLINE float ` [`e12`](#structkln_1_1entity_1aa1e06fabcb77b201ce1b5a43d1d1cb27)`() const noexcept`  | 
`public constexpr KLN_INLINE float ` [`e21`](#structkln_1_1entity_1a50bbd24b01ebb1a55291fbb1ab75599a)`() const noexcept`  | 
`public constexpr KLN_INLINE float ` [`e31`](#structkln_1_1entity_1a7b2e7f2b10fcf21d7dc11d8b4b59f4a3)`() const noexcept`  | 
`public constexpr KLN_INLINE float ` [`e13`](#structkln_1_1entity_1aee357fbf4f8c689bed9e8d3efc8dca38)`() const noexcept`  | 
`public constexpr KLN_INLINE float ` [`e23`](#structkln_1_1entity_1aeb95c72f276000f9db2e2c38dd81b6a6)`() const noexcept`  | 
`public constexpr KLN_INLINE float ` [`e32`](#structkln_1_1entity_1a3fa2b35b59bfd9dc80078f3a9eeac474)`() const noexcept`  | 
`public constexpr KLN_INLINE float ` [`e01`](#structkln_1_1entity_1a55f13415da9b4c0eb0e0becb4f40ece3)`() const noexcept`  | 
`public constexpr KLN_INLINE float ` [`e10`](#structkln_1_1entity_1a7e19e32456e9ca0beed00cd136d8a5b3)`() const noexcept`  | 
`public constexpr KLN_INLINE float ` [`e02`](#structkln_1_1entity_1ade984d1ced6248671098bb8b3be54d76)`() const noexcept`  | 
`public constexpr KLN_INLINE float ` [`e20`](#structkln_1_1entity_1a4437dfec6857a548c56146cc7421443c)`() const noexcept`  | 
`public constexpr KLN_INLINE float ` [`e03`](#structkln_1_1entity_1aa058a1efe6f524d8dca5eb62bcee7119)`() const noexcept`  | 
`public constexpr KLN_INLINE float ` [`e30`](#structkln_1_1entity_1a7dad08eca3bb1ad66e0ae18c12fd2dce)`() const noexcept`  | 
`public constexpr KLN_INLINE float ` [`e123`](#structkln_1_1entity_1aa0815f2b21d673f611bbde9235a2c8f1)`() const noexcept`  | 
`public constexpr KLN_INLINE float ` [`e021`](#structkln_1_1entity_1a55a5fdcf5803e20a277088b51407dfdf)`() const noexcept`  | 
`public constexpr KLN_INLINE float ` [`e013`](#structkln_1_1entity_1a74abd8e8f52f3af1e4f5047bd9726571)`() const noexcept`  | 
`public constexpr KLN_INLINE float ` [`e032`](#structkln_1_1entity_1ac571c7e7ad105a50130646f477e8dcea)`() const noexcept`  | 
`public constexpr KLN_INLINE float ` [`e0123`](#structkln_1_1entity_1a429ecf90306003684c804f08351ab530)`() const noexcept`  | 
`public constexpr KLN_INLINE __m128 const  & ` [`p0`](#structkln_1_1entity_1abf168e157c9271173de069b6de62bcc1)`() const noexcept`  | 
`public constexpr KLN_INLINE __m128 const  & ` [`p1`](#structkln_1_1entity_1a7a34322ee2e4b49e404b59a3efc644e1)`() const noexcept`  | 
`public constexpr KLN_INLINE __m128 const  & ` [`p2`](#structkln_1_1entity_1a58bd400f84669e248bed438dd18f5239)`() const noexcept`  | 
`public constexpr KLN_INLINE __m128 const  & ` [`p3`](#structkln_1_1entity_1a677765e6eba5338f2ffea28c7b0cc3bf)`() const noexcept`  | 
`public constexpr KLN_INLINE float const  * ` [`p0f`](#structkln_1_1entity_1aaaeabf34ad615fe756a2ccf7725ef3aa)`() const noexcept`  | 
`public constexpr KLN_INLINE float const  * ` [`p1f`](#structkln_1_1entity_1a55df7701da4c18be993616a867ed578d)`() const noexcept`  | 
`public constexpr KLN_INLINE float const  * ` [`p2f`](#structkln_1_1entity_1ae72c795b19eb7f44ecec17b58ebecab0)`() const noexcept`  | 
`public constexpr KLN_INLINE float const  * ` [`p3f`](#structkln_1_1entity_1a9ae540deeb8a5bd79e5e66a2fad8fc70)`() const noexcept`  | 
`public constexpr KLN_INLINE __m128 & ` [`p0`](#structkln_1_1entity_1a3acae1a153b333b8fa033d787a60d551)`() noexcept`  | 
`public constexpr KLN_INLINE __m128 & ` [`p1`](#structkln_1_1entity_1a868f7278b039cda4d39d9a75440a6520)`() noexcept`  | 
`public constexpr KLN_INLINE __m128 & ` [`p2`](#structkln_1_1entity_1a9655fcede93875b3f59a2ff2a717e7ff)`() noexcept`  | 
`public constexpr KLN_INLINE __m128 & ` [`p3`](#structkln_1_1entity_1ac55a05247356a8787cf41c5ad2ebd552)`() noexcept`  | 
`protected ` [`partition`](/Klein/api/kln::entity::partition#unionkln_1_1entity_1_1partition)` ` [`parts`](#structkln_1_1entity_1accb4153a7732f7f3649c016b87210b23) | 

### Members

####   [entity](#structkln_1_1entity_1a5b24d28db8dd4146409bfb6167039be0)()  {#structkln_1_1entity_1a5b24d28db8dd4146409bfb6167039be0}

Default constructor. The contents of the entity are left uninitialized.

####   [entity](#structkln_1_1entity_1ac2804bf484d645466da79b1dbf47ecaa)( [entity](#structkln_1_1entity) const & other)  {#structkln_1_1entity_1ac2804bf484d645466da79b1dbf47ecaa}

Copy constructor.

#### template<>  <br/>KLN_INLINE auto  [operator+](#structkln_1_1entity_1a8e360a40492c2a7a6731e9c6b5bc1ecb)( [entity](#structkln_1_1entity)< P > const & other) const noexcept  {#structkln_1_1entity_1a8e360a40492c2a7a6731e9c6b5bc1ecb}

Addition.

Returns the sum of this entity and another. The partition mask of the result will be the union of the two addends.

#### template<>  <br/>KLN_INLINE  [entity](#structkln_1_1entity) &  [operator+=](#structkln_1_1entity_1ac6c390c05ea533f2ff95a6579d9d38b3)( [entity](#structkln_1_1entity)< P > const & other) noexcept  {#structkln_1_1entity_1ac6c390c05ea533f2ff95a6579d9d38b3}

#### template<>  <br/>KLN_INLINE auto  [operator-](#structkln_1_1entity_1ae2cdb3c51c8a54cd95f53f8902e6e2d7)( [entity](#structkln_1_1entity)< P > const & other) const noexcept  {#structkln_1_1entity_1ae2cdb3c51c8a54cd95f53f8902e6e2d7}

Subtraction.

Returns the difference of this entity and another. The partition mask of the result will be the union of the two operands.

#### template<>  <br/>KLN_INLINE  [entity](#structkln_1_1entity) &  [operator-=](#structkln_1_1entity_1afd4c26191264b10c2959fc0f3466ae9f)( [entity](#structkln_1_1entity)< P > const & other) noexcept  {#structkln_1_1entity_1afd4c26191264b10c2959fc0f3466ae9f}

#### KLN_INLINE  [entity](#structkln_1_1entity) &  [operator*=](#structkln_1_1entity_1abc3d7c16ce1c1484ce756fb76097a49a)(float scalar) noexcept  {#structkln_1_1entity_1abc3d7c16ce1c1484ce756fb76097a49a}

Scale the multivector by a scalar constant in-place.

#### KLN_INLINE  [entity](#structkln_1_1entity)  [operator*](#structkln_1_1entity_1a33986ac860118e521e25ff6e907f19d3)(float scalar) const noexcept  {#structkln_1_1entity_1a33986ac860118e521e25ff6e907f19d3}

Scale the multivector by a scalar constant and return the result.

#### KLN_INLINE  [entity](#structkln_1_1entity) &  [operator/=](#structkln_1_1entity_1a7282fd0b07e44ed6b6f3a60432800251)(float s) noexcept  {#structkln_1_1entity_1a7282fd0b07e44ed6b6f3a60432800251}

Divide the multivector by a scalar constant in-place.

#### KLN_INLINE  [entity](#structkln_1_1entity)  [operator/](#structkln_1_1entity_1a6d5de5a07546bbb274cecd5d60fdbd29)(float s) const noexcept  {#structkln_1_1entity_1a6d5de5a07546bbb274cecd5d60fdbd29}

Divide the multivector by a scalar constant and return the result.

#### KLN_INLINE  [entity](#structkln_1_1entity)  [operator~](#structkln_1_1entity_1a080f2750e9f4a871df78333f612e8f45)() const noexcept  {#structkln_1_1entity_1a080f2750e9f4a871df78333f612e8f45}

Reversion operator

Given a basis element $e_S$, the reverse is given as $\mathbf{e}_{\widetilde{S}}$ where the sequence $\widetilde{S}$ is the reverse of the indices in $S$. For a given basis element, $e_S\widetilde{e}_S = 1$. The operator extends linearly to general multivectors.

Ex: The reverse of $\mathbf{e}_{12} + 3\mathbf{e}_{021}$ is $\mathbf{e}_{21} + 3\mathbf{e}_{120}$. Signs will be flipped to reexpress the result in the cyclic basis as $-\mathbf{e}_{12} - 3\mathbf{e}_{021}$.

#### template<>  <br/>KLN_INLINE auto  [operator|](#structkln_1_1entity_1ac3f81a6633e42d2cc9ffc2c597c44d5c)( [entity](#structkln_1_1entity)< PMask2 > const & rhs) const noexcept  {#structkln_1_1entity_1ac3f81a6633e42d2cc9ffc2c597c44d5c}

Symmetric Inner Product

The symmetric inner product takes two arguments and contracts the lower graded element to the greater graded element. If lower graded element spans an index that is not contained in the higher graded element, the result is annihilated. Otherwise, the result is the part of the higher graded element "most unlike" the lower graded element. Thus, the symmetric inner product can be thought of as a bidirectional contraction operator.

There is some merit in providing both a left and right contraction operator for explicitness. However, when using Klein, it's generally clear what the interpretation of the symmetric inner product is with respect to the projection on various entities.

#### template<>  <br/>KLN_INLINE auto  [operator^](#structkln_1_1entity_1af55e7d089149e4d1781c13c5110991c5)( [entity](#structkln_1_1entity)< PMask2 > const & rhs) const noexcept  {#structkln_1_1entity_1af55e7d089149e4d1781c13c5110991c5}

Exterior Product

The exterior product between two basis elements extinguishes if the two operands share any common index. Otherwise, the element produced is equivalent to the union of the subspaces. A sign flip is introduced if the concatenation of the element indices is an odd permutation of the cyclic basis representation.

The exterior product extends to general multivectors by linearity.

Ex: The exterior product $e_1 \wedge \mathbf{e}_{32}$ is $-\mathbf{e}_{123}$.

#### KLN_INLINE auto  [operator!](#structkln_1_1entity_1adfd82048030dab3923a936764ba0bebc)() const noexcept  {#structkln_1_1entity_1adfd82048030dab3923a936764ba0bebc}

Poincaré Dual

The Poincaré Dual of an element is the "subspace complement" of the argument with respect to the pseudoscalar. In practice, it is a relabeling of the coordinates to their dual-coordinates and is used most often to implement a "join" operation in terms of the exterior product of the duals of each operand.

Ex: The dual of the point $\mathbf{e}_{123} + 3\mathbf{e}_{013} - 2\mathbf{e}_{021}$ (the point at $(0, 3, -2)$) is the plane $e_0 + 3e_2 - 2e_3$.

#### template<>  <br/>KLN_INLINE auto  [operator&](#structkln_1_1entity_1a91f91384b86bd2816cdebf3c366a0127)( [entity](#structkln_1_1entity)< PMask2 > const & rhs) const noexcept  {#structkln_1_1entity_1a91f91384b86bd2816cdebf3c366a0127}

Regressive Product

The regressive product is implemented in terms of the exterior product. Given multivectors $\mathbf{a}$ and $\mathbf{b}$, the regressive product $\mathbf{a}\vee\mathbf{b}$ is equivalent to $J(J(\mathbf{a})\wedge J(\mathbf{b}))$. Thus, both meets and joins reside in the same algebraic structure.

#### template<>  <br/>KLN_INLINE auto  [operator*](#structkln_1_1entity_1a208c1d169995e533ceadc8a33828e148)( [entity](#structkln_1_1entity)< PMask2 > const & rhs) const noexcept  {#structkln_1_1entity_1a208c1d169995e533ceadc8a33828e148}

Geometric Product

The geometric product extends the exterior product with a notion of a metric. When the subspace intersection of the operands of two basis elements is non-zero, instead of the product extinguishing, the grade collapses and a scalar weight is included in the final result according to the metric. The geometric product can be used to build rotations, and by extension, rotations and translations in projective space.

#### KLN_INLINE float  [scalar](#structkln_1_1entity_1a566913263d5b478360fd73a5b24e7672)() const noexcept  {#structkln_1_1entity_1a566913263d5b478360fd73a5b24e7672}

#### KLN_INLINE float  [e0](#structkln_1_1entity_1a92cf5ab25f53d6c697a82d2841ade541)() const noexcept  {#structkln_1_1entity_1a92cf5ab25f53d6c697a82d2841ade541}

#### KLN_INLINE float  [e1](#structkln_1_1entity_1a0b6542f7f228c740c64ca9e92b0a1c55)() const noexcept  {#structkln_1_1entity_1a0b6542f7f228c740c64ca9e92b0a1c55}

#### KLN_INLINE float  [e2](#structkln_1_1entity_1a1211965c1130241734bfdb9798c68817)() const noexcept  {#structkln_1_1entity_1a1211965c1130241734bfdb9798c68817}

#### KLN_INLINE float  [e3](#structkln_1_1entity_1a560d5ecb1676831f68eba0ea328e3cde)() const noexcept  {#structkln_1_1entity_1a560d5ecb1676831f68eba0ea328e3cde}

#### KLN_INLINE float  [e12](#structkln_1_1entity_1aa1e06fabcb77b201ce1b5a43d1d1cb27)() const noexcept  {#structkln_1_1entity_1aa1e06fabcb77b201ce1b5a43d1d1cb27}

#### KLN_INLINE float  [e21](#structkln_1_1entity_1a50bbd24b01ebb1a55291fbb1ab75599a)() const noexcept  {#structkln_1_1entity_1a50bbd24b01ebb1a55291fbb1ab75599a}

#### KLN_INLINE float  [e31](#structkln_1_1entity_1a7b2e7f2b10fcf21d7dc11d8b4b59f4a3)() const noexcept  {#structkln_1_1entity_1a7b2e7f2b10fcf21d7dc11d8b4b59f4a3}

#### KLN_INLINE float  [e13](#structkln_1_1entity_1aee357fbf4f8c689bed9e8d3efc8dca38)() const noexcept  {#structkln_1_1entity_1aee357fbf4f8c689bed9e8d3efc8dca38}

#### KLN_INLINE float  [e23](#structkln_1_1entity_1aeb95c72f276000f9db2e2c38dd81b6a6)() const noexcept  {#structkln_1_1entity_1aeb95c72f276000f9db2e2c38dd81b6a6}

#### KLN_INLINE float  [e32](#structkln_1_1entity_1a3fa2b35b59bfd9dc80078f3a9eeac474)() const noexcept  {#structkln_1_1entity_1a3fa2b35b59bfd9dc80078f3a9eeac474}

#### KLN_INLINE float  [e01](#structkln_1_1entity_1a55f13415da9b4c0eb0e0becb4f40ece3)() const noexcept  {#structkln_1_1entity_1a55f13415da9b4c0eb0e0becb4f40ece3}

#### KLN_INLINE float  [e10](#structkln_1_1entity_1a7e19e32456e9ca0beed00cd136d8a5b3)() const noexcept  {#structkln_1_1entity_1a7e19e32456e9ca0beed00cd136d8a5b3}

#### KLN_INLINE float  [e02](#structkln_1_1entity_1ade984d1ced6248671098bb8b3be54d76)() const noexcept  {#structkln_1_1entity_1ade984d1ced6248671098bb8b3be54d76}

#### KLN_INLINE float  [e20](#structkln_1_1entity_1a4437dfec6857a548c56146cc7421443c)() const noexcept  {#structkln_1_1entity_1a4437dfec6857a548c56146cc7421443c}

#### KLN_INLINE float  [e03](#structkln_1_1entity_1aa058a1efe6f524d8dca5eb62bcee7119)() const noexcept  {#structkln_1_1entity_1aa058a1efe6f524d8dca5eb62bcee7119}

#### KLN_INLINE float  [e30](#structkln_1_1entity_1a7dad08eca3bb1ad66e0ae18c12fd2dce)() const noexcept  {#structkln_1_1entity_1a7dad08eca3bb1ad66e0ae18c12fd2dce}

#### KLN_INLINE float  [e123](#structkln_1_1entity_1aa0815f2b21d673f611bbde9235a2c8f1)() const noexcept  {#structkln_1_1entity_1aa0815f2b21d673f611bbde9235a2c8f1}

#### KLN_INLINE float  [e021](#structkln_1_1entity_1a55a5fdcf5803e20a277088b51407dfdf)() const noexcept  {#structkln_1_1entity_1a55a5fdcf5803e20a277088b51407dfdf}

#### KLN_INLINE float  [e013](#structkln_1_1entity_1a74abd8e8f52f3af1e4f5047bd9726571)() const noexcept  {#structkln_1_1entity_1a74abd8e8f52f3af1e4f5047bd9726571}

#### KLN_INLINE float  [e032](#structkln_1_1entity_1ac571c7e7ad105a50130646f477e8dcea)() const noexcept  {#structkln_1_1entity_1ac571c7e7ad105a50130646f477e8dcea}

#### KLN_INLINE float  [e0123](#structkln_1_1entity_1a429ecf90306003684c804f08351ab530)() const noexcept  {#structkln_1_1entity_1a429ecf90306003684c804f08351ab530}

#### KLN_INLINE __m128 const  &  [p0](#structkln_1_1entity_1abf168e157c9271173de069b6de62bcc1)() const noexcept  {#structkln_1_1entity_1abf168e157c9271173de069b6de62bcc1}

#### KLN_INLINE __m128 const  &  [p1](#structkln_1_1entity_1a7a34322ee2e4b49e404b59a3efc644e1)() const noexcept  {#structkln_1_1entity_1a7a34322ee2e4b49e404b59a3efc644e1}

#### KLN_INLINE __m128 const  &  [p2](#structkln_1_1entity_1a58bd400f84669e248bed438dd18f5239)() const noexcept  {#structkln_1_1entity_1a58bd400f84669e248bed438dd18f5239}

#### KLN_INLINE __m128 const  &  [p3](#structkln_1_1entity_1a677765e6eba5338f2ffea28c7b0cc3bf)() const noexcept  {#structkln_1_1entity_1a677765e6eba5338f2ffea28c7b0cc3bf}

#### KLN_INLINE float const  *  [p0f](#structkln_1_1entity_1aaaeabf34ad615fe756a2ccf7725ef3aa)() const noexcept  {#structkln_1_1entity_1aaaeabf34ad615fe756a2ccf7725ef3aa}

#### KLN_INLINE float const  *  [p1f](#structkln_1_1entity_1a55df7701da4c18be993616a867ed578d)() const noexcept  {#structkln_1_1entity_1a55df7701da4c18be993616a867ed578d}

#### KLN_INLINE float const  *  [p2f](#structkln_1_1entity_1ae72c795b19eb7f44ecec17b58ebecab0)() const noexcept  {#structkln_1_1entity_1ae72c795b19eb7f44ecec17b58ebecab0}

#### KLN_INLINE float const  *  [p3f](#structkln_1_1entity_1a9ae540deeb8a5bd79e5e66a2fad8fc70)() const noexcept  {#structkln_1_1entity_1a9ae540deeb8a5bd79e5e66a2fad8fc70}

#### KLN_INLINE __m128 &  [p0](#structkln_1_1entity_1a3acae1a153b333b8fa033d787a60d551)() noexcept  {#structkln_1_1entity_1a3acae1a153b333b8fa033d787a60d551}

#### KLN_INLINE __m128 &  [p1](#structkln_1_1entity_1a868f7278b039cda4d39d9a75440a6520)() noexcept  {#structkln_1_1entity_1a868f7278b039cda4d39d9a75440a6520}

#### KLN_INLINE __m128 &  [p2](#structkln_1_1entity_1a9655fcede93875b3f59a2ff2a717e7ff)() noexcept  {#structkln_1_1entity_1a9655fcede93875b3f59a2ff2a717e7ff}

#### KLN_INLINE __m128 &  [p3](#structkln_1_1entity_1ac55a05247356a8787cf41c5ad2ebd552)() noexcept  {#structkln_1_1entity_1ac55a05247356a8787cf41c5ad2ebd552}

#### protected  [partition](/Klein/api/kln::entity::partition#unionkln_1_1entity_1_1partition)  [parts](#structkln_1_1entity_1accb4153a7732f7f3649c016b87210b23) {#structkln_1_1entity_1accb4153a7732f7f3649c016b87210b23}

