#pragma once

#include "detail/exterior_product.hpp"

#include "dual.hpp"
#include "line.hpp"
#include "plane.hpp"
#include "point.hpp"

namespace kln
{
/// \defgroup ext Exterior Product
///
/// (meet.hpp)
///
/// The exterior product between two basis elements extinguishes if the two
/// operands share any common index. Otherwise, the element produced is
/// equivalent to the union of the subspaces. A sign flip is introduced if
/// the concatenation of the element indices is an odd permutation of the
/// cyclic basis representation. The exterior product extends to general
/// multivectors by linearity.
///
/// !!! example "Meeting two planes"
///
///     ```cpp
///         kln::plane p1{x1, y1, z1, d1};
///         kln::plane p2{x2, y2, z2, d2};
///
///         // l lies at the intersection of p1 and p2.
///         kln::line l = p1 ^ p2;
///     ```
///
/// !!! example "Meeting a line and a plane"
///
///     ```cpp
///         kln::plane p1{x, y, z, d};
///         kln::line l2{mx, my, mz, dx, dy, dz};
///
///         // p2 lies at the intersection of p1 and l2.
///         kln::point p2 = p1 ^ l2;
///     ```

/// \addtogroup ext
/// @{

[[nodiscard]] inline line KLN_VEC_CALL operator^(plane a, plane b) noexcept
{
    line out;
    detail::ext00(a.p0_, b.p0_, out.p1_, out.p2_);
    return out;
}

[[nodiscard]] inline point KLN_VEC_CALL operator^(plane a, branch b) noexcept
{
    point out;
    detail::extPB(a.p0_, b.p1_, out.p3_);
    return out;
}

[[nodiscard]] inline point KLN_VEC_CALL operator^(branch b, plane a) noexcept
{
    return a ^ b;
}

[[nodiscard]] inline point KLN_VEC_CALL operator^(plane a, ideal_line b) noexcept
{
    point out;
    detail::ext02(a.p0_, b.p2_, out.p3_);
    return out;
}

[[nodiscard]] inline point KLN_VEC_CALL operator^(ideal_line b, plane a) noexcept
{
    return a ^ b;
}

[[nodiscard]] inline point KLN_VEC_CALL operator^(plane a, line b) noexcept
{
    point out;
    detail::extPB(a.p0_, b.p1_, out.p3_);
    __m128 tmp;
    detail::ext02(a.p0_, b.p2_, tmp);
    out.p3_ = _mm_add_ps(tmp, out.p3_);
    return out;
}

[[nodiscard]] inline point KLN_VEC_CALL operator^(line b, plane a) noexcept
{
    return a ^ b;
}

[[nodiscard]] inline dual KLN_VEC_CALL operator^(plane a, point b) noexcept
{
    __m128 tmp;
    detail::ext03<false>(a.p0_, b.p3_, tmp);
    dual out{0.f};
    _mm_store_ss(&out.q, tmp);
    return out;
}

[[nodiscard]] inline dual KLN_VEC_CALL operator^(point b, plane a) noexcept
{
    __m128 tmp;
    detail::ext03<true>(a.p0_, b.p3_, tmp);
    dual out{0.f};
    _mm_store_ss(&out.q, tmp);
    return out;
}

[[nodiscard]] inline dual KLN_VEC_CALL operator^(branch a, ideal_line b) noexcept
{
    __m128 dp = detail::hi_dp_ss(a.p1_, b.p2_);
    float out;
    _mm_store_ss(&out, dp);
    return {0.f, out};
}

[[nodiscard]] inline dual KLN_VEC_CALL operator^(ideal_line b, branch a) noexcept
{
    return a ^ b;
}

[[nodiscard]] inline dual KLN_VEC_CALL operator^(line a, line b) noexcept
{
    __m128 dp = detail::hi_dp_ss(a.p1_, b.p2_);
    float out[2];
    _mm_store_ss(out, dp);
    dp = detail::hi_dp_ss(b.p1_, a.p2_);
    _mm_store_ss(out + 1, dp);
    return {0.f, out[0] + out[1]};
}

[[nodiscard]] inline dual KLN_VEC_CALL operator^(line a, ideal_line b) noexcept
{
    return branch{a.p1_} ^ b;
}

[[nodiscard]] inline dual KLN_VEC_CALL operator^(ideal_line b, line a) noexcept
{
    return a ^ b;
}

[[nodiscard]] inline dual KLN_VEC_CALL operator^(line a, branch b) noexcept
{
    return ideal_line{a.p2_} ^ b;
}

[[nodiscard]] inline dual KLN_VEC_CALL operator^(branch b, line a) noexcept
{
    return a ^ b;
}
/// @}
} // namespace kln