## struct `kln::rotor` {#structkln_1_1rotor}

```
struct kln::rotor
  : public kln::entity< 0b10 >
```  

The rotor is an entity that represents a rigid rotation about an axis. To apply the rotor to a supported entity, the call operator is available.

!!! example 
    ```c++
        // Initialize a point at (1, 3, 2)
        kln::point p{1.f, 3.f, 2.f};
    
        // Create a normalized rotor representing a pi/2 radian
        // rotation about the xz-axis.
        kln::rotor r{M_PI * 0.5f, 1.f, 0.f, 1.f};
    
        // Rotate our point using the created rotor
        kln::point rotated = r(p);
    ```
    We can rotate lines and planes as well using the rotor's call operator.
    

Rotors can be multiplied to one another with the `*`  operator to create a new rotor equivalent to the application of each factor.

!!! example 
    ```c++
        // Create a normalized rotor representing a $\frac{\pi}{2}$ radian
        // rotation about the xz-axis.
        kln::rotor r1{M_PI * 0.5f, 1.f, 0.f, 1.f};
    
        // Create a second rotor representing a $\frac{\pi}{3}$ radian
        // rotation about the yz-axis.
        kln::rotor r2{M_PI / 3.f, 0.f, 1.f, 1.f};
    
        // Use the geometric product to create a rotor equivalent to first
        // applying r1, then applying r2. Note that the order of the
        // operands here is significant.
        kln::rotor r3 = r2 * r1;
    ```
    

The same `*`  operator can be used to compose the rotor's action with other translators and motors.

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  ` [`rotor`](#structkln_1_1rotor_1a3d3e11652d0c83a5f86de0d33b259be4)`() = default`  | Default constructor leaves memory uninitialized.
`public  ` [`rotor`](#structkln_1_1rotor_1a1ed5b58579ef482f98fcd019476f883c)`(float ang_rad,float x,float y,float z)`  | Convenience constructor. Computes transcendentals and normalizes rotation axis.
`public  ` [`rotor`](#structkln_1_1rotor_1aa14da87f8cbcddbd997fb29738214298)`(` [`entity`](/Klein/api/kln::entity#structkln_1_1entity)`< 0b10 > const & other)`  | 
`public void ` [`load_normalized`](#structkln_1_1rotor_1ab063d72ca484de581a78ebd7b49e41da)`(float * data) noexcept`  | Fast load operation for packed data that is already normalized. The argument `data`  should point to a set of 4 float values with layout `(a, b, c, d)`  corresponding to the multivector $a + b\mathbf{e}_{12} + c\mathbf{e}_{31} + d\mathbf{e}_{23}$.
`public void ` [`normalize`](#structkln_1_1rotor_1a4c9b04d0a4119e7d6b56b9e1478db5d4)`() noexcept`  | Normalize a rotor such that $\mathbf{r}\widetilde{\mathbf{r}} = 1$.
`public ` [`mat4x4`](/Klein/api/kln::mat4x4#structkln_1_1mat4x4)` ` [`as_matrix`](#structkln_1_1rotor_1a0f13d2649e679220fc79ee7bc0bbea11)`() const noexcept`  | Converts the rotor to a 4x4 column-major matrix.
`public ` [`plane`](/Klein/api/kln::plane#structkln_1_1plane)` KLN_VEC_CALL ` [`operator()`](#structkln_1_1rotor_1ae9e58f02352f5241dd94d22353a5e9ec)`(` [`plane`](/Klein/api/kln::plane#structkln_1_1plane)` const & p) const noexcept`  | Conjugates a plane $p$ with this rotor and returns the result $rp\widetilde{r}$.
`public void KLN_VEC_CALL ` [`operator()`](#structkln_1_1rotor_1a491f6f2264c6ecf180664e75fc4a159b)`(` [`plane`](/Klein/api/kln::plane#structkln_1_1plane)` * in,` [`plane`](/Klein/api/kln::plane#structkln_1_1plane)` * out,size_t count) const noexcept`  | Conjugates an array of planes with this rotor in the input array and stores the result in the output array. Aliasing is only permitted when `in == out`  (in place motor application).
`public ` [`line`](/Klein/api/kln::line#structkln_1_1line)` KLN_VEC_CALL ` [`operator()`](#structkln_1_1rotor_1ac4d044ea5b98ba540fc5da8d75f43ccc)`(` [`line`](/Klein/api/kln::line#structkln_1_1line)` const & l) const noexcept`  | Conjugates a line $\ell$ with this rotor and returns the result $r\ell \widetilde{r}$.
`public void KLN_VEC_CALL ` [`operator()`](#structkln_1_1rotor_1aad794881fa0c11fb05486986032a431a)`(` [`line`](/Klein/api/kln::line#structkln_1_1line)` * in,` [`line`](/Klein/api/kln::line#structkln_1_1line)` * out,size_t count) const noexcept`  | Conjugates an array of lines with this rotor in the input array and stores the result in the output array. Aliasing is only permitted when `in == out`  (in place rotor application).
`public ` [`point`](/Klein/api/kln::point#structkln_1_1point)` KLN_VEC_CALL ` [`operator()`](#structkln_1_1rotor_1a5aabb4caa402fb5793807fe1d8cec199)`(` [`point`](/Klein/api/kln::point#structkln_1_1point)` const & p) const noexcept`  | Conjugates a point $p$ with this rotor and returns the result $rp\widetilde{r}$.
`public void KLN_VEC_CALL ` [`operator()`](#structkln_1_1rotor_1aa91e4024d7368fbd14a93ead29905aad)`(` [`point`](/Klein/api/kln::point#structkln_1_1point)` * in,` [`point`](/Klein/api/kln::point#structkln_1_1point)` * out,size_t count) const noexcept`  | Conjugates an array of points with this rotor in the input array and stores the result in the output array. Aliasing is only permitted when `in == out`  (in place rotor application).
`public ` [`direction`](/Klein/api/kln::direction#structkln_1_1direction)` KLN_VEC_CALL ` [`operator()`](#structkln_1_1rotor_1a80935add9a99987a59879df1aa868b43)`(` [`direction`](/Klein/api/kln::direction#structkln_1_1direction)` const & d) const noexcept`  | Conjugates a direction $d$ with this rotor and returns the result $rd\widetilde{r}$.
`public void KLN_VEC_CALL ` [`operator()`](#structkln_1_1rotor_1a185ca5be93f00396e5e0de9a05561999)`(` [`direction`](/Klein/api/kln::direction#structkln_1_1direction)` * in,` [`direction`](/Klein/api/kln::direction#structkln_1_1direction)` * out,size_t count) const noexcept`  | Conjugates an array of directions with this rotor in the input array and stores the result in the output array. Aliasing is only permitted when `in == out`  (in place rotor application).

### Members

####   [rotor](#structkln_1_1rotor_1a3d3e11652d0c83a5f86de0d33b259be4)() = default  {#structkln_1_1rotor_1a3d3e11652d0c83a5f86de0d33b259be4}

Default constructor leaves memory uninitialized.

####   [rotor](#structkln_1_1rotor_1a1ed5b58579ef482f98fcd019476f883c)(float ang_rad,float x,float y,float z)  {#structkln_1_1rotor_1a1ed5b58579ef482f98fcd019476f883c}

Convenience constructor. Computes transcendentals and normalizes rotation axis.

####   [rotor](#structkln_1_1rotor_1aa14da87f8cbcddbd997fb29738214298)( [entity](/Klein/api/kln::entity#structkln_1_1entity)< 0b10 > const & other)  {#structkln_1_1rotor_1aa14da87f8cbcddbd997fb29738214298}

#### void  [load_normalized](#structkln_1_1rotor_1ab063d72ca484de581a78ebd7b49e41da)(float * data) noexcept  {#structkln_1_1rotor_1ab063d72ca484de581a78ebd7b49e41da}

Fast load operation for packed data that is already normalized. The argument `data`  should point to a set of 4 float values with layout `(a, b, c, d)`  corresponding to the multivector $a + b\mathbf{e}_{12} + c\mathbf{e}_{31} + d\mathbf{e}_{23}$.

!!! danger 
    The rotor data loaded this way *must* be normalized. That is, the
    rotor $r$ must satisfy $r\widetilde{r} = 1$.

#### void  [normalize](#structkln_1_1rotor_1a4c9b04d0a4119e7d6b56b9e1478db5d4)() noexcept  {#structkln_1_1rotor_1a4c9b04d0a4119e7d6b56b9e1478db5d4}

Normalize a rotor such that $\mathbf{r}\widetilde{\mathbf{r}} = 1$.

####  [mat4x4](/Klein/api/kln::mat4x4#structkln_1_1mat4x4)  [as_matrix](#structkln_1_1rotor_1a0f13d2649e679220fc79ee7bc0bbea11)() const noexcept  {#structkln_1_1rotor_1a0f13d2649e679220fc79ee7bc0bbea11}

Converts the rotor to a 4x4 column-major matrix.

####  [plane](/Klein/api/kln::plane#structkln_1_1plane) KLN_VEC_CALL  [operator()](#structkln_1_1rotor_1ae9e58f02352f5241dd94d22353a5e9ec)( [plane](/Klein/api/kln::plane#structkln_1_1plane) const & p) const noexcept  {#structkln_1_1rotor_1ae9e58f02352f5241dd94d22353a5e9ec}

Conjugates a plane $p$ with this rotor and returns the result $rp\widetilde{r}$.

#### void KLN_VEC_CALL  [operator()](#structkln_1_1rotor_1a491f6f2264c6ecf180664e75fc4a159b)( [plane](/Klein/api/kln::plane#structkln_1_1plane) * in, [plane](/Klein/api/kln::plane#structkln_1_1plane) * out,size_t count) const noexcept  {#structkln_1_1rotor_1a491f6f2264c6ecf180664e75fc4a159b}

Conjugates an array of planes with this rotor in the input array and stores the result in the output array. Aliasing is only permitted when `in == out`  (in place motor application).

!!! tip 
    When applying a rotor to a list of tightly packed planes, this
    routine will be *significantly faster* than applying the rotor to
    each plane individually.

####  [line](/Klein/api/kln::line#structkln_1_1line) KLN_VEC_CALL  [operator()](#structkln_1_1rotor_1ac4d044ea5b98ba540fc5da8d75f43ccc)( [line](/Klein/api/kln::line#structkln_1_1line) const & l) const noexcept  {#structkln_1_1rotor_1ac4d044ea5b98ba540fc5da8d75f43ccc}

Conjugates a line $\ell$ with this rotor and returns the result $r\ell \widetilde{r}$.

#### void KLN_VEC_CALL  [operator()](#structkln_1_1rotor_1aad794881fa0c11fb05486986032a431a)( [line](/Klein/api/kln::line#structkln_1_1line) * in, [line](/Klein/api/kln::line#structkln_1_1line) * out,size_t count) const noexcept  {#structkln_1_1rotor_1aad794881fa0c11fb05486986032a431a}

Conjugates an array of lines with this rotor in the input array and stores the result in the output array. Aliasing is only permitted when `in == out`  (in place rotor application).

!!! tip 
    When applying a rotor to a list of tightly packed lines, this
    routine will be *significantly faster* than applying the rotor to
    each line individually.

####  [point](/Klein/api/kln::point#structkln_1_1point) KLN_VEC_CALL  [operator()](#structkln_1_1rotor_1a5aabb4caa402fb5793807fe1d8cec199)( [point](/Klein/api/kln::point#structkln_1_1point) const & p) const noexcept  {#structkln_1_1rotor_1a5aabb4caa402fb5793807fe1d8cec199}

Conjugates a point $p$ with this rotor and returns the result $rp\widetilde{r}$.

#### void KLN_VEC_CALL  [operator()](#structkln_1_1rotor_1aa91e4024d7368fbd14a93ead29905aad)( [point](/Klein/api/kln::point#structkln_1_1point) * in, [point](/Klein/api/kln::point#structkln_1_1point) * out,size_t count) const noexcept  {#structkln_1_1rotor_1aa91e4024d7368fbd14a93ead29905aad}

Conjugates an array of points with this rotor in the input array and stores the result in the output array. Aliasing is only permitted when `in == out`  (in place rotor application).

!!! tip 
    When applying a rotor to a list of tightly packed points, this
    routine will be *significantly faster* than applying the rotor to
    each point individually.

####  [direction](/Klein/api/kln::direction#structkln_1_1direction) KLN_VEC_CALL  [operator()](#structkln_1_1rotor_1a80935add9a99987a59879df1aa868b43)( [direction](/Klein/api/kln::direction#structkln_1_1direction) const & d) const noexcept  {#structkln_1_1rotor_1a80935add9a99987a59879df1aa868b43}

Conjugates a direction $d$ with this rotor and returns the result $rd\widetilde{r}$.

#### void KLN_VEC_CALL  [operator()](#structkln_1_1rotor_1a185ca5be93f00396e5e0de9a05561999)( [direction](/Klein/api/kln::direction#structkln_1_1direction) * in, [direction](/Klein/api/kln::direction#structkln_1_1direction) * out,size_t count) const noexcept  {#structkln_1_1rotor_1a185ca5be93f00396e5e0de9a05561999}

Conjugates an array of directions with this rotor in the input array and stores the result in the output array. Aliasing is only permitted when `in == out`  (in place rotor application).

!!! tip 
    When applying a rotor to a list of tightly packed directions, this
    routine will be *significantly faster* than applying the rotor to
    each direction individually.

