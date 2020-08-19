## group `ext` {#group__ext}

([meet.hpp](../../api/undefined#meet_8hpp))

The exterior product between two basis elements extinguishes if the two operands share any common index. Otherwise, the element produced is equivalent to the union of the subspaces. A sign flip is introduced if the concatenation of the element indices is an odd permutation of the cyclic basis representation. The exterior product extends to general multivectors by linearity.

!!! example "Meeting two planes" 
    ```cpp
        kln::plane p1{x1, y1, z1, d1};
        kln::plane p2{x2, y2, z2, d2};
    
        // l lies at the intersection of p1 and p2.
        kln::line l = p1 ^ p2;
    ```
    

!!! example "Meeting a line and a plane" 
    ```cpp
        kln::plane p1{x, y, z, d};
        kln::line l2{mx, my, mz, dx, dy, dz};
    
        // p2 lies at the intersection of p1 and l2.
        kln::point p2 = p1 ^ l2;
    ```

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public line KLN_VEC_CALL ` [`operator^`](#group__ext_1gaf6b69634e1bd50ac311c3c3809e0d3f0)`(plane a,plane b) noexcept`             | 
`public point KLN_VEC_CALL ` [`operator^`](#group__ext_1gaddd37930213efde0f90e8abb0f60c2bc)`(plane a,branch b) noexcept`             | 
`public point KLN_VEC_CALL ` [`operator^`](#group__ext_1ga17077e02ba6e4391e6fdf056ae06da76)`(branch b,plane a) noexcept`             | 
`public point KLN_VEC_CALL ` [`operator^`](#group__ext_1ga7c2f4e2deca4fc77fe75ff0fc608ed23)`(plane a,ideal_line b) noexcept`             | 
`public point KLN_VEC_CALL ` [`operator^`](#group__ext_1ga0aa1144df65f9d813a10f258d06277ae)`(ideal_line b,plane a) noexcept`             | 
`public point KLN_VEC_CALL ` [`operator^`](#group__ext_1gaa1676d98117be736ee2bba5f56e309b3)`(plane a,line b) noexcept`             | 
`public point KLN_VEC_CALL ` [`operator^`](#group__ext_1gaf6b24c4d8ecfa0b241e6549f6ce55531)`(line b,plane a) noexcept`             | 
`public dual KLN_VEC_CALL ` [`operator^`](#group__ext_1ga4586341ae4d37e91856b56a6890ce5f8)`(plane a,point b) noexcept`             | 
`public dual KLN_VEC_CALL ` [`operator^`](#group__ext_1ga0ca0c0ab8d43f634ca56afd825f9d44e)`(point b,plane a) noexcept`             | 
`public dual KLN_VEC_CALL ` [`operator^`](#group__ext_1gad6a59a5e1fce6d154880a2f703d57904)`(branch a,ideal_line b) noexcept`             | 
`public dual KLN_VEC_CALL ` [`operator^`](#group__ext_1gab85e4f6b524bf5ced8e69bed740a5c36)`(ideal_line b,branch a) noexcept`             | 
`public dual KLN_VEC_CALL ` [`operator^`](#group__ext_1ga2e4a907b6183e39f7d1654b2d2a5fbf7)`(line a,line b) noexcept`             | 
`public dual KLN_VEC_CALL ` [`operator^`](#group__ext_1ga870be4918722a28ad026286942172a07)`(line a,ideal_line b) noexcept`             | 
`public dual KLN_VEC_CALL ` [`operator^`](#group__ext_1ga4d9bce873ef833b7845ac0fdc5eb8b0f)`(ideal_line b,line a) noexcept`             | 
`public dual KLN_VEC_CALL ` [`operator^`](#group__ext_1gad6dec9eb7586335e38b38485ea08cf9c)`(line a,branch b) noexcept`             | 
`public dual KLN_VEC_CALL ` [`operator^`](#group__ext_1gaf52ece148d4d7adfb0645b7c96b75cfa)`(branch b,line a) noexcept`             | 

### Members

#### line KLN_VEC_CALL  [operator^](#group__ext_1gaf6b69634e1bd50ac311c3c3809e0d3f0)(plane a,plane b) noexcept  {#group__ext_1gaf6b69634e1bd50ac311c3c3809e0d3f0}

#### point KLN_VEC_CALL  [operator^](#group__ext_1gaddd37930213efde0f90e8abb0f60c2bc)(plane a,branch b) noexcept  {#group__ext_1gaddd37930213efde0f90e8abb0f60c2bc}

#### point KLN_VEC_CALL  [operator^](#group__ext_1ga17077e02ba6e4391e6fdf056ae06da76)(branch b,plane a) noexcept  {#group__ext_1ga17077e02ba6e4391e6fdf056ae06da76}

#### point KLN_VEC_CALL  [operator^](#group__ext_1ga7c2f4e2deca4fc77fe75ff0fc608ed23)(plane a,ideal_line b) noexcept  {#group__ext_1ga7c2f4e2deca4fc77fe75ff0fc608ed23}

#### point KLN_VEC_CALL  [operator^](#group__ext_1ga0aa1144df65f9d813a10f258d06277ae)(ideal_line b,plane a) noexcept  {#group__ext_1ga0aa1144df65f9d813a10f258d06277ae}

#### point KLN_VEC_CALL  [operator^](#group__ext_1gaa1676d98117be736ee2bba5f56e309b3)(plane a,line b) noexcept  {#group__ext_1gaa1676d98117be736ee2bba5f56e309b3}

#### point KLN_VEC_CALL  [operator^](#group__ext_1gaf6b24c4d8ecfa0b241e6549f6ce55531)(line b,plane a) noexcept  {#group__ext_1gaf6b24c4d8ecfa0b241e6549f6ce55531}

#### dual KLN_VEC_CALL  [operator^](#group__ext_1ga4586341ae4d37e91856b56a6890ce5f8)(plane a,point b) noexcept  {#group__ext_1ga4586341ae4d37e91856b56a6890ce5f8}

#### dual KLN_VEC_CALL  [operator^](#group__ext_1ga0ca0c0ab8d43f634ca56afd825f9d44e)(point b,plane a) noexcept  {#group__ext_1ga0ca0c0ab8d43f634ca56afd825f9d44e}

#### dual KLN_VEC_CALL  [operator^](#group__ext_1gad6a59a5e1fce6d154880a2f703d57904)(branch a,ideal_line b) noexcept  {#group__ext_1gad6a59a5e1fce6d154880a2f703d57904}

#### dual KLN_VEC_CALL  [operator^](#group__ext_1gab85e4f6b524bf5ced8e69bed740a5c36)(ideal_line b,branch a) noexcept  {#group__ext_1gab85e4f6b524bf5ced8e69bed740a5c36}

#### dual KLN_VEC_CALL  [operator^](#group__ext_1ga2e4a907b6183e39f7d1654b2d2a5fbf7)(line a,line b) noexcept  {#group__ext_1ga2e4a907b6183e39f7d1654b2d2a5fbf7}

#### dual KLN_VEC_CALL  [operator^](#group__ext_1ga870be4918722a28ad026286942172a07)(line a,ideal_line b) noexcept  {#group__ext_1ga870be4918722a28ad026286942172a07}

#### dual KLN_VEC_CALL  [operator^](#group__ext_1ga4d9bce873ef833b7845ac0fdc5eb8b0f)(ideal_line b,line a) noexcept  {#group__ext_1ga4d9bce873ef833b7845ac0fdc5eb8b0f}

#### dual KLN_VEC_CALL  [operator^](#group__ext_1gad6dec9eb7586335e38b38485ea08cf9c)(line a,branch b) noexcept  {#group__ext_1gad6dec9eb7586335e38b38485ea08cf9c}

#### dual KLN_VEC_CALL  [operator^](#group__ext_1gaf52ece148d4d7adfb0645b7c96b75cfa)(branch b,line a) noexcept  {#group__ext_1gaf52ece148d4d7adfb0645b7c96b75cfa}

