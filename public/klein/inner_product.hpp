#pragma once

#include "detail/inner_product.hpp"

#include "line.hpp"
#include "motor.hpp"
#include "plane.hpp"
#include "point.hpp"
#include "rotor.hpp"

namespace kln
{
/// \defgroup dot Symmetric Inner Product
///
/// The symmetric inner product takes two arguments and contracts the lower
/// graded element to the greater graded element. If lower graded element
/// spans an index that is not contained in the higher graded element, the
/// result is annihilated. Otherwise, the result is the part of the higher
/// graded element "most unlike" the lower graded element. Thus, the
/// symmetric inner product can be thought of as a bidirectional contraction
/// operator.
///
/// There is some merit in providing both a left and right contraction
/// operator for explicitness. However, when using Klein, it's generally
/// clear what the interpretation of the symmetric inner product is with
/// respect to the projection on various entities.
///
/// !!! example "Angle between planes"
///
///     ```cpp
///         kln::plane a{x1, y1, z1, d1};
///         kln::plane b{x2, y2, z2, d2};
///
///         // Compute the cos of the angle between two planes
///         float cos_ang = a | b;
///     ```
///
/// !!! example "Line to plane through point"
///
///     ```cpp
///         kln::point a{x1, y1, z1};
///         kln::plane b{x2, y2, z2, d2};
///
///         // The line l contains a and the shortest path from a to plane b.
///         line l = a | b;
///     ```

/// \addtogroup dot
/// @{

[[nodiscard]] inline float operator|(plane a, plane b) noexcept
{
    float out;
    __m128 s;
    detail::dot00(a.p0_, b.p0_, s);
    _mm_store_ss(&out, s);
    return out;
}

[[nodiscard]] inline plane operator|(plane a, line b) noexcept
{
    plane out;
    detail::dotPL<false>(a.p0_, b.p1_, b.p2_, out.p0_);
    return out;
}

[[nodiscard]] inline plane operator|(line b, plane a) noexcept
{
    plane out;
    detail::dotPL<true>(a.p0_, b.p1_, b.p2_, out.p0_);
    return out;
}

[[nodiscard]] inline plane operator|(plane a, ideal_line b) noexcept
{
    plane out;
    detail::dotPIL<false>(a.p0_, b.p2_, out.p0_);
    return out;
}

[[nodiscard]] inline plane operator|(ideal_line b, plane a) noexcept
{
    plane out;
    detail::dotPIL<true>(a.p0_, b.p2_, out.p0_);
    return out;
}

[[nodiscard]] inline line operator|(plane a, point b) noexcept
{
    line out;
    detail::dot03(a.p0_, b.p3_, out.p1_, out.p2_);
    return out;
}

[[nodiscard]] inline line operator|(point a, plane b) noexcept
{
    return b | a;
}

[[nodiscard]] inline float operator|(line a, line b) noexcept
{
    __m128 s;
    detail::dot11(a.p1_, b.p1_, s);
    float out;
    _mm_store_ss(&out, s);
    return out;
}

[[nodiscard]] inline plane operator|(point a, line b) noexcept
{
    plane out;
    detail::dotPTL(a.p3_, b.p1_, out.p0_);
    return out;
}

[[nodiscard]] inline plane operator|(line b, point a) noexcept
{
    return a | b;
}

[[nodiscard]] inline float operator|(point a, point b) noexcept
{
    __m128 s;
    detail::dot33(a.p3_, b.p3_, s);
    float out;
    _mm_store_ss(&out, s);
    return out;
}
/// @}
} // namespace kln