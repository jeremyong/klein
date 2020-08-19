## group `plane` {#group__plane}

In projective geometry, planes are the fundamental element through which all other entities are constructed. Lines are the meet of two planes, and points are the meet of three planes (equivalently, a line and a plane).

The plane multivector in PGA looks like $d\mathbf{e}_0 + a\mathbf{e}_1 + b\mathbf{e}_2 + c\mathbf{e}_3$. Points that reside on the plane satisfy the familiar equation $d + ax + by + cz = 0$.

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  ` [`plane`](#group__plane_1ga06059c2dd2626f53f552d904060e3ff8)`() = default`             | 
`public  ` [`plane`](#group__plane_1gaf3f1f15a24e94cea2795dc5b978b69f2)`(__m128 xmm) noexcept`             | 
`public  ` [`plane`](#group__plane_1ga51933d8d8853797034621ce41ad34a8e)`(float a,float b,float c,float d) noexcept`             | The constructor performs the rearrangement so the plane can be specified in the familiar form: ax + by + cz + d
`public  explicit ` [`plane`](#group__plane_1ga29dbb1804fa3ec402f901ca8049d60bc)`(float * data) noexcept`             | Data should point to four floats with memory layout `(d, a, b, c)`  where `d`  occupies the lowest address in memory.
`public void ` [`load`](#group__plane_1ga5a00871dbe19d7658b7e8cda71b326f2)`(float * data) noexcept`             | Unaligned load of data. The `data`  argument should point to 4 floats corresponding to the `(d, a, b, c)`  components of the plane multivector where `d`  occupies the lowest address in memory.
`public void ` [`normalize`](#group__plane_1gae5e1e0af05e84799d27d7b8782fe5f22)`() noexcept`             | Normalize this plane $p$ such that $p \cdot p = 1$.
`public plane ` [`normalized`](#group__plane_1ga15ec918ecd05f7e9b21887afa590d405)`() const noexcept`             | Return a normalized copy of this plane.
`public float ` [`norm`](#group__plane_1ga2f86598e6a327c72201e68615bd10384)`() const noexcept`             | Compute the plane norm, which is often used to compute distances between points and lines.
`public void ` [`invert`](#group__plane_1ga8b2ee34f6cc0fd6992520835b13c10e6)`() noexcept`             | 
`public plane ` [`inverse`](#group__plane_1gab3e738eb24a1528e69a1a3ebd75c051e)`() const noexcept`             | 
`public bool KLN_VEC_CALL ` [`operator==`](#group__plane_1ga1163a89d4d307d9f8812cd491d5e80e1)`(plane other) const noexcept`             | 
`public bool KLN_VEC_CALL ` [`approx_eq`](#group__plane_1ga4fecdce7f0b686851053d5edfe55aed8)`(plane other,float epsilon) const noexcept`             | 
`public plane KLN_VEC_CALL ` [`operator()`](#group__plane_1ga1c7a11e35d91c2aee88a4152b1799ca9)`(plane const & p) const noexcept`             | Reflect another plane $p_2$ through this plane $p_1$. The operation performed via this call operator is an optimized routine equivalent to the expression $p_1 p_2 p_1$.
`public line KLN_VEC_CALL ` [`operator()`](#group__plane_1ga782e4e0b1b93ab5bffb2c972f6d7acfa)`(line const & l) const noexcept`             | Reflect line $\ell$ through this plane $p$. The operation performed via this call operator is an optimized routine equivalent to the expression $p \ell p$.
`public point KLN_VEC_CALL ` [`operator()`](#group__plane_1ga20b6577f6d1717e1ec086314d3ebd497)`(point const & p) const noexcept`             | Reflect the point $P$ through this plane $p$. The operation performed via this call operator is an optimized routine equivalent to the expression $p P p$.
`public plane &KLN_VEC_CALL ` [`operator+=`](#group__plane_1gaf80a42a5457dd6f4686501f46e22635c)`(plane b) noexcept`             | Plane addition.
`public plane &KLN_VEC_CALL ` [`operator-=`](#group__plane_1gac4f9a791dcfa8910218d843522fd5509)`(plane b) noexcept`             | Plane subtraction.
`public plane & ` [`operator*=`](#group__plane_1ga9b9724a8d77be2b8cd68b86c1fde963c)`(float s) noexcept`             | Plane uniform scale.
`public plane & ` [`operator*=`](#group__plane_1ga65224cbcfae331161073e8d5829d870d)`(int s) noexcept`             | Plane uniform scale.
`public plane & ` [`operator/=`](#group__plane_1ga2ab699f0afa0a6d33dda86029167b429)`(float s) noexcept`             | Plane uniform inverse scale.
`public plane & ` [`operator/=`](#group__plane_1gae86c20070f4cea4f66d79265f495dec8)`(int s) noexcept`             | Plane uniform inverse scale.
`public float ` [`x`](#group__plane_1gad2a57bafbd388d4ca9ca98d0074fee0a)`() const noexcept`             | 
`public float ` [`e1`](#group__plane_1gaa80c303821219e07892d3cb2a46a548b)`() const noexcept`             | 
`public float ` [`y`](#group__plane_1gadce64826f47e1a017fba8fefab69c174)`() const noexcept`             | 
`public float ` [`e2`](#group__plane_1ga09f8041b7603bcbe9273933f88368f28)`() const noexcept`             | 
`public float ` [`z`](#group__plane_1ga2a01bee79dfb0c11414dc5a936397987)`() const noexcept`             | 
`public float ` [`e3`](#group__plane_1ga82e3a007a85af14bc9c4563f206d4c16)`() const noexcept`             | 
`public float ` [`d`](#group__plane_1gab3aa088fdf83091809bb7e08ace460bb)`() const noexcept`             | 
`public float ` [`e0`](#group__plane_1gadcaf9730f9c22581d196d74b3197769c)`() const noexcept`             | 
`public plane KLN_VEC_CALL ` [`operator+`](#group__plane_1ga6d2534f1b282e146cdda7cd36dd4876f)`(plane a,plane b) noexcept`             | Plane addition.
`public plane KLN_VEC_CALL ` [`operator-`](#group__plane_1ga2afbbeb64867bf4b3d68b56fc71c439a)`(plane a,plane b) noexcept`             | Plane subtraction.
`public plane KLN_VEC_CALL ` [`operator*`](#group__plane_1ga0909ca0b8d5e499d81880382be07006c)`(plane p,float s) noexcept`             | Plane uniform scale.
`public plane KLN_VEC_CALL ` [`operator*`](#group__plane_1ga94594aec80d6cda91582a3728a767ca0)`(float s,plane p) noexcept`             | Plane uniform scale.
`public plane KLN_VEC_CALL ` [`operator*`](#group__plane_1ga13a4925eaf838675c23479343ee7e765)`(plane p,int s) noexcept`             | Plane uniform scale.
`public plane KLN_VEC_CALL ` [`operator*`](#group__plane_1ga46d2c31f730f0760f0c22c6022bb0a3b)`(int s,plane p) noexcept`             | Plane uniform scale.
`public plane KLN_VEC_CALL ` [`operator/`](#group__plane_1ga0f591eb9e778135613a1d5c4a3ac5d51)`(plane p,float s) noexcept`             | Plane uniform inverse scale.
`public plane KLN_VEC_CALL ` [`operator/`](#group__plane_1gafa4b66325f423b360e28b5b5efffa75f)`(plane p,int s) noexcept`             | Plane uniform inverse scale.
`public plane KLN_VEC_CALL ` [`operator-`](#group__plane_1gae018fc4984db372392abd5305b86a212)`(plane p) noexcept`             | Unary minus (leaves displacement from origin untouched, changing orientation only)

### Members

####   [plane](#group__plane_1ga06059c2dd2626f53f552d904060e3ff8)() = default  {#group__plane_1ga06059c2dd2626f53f552d904060e3ff8}

####   [plane](#group__plane_1gaf3f1f15a24e94cea2795dc5b978b69f2)(__m128 xmm) noexcept  {#group__plane_1gaf3f1f15a24e94cea2795dc5b978b69f2}

####   [plane](#group__plane_1ga51933d8d8853797034621ce41ad34a8e)(float a,float b,float c,float d) noexcept  {#group__plane_1ga51933d8d8853797034621ce41ad34a8e}

The constructor performs the rearrangement so the plane can be specified in the familiar form: ax + by + cz + d

####  explicit  [plane](#group__plane_1ga29dbb1804fa3ec402f901ca8049d60bc)(float * data) noexcept  {#group__plane_1ga29dbb1804fa3ec402f901ca8049d60bc}

Data should point to four floats with memory layout `(d, a, b, c)`  where `d`  occupies the lowest address in memory.

#### void  [load](#group__plane_1ga5a00871dbe19d7658b7e8cda71b326f2)(float * data) noexcept  {#group__plane_1ga5a00871dbe19d7658b7e8cda71b326f2}

Unaligned load of data. The `data`  argument should point to 4 floats corresponding to the `(d, a, b, c)`  components of the plane multivector where `d`  occupies the lowest address in memory.

!!! tip 
    This is a faster mechanism for setting data compared to setting
    components one at a time.

#### void  [normalize](#group__plane_1gae5e1e0af05e84799d27d7b8782fe5f22)() noexcept  {#group__plane_1gae5e1e0af05e84799d27d7b8782fe5f22}

Normalize this plane $p$ such that $p \cdot p = 1$.

In order to compute the cosine of the angle between planes via the inner product operator `|` , the planes must be normalized. Producing a normalized rotor between two planes with the geometric product `*`  also requires that the planes are normalized.

#### plane  [normalized](#group__plane_1ga15ec918ecd05f7e9b21887afa590d405)() const noexcept  {#group__plane_1ga15ec918ecd05f7e9b21887afa590d405}

Return a normalized copy of this plane.

#### float  [norm](#group__plane_1ga2f86598e6a327c72201e68615bd10384)() const noexcept  {#group__plane_1ga2f86598e6a327c72201e68615bd10384}

Compute the plane norm, which is often used to compute distances between points and lines.

Given a normalized point $P$ and normalized line $\ell$, the plane $P\vee\ell$ containing both $\ell$ and $P$ will have a norm equivalent to the distance between $P$ and $\ell$.

#### void  [invert](#group__plane_1ga8b2ee34f6cc0fd6992520835b13c10e6)() noexcept  {#group__plane_1ga8b2ee34f6cc0fd6992520835b13c10e6}

#### plane  [inverse](#group__plane_1gab3e738eb24a1528e69a1a3ebd75c051e)() const noexcept  {#group__plane_1gab3e738eb24a1528e69a1a3ebd75c051e}

#### bool KLN_VEC_CALL  [operator==](#group__plane_1ga1163a89d4d307d9f8812cd491d5e80e1)(plane other) const noexcept  {#group__plane_1ga1163a89d4d307d9f8812cd491d5e80e1}

#### bool KLN_VEC_CALL  [approx_eq](#group__plane_1ga4fecdce7f0b686851053d5edfe55aed8)(plane other,float epsilon) const noexcept  {#group__plane_1ga4fecdce7f0b686851053d5edfe55aed8}

#### plane KLN_VEC_CALL  [operator()](#group__plane_1ga1c7a11e35d91c2aee88a4152b1799ca9)(plane const & p) const noexcept  {#group__plane_1ga1c7a11e35d91c2aee88a4152b1799ca9}

Reflect another plane $p_2$ through this plane $p_1$. The operation performed via this call operator is an optimized routine equivalent to the expression $p_1 p_2 p_1$.

#### line KLN_VEC_CALL  [operator()](#group__plane_1ga782e4e0b1b93ab5bffb2c972f6d7acfa)(line const & l) const noexcept  {#group__plane_1ga782e4e0b1b93ab5bffb2c972f6d7acfa}

Reflect line $\ell$ through this plane $p$. The operation performed via this call operator is an optimized routine equivalent to the expression $p \ell p$.

#### point KLN_VEC_CALL  [operator()](#group__plane_1ga20b6577f6d1717e1ec086314d3ebd497)(point const & p) const noexcept  {#group__plane_1ga20b6577f6d1717e1ec086314d3ebd497}

Reflect the point $P$ through this plane $p$. The operation performed via this call operator is an optimized routine equivalent to the expression $p P p$.

#### plane &KLN_VEC_CALL  [operator+=](#group__plane_1gaf80a42a5457dd6f4686501f46e22635c)(plane b) noexcept  {#group__plane_1gaf80a42a5457dd6f4686501f46e22635c}

Plane addition.

#### plane &KLN_VEC_CALL  [operator-=](#group__plane_1gac4f9a791dcfa8910218d843522fd5509)(plane b) noexcept  {#group__plane_1gac4f9a791dcfa8910218d843522fd5509}

Plane subtraction.

#### plane &  [operator*=](#group__plane_1ga9b9724a8d77be2b8cd68b86c1fde963c)(float s) noexcept  {#group__plane_1ga9b9724a8d77be2b8cd68b86c1fde963c}

Plane uniform scale.

#### plane &  [operator*=](#group__plane_1ga65224cbcfae331161073e8d5829d870d)(int s) noexcept  {#group__plane_1ga65224cbcfae331161073e8d5829d870d}

Plane uniform scale.

#### plane &  [operator/=](#group__plane_1ga2ab699f0afa0a6d33dda86029167b429)(float s) noexcept  {#group__plane_1ga2ab699f0afa0a6d33dda86029167b429}

Plane uniform inverse scale.

#### plane &  [operator/=](#group__plane_1gae86c20070f4cea4f66d79265f495dec8)(int s) noexcept  {#group__plane_1gae86c20070f4cea4f66d79265f495dec8}

Plane uniform inverse scale.

#### float  [x](#group__plane_1gad2a57bafbd388d4ca9ca98d0074fee0a)() const noexcept  {#group__plane_1gad2a57bafbd388d4ca9ca98d0074fee0a}

#### float  [e1](#group__plane_1gaa80c303821219e07892d3cb2a46a548b)() const noexcept  {#group__plane_1gaa80c303821219e07892d3cb2a46a548b}

#### float  [y](#group__plane_1gadce64826f47e1a017fba8fefab69c174)() const noexcept  {#group__plane_1gadce64826f47e1a017fba8fefab69c174}

#### float  [e2](#group__plane_1ga09f8041b7603bcbe9273933f88368f28)() const noexcept  {#group__plane_1ga09f8041b7603bcbe9273933f88368f28}

#### float  [z](#group__plane_1ga2a01bee79dfb0c11414dc5a936397987)() const noexcept  {#group__plane_1ga2a01bee79dfb0c11414dc5a936397987}

#### float  [e3](#group__plane_1ga82e3a007a85af14bc9c4563f206d4c16)() const noexcept  {#group__plane_1ga82e3a007a85af14bc9c4563f206d4c16}

#### float  [d](#group__plane_1gab3aa088fdf83091809bb7e08ace460bb)() const noexcept  {#group__plane_1gab3aa088fdf83091809bb7e08ace460bb}

#### float  [e0](#group__plane_1gadcaf9730f9c22581d196d74b3197769c)() const noexcept  {#group__plane_1gadcaf9730f9c22581d196d74b3197769c}

#### plane KLN_VEC_CALL  [operator+](#group__plane_1ga6d2534f1b282e146cdda7cd36dd4876f)(plane a,plane b) noexcept  {#group__plane_1ga6d2534f1b282e146cdda7cd36dd4876f}

Plane addition.

#### plane KLN_VEC_CALL  [operator-](#group__plane_1ga2afbbeb64867bf4b3d68b56fc71c439a)(plane a,plane b) noexcept  {#group__plane_1ga2afbbeb64867bf4b3d68b56fc71c439a}

Plane subtraction.

#### plane KLN_VEC_CALL  [operator*](#group__plane_1ga0909ca0b8d5e499d81880382be07006c)(plane p,float s) noexcept  {#group__plane_1ga0909ca0b8d5e499d81880382be07006c}

Plane uniform scale.

#### plane KLN_VEC_CALL  [operator*](#group__plane_1ga94594aec80d6cda91582a3728a767ca0)(float s,plane p) noexcept  {#group__plane_1ga94594aec80d6cda91582a3728a767ca0}

Plane uniform scale.

#### plane KLN_VEC_CALL  [operator*](#group__plane_1ga13a4925eaf838675c23479343ee7e765)(plane p,int s) noexcept  {#group__plane_1ga13a4925eaf838675c23479343ee7e765}

Plane uniform scale.

#### plane KLN_VEC_CALL  [operator*](#group__plane_1ga46d2c31f730f0760f0c22c6022bb0a3b)(int s,plane p) noexcept  {#group__plane_1ga46d2c31f730f0760f0c22c6022bb0a3b}

Plane uniform scale.

#### plane KLN_VEC_CALL  [operator/](#group__plane_1ga0f591eb9e778135613a1d5c4a3ac5d51)(plane p,float s) noexcept  {#group__plane_1ga0f591eb9e778135613a1d5c4a3ac5d51}

Plane uniform inverse scale.

#### plane KLN_VEC_CALL  [operator/](#group__plane_1gafa4b66325f423b360e28b5b5efffa75f)(plane p,int s) noexcept  {#group__plane_1gafa4b66325f423b360e28b5b5efffa75f}

Plane uniform inverse scale.

#### plane KLN_VEC_CALL  [operator-](#group__plane_1gae018fc4984db372392abd5305b86a212)(plane p) noexcept  {#group__plane_1gae018fc4984db372392abd5305b86a212}

Unary minus (leaves displacement from origin untouched, changing orientation only)

