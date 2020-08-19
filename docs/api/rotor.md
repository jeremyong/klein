## group `rotor` {#group__rotor}

The rotor is an entity that represents a rigid rotation about an axis. To apply the rotor to a supported entity, the call operator is available.

!!! example 
    ```c++
        // Initialize a point at (1, 3, 2)
        kln::point p{1.f, 3.f, 2.f};
    
        // Create a normalized rotor representing a pi/2 radian
        // rotation about the xz-axis.
        kln::rotor r{kln::pi * 0.5f, 1.f, 0.f, 1.f};
    
        // Rotate our point using the created rotor
        kln::point rotated = r(p);
    ```
    We can rotate lines and planes as well using the rotor's call operator.
    

Rotors can be multiplied to one another with the `*`  operator to create a new rotor equivalent to the application of each factor.

!!! example 
    ```c++
        // Create a normalized rotor representing a $\frac{\pi}{2}$ radian
        // rotation about the xz-axis.
        kln::rotor r1{kln::pi * 0.5f, 1.f, 0.f, 1.f};
    
        // Create a second rotor representing a $\frac{\pi}{3}$ radian
        // rotation about the yz-axis.
        kln::rotor r2{kln::pi / 3.f, 0.f, 1.f, 1.f};
    
        // Use the geometric product to create a rotor equivalent to first
        // applying r1, then applying r2. Note that the order of the
        // operands here is significant.
        kln::rotor r3 = r2 * r1;
    ```
    

The same `*`  operator can be used to compose the rotor's action with other translators and motors.

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  ` [`rotor`](#group__rotor_1gac31c726af9caf7e1de31bf02d9c9d8a5)`() = default`             | 
`public  ` [`rotor`](#group__rotor_1gabd1532e0cd7e2c3cd88812cdccdd7dd4)`(float ang_rad,float x,float y,float z) noexcept`             | Convenience constructor. Computes transcendentals and normalizes rotation axis.
`public  ` [`rotor`](#group__rotor_1gaa01cee77a321c13eb1260afbbfd1dbe2)`(__m128 p1) noexcept`             | 
`public void ` [`load_normalized`](#group__rotor_1gab063d72ca484de581a78ebd7b49e41da)`(float * data) noexcept`             | Fast load operation for packed data that is already normalized. The argument `data`  should point to a set of 4 float values with layout `(a, b, c, d)`  corresponding to the multivector $a + b\mathbf{e}_{23} + c\mathbf{e}_{31} + d\mathbf{e}_{12}$.
`public void ` [`normalize`](#group__rotor_1ga4c9b04d0a4119e7d6b56b9e1478db5d4)`() noexcept`             | Normalize a rotor such that $\mathbf{r}\widetilde{\mathbf{r}} = 1$.
`public rotor ` [`normalized`](#group__rotor_1ga26bfef944e4ae6879de054390d297bc7)`() const noexcept`             | Return a normalized copy of this rotor.
`public void ` [`invert`](#group__rotor_1ga9203cbd66f7cc6f61e545e02657868d8)`() noexcept`             | 
`public rotor ` [`inverse`](#group__rotor_1gaaac6e3fe391fc452089f8742427f011a)`() const noexcept`             | 
`public void ` [`constrain`](#group__rotor_1gad54377a528107dc4dea11e2235c7bcb4)`() noexcept`             | Constrains the rotor to traverse the shortest arc.
`public rotor ` [`constrained`](#group__rotor_1ga16106f423e64a1e83eb3e8c565185a4c)`() const noexcept`             | 
`public bool KLN_VEC_CALL ` [`operator==`](#group__rotor_1gacde3f253079c87e7f14af37d1ecbb820)`(rotor other) const noexcept`             | 
`public bool KLN_VEC_CALL ` [`approx_eq`](#group__rotor_1gae600982e491885c97654229bc86321a1)`(rotor other,float epsilon) const noexcept`             | 
`public mat3x4 ` [`as_mat3x4`](#group__rotor_1gad0e18686170db4038e5b7c287b3e8e7d)`() const noexcept`             | Converts the rotor to a 3x4 column-major matrix. The results of this conversion are only defined if the rotor is normalized, and this conversion is preferable if so.
`public mat4x4 ` [`as_mat4x4`](#group__rotor_1ga2484fc74feb9a79cabd474005fd1c0d8)`() const noexcept`             | Converts the rotor to a 4x4 column-major matrix.
`public plane KLN_VEC_CALL ` [`operator()`](#group__rotor_1gae9e58f02352f5241dd94d22353a5e9ec)`(plane const & p) const noexcept`             | Conjugates a plane $p$ with this rotor and returns the result $rp\widetilde{r}$.
`public void KLN_VEC_CALL ` [`operator()`](#group__rotor_1ga491f6f2264c6ecf180664e75fc4a159b)`(plane * in,plane * out,size_t count) const noexcept`             | Conjugates an array of planes with this rotor in the input array and stores the result in the output array. Aliasing is only permitted when `in == out`  (in place motor application).
`public branch KLN_VEC_CALL ` [`operator()`](#group__rotor_1ga4fb7861b9656f5cbc44484c1ba66ce74)`(branch const & b) const noexcept`             | 
`public line KLN_VEC_CALL ` [`operator()`](#group__rotor_1gac4d044ea5b98ba540fc5da8d75f43ccc)`(line const & l) const noexcept`             | Conjugates a line $\ell$ with this rotor and returns the result $r\ell \widetilde{r}$.
`public void KLN_VEC_CALL ` [`operator()`](#group__rotor_1gaad794881fa0c11fb05486986032a431a)`(line * in,line * out,size_t count) const noexcept`             | Conjugates an array of lines with this rotor in the input array and stores the result in the output array. Aliasing is only permitted when `in == out`  (in place rotor application).
`public point KLN_VEC_CALL ` [`operator()`](#group__rotor_1ga5aabb4caa402fb5793807fe1d8cec199)`(point const & p) const noexcept`             | Conjugates a point $p$ with this rotor and returns the result $rp\widetilde{r}$.
`public void KLN_VEC_CALL ` [`operator()`](#group__rotor_1gaa91e4024d7368fbd14a93ead29905aad)`(point * in,point * out,size_t count) const noexcept`             | Conjugates an array of points with this rotor in the input array and stores the result in the output array. Aliasing is only permitted when `in == out`  (in place rotor application).
`public direction KLN_VEC_CALL ` [`operator()`](#group__rotor_1ga80935add9a99987a59879df1aa868b43)`(direction const & d) const noexcept`             | Conjugates a direction $d$ with this rotor and returns the result $rd\widetilde{r}$.
`public void KLN_VEC_CALL ` [`operator()`](#group__rotor_1ga185ca5be93f00396e5e0de9a05561999)`(direction * in,direction * out,size_t count) const noexcept`             | Conjugates an array of directions with this rotor in the input array and stores the result in the output array. Aliasing is only permitted when `in == out`  (in place rotor application).
`public rotor &KLN_VEC_CALL ` [`operator+=`](#group__rotor_1ga45e39a62243e36e5e355ebd2b568f4e8)`(rotor b) noexcept`             | Rotor addition.
`public rotor &KLN_VEC_CALL ` [`operator-=`](#group__rotor_1ga6c3e3d03a77a3e6912a6de71587eec6c)`(rotor b) noexcept`             | Rotor subtraction.
`public rotor & ` [`operator*=`](#group__rotor_1ga6dee3c43d98062a0d84c89c21f6e2eab)`(float s) noexcept`             | Rotor uniform scale.
`public rotor & ` [`operator*=`](#group__rotor_1ga0192dadc8c52d7c8b0935498c79bac3c)`(int s) noexcept`             | Rotor uniform scale.
`public rotor & ` [`operator/=`](#group__rotor_1ga471b8aca5f4b10e324d9da1261b96819)`(float s) noexcept`             | Rotor uniform inverse scale.
`public rotor & ` [`operator/=`](#group__rotor_1gab9b4f34c5626f8f718d40f4244325627)`(int s) noexcept`             | Rotor uniform inverse scale.
`public float ` [`scalar`](#group__rotor_1gad02dd43ba81281970b6c177897097bcb)`() const noexcept`             | 
`public float ` [`e12`](#group__rotor_1gaeca61f73a42e3e4e33c15ef429ecaeb5)`() const noexcept`             | 
`public float ` [`e21`](#group__rotor_1gaa0b572c94d744b0cfc991fb6b4553e93)`() const noexcept`             | 
`public float ` [`e31`](#group__rotor_1gac0fd6fb45a971064cbe9b77c8c6f96e6)`() const noexcept`             | 
`public float ` [`e13`](#group__rotor_1ga54519295ac9dcef24687d0d60d0a4fb7)`() const noexcept`             | 
`public float ` [`e23`](#group__rotor_1gaa1aee031886928dd7e62e65a2bc4c8c1)`() const noexcept`             | 
`public float ` [`e32`](#group__rotor_1gac0aa82cab673eefc743c4bd7b9753440)`() const noexcept`             | 
`public rotor KLN_VEC_CALL ` [`operator+`](#group__rotor_1gabd46b22dfdc4f00b1ee7d05f1570f071)`(rotor a,rotor b) noexcept`             | Rotor addition.
`public rotor KLN_VEC_CALL ` [`operator-`](#group__rotor_1ga1479b477d3a0e2ae643dbfce8b790e46)`(rotor a,rotor b) noexcept`             | Rotor subtraction.
`public rotor KLN_VEC_CALL ` [`operator*`](#group__rotor_1ga9a9b601b2fb07e3ad3984e1e92675903)`(rotor r,float s) noexcept`             | Rotor uniform scale.
`public rotor KLN_VEC_CALL ` [`operator*`](#group__rotor_1ga142d2a565a37e7646ed13d6461c193ec)`(rotor r,int s) noexcept`             | Rotor uniform scale.
`public rotor KLN_VEC_CALL ` [`operator*`](#group__rotor_1gade99d6f57e8b4014485ded5b0d749bfa)`(float s,rotor r) noexcept`             | Rotor uniform scale.
`public rotor KLN_VEC_CALL ` [`operator*`](#group__rotor_1ga57de1a4a27ca3515aea0ca8b5b4b69a0)`(int s,rotor r) noexcept`             | Rotor uniform scale.
`public rotor KLN_VEC_CALL ` [`operator/`](#group__rotor_1gaacf6f0f789dfae74dae83af785b69232)`(rotor r,float s) noexcept`             | Rotor uniform inverse scale.
`public rotor KLN_VEC_CALL ` [`operator/`](#group__rotor_1gaf87b76ceb327655df465f15b7e0dd96b)`(rotor r,int s) noexcept`             | Rotor uniform inverse scale.
`public rotor KLN_VEC_CALL ` [`operator~`](#group__rotor_1ga2c4b1d7565d89e7a6f6e6b838f838ed5)`(rotor r) noexcept`             | Reversion operator.
`public rotor KLN_VEC_CALL ` [`operator-`](#group__rotor_1ga2da1f112e6633bfefb1a15e5e2bdcd5b)`(rotor r) noexcept`             | Unary minus.

### Members

####   [rotor](#group__rotor_1gac31c726af9caf7e1de31bf02d9c9d8a5)() = default  {#group__rotor_1gac31c726af9caf7e1de31bf02d9c9d8a5}

####   [rotor](#group__rotor_1gabd1532e0cd7e2c3cd88812cdccdd7dd4)(float ang_rad,float x,float y,float z) noexcept  {#group__rotor_1gabd1532e0cd7e2c3cd88812cdccdd7dd4}

Convenience constructor. Computes transcendentals and normalizes rotation axis.

####   [rotor](#group__rotor_1gaa01cee77a321c13eb1260afbbfd1dbe2)(__m128 p1) noexcept  {#group__rotor_1gaa01cee77a321c13eb1260afbbfd1dbe2}

#### void  [load_normalized](#group__rotor_1gab063d72ca484de581a78ebd7b49e41da)(float * data) noexcept  {#group__rotor_1gab063d72ca484de581a78ebd7b49e41da}

Fast load operation for packed data that is already normalized. The argument `data`  should point to a set of 4 float values with layout `(a, b, c, d)`  corresponding to the multivector $a + b\mathbf{e}_{23} + c\mathbf{e}_{31} + d\mathbf{e}_{12}$.

!!! danger 
    The rotor data loaded this way *must* be normalized. That is, the
    rotor $r$ must satisfy $r\widetilde{r} = 1$.

#### void  [normalize](#group__rotor_1ga4c9b04d0a4119e7d6b56b9e1478db5d4)() noexcept  {#group__rotor_1ga4c9b04d0a4119e7d6b56b9e1478db5d4}

Normalize a rotor such that $\mathbf{r}\widetilde{\mathbf{r}} = 1$.

#### rotor  [normalized](#group__rotor_1ga26bfef944e4ae6879de054390d297bc7)() const noexcept  {#group__rotor_1ga26bfef944e4ae6879de054390d297bc7}

Return a normalized copy of this rotor.

#### void  [invert](#group__rotor_1ga9203cbd66f7cc6f61e545e02657868d8)() noexcept  {#group__rotor_1ga9203cbd66f7cc6f61e545e02657868d8}

#### rotor  [inverse](#group__rotor_1gaaac6e3fe391fc452089f8742427f011a)() const noexcept  {#group__rotor_1gaaac6e3fe391fc452089f8742427f011a}

#### void  [constrain](#group__rotor_1gad54377a528107dc4dea11e2235c7bcb4)() noexcept  {#group__rotor_1gad54377a528107dc4dea11e2235c7bcb4}

Constrains the rotor to traverse the shortest arc.

#### rotor  [constrained](#group__rotor_1ga16106f423e64a1e83eb3e8c565185a4c)() const noexcept  {#group__rotor_1ga16106f423e64a1e83eb3e8c565185a4c}

#### bool KLN_VEC_CALL  [operator==](#group__rotor_1gacde3f253079c87e7f14af37d1ecbb820)(rotor other) const noexcept  {#group__rotor_1gacde3f253079c87e7f14af37d1ecbb820}

#### bool KLN_VEC_CALL  [approx_eq](#group__rotor_1gae600982e491885c97654229bc86321a1)(rotor other,float epsilon) const noexcept  {#group__rotor_1gae600982e491885c97654229bc86321a1}

#### mat3x4  [as_mat3x4](#group__rotor_1gad0e18686170db4038e5b7c287b3e8e7d)() const noexcept  {#group__rotor_1gad0e18686170db4038e5b7c287b3e8e7d}

Converts the rotor to a 3x4 column-major matrix. The results of this conversion are only defined if the rotor is normalized, and this conversion is preferable if so.

#### mat4x4  [as_mat4x4](#group__rotor_1ga2484fc74feb9a79cabd474005fd1c0d8)() const noexcept  {#group__rotor_1ga2484fc74feb9a79cabd474005fd1c0d8}

Converts the rotor to a 4x4 column-major matrix.

#### plane KLN_VEC_CALL  [operator()](#group__rotor_1gae9e58f02352f5241dd94d22353a5e9ec)(plane const & p) const noexcept  {#group__rotor_1gae9e58f02352f5241dd94d22353a5e9ec}

Conjugates a plane $p$ with this rotor and returns the result $rp\widetilde{r}$.

#### void KLN_VEC_CALL  [operator()](#group__rotor_1ga491f6f2264c6ecf180664e75fc4a159b)(plane * in,plane * out,size_t count) const noexcept  {#group__rotor_1ga491f6f2264c6ecf180664e75fc4a159b}

Conjugates an array of planes with this rotor in the input array and stores the result in the output array. Aliasing is only permitted when `in == out`  (in place motor application).

!!! tip 
    When applying a rotor to a list of tightly packed planes, this
    routine will be *significantly faster* than applying the rotor to
    each plane individually.

#### branch KLN_VEC_CALL  [operator()](#group__rotor_1ga4fb7861b9656f5cbc44484c1ba66ce74)(branch const & b) const noexcept  {#group__rotor_1ga4fb7861b9656f5cbc44484c1ba66ce74}

#### line KLN_VEC_CALL  [operator()](#group__rotor_1gac4d044ea5b98ba540fc5da8d75f43ccc)(line const & l) const noexcept  {#group__rotor_1gac4d044ea5b98ba540fc5da8d75f43ccc}

Conjugates a line $\ell$ with this rotor and returns the result $r\ell \widetilde{r}$.

#### void KLN_VEC_CALL  [operator()](#group__rotor_1gaad794881fa0c11fb05486986032a431a)(line * in,line * out,size_t count) const noexcept  {#group__rotor_1gaad794881fa0c11fb05486986032a431a}

Conjugates an array of lines with this rotor in the input array and stores the result in the output array. Aliasing is only permitted when `in == out`  (in place rotor application).

!!! tip 
    When applying a rotor to a list of tightly packed lines, this
    routine will be *significantly faster* than applying the rotor to
    each line individually.

#### point KLN_VEC_CALL  [operator()](#group__rotor_1ga5aabb4caa402fb5793807fe1d8cec199)(point const & p) const noexcept  {#group__rotor_1ga5aabb4caa402fb5793807fe1d8cec199}

Conjugates a point $p$ with this rotor and returns the result $rp\widetilde{r}$.

#### void KLN_VEC_CALL  [operator()](#group__rotor_1gaa91e4024d7368fbd14a93ead29905aad)(point * in,point * out,size_t count) const noexcept  {#group__rotor_1gaa91e4024d7368fbd14a93ead29905aad}

Conjugates an array of points with this rotor in the input array and stores the result in the output array. Aliasing is only permitted when `in == out`  (in place rotor application).

!!! tip 
    When applying a rotor to a list of tightly packed points, this
    routine will be *significantly faster* than applying the rotor to
    each point individually.

#### direction KLN_VEC_CALL  [operator()](#group__rotor_1ga80935add9a99987a59879df1aa868b43)(direction const & d) const noexcept  {#group__rotor_1ga80935add9a99987a59879df1aa868b43}

Conjugates a direction $d$ with this rotor and returns the result $rd\widetilde{r}$.

#### void KLN_VEC_CALL  [operator()](#group__rotor_1ga185ca5be93f00396e5e0de9a05561999)(direction * in,direction * out,size_t count) const noexcept  {#group__rotor_1ga185ca5be93f00396e5e0de9a05561999}

Conjugates an array of directions with this rotor in the input array and stores the result in the output array. Aliasing is only permitted when `in == out`  (in place rotor application).

!!! tip 
    When applying a rotor to a list of tightly packed directions, this
    routine will be *significantly faster* than applying the rotor to
    each direction individually.

#### rotor &KLN_VEC_CALL  [operator+=](#group__rotor_1ga45e39a62243e36e5e355ebd2b568f4e8)(rotor b) noexcept  {#group__rotor_1ga45e39a62243e36e5e355ebd2b568f4e8}

Rotor addition.

#### rotor &KLN_VEC_CALL  [operator-=](#group__rotor_1ga6c3e3d03a77a3e6912a6de71587eec6c)(rotor b) noexcept  {#group__rotor_1ga6c3e3d03a77a3e6912a6de71587eec6c}

Rotor subtraction.

#### rotor &  [operator*=](#group__rotor_1ga6dee3c43d98062a0d84c89c21f6e2eab)(float s) noexcept  {#group__rotor_1ga6dee3c43d98062a0d84c89c21f6e2eab}

Rotor uniform scale.

#### rotor &  [operator*=](#group__rotor_1ga0192dadc8c52d7c8b0935498c79bac3c)(int s) noexcept  {#group__rotor_1ga0192dadc8c52d7c8b0935498c79bac3c}

Rotor uniform scale.

#### rotor &  [operator/=](#group__rotor_1ga471b8aca5f4b10e324d9da1261b96819)(float s) noexcept  {#group__rotor_1ga471b8aca5f4b10e324d9da1261b96819}

Rotor uniform inverse scale.

#### rotor &  [operator/=](#group__rotor_1gab9b4f34c5626f8f718d40f4244325627)(int s) noexcept  {#group__rotor_1gab9b4f34c5626f8f718d40f4244325627}

Rotor uniform inverse scale.

#### float  [scalar](#group__rotor_1gad02dd43ba81281970b6c177897097bcb)() const noexcept  {#group__rotor_1gad02dd43ba81281970b6c177897097bcb}

#### float  [e12](#group__rotor_1gaeca61f73a42e3e4e33c15ef429ecaeb5)() const noexcept  {#group__rotor_1gaeca61f73a42e3e4e33c15ef429ecaeb5}

#### float  [e21](#group__rotor_1gaa0b572c94d744b0cfc991fb6b4553e93)() const noexcept  {#group__rotor_1gaa0b572c94d744b0cfc991fb6b4553e93}

#### float  [e31](#group__rotor_1gac0fd6fb45a971064cbe9b77c8c6f96e6)() const noexcept  {#group__rotor_1gac0fd6fb45a971064cbe9b77c8c6f96e6}

#### float  [e13](#group__rotor_1ga54519295ac9dcef24687d0d60d0a4fb7)() const noexcept  {#group__rotor_1ga54519295ac9dcef24687d0d60d0a4fb7}

#### float  [e23](#group__rotor_1gaa1aee031886928dd7e62e65a2bc4c8c1)() const noexcept  {#group__rotor_1gaa1aee031886928dd7e62e65a2bc4c8c1}

#### float  [e32](#group__rotor_1gac0aa82cab673eefc743c4bd7b9753440)() const noexcept  {#group__rotor_1gac0aa82cab673eefc743c4bd7b9753440}

#### rotor KLN_VEC_CALL  [operator+](#group__rotor_1gabd46b22dfdc4f00b1ee7d05f1570f071)(rotor a,rotor b) noexcept  {#group__rotor_1gabd46b22dfdc4f00b1ee7d05f1570f071}

Rotor addition.

#### rotor KLN_VEC_CALL  [operator-](#group__rotor_1ga1479b477d3a0e2ae643dbfce8b790e46)(rotor a,rotor b) noexcept  {#group__rotor_1ga1479b477d3a0e2ae643dbfce8b790e46}

Rotor subtraction.

#### rotor KLN_VEC_CALL  [operator*](#group__rotor_1ga9a9b601b2fb07e3ad3984e1e92675903)(rotor r,float s) noexcept  {#group__rotor_1ga9a9b601b2fb07e3ad3984e1e92675903}

Rotor uniform scale.

#### rotor KLN_VEC_CALL  [operator*](#group__rotor_1ga142d2a565a37e7646ed13d6461c193ec)(rotor r,int s) noexcept  {#group__rotor_1ga142d2a565a37e7646ed13d6461c193ec}

Rotor uniform scale.

#### rotor KLN_VEC_CALL  [operator*](#group__rotor_1gade99d6f57e8b4014485ded5b0d749bfa)(float s,rotor r) noexcept  {#group__rotor_1gade99d6f57e8b4014485ded5b0d749bfa}

Rotor uniform scale.

#### rotor KLN_VEC_CALL  [operator*](#group__rotor_1ga57de1a4a27ca3515aea0ca8b5b4b69a0)(int s,rotor r) noexcept  {#group__rotor_1ga57de1a4a27ca3515aea0ca8b5b4b69a0}

Rotor uniform scale.

#### rotor KLN_VEC_CALL  [operator/](#group__rotor_1gaacf6f0f789dfae74dae83af785b69232)(rotor r,float s) noexcept  {#group__rotor_1gaacf6f0f789dfae74dae83af785b69232}

Rotor uniform inverse scale.

#### rotor KLN_VEC_CALL  [operator/](#group__rotor_1gaf87b76ceb327655df465f15b7e0dd96b)(rotor r,int s) noexcept  {#group__rotor_1gaf87b76ceb327655df465f15b7e0dd96b}

Rotor uniform inverse scale.

#### rotor KLN_VEC_CALL  [operator~](#group__rotor_1ga2c4b1d7565d89e7a6f6e6b838f838ed5)(rotor r) noexcept  {#group__rotor_1ga2c4b1d7565d89e7a6f6e6b838f838ed5}

Reversion operator.

#### rotor KLN_VEC_CALL  [operator-](#group__rotor_1ga2da1f112e6633bfefb1a15e5e2bdcd5b)(rotor r) noexcept  {#group__rotor_1ga2da1f112e6633bfefb1a15e5e2bdcd5b}

Unary minus.

