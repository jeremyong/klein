## group `gp` {#group__gp}

The geometric product extends the exterior product with a notion of a metric. When the subspace intersection of the operands of two basis elements is non-zero, instead of the product extinguishing, the grade collapses and a scalar weight is included in the final result according to the metric. The geometric product can be used to build rotations, and by extension, rotations and translations in projective space.

!!! example "Rotor composition" 
    ```cpp
        kln::rotor r1{ang1, x1, y1, z1};
        kln::rotor r2{ang2, x2, y2, z2};
    
        // Compose rotors with the geometric product
        kln::rotor r3 = r1 * r2;; // r3 combines r2 and r1 in that order
    ```
    

!!! example "Two reflections" 
    ```cpp
        kln::plane p1{x1, y1, z1, d1};
        kln::plane p2{x2, y2, z2, d2};
    
        // The geometric product of two planes combines their reflections
        kln::motor m3 = p1 * p2; // m3 combines p2 and p1 in that order
        // If p1 and p2 were parallel, m3 would be a translation. Otherwise,
        // m3 would be a rotation.
    ```
    

Another common usage of the geometric product is to create a transformation that takes one entity to another. Suppose we have two entities $a$ and $b$ and suppose that both entities are normalized such that $a^2 = b^2 = 1$. Then, the action created by $\sqrt{ab}$ is the action that maps $b$ to $a$.

!!! example "Motor between two lines" 
    ```cpp
        kln::line l1{mx1, my1, mz1, dx1, dy1, dz1};
        kln::line l2{mx2, my2, mz2, dx2, dy2, dz2};
        // Ensure lines are normalized if they aren't already
        l1.normalize();
        l2.normalize();
        kln::motor m = kln::sqrt(l1 * l2);
    
        kln::line l3 = m(l2);
        // l3 will be projectively equivalent to l1.
    ```
    

Also provided are division operators that multiply the first argument by the inverse of the second argument.

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public motor KLN_VEC_CALL ` [`operator*`](#group__gp_1gaa3e61221bb38010db55aa0b5f8e17efc)`(plane a,plane b) noexcept`             | Construct a motor $m$ such that $\sqrt{m}$ takes plane $b$ to plane $a$.
`public motor KLN_VEC_CALL ` [`operator*`](#group__gp_1ga6ebccec1c450228f4d70a2862981a6ae)`(plane a,point b) noexcept`             | 
`public motor KLN_VEC_CALL ` [`operator*`](#group__gp_1ga72c655dc80b7be4642a36be1cacc39f7)`(point b,plane a) noexcept`             | 
`public rotor KLN_VEC_CALL ` [`operator*`](#group__gp_1ga2c84f0a8b28b709e973668df084d1529)`(branch a,branch b) noexcept`             | Generate a rotor $r$ such that $\widetilde{\sqrt{r}}$ takes branch $b$ to branch $a$.
`public motor KLN_VEC_CALL ` [`operator*`](#group__gp_1ga152dac80fd07d20e8205a75a651717c7)`(line a,line b) noexcept`             | Generates a motor $m$ that produces a screw motion about the common normal to lines $a$ and $b$. The motor given by $\sqrt{m}$ takes $b$ to $a$ provided that $a$ and $b$ are both normalized.
`public translator KLN_VEC_CALL ` [`operator*`](#group__gp_1ga6d59afd80f83622351ee528209242505)`(point a,point b) noexcept`             | Generates a translator $t$ that produces a displacement along the line between points $a$ and $b$. The translator given by $\sqrt{t}$ takes $b$ to $a$.
`public rotor KLN_VEC_CALL ` [`operator*`](#group__gp_1ga13acc1dbe5763c924a051093829cfa7f)`(rotor a,rotor b) noexcept`             | Composes two rotational actions such that the produced rotor has the same effect as applying rotor $b$, then rotor $a$.
`public line KLN_VEC_CALL ` [`operator*`](#group__gp_1ga8c4d528a130478a054f82d57d4fb7301)`(dual a,line b) noexcept`             | The product of a dual number and a line effectively weights the line with a rotational and translational quantity. Subsequent exponentiation will produce a motor along the screw axis of line $b$ with rotation and translation given by half the scalar and pseudoscalar parts of the dual number $a$ respectively.
`public line KLN_VEC_CALL ` [`operator*`](#group__gp_1ga8ce7535e36f267c43cd82e636cef84f1)`(line b,dual a) noexcept`             | 
`public motor KLN_VEC_CALL ` [`operator*`](#group__gp_1gafdd46a387780ea583d6ab6bb68da17e7)`(rotor a,translator b) noexcept`             | Compose the action of a translator and rotor (`b`  will be applied, then `a` )
`public motor KLN_VEC_CALL ` [`operator*`](#group__gp_1ga8c85df199553c9189e2238de6f8ea75f)`(translator b,rotor a) noexcept`             | Compose the action of a rotor and translator (`a`  will be applied, then `b` )
`public translator KLN_VEC_CALL ` [`operator*`](#group__gp_1gae58f3fe871600c10a862f0d798ecfa9a)`(translator a,translator b) noexcept`             | Compose the action of two translators (this operation is commutative for these operands).
`public motor KLN_VEC_CALL ` [`operator*`](#group__gp_1ga6b7806b8e0563902a4799e8a96023419)`(rotor a,motor b) noexcept`             | Compose the action of a rotor and motor (`b`  will be applied, then `a` )
`public motor KLN_VEC_CALL ` [`operator*`](#group__gp_1ga0d66c1ed07072e669a6618c8a2cd3915)`(motor b,rotor a) noexcept`             | Compose the action of a rotor and motor (`a`  will be applied, then `b` )
`public motor KLN_VEC_CALL ` [`operator*`](#group__gp_1gaf71d001695eb98b0dbde90039957feda)`(translator a,motor b) noexcept`             | Compose the action of a translator and motor (`b`  will be applied, then `a` )
`public motor KLN_VEC_CALL ` [`operator*`](#group__gp_1gae243255b3c91515f8a651ad3ce531650)`(motor b,translator a) noexcept`             | Compose the action of a translator and motor (`a`  will be applied, then `b` )
`public motor KLN_VEC_CALL ` [`operator*`](#group__gp_1ga88f8e53b1842ca28ec1456d887144fec)`(motor a,motor b) noexcept`             | Compose the action of two motors (`b`  will be applied, then `a` )
`public motor KLN_VEC_CALL ` [`operator/`](#group__gp_1gae07ffecb7a36960edc6959958faabc66)`(plane a,plane b) noexcept`             | 
`public translator KLN_VEC_CALL ` [`operator/`](#group__gp_1gab85d0363fbcf716788bedca7d82dbf33)`(point a,point b) noexcept`             | 
`public rotor KLN_VEC_CALL ` [`operator/`](#group__gp_1gae2b0b438f70ae7fdcb0bab00472074ec)`(branch a,branch b) noexcept`             | 
`public rotor KLN_VEC_CALL ` [`operator/`](#group__gp_1ga9ed0e3e8b451b340f465d8f910d1ab35)`(rotor a,rotor b) noexcept`             | 
`public translator KLN_VEC_CALL ` [`operator/`](#group__gp_1ga3bcbe21374e5abcbdcb62586091a9540)`(translator a,translator b) noexcept`             | 
`public motor KLN_VEC_CALL ` [`operator/`](#group__gp_1ga391b74b2c0cab4a1fd80505ddd18763b)`(line a,line b) noexcept`             | 
`public motor KLN_VEC_CALL ` [`operator/`](#group__gp_1gadf3632ea9928e28c4293deff327bdb6c)`(motor a,rotor b) noexcept`             | 
`public motor KLN_VEC_CALL ` [`operator/`](#group__gp_1gac04a8339b0036a0949b2cdd30a7dbcfc)`(motor a,translator b) noexcept`             | 
`public motor KLN_VEC_CALL ` [`operator/`](#group__gp_1ga195ed6702368641d3c46f5afe1f752d3)`(motor a,motor b) noexcept`             | 

### Members

#### motor KLN_VEC_CALL  [operator*](#group__gp_1gaa3e61221bb38010db55aa0b5f8e17efc)(plane a,plane b) noexcept  {#group__gp_1gaa3e61221bb38010db55aa0b5f8e17efc}

Construct a motor $m$ such that $\sqrt{m}$ takes plane $b$ to plane $a$.

!!! example 
    ```cpp
        kln::plane p1{x1, y1, z1, d1};
        kln::plane p2{x2, y2, z2, d2};
        kln::motor m = sqrt(p1 * p2);
        plane p3 = m(p2);
        // p3 will be approximately equal to p1
    ```

#### motor KLN_VEC_CALL  [operator*](#group__gp_1ga6ebccec1c450228f4d70a2862981a6ae)(plane a,point b) noexcept  {#group__gp_1ga6ebccec1c450228f4d70a2862981a6ae}

#### motor KLN_VEC_CALL  [operator*](#group__gp_1ga72c655dc80b7be4642a36be1cacc39f7)(point b,plane a) noexcept  {#group__gp_1ga72c655dc80b7be4642a36be1cacc39f7}

#### rotor KLN_VEC_CALL  [operator*](#group__gp_1ga2c84f0a8b28b709e973668df084d1529)(branch a,branch b) noexcept  {#group__gp_1ga2c84f0a8b28b709e973668df084d1529}

Generate a rotor $r$ such that $\widetilde{\sqrt{r}}$ takes branch $b$ to branch $a$.

#### motor KLN_VEC_CALL  [operator*](#group__gp_1ga152dac80fd07d20e8205a75a651717c7)(line a,line b) noexcept  {#group__gp_1ga152dac80fd07d20e8205a75a651717c7}

Generates a motor $m$ that produces a screw motion about the common normal to lines $a$ and $b$. The motor given by $\sqrt{m}$ takes $b$ to $a$ provided that $a$ and $b$ are both normalized.

#### translator KLN_VEC_CALL  [operator*](#group__gp_1ga6d59afd80f83622351ee528209242505)(point a,point b) noexcept  {#group__gp_1ga6d59afd80f83622351ee528209242505}

Generates a translator $t$ that produces a displacement along the line between points $a$ and $b$. The translator given by $\sqrt{t}$ takes $b$ to $a$.

#### rotor KLN_VEC_CALL  [operator*](#group__gp_1ga13acc1dbe5763c924a051093829cfa7f)(rotor a,rotor b) noexcept  {#group__gp_1ga13acc1dbe5763c924a051093829cfa7f}

Composes two rotational actions such that the produced rotor has the same effect as applying rotor $b$, then rotor $a$.

#### line KLN_VEC_CALL  [operator*](#group__gp_1ga8c4d528a130478a054f82d57d4fb7301)(dual a,line b) noexcept  {#group__gp_1ga8c4d528a130478a054f82d57d4fb7301}

The product of a dual number and a line effectively weights the line with a rotational and translational quantity. Subsequent exponentiation will produce a motor along the screw axis of line $b$ with rotation and translation given by half the scalar and pseudoscalar parts of the dual number $a$ respectively.

#### line KLN_VEC_CALL  [operator*](#group__gp_1ga8ce7535e36f267c43cd82e636cef84f1)(line b,dual a) noexcept  {#group__gp_1ga8ce7535e36f267c43cd82e636cef84f1}

#### motor KLN_VEC_CALL  [operator*](#group__gp_1gafdd46a387780ea583d6ab6bb68da17e7)(rotor a,translator b) noexcept  {#group__gp_1gafdd46a387780ea583d6ab6bb68da17e7}

Compose the action of a translator and rotor (`b`  will be applied, then `a` )

#### motor KLN_VEC_CALL  [operator*](#group__gp_1ga8c85df199553c9189e2238de6f8ea75f)(translator b,rotor a) noexcept  {#group__gp_1ga8c85df199553c9189e2238de6f8ea75f}

Compose the action of a rotor and translator (`a`  will be applied, then `b` )

#### translator KLN_VEC_CALL  [operator*](#group__gp_1gae58f3fe871600c10a862f0d798ecfa9a)(translator a,translator b) noexcept  {#group__gp_1gae58f3fe871600c10a862f0d798ecfa9a}

Compose the action of two translators (this operation is commutative for these operands).

#### motor KLN_VEC_CALL  [operator*](#group__gp_1ga6b7806b8e0563902a4799e8a96023419)(rotor a,motor b) noexcept  {#group__gp_1ga6b7806b8e0563902a4799e8a96023419}

Compose the action of a rotor and motor (`b`  will be applied, then `a` )

#### motor KLN_VEC_CALL  [operator*](#group__gp_1ga0d66c1ed07072e669a6618c8a2cd3915)(motor b,rotor a) noexcept  {#group__gp_1ga0d66c1ed07072e669a6618c8a2cd3915}

Compose the action of a rotor and motor (`a`  will be applied, then `b` )

#### motor KLN_VEC_CALL  [operator*](#group__gp_1gaf71d001695eb98b0dbde90039957feda)(translator a,motor b) noexcept  {#group__gp_1gaf71d001695eb98b0dbde90039957feda}

Compose the action of a translator and motor (`b`  will be applied, then `a` )

#### motor KLN_VEC_CALL  [operator*](#group__gp_1gae243255b3c91515f8a651ad3ce531650)(motor b,translator a) noexcept  {#group__gp_1gae243255b3c91515f8a651ad3ce531650}

Compose the action of a translator and motor (`a`  will be applied, then `b` )

#### motor KLN_VEC_CALL  [operator*](#group__gp_1ga88f8e53b1842ca28ec1456d887144fec)(motor a,motor b) noexcept  {#group__gp_1ga88f8e53b1842ca28ec1456d887144fec}

Compose the action of two motors (`b`  will be applied, then `a` )

#### motor KLN_VEC_CALL  [operator/](#group__gp_1gae07ffecb7a36960edc6959958faabc66)(plane a,plane b) noexcept  {#group__gp_1gae07ffecb7a36960edc6959958faabc66}

#### translator KLN_VEC_CALL  [operator/](#group__gp_1gab85d0363fbcf716788bedca7d82dbf33)(point a,point b) noexcept  {#group__gp_1gab85d0363fbcf716788bedca7d82dbf33}

#### rotor KLN_VEC_CALL  [operator/](#group__gp_1gae2b0b438f70ae7fdcb0bab00472074ec)(branch a,branch b) noexcept  {#group__gp_1gae2b0b438f70ae7fdcb0bab00472074ec}

#### rotor KLN_VEC_CALL  [operator/](#group__gp_1ga9ed0e3e8b451b340f465d8f910d1ab35)(rotor a,rotor b) noexcept  {#group__gp_1ga9ed0e3e8b451b340f465d8f910d1ab35}

#### translator KLN_VEC_CALL  [operator/](#group__gp_1ga3bcbe21374e5abcbdcb62586091a9540)(translator a,translator b) noexcept  {#group__gp_1ga3bcbe21374e5abcbdcb62586091a9540}

#### motor KLN_VEC_CALL  [operator/](#group__gp_1ga391b74b2c0cab4a1fd80505ddd18763b)(line a,line b) noexcept  {#group__gp_1ga391b74b2c0cab4a1fd80505ddd18763b}

#### motor KLN_VEC_CALL  [operator/](#group__gp_1gadf3632ea9928e28c4293deff327bdb6c)(motor a,rotor b) noexcept  {#group__gp_1gadf3632ea9928e28c4293deff327bdb6c}

#### motor KLN_VEC_CALL  [operator/](#group__gp_1gac04a8339b0036a0949b2cdd30a7dbcfc)(motor a,translator b) noexcept  {#group__gp_1gac04a8339b0036a0949b2cdd30a7dbcfc}

#### motor KLN_VEC_CALL  [operator/](#group__gp_1ga195ed6702368641d3c46f5afe1f752d3)(motor a,motor b) noexcept  {#group__gp_1ga195ed6702368641d3c46f5afe1f752d3}

