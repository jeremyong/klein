#pragma once

#include "sse.hpp"

namespace kln
{
inline namespace detail
{
    // Partition memory layouts
    //     LSB --> MSB
    // p0: (e0, e1, e2, e3)
    // p1: (1, e12, e31, e23)
    // p2: (e0123, e01, e02, e03)
    // p3: (e123, e021, e013, e032)

    KLN_INLINE void KLN_VEC_CALL dot00(__m128 const& a,
                                       __m128 const& b,
                                       __m128& p1_out) noexcept
    {
        // a1 b1 + a2 b2 + a3 b3
        p1_out = _mm_dp_ps(a, b, 0b11100001);
    }

    template <bool Flip>
    KLN_INLINE void KLN_VEC_CALL dot01(__m128 const& a,
                                       __m128 const& b,
                                       __m128& p0_out) noexcept
    {
        // (a3 b2 - a2 b1) e1 +
        // (a1 b1 - a3 b3) e2 +
        // (a2 b3 - a1 b2) e3
        //
        // With flip:
        // (-a3 b2 + a2 b1) e1 +
        // (-a1 b1 + a3 b3) e2 +
        // (-a2 b3 + a1 b2) e3

        if constexpr (Flip)
        {
            p0_out = _mm_sub_ps(_mm_mul_ps(KLN_SWIZZLE(a, 1, 3, 2, 0),
                                           KLN_SWIZZLE(b, 2, 3, 1, 0)),
                                _mm_mul_ps(KLN_SWIZZLE(a, 2, 1, 3, 0),
                                           KLN_SWIZZLE(b, 3, 1, 2, 0)));
        }
        else
        {
            p0_out = _mm_sub_ps(_mm_mul_ps(KLN_SWIZZLE(a, 2, 1, 3, 0),
                                           KLN_SWIZZLE(b, 3, 1, 2, 0)),
                                _mm_mul_ps(KLN_SWIZZLE(a, 1, 3, 2, 0),
                                           KLN_SWIZZLE(b, 2, 3, 1, 0)));
        }
    }

    template <bool Flip>
    KLN_INLINE void KLN_VEC_CALL
    dot02(__m128 const& a, __m128 const& b, __m128& p0_out, __m128& p3_out)
    {
        // -(a1 b1 + a2 b2 + a3 b3) e0 +
        // a3 b0 e021 +
        // a2 b0 e013 +
        // a1 b0 e023
        //
        // With flip:
        // (a1 b1 + a2 b2 + a3 b3) e0 +
        // -a3 b0 e012 +
        // -a2 b0 e013 +
        // -a1 b0 e023

        p0_out = _mm_dp_ps(a, b, 0b11100001);
        if constexpr (!Flip)
        {
            p0_out = _mm_xor_ps(p0_out, _mm_set_ss(-0.f));
        }

        p3_out
            = _mm_mul_ps(KLN_SWIZZLE(a, 1, 2, 3, 0), KLN_SWIZZLE(b, 0, 0, 0, 0));

        if constexpr (Flip)
        {
            // Combine a mask with a negation
            p3_out = _mm_mul_ps(_mm_set_ps(-1.f, -1.f, -1.f, 0.f), p3_out);
        }
        else
        {
            // Mask low component
            p3_out = _mm_blend_ps(p3_out, _mm_setzero_ps(), 1);
        }
    }

    // The symmetric inner product on these two partitions commutes
    KLN_INLINE void KLN_VEC_CALL dot03(__m128 const& a,
                                       __m128 const& b,
                                       __m128& p1_out,
                                       __m128& p2_out)
    {
        // (a3 b2 - a2 b1) e01 +
        // (a1 b1 - a3 b3) e02 +
        // (a2 b3 - a1 b2) e03 +
        // a3 b0 e12 +
        // a2 b0 e31 +
        // a1 b0 e23

        p1_out = _mm_blend_ps(
            _mm_mul_ps(KLN_SWIZZLE(a, 1, 2, 3, 0), KLN_SWIZZLE(b, 0, 0, 0, 0)),
            _mm_setzero_ps(),
            1);

        p2_out = _mm_sub_ps(
            _mm_mul_ps(KLN_SWIZZLE(a, 2, 1, 3, 0), KLN_SWIZZLE(b, 3, 1, 2, 0)),
            _mm_mul_ps(KLN_SWIZZLE(a, 1, 3, 2, 0), KLN_SWIZZLE(b, 2, 3, 1, 0)));
    }

    KLN_INLINE void KLN_VEC_CALL dot11(__m128 const& a,
                                       __m128 const& b,
                                       __m128& p1_out)
    {
        p1_out = _mm_xor_ps(_mm_set_ss(-0.f), _mm_dp_ps(a, b, 0b11100001));
    }

    KLN_INLINE void KLN_VEC_CALL dot12(__m128 const& a,
                                       __m128 const& b,
                                       __m128& p2_out)
    {
        // -a3 b0 e01 +
        // -a2 b0 e02 +
        // -a1 b0 e03

        p2_out = _mm_mul_ps(
            _mm_set_ps(-1.f, -1.f, -1.f, 0.f),
            _mm_mul_ps(KLN_SWIZZLE(a, 1, 2, 3, 0), KLN_SWIZZLE(b, 0, 0, 0, 0)));
    }

    KLN_INLINE void KLN_VEC_CALL dot13(__m128 const& a,
                                       __m128 const& b,
                                       __m128& p0_out)
    {
        // (a1 b1 + a2 b2 + a3 b3) e0 +
        // -a3 b0 e1 +
        // -a2 b0 e2 +
        // -a1 b0 e3
        p0_out = _mm_sub_ps(
            _mm_dp_ps(a, b, 0b11110001),
            _mm_mul_ps(KLN_SWIZZLE(a, 1, 2, 3, 0), KLN_SWIZZLE(b, 0, 0, 0, 0)));
    }

    template <bool Flip>
    KLN_INLINE void KLN_VEC_CALL dot23(__m128 const& a,
                                       __m128 const& b,
                                       __m128& p0_out)
    {
        if constexpr (Flip)
        {
            // a0 b0 e0
            p0_out = _mm_blend_ps(_mm_setzero_ps(), _mm_mul_ss(a, b), 1);
        }
        else
        {
            // -a0 b0 e0
            p0_out = _mm_blend_ps(_mm_setzero_ps(),
                                  _mm_xor_ps(_mm_set_ss(-0.f), _mm_mul_ss(a, b)),
                                  1);
        }
    }

    KLN_INLINE void KLN_VEC_CALL dot33(__m128 const& a,
                                       __m128 const& b,
                                       __m128& p1_out)
    {
        // -a0 b0
        p1_out = _mm_xor_ps(_mm_set_ss(-0.f), _mm_mul_ss(a, b));
    }
} // namespace detail
} // namespace kln