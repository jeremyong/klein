## group `proj` {#group__proj}

Projections in Geometric Algebra take on a particularly simple form. For two geometric entities $a$ and $b$, there are two cases to consider. First, if the grade of $a$ is greater than the grade of $b$, the projection of $a$ on $b$ is given by:

$$ \textit{proj}_b a = (a \cdot b) \wedge b $$

The inner product can be thought of as the part of $b$ *least like* $a$. Using the meet operator on this part produces the part of $b$ *most like* $a$. A simple sanity check is to consider the grades of the result. If the grade of $b$ is less than the grade of $a$, we end up with an entity with grade $a - b + b = a$ as expected.

In the second case (the grade of $a$ is less than the grade of $b$), the projection of $a$ on $b$ is given by:

$$ \textit{proj}_b a = (a \cdot b) \cdot b $$

It can be verified that as in the first case, the grade of the result is the same as the grade of $a$. As this projection occurs in the opposite sense from what one may have seen before, additional clarification is provided below.

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public point KLN_VEC_CALL ` [`project`](#group__proj_1gad3cddd86655de814988bb594b8df5ff7)`(point a,line b) noexcept`             | Project a point onto a line.
`public point KLN_VEC_CALL ` [`project`](#group__proj_1ga6732017602bbd6cbb4326946720927f2)`(point a,plane b) noexcept`             | Project a point onto a plane.
`public line KLN_VEC_CALL ` [`project`](#group__proj_1gad0ac38479bfb78b1ef9d0c06cb37a033)`(line a,plane b) noexcept`             | Project a line onto a plane.
`public plane KLN_VEC_CALL ` [`project`](#group__proj_1ga9ba81079e93afed456b56ae7273af189)`(plane a,point b) noexcept`             | Project a plane onto a point. Given a plane $p$ and point $P$, produces the plane through $P$ that is parallel to $p$.
`public line KLN_VEC_CALL ` [`project`](#group__proj_1ga1d875a5cc0de38ff17c3e4f298a116bd)`(line a,point b) noexcept`             | Project a line onto a point. Given a line $\ell$ and point $P$, produces the line through $P$ that is parallel to $\ell$.
`public plane KLN_VEC_CALL ` [`project`](#group__proj_1ga29fd7694ba97a90fc9ae4525ab609314)`(plane a,line b) noexcept`             | Project a plane onto a line. Given a plane $p$ and line $\ell$, produces the plane through $\ell$ that is parallel to $p$ if $p \parallel \ell$.

### Members

#### point KLN_VEC_CALL  [project](#group__proj_1gad3cddd86655de814988bb594b8df5ff7)(point a,line b) noexcept  {#group__proj_1gad3cddd86655de814988bb594b8df5ff7}

Project a point onto a line.

#### point KLN_VEC_CALL  [project](#group__proj_1ga6732017602bbd6cbb4326946720927f2)(point a,plane b) noexcept  {#group__proj_1ga6732017602bbd6cbb4326946720927f2}

Project a point onto a plane.

#### line KLN_VEC_CALL  [project](#group__proj_1gad0ac38479bfb78b1ef9d0c06cb37a033)(line a,plane b) noexcept  {#group__proj_1gad0ac38479bfb78b1ef9d0c06cb37a033}

Project a line onto a plane.

#### plane KLN_VEC_CALL  [project](#group__proj_1ga9ba81079e93afed456b56ae7273af189)(plane a,point b) noexcept  {#group__proj_1ga9ba81079e93afed456b56ae7273af189}

Project a plane onto a point. Given a plane $p$ and point $P$, produces the plane through $P$ that is parallel to $p$.

Intuitively, the point is represented dually in terms of a *pencil of planes* that converge on the point itself. When we compute $p | P$, this selects the line perpendicular to $p$ through $P$. Subsequently, taking the inner product with $P$ again selects the plane from the plane pencil of $P$ *least like* that line.

#### line KLN_VEC_CALL  [project](#group__proj_1ga1d875a5cc0de38ff17c3e4f298a116bd)(line a,point b) noexcept  {#group__proj_1ga1d875a5cc0de38ff17c3e4f298a116bd}

Project a line onto a point. Given a line $\ell$ and point $P$, produces the line through $P$ that is parallel to $\ell$.

#### plane KLN_VEC_CALL  [project](#group__proj_1ga29fd7694ba97a90fc9ae4525ab609314)(plane a,line b) noexcept  {#group__proj_1ga29fd7694ba97a90fc9ae4525ab609314}

Project a plane onto a line. Given a plane $p$ and line $\ell$, produces the plane through $\ell$ that is parallel to $p$ if $p \parallel \ell$.

If $p \nparallel \ell$, the result will be the plane $p'$ containing $\ell$ that maximizes $p \cdot p'$ (that is, $p'$ is as parallel to $p$ as possible).

