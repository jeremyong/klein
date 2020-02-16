#pragma once

#include "sse.hpp"

namespace kln
{
inline namespace detail
{
    // Partition memory layouts
    //     LSB --> MSB
    // p0: (e3, e2, e1, e0)
    // p1: (1, e12, e31, e23)
    // p2: (e0123, e01, e02, e03)
    // p3: (e123, e021, e013, e032)

    inline void KLN_VEC_CALL ext00(__m128 const& a,
                                   __m128 const& b,
                                   __m128& p1_out,
                                   __m128& p2_out) noexcept
    {
        // (a2 b1 - a1 b2) e12 +
        // (a0 b2 - a2 b0) e31 +
        // (a1 b0 - a0 b1) e23 +
        // (a3 b2 - a2 b3) e01 +
        // (a3 b1 - a1 b3) e02 +
        // (a3 b0 - a0 b3) e03

        p1_out
            = _mm_mul_ps(KLN_SWIZZLE(a, 1, 0, 2, 3), KLN_SWIZZLE(b, 0, 2, 1, 3));
        p1_out = _mm_sub_ps(
            p1_out,
            _mm_mul_ps(KLN_SWIZZLE(a, 0, 2, 1, 3), KLN_SWIZZLE(b, 1, 0, 2, 3)));
        p1_out = _mm_blend_ps(p1_out, _mm_setzero_ps(), 0b0001);

        p2_out
            = _mm_mul_ps(KLN_SWIZZLE(a, 3, 3, 3, 0), KLN_SWIZZLE(b, 0, 1, 2, 0));
        p2_out = _mm_sub_ps(
            p2_out,
            _mm_mul_ps(KLN_SWIZZLE(a, 0, 1, 2, 3), KLN_SWIZZLE(b, 3, 3, 3, 3)));
        p2_out = _mm_blend_ps(p2_out, _mm_setzero_ps(), 0b0001);
    }

    // NOTE: p1 ^ p0 and p0 ^ p1 produce identical results
    // p0: (e3, e2, e1, e0)
    // p3: (e123, e021, e013, e032)
    inline void KLN_VEC_CALL ext01(__m128 const& a,
                                   __m128 const& b,
                                   __m128& p0_out,
                                   __m128& p3_out) noexcept
    {
        // (a0 b0) e3 +
        // (a1 b0) e2 +
        // (a2 b0) e1 +
        // (a3 b0) e0 +
        // (a0 b1 + a1 b2 + a2 b3) e123 +
        // (-a3 b1) e021 +
        // (-a3 b2) e013 +
        // (-a3 b3) e032

        p0_out = _mm_mul_ps(a, KLN_SWIZZLE(b, 0, 0, 0, 0));

        p3_out
            = _mm_mul_ps(KLN_SWIZZLE(a, 3, 3, 3, 0), KLN_SWIZZLE(b, 3, 2, 1, 1));

        p3_out = _mm_xor_ps(
            _mm_set1_ps(-0.f),
            _mm_add_ss(
                p3_out, _mm_dp_ps(a, KLN_SWIZZLE(b, 0, 3, 2, 1), 0b01100001)));
    }

    // p0 ^ p2 = p2 ^ p0
    inline void KLN_VEC_CALL ext02(__m128 const& a,
                                   __m128 const& b,
                                   __m128& p3_out) noexcept
    {
        // (a2 b2 - a1 b1) e021 +
        // (a0 b1 - a2 b3) e013 +
        // (a1 b3 - a0 b2) e032

        p3_out
            = _mm_mul_ps(KLN_SWIZZLE(a, 1, 0, 2, 3), KLN_SWIZZLE(b, 3, 1, 2, 0));
        p3_out = _mm_sub_ps(
            p3_out,
            _mm_mul_ps(KLN_SWIZZLE(a, 0, 2, 1, 3), KLN_SWIZZLE(b, 2, 3, 1, 0)));
        p3_out = _mm_blend_ps(p3_out, _mm_setzero_ps(), 0b0001);
    }

    // p0 ^ p3 = -p3 ^ p0
    template <bool Flip = false>
    inline void KLN_VEC_CALL ext03(__m128 const& a,
                                   __m128 const& b,
                                   __m128& p2_out) noexcept
    {
        // (a0 b1 + a1 b2 + a2 b3 + a3 b0) e0123
        p2_out = _mm_dp_ps(a, KLN_SWIZZLE(b, 0, 3, 2, 1), 0b11110001);
        if constexpr (Flip)
        {
            p2_out = _mm_xor_ps(p2_out, _mm_set_ps(0, 0, 0, -0.f));
        }
    }

    inline void KLN_VEC_CALL ext11(__m128 const& a,
                                   __m128 const& b,
                                   __m128& p1_out) noexcept
    {
        // a0 b0 +
        // (a0 b1 + a1 b0) e12 +
        // (a0 b2 + a2 b0) e31 +
        // (a0 b3 + a3 b0) e23

        p1_out = _mm_mul_ps(KLN_SWIZZLE(a, 0, 0, 0, 0), b);
        p1_out = _mm_add_ps(p1_out, _mm_mul_ps(a, KLN_SWIZZLE(b, 0, 0, 0, 0)));
        p1_out = _mm_mul_ss(p1_out, _mm_set_ss(0.5f));
    }

    // p1 ^ p2 = p2 ^ p1
    inline void KLN_VEC_CALL ext12(__m128 const& a,
                                   __m128 const& b,
                                   __m128& p2_out) noexcept
    {
        // (a0 b0 + a1 b3 + a2 b2 + b3 b1) e0123 +
        // (a0 b1) e01 +
        // (a0 b2) e02 +
        // (a0 b3) e03
        p2_out = _mm_mul_ps(KLN_SWIZZLE(a, 0, 0, 0, 0), b);
        p2_out = _mm_add_ps(
            p2_out, _mm_dp_ps(a, KLN_SWIZZLE(b, 1, 2, 3, 0), 0b11100001));
    }

    // p1 ^ p3 = p3 ^ p1
    inline void KLN_VEC_CALL ext13(__m128 const& a,
                                   __m128 const& b,
                                   __m128& p3_out) noexcept
    {
        // a0 b0 e123 +
        // a0 b1 e021 +
        // a0 b2 e013 +
        // a0 b3 e032
        p3_out = _mm_mul_ps(KLN_SWIZZLE(a, 0, 0, 0, 0), b);
    }

    // The exterior products p2 ^ p2, p2 ^ p3, p3 ^ p2, and p3 ^ p3 all vanish
} // namespace detail
} // namespace kln