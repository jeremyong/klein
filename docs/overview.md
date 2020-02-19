# API Overview

Working with Klein is designed to be as simple as it is efficient. To "grok" the API, the main thing
to understand is that everything that has an underlying multivector representation is an
[`entity`](../api/kln::entity) which means that all operations supported by the entity will be
inherited.

The entities provided are Euclidean objects ([`points`](../api/kln::point), [`lines`](../api/kln::line), [`planes`](../api/kln::plane)), objects that arise in
Projective space ([`directions`](../api/kln::direction), [`ideal lines`](../api/kln::ideal_line)),
and geometric actions ([`rotors`](../api/kln::rotor), [`translators`](../api/kln::translator),
[`motors`](../api/kln::motor), and [`planes`](../api/kln::plane)).

!!! note

    The call operator on a plane performs a _reflection_ of the passed entity through the plane. The call operator on a rotor performs a _rotation_ of the entity. The translator
    translates, and the motor performs a combination of a rotation and a translation.

The multivector operations such as the geometric product, exterior product, regressive product, etc.
are supported for all the listed entities above via the following operator table:

| Operator | Description             |
| -------- | ----------------------- |
| `+`      | Addition                |
| `-`      | Subtraction             |
| `*`      | Geometric Product       |
| `^`      | Exterior Product        |
| `&`      | Regressive Product      |
| `|`      | Symmetric Inner Product |
| `!`      | Poincaré Dual           |

!!! tip

    For the geometric actions (implemented via the conjugation operator $xP\widetilde{x}$), the call
    operator should be used on the action itself as this will invoke a more optimized routine than
    invoking `x * P * ~x` manually. For example, given a rotor `r` and a point `p`, applying the rotor
    to `p` as `r(p)` will be faster with equivalent results to `r * p * ~r`.

    Similarly, while the regressive product between two entities `a` and `b` can be computed as
    `!(!a ^ !b)`, the explicit `a & b` should be preferred for efficiency.

In some cases, entities may have specialized routines that will live on the child class. For
example, the exponential map makes sense to apply to bivector entities and thus lives on the `line`
struct. Each child entity also provides convenient constructors that accept Cartesian coordinates.
