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

    KLN_INLINE void KLN_VEC_CALL dot00(__m128 a, __m128 b, __m128& p1_out) noexcept
    {
        // a1 b1 + a2 b2 + a3 b3
        p1_out = hi_dp(a, b);
    }

    // The symmetric inner product on these two partitions commutes
    KLN_INLINE void KLN_VEC_CALL dot03(__m128 a,
                                       __m128 b,
                                       __m128& KLN_RESTRICT p1_out,
                                       __m128& KLN_RESTRICT p2_out) noexcept
    {
        // (a2 b1 - a1 b2) e03 +
        // (a3 b2 - a2 b3) e01 +
        // (a1 b3 - a3 b1) e02 +
        // a1 b0 e23 +
        // a2 b0 e31 +
        // a3 b0 e12

        p1_out = _mm_mul_ps(a, KLN_SWIZZLE(b, 0, 0, 0, 0));
#ifdef KLEIN_SSE_4_1
        p1_out = _mm_blend_ps(p1_out, _mm_setzero_ps(), 1);
#else
        p1_out
            = _mm_and_ps(p1_out, _mm_castsi128_ps(_mm_set_epi32(-1, -1, -1, 0)));
#endif

        p2_out
            = KLN_SWIZZLE(_mm_sub_ps(_mm_mul_ps(KLN_SWIZZLE(a, 1, 3, 2, 0), b),
                                     _mm_mul_ps(a, KLN_SWIZZLE(b, 1, 3, 2, 0))),
                          1,
                          3,
                          2,
                          0);
    }

    KLN_INLINE void KLN_VEC_CALL dot11(__m128 a, __m128 b, __m128& p1_out) noexcept
    {
        p1_out = _mm_xor_ps(_mm_set_ss(-0.f), hi_dp_ss(a, b));
    }

    KLN_INLINE void KLN_VEC_CALL dot33(__m128 a, __m128 b, __m128& p1_out) noexcept
    {
        // -a0 b0
        p1_out = _mm_mul_ps(_mm_set_ss(-1.f), _mm_mul_ss(a, b));
    }

    // Point | Line
    KLN_INLINE void KLN_VEC_CALL dotPTL(__m128 a, __m128 b, __m128& p0) noexcept
    {
        // (a1 b1 + a2 b2 + a3 b3) e0 +
        // -a0 b1 e1 +
        // -a0 b2 e2 +
        // -a0 b3 e3

        __m128 dp = hi_dp_ss(a, b);
        p0        = _mm_mul_ps(KLN_SWIZZLE(a, 0, 0, 0, 0), b);
        p0        = _mm_xor_ps(p0, _mm_set_ps(-0.f, -0.f, -0.f, 0.f));
#ifdef KLEIN_SSE_4_1
        p0 = _mm_blend_ps(p0, dp, 1);
#else
        p0 = _mm_add_ss(p0, dp);
#endif
    }

    // Plane | Ideal Line
    template <bool Flip>
    KLN_INLINE void KLN_VEC_CALL dotPIL(__m128 a, __m128 c, __m128& p0) noexcept
    {
        p0 = hi_dp(a, c);
    }

    template <>
    KLN_INLINE void KLN_VEC_CALL dotPIL<false>(__m128 a, __m128 c, __m128& p0) noexcept
    {
        dotPIL<true>(a, c, p0);
        p0 = _mm_xor_ps(p0, _mm_set_ss(-0.f));
    }

    // Plane | Line
    template <bool Flip>
    KLN_INLINE void KLN_VEC_CALL dotPL(__m128 a, __m128 b, __m128 c, __m128& p0) noexcept
    {
        // -(a1 c1 + a2 c2 + a3 c3) e0 +
        // (a2 b1 - a1 b2) e3
        // (a3 b2 - a2 b3) e1 +
        // (a1 b3 - a3 b1) e2 +

        p0 = _mm_mul_ps(KLN_SWIZZLE(a, 1, 3, 2, 0), b);
        p0 = _mm_sub_ps(p0, _mm_mul_ps(a, KLN_SWIZZLE(b, 1, 3, 2, 0)));
        p0 = _mm_sub_ss(KLN_SWIZZLE(p0, 1, 3, 2, 0), hi_dp_ss(a, c));
    }

    template <>
    KLN_INLINE void KLN_VEC_CALL
    dotPL<true>(__m128 a, __m128 b, __m128 c, __m128& p0) noexcept
    {
        // (a1 c1 + a2 c2 + a3 c3) e0 +
        // (a1 b2 - a2 b1) e3
        // (a2 b3 - a3 b2) e1 +
        // (a3 b1 - a1 b3) e2 +

        p0 = _mm_mul_ps(a, KLN_SWIZZLE(b, 1, 3, 2, 0));
        p0 = _mm_sub_ps(p0, _mm_mul_ps(KLN_SWIZZLE(a, 1, 3, 2, 0), b));
        p0 = _mm_add_ss(KLN_SWIZZLE(p0, 1, 3, 2, 0), hi_dp_ss(a, c));
    }
} // namespace detail
} // namespace kln