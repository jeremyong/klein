## group `gp` {#group__gp}

The geometric product extends the exterior product with a notion of a metric. When the subspace intersection of the operands of two basis elements is non-zero, instead of the product extinguishing, the grade collapses and a scalar weight is included in the final result according to the metric. The geometric product can be used to build rotations, and by extension, rotations and translations in projective space.

!!! example Rotor composition 
    ```cpp
        kln::rotor r1{ang1, x1, y1, z1};
        kln::rotor r2{ang2, x2, y2, z2};
    
        // Compose rotors with the geometric product
        kln::rotor r3 = r1 * r2;; // r3 combines r2 and r1 in that order
    ```
    

!!! example Two reflections 
    ```cpp
        kln::plane p1{x1, y1, z1, d1};
        kln::plane p2{x2, y2, z2, d2};
    
        // The geometric product of two planes combines their reflections
        kln::motor m3 = p1 * p2;; // m3 combines p2 and p1 in that order
    ```

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public motor KLN_VEC_CALL ` [`operator*`](#group__gp_1gaa3e61221bb38010db55aa0b5f8e17efc)`(plane a,plane b) noexcept`             | 
`public motor KLN_VEC_CALL ` [`operator*`](#group__gp_1ga6ebccec1c450228f4d70a2862981a6ae)`(plane a,point b) noexcept`             | 
`public motor KLN_VEC_CALL ` [`operator*`](#group__gp_1ga72c655dc80b7be4642a36be1cacc39f7)`(point b,plane a) noexcept`             | 
`public motor KLN_VEC_CALL ` [`operator*`](#group__gp_1ga152dac80fd07d20e8205a75a651717c7)`(line a,line b) noexcept`             | 
`public motor KLN_VEC_CALL ` [`operator*`](#group__gp_1ga6f6fbd02c08bc9ef8e1b598a402e6b4d)`(point a,point b) noexcept`             | 
`public rotor KLN_VEC_CALL ` [`operator*`](#group__gp_1ga13acc1dbe5763c924a051093829cfa7f)`(rotor a,rotor b) noexcept`             | 
`public line KLN_VEC_CALL ` [`operator*`](#group__gp_1ga8c4d528a130478a054f82d57d4fb7301)`(dual a,line b) noexcept`             | The product of a dual number and a line effectively weights the line with a rotational and translational quantity. Subsequent exponentiation will produce a motor along the screw axis of line $b$ with rotation and translation given by half the scalar and pseudoscalar parts of the dual number $a$ respectively.
`public line KLN_VEC_CALL ` [`operator*`](#group__gp_1ga8ce7535e36f267c43cd82e636cef84f1)`(line b,dual a) noexcept`             | 
`public motor KLN_VEC_CALL ` [`operator*`](#group__gp_1gafdd46a387780ea583d6ab6bb68da17e7)`(rotor a,translator b) noexcept`             | 
`public motor KLN_VEC_CALL ` [`operator*`](#group__gp_1ga8c85df199553c9189e2238de6f8ea75f)`(translator b,rotor a) noexcept`             | 
`public translator KLN_VEC_CALL ` [`operator*`](#group__gp_1gae58f3fe871600c10a862f0d798ecfa9a)`(translator a,translator b) noexcept`             | 
`public motor KLN_VEC_CALL ` [`operator*`](#group__gp_1ga88f8e53b1842ca28ec1456d887144fec)`(motor a,motor b) noexcept`             | 

### Members

#### motor KLN_VEC_CALL  [operator*](#group__gp_1gaa3e61221bb38010db55aa0b5f8e17efc)(plane a,plane b) noexcept  {#group__gp_1gaa3e61221bb38010db55aa0b5f8e17efc}

#### motor KLN_VEC_CALL  [operator*](#group__gp_1ga6ebccec1c450228f4d70a2862981a6ae)(plane a,point b) noexcept  {#group__gp_1ga6ebccec1c450228f4d70a2862981a6ae}

#### motor KLN_VEC_CALL  [operator*](#group__gp_1ga72c655dc80b7be4642a36be1cacc39f7)(point b,plane a) noexcept  {#group__gp_1ga72c655dc80b7be4642a36be1cacc39f7}

#### motor KLN_VEC_CALL  [operator*](#group__gp_1ga152dac80fd07d20e8205a75a651717c7)(line a,line b) noexcept  {#group__gp_1ga152dac80fd07d20e8205a75a651717c7}

#### motor KLN_VEC_CALL  [operator*](#group__gp_1ga6f6fbd02c08bc9ef8e1b598a402e6b4d)(point a,point b) noexcept  {#group__gp_1ga6f6fbd02c08bc9ef8e1b598a402e6b4d}

#### rotor KLN_VEC_CALL  [operator*](#group__gp_1ga13acc1dbe5763c924a051093829cfa7f)(rotor a,rotor b) noexcept  {#group__gp_1ga13acc1dbe5763c924a051093829cfa7f}

#### line KLN_VEC_CALL  [operator*](#group__gp_1ga8c4d528a130478a054f82d57d4fb7301)(dual a,line b) noexcept  {#group__gp_1ga8c4d528a130478a054f82d57d4fb7301}

The product of a dual number and a line effectively weights the line with a rotational and translational quantity. Subsequent exponentiation will produce a motor along the screw axis of line $b$ with rotation and translation given by half the scalar and pseudoscalar parts of the dual number $a$ respectively.

#### line KLN_VEC_CALL  [operator*](#group__gp_1ga8ce7535e36f267c43cd82e636cef84f1)(line b,dual a) noexcept  {#group__gp_1ga8ce7535e36f267c43cd82e636cef84f1}

#### motor KLN_VEC_CALL  [operator*](#group__gp_1gafdd46a387780ea583d6ab6bb68da17e7)(rotor a,translator b) noexcept  {#group__gp_1gafdd46a387780ea583d6ab6bb68da17e7}

#### motor KLN_VEC_CALL  [operator*](#group__gp_1ga8c85df199553c9189e2238de6f8ea75f)(translator b,rotor a) noexcept  {#group__gp_1ga8c85df199553c9189e2238de6f8ea75f}

#### translator KLN_VEC_CALL  [operator*](#group__gp_1gae58f3fe871600c10a862f0d798ecfa9a)(translator a,translator b) noexcept  {#group__gp_1gae58f3fe871600c10a862f0d798ecfa9a}

#### motor KLN_VEC_CALL  [operator*](#group__gp_1ga88f8e53b1842ca28ec1456d887144fec)(motor a,motor b) noexcept  {#group__gp_1ga88f8e53b1842ca28ec1456d887144fec}

