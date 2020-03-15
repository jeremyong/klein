#pragma once

#include "x86_sse.hpp"

namespace kln
{
namespace detail
{
    // Partition memory layouts
    //     LSB --> MSB
    // p0: (e0, e1, e2, e3)
    // p1: (1, e23, e31, e12)
    // p2: (e0123, e01, e02, e03)
    // p3: (e123, e032, e013, e021)

    KLN_INLINE void KLN_VEC_CALL ext00(__m128 a,
                                       __m128 b,
                                       __m128& KLN_RESTRICT p1_out,
                                       __m128& KLN_RESTRICT p2_out) noexcept
    {
        // (a1 b2 - a2 b1) e12 +
        // (a2 b3 - a3 b2) e23 +
        // (a3 b1 - a1 b3) e31 +

        // (a0 b1 - a1 b0) e01 +
        // (a0 b2 - a2 b0) e02 +
        // (a0 b3 - a3 b0) e03

        p1_out = _mm_mul_ps(a, KLN_SWIZZLE(b, 1, 3, 2, 0));
        p1_out = KLN_SWIZZLE(
            _mm_sub_ps(p1_out, _mm_mul_ps(KLN_SWIZZLE(a, 1, 3, 2, 0), b)),
            1,
            3,
            2,
            0);

        p2_out = _mm_mul_ps(KLN_SWIZZLE(a, 0, 0, 0, 0), b);
        p2_out = _mm_sub_ps(p2_out, _mm_mul_ps(a, KLN_SWIZZLE(b, 0, 0, 0, 0)));

        // For both outputs above, we don't zero the lowest component because
        // we've arranged a cancelation
    }

    // Plane ^ Branch (branch is a line through the origin)
    KLN_INLINE void KLN_VEC_CALL extPB(__m128 a, __m128 b, __m128& p3_out) noexcept
    {
        // (a1 b1 + a2 b2 + a3 b3) e123 +
        // (-a0 b1) e032 +
        // (-a0 b2) e013 +
        // (-a0 b3) e021
        p3_out = _mm_mul_ps(_mm_mul_ps(KLN_SWIZZLE(a, 0, 0, 0, 1), b),
                            _mm_set_ps(-1.f, -1.f, -1.f, 0.f));

        p3_out = _mm_add_ss(p3_out, hi_dp(a, b));
    }

    // p0 ^ p2 = p2 ^ p0
    KLN_INLINE void KLN_VEC_CALL ext02(__m128 a, __m128 b, __m128& p3_out) noexcept
    {
        // (a1 b2 - a2 b1) e021
        // (a2 b3 - a3 b2) e032 +
        // (a3 b1 - a1 b3) e013 +

        p3_out = _mm_mul_ps(a, KLN_SWIZZLE(b, 1, 3, 2, 0));
        p3_out = KLN_SWIZZLE(
            _mm_sub_ps(p3_out, _mm_mul_ps(KLN_SWIZZLE(a, 1, 3, 2, 0), b)),
            1,
            3,
            2,
            0);
    }

    template <bool Flip>
    KLN_INLINE void KLN_VEC_CALL ext03(__m128 a, __m128 b, __m128& p2) noexcept
    {
        // (a0 b0 + a1 b1 + a2 b2 + a3 b3) e0123
        p2 = dp(a, b);
    }

    // p0 ^ p3 = -p3 ^ p0
    template <>
    KLN_INLINE void KLN_VEC_CALL ext03<true>(__m128 a, __m128 b, __m128& p2) noexcept
    {
        ext03<false>(a, b, p2);
        p2 = _mm_xor_ps(p2, _mm_set_ss(-0.f));
    }
    // The exterior products p2 ^ p2, p2 ^ p3, p3 ^ p2, and p3 ^ p3 all vanish
} // namespace detail
} // namespace kln