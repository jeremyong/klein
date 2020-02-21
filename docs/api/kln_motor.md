## struct `kln::motor` {#structkln_1_1motor}

```
struct kln::motor
  : public kln::entity< 0b110 >
```  

A `motor`  represents a kinematic motion in our algebra. From [Chasles' theorem](https://en.wikipedia.org/wiki/Chasles%27_theorem_(kinematics)), we know that any rigid body displacement can be produced by a translation along a line, followed or preceded by a rotation about an axis parallel to that line. The motor algebra is isomorphic to the dual quaternions but exists here in the same algebra as all the other geometric entities and actions at our disposal. Operations such as composing a motor with a rotor or translator are possible for example. The primary benefit to using a motor over its corresponding matrix operation is twofold. First, you get the benefit of numerical stability when composing multiple actions via the geometric product (`*` ). Second, because the motors constitute a continuous group, they are amenable to smooth interpolation and differentiation.

!!! example 
    ```c++
        // Create a rotor representing a pi/2 rotation about the z-axis
        // Normalization is done automatically
        rotor r{M_PI * 0.5f, 0.f, 0.f, 1.f};
    
        // Create a translator that represents a translation of 1 unit
        // in the yz-direction. Normalization is done automatically.
        translator t{1.f, 0.f, 1.f, 1.f};
    
        // Create a motor that combines the action of the rotation and
        // translation above.
        motor m = r * t;
    
        // Initialize a point at (1, 3, 2)
        kln::point p1{1.f, 3.f, 2.f};
    
        // Translate p1 and rotate it to create a new point p2
        kln::point p2 = m(p1);
    ```
    

Motors can be multiplied to one another with the `*`  operator to create a new motor equivalent to the application of each factor.

!!! example 
    ```c++
        // Suppose we have 3 motors m1, m2, and m3
    
        // The motor m created here represents the combined action of m1,
        // m2, and m3.
        kln::motor m = m3 * m2 * m1;
    ```
    

The same `*`  operator can be used to compose the motor's action with other translators and rotors.

A demonstration of using the exponential and logarithmic map to blend between two motors is provided in a test case [here](https://github.com/jeremyong/Klein/blob/master/test/test_exp_log.cpp#L48).

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  ` [`motor`](#structkln_1_1motor_1af185a86b951973e31cd16398845f73bf)`() = default`  | 
`public  ` [`motor`](#structkln_1_1motor_1a0fc9829b8e6323e3ae2cc583361ce3d5)`(float a,float b,float c,float d,float e,float f,float g,float h) noexcept`  | Direct initialization from components. A more common way of creating a motor is to take a product between a rotor and a translator. The arguments coorespond to the multivector $a + b\mathbf{e}_{12} + c\mathbf{e}_{31} + d\mathbf{e}_{23} +\ e\mathbf{e}_{01} + f\mathbf{e}_{02} + g\mathbf{e}_{03} +\ h\mathbf{e}_{0123}$
`public  ` [`motor`](#structkln_1_1motor_1a3c24baaa74a00bbc2cf64729916498b8)`(` [`entity`](../../api/kln_entity#structkln_1_1entity)`< 0b110 > const & e) noexcept`  | 
`public void ` [`load`](#structkln_1_1motor_1a3a048b8d0f35322259f8f1cbaad88cab)`(float * in) noexcept`  | Load motor data using two unaligned loads. This routine does *not* assume the data passed in this way is normalized.
`public void ` [`normalize`](#structkln_1_1motor_1a8af12b78c4e98b84c51f605b47dbc0a1)`() noexcept`  | Normalizes this motor $m$ such that $m\widetilde{m} = 1$.
`public ` [`mat4x4`](../../api/kln_mat4x4#structkln_1_1mat4x4)` ` [`as_matrix`](#structkln_1_1motor_1a51c1bcd6b7c6a6aa0525a8eff29974ab)`() const noexcept`  | Convert this motor to a 4x4 column-major matrix representing this motor's action as a linear transformation.
`public ` [`entity`](../../api/kln_entity#structkln_1_1entity)`< 0b110 > ` [`log`](#structkln_1_1motor_1a578fe040bb8c7c9b90c9c10050549374)`() const noexcept`  | Takes the principal branch of the logarithm of the motor, returning a bivector. Exponentiation of that bivector without any changes produces this motor again. Scaling that bivector by $\frac{1}{n}$, re-exponentiating, and taking the result to the $n$th power will also produce this motor again.
`public ` [`plane`](../../api/kln_plane#structkln_1_1plane)` KLN_VEC_CALL ` [`operator()`](#structkln_1_1motor_1aa0a1d879d7716f962c1c18a0d8483196)`(` [`plane`](../../api/kln_plane#structkln_1_1plane)` const & p) const noexcept`  | Conjugates a plane $p$ with this motor and returns the result $mp\widetilde{m}$.
`public void KLN_VEC_CALL ` [`operator()`](#structkln_1_1motor_1aff16ea8f993f2c7ddb7e64aa5fd089ad)`(` [`plane`](../../api/kln_plane#structkln_1_1plane)` * in,` [`plane`](../../api/kln_plane#structkln_1_1plane)` * out,size_t count) const noexcept`  | Conjugates an array of planes with this motor in the input array and stores the result in the output array. Aliasing is only permitted when `in == out`  (in place motor application).
`public ` [`line`](../../api/kln_line#structkln_1_1line)` KLN_VEC_CALL ` [`operator()`](#structkln_1_1motor_1addae2fa94b3f6aa0045209c7692397e7)`(` [`line`](../../api/kln_line#structkln_1_1line)` const & l) const noexcept`  | Conjugates a line $\ell$ with this motor and returns the result $m\ell \widetilde{m}$.
`public void KLN_VEC_CALL ` [`operator()`](#structkln_1_1motor_1a63d8a856db029b21898c203115c431e0)`(` [`line`](../../api/kln_line#structkln_1_1line)` * in,` [`line`](../../api/kln_line#structkln_1_1line)` * out,size_t count) const noexcept`  | Conjugates an array of lines with this motor in the input array and stores the result in the output array. Aliasing is only permitted when `in == out`  (in place motor application).
`public ` [`point`](../../api/kln_point#structkln_1_1point)` KLN_VEC_CALL ` [`operator()`](#structkln_1_1motor_1a7ae8d73c558d1f6581df3a4b50fb2a40)`(` [`point`](../../api/kln_point#structkln_1_1point)` const & p) const noexcept`  | Conjugates a point $p$ with this motor and returns the result $mp\widetilde{m}$.
`public void KLN_VEC_CALL ` [`operator()`](#structkln_1_1motor_1ab14cf440bf8281b4a56cc338c568156b)`(` [`point`](../../api/kln_point#structkln_1_1point)` * in,` [`point`](../../api/kln_point#structkln_1_1point)` * out,size_t count) const noexcept`  | Conjugates an array of points with this motor in the input array and stores the result in the output array. Aliasing is only permitted when `in == out`  (in place motor application).
`public ` [`point`](../../api/kln_point#structkln_1_1point)` KLN_VEC_CALL ` [`operator()`](#structkln_1_1motor_1afa77e3a1d5a8f28bf6eee4de9e174489)`(` [`origin`](../../api/kln_origin#structkln_1_1origin)`) const noexcept`  | Conjugates the origin $O$ with this motor and returns the result $mO\widetilde{m}$.
`public ` [`direction`](../../api/kln_direction#structkln_1_1direction)` KLN_VEC_CALL ` [`operator()`](#structkln_1_1motor_1ac8debbfe23b80affa7bf9ef7e0dffc1f)`(` [`direction`](../../api/kln_direction#structkln_1_1direction)` const & d) const noexcept`  | Conjugates a direction $d$ with this motor and returns the result $md\widetilde{m}$.
`public void KLN_VEC_CALL ` [`operator()`](#structkln_1_1motor_1aff385bad1df3b7ee29439b56bec43376)`(` [`direction`](../../api/kln_direction#structkln_1_1direction)` * in,` [`direction`](../../api/kln_direction#structkln_1_1direction)` * out,size_t count) const noexcept`  | Conjugates an array of directions with this motor in the input array and stores the result in the output array. Aliasing is only permitted when `in == out`  (in place motor application).

### Members

####   [motor](#structkln_1_1motor_1af185a86b951973e31cd16398845f73bf)() = default  {#structkln_1_1motor_1af185a86b951973e31cd16398845f73bf}

####   [motor](#structkln_1_1motor_1a0fc9829b8e6323e3ae2cc583361ce3d5)(float a,float b,float c,float d,float e,float f,float g,float h) noexcept  {#structkln_1_1motor_1a0fc9829b8e6323e3ae2cc583361ce3d5}

Direct initialization from components. A more common way of creating a motor is to take a product between a rotor and a translator. The arguments coorespond to the multivector $a + b\mathbf{e}_{12} + c\mathbf{e}_{31} + d\mathbf{e}_{23} +\ e\mathbf{e}_{01} + f\mathbf{e}_{02} + g\mathbf{e}_{03} +\ h\mathbf{e}_{0123}$

####   [motor](#structkln_1_1motor_1a3c24baaa74a00bbc2cf64729916498b8)( [entity](../../api/kln_entity#structkln_1_1entity)< 0b110 > const & e) noexcept  {#structkln_1_1motor_1a3c24baaa74a00bbc2cf64729916498b8}

#### void  [load](#structkln_1_1motor_1a3a048b8d0f35322259f8f1cbaad88cab)(float * in) noexcept  {#structkln_1_1motor_1a3a048b8d0f35322259f8f1cbaad88cab}

Load motor data using two unaligned loads. This routine does *not* assume the data passed in this way is normalized.

#### void  [normalize](#structkln_1_1motor_1a8af12b78c4e98b84c51f605b47dbc0a1)() noexcept  {#structkln_1_1motor_1a8af12b78c4e98b84c51f605b47dbc0a1}

Normalizes this motor $m$ such that $m\widetilde{m} = 1$.

####  [mat4x4](../../api/kln_mat4x4#structkln_1_1mat4x4)  [as_matrix](#structkln_1_1motor_1a51c1bcd6b7c6a6aa0525a8eff29974ab)() const noexcept  {#structkln_1_1motor_1a51c1bcd6b7c6a6aa0525a8eff29974ab}

Convert this motor to a 4x4 column-major matrix representing this motor's action as a linear transformation.

####  [entity](../../api/kln_entity#structkln_1_1entity)< 0b110 >  [log](#structkln_1_1motor_1a578fe040bb8c7c9b90c9c10050549374)() const noexcept  {#structkln_1_1motor_1a578fe040bb8c7c9b90c9c10050549374}

Takes the principal branch of the logarithm of the motor, returning a bivector. Exponentiation of that bivector without any changes produces this motor again. Scaling that bivector by $\frac{1}{n}$, re-exponentiating, and taking the result to the $n$th power will also produce this motor again.

####  [plane](../../api/kln_plane#structkln_1_1plane) KLN_VEC_CALL  [operator()](#structkln_1_1motor_1aa0a1d879d7716f962c1c18a0d8483196)( [plane](../../api/kln_plane#structkln_1_1plane) const & p) const noexcept  {#structkln_1_1motor_1aa0a1d879d7716f962c1c18a0d8483196}

Conjugates a plane $p$ with this motor and returns the result $mp\widetilde{m}$.

#### void KLN_VEC_CALL  [operator()](#structkln_1_1motor_1aff16ea8f993f2c7ddb7e64aa5fd089ad)( [plane](../../api/kln_plane#structkln_1_1plane) * in, [plane](../../api/kln_plane#structkln_1_1plane) * out,size_t count) const noexcept  {#structkln_1_1motor_1aff16ea8f993f2c7ddb7e64aa5fd089ad}

Conjugates an array of planes with this motor in the input array and stores the result in the output array. Aliasing is only permitted when `in == out`  (in place motor application).

!!! tip 
    When applying a motor to a list of tightly packed planes, this
    routine will be *significantly faster* than applying the motor to
    each plane individually.

####  [line](../../api/kln_line#structkln_1_1line) KLN_VEC_CALL  [operator()](#structkln_1_1motor_1addae2fa94b3f6aa0045209c7692397e7)( [line](../../api/kln_line#structkln_1_1line) const & l) const noexcept  {#structkln_1_1motor_1addae2fa94b3f6aa0045209c7692397e7}

Conjugates a line $\ell$ with this motor and returns the result $m\ell \widetilde{m}$.

#### void KLN_VEC_CALL  [operator()](#structkln_1_1motor_1a63d8a856db029b21898c203115c431e0)( [line](../../api/kln_line#structkln_1_1line) * in, [line](../../api/kln_line#structkln_1_1line) * out,size_t count) const noexcept  {#structkln_1_1motor_1a63d8a856db029b21898c203115c431e0}

Conjugates an array of lines with this motor in the input array and stores the result in the output array. Aliasing is only permitted when `in == out`  (in place motor application).

!!! tip 
    When applying a motor to a list of tightly packed lines, this
    routine will be *significantly faster* than applying the motor to
    each line individually.

####  [point](../../api/kln_point#structkln_1_1point) KLN_VEC_CALL  [operator()](#structkln_1_1motor_1a7ae8d73c558d1f6581df3a4b50fb2a40)( [point](../../api/kln_point#structkln_1_1point) const & p) const noexcept  {#structkln_1_1motor_1a7ae8d73c558d1f6581df3a4b50fb2a40}

Conjugates a point $p$ with this motor and returns the result $mp\widetilde{m}$.

#### void KLN_VEC_CALL  [operator()](#structkln_1_1motor_1ab14cf440bf8281b4a56cc338c568156b)( [point](../../api/kln_point#structkln_1_1point) * in, [point](../../api/kln_point#structkln_1_1point) * out,size_t count) const noexcept  {#structkln_1_1motor_1ab14cf440bf8281b4a56cc338c568156b}

Conjugates an array of points with this motor in the input array and stores the result in the output array. Aliasing is only permitted when `in == out`  (in place motor application).

!!! tip 
    When applying a motor to a list of tightly packed points, this
    routine will be *significantly faster* than applying the motor to
    each point individually.

####  [point](../../api/kln_point#structkln_1_1point) KLN_VEC_CALL  [operator()](#structkln_1_1motor_1afa77e3a1d5a8f28bf6eee4de9e174489)( [origin](../../api/kln_origin#structkln_1_1origin)) const noexcept  {#structkln_1_1motor_1afa77e3a1d5a8f28bf6eee4de9e174489}

Conjugates the origin $O$ with this motor and returns the result $mO\widetilde{m}$.

####  [direction](../../api/kln_direction#structkln_1_1direction) KLN_VEC_CALL  [operator()](#structkln_1_1motor_1ac8debbfe23b80affa7bf9ef7e0dffc1f)( [direction](../../api/kln_direction#structkln_1_1direction) const & d) const noexcept  {#structkln_1_1motor_1ac8debbfe23b80affa7bf9ef7e0dffc1f}

Conjugates a direction $d$ with this motor and returns the result $md\widetilde{m}$.

The cost of this operation is the same as the application of a rotor due to the translational invariance of directions (points at infinity).

#### void KLN_VEC_CALL  [operator()](#structkln_1_1motor_1aff385bad1df3b7ee29439b56bec43376)( [direction](../../api/kln_direction#structkln_1_1direction) * in, [direction](../../api/kln_direction#structkln_1_1direction) * out,size_t count) const noexcept  {#structkln_1_1motor_1aff385bad1df3b7ee29439b56bec43376}

Conjugates an array of directions with this motor in the input array and stores the result in the output array. Aliasing is only permitted when `in == out`  (in place motor application).

The cost of this operation is the same as the application of a rotor due to the translational invariance of directions (points at infinity).

!!! tip 
    When applying a motor to a list of tightly packed directions, this
    routine will be *significantly faster* than applying the motor to
    each direction individually.

