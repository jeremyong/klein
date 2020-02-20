## struct `kln::direction` {#structkln_1_1direction}

```
struct kln::direction
  : public kln::entity< 0b1000 >
```  

Directions in $\mathbf{P}(\mathbb{R}^3_{3, 0, 1})$ are represented using points at infinity (homogeneous coordinate 0). Having a homogeneous coordinate of zero ensures that directions are translation-invariant.

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  ` [`direction`](#structkln_1_1direction_1a6d22510e72f67516a65a2ee39a5591a3)`() = default`  | 
`public  ` [`direction`](#structkln_1_1direction_1a8fc796733d32a69230136b8376003fca)`(float x,float y,float z) noexcept`  | Create a normalized direction.
`public  ` [`direction`](#structkln_1_1direction_1a81cd76b26d928f02e830d8c0175157d6)`(` [`entity`](/Klein/api/kln::entity#structkln_1_1entity)`< 0b1000 > const & e) noexcept`  | 
`public constexpr float ` [`operator[]`](#structkln_1_1direction_1a8fa09342bff2583a7f29d04adf6dd3c2)`(size_t i) const noexcept`  | 
`public constexpr float & ` [`operator[]`](#structkln_1_1direction_1a67a82ca405563ca75b7f8a84842e42c0)`(size_t i) noexcept`  | 
`public float ` [`x`](#structkln_1_1direction_1a721087c2056a33cd780c678ae0ec39dd)`() const noexcept`  | 
`public float & ` [`x`](#structkln_1_1direction_1a161c9821553a28babae050e37a0d1096)`() noexcept`  | 
`public float ` [`y`](#structkln_1_1direction_1a40bc7052a639d57afde7a860c1631638)`() const noexcept`  | 
`public float & ` [`y`](#structkln_1_1direction_1a582345212cc5165ac7f3b1c5483dd17c)`() noexcept`  | 
`public float ` [`z`](#structkln_1_1direction_1a1e16d3ed0ff945d0d1cbf1e6458d334b)`() const noexcept`  | 
`public float & ` [`z`](#structkln_1_1direction_1aff096710eaf0b26832f00b5313bdac75)`() noexcept`  | 
`public void ` [`normalize`](#structkln_1_1direction_1a143cd2cfeb94860ce1d47b9735064802)`() noexcept`  | Normalize this direction by dividing all components by the square magnitude

### Members

####   [direction](#structkln_1_1direction_1a6d22510e72f67516a65a2ee39a5591a3)() = default  {#structkln_1_1direction_1a6d22510e72f67516a65a2ee39a5591a3}

####   [direction](#structkln_1_1direction_1a8fc796733d32a69230136b8376003fca)(float x,float y,float z) noexcept  {#structkln_1_1direction_1a8fc796733d32a69230136b8376003fca}

Create a normalized direction.

####   [direction](#structkln_1_1direction_1a81cd76b26d928f02e830d8c0175157d6)( [entity](/Klein/api/kln::entity#structkln_1_1entity)< 0b1000 > const & e) noexcept  {#structkln_1_1direction_1a81cd76b26d928f02e830d8c0175157d6}

#### float  [operator[]](#structkln_1_1direction_1a8fa09342bff2583a7f29d04adf6dd3c2)(size_t i) const noexcept  {#structkln_1_1direction_1a8fa09342bff2583a7f29d04adf6dd3c2}

#### float &  [operator[]](#structkln_1_1direction_1a67a82ca405563ca75b7f8a84842e42c0)(size_t i) noexcept  {#structkln_1_1direction_1a67a82ca405563ca75b7f8a84842e42c0}

#### float  [x](#structkln_1_1direction_1a721087c2056a33cd780c678ae0ec39dd)() const noexcept  {#structkln_1_1direction_1a721087c2056a33cd780c678ae0ec39dd}

#### float &  [x](#structkln_1_1direction_1a161c9821553a28babae050e37a0d1096)() noexcept  {#structkln_1_1direction_1a161c9821553a28babae050e37a0d1096}

#### float  [y](#structkln_1_1direction_1a40bc7052a639d57afde7a860c1631638)() const noexcept  {#structkln_1_1direction_1a40bc7052a639d57afde7a860c1631638}

#### float &  [y](#structkln_1_1direction_1a582345212cc5165ac7f3b1c5483dd17c)() noexcept  {#structkln_1_1direction_1a582345212cc5165ac7f3b1c5483dd17c}

#### float  [z](#structkln_1_1direction_1a1e16d3ed0ff945d0d1cbf1e6458d334b)() const noexcept  {#structkln_1_1direction_1a1e16d3ed0ff945d0d1cbf1e6458d334b}

#### float &  [z](#structkln_1_1direction_1aff096710eaf0b26832f00b5313bdac75)() noexcept  {#structkln_1_1direction_1aff096710eaf0b26832f00b5313bdac75}

#### void  [normalize](#structkln_1_1direction_1a143cd2cfeb94860ce1d47b9735064802)() noexcept  {#structkln_1_1direction_1a143cd2cfeb94860ce1d47b9735064802}

Normalize this direction by dividing all components by the square magnitude

!!! tip 
    Direction normalization divides the coordinates by the quantity
    a^2 + b^2 + c^2. This is done using the `rcpps` instruction with a
    maximum relative error of $1.5\times 2^{-12}$.

