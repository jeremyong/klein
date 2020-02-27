## struct `kln::branch` {#structkln_1_1branch}

```
struct kln::branch
  : public kln::entity< 0b10 >
```  

The `branch`  both a line through the origin and also the principal branch of the logarithm of a rotor.

The rotor branch will be most commonly constructed by taking the logarithm of a normalized rotor. The branch may then be linearily scaled to adjust the "strength" of the rotor, and subsequently re-exponentiated to create the adjusted rotor.

!!! example 
    Suppose we have a rotor $r$ and we wish to produce a rotor
    $\sqrt[4]{r}$ which performs a quarter of the rotation produced by
    $r$. We can construct it like so:
    
    ```c++
        kln::branch b = r.log();
        kln::rotor r_4 = (0.25f * b).exp();
    ```
    

!!! note 
    The branch of a rotor is technically a `line`, but because there are
    no translational components, the branch is given its own type for
    efficiency.

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  ` [`branch`](#structkln_1_1branch_1ac0b6196328f798a024d116b0052dc933)`() = default`  | 
`public  ` [`branch`](#structkln_1_1branch_1a85e647f4c92a2dd6896c5afd849d00a5)`(float a,float b,float c) noexcept`  | Construct the branch as the following multivector:
`public  ` [`branch`](#structkln_1_1branch_1a870f4e065425fe5f13bbed7bab1813f5)`(` [`entity`](../../api/kln_entity#structkln_1_1entity)` const & other) noexcept`  | 
`public  ` [`branch`](#structkln_1_1branch_1ab521b26d8ec73aff3695456573964d77)`(` [`entity`](../../api/kln_entity#structkln_1_1entity)` && other) noexcept`  | 
`public float ` [`squared_norm`](#structkln_1_1branch_1a0c6c16090b660c63df26aacf985c6f0c)`() noexcept`  | If a line is constructed as the regressive product (join) of two points, the squared norm provided here is the squared distance between the two points (provided the points are normalized). Returns $d^2 + e^2 + f^2$.
`public float ` [`norm`](#structkln_1_1branch_1a6174cbd24d0189e3f5f9b893d63f5086)`() noexcept`  | Returns the square root of the quantity produced by `squared_norm` .
`public ` [`entity`](../../api/kln_entity#structkln_1_1entity)` ` [`exp`](#structkln_1_1branch_1a341d43c4152ba03b8001134962900799)`() const noexcept`  | Exponentiate this branch to produce a rotor. To avoid a circular dependency, an `entity<0b10>`  is returned but this can be implicitly cast to a rotor.

### Members

####   [branch](#structkln_1_1branch_1ac0b6196328f798a024d116b0052dc933)() = default  {#structkln_1_1branch_1ac0b6196328f798a024d116b0052dc933}

####   [branch](#structkln_1_1branch_1a85e647f4c92a2dd6896c5afd849d00a5)(float a,float b,float c) noexcept  {#structkln_1_1branch_1a85e647f4c92a2dd6896c5afd849d00a5}

Construct the branch as the following multivector:

$$a \mathbf{e}_{23} + b\mathbf{e}_{31} + c\mathbf{e}_{23}$$

To convince yourself this is a line through the origin, remember that such a line can be generated using the geometric product of two planes through the origin.

####   [branch](#structkln_1_1branch_1a870f4e065425fe5f13bbed7bab1813f5)( [entity](../../api/kln_entity#structkln_1_1entity) const & other) noexcept  {#structkln_1_1branch_1a870f4e065425fe5f13bbed7bab1813f5}

####   [branch](#structkln_1_1branch_1ab521b26d8ec73aff3695456573964d77)( [entity](../../api/kln_entity#structkln_1_1entity) && other) noexcept  {#structkln_1_1branch_1ab521b26d8ec73aff3695456573964d77}

#### float  [squared_norm](#structkln_1_1branch_1a0c6c16090b660c63df26aacf985c6f0c)() noexcept  {#structkln_1_1branch_1a0c6c16090b660c63df26aacf985c6f0c}

If a line is constructed as the regressive product (join) of two points, the squared norm provided here is the squared distance between the two points (provided the points are normalized). Returns $d^2 + e^2 + f^2$.

#### float  [norm](#structkln_1_1branch_1a6174cbd24d0189e3f5f9b893d63f5086)() noexcept  {#structkln_1_1branch_1a6174cbd24d0189e3f5f9b893d63f5086}

Returns the square root of the quantity produced by `squared_norm` .

####  [entity](../../api/kln_entity#structkln_1_1entity)  [exp](#structkln_1_1branch_1a341d43c4152ba03b8001134962900799)() const noexcept  {#structkln_1_1branch_1a341d43c4152ba03b8001134962900799}

Exponentiate this branch to produce a rotor. To avoid a circular dependency, an `entity<0b10>`  is returned but this can be implicitly cast to a rotor.

