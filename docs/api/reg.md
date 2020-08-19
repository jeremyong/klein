## group `reg` {#group__reg}

The regressive product is implemented in terms of the exterior product. Given multivectors $\mathbf{a}$ and $\mathbf{b}$, the regressive product $\mathbf{a}\vee\mathbf{b}$ is equivalent to $J(J(\mathbf{a})\wedge J(\mathbf{b}))$. Thus, both meets and joins reside in the same algebraic structure.

!!! example "Joining two points" 
    ```cpp
        kln::point p1{x1, y1, z1};
        kln::point p2{x2, y2, z2};
    
        // l contains both p1 and p2.
        kln::line l = p1 & p2;
    ```
    

!!! example "Joining a line and a point" 
    ```cpp
        kln::point p1{x, y, z};
        kln::line l2{mx, my, mz, dx, dy, dz};
    
        // p2 contains both p1 and l2.
        kln::plane p2 = p1 & l2;
    ```

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public line KLN_VEC_CALL ` [`operator&`](#group__reg_1ga63b0997f8119571d904e3c02673d8bbb)`(point a,point b) noexcept`             | 
`public plane KLN_VEC_CALL ` [`operator&`](#group__reg_1gad37eea7e6c630474cae21c6a6d76dfd1)`(point a,line b) noexcept`             | 
`public plane KLN_VEC_CALL ` [`operator&`](#group__reg_1ga6be92308d719cd634211b5fc0909d00c)`(line b,point a) noexcept`             | 
`public plane KLN_VEC_CALL ` [`operator&`](#group__reg_1ga9f3f5c16881afe59f2c77e2977653094)`(point a,branch b) noexcept`             | 
`public plane KLN_VEC_CALL ` [`operator&`](#group__reg_1ga7b9ddcd88aa6a10b980b69de28aebeb3)`(branch b,point a) noexcept`             | 
`public plane KLN_VEC_CALL ` [`operator&`](#group__reg_1ga05885edf19c3ef66e942390073922bd0)`(point a,ideal_line b) noexcept`             | 
`public plane KLN_VEC_CALL ` [`operator&`](#group__reg_1ga2da1a859d4b8c745a77855eabc380980)`(ideal_line b,point a) noexcept`             | 
`public dual KLN_VEC_CALL ` [`operator&`](#group__reg_1gaff23302987cbc2a0a33bae1420992e01)`(plane a,point b) noexcept`             | 
`public dual KLN_VEC_CALL ` [`operator&`](#group__reg_1ga66d87e84a1c2618381cb696800164ecc)`(point a,plane b) noexcept`             | 

### Members

#### line KLN_VEC_CALL  [operator&](#group__reg_1ga63b0997f8119571d904e3c02673d8bbb)(point a,point b) noexcept  {#group__reg_1ga63b0997f8119571d904e3c02673d8bbb}

#### plane KLN_VEC_CALL  [operator&](#group__reg_1gad37eea7e6c630474cae21c6a6d76dfd1)(point a,line b) noexcept  {#group__reg_1gad37eea7e6c630474cae21c6a6d76dfd1}

#### plane KLN_VEC_CALL  [operator&](#group__reg_1ga6be92308d719cd634211b5fc0909d00c)(line b,point a) noexcept  {#group__reg_1ga6be92308d719cd634211b5fc0909d00c}

#### plane KLN_VEC_CALL  [operator&](#group__reg_1ga9f3f5c16881afe59f2c77e2977653094)(point a,branch b) noexcept  {#group__reg_1ga9f3f5c16881afe59f2c77e2977653094}

#### plane KLN_VEC_CALL  [operator&](#group__reg_1ga7b9ddcd88aa6a10b980b69de28aebeb3)(branch b,point a) noexcept  {#group__reg_1ga7b9ddcd88aa6a10b980b69de28aebeb3}

#### plane KLN_VEC_CALL  [operator&](#group__reg_1ga05885edf19c3ef66e942390073922bd0)(point a,ideal_line b) noexcept  {#group__reg_1ga05885edf19c3ef66e942390073922bd0}

#### plane KLN_VEC_CALL  [operator&](#group__reg_1ga2da1a859d4b8c745a77855eabc380980)(ideal_line b,point a) noexcept  {#group__reg_1ga2da1a859d4b8c745a77855eabc380980}

#### dual KLN_VEC_CALL  [operator&](#group__reg_1gaff23302987cbc2a0a33bae1420992e01)(plane a,point b) noexcept  {#group__reg_1gaff23302987cbc2a0a33bae1420992e01}

#### dual KLN_VEC_CALL  [operator&](#group__reg_1ga66d87e84a1c2618381cb696800164ecc)(point a,plane b) noexcept  {#group__reg_1ga66d87e84a1c2618381cb696800164ecc}

