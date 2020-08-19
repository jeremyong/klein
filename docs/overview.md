# API Overview

<style>
tr > td:first-child {
  white-space: nowrap;
}
</style>

Working with Klein is designed to be as simple as it is efficient. To "grok" the API, it suffices to
understand the API in terms of the primary operations supported through the primary geometric entities.

The entities provided are Euclidean objects ([`points`](../api/point), [`lines`](../api/lines), [`planes`](../api/plane)), objects that arise in
Projective space ([`directions`](../api/dir), [`ideal lines`](../api/lines)),
and geometric actions ([`rotors`](../api/rotor), [`translators`](../api/translator),
[`motors`](../api/motor), and [`planes`](../api/plane)).

| Class        | Description                                                                                                                                                                                                |
| ------------ | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `plane`      | A plane is the manifestation of a reflection of $\mathbf{E}^3$ (consider the set of fixed points of a reflection).                                                                                         |
| `line`       | A line is the manifestation of a rotation of $\mathbf{E}^3$ (consider the set of fixed points of a rotation).                                                                                              |
| `branch`     | A branch is a line through the origin                                                                                                                                                                      |
| `ideal_line` | An ideal line is a line at infinity                                                                                                                                                                        |
| `point`      | A point is the manifestation of a roto-reflection of $\mathbf{E}^3$ (which has a single fixed point)                                                                                                       |
| `direction`  | A direction is modeled as a point at infinity (homogeneous weight $0$)                                                                                                                                     |
| `rotor`      | A rotor is the product of two intersecting planes (generating a rotation)                                                                                                                                  |
| `translator` | A translator is the product of two parallel planes (generating a translation)                                                                                                                              |
| `motor`      | A motor is a screw combining a rotation and translation along a screw axis                                                                                                                                 |
| `dual`       | A dual is the sum of a scalar and pseudoscalar quantity. Dual numbers show up in a number of contexts, including the factorization of a motor axis, and as the result of several meet and join operations. |

!!! note

    The call operator on a plane performs a _reflection_ of the passed entity through the plane. The call operator on a rotor performs a _rotation_ of the entity. The translator
    translates, and the motor performs a combination of a rotation and a translation.

The multivector operations such as the geometric product, exterior product, regressive product, etc.
are supported for all the listed entities above via the following operator table:

| Operator | Description                                   |
| -------- | --------------------------------------------- |
| `+`      | Addition                                      |
| `-`      | Subtraction                                   |
| `* s`    | Uniform scaling by a float or int `s`         |
| `/ s`    | Uniform inverse scaling by a float or int `s` |
| `*`      | [Geometric Product](../api/gp)                |
| `^`      | [Exterior Product](../api/ext)                |
| `&`      | [Regressive Product](../api/reg)              |
| `|`      | [Symmetric Inner Product](../api/dot)         |
| `!`      | [Poincaré Dual](../api/dual)                  |

!!! note

    Addition and subtraction is only supported between arguments of the same type. For example, two planes can be added together, but not a `plane` and a `rotor`.

!!! tip

    For the geometric actions (implemented via the conjugation operator $xP\widetilde{x}$), the call
    operator should be used on the action itself as this will invoke a more optimized routine than
    invoking `x * P * ~x` manually. For example, given a rotor `r` and a point `p`, applying the rotor
    to `p` as `r(p)` will be faster with equivalent results to `r * p * ~r`.

    Similarly, while the regressive product between two entities `a` and `b` can be computed as
    `!(!a ^ !b)`, the explicit `a & b` should be preferred for efficiency.

There are a few additional freestanding functions to perform various tasks.

| Function  | Description                                                                  |
| --------- | ---------------------------------------------------------------------------- |
| `project` | Projects the first argument onto the second argument and returns the result. |
| `log`     | Takes the logarithm of the argument and returns the result.                  |
| `exp`     | Computes the exponential of the argument and returns the result.             |
| `sqrt`    | Computes the square root of a rotor or motor and returns the result.         |

!!! note

    Throughout the API, you may see functions and methods marked with `KLN_VEC_CALL`. This macro expands to `__vectorcall` to ensure that register passing is used on MSVC.
