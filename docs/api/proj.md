## group `proj` {#group__proj}

Projections in Geometric Algebra take on a particularly simple form. For two geometric entities $a$ and $b$, the projection of $a$ on $b$ is given by:

$$ \textit{proj}_b a = (a \cdot b) \wedge b $$

The inner product can be thought of as the part of $b$ *least like* $a$. Using the meet operator on this part produces the part of $b$ *most like* $a$. A simple sanity check is to consider the grades of the result. If the grade of $b$ is less than the grade of $a$, we end up with an entity with grade $a - b + b = a$ as expected.

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public point KLN_VEC_CALL ` [`project`](#group__proj_1gad3cddd86655de814988bb594b8df5ff7)`(point a,line b) noexcept`             | Project a point onto a line.
`public point KLN_VEC_CALL ` [`project`](#group__proj_1ga6732017602bbd6cbb4326946720927f2)`(point a,plane b) noexcept`             | Project a point onto a plane.
`public line KLN_VEC_CALL ` [`project`](#group__proj_1gad0ac38479bfb78b1ef9d0c06cb37a033)`(line a,plane b) noexcept`             | Project a line onto a plane.

### Members

#### point KLN_VEC_CALL  [project](#group__proj_1gad3cddd86655de814988bb594b8df5ff7)(point a,line b) noexcept  {#group__proj_1gad3cddd86655de814988bb594b8df5ff7}

Project a point onto a line.

#### point KLN_VEC_CALL  [project](#group__proj_1ga6732017602bbd6cbb4326946720927f2)(point a,plane b) noexcept  {#group__proj_1ga6732017602bbd6cbb4326946720927f2}

Project a point onto a plane.

#### line KLN_VEC_CALL  [project](#group__proj_1gad0ac38479bfb78b1ef9d0c06cb37a033)(line a,plane b) noexcept  {#group__proj_1gad0ac38479bfb78b1ef9d0c06cb37a033}

Project a line onto a plane.

