## group `dir` {#group__dir}

Directions in $\mathbf{P}(\mathbb{R}^3_{3, 0, 1})$ are represented using points at infinity (homogeneous coordinate 0). Having a homogeneous coordinate of zero ensures that directions are translation-invariant.

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  ` [`direction`](#group__dir_1gac86167cefc9b8118a8f894aaba99f9a5)`() = default`             | 
`public  ` [`direction`](#group__dir_1ga8fc796733d32a69230136b8376003fca)`(float x,float y,float z) noexcept`             | Create a normalized direction.
`public  ` [`direction`](#group__dir_1ga7cc439bc60bbbe279bbda37f2e0d139b)`(__m128 p3) noexcept`             | 
`public  explicit ` [`direction`](#group__dir_1ga42ce139ace571176acabbce21d6c64b2)`(float * data) noexcept`             | Data should point to four floats with memory layout `(0.f, x, y, z)`  where the zero occupies the lowest address in memory.
`public float ` [`x`](#group__dir_1ga721087c2056a33cd780c678ae0ec39dd)`() const noexcept`             | 
`public float ` [`y`](#group__dir_1ga40bc7052a639d57afde7a860c1631638)`() const noexcept`             | 
`public float ` [`z`](#group__dir_1ga1e16d3ed0ff945d0d1cbf1e6458d334b)`() const noexcept`             | 
`public void ` [`normalize`](#group__dir_1ga143cd2cfeb94860ce1d47b9735064802)`() noexcept`             | Normalize this direction by dividing all components by the magnitude (by default, `rsqrtps`  is used with a single Newton-Raphson refinement iteration)
`public direction ` [`normalized`](#group__dir_1ga1f97cae228749958e81d2747a3cdb4c2)`() const noexcept`             | Return a normalized copy of this direction.
`public direction &KLN_VEC_CALL ` [`operator+=`](#group__dir_1gabf098bdf982bbd9572d9fb09a5f76786)`(direction b) noexcept`             | Direction addition.
`public direction &KLN_VEC_CALL ` [`operator-=`](#group__dir_1ga4bd0650e5c363ec427a4021b678f0567)`(direction b) noexcept`             | Direction subtraction.
`public direction & ` [`operator*=`](#group__dir_1ga8f2c363e3b6ce34e18451b6c716be97a)`(float s) noexcept`             | Direction uniform scale.
`public direction & ` [`operator*=`](#group__dir_1ga6a07c40530461b7a4c94d2aff1371217)`(int s) noexcept`             | Direction uniform scale.
`public direction & ` [`operator/=`](#group__dir_1ga9cac6b5beba3d2e2b0ce1e9a5158c25f)`(float s) noexcept`             | Direction uniform inverse scale.
`public direction & ` [`operator/=`](#group__dir_1ga2717db218937fdb1b88aba24d3abd189)`(int s) noexcept`             | Direction uniform inverse scale.
`public direction KLN_VEC_CALL ` [`operator+`](#group__dir_1ga3aa93423517b128de3d64111201220ce)`(direction a,direction b) noexcept`             | Direction addition.
`public direction KLN_VEC_CALL ` [`operator-`](#group__dir_1gacdc4f7208ad657c450708efcc7fe27d0)`(direction a,direction b) noexcept`             | Direction subtraction.
`public direction KLN_VEC_CALL ` [`operator*`](#group__dir_1ga5d061f57e3a9f92620f6e90d5dbcb8cb)`(direction d,float s) noexcept`             | Direction uniform scale.
`public direction KLN_VEC_CALL ` [`operator*`](#group__dir_1ga0a2f15a137d3c9ef3e5b83e3eee71f9a)`(float s,direction d) noexcept`             | Direction uniform scale.
`public direction KLN_VEC_CALL ` [`operator*`](#group__dir_1ga9d4aadcb32609919e0a2614b1041fdf0)`(direction d,int s) noexcept`             | Direction uniform scale.
`public direction KLN_VEC_CALL ` [`operator*`](#group__dir_1ga0229ad2276f2d9a7f07baee7ee3d7582)`(int s,direction d) noexcept`             | Direction uniform scale.
`public direction KLN_VEC_CALL ` [`operator/`](#group__dir_1ga4473202567a1e1bf3a0929c33d723f52)`(direction d,float s) noexcept`             | Direction uniform inverse scale.
`public direction KLN_VEC_CALL ` [`operator/`](#group__dir_1ga2a8d9ef9111a21d1a55fe08e2c656317)`(direction d,int s) noexcept`             | Direction uniform inverse scale.
`public direction ` [`operator-`](#group__dir_1ga65b1fe0cfac3611b65b78924cb5a61ac)`(direction d) noexcept`             | Unary minus.

### Members

####   [direction](#group__dir_1gac86167cefc9b8118a8f894aaba99f9a5)() = default  {#group__dir_1gac86167cefc9b8118a8f894aaba99f9a5}

####   [direction](#group__dir_1ga8fc796733d32a69230136b8376003fca)(float x,float y,float z) noexcept  {#group__dir_1ga8fc796733d32a69230136b8376003fca}

Create a normalized direction.

####   [direction](#group__dir_1ga7cc439bc60bbbe279bbda37f2e0d139b)(__m128 p3) noexcept  {#group__dir_1ga7cc439bc60bbbe279bbda37f2e0d139b}

####  explicit  [direction](#group__dir_1ga42ce139ace571176acabbce21d6c64b2)(float * data) noexcept  {#group__dir_1ga42ce139ace571176acabbce21d6c64b2}

Data should point to four floats with memory layout `(0.f, x, y, z)`  where the zero occupies the lowest address in memory.

#### float  [x](#group__dir_1ga721087c2056a33cd780c678ae0ec39dd)() const noexcept  {#group__dir_1ga721087c2056a33cd780c678ae0ec39dd}

#### float  [y](#group__dir_1ga40bc7052a639d57afde7a860c1631638)() const noexcept  {#group__dir_1ga40bc7052a639d57afde7a860c1631638}

#### float  [z](#group__dir_1ga1e16d3ed0ff945d0d1cbf1e6458d334b)() const noexcept  {#group__dir_1ga1e16d3ed0ff945d0d1cbf1e6458d334b}

#### void  [normalize](#group__dir_1ga143cd2cfeb94860ce1d47b9735064802)() noexcept  {#group__dir_1ga143cd2cfeb94860ce1d47b9735064802}

Normalize this direction by dividing all components by the magnitude (by default, `rsqrtps`  is used with a single Newton-Raphson refinement iteration)

#### direction  [normalized](#group__dir_1ga1f97cae228749958e81d2747a3cdb4c2)() const noexcept  {#group__dir_1ga1f97cae228749958e81d2747a3cdb4c2}

Return a normalized copy of this direction.

#### direction &KLN_VEC_CALL  [operator+=](#group__dir_1gabf098bdf982bbd9572d9fb09a5f76786)(direction b) noexcept  {#group__dir_1gabf098bdf982bbd9572d9fb09a5f76786}

Direction addition.

#### direction &KLN_VEC_CALL  [operator-=](#group__dir_1ga4bd0650e5c363ec427a4021b678f0567)(direction b) noexcept  {#group__dir_1ga4bd0650e5c363ec427a4021b678f0567}

Direction subtraction.

#### direction &  [operator*=](#group__dir_1ga8f2c363e3b6ce34e18451b6c716be97a)(float s) noexcept  {#group__dir_1ga8f2c363e3b6ce34e18451b6c716be97a}

Direction uniform scale.

#### direction &  [operator*=](#group__dir_1ga6a07c40530461b7a4c94d2aff1371217)(int s) noexcept  {#group__dir_1ga6a07c40530461b7a4c94d2aff1371217}

Direction uniform scale.

#### direction &  [operator/=](#group__dir_1ga9cac6b5beba3d2e2b0ce1e9a5158c25f)(float s) noexcept  {#group__dir_1ga9cac6b5beba3d2e2b0ce1e9a5158c25f}

Direction uniform inverse scale.

#### direction &  [operator/=](#group__dir_1ga2717db218937fdb1b88aba24d3abd189)(int s) noexcept  {#group__dir_1ga2717db218937fdb1b88aba24d3abd189}

Direction uniform inverse scale.

#### direction KLN_VEC_CALL  [operator+](#group__dir_1ga3aa93423517b128de3d64111201220ce)(direction a,direction b) noexcept  {#group__dir_1ga3aa93423517b128de3d64111201220ce}

Direction addition.

#### direction KLN_VEC_CALL  [operator-](#group__dir_1gacdc4f7208ad657c450708efcc7fe27d0)(direction a,direction b) noexcept  {#group__dir_1gacdc4f7208ad657c450708efcc7fe27d0}

Direction subtraction.

#### direction KLN_VEC_CALL  [operator*](#group__dir_1ga5d061f57e3a9f92620f6e90d5dbcb8cb)(direction d,float s) noexcept  {#group__dir_1ga5d061f57e3a9f92620f6e90d5dbcb8cb}

Direction uniform scale.

#### direction KLN_VEC_CALL  [operator*](#group__dir_1ga0a2f15a137d3c9ef3e5b83e3eee71f9a)(float s,direction d) noexcept  {#group__dir_1ga0a2f15a137d3c9ef3e5b83e3eee71f9a}

Direction uniform scale.

#### direction KLN_VEC_CALL  [operator*](#group__dir_1ga9d4aadcb32609919e0a2614b1041fdf0)(direction d,int s) noexcept  {#group__dir_1ga9d4aadcb32609919e0a2614b1041fdf0}

Direction uniform scale.

#### direction KLN_VEC_CALL  [operator*](#group__dir_1ga0229ad2276f2d9a7f07baee7ee3d7582)(int s,direction d) noexcept  {#group__dir_1ga0229ad2276f2d9a7f07baee7ee3d7582}

Direction uniform scale.

#### direction KLN_VEC_CALL  [operator/](#group__dir_1ga4473202567a1e1bf3a0929c33d723f52)(direction d,float s) noexcept  {#group__dir_1ga4473202567a1e1bf3a0929c33d723f52}

Direction uniform inverse scale.

#### direction KLN_VEC_CALL  [operator/](#group__dir_1ga2a8d9ef9111a21d1a55fe08e2c656317)(direction d,int s) noexcept  {#group__dir_1ga2a8d9ef9111a21d1a55fe08e2c656317}

Direction uniform inverse scale.

#### direction  [operator-](#group__dir_1ga65b1fe0cfac3611b65b78924cb5a61ac)(direction d) noexcept  {#group__dir_1ga65b1fe0cfac3611b65b78924cb5a61ac}

Unary minus.

