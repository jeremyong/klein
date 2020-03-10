#pragma once

#include "inner_product.hpp"
#include "line.hpp"
#include "meet.hpp"
#include "plane.hpp"
#include "point.hpp"

namespace kln
{
/// \defgroup proj Projections
///
/// Projections in Geometric Algebra take on a particularly simple form.
/// For two geometric entities $a$ and $b$, there are two cases to consider.
/// First, if the grade of $a$ is greater than the grade of $b$, the projection
/// of $a$ on $b$ is given by:
///
/// $$ \textit{proj}_b a = (a \cdot b) \wedge b $$
///
/// The inner product can be thought of as the part of $b$ _least like_ $a$.
/// Using the meet operator on this part produces the part of $b$ _most like_
/// $a$. A simple sanity check is to consider the grades of the result. If the
/// grade of $b$ is less than the grade of $a$, we end up with an entity with
/// grade $a - b + b = a$ as expected.
///
/// In the second case (the grade of $a$ is less than the grade of $b$), the
/// projection of $a$ on $b$ is given by:
///
/// $$ \textit{proj}_b a = (a \cdot b) \cdot b $$
///
/// It can be verified that as in the first case, the grade of the result is the
/// same as the grade of $a$. As this projection occurs in the opposite sense
/// from what one may have seen before, additional clarification is provided
/// below.

/// \addtogroup proj
/// @{

/// Project a point onto a line
inline point KLN_VEC_CALL project(point a, line b) noexcept
{
    return {(a | b) ^ b};
}

/// Project a point onto a plane
inline point KLN_VEC_CALL project(point a, plane b) noexcept
{
    return {(a | b) ^ b};
}

/// Project a line onto a plane
inline line KLN_VEC_CALL project(line a, plane b) noexcept
{
    return {(a | b) ^ b};
}

/// Project a plane onto a point. Given a plane $p$ and point $P$, produces the
/// plane through $P$ that is parallel to $p$.
///
/// Intuitively, the point is represented dually in terms of a _pencil of
/// planes_ that converge on the point itself. When we compute $p | P$, this
/// selects the line perpendicular to $p$ through $P$. Subsequently, taking the
/// inner product with $P$ again selects the plane from the plane pencil of $P$
/// _least like_ that line.
inline plane KLN_VEC_CALL project(plane a, point b) noexcept
{
    return {(a | b) | b};
}

/// Project a line onto a point. Given a line $\ell$ and point $P$, produces the
/// line through $P$ that is parallel to $\ell$.
inline line KLN_VEC_CALL project(line a, point b) noexcept
{
    return {(a | b) | b};
}

/// Project a plane onto a line. Given a plane $p$ and line $\ell$, produces the
/// plane through $\ell$ that is parallel to $p$ if $p \parallel \ell$.
///
/// If $p \nparallel \ell$, the result will be the plane $p'$ containing $\ell$
/// that maximizes $p \cdot p'$ (that is, $p'$ is as parallel to $p$ as
/// possible).
inline plane KLN_VEC_CALL project(plane a, line b) noexcept
{
    return {(a | b) | b};
}
/// @}
} // namespace kln
