## struct `kln::line` {#structkln_1_1line}

```
struct kln::line
  : public kln::entity< 0b110 >
```  

A general line in $\PGA$ is given as a 6-coordinate bivector with a direct correspondence to Plücker coordinates. All lines can be exponentiated using the `exp`  method to generate a motor.

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  ` [`line`](#structkln_1_1line_1a51e1c8ea3127970e521a48bf6139224a)`()`  | 
`public  ` [`line`](#structkln_1_1line_1a3a7b1cdde6811a23a30cd5d4082ee5d7)`(float a,float b,float c,float d,float e,float f) noexcept`  | A line is specifed by 6 coordinates which correspond to the line's [Plücker coordinates](https://en.wikipedia.org/wiki/Pl%C3%BCcker_coordinates). The coordinates specified in this way correspond to the following multivector:
`public  ` [`line`](#structkln_1_1line_1ab34c8ce4640a7f82ada73265dc979a2c)`(` [`entity`](../../api/kln_entity#structkln_1_1entity)`< 0b110 > const & e) noexcept`  | 
`public  ` [`line`](#structkln_1_1line_1adea8b05010cbb6b785795ba2f4f91072)`(` [`entity`](../../api/kln_entity#structkln_1_1entity)`< 0b100 > const & e) noexcept`  | 
`public  ` [`line`](#structkln_1_1line_1a0b787e3e257d022d94fd54c0db2f15ef)`(` [`entity`](../../api/kln_entity#structkln_1_1entity)`< 0b10 > const & e) noexcept`  | 
`public float ` [`squared_norm`](#structkln_1_1line_1a941c27dc8594f947ecf718160ebb084b)`() noexcept`  | If a line is constructed as the regressive product (join) of two points, the squared norm provided here is the squared distance between the two points (provided the points are normalized). Returns $d^2 + e^2 + f^2$.
`public float ` [`norm`](#structkln_1_1line_1ad388b8d134c0c22b1f82026277e39c22)`() noexcept`  | Returns the square root of the quantity produced by `squared_norm` .
`public void ` [`normalize`](#structkln_1_1line_1a1bf22b022eadfaf1e9f9179f346a4cd3)`() noexcept`  | Normalize a line such that $\ell^2 = 1$.
`public ` [`entity`](../../api/kln_entity#structkln_1_1entity)`< 0b110 > ` [`exp`](#structkln_1_1line_1ab81feed09b9c02934914071206bf54d1)`() const noexcept`  | Line exponentiation

### Members

####   [line](#structkln_1_1line_1a51e1c8ea3127970e521a48bf6139224a)()  {#structkln_1_1line_1a51e1c8ea3127970e521a48bf6139224a}

####   [line](#structkln_1_1line_1a3a7b1cdde6811a23a30cd5d4082ee5d7)(float a,float b,float c,float d,float e,float f) noexcept  {#structkln_1_1line_1a3a7b1cdde6811a23a30cd5d4082ee5d7}

A line is specifed by 6 coordinates which correspond to the line's [Plücker coordinates](https://en.wikipedia.org/wiki/Pl%C3%BCcker_coordinates). The coordinates specified in this way correspond to the following multivector:

$$a\mathbf{e}_{01} + b\mathbf{e}_{02} + c\mathbf{e}_{03} +\ d\mathbf{e}_{23} + e\mathbf{e}_{31} + f\mathbf{e}_{12}$$

####   [line](#structkln_1_1line_1ab34c8ce4640a7f82ada73265dc979a2c)( [entity](../../api/kln_entity#structkln_1_1entity)< 0b110 > const & e) noexcept  {#structkln_1_1line_1ab34c8ce4640a7f82ada73265dc979a2c}

####   [line](#structkln_1_1line_1adea8b05010cbb6b785795ba2f4f91072)( [entity](../../api/kln_entity#structkln_1_1entity)< 0b100 > const & e) noexcept  {#structkln_1_1line_1adea8b05010cbb6b785795ba2f4f91072}

####   [line](#structkln_1_1line_1a0b787e3e257d022d94fd54c0db2f15ef)( [entity](../../api/kln_entity#structkln_1_1entity)< 0b10 > const & e) noexcept  {#structkln_1_1line_1a0b787e3e257d022d94fd54c0db2f15ef}

#### float  [squared_norm](#structkln_1_1line_1a941c27dc8594f947ecf718160ebb084b)() noexcept  {#structkln_1_1line_1a941c27dc8594f947ecf718160ebb084b}

If a line is constructed as the regressive product (join) of two points, the squared norm provided here is the squared distance between the two points (provided the points are normalized). Returns $d^2 + e^2 + f^2$.

#### float  [norm](#structkln_1_1line_1ad388b8d134c0c22b1f82026277e39c22)() noexcept  {#structkln_1_1line_1ad388b8d134c0c22b1f82026277e39c22}

Returns the square root of the quantity produced by `squared_norm` .

#### void  [normalize](#structkln_1_1line_1a1bf22b022eadfaf1e9f9179f346a4cd3)() noexcept  {#structkln_1_1line_1a1bf22b022eadfaf1e9f9179f346a4cd3}

Normalize a line such that $\ell^2 = 1$.

!!! tip 
    Normalization here is done using the `rsqrtps`
    instruction with a maximum relative error of $1.5\times 2^{-12}$.

####  [entity](../../api/kln_entity#structkln_1_1entity)< 0b110 >  [exp](#structkln_1_1line_1ab81feed09b9c02934914071206bf54d1)() const noexcept  {#structkln_1_1line_1ab81feed09b9c02934914071206bf54d1}

Line exponentiation

The line can be exponentiated to produce a motor that posesses this line as its axis. This routine will be used most often when this line is produced as the logarithm of an existing rotor, then scaled to subdivide or accelerate the motor's action.

