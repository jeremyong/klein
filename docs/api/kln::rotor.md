## struct `kln::rotor` {#structkln_1_1rotor}

```
struct kln::rotor
  : public kln::entity< 0b10 >
```  

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  ` [`rotor`](#structkln_1_1rotor_1a3d3e11652d0c83a5f86de0d33b259be4)`() = default`  | Default constructor leaves memory uninitialized.
`public  ` [`rotor`](#structkln_1_1rotor_1a1ed5b58579ef482f98fcd019476f883c)`(float ang_rad,float x,float y,float z)`  | Convenience constructor. Computes transcendentals and normalizes rotation axis.
`public  ` [`rotor`](#structkln_1_1rotor_1aa14da87f8cbcddbd997fb29738214298)`(` [`entity`](/Klein/api/kln::entity#structkln_1_1entity)`< 0b10 > const & other)`  | 
`public void ` [`load_normalized`](#structkln_1_1rotor_1ab063d72ca484de581a78ebd7b49e41da)`(float * data) noexcept`  | Fast load operation for packed data that is already normalized. The argument `data`  should point to a set of 4 float values with layout `(a, b, c, d)`  corresponding to the multivector $a + b\mathbf{e}_{12} + c\mathbf{e}_{31} + d\mathbf{e}_{23}$.
`public void ` [`normalize`](#structkln_1_1rotor_1a4c9b04d0a4119e7d6b56b9e1478db5d4)`() noexcept`  | Normalize a rotor such that $\mathbf{r}\widetilde{\mathbf{r}} = 1$.
`public ` [`plane`](/Klein/api/kln::plane#structkln_1_1plane)` KLN_VEC_CALL ` [`operator()`](#structkln_1_1rotor_1ae9e58f02352f5241dd94d22353a5e9ec)`(` [`plane`](/Klein/api/kln::plane#structkln_1_1plane)` const & p) const noexcept`  | Conjugates a plane $p$ with this rotor and returns the result $rp\widetilde{r}$.
`public ` [`point`](/Klein/api/kln::point#structkln_1_1point)` KLN_VEC_CALL ` [`operator()`](#structkln_1_1rotor_1a5aabb4caa402fb5793807fe1d8cec199)`(` [`point`](/Klein/api/kln::point#structkln_1_1point)` const & p) const noexcept`  | Conjugates a point $p$ with this rotor and returns the result $rp\widetilde{r}$.
`public ` [`mat4x4`](/Klein/api/kln::mat4x4#structkln_1_1mat4x4)` ` [`as_matrix`](#structkln_1_1rotor_1a0f13d2649e679220fc79ee7bc0bbea11)`() const noexcept`  | Converts the rotor to a 4x4 column-major matrix.

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

####  [plane](/Klein/api/kln::plane#structkln_1_1plane) KLN_VEC_CALL  [operator()](#structkln_1_1rotor_1ae9e58f02352f5241dd94d22353a5e9ec)( [plane](/Klein/api/kln::plane#structkln_1_1plane) const & p) const noexcept  {#structkln_1_1rotor_1ae9e58f02352f5241dd94d22353a5e9ec}

Conjugates a plane $p$ with this rotor and returns the result $rp\widetilde{r}$.

####  [point](/Klein/api/kln::point#structkln_1_1point) KLN_VEC_CALL  [operator()](#structkln_1_1rotor_1a5aabb4caa402fb5793807fe1d8cec199)( [point](/Klein/api/kln::point#structkln_1_1point) const & p) const noexcept  {#structkln_1_1rotor_1a5aabb4caa402fb5793807fe1d8cec199}

Conjugates a point $p$ with this rotor and returns the result $rp\widetilde{r}$.

####  [mat4x4](/Klein/api/kln::mat4x4#structkln_1_1mat4x4)  [as_matrix](#structkln_1_1rotor_1a0f13d2649e679220fc79ee7bc0bbea11)() const noexcept  {#structkln_1_1rotor_1a0f13d2649e679220fc79ee7bc0bbea11}

Converts the rotor to a 4x4 column-major matrix.

