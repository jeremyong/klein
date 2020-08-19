## group `motor` {#group__motor}

A `motor`  represents a kinematic motion in our algebra. From [Chasles' theorem](https://en.wikipedia.org/wiki/Chasles%27_theorem_(kinematics)), we know that any rigid body displacement can be produced by a translation along a line, followed or preceded by a rotation about an axis parallel to that line. The motor algebra is isomorphic to the dual quaternions but exists here in the same algebra as all the other geometric entities and actions at our disposal. Operations such as composing a motor with a rotor or translator are possible for example. The primary benefit to using a motor over its corresponding matrix operation is twofold. First, you get the benefit of numerical stability when composing multiple actions via the geometric product (`*` ). Second, because the motors constitute a continuous group, they are amenable to smooth interpolation and differentiation.

!!! example 
    ```c++
        // Create a rotor representing a pi/2 rotation about the z-axis
        // Normalization is done automatically
        rotor r{kln::pi * 0.5f, 0.f, 0.f, 1.f};
    
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
`public  ` [`motor`](#group__motor_1ga96e82b7a735eed93288b76e1ecb3c13c)`() = default`             | 
`public  ` [`motor`](#group__motor_1ga0fc9829b8e6323e3ae2cc583361ce3d5)`(float a,float b,float c,float d,float e,float f,float g,float h) noexcept`             | Direct initialization from components. A more common way of creating a motor is to take a product between a rotor and a translator. The arguments coorespond to the multivector $a + b\mathbf{e}_{23} + c\mathbf{e}_{31} + d\mathbf{e}_{12} +\ e\mathbf{e}_{01} + f\mathbf{e}_{02} + g\mathbf{e}_{03} +\ h\mathbf{e}_{0123}$.
`public  ` [`motor`](#group__motor_1ga5cb2fa5186236dffe8ddc875ad0b5063)`(float ang_rad,float d,line l) noexcept`             | Produce a screw motion rotating and translating by given amounts along a provided Euclidean axis.
`public  ` [`motor`](#group__motor_1gae0f8cc6b72368628648b650d0fb21186)`(__m128 p1,__m128 p2) noexcept`             | 
`public KLN_VEC_CALL explicit ` [`motor`](#group__motor_1ga87f97067c7decdab7ee4fda78dc37e88)`(rotor r) noexcept`             | 
`public KLN_VEC_CALL explicit ` [`motor`](#group__motor_1ga032fcbcf02e92c46144674a3365fc75a)`(translator t) noexcept`             | 
`public motor &KLN_VEC_CALL ` [`operator=`](#group__motor_1ga34cad9009f782f022e61b57d2364e414)`(rotor r) noexcept`             | 
`public motor &KLN_VEC_CALL ` [`operator=`](#group__motor_1gacbd7ff04372942af09879f71d0f62d3a)`(translator t) noexcept`             | 
`public void ` [`load`](#group__motor_1ga3a048b8d0f35322259f8f1cbaad88cab)`(float * in) noexcept`             | Load motor data using two unaligned loads. This routine does *not* assume the data passed in this way is normalized.
`public void ` [`normalize`](#group__motor_1ga8af12b78c4e98b84c51f605b47dbc0a1)`() noexcept`             | Normalizes this motor $m$ such that $m\widetilde{m} = 1$.
`public motor ` [`normalized`](#group__motor_1ga6d04fd7c7cfc51f614e73018f1e92122)`() const noexcept`             | Return a normalized copy of this motor.
`public void ` [`invert`](#group__motor_1ga934628e8e8f6d444b1d2fde50e44e219)`() noexcept`             | 
`public motor ` [`inverse`](#group__motor_1ga0eacf6f6c4f25da1746a9769040ef17f)`() const noexcept`             | 
`public void ` [`constrain`](#group__motor_1gae856f717434c757ae51f7b63d3a46871)`() noexcept`             | Constrains the motor to traverse the shortest arc.
`public motor ` [`constrained`](#group__motor_1ga7db461c10aede892e0d3abd5be0fa099)`() const noexcept`             | 
`public bool KLN_VEC_CALL ` [`operator==`](#group__motor_1ga96324fdd9ee73afdc3b246b1aa1177a0)`(motor other) const noexcept`             | Bitwise comparison.
`public bool KLN_VEC_CALL ` [`approx_eq`](#group__motor_1ga38cc29c04cc13dadeac2b93547079ced)`(motor other,float epsilon) const noexcept`             | 
`public mat3x4 ` [`as_mat3x4`](#group__motor_1gae07a4ac9001f3afe4e1200e114ccf4c6)`() const noexcept`             | Convert this motor to a 3x4 column-major matrix representing this motor's action as a linear transformation. The motor must be normalized for this conversion to produce well-defined results, but is more efficient than a 4x4 matrix conversion.
`public mat4x4 ` [`as_mat4x4`](#group__motor_1gaa84cd8df11fc906888dff2fd20fa6e7b)`() const noexcept`             | Convert this motor to a 4x4 column-major matrix representing this motor's action as a linear transformation.
`public plane KLN_VEC_CALL ` [`operator()`](#group__motor_1gaa0a1d879d7716f962c1c18a0d8483196)`(plane const & p) const noexcept`             | Conjugates a plane $p$ with this motor and returns the result $mp\widetilde{m}$.
`public void KLN_VEC_CALL ` [`operator()`](#group__motor_1gaff16ea8f993f2c7ddb7e64aa5fd089ad)`(plane * in,plane * out,size_t count) const noexcept`             | Conjugates an array of planes with this motor in the input array and stores the result in the output array. Aliasing is only permitted when `in == out`  (in place motor application).
`public line KLN_VEC_CALL ` [`operator()`](#group__motor_1gaddae2fa94b3f6aa0045209c7692397e7)`(line const & l) const noexcept`             | Conjugates a line $\ell$ with this motor and returns the result $m\ell \widetilde{m}$.
`public void KLN_VEC_CALL ` [`operator()`](#group__motor_1ga63d8a856db029b21898c203115c431e0)`(line * in,line * out,size_t count) const noexcept`             | Conjugates an array of lines with this motor in the input array and stores the result in the output array. Aliasing is only permitted when `in == out`  (in place motor application).
`public point KLN_VEC_CALL ` [`operator()`](#group__motor_1ga7ae8d73c558d1f6581df3a4b50fb2a40)`(point const & p) const noexcept`             | Conjugates a point $p$ with this motor and returns the result $mp\widetilde{m}$.
`public void KLN_VEC_CALL ` [`operator()`](#group__motor_1gab14cf440bf8281b4a56cc338c568156b)`(point * in,point * out,size_t count) const noexcept`             | Conjugates an array of points with this motor in the input array and stores the result in the output array. Aliasing is only permitted when `in == out`  (in place motor application).
`public point KLN_VEC_CALL ` [`operator()`](#group__motor_1gafa77e3a1d5a8f28bf6eee4de9e174489)`(origin) const noexcept`             | Conjugates the origin $O$ with this motor and returns the result $mO\widetilde{m}$.
`public direction KLN_VEC_CALL ` [`operator()`](#group__motor_1gac8debbfe23b80affa7bf9ef7e0dffc1f)`(direction const & d) const noexcept`             | Conjugates a direction $d$ with this motor and returns the result $md\widetilde{m}$.
`public void KLN_VEC_CALL ` [`operator()`](#group__motor_1gaff385bad1df3b7ee29439b56bec43376)`(direction * in,direction * out,size_t count) const noexcept`             | Conjugates an array of directions with this motor in the input array and stores the result in the output array. Aliasing is only permitted when `in == out`  (in place motor application).
`public motor &KLN_VEC_CALL ` [`operator+=`](#group__motor_1ga818ff5291121c508902dca5f1e5b7a09)`(motor b) noexcept`             | Motor addition.
`public motor &KLN_VEC_CALL ` [`operator-=`](#group__motor_1ga339f89870f76a0016cfadf2fc68cd918)`(motor b) noexcept`             | Motor subtraction.
`public motor & ` [`operator*=`](#group__motor_1gafd63fa96a2333b28014f8e3a7a4134ca)`(float s) noexcept`             | Motor uniform scale.
`public motor & ` [`operator*=`](#group__motor_1ga119d48b12fc69b8fa0d1d02654d719a8)`(int s) noexcept`             | Motor uniform scale.
`public motor & ` [`operator/=`](#group__motor_1gad8ffc1682cb5df750eea6436a4f27d77)`(float s) noexcept`             | Motor uniform inverse scale.
`public motor & ` [`operator/=`](#group__motor_1gaa8b3dad31ce3e1fd6d62ee72e5b826e0)`(int s) noexcept`             | Motor uniform inverse scale.
`public float ` [`scalar`](#group__motor_1ga2dad79dbeb201dc9dafad1c94ecd51cc)`() const noexcept`             | 
`public float ` [`e12`](#group__motor_1ga0d37119c1407e00425424c4784e7f075)`() const noexcept`             | 
`public float ` [`e21`](#group__motor_1ga6d47c218ab3242156f10106fdf36a777)`() const noexcept`             | 
`public float ` [`e31`](#group__motor_1gae65d5ca5b4d158e23c942f93e3e2a6c1)`() const noexcept`             | 
`public float ` [`e13`](#group__motor_1ga12938d12f57ccb5f76e7594912582f7e)`() const noexcept`             | 
`public float ` [`e23`](#group__motor_1ga016619bad5d460399f782c396a4f1790)`() const noexcept`             | 
`public float ` [`e32`](#group__motor_1gadba251b758a64f618a0768b25de96644)`() const noexcept`             | 
`public float ` [`e01`](#group__motor_1gad7a738cbde6bf041842e9fce7db1a9aa)`() const noexcept`             | 
`public float ` [`e10`](#group__motor_1gac75be08d6e10f57e8c568968ff11fb0d)`() const noexcept`             | 
`public float ` [`e02`](#group__motor_1ga6e8d74bcf2ba45b732b34493104d9a68)`() const noexcept`             | 
`public float ` [`e20`](#group__motor_1ga119218e9aa8d5c1df3c06ac2a79d7eed)`() const noexcept`             | 
`public float ` [`e03`](#group__motor_1ga0f483bcb7243e177dc9815f383066fd1)`() const noexcept`             | 
`public float ` [`e30`](#group__motor_1ga607a40f4fffbad7fb4776ba68bbb1fea)`() const noexcept`             | 
`public float ` [`e0123`](#group__motor_1ga7c31381a8ba0be1d784f79f787ca06fc)`() const noexcept`             | 
`public motor KLN_VEC_CALL ` [`operator+`](#group__motor_1ga55bb0d01d56750ae852cccc9127ae60b)`(motor a,motor b) noexcept`             | Motor addition.
`public motor KLN_VEC_CALL ` [`operator-`](#group__motor_1ga3cb485fe89040eb6d01c70c96a031a14)`(motor a,motor b) noexcept`             | Motor subtraction.
`public motor KLN_VEC_CALL ` [`operator*`](#group__motor_1gafdb054b171b09ab54d6476d86e5d61e5)`(motor l,float s) noexcept`             | Motor uniform scale.
`public motor KLN_VEC_CALL ` [`operator*`](#group__motor_1gae7eb210b5f7b49e24db9ee02fda857e3)`(motor l,int s) noexcept`             | Motor uniform scale.
`public motor KLN_VEC_CALL ` [`operator*`](#group__motor_1ga046f149d83052d0f83a7d24e48653d00)`(float s,motor l) noexcept`             | Motor uniform scale.
`public motor KLN_VEC_CALL ` [`operator*`](#group__motor_1gadeb2482d5ca5548b73fbc81ea1559169)`(int s,motor l) noexcept`             | Motor uniform scale.
`public motor KLN_VEC_CALL ` [`operator/`](#group__motor_1gab9468a090086428d6c48d47f75e8b0e7)`(motor r,float s) noexcept`             | Motor uniform inverse scale.
`public motor KLN_VEC_CALL ` [`operator/`](#group__motor_1gacd7a8807bc6b6238b893150a8d8f97ca)`(motor r,int s) noexcept`             | Motor uniform inverse scale.
`public motor KLN_VEC_CALL ` [`operator-`](#group__motor_1gaf953e632f3ddff1dc435c3070e07c9b5)`(motor m) noexcept`             | Unary minus.
`public motor KLN_VEC_CALL ` [`operator~`](#group__motor_1gaf4f013b57e29f6925ddfdf2d6e25ce0a)`(motor m) noexcept`             | Reversion operator.

### Members

####   [motor](#group__motor_1ga96e82b7a735eed93288b76e1ecb3c13c)() = default  {#group__motor_1ga96e82b7a735eed93288b76e1ecb3c13c}

####   [motor](#group__motor_1ga0fc9829b8e6323e3ae2cc583361ce3d5)(float a,float b,float c,float d,float e,float f,float g,float h) noexcept  {#group__motor_1ga0fc9829b8e6323e3ae2cc583361ce3d5}

Direct initialization from components. A more common way of creating a motor is to take a product between a rotor and a translator. The arguments coorespond to the multivector $a + b\mathbf{e}_{23} + c\mathbf{e}_{31} + d\mathbf{e}_{12} +\ e\mathbf{e}_{01} + f\mathbf{e}_{02} + g\mathbf{e}_{03} +\ h\mathbf{e}_{0123}$.

####   [motor](#group__motor_1ga5cb2fa5186236dffe8ddc875ad0b5063)(float ang_rad,float d,line l) noexcept  {#group__motor_1ga5cb2fa5186236dffe8ddc875ad0b5063}

Produce a screw motion rotating and translating by given amounts along a provided Euclidean axis.

####   [motor](#group__motor_1gae0f8cc6b72368628648b650d0fb21186)(__m128 p1,__m128 p2) noexcept  {#group__motor_1gae0f8cc6b72368628648b650d0fb21186}

#### KLN_VEC_CALL explicit  [motor](#group__motor_1ga87f97067c7decdab7ee4fda78dc37e88)(rotor r) noexcept  {#group__motor_1ga87f97067c7decdab7ee4fda78dc37e88}

#### KLN_VEC_CALL explicit  [motor](#group__motor_1ga032fcbcf02e92c46144674a3365fc75a)(translator t) noexcept  {#group__motor_1ga032fcbcf02e92c46144674a3365fc75a}

#### motor &KLN_VEC_CALL  [operator=](#group__motor_1ga34cad9009f782f022e61b57d2364e414)(rotor r) noexcept  {#group__motor_1ga34cad9009f782f022e61b57d2364e414}

#### motor &KLN_VEC_CALL  [operator=](#group__motor_1gacbd7ff04372942af09879f71d0f62d3a)(translator t) noexcept  {#group__motor_1gacbd7ff04372942af09879f71d0f62d3a}

#### void  [load](#group__motor_1ga3a048b8d0f35322259f8f1cbaad88cab)(float * in) noexcept  {#group__motor_1ga3a048b8d0f35322259f8f1cbaad88cab}

Load motor data using two unaligned loads. This routine does *not* assume the data passed in this way is normalized.

#### void  [normalize](#group__motor_1ga8af12b78c4e98b84c51f605b47dbc0a1)() noexcept  {#group__motor_1ga8af12b78c4e98b84c51f605b47dbc0a1}

Normalizes this motor $m$ such that $m\widetilde{m} = 1$.

#### motor  [normalized](#group__motor_1ga6d04fd7c7cfc51f614e73018f1e92122)() const noexcept  {#group__motor_1ga6d04fd7c7cfc51f614e73018f1e92122}

Return a normalized copy of this motor.

#### void  [invert](#group__motor_1ga934628e8e8f6d444b1d2fde50e44e219)() noexcept  {#group__motor_1ga934628e8e8f6d444b1d2fde50e44e219}

#### motor  [inverse](#group__motor_1ga0eacf6f6c4f25da1746a9769040ef17f)() const noexcept  {#group__motor_1ga0eacf6f6c4f25da1746a9769040ef17f}

#### void  [constrain](#group__motor_1gae856f717434c757ae51f7b63d3a46871)() noexcept  {#group__motor_1gae856f717434c757ae51f7b63d3a46871}

Constrains the motor to traverse the shortest arc.

#### motor  [constrained](#group__motor_1ga7db461c10aede892e0d3abd5be0fa099)() const noexcept  {#group__motor_1ga7db461c10aede892e0d3abd5be0fa099}

#### bool KLN_VEC_CALL  [operator==](#group__motor_1ga96324fdd9ee73afdc3b246b1aa1177a0)(motor other) const noexcept  {#group__motor_1ga96324fdd9ee73afdc3b246b1aa1177a0}

Bitwise comparison.

#### bool KLN_VEC_CALL  [approx_eq](#group__motor_1ga38cc29c04cc13dadeac2b93547079ced)(motor other,float epsilon) const noexcept  {#group__motor_1ga38cc29c04cc13dadeac2b93547079ced}

#### mat3x4  [as_mat3x4](#group__motor_1gae07a4ac9001f3afe4e1200e114ccf4c6)() const noexcept  {#group__motor_1gae07a4ac9001f3afe4e1200e114ccf4c6}

Convert this motor to a 3x4 column-major matrix representing this motor's action as a linear transformation. The motor must be normalized for this conversion to produce well-defined results, but is more efficient than a 4x4 matrix conversion.

#### mat4x4  [as_mat4x4](#group__motor_1gaa84cd8df11fc906888dff2fd20fa6e7b)() const noexcept  {#group__motor_1gaa84cd8df11fc906888dff2fd20fa6e7b}

Convert this motor to a 4x4 column-major matrix representing this motor's action as a linear transformation.

#### plane KLN_VEC_CALL  [operator()](#group__motor_1gaa0a1d879d7716f962c1c18a0d8483196)(plane const & p) const noexcept  {#group__motor_1gaa0a1d879d7716f962c1c18a0d8483196}

Conjugates a plane $p$ with this motor and returns the result $mp\widetilde{m}$.

#### void KLN_VEC_CALL  [operator()](#group__motor_1gaff16ea8f993f2c7ddb7e64aa5fd089ad)(plane * in,plane * out,size_t count) const noexcept  {#group__motor_1gaff16ea8f993f2c7ddb7e64aa5fd089ad}

Conjugates an array of planes with this motor in the input array and stores the result in the output array. Aliasing is only permitted when `in == out`  (in place motor application).

!!! tip 
    When applying a motor to a list of tightly packed planes, this
    routine will be *significantly faster* than applying the motor to
    each plane individually.

#### line KLN_VEC_CALL  [operator()](#group__motor_1gaddae2fa94b3f6aa0045209c7692397e7)(line const & l) const noexcept  {#group__motor_1gaddae2fa94b3f6aa0045209c7692397e7}

Conjugates a line $\ell$ with this motor and returns the result $m\ell \widetilde{m}$.

#### void KLN_VEC_CALL  [operator()](#group__motor_1ga63d8a856db029b21898c203115c431e0)(line * in,line * out,size_t count) const noexcept  {#group__motor_1ga63d8a856db029b21898c203115c431e0}

Conjugates an array of lines with this motor in the input array and stores the result in the output array. Aliasing is only permitted when `in == out`  (in place motor application).

!!! tip 
    When applying a motor to a list of tightly packed lines, this
    routine will be *significantly faster* than applying the motor to
    each line individually.

#### point KLN_VEC_CALL  [operator()](#group__motor_1ga7ae8d73c558d1f6581df3a4b50fb2a40)(point const & p) const noexcept  {#group__motor_1ga7ae8d73c558d1f6581df3a4b50fb2a40}

Conjugates a point $p$ with this motor and returns the result $mp\widetilde{m}$.

#### void KLN_VEC_CALL  [operator()](#group__motor_1gab14cf440bf8281b4a56cc338c568156b)(point * in,point * out,size_t count) const noexcept  {#group__motor_1gab14cf440bf8281b4a56cc338c568156b}

Conjugates an array of points with this motor in the input array and stores the result in the output array. Aliasing is only permitted when `in == out`  (in place motor application).

!!! tip 
    When applying a motor to a list of tightly packed points, this
    routine will be *significantly faster* than applying the motor to
    each point individually.

#### point KLN_VEC_CALL  [operator()](#group__motor_1gafa77e3a1d5a8f28bf6eee4de9e174489)(origin) const noexcept  {#group__motor_1gafa77e3a1d5a8f28bf6eee4de9e174489}

Conjugates the origin $O$ with this motor and returns the result $mO\widetilde{m}$.

#### direction KLN_VEC_CALL  [operator()](#group__motor_1gac8debbfe23b80affa7bf9ef7e0dffc1f)(direction const & d) const noexcept  {#group__motor_1gac8debbfe23b80affa7bf9ef7e0dffc1f}

Conjugates a direction $d$ with this motor and returns the result $md\widetilde{m}$.

The cost of this operation is the same as the application of a rotor due to the translational invariance of directions (points at infinity).

#### void KLN_VEC_CALL  [operator()](#group__motor_1gaff385bad1df3b7ee29439b56bec43376)(direction * in,direction * out,size_t count) const noexcept  {#group__motor_1gaff385bad1df3b7ee29439b56bec43376}

Conjugates an array of directions with this motor in the input array and stores the result in the output array. Aliasing is only permitted when `in == out`  (in place motor application).

The cost of this operation is the same as the application of a rotor due to the translational invariance of directions (points at infinity).

!!! tip 
    When applying a motor to a list of tightly packed directions, this
    routine will be *significantly faster* than applying the motor to
    each direction individually.

#### motor &KLN_VEC_CALL  [operator+=](#group__motor_1ga818ff5291121c508902dca5f1e5b7a09)(motor b) noexcept  {#group__motor_1ga818ff5291121c508902dca5f1e5b7a09}

Motor addition.

#### motor &KLN_VEC_CALL  [operator-=](#group__motor_1ga339f89870f76a0016cfadf2fc68cd918)(motor b) noexcept  {#group__motor_1ga339f89870f76a0016cfadf2fc68cd918}

Motor subtraction.

#### motor &  [operator*=](#group__motor_1gafd63fa96a2333b28014f8e3a7a4134ca)(float s) noexcept  {#group__motor_1gafd63fa96a2333b28014f8e3a7a4134ca}

Motor uniform scale.

#### motor &  [operator*=](#group__motor_1ga119d48b12fc69b8fa0d1d02654d719a8)(int s) noexcept  {#group__motor_1ga119d48b12fc69b8fa0d1d02654d719a8}

Motor uniform scale.

#### motor &  [operator/=](#group__motor_1gad8ffc1682cb5df750eea6436a4f27d77)(float s) noexcept  {#group__motor_1gad8ffc1682cb5df750eea6436a4f27d77}

Motor uniform inverse scale.

#### motor &  [operator/=](#group__motor_1gaa8b3dad31ce3e1fd6d62ee72e5b826e0)(int s) noexcept  {#group__motor_1gaa8b3dad31ce3e1fd6d62ee72e5b826e0}

Motor uniform inverse scale.

#### float  [scalar](#group__motor_1ga2dad79dbeb201dc9dafad1c94ecd51cc)() const noexcept  {#group__motor_1ga2dad79dbeb201dc9dafad1c94ecd51cc}

#### float  [e12](#group__motor_1ga0d37119c1407e00425424c4784e7f075)() const noexcept  {#group__motor_1ga0d37119c1407e00425424c4784e7f075}

#### float  [e21](#group__motor_1ga6d47c218ab3242156f10106fdf36a777)() const noexcept  {#group__motor_1ga6d47c218ab3242156f10106fdf36a777}

#### float  [e31](#group__motor_1gae65d5ca5b4d158e23c942f93e3e2a6c1)() const noexcept  {#group__motor_1gae65d5ca5b4d158e23c942f93e3e2a6c1}

#### float  [e13](#group__motor_1ga12938d12f57ccb5f76e7594912582f7e)() const noexcept  {#group__motor_1ga12938d12f57ccb5f76e7594912582f7e}

#### float  [e23](#group__motor_1ga016619bad5d460399f782c396a4f1790)() const noexcept  {#group__motor_1ga016619bad5d460399f782c396a4f1790}

#### float  [e32](#group__motor_1gadba251b758a64f618a0768b25de96644)() const noexcept  {#group__motor_1gadba251b758a64f618a0768b25de96644}

#### float  [e01](#group__motor_1gad7a738cbde6bf041842e9fce7db1a9aa)() const noexcept  {#group__motor_1gad7a738cbde6bf041842e9fce7db1a9aa}

#### float  [e10](#group__motor_1gac75be08d6e10f57e8c568968ff11fb0d)() const noexcept  {#group__motor_1gac75be08d6e10f57e8c568968ff11fb0d}

#### float  [e02](#group__motor_1ga6e8d74bcf2ba45b732b34493104d9a68)() const noexcept  {#group__motor_1ga6e8d74bcf2ba45b732b34493104d9a68}

#### float  [e20](#group__motor_1ga119218e9aa8d5c1df3c06ac2a79d7eed)() const noexcept  {#group__motor_1ga119218e9aa8d5c1df3c06ac2a79d7eed}

#### float  [e03](#group__motor_1ga0f483bcb7243e177dc9815f383066fd1)() const noexcept  {#group__motor_1ga0f483bcb7243e177dc9815f383066fd1}

#### float  [e30](#group__motor_1ga607a40f4fffbad7fb4776ba68bbb1fea)() const noexcept  {#group__motor_1ga607a40f4fffbad7fb4776ba68bbb1fea}

#### float  [e0123](#group__motor_1ga7c31381a8ba0be1d784f79f787ca06fc)() const noexcept  {#group__motor_1ga7c31381a8ba0be1d784f79f787ca06fc}

#### motor KLN_VEC_CALL  [operator+](#group__motor_1ga55bb0d01d56750ae852cccc9127ae60b)(motor a,motor b) noexcept  {#group__motor_1ga55bb0d01d56750ae852cccc9127ae60b}

Motor addition.

#### motor KLN_VEC_CALL  [operator-](#group__motor_1ga3cb485fe89040eb6d01c70c96a031a14)(motor a,motor b) noexcept  {#group__motor_1ga3cb485fe89040eb6d01c70c96a031a14}

Motor subtraction.

#### motor KLN_VEC_CALL  [operator*](#group__motor_1gafdb054b171b09ab54d6476d86e5d61e5)(motor l,float s) noexcept  {#group__motor_1gafdb054b171b09ab54d6476d86e5d61e5}

Motor uniform scale.

#### motor KLN_VEC_CALL  [operator*](#group__motor_1gae7eb210b5f7b49e24db9ee02fda857e3)(motor l,int s) noexcept  {#group__motor_1gae7eb210b5f7b49e24db9ee02fda857e3}

Motor uniform scale.

#### motor KLN_VEC_CALL  [operator*](#group__motor_1ga046f149d83052d0f83a7d24e48653d00)(float s,motor l) noexcept  {#group__motor_1ga046f149d83052d0f83a7d24e48653d00}

Motor uniform scale.

#### motor KLN_VEC_CALL  [operator*](#group__motor_1gadeb2482d5ca5548b73fbc81ea1559169)(int s,motor l) noexcept  {#group__motor_1gadeb2482d5ca5548b73fbc81ea1559169}

Motor uniform scale.

#### motor KLN_VEC_CALL  [operator/](#group__motor_1gab9468a090086428d6c48d47f75e8b0e7)(motor r,float s) noexcept  {#group__motor_1gab9468a090086428d6c48d47f75e8b0e7}

Motor uniform inverse scale.

#### motor KLN_VEC_CALL  [operator/](#group__motor_1gacd7a8807bc6b6238b893150a8d8f97ca)(motor r,int s) noexcept  {#group__motor_1gacd7a8807bc6b6238b893150a8d8f97ca}

Motor uniform inverse scale.

#### motor KLN_VEC_CALL  [operator-](#group__motor_1gaf953e632f3ddff1dc435c3070e07c9b5)(motor m) noexcept  {#group__motor_1gaf953e632f3ddff1dc435c3070e07c9b5}

Unary minus.

#### motor KLN_VEC_CALL  [operator~](#group__motor_1gaf4f013b57e29f6925ddfdf2d6e25ce0a)(motor m) noexcept  {#group__motor_1gaf4f013b57e29f6925ddfdf2d6e25ce0a}

Reversion operator.

