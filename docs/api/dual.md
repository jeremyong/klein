## group `dual` {#group__dual}

The Poincaré Dual of an element is the "subspace complement" of the argument with respect to the pseudoscalar in the exterior algebra. In practice, it is a relabeling of the coordinates to their dual-coordinates and is used most often to implement a "join" operation in terms of the exterior product of the duals of each operand.

Ex: The dual of the point $\mathbf{e}_{123} + 3\mathbf{e}_{013} - 2\mathbf{e}_{021}$ (the point at $(0, 3, -2)$) is the plane $\mathbf{e}_0 + 3\mathbf{e}_2 - 2\mathbf{e}_3$.

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public KLN_INLINE point KLN_VEC_CALL ` [`operator!`](#group__dual_1ga3a687310cf04e42ff485b03d557ed5a0)`(plane in) noexcept`             | 
`public KLN_INLINE plane KLN_VEC_CALL ` [`operator!`](#group__dual_1ga105ff06095b7eb1fc4ab4b345d7aefb1)`(point in) noexcept`             | 
`public KLN_INLINE line KLN_VEC_CALL ` [`operator!`](#group__dual_1gaa54dbe6355262d69f4302296708cc3fd)`(line in) noexcept`             | 
`public KLN_INLINE branch KLN_VEC_CALL ` [`operator!`](#group__dual_1gac57689e4bf002977c93dbb5e162f7a73)`(ideal_line in) noexcept`             | 
`public KLN_INLINE ideal_line KLN_VEC_CALL ` [`operator!`](#group__dual_1gaba4e70ba96775d4bda3676593256a6be)`(branch in) noexcept`             | 
`public KLN_INLINE dual KLN_VEC_CALL ` [`operator!`](#group__dual_1ga322859aabdd00a64e316ef1d4923a266)`(dual in) noexcept`             | 

### Members

#### KLN_INLINE point KLN_VEC_CALL  [operator!](#group__dual_1ga3a687310cf04e42ff485b03d557ed5a0)(plane in) noexcept  {#group__dual_1ga3a687310cf04e42ff485b03d557ed5a0}

#### KLN_INLINE plane KLN_VEC_CALL  [operator!](#group__dual_1ga105ff06095b7eb1fc4ab4b345d7aefb1)(point in) noexcept  {#group__dual_1ga105ff06095b7eb1fc4ab4b345d7aefb1}

#### KLN_INLINE line KLN_VEC_CALL  [operator!](#group__dual_1gaa54dbe6355262d69f4302296708cc3fd)(line in) noexcept  {#group__dual_1gaa54dbe6355262d69f4302296708cc3fd}

#### KLN_INLINE branch KLN_VEC_CALL  [operator!](#group__dual_1gac57689e4bf002977c93dbb5e162f7a73)(ideal_line in) noexcept  {#group__dual_1gac57689e4bf002977c93dbb5e162f7a73}

#### KLN_INLINE ideal_line KLN_VEC_CALL  [operator!](#group__dual_1gaba4e70ba96775d4bda3676593256a6be)(branch in) noexcept  {#group__dual_1gaba4e70ba96775d4bda3676593256a6be}

#### KLN_INLINE dual KLN_VEC_CALL  [operator!](#group__dual_1ga322859aabdd00a64e316ef1d4923a266)(dual in) noexcept  {#group__dual_1ga322859aabdd00a64e316ef1d4923a266}

