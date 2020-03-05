#pragma once

#include "detail/geometric_product.hpp"

#include "dual.hpp"
#include "line.hpp"
#include "motor.hpp"
#include "plane.hpp"
#include "point.hpp"
#include "rotor.hpp"
#include "translator.hpp"

namespace kln
{
/// \defgroup gp Geometric Product
///
/// The geometric product extends the exterior product with a notion of a
/// metric. When the subspace intersection of the operands of two basis
/// elements is non-zero, instead of the product extinguishing, the grade
/// collapses and a scalar weight is included in the final result according
/// to the metric. The geometric product can be used to build rotations, and
/// by extension, rotations and translations in projective space.
///
/// !!! example "Rotor composition"
///
///     ```cpp
///         kln::rotor r1{ang1, x1, y1, z1};
///         kln::rotor r2{ang2, x2, y2, z2};
///
///         // Compose rotors with the geometric product
///         kln::rotor r3 = r1 * r2;; // r3 combines r2 and r1 in that order
///     ```
///
/// !!! example "Two reflections"
///
///     ```cpp
///         kln::plane p1{x1, y1, z1, d1};
///         kln::plane p2{x2, y2, z2, d2};
///
///         // The geometric product of two planes combines their reflections
///         kln::motor m3 = p1 * p2;; // m3 combines p2 and p1 in that order
///     ```
/// \addtogroup gp
/// @{

/// Construct a motor $m$ such that $\sqrt{m}$ takes plane $b$ to plane $a$.
///
/// !!! example
///
///     ```cpp
///         kln::plane p1{x1, y1, z1, d1};
///         kln::plane p2{x2, y2, z2, d2};
///         kln::motor m = sqrt(p1 * p2);
///         plane p3 = m(p2);
///         // p3 will be approximately equal to p1
///     ```
[[nodiscard]] inline motor KLN_VEC_CALL operator*(plane a, plane b) noexcept
{
    motor out;
    detail::gp00(a.p0_, b.p0_, out.p1_, out.p2_);
    return out;
}

[[nodiscard]] inline motor KLN_VEC_CALL operator*(plane a, point b) noexcept
{
    motor out;
    detail::gp03<false>(a.p0_, b.p3_, out.p1_, out.p2_);
    return out;
}

[[nodiscard]] inline motor KLN_VEC_CALL operator*(point b, plane a) noexcept
{
    motor out;
    detail::gp03<true>(a.p0_, b.p3_, out.p1_, out.p2_);
    return out;
}

/// Generates a motor $m$ that produces a screw motion about the common normal
/// to lines $a$ and $b$. The motor given by $\sqrt{m}$ takes $b$ to $a$
/// provided that $a$ and $b$ are both normalized.
[[nodiscard]] inline motor KLN_VEC_CALL operator*(line a, line b) noexcept
{
    motor out;
    detail::gpLL(a.p1_, b.p1_, &out.p1_);
    return out;
}

/// Generates a translator $t$ that produces a displacement along the line
/// between points $a$ and $b$. The translator given by $\sqrt{t}$ takes $b$ to
/// $a$.
[[nodiscard]] inline translator KLN_VEC_CALL operator*(point a, point b) noexcept
{
    translator out;
    detail::gp33(a.p3_, b.p3_, out.p2_);
    return out;
}

/// Composes two rotational actions such that the produced rotor has the same
/// effect as applying rotor $b$, then rotor $a$.
[[nodiscard]] inline rotor KLN_VEC_CALL operator*(rotor a, rotor b) noexcept
{
    rotor out;
    detail::gp11(a.p1_, b.p1_, out.p1_);
    return out;
}

/// The product of a dual number and a line effectively weights the line with a
/// rotational and translational quantity. Subsequent exponentiation will
/// produce a motor along the screw axis of line $b$ with rotation and
/// translation given by half the scalar and pseudoscalar parts of the dual
/// number $a$ respectively.
[[nodiscard]] inline line KLN_VEC_CALL operator*(dual a, line b) noexcept
{
    line out;
    detail::gpDL(a.p, a.q, b.p1_, b.p2_, out.p1_, out.p2_);
    return out;
}

[[nodiscard]] inline line KLN_VEC_CALL operator*(line b, dual a) noexcept
{
    return a * b;
}

[[nodiscard]] inline motor KLN_VEC_CALL operator*(rotor a, translator b) noexcept
{
    motor out;
    out.p1_ = a.p1_;
    detail::gpRT<false>(a.p1_, b.p2_, out.p2_);
    return out;
}

[[nodiscard]] inline motor KLN_VEC_CALL operator*(translator b, rotor a) noexcept
{
    motor out;
    out.p1_ = a.p1_;
    detail::gpRT<true>(a.p1_, b.p2_, out.p2_);
    return out;
}

[[nodiscard]] inline translator KLN_VEC_CALL operator*(translator a,
                                                       translator b) noexcept
{
    return a + b;
}

[[nodiscard]] inline motor KLN_VEC_CALL operator*(rotor a, motor b) noexcept
{
    motor out;
    detail::gp11(a.p1_, b.p1_, out.p1_);
    detail::gp12<false>(a.p1_, b.p2_, out.p2_);
    return out;
}

[[nodiscard]] inline motor KLN_VEC_CALL operator*(motor b, rotor a) noexcept
{
    motor out;
    detail::gp11(b.p1_, a.p1_, out.p1_);
    detail::gp12<true>(a.p1_, b.p2_, out.p2_);
    return out;
}

[[nodiscard]] inline motor KLN_VEC_CALL operator*(translator a, motor b) noexcept
{
    motor out;
    out.p1_ = b.p1_;
    detail::gpRT<true>(b.p1_, a.p2_, out.p2_);
    out.p2_ = _mm_add_ps(out.p2_, b.p2_);
    return out;
}

[[nodiscard]] inline motor KLN_VEC_CALL operator*(motor b, translator a) noexcept
{
    motor out;
    out.p1_ = b.p1_;
    detail::gpRT<false>(b.p1_, a.p2_, out.p2_);
    out.p2_ = _mm_add_ps(out.p2_, b.p2_);
    return out;
}

[[nodiscard]] inline motor KLN_VEC_CALL operator*(motor a, motor b) noexcept
{
    motor out;
    detail::gpMM(a.p1_, b.p1_, &out.p1_);
    return out;
}
/// @}
} // namespace kln