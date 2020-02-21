## struct `kln::origin` {#structkln_1_1origin}

The origin is a convenience type that occupies no memory but is castable to a point entity. Several operations like conjugation of the origin by a motor is optimized.

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  ` [`operator entity< 0b1000 >`](#structkln_1_1origin_1a28d4f7e2065c6e9e48789b2e825f982a)`() const noexcept`  | On its own, the origin occupies no memory, but it can be casted as an entity at any point, at which point it is represented as $\mathbf{e}_{123}$.

### Members

####   [operator entity< 0b1000 >](#structkln_1_1origin_1a28d4f7e2065c6e9e48789b2e825f982a)() const noexcept  {#structkln_1_1origin_1a28d4f7e2065c6e9e48789b2e825f982a}

On its own, the origin occupies no memory, but it can be casted as an entity at any point, at which point it is represented as $\mathbf{e}_{123}$.

