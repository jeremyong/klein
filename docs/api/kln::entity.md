## struct `kln::entity` 

```
struct kln::entity
  : public kln::base_entity
```  

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  entity()`  | 
`public  entity(` [`entity`](#structkln_1_1entity) ` const & other)`  | 
`public template<>`  <br/>`constexpr auto operator+(` [`entity`](#structkln_1_1entity) `< P > const & other) const noexcept`  | 
`public template<>`  <br/>`constexpr auto operator+(` [`entity`](#structkln_1_1entity) `< P > const & other) noexcept`  | 
`public template<>`  <br/>`constexpr auto operator-(` [`entity`](#structkln_1_1entity) `< P > const & other) const noexcept`  | 
`public template<>`  <br/>`constexpr auto operator-(` [`entity`](#structkln_1_1entity) `< P > const & other) noexcept`  | 
`public ` [`entity`](#structkln_1_1entity) ` & operator*=(float scalar) noexcept`  | 
`public ` [`entity`](#structkln_1_1entity) ` operator*(float scalar) const noexcept`  | 
`public ` [`entity`](#structkln_1_1entity) ` & operator/=(float s) noexcept`  | 
`public ` [`entity`](#structkln_1_1entity) ` operator/(float s) const noexcept`  | 
`public constexpr ` [`entity`](#structkln_1_1entity) ` operator~() const noexcept`  | 
`public template<>`  <br/>`constexpr auto operator^(` [`entity`](#structkln_1_1entity) `< PMask2 > const & rhs) const noexcept`  | 
`public constexpr auto operator!() const noexcept`  | 
`public template<>`  <br/>`constexpr auto operator&(` [`entity`](#structkln_1_1entity) `< PMask2 > const & rhs) const noexcept`  | 
`public template<>`  <br/>`constexpr auto operator*(` [`entity`](#structkln_1_1entity) `< PMask2 > const & rhs) const noexcept`  | 
`public constexpr float scalar() const noexcept`  | 
`public constexpr float e0() const noexcept`  | 
`public constexpr float e1() const noexcept`  | 
`public constexpr float e2() const noexcept`  | 
`public constexpr float e3() const noexcept`  | 
`public constexpr float e12() const noexcept`  | 
`public constexpr float e21() const noexcept`  | 
`public constexpr float e31() const noexcept`  | 
`public constexpr float e13() const noexcept`  | 
`public constexpr float e23() const noexcept`  | 
`public constexpr float e32() const noexcept`  | 
`public constexpr float e01() const noexcept`  | 
`public constexpr float e10() const noexcept`  | 
`public constexpr float e02() const noexcept`  | 
`public constexpr float e20() const noexcept`  | 
`public constexpr float e03() const noexcept`  | 
`public constexpr float e30() const noexcept`  | 
`public constexpr float e123() const noexcept`  | 
`public constexpr float e021() const noexcept`  | 
`public constexpr float e013() const noexcept`  | 
`public constexpr float e032() const noexcept`  | 
`public constexpr float e0123() const noexcept`  | 
`public __m128 const  & p0() const noexcept`  | 
`public __m128 const  & p1() const noexcept`  | 
`public __m128 const  & p2() const noexcept`  | 
`public __m128 const  & p3() const noexcept`  | 
`public float const  * p0f() const noexcept`  | 
`public float const  * p1f() const noexcept`  | 
`public float const  * p2f() const noexcept`  | 
`public float const  * p3f() const noexcept`  | 
`public __m128 & p0() noexcept`  | 
`public __m128 & p1() noexcept`  | 
`public __m128 & p2() noexcept`  | 
`public __m128 & p3() noexcept`  | 
`protected ` [`partition`](/api/kln::partition#unionkln_1_1partition) ` ` [`parts`](#structkln_1_1entity_1accb4153a7732f7f3649c016b87210b23)   | 

### Members

#### `public  entity()`  

#### `public  entity(` [`entity`](#structkln_1_1entity) ` const & other)`  

#### `public template<>`  <br/>`constexpr auto operator+(` [`entity`](#structkln_1_1entity) `< P > const & other) const noexcept`  

#### `public template<>`  <br/>`constexpr auto operator+(` [`entity`](#structkln_1_1entity) `< P > const & other) noexcept`  

#### `public template<>`  <br/>`constexpr auto operator-(` [`entity`](#structkln_1_1entity) `< P > const & other) const noexcept`  

#### `public template<>`  <br/>`constexpr auto operator-(` [`entity`](#structkln_1_1entity) `< P > const & other) noexcept`  

#### `public ` [`entity`](#structkln_1_1entity) ` & operator*=(float scalar) noexcept`  

#### `public ` [`entity`](#structkln_1_1entity) ` operator*(float scalar) const noexcept`  

#### `public ` [`entity`](#structkln_1_1entity) ` & operator/=(float s) noexcept`  

#### `public ` [`entity`](#structkln_1_1entity) ` operator/(float s) const noexcept`  

#### `public constexpr ` [`entity`](#structkln_1_1entity) ` operator~() const noexcept`  

#### `public template<>`  <br/>`constexpr auto operator^(` [`entity`](#structkln_1_1entity) `< PMask2 > const & rhs) const noexcept`  

#### `public constexpr auto operator!() const noexcept`  

#### `public template<>`  <br/>`constexpr auto operator&(` [`entity`](#structkln_1_1entity) `< PMask2 > const & rhs) const noexcept`  

#### `public template<>`  <br/>`constexpr auto operator*(` [`entity`](#structkln_1_1entity) `< PMask2 > const & rhs) const noexcept`  

#### `public constexpr float scalar() const noexcept`  

#### `public constexpr float e0() const noexcept`  

#### `public constexpr float e1() const noexcept`  

#### `public constexpr float e2() const noexcept`  

#### `public constexpr float e3() const noexcept`  

#### `public constexpr float e12() const noexcept`  

#### `public constexpr float e21() const noexcept`  

#### `public constexpr float e31() const noexcept`  

#### `public constexpr float e13() const noexcept`  

#### `public constexpr float e23() const noexcept`  

#### `public constexpr float e32() const noexcept`  

#### `public constexpr float e01() const noexcept`  

#### `public constexpr float e10() const noexcept`  

#### `public constexpr float e02() const noexcept`  

#### `public constexpr float e20() const noexcept`  

#### `public constexpr float e03() const noexcept`  

#### `public constexpr float e30() const noexcept`  

#### `public constexpr float e123() const noexcept`  

#### `public constexpr float e021() const noexcept`  

#### `public constexpr float e013() const noexcept`  

#### `public constexpr float e032() const noexcept`  

#### `public constexpr float e0123() const noexcept`  

#### `public __m128 const  & p0() const noexcept`  

#### `public __m128 const  & p1() const noexcept`  

#### `public __m128 const  & p2() const noexcept`  

#### `public __m128 const  & p3() const noexcept`  

#### `public float const  * p0f() const noexcept`  

#### `public float const  * p1f() const noexcept`  

#### `public float const  * p2f() const noexcept`  

#### `public float const  * p3f() const noexcept`  

#### `public __m128 & p0() noexcept`  

#### `public __m128 & p1() noexcept`  

#### `public __m128 & p2() noexcept`  

#### `public __m128 & p3() noexcept`  

#### `protected ` [`partition`](/api/kln::partition#unionkln_1_1partition) ` ` [`parts`](#structkln_1_1entity_1accb4153a7732f7f3649c016b87210b23)   

