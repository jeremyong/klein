## struct `kln::translator` {#structkln_1_1translator}

```
struct kln::translator
  : public kln::entity< 0b110 >
```  

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
`public  ` [`translator`](#structkln_1_1translator_1aea5e64c659061f07a509d5924b0c07b1)`() = default`  | 
`public  ` [`translator`](#structkln_1_1translator_1a79f802a9ad0d2ce8121e53e1041300d2)`(float delta,float x,float y,float z)`  | 
`public  ` [`translator`](#structkln_1_1translator_1abad7c4f575baf7c82b8e6dd4917a12cb)`(` [`entity`](/Klein/api/kln::entity#structkln_1_1entity)`< 0b110 > const & other)`  | 
`public void ` [`load_normalized`](#structkln_1_1translator_1af41d16e554ed66e640671ca9065971b7)`(float * data) noexcept`  | Fast load operation for packed data that is already normalized. The argument `data`  should point to a set of 4 float values with layout `(0.f, a, b, c)`  corresponding to the multivector $a\mathbf{e}_{01} + b\mathbf{e}_{02} + c\mathbf{e}_{03}$.
`public ` [`plane`](/Klein/api/kln::plane#structkln_1_1plane)` KLN_VEC_CALL ` [`operator()`](#structkln_1_1translator_1a0e313cc6d057b518bbc8b04ad6baec59)`(` [`plane`](/Klein/api/kln::plane#structkln_1_1plane)` const & p) const noexcept`  | Conjugates a plane $p$ with this translator and returns the result $tp\widetilde{t}$.
`public ` [`line`](/Klein/api/kln::line#structkln_1_1line)` KLN_VEC_CALL ` [`operator()`](#structkln_1_1translator_1aa0a9ea85643aa7661d52dd477abd76e7)`(` [`line`](/Klein/api/kln::line#structkln_1_1line)` const & l) const noexcept`  | Conjugates a line $\ell$ with this translator and returns the result $t\ell\widetilde{t}$.
`public ` [`point`](/Klein/api/kln::point#structkln_1_1point)` KLN_VEC_CALL ` [`operator()`](#structkln_1_1translator_1a6d5ee3578eb48f36bf3e21d321899de5)`(` [`point`](/Klein/api/kln::point#structkln_1_1point)` const & p) const noexcept`  | Conjugates a point $p$ with this translator and returns the result $tp\widetilde{t}$.

### Members

####   [translator](#structkln_1_1translator_1aea5e64c659061f07a509d5924b0c07b1)() = default  {#structkln_1_1translator_1aea5e64c659061f07a509d5924b0c07b1}

####   [translator](#structkln_1_1translator_1a79f802a9ad0d2ce8121e53e1041300d2)(float delta,float x,float y,float z)  {#structkln_1_1translator_1a79f802a9ad0d2ce8121e53e1041300d2}

####   [translator](#structkln_1_1translator_1abad7c4f575baf7c82b8e6dd4917a12cb)( [entity](/Klein/api/kln::entity#structkln_1_1entity)< 0b110 > const & other)  {#structkln_1_1translator_1abad7c4f575baf7c82b8e6dd4917a12cb}

#### void  [load_normalized](#structkln_1_1translator_1af41d16e554ed66e640671ca9065971b7)(float * data) noexcept  {#structkln_1_1translator_1af41d16e554ed66e640671ca9065971b7}

Fast load operation for packed data that is already normalized. The argument `data`  should point to a set of 4 float values with layout `(0.f, a, b, c)`  corresponding to the multivector $a\mathbf{e}_{01} + b\mathbf{e}_{02} + c\mathbf{e}_{03}$.

!!! danger 
    The translator data loaded this way *must* be normalized. That is,
    the quantity $-\sqrt{a^2 + b^2 + c^2}$ must be half the desired
    displacement.

####  [plane](/Klein/api/kln::plane#structkln_1_1plane) KLN_VEC_CALL  [operator()](#structkln_1_1translator_1a0e313cc6d057b518bbc8b04ad6baec59)( [plane](/Klein/api/kln::plane#structkln_1_1plane) const & p) const noexcept  {#structkln_1_1translator_1a0e313cc6d057b518bbc8b04ad6baec59}

Conjugates a plane $p$ with this translator and returns the result $tp\widetilde{t}$.

####  [line](/Klein/api/kln::line#structkln_1_1line) KLN_VEC_CALL  [operator()](#structkln_1_1translator_1aa0a9ea85643aa7661d52dd477abd76e7)( [line](/Klein/api/kln::line#structkln_1_1line) const & l) const noexcept  {#structkln_1_1translator_1aa0a9ea85643aa7661d52dd477abd76e7}

Conjugates a line $\ell$ with this translator and returns the result $t\ell\widetilde{t}$.

####  [point](/Klein/api/kln::point#structkln_1_1point) KLN_VEC_CALL  [operator()](#structkln_1_1translator_1a6d5ee3578eb48f36bf3e21d321899de5)( [point](/Klein/api/kln::point#structkln_1_1point) const & p) const noexcept  {#structkln_1_1translator_1a6d5ee3578eb48f36bf3e21d321899de5}

Conjugates a point $p$ with this translator and returns the result $tp\widetilde{t}$.

