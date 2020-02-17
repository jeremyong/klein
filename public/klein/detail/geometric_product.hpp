// File: geometric_product.hpp
// Purpose: Define functions of the form gpAB where A and B are partition
// indices. Each function so-defined computes the geometric product using vector
// intrinsics. The partition index determines which basis elements are present
// in each XMM component of the operand.
// A number of the computations in this file are performed symbolically in
// scripts/validation.klein

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

    // p0: (e0, e1, e2, e3)
    // p1: (1, e12, e31, e23)
    // p2: (e0123, e01, e02, e03)
    KLN_INLINE void KLN_VEC_CALL gp00(__m128 const& a,
                                  __m128 const& b,
                                  __m128& p1_out,
                                  __m128& p2_out) noexcept
    {
        // (a1 b1 + a2 b2 + a3 b3) +
        // (a1 b2 - a2 b1) e12 +
        // (a3 b1 - a1 b3) e31 +
        // (a2 b3 - a3 b2) e23 +
        // (a0 b1 - a1 b0) e01 +
        // (a0 b2 - a2 b0) e02 +
        // (a0 b3 - a3 b0) e03

        // (a1 b1, a1 b2, a3 b1, a2 b3)
        p1_out
            = _mm_mul_ps(KLN_SWIZZLE(a, 2, 3, 1, 1), KLN_SWIZZLE(b, 3, 1, 2, 1));

        // Sub (-a2 b2, a2 b1, a1 b3, a3 b2)
        p1_out = _mm_sub_ps(p1_out,
                            _mm_xor_ps(_mm_set_ss(-0.f),
                                       _mm_mul_ps(KLN_SWIZZLE(a, 3, 1, 2, 2),
                                                  KLN_SWIZZLE(b, 2, 3, 1, 2))));
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
    // p1: (1, e12, e31, e23)
    // p3: (e123, e021, e013, e032)
    template <bool Flip>
    KLN_INLINE void KLN_VEC_CALL gp01(__m128 const& a,
                                  __m128 const& b,
                                  __m128& p0_out,
                                  __m128& p3_out) noexcept
    {
        // a0 b0 e0 +
        // (a1 b0 + a3 b2 - a2 b1) e1 +
        // (a2 b0 + a1 b1 - a3 b3) e2 +
        // (a3 b0 + a2 b3 - a1 b2) e3 +
        // (a1 b3 + a2 b2 + a3 b1) e123 +
        // -a0 b1 e021 +
        // -a0 b2 e013 +
        // -a0 b3 e032
        //
        // If flipped, the above turns into:
        // a0 b0 e0 +
        // (a1 b0 - a3 b2 + a2 b1) e1 +
        // (a2 b0 - a1 b1 + a3 b3) e2 +
        // (a3 b0 - a2 b3 + a1 b2) e3 +
        // (a1 b3 + a2 b2 + a3 b1) e123 +
        // -a0 b1 e021 +
        // -a0 b2 e013 +
        // -a0 b3 e032

        // To keep lanes occupied, swap e0 and e123 when accumulating sums and
        // interchange them later

        // (a1 b3, a1 b0, a2 b0, a3 b0)
        __m128 p0_tmp
            = _mm_mul_ps(KLN_SWIZZLE(a, 3, 2, 1, 1), KLN_SWIZZLE(b, 0, 0, 0, 3));

        if constexpr (Flip)
        {
            // Sub (-a2 b2, a3 b2, a1 b1, a2 b3)
            p0_tmp
                = _mm_sub_ps(p0_tmp,
                             _mm_xor_ps(_mm_mul_ps(KLN_SWIZZLE(a, 2, 1, 3, 2),
                                                   KLN_SWIZZLE(b, 3, 1, 2, 2)),
                                        _mm_set_ss(-0.f)));

            // Add (a3 b1, a2 b1, a3 b3, a1 b2)
            p0_tmp = _mm_add_ps(p0_tmp,
                                _mm_mul_ps(KLN_SWIZZLE(a, 1, 3, 2, 3),
                                           KLN_SWIZZLE(b, 2, 3, 1, 1)));
        }
        else
        {
            // Add (a2 b2, a3 b2, a1 b1, a2 b3)
            p0_tmp = _mm_add_ps(p0_tmp,
                                _mm_mul_ps(KLN_SWIZZLE(a, 2, 1, 3, 2),
                                           KLN_SWIZZLE(b, 3, 1, 2, 2)));

            // Sub (-a3 b1, a2 b1, a3 b3, a1 b2)
            p0_tmp
                = _mm_sub_ps(p0_tmp,
                             _mm_xor_ps(_mm_mul_ps(KLN_SWIZZLE(a, 1, 3, 2, 3),
                                                   KLN_SWIZZLE(b, 2, 3, 1, 1)),
                                        _mm_set_ss(-0.f)));
        }

        // (a0 b0, -a0 b1, -a0 b2, -a0 b3)
        __m128 p3_tmp = _mm_xor_ps(_mm_mul_ps(KLN_SWIZZLE(a, 0, 0, 0, 0), b),
                                   _mm_set_ps(-0.f, -0.f, -0.f, 0.f));

        // Interchange low components
        p0_out = _mm_blend_ps(p0_tmp, p3_tmp, 1);
        p3_out = _mm_blend_ps(p3_tmp, p0_tmp, 1);
    }

    // p0: (e0, e1, e2, e3)
    // p2: (e0123, e01, e02, e03)
    // p3: (e123, e021, e013, e032)
    template <bool Flip>
    KLN_INLINE void KLN_VEC_CALL gp02(__m128 const& a,
                                  __m128 const& b,
                                  __m128& p0_out,
                                  __m128& p3_out) noexcept
    {
        // -(a1 b1 + a2 b2 + a3 b3) e0 +
        // (a1 b2 + a3 b0 - a2 b1) e021 +
        // (a3 b1 + a2 b0 - a1 b3) e013 +
        // (a2 b3 + a1 b0 - a3 b2) e032
        //
        // With a flip:
        // (a1 b1 + a2 b2 + a3 b3) e0 +
        // (a1 b2 - a3 b0 - a2 b1) e021 +
        // (a3 b1 - a2 b0 - a1 b3) e013 +
        // (a2 b3 - a1 b0 - a3 b2) e032

        // (a1 b1, a1 b2, a3 b1, a2 b3)
        __m128 p3_tmp
            = _mm_mul_ps(KLN_SWIZZLE(a, 2, 3, 1, 1), KLN_SWIZZLE(b, 3, 1, 2, 1));

        if constexpr (Flip)
        {
            // Sub (-a2 b2, a3 b0, a1 b3, a1 b0)
            p3_tmp
                = _mm_sub_ps(p3_tmp,
                             _mm_xor_ps(_mm_mul_ps(KLN_SWIZZLE(a, 1, 2, 3, 2),
                                                   KLN_SWIZZLE(b, 0, 0, 0, 2)),
                                        _mm_set_ss(-0.f)));
        }
        else
        {
            // Add (a2 b2, a3 b0, a1 b3, a1 b0)
            p3_tmp = _mm_add_ps(p3_tmp,
                                _mm_mul_ps(KLN_SWIZZLE(a, 1, 2, 3, 2),
                                           KLN_SWIZZLE(b, 0, 0, 0, 2)));
        }

        // Sub (-a3 b3, a2 b1, a1 b3, a3 b2)
        p3_tmp = _mm_sub_ps(p3_tmp,
                            _mm_xor_ps(_mm_mul_ps(KLN_SWIZZLE(a, 3, 1, 2, 3),
                                                  KLN_SWIZZLE(b, 2, 3, 1, 3)),
                                       _mm_set_ss(-0.f)));

        if constexpr (!Flip)
        {
            // Negate low component
            p3_tmp = _mm_xor_ps(p3_tmp, _mm_set_ss(-0.f));
        }

        // Take the low component
        p0_out = _mm_blend_ps(_mm_setzero_ps(), p3_tmp, 1);

        // Mask the low component
        p3_out = _mm_blend_ps(p3_tmp, _mm_setzero_ps(), 1);
    }

    // p0: (e0, e1, e2, e3)
    // p3: (e123, e021, e013, e032)
    // p1: (1, e12, e31, e23)
    // p2: (e0123, e01, e02, e03)
    template <bool Flip>
    KLN_INLINE void KLN_VEC_CALL gp03(__m128 const& a,
                                  __m128 const& b,
                                  __m128& p1_out,
                                  __m128& p2_out) noexcept
    {
        // a3 b0 e12 +
        // a2 b0 e31 +
        // a1 b0 e23 +
        // (a0 b0 + a1 b3 + a2 b2 + a3 b1) e0123 +
        // (a3 b2 - a2 b1) e01 +
        // (a1 b1 - a3 b3) e02 +
        // (a2 b3 - a1 b2) e03
        //
        // With flip:
        //
        // a3 b0 e12 +
        // a2 b0 e31 +
        // a1 b0 e23 +
        // -(a0 b0 + a1 b3 + a2 b2 + a3 b1) e0123 +
        // (a3 b2 - a2 b1) e01 +
        // (a1 b1 - a3 b3) e02 +
        // (a2 b3 - a1 b2) e03

        p1_out = _mm_blend_ps(
            _mm_mul_ps(KLN_SWIZZLE(a, 1, 2, 3, 0), KLN_SWIZZLE(b, 0, 0, 0, 0)),
            _mm_setzero_ps(),
            1);

        // (_, a3 b2, a1 b1, a2 b3)
        p2_out
            = _mm_mul_ps(KLN_SWIZZLE(a, 2, 1, 3, 0), KLN_SWIZZLE(b, 3, 1, 2, 0));
        p2_out = _mm_sub_ps(
            p2_out,
            _mm_mul_ps(KLN_SWIZZLE(a, 1, 3, 2, 0), KLN_SWIZZLE(b, 2, 3, 1, 0)));

        // Compute a0 b0 + a1 b3 + a2 b2 + a3 b1 and store it in the low
        // component
        __m128 dp = _mm_dp_ps(a, KLN_SWIZZLE(b, 1, 2, 3, 0), 0b11110001);

        if constexpr (Flip)
        {
            dp = _mm_xor_ps(dp, _mm_set_ss(-0.f));
        }

        p2_out = _mm_blend_ps(p2_out, dp, 1);
    }

    // p1: (1, e12, e31, e23)
    // Returns p1
    // 16 instructions:
    // - 7 shuffles
    // - 5 mul
    // - 3 add
    // - 1 set
    inline __m128 KLN_VEC_CALL gp11(__m128 const& lhs, __m128 const& rhs) noexcept
    {
        // (a0 + a1*e12 + a2*e31 + a3*e23) * (b0 + b1*e12 + b2*e31 + b3*e23) =
        //
        //       (a0*b0 - a1*b1 - a2*b2 - a3*b3)
        //     + (a0*b1 - a3*b2 + a1*b0 + a2*b3)*e12
        //     + (a0*b2 - a1*b3 + a2*b0 + a3*b1)*e31
        //     + (a0*b3 - a2*b1 + a3*b0 + a1*b2)*e23

        // We use abcd to refer to the slots to avoid conflating bivector/scalar
        // coefficients with cartesian coordinates

        // (a0*b0, a0*b1, a0*b2, a0*b3)
        __m128 tmp = _mm_mul_ps(KLN_SWIZZLE(lhs, 0, 0, 0, 0), rhs);

        // Subtract (a1*b1, a3*b2, a1*b3, a2*b1)
        tmp = _mm_sub_ps(tmp,
                         _mm_mul_ps(KLN_SWIZZLE(lhs, 2, 1, 3, 1),
                                    KLN_SWIZZLE(rhs, 1, 3, 2, 1)));

        // In a separate register, accumulate the later components so we can
        // negate the lower single-precision element with a single instruction
        __m128 tmp2 = _mm_mul_ps(
            KLN_SWIZZLE(lhs, 3, 2, 1, 2), KLN_SWIZZLE(rhs, 0, 0, 0, 2));

        tmp2 = _mm_add_ps(tmp2,
                          _mm_mul_ps(KLN_SWIZZLE(lhs, 1, 3, 2, 3),
                                     KLN_SWIZZLE(rhs, 2, 1, 3, 3)));

        tmp2 = _mm_xor_ps(tmp2, _mm_set_ss(-0.f));

        return _mm_add_ps(tmp, tmp2);
    }

    // p1: (1, e12, e31, e23)
    // p2: (e0123, e01, e02, e03)
    // Returns p2
    // 16 instructions:
    // - 7 shuffles
    // - 5 mul
    // - 3 add
    // - 1 set
    inline __m128 KLN_VEC_CALL gp12(__m128 const& a, __m128 const& b) noexcept
    {
        // (a0 + a1*e12 + a2*e31 + a3*e23) *
        //   (b0*e0123 + b1*e01 + b2*e02 + b3*e03) =
        //
        //     (a0*b0 + a2*b2 + a1*b3 + a3*b1)*e0123
        //   + (a0*b1 + a1*b2 - a2*b3 - a3*b0)*e01
        //   + (a0*b2 + a3*b3 - a2*b0 - a1*b1)*e02
        //   + (a0*b3 + a2*b1 - a1*b0 - a3*b2)*e03

        // (a0*b0, a0*b1, a0*b2, a0*b3)
        __m128 tmp = _mm_mul_ps(KLN_SWIZZLE(a, 0, 0, 0, 0), b);

        // Add (a2*b2, a1*b2, a3*b3, a2*b1)
        tmp = _mm_add_ps(
            tmp,
            _mm_mul_ps(KLN_SWIZZLE(a, 2, 3, 1, 2), KLN_SWIZZLE(b, 1, 3, 2, 2)));

        // Accumulate the 3rd and 4th columns separately to negate lowest
        // component once and subtract

        // (a1*b3, a2*b3, a2*b0, a1*b0)
        __m128 tmp2
            = _mm_mul_ps(KLN_SWIZZLE(a, 1, 2, 2, 1), KLN_SWIZZLE(b, 0, 0, 3, 3));

        // Add (a3*b1, a3*b0, a1*b1, a3*b2)
        tmp2 = _mm_add_ps(
            tmp2,
            _mm_mul_ps(KLN_SWIZZLE(a, 3, 1, 3, 3), KLN_SWIZZLE(b, 2, 1, 0, 1)));

        tmp2 = _mm_xor_ps(tmp2, _mm_set_ss(-0.f));

        return _mm_sub_ps(tmp, tmp2);
    }

    inline __m128 KLN_VEC_CALL gp21(__m128 const& a, __m128 const& b) noexcept
    {
        // (a0*e0123 + a1*e01 + a2*e02 + a3*e03) *
        //   (b0 + b1*e12 + b2*e31 + b3*e23) =
        //
        //     (a0*b0 + a1*b3 + a2*b2 + a3*b1)*e0123
        //   + (a1 b0 + a3 b2 - a0 b3 - a2 b1)*e01
        //   + (a2 b0 + a1 b1 - a0 b2 - a3 b3)*e02
        //   + (a3 b0 + a2 b3 - a0 b1 - a1 b2)*e03

        __m128 tmp = _mm_mul_ps(a, KLN_SWIZZLE(b, 0, 0, 0, 0));

        tmp = _mm_add_ps(
            tmp,
            _mm_mul_ps(KLN_SWIZZLE(a, 2, 1, 3, 1), KLN_SWIZZLE(b, 3, 1, 2, 3)));

        __m128 tmp2
            = _mm_mul_ps(KLN_SWIZZLE(a, 0, 0, 0, 2), KLN_SWIZZLE(b, 1, 2, 3, 2));

        tmp2 = _mm_add_ps(
            tmp2,
            _mm_mul_ps(KLN_SWIZZLE(a, 1, 3, 2, 3), KLN_SWIZZLE(b, 2, 3, 1, 1)));

        tmp2 = _mm_xor_ps(tmp2, _mm_set_ss(-0.f));

        return _mm_sub_ps(tmp, tmp2);
    }

    // p1: (1, e12, e31, e23)
    // p3: (e123, e021, e013, e032)
    // Returns p0 and p3
    // p0: (e0, e1, e2, e3)
    // p3: (e123, e021, e013, e032)
    template <bool Flip>
    KLN_INLINE void KLN_VEC_CALL gp13(__m128 const& a,
                                  __m128 const& b,
                                  __m128& p0_out,
                                  __m128& p3_out) noexcept
    {
        // a0 b0 e123 +
        // -a3 b0 e1 +
        // -a2 b0 e2 +
        // -a1 b0 e3 +
        // (a1 b1 + a2 b2 + a3 b3) e0 +
        // (a0 b1 + a2 b3 - a3 b2) e021 +
        // (a0 b2 + a3 b1 - a1 b3) e013 +
        // (a0 b3 + a1 b2 - a2 b1) e032
        //
        // With flip:
        //
        // a0 b0 e123 +
        // -a3 b0 e1 +
        // -a2 b0 e2 +
        // -a1 b0 e3 +
        // (a1 b1 + a2 b2 + a3 b3) e0 +
        // (a0 b1 - a2 b3 + a3 b2) e021 +
        // (a0 b2 - a3 b1 + a1 b3) e013 +
        // (a0 b3 - a1 b2 + a2 b1) e032

        // As with other partition combinations, we exchange two components to
        // increase lane occupancy and perform two blends to read the results at
        // the end.

        // (a0, b0, -a3 b0, -a2 b0, -a1 b0)
        __m128 p0_tmp = _mm_xor_ps(
            _mm_mul_ps(KLN_SWIZZLE(a, 1, 2, 3, 0), KLN_SWIZZLE(b, 0, 0, 0, 0)),
            _mm_set_ps(-0.f, -0.f, -0.f, 0.f));

        __m128 p3_tmp
            = _mm_mul_ps(KLN_SWIZZLE(a, 0, 0, 0, 1), KLN_SWIZZLE(b, 3, 2, 1, 1));

        if constexpr (Flip)
        {
            p3_tmp
                = _mm_sub_ps(p3_tmp,
                             _mm_xor_ps(_mm_mul_ps(KLN_SWIZZLE(a, 1, 3, 2, 2),
                                                   KLN_SWIZZLE(b, 2, 1, 3, 2)),
                                        _mm_set_ss(-0.f)));
            p3_tmp = _mm_add_ps(p3_tmp,
                                _mm_mul_ps(KLN_SWIZZLE(a, 2, 1, 3, 3),
                                           KLN_SWIZZLE(b, 1, 3, 2, 3)));
        }
        else
        {
            p3_tmp
                = _mm_sub_ps(p3_tmp,
                             _mm_xor_ps(_mm_mul_ps(KLN_SWIZZLE(a, 2, 1, 3, 3),
                                                   KLN_SWIZZLE(b, 1, 3, 2, 3)),
                                        _mm_set_ss(-0.f)));
            p3_tmp = _mm_add_ps(p3_tmp,
                                _mm_mul_ps(KLN_SWIZZLE(a, 1, 3, 2, 2),
                                           KLN_SWIZZLE(b, 2, 1, 3, 2)));
        }

        // Exchange low components
        p0_out = _mm_blend_ps(p0_tmp, p3_tmp, 1);
        p3_out = _mm_blend_ps(p3_tmp, p0_tmp, 1);
    }

    // p2: (e0123, e01, e02, e03)
    // p3: (e123, e021, e013, e032)
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
        // -a3 b0 e021 +
        // -a2 b0 e013 +
        // -a1 b0 e032
        //
        // With the flip:
        // a0 b0 e0 +
        // a3 b0 e021 +
        // a2 b0 e013 +
        // a1 b0 e032

        __m128 tmp
            = _mm_mul_ps(KLN_SWIZZLE(a, 1, 2, 3, 0), KLN_SWIZZLE(b, 0, 0, 0, 0));
        if constexpr (!Flip)
        {
            // Negate tmp
            tmp = _mm_xor_ps(tmp, _mm_set1_ps(-0.f));
        }
        p0_out = _mm_blend_ps(_mm_setzero_ps(), tmp, 1);
        p3_out = _mm_blend_ps(tmp, _mm_setzero_ps(), 1);
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
        // (a0*e123 + a1*e021 + a2*e013 + a3*e032) =
        //   (b0*e123 + b1*e021 + b2*e013 + b3*e032) =
        //
        //      (-a0*b0)
        //    + (-a0*b3 + a3*b0)*e01
        //    + (-a0*b2 + a2*b0)*e02
        //    + (-a0*b1 + a1*b0)*e03

        __m128 tmp
            = _mm_mul_ps(KLN_SWIZZLE(a, 0, 0, 0, 0), KLN_SWIZZLE(b, 1, 2, 3, 0));

        // (-2*a0*b0, -a0*b1, -a0*b2, -a0*b3)
        tmp = _mm_mul_ps(tmp, _mm_set_ps(-1.f, -1.f, -1.f, -2.f));

        // (1, e03, e02, e01)
        tmp = _mm_add_ps(
            tmp,
            _mm_mul_ps(KLN_SWIZZLE(a, 1, 2, 3, 0), KLN_SWIZZLE(b, 0, 0, 0, 0)));

        p1_out = _mm_blend_ps(_mm_setzero_ps(), tmp, 1);
        p2_out = _mm_blend_ps(tmp, _mm_setzero_ps(), 1);
    }
} // namespace detail
} // namespace kln