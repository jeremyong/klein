// File: geometric_product.hpp
// Purpose: Define functions of the form gpAB where A and B are partition
// indices. Each function so-defined computes the geometric product using vector
// intrinsics. The partition index determines which basis elements are present
// in each XMM component of the operand.
// A number of the computations in this file are performed symbolically in
// scripts/validation.klein

#pragma once

#include "x86_sse.hpp"

namespace kln
{
namespace detail
{
    // Partition memory layouts
    //     LSB --> MSB
    // p0: (e0, e1, e2, e3)
    // p1: (1, e12, e31, e23)
    // p2: (e0123, e01, e02, e03)
    // p3: (e123, e032, e013, e021)

    // p0: (e0, e1, e2, e3)
    // p1: (1, e23, e31, e12)
    // p2: (e0123, e01, e02, e03)
    KLN_INLINE void KLN_VEC_CALL gp00(__m128 const& a,
                                      __m128 const& b,
                                      __m128& p1_out,
                                      __m128& p2_out) noexcept
    {
        // (a1 b1 + a2 b2 + a3 b3) +
        //
        // (a2 b3 - a3 b2) e23 +
        // (a3 b1 - a1 b3) e31 +
        // (a1 b2 - a2 b1) e12 +
        //
        // (a0 b1 - a1 b0) e01 +
        // (a0 b2 - a2 b0) e02 +
        // (a0 b3 - a3 b0) e03

        p1_out
            = _mm_mul_ps(KLN_SWIZZLE(a, 1, 3, 2, 1), KLN_SWIZZLE(b, 2, 1, 3, 1));

        p1_out = _mm_sub_ps(p1_out,
                            _mm_xor_ps(_mm_set_ss(-0.f),
                                       _mm_mul_ps(KLN_SWIZZLE(a, 2, 1, 3, 2),
                                                  KLN_SWIZZLE(b, 1, 3, 2, 2))));
        // Add a3 b3 to the lowest component
        p1_out = _mm_add_ss(
            p1_out,
            _mm_mul_ps(KLN_SWIZZLE(a, 0, 0, 0, 3), KLN_SWIZZLE(b, 0, 0, 0, 3)));

        // (a0 b0, a0 b1, a0 b2, a0 b3)
        p2_out = _mm_mul_ps(KLN_SWIZZLE(a, 0, 0, 0, 0), b);

        // Sub (a0 b0, a1 b0, a2 b0, a3 b0)
        // Note that the lowest component cancels
        p2_out = _mm_sub_ps(p2_out, _mm_mul_ps(a, KLN_SWIZZLE(b, 0, 0, 0, 0)));
    }

    // p0: (e0, e1, e2, e3)
    // p1: (1, e23, e31, e12)
    // p3: (e123, e032, e013, e021)
    template <bool Flip>
    KLN_INLINE void KLN_VEC_CALL gp01(__m128 const& a,
                                      __m128 const& b,
                                      __m128& p0_out,
                                      __m128& p3_out) noexcept
    {
        // a0 b0 e0 +
        // (a1 b0 + a3 b2 - a2 b3) e1 +
        // (a2 b0 + a1 b3 - a3 b1) e2 +
        // (a3 b0 + a2 b1 - a1 b2) e3 +
        // (a1 b1 + a2 b2 + a3 b3) e123 +
        // -a0 b1 e032
        // -a0 b2 e013 +
        // -a0 b3 e021 +
        //
        // If flipped, the above turns into:
        // a0 b0 e0 +
        // (a1 b0 - a3 b2 + a2 b3) e1 +
        // (a2 b0 - a1 b3 + a3 b1) e2 +
        // (a3 b0 - a2 b1 + a1 b2) e3 +
        // (a1 b1 + a2 b2 + a3 b3) e123 +
        // -a0 b1 e032
        // -a0 b2 e013 +
        // -a0 b3 e021 +

        // To keep lanes occupied, swap e0 and e123 when accumulating sums and
        // interchange them later

        // (a1 b1, a1 b0, a2 b0, a3 b0)
        __m128 p0_tmp
            = _mm_mul_ps(KLN_SWIZZLE(a, 3, 2, 1, 1), KLN_SWIZZLE(b, 0, 0, 0, 1));

        if constexpr (Flip)
        {
            // Sub (-a2 b2, a3 b2, a1 b3, a2 b1)
            p0_tmp
                = _mm_sub_ps(p0_tmp,
                             _mm_xor_ps(_mm_mul_ps(KLN_SWIZZLE(a, 2, 1, 3, 2),
                                                   KLN_SWIZZLE(b, 1, 3, 2, 2)),
                                        _mm_set_ss(-0.f)));

            // Add (a3 b3, a2 b3, a3 b1, a1 b2)
            p0_tmp = _mm_add_ps(p0_tmp,
                                _mm_mul_ps(KLN_SWIZZLE(a, 1, 3, 2, 3),
                                           KLN_SWIZZLE(b, 2, 1, 3, 3)));
        }
        else
        {
            // Add (a2 b2, a3 b2, a1 b3, a2 b1)
            p0_tmp = _mm_add_ps(p0_tmp,
                                _mm_mul_ps(KLN_SWIZZLE(a, 2, 1, 3, 2),
                                           KLN_SWIZZLE(b, 1, 3, 2, 2)));

            // Sub (-a3 b3, a2 b3, a3 b1, a1 b2)
            p0_tmp
                = _mm_sub_ps(p0_tmp,
                             _mm_xor_ps(_mm_mul_ps(KLN_SWIZZLE(a, 1, 3, 2, 3),
                                                   KLN_SWIZZLE(b, 2, 1, 3, 3)),
                                        _mm_set_ss(-0.f)));
        }

        // (a0 b0, -a0 b1, -a0 b2, -a0 b3)
        __m128 p3_tmp = _mm_xor_ps(_mm_mul_ps(KLN_SWIZZLE(a, 0, 0, 0, 0), b),
                                   _mm_set_ps(-0.f, -0.f, -0.f, 0.f));

        // Interchange low components
        exchange_ss(p0_tmp, p3_tmp, p0_out, p3_out);
    }

    // p0: (e0, e1, e2, e3)
    // p2: (e0123, e01, e02, e03)
    // p3: (e123, e032, e013, e021)
    template <bool Flip>
    KLN_INLINE void KLN_VEC_CALL gp02(__m128 const& a,
                                      __m128 const& b,
                                      __m128& p0_out,
                                      __m128& p3_out) noexcept
    {
        // -(a1 b1 + a2 b2 + a3 b3) e0 +
        // (a2 b3 + a1 b0 - a3 b2) e032
        // (a3 b1 + a2 b0 - a1 b3) e013 +
        // (a1 b2 + a3 b0 - a2 b1) e021 +
        //
        // With a flip:
        // (a1 b1 + a2 b2 + a3 b3) e0 +
        // (a2 b3 - a1 b0 - a3 b2) e032
        // (a3 b1 - a2 b0 - a1 b3) e013 +
        // (a1 b2 - a3 b0 - a2 b1) e021 +

        __m128 p3_tmp
            = _mm_mul_ps(KLN_SWIZZLE(a, 1, 3, 2, 1), KLN_SWIZZLE(b, 2, 1, 3, 1));

        if constexpr (Flip)
        {
            // Sub (-a2 b2, a1 b0, a2 b3, a3 b0)
            p3_tmp
                = _mm_sub_ps(p3_tmp,
                             _mm_xor_ps(_mm_mul_ps(KLN_SWIZZLE(a, 3, 2, 1, 2),
                                                   KLN_SWIZZLE(b, 0, 0, 0, 2)),
                                        _mm_set_ss(-0.f)));
        }
        else
        {
            // Add (a2 b2, a1 b0, a1 b3, a3 b0)
            p3_tmp = _mm_add_ps(p3_tmp,
                                _mm_mul_ps(KLN_SWIZZLE(a, 3, 2, 1, 2),
                                           KLN_SWIZZLE(b, 0, 0, 0, 2)));
        }

        // Sub (-a3 b3, a3 b2, a1 b3, a2 b1)
        p3_tmp = _mm_sub_ps(p3_tmp,
                            _mm_xor_ps(_mm_mul_ps(KLN_SWIZZLE(a, 2, 1, 3, 3),
                                                  KLN_SWIZZLE(b, 1, 3, 2, 3)),
                                       _mm_set_ss(-0.f)));

        if constexpr (!Flip)
        {
            // Negate low component
            p3_tmp = _mm_xor_ps(p3_tmp, _mm_set_ss(-0.f));
        }

#ifdef KLEIN_SSE_4_1
        // Take the low component
        p0_out = _mm_blend_ps(_mm_setzero_ps(), p3_tmp, 1);
        // Mask the low component
        p3_out = _mm_blend_ps(p3_tmp, _mm_setzero_ps(), 1);
#else
        p0_out = _mm_and_ps(p3_tmp, _mm_castsi128_ps(_mm_set_epi32(0, 0, 0, -1)));
        p3_out
            = _mm_and_ps(p3_tmp, _mm_castsi128_ps(_mm_set_epi32(-1, -1, -1, 0)));
#endif
    }

    // p0: (e0, e1, e2, e3)
    // p3: (e123, e032, e013, e021)
    // p1: (1, e12, e31, e23)
    // p2: (e0123, e01, e02, e03)
    template <bool Flip>
    KLN_INLINE void KLN_VEC_CALL gp03(__m128 const& a,
                                      __m128 const& b,
                                      __m128& p1_out,
                                      __m128& p2_out) noexcept
    {
        // a1 b0 e23 +
        // a2 b0 e31 +
        // a3 b0 e12 +
        // (a0 b0 + a1 b1 + a2 b2 + a3 b3) e0123 +
        // (a3 b2 - a2 b3) e01 +
        // (a1 b3 - a3 b1) e02 +
        // (a2 b1 - a1 b2) e03
        //
        // With flip:
        //
        // a1 b0 e23 +
        // a2 b0 e31 +
        // a3 b0 e12 +
        // -(a0 b0 + a1 b1 + a2 b2 + a3 b3) e0123 +
        // (a3 b2 - a2 b3) e01 +
        // (a1 b3 - a3 b1) e02 +
        // (a2 b1 - a1 b2) e03

        p1_out = _mm_mul_ps(a, KLN_SWIZZLE(b, 0, 0, 0, 0));
#ifdef KLEIN_SSE_4_1
        p1_out = _mm_blend_ps(p1_out, _mm_setzero_ps(), 1);
#else
        p1_out
            = _mm_and_ps(p1_out, _mm_castsi128_ps(_mm_set_epi32(-1, -1, -1, 0)));
#endif

        // (_, a3 b2, a1 b3, a2 b1)
        p2_out
            = _mm_mul_ps(KLN_SWIZZLE(a, 2, 1, 3, 0), KLN_SWIZZLE(b, 1, 3, 2, 0));
        p2_out = _mm_sub_ps(
            p2_out,
            _mm_mul_ps(KLN_SWIZZLE(a, 1, 3, 2, 0), KLN_SWIZZLE(b, 2, 1, 3, 0)));

        // Compute a0 b0 + a1 b1 + a2 b2 + a3 b3 and store it in the low
        // component
        __m128 tmp = dp(a, b);

        if constexpr (Flip)
        {
            tmp = _mm_xor_ps(tmp, _mm_set_ss(-0.f));
        }

        p2_out = _mm_add_ps(p2_out, tmp);
    }

    // p1: (1, e23, e31, e12)
    inline void KLN_VEC_CALL gp11(__m128 const& a,
                                  __m128 const& b,
                                  __m128& p1_out) noexcept
    {
        // (a0 b0 - a1 b1 - a2 b2 - a3 b3) +
        // (a0 b1 - a2 b3 + a1 b0 + a3 b2)*e23
        // (a0 b2 - a3 b1 + a2 b0 + a1 b3)*e31
        // (a0 b3 - a1 b2 + a3 b0 + a2 b1)*e12

        // We use abcd to refer to the slots to avoid conflating bivector/scalar
        // coefficients with cartesian coordinates

        // In general, we can get rid of at most one swizzle
        p1_out = _mm_mul_ps(KLN_SWIZZLE(a, 0, 0, 0, 0), b);

        p1_out = _mm_sub_ps(
            p1_out,
            _mm_mul_ps(KLN_SWIZZLE(a, 1, 3, 2, 1), KLN_SWIZZLE(b, 2, 1, 3, 1)));

        // In a separate register, accumulate the later components so we can
        // negate the lower single-precision element with a single instruction
        __m128 tmp
            = _mm_mul_ps(KLN_SWIZZLE(a, 3, 2, 1, 2), KLN_SWIZZLE(b, 0, 0, 0, 2));

        tmp = _mm_add_ps(
            tmp,
            _mm_mul_ps(KLN_SWIZZLE(a, 2, 1, 3, 3), KLN_SWIZZLE(b, 1, 3, 2, 3)));

        tmp = _mm_xor_ps(tmp, _mm_set_ss(-0.f));

        p1_out = _mm_add_ps(p1_out, tmp);
    }

    // p1: (1, e23, e31, e12)
    // p2: (e0123, e01, e02, e03)
    template <bool Flip>
    inline void KLN_VEC_CALL gp12(__m128 const& a,
                                  __m128 const& b,
                                  __m128& p2_out) noexcept
    {
        // (a0 b0 + a1 b1 + a2 b2 + a3 b3) e0123 +
        // (a0 b1 + a3 b2 - a1 b0 - a2 b3) e01 +
        // (a0 b2 + a1 b3 - a2 b0 - a3 b1) e02 +
        // (a0 b3 + a2 b1 - a3 b0 - a1 b2) e03

        // With flip:
        // (a0 b0 + a1 b1 + a2 b2 + a3 b3) e0123 +
        // (-a0 b1 + a3 b2 + a1 b0 - a2 b3) e01 +
        // (-a0 b2 + a1 b3 + a2 b0 - a3 b1) e02 +
        // (-a0 b3 + a2 b1 + a3 b0 - a1 b2) e03

        p2_out
            = _mm_mul_ps(KLN_SWIZZLE(a, 2, 1, 3, 1), KLN_SWIZZLE(b, 1, 3, 2, 1));

        __m128 tmp
            = _mm_mul_ps(KLN_SWIZZLE(a, 1, 3, 2, 3), KLN_SWIZZLE(b, 2, 1, 3, 3));

        if constexpr (Flip)
        {
            p2_out = _mm_add_ps(p2_out,
                                _mm_mul_ps(KLN_SWIZZLE(a, 3, 2, 1, 2),
                                           KLN_SWIZZLE(b, 0, 0, 0, 2)));
            tmp    = _mm_add_ps(tmp, _mm_mul_ps(KLN_SWIZZLE(a, 0, 0, 0, 0), b));
        }
        else
        {
            p2_out
                = _mm_add_ps(p2_out, _mm_mul_ps(KLN_SWIZZLE(a, 0, 0, 0, 0), b));
            tmp = _mm_add_ps(tmp,
                             _mm_mul_ps(KLN_SWIZZLE(a, 3, 2, 1, 2),
                                        KLN_SWIZZLE(b, 0, 0, 0, 2)));
        }

        p2_out = _mm_sub_ps(p2_out, _mm_xor_ps(tmp, _mm_set_ss(-0.f)));
    }

    // p1: (1, e23, e31, e12)
    // p3: (e123, e032, e013, e021)
    // Returns p0 and p3
    // p0: (e0, e1, e2, e3)
    // p3: (e123, e021, e013, e021)
    template <bool Flip>
    KLN_INLINE void KLN_VEC_CALL gp13(__m128 const& a,
                                      __m128 const& b,
                                      __m128& p0_out,
                                      __m128& p3_out) noexcept
    {
        // a0 b0 e123 +
        // -a1 b0 e1 +
        // -a2 b0 e2 +
        // -a3 b0 e3 +
        // (a1 b1 + a2 b2 + a3 b3) e0 +
        // (a0 b1 + a3 b2 - a2 b3) e032 +
        // (a0 b2 + a1 b3 - a3 b1) e013 +
        // (a0 b3 + a2 b1 - a1 b2) e021
        //
        // With flip:
        //
        // a0 b0 e123 +
        // -a1 b0 e1 +
        // -a2 b0 e2 +
        // -a3 b0 e3 +
        // (a1 b1 + a2 b2 + a3 b3) e0 +
        // (a0 b1 - a3 b2 + a2 b3) e032 +
        // (a0 b2 - a1 b3 + a3 b1) e013 +
        // (a0 b3 - a2 b1 + a1 b2) e021

        // As with other partition combinations, we exchange two components to
        // increase lane occupancy and perform two blends to read the results at
        // the end.

        __m128 p0_tmp = _mm_xor_ps(_mm_mul_ps(a, KLN_SWIZZLE(b, 0, 0, 0, 0)),
                                   _mm_set_ps(-0.f, -0.f, -0.f, 0.f));

        __m128 p3_tmp
            = _mm_mul_ps(KLN_SWIZZLE(a, 0, 0, 0, 1), KLN_SWIZZLE(b, 3, 2, 1, 1));

        if constexpr (Flip)
        {
            p3_tmp
                = _mm_sub_ps(p3_tmp,
                             _mm_xor_ps(_mm_mul_ps(KLN_SWIZZLE(a, 2, 1, 3, 2),
                                                   KLN_SWIZZLE(b, 1, 3, 2, 2)),
                                        _mm_set_ss(-0.f)));
            p3_tmp = _mm_add_ps(p3_tmp,
                                _mm_mul_ps(KLN_SWIZZLE(a, 1, 3, 2, 3),
                                           KLN_SWIZZLE(b, 2, 1, 3, 3)));
        }
        else
        {
            p3_tmp
                = _mm_sub_ps(p3_tmp,
                             _mm_xor_ps(_mm_mul_ps(KLN_SWIZZLE(a, 1, 3, 2, 3),
                                                   KLN_SWIZZLE(b, 2, 1, 3, 3)),
                                        _mm_set_ss(-0.f)));
            p3_tmp = _mm_add_ps(p3_tmp,
                                _mm_mul_ps(KLN_SWIZZLE(a, 2, 1, 3, 2),
                                           KLN_SWIZZLE(b, 1, 3, 2, 2)));
        }

        // Exchange low components
        exchange_ss(p0_tmp, p3_tmp, p0_out, p3_out);
    }

    // p2: (e0123, e01, e02, e03)
    // p3: (e123, e032, e013, e021)
    // Returns p0 and p3
    // p0: (e0, e1, e2, e3)
    // Note that this specific product is somewhat awkward as e1, e2, and e3 are
    // unused
    template <bool Flip>
    KLN_INLINE void KLN_VEC_CALL gp23(__m128 const& a,
                                      __m128 const& b,
                                      __m128& p0_out,
                                      __m128& p3_out) noexcept
    {
        // -a0 b0 e0 +
        // -a1 b0 e032
        // -a2 b0 e013 +
        // -a3 b0 e021 +
        //
        // With the flip:
        // a0 b0 e0 +
        // a1 b0 e032
        // a2 b0 e013 +
        // a3 b0 e021 +

        __m128 tmp = _mm_mul_ps(a, KLN_SWIZZLE(b, 0, 0, 0, 0));
        if constexpr (!Flip)
        {
            // Negate tmp
            tmp = _mm_xor_ps(tmp, _mm_set1_ps(-0.f));
        }
#ifdef KLEIN_SSE_4_1
        p0_out = _mm_blend_ps(_mm_setzero_ps(), tmp, 1);
        p3_out = _mm_blend_ps(tmp, _mm_setzero_ps(), 1);
#else
        p0_out = _mm_and_ps(tmp, _mm_castsi128_ps(_mm_set_epi32(0, 0, 0, -1)));
        p3_out = _mm_and_ps(tmp, _mm_castsi128_ps(_mm_set_epi32(-1, -1, -1, 0)));
#endif
    }

    // p3: (e123, e021, e013, e032)
    // Returns p1 and p2
    // p1: (1, e12, e31, e23)
    // p2: (e0123, e01, e02, e03)
    KLN_INLINE void KLN_VEC_CALL gp33(__m128 const& a,
                                      __m128 const& b,
                                      __m128& p1_out,
                                      __m128& p2_out) noexcept
    {
        // (-a0 b0) +
        // (-a0 b1 + a1 b0) e01 +
        // (-a0 b2 + a2 b0) e02 +
        // (-a0 b3 + a3 b0) e03

        __m128 tmp = _mm_mul_ps(KLN_SWIZZLE(a, 0, 0, 0, 0), b);
        tmp        = _mm_mul_ps(tmp, _mm_set_ps(-1.f, -1.f, -1.f, -2.f));
        tmp        = _mm_add_ps(tmp, _mm_mul_ps(a, KLN_SWIZZLE(b, 0, 0, 0, 0)));

#ifdef KLEIN_SSE_4_1
        p1_out = _mm_blend_ps(_mm_setzero_ps(), tmp, 1);
        p2_out = _mm_blend_ps(tmp, _mm_setzero_ps(), 1);
#else
        p1_out = _mm_and_ps(tmp, _mm_castsi128_ps(_mm_set_epi32(0, 0, 0, -1)));
        p2_out = _mm_and_ps(tmp, _mm_castsi128_ps(_mm_set_epi32(-1, -1, -1, 0)));
#endif
    }

    // Optimized motor * motor operation
    KLN_INLINE void KLN_VEC_CALL gpMM(__m128 const* m1,
                                      __m128 const* m2,
                                      __m128* out) noexcept
    {
        // (a0 c0 - a1 c1 - a2 c2 - a3 c3) +
        // (a0 c1 + a3 c2 + a1 c0 - a2 c3) e23 +
        // (a0 c2 + a1 c3 + a2 c0 - a3 c1) e31 +
        // (a0 c3 + a2 c1 + a3 c0 - a1 c2) e12 +
        //
        // (a0 d0 + b0 c0 + a1 d1 + b1 c1 + a2 d2 + a3 d3 + b2 c2 + b3 c3)
        //  e0123 +
        // (a0 d1 + b1 c0 + a3 d2 + b3 c2 - a1 d0 - a2 d3 - b0 c1 - b2 c3)
        //  e01 +
        // (a0 d2 + b2 c0 + a1 d3 + b1 c3 - a2 d0 - a3 d1 - b0 c2 - b3 c1)
        //  e02 +
        // (a0 d3 + b3 c0 + a2 d1 + b2 c1 - a3 d0 - a1 d2 - b0 c3 - b1 c2)
        //  e03
        __m128 const& a = *m1;
        __m128 const& b = *(m1 + 1);
        __m128 const& c = *m2;
        __m128 const& d = *(m2 + 1);

        __m128& e = *out;
        __m128& f = *(out + 1);

        __m128 a_xxxx = KLN_SWIZZLE(a, 0, 0, 0, 0);
        __m128 a_zyzw = KLN_SWIZZLE(a, 3, 2, 1, 2);
        __m128 a_ywyz = KLN_SWIZZLE(a, 2, 1, 3, 1);
        __m128 a_wzwy = KLN_SWIZZLE(a, 1, 3, 2, 3);
        __m128 c_wwyz = KLN_SWIZZLE(c, 2, 1, 3, 3);
        __m128 c_yzwy = KLN_SWIZZLE(c, 1, 3, 2, 1);
        __m128 s_flip = _mm_set_ss(-0.f);

        e        = _mm_mul_ps(a_xxxx, c);
        __m128 t = _mm_mul_ps(a_ywyz, c_yzwy);
        t = _mm_add_ps(t, _mm_mul_ps(a_zyzw, KLN_SWIZZLE(c, 0, 0, 0, 2)));
        t = _mm_xor_ps(t, s_flip);
        e = _mm_add_ps(e, t);
        e = _mm_sub_ps(e, _mm_mul_ps(a_wzwy, c_wwyz));

        f = _mm_mul_ps(a_xxxx, d);
        f = _mm_add_ps(f, _mm_mul_ps(b, KLN_SWIZZLE(c, 0, 0, 0, 0)));
        f = _mm_add_ps(f, _mm_mul_ps(a_ywyz, KLN_SWIZZLE(d, 1, 3, 2, 1)));
        f = _mm_add_ps(f, _mm_mul_ps(KLN_SWIZZLE(b, 2, 1, 3, 1), c_yzwy));
        t = _mm_mul_ps(a_zyzw, KLN_SWIZZLE(d, 0, 0, 0, 2));
        t = _mm_add_ps(t, _mm_mul_ps(a_wzwy, KLN_SWIZZLE(d, 2, 1, 3, 3)));
        t = _mm_add_ps(
            t,
            _mm_mul_ps(KLN_SWIZZLE(b, 0, 0, 0, 2), KLN_SWIZZLE(c, 3, 2, 1, 2)));
        t = _mm_add_ps(t, _mm_mul_ps(KLN_SWIZZLE(b, 1, 3, 2, 3), c_wwyz));
        t = _mm_xor_ps(t, s_flip);
        f = _mm_sub_ps(f, t);
    }
} // namespace detail
} // namespace kln