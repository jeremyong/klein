## group `translator` {#group__translator}

A translator represents a rigid-body displacement along a normalized axis. To apply the translator to a supported entity, the call operator is available.

!!! example 
    ```c++
        // Initialize a point at (1, 3, 2)
        kln::point p{1.f, 3.f, 2.f};
    
        // Create a normalized translator representing a 4-unit
        // displacement along the xz-axis.
        kln::translator r{4.f, 1.f, 0.f, 1.f};
    
        // Displace our point using the created translator
        kln::point translated = r(p);
    ```
    We can translate lines and planes as well using the translator's call
    operator.
    

Translators can be multiplied to one another with the `*`  operator to create a new translator equivalent to the application of each factor.

!!! example 
    ```c++
        // Suppose we have 3 translators t1, t2, and t3
    
        // The translator t created here represents the combined action of
        // t1, t2, and t3.
        kln::translator t = t3 * t2 * t1;
    ```
    

The same `*`  operator can be used to compose the translator's action with other rotors and motors.

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  ` [`translator`](#group__translator_1ga874afec21015e89c7b5f6f2100b5d2e7)`() = default`             | 
`public  ` [`translator`](#group__translator_1ga0978aecd03c99d9f677ec606ccc2ace7)`(float delta,float x,float y,float z) noexcept`             | 
`public void ` [`load_normalized`](#group__translator_1gaf41d16e554ed66e640671ca9065971b7)`(float * data) noexcept`             | Fast load operation for packed data that is already normalized. The argument `data`  should point to a set of 4 float values with layout `(0.f, a, b, c)`  corresponding to the multivector $a\mathbf{e}_{01} + b\mathbf{e}_{02} + c\mathbf{e}_{03}$.
`public void ` [`invert`](#group__translator_1gaeec4cf70b528e2d42197dd41988a54a5)`() noexcept`             | 
`public translator ` [`inverse`](#group__translator_1ga73c92c1080705f7ba48db4d3618099f8)`() const noexcept`             | 
`public plane KLN_VEC_CALL ` [`operator()`](#group__translator_1ga0e313cc6d057b518bbc8b04ad6baec59)`(plane const & p) const noexcept`             | Conjugates a plane $p$ with this translator and returns the result $tp\widetilde{t}$.
`public line KLN_VEC_CALL ` [`operator()`](#group__translator_1gaa0a9ea85643aa7661d52dd477abd76e7)`(line const & l) const noexcept`             | Conjugates a line $\ell$ with this translator and returns the result $t\ell\widetilde{t}$.
`public point KLN_VEC_CALL ` [`operator()`](#group__translator_1ga6d5ee3578eb48f36bf3e21d321899de5)`(point const & p) const noexcept`             | Conjugates a point $p$ with this translator and returns the result $tp\widetilde{t}$.
`public translator &KLN_VEC_CALL ` [`operator+=`](#group__translator_1ga49752f41c5f97f0762539987d642a4d1)`(translator b) noexcept`             | Translator addition.
`public translator &KLN_VEC_CALL ` [`operator-=`](#group__translator_1gaaca2b5944e513109311d94db6f294602)`(translator b) noexcept`             | Translator subtraction.
`public translator & ` [`operator*=`](#group__translator_1ga85db690441a3e6b08a011fc135c6143d)`(float s) noexcept`             | Translator uniform scale.
`public translator & ` [`operator*=`](#group__translator_1ga0fb9f7fec0d845c83f3c0562cb11d4bc)`(int s) noexcept`             | Translator uniform scale.
`public translator & ` [`operator/=`](#group__translator_1gabb5212f116d7a101f1b100a633a47f8a)`(float s) noexcept`             | Translator uniform inverse scale.
`public translator & ` [`operator/=`](#group__translator_1ga6a9907e06b825ceff92381a60f14570f)`(int s) noexcept`             | Translator uniform inverse scale.
`public constexpr float ` [`scalar`](#group__translator_1gaa533f8460dc4d5dcc3b6b868312d89b2)`() const noexcept`             | 
`public float ` [`e01`](#group__translator_1ga6c6997510798262d55159ad561e6d802)`() const noexcept`             | 
`public float ` [`e10`](#group__translator_1ga00ad9b79f9f69cfb673181cba78f2b2a)`() const noexcept`             | 
`public float ` [`e02`](#group__translator_1ga1e5679476ac84d9e955eed0acda3f59f)`() const noexcept`             | 
`public float ` [`e20`](#group__translator_1ga9a45e67aa72dd2a2e64018c88c2718c4)`() const noexcept`             | 
`public float ` [`e03`](#group__translator_1ga2cfdf0ad3c3d46577ad1fa35823cb269)`() const noexcept`             | 
`public float ` [`e30`](#group__translator_1ga368c9a79810d0e89dba2c2db60c1b64b)`() const noexcept`             | 
`public translator KLN_VEC_CALL ` [`operator+`](#group__translator_1ga4d4537ac246252b4e8e74ac59da4de7a)`(translator a,translator b) noexcept`             | Translator addition.
`public translator KLN_VEC_CALL ` [`operator-`](#group__translator_1gad9a822eb6bd4121692f793e8daf68ecf)`(translator a,translator b) noexcept`             | Translator subtraction.
`public translator KLN_VEC_CALL ` [`operator*`](#group__translator_1gac8b7dc64bc66050e4ca2420f5e428afb)`(translator t,float s) noexcept`             | Translator uniform scale.
`public translator KLN_VEC_CALL ` [`operator*`](#group__translator_1gaa866552f47bd7da0babfab1773b15ef9)`(translator t,int s) noexcept`             | Translator uniform scale.
`public translator KLN_VEC_CALL ` [`operator*`](#group__translator_1ga624432a0049e9dde5e0212a8cea3947a)`(float s,translator t) noexcept`             | Translator uniform scale.
`public translator KLN_VEC_CALL ` [`operator*`](#group__translator_1gae9e9a9834017da4ff56a7534f4fbfab2)`(int s,translator t) noexcept`             | Translator uniform scale.
`public translator KLN_VEC_CALL ` [`operator/`](#group__translator_1ga37b49b10ff0308eb2ace0ddce0dc1f2c)`(translator t,float s) noexcept`             | Translator uniform inverse scale.
`public translator KLN_VEC_CALL ` [`operator/`](#group__translator_1gacbb55db349bac24159d854b293df81c7)`(translator t,int s) noexcept`             | Translator uniform inverse scale.

### Members

####   [translator](#group__translator_1ga874afec21015e89c7b5f6f2100b5d2e7)() = default  {#group__translator_1ga874afec21015e89c7b5f6f2100b5d2e7}

####   [translator](#group__translator_1ga0978aecd03c99d9f677ec606ccc2ace7)(float delta,float x,float y,float z) noexcept  {#group__translator_1ga0978aecd03c99d9f677ec606ccc2ace7}

#### void  [load_normalized](#group__translator_1gaf41d16e554ed66e640671ca9065971b7)(float * data) noexcept  {#group__translator_1gaf41d16e554ed66e640671ca9065971b7}

Fast load operation for packed data that is already normalized. The argument `data`  should point to a set of 4 float values with layout `(0.f, a, b, c)`  corresponding to the multivector $a\mathbf{e}_{01} + b\mathbf{e}_{02} + c\mathbf{e}_{03}$.

!!! danger 
    The translator data loaded this way *must* be normalized. That is,
    the quantity $-\sqrt{a^2 + b^2 + c^2}$ must be half the desired
    displacement.

#### void  [invert](#group__translator_1gaeec4cf70b528e2d42197dd41988a54a5)() noexcept  {#group__translator_1gaeec4cf70b528e2d42197dd41988a54a5}

#### translator  [inverse](#group__translator_1ga73c92c1080705f7ba48db4d3618099f8)() const noexcept  {#group__translator_1ga73c92c1080705f7ba48db4d3618099f8}

#### plane KLN_VEC_CALL  [operator()](#group__translator_1ga0e313cc6d057b518bbc8b04ad6baec59)(plane const & p) const noexcept  {#group__translator_1ga0e313cc6d057b518bbc8b04ad6baec59}

Conjugates a plane $p$ with this translator and returns the result $tp\widetilde{t}$.

#### line KLN_VEC_CALL  [operator()](#group__translator_1gaa0a9ea85643aa7661d52dd477abd76e7)(line const & l) const noexcept  {#group__translator_1gaa0a9ea85643aa7661d52dd477abd76e7}

Conjugates a line $\ell$ with this translator and returns the result $t\ell\widetilde{t}$.

#### point KLN_VEC_CALL  [operator()](#group__translator_1ga6d5ee3578eb48f36bf3e21d321899de5)(point const & p) const noexcept  {#group__translator_1ga6d5ee3578eb48f36bf3e21d321899de5}

Conjugates a point $p$ with this translator and returns the result $tp\widetilde{t}$.

#### translator &KLN_VEC_CALL  [operator+=](#group__translator_1ga49752f41c5f97f0762539987d642a4d1)(translator b) noexcept  {#group__translator_1ga49752f41c5f97f0762539987d642a4d1}

Translator addition.

#### translator &KLN_VEC_CALL  [operator-=](#group__translator_1gaaca2b5944e513109311d94db6f294602)(translator b) noexcept  {#group__translator_1gaaca2b5944e513109311d94db6f294602}

Translator subtraction.

#### translator &  [operator*=](#group__translator_1ga85db690441a3e6b08a011fc135c6143d)(float s) noexcept  {#group__translator_1ga85db690441a3e6b08a011fc135c6143d}

Translator uniform scale.

#### translator &  [operator*=](#group__translator_1ga0fb9f7fec0d845c83f3c0562cb11d4bc)(int s) noexcept  {#group__translator_1ga0fb9f7fec0d845c83f3c0562cb11d4bc}

Translator uniform scale.

#### translator &  [operator/=](#group__translator_1gabb5212f116d7a101f1b100a633a47f8a)(float s) noexcept  {#group__translator_1gabb5212f116d7a101f1b100a633a47f8a}

Translator uniform inverse scale.

#### translator &  [operator/=](#group__translator_1ga6a9907e06b825ceff92381a60f14570f)(int s) noexcept  {#group__translator_1ga6a9907e06b825ceff92381a60f14570f}

Translator uniform inverse scale.

#### float  [scalar](#group__translator_1gaa533f8460dc4d5dcc3b6b868312d89b2)() const noexcept  {#group__translator_1gaa533f8460dc4d5dcc3b6b868312d89b2}

#### float  [e01](#group__translator_1ga6c6997510798262d55159ad561e6d802)() const noexcept  {#group__translator_1ga6c6997510798262d55159ad561e6d802}

#### float  [e10](#group__translator_1ga00ad9b79f9f69cfb673181cba78f2b2a)() const noexcept  {#group__translator_1ga00ad9b79f9f69cfb673181cba78f2b2a}

#### float  [e02](#group__translator_1ga1e5679476ac84d9e955eed0acda3f59f)() const noexcept  {#group__translator_1ga1e5679476ac84d9e955eed0acda3f59f}

#### float  [e20](#group__translator_1ga9a45e67aa72dd2a2e64018c88c2718c4)() const noexcept  {#group__translator_1ga9a45e67aa72dd2a2e64018c88c2718c4}

#### float  [e03](#group__translator_1ga2cfdf0ad3c3d46577ad1fa35823cb269)() const noexcept  {#group__translator_1ga2cfdf0ad3c3d46577ad1fa35823cb269}

#### float  [e30](#group__translator_1ga368c9a79810d0e89dba2c2db60c1b64b)() const noexcept  {#group__translator_1ga368c9a79810d0e89dba2c2db60c1b64b}

#### translator KLN_VEC_CALL  [operator+](#group__translator_1ga4d4537ac246252b4e8e74ac59da4de7a)(translator a,translator b) noexcept  {#group__translator_1ga4d4537ac246252b4e8e74ac59da4de7a}

Translator addition.

#### translator KLN_VEC_CALL  [operator-](#group__translator_1gad9a822eb6bd4121692f793e8daf68ecf)(translator a,translator b) noexcept  {#group__translator_1gad9a822eb6bd4121692f793e8daf68ecf}

Translator subtraction.

#### translator KLN_VEC_CALL  [operator*](#group__translator_1gac8b7dc64bc66050e4ca2420f5e428afb)(translator t,float s) noexcept  {#group__translator_1gac8b7dc64bc66050e4ca2420f5e428afb}

Translator uniform scale.

#### translator KLN_VEC_CALL  [operator*](#group__translator_1gaa866552f47bd7da0babfab1773b15ef9)(translator t,int s) noexcept  {#group__translator_1gaa866552f47bd7da0babfab1773b15ef9}

Translator uniform scale.

#### translator KLN_VEC_CALL  [operator*](#group__translator_1ga624432a0049e9dde5e0212a8cea3947a)(float s,translator t) noexcept  {#group__translator_1ga624432a0049e9dde5e0212a8cea3947a}

Translator uniform scale.

#### translator KLN_VEC_CALL  [operator*](#group__translator_1gae9e9a9834017da4ff56a7534f4fbfab2)(int s,translator t) noexcept  {#group__translator_1gae9e9a9834017da4ff56a7534f4fbfab2}

Translator uniform scale.

#### translator KLN_VEC_CALL  [operator/](#group__translator_1ga37b49b10ff0308eb2ace0ddce0dc1f2c)(translator t,float s) noexcept  {#group__translator_1ga37b49b10ff0308eb2ace0ddce0dc1f2c}

Translator uniform inverse scale.

#### translator KLN_VEC_CALL  [operator/](#group__translator_1gacbb55db349bac24159d854b293df81c7)(translator t,int s) noexcept  {#group__translator_1gacbb55db349bac24159d854b293df81c7}

Translator uniform inverse scale.

