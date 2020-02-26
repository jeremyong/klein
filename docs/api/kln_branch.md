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
`public ` [`entity`](../../api/kln_entity#structkln_1_1entity)` ` [`exp`](#structkln_1_1branch_1a341d43c4152ba03b8001134962900799)`() const noexcept`  | Exponentiate this branch to produce a rotor. To avoid a circular dependency, an `entity<0b10>`  is returned but this can be implicitly cast to a rotor.

### Members

####   [branch](#structkln_1_1branch_1ac0b6196328f798a024d116b0052dc933)() = default  {#structkln_1_1branch_1ac0b6196328f798a024d116b0052dc933}

####   [branch](#structkln_1_1branch_1a85e647f4c92a2dd6896c5afd849d00a5)(float a,float b,float c) noexcept  {#structkln_1_1branch_1a85e647f4c92a2dd6896c5afd849d00a5}

Construct the branch as the following multivector:

$$a \mathbf{e}_{23} + b\mathbf{e}_{31} + c\mathbf{e}_{23}$$

To convince yourself this is a line through the origin, remember that such a line can be generated using the geometric product of two planes through the origin.

####   [branch](#structkln_1_1branch_1a870f4e065425fe5f13bbed7bab1813f5)( [entity](../../api/kln_entity#structkln_1_1entity) const & other) noexcept  {#structkln_1_1branch_1a870f4e065425fe5f13bbed7bab1813f5}

####   [branch](#structkln_1_1branch_1ab521b26d8ec73aff3695456573964d77)( [entity](../../api/kln_entity#structkln_1_1entity) && other) noexcept  {#structkln_1_1branch_1ab521b26d8ec73aff3695456573964d77}

####  [entity](../../api/kln_entity#structkln_1_1entity)  [exp](#structkln_1_1branch_1a341d43c4152ba03b8001134962900799)() const noexcept  {#structkln_1_1branch_1a341d43c4152ba03b8001134962900799}

Exponentiate this branch to produce a rotor. To avoid a circular dependency, an `entity<0b10>`  is returned but this can be implicitly cast to a rotor.

