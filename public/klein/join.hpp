#pragma once

#include "dual.hpp"
#include "line.hpp"
#include "plane.hpp"
#include "point.hpp"

#include "meet.hpp"

namespace kln
{
/// \defgroup dual Poincaré Dual
///
/// The Poincaré Dual of an element is the "subspace complement" of the
/// argument with respect to the pseudoscalar in the exterior algebra. In
/// practice, it is a relabeling of the coordinates to their
/// dual-coordinates and is used most often to implement a "join" operation
/// in terms of the exterior product of the duals of each operand.
///
/// Ex: The dual of the point $\mathbf{e}_{123} + 3\mathbf{e}_{013} -
/// 2\mathbf{e}_{021}$ (the point at
/// $(0, 3, -2)$) is the plane
/// $\mathbf{e}_0 + 3\mathbf{e}_2 - 2\mathbf{e}_3$.

/// \addtogroup dual
/// @{

KLN_INLINE point KLN_VEC_CALL operator!(plane in) noexcept
{
    return {in.p0_};
}

KLN_INLINE plane KLN_VEC_CALL operator!(point in) noexcept
{
    return {in.p3_};
}

KLN_INLINE line KLN_VEC_CALL operator!(line in) noexcept
{
    return {in.p2_, in.p1_};
}

KLN_INLINE branch KLN_VEC_CALL operator!(ideal_line in) noexcept
{
    return {in.p2_};
}

KLN_INLINE ideal_line KLN_VEC_CALL operator!(branch in) noexcept
{
    return {in.p1_};
}

KLN_INLINE dual KLN_VEC_CALL operator!(dual in) noexcept
{
    return {in.q, in.p};
}
/// @}

/// \defgroup reg Regressive Product
///
/// The regressive product is implemented in terms of the exterior product.
/// Given multivectors $\mathbf{a}$ and $\mathbf{b}$, the regressive product
/// $\mathbf{a}\vee\mathbf{b}$ is equivalent to
/// $J(J(\mathbf{a})\wedge J(\mathbf{b}))$. Thus, both meets and joins
/// reside in the same algebraic structure.
///
/// !!! example "Joining two points"
///
///     ```cpp
///         kln::point p1{x1, y1, z1};
///         kln::point p2{x2, y2, z2};
///
///         // l contains both p1 and p2.
///         kln::line l = p1 & p2;
///     ```
///
/// !!! example "Joining a line and a point"
///
///     ```cpp
///         kln::point p1{x, y, z};
///         kln::line l2{mx, my, mz, dx, dy, dz};
///
///         // p2 contains both p1 and l2.
///         kln::plane p2 = p1 & l2;
///     ```

/// \addtogroup reg
/// @{
[[nodiscard]] inline line KLN_VEC_CALL operator&(point a, point b) noexcept
{
    return !(!a ^ !b);
}

[[nodiscard]] inline plane KLN_VEC_CALL operator&(point a, line b) noexcept
{
    return !(!a ^ !b);
}

[[nodiscard]] inline plane KLN_VEC_CALL operator&(line b, point a) noexcept
{
    return a & b;
}

[[nodiscard]] inline plane KLN_VEC_CALL operator&(point a, branch b) noexcept
{
    return !(!a ^ !b);
}

[[nodiscard]] inline plane KLN_VEC_CALL operator&(branch b, point a) noexcept
{
    return a & b;
}

[[nodiscard]] inline plane KLN_VEC_CALL operator&(point a, ideal_line b) noexcept
{
    return !(!a ^ !b);
}

[[nodiscard]] inline plane KLN_VEC_CALL operator&(ideal_line b, point a) noexcept
{
    return a & b;
}

[[nodiscard]] inline dual KLN_VEC_CALL operator&(plane a, point b) noexcept
{
    return !(!a ^ !b);
}

[[nodiscard]] inline dual KLN_VEC_CALL operator&(point a, plane b) noexcept
{
    return !(!a ^ !b);
}
/// @}
} // namespace kln