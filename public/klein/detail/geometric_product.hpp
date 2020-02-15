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
    // p0: (e3, e2, e1, e0)
    // p1: (1, e12, e31, e23)
    // p2: (e0123, e01, e02, e03)
    // p3: (e123, e021, e013, e032)

    struct p1p2
    {
        __m128 p1;
        __m128 p2;
    };

    struct p0p3
    {
        __m128 p0;
        __m128 p3;
    };

    struct p2p3
    {
        __m128 p2;
        __m128 p3;
    };

    // p0: (e3, e2, e1, e0)
    // Returns both p1 and p2 packed in a struct
    // 20 instructions
    // - 8 shuffles
    // - 7 muls
    // - 3 adds
    // - 2 sets
    inline p1p2 KLN_VEC_CALL gp00(__m128 const& lhs, __m128 const& rhs) noexcept
    {
        // (a3*e0 + a2*e1 + a1*e2 + a0*e3) * (b3*e0 + b2*e1 + b1*e2 + b0*e3) =
        //
        //      (a2*b2 + a1*b1 + a0*b0)
        //    + (a2*b1 - a1*b2)*e12
        //    + (a0*b2 - a2*b0)*e31
        //    + (a1*b0 - a0*b1)*e23
        //    + (a3*b2 - a2*b3)*e01
        //    + (a3*b1 - a1*b3)*e02
        //    + (a3*b0 - a0*b3)*e03

        // (a2*b2, a2*b1, a0*b2, a1*b0)
        __m128 tmp = _mm_mul_ps(
            KLN_SWIZZLE(lhs, 1, 0, 2, 2), KLN_SWIZZLE(rhs, 0, 2, 1, 2));

        // (a1*b1, a1*b2, a2*b0, a0*b1)
        __m128 tmp2 = _mm_mul_ps(
            KLN_SWIZZLE(lhs, 0, 2, 1, 1), KLN_SWIZZLE(rhs, 1, 0, 2, 1));
        // Add a3*b3 to the lowest component and negate the lowest component
        tmp2 = _mm_mul_ss(
            _mm_add_ss(tmp2, _mm_mul_ss(lhs, rhs)), _mm_set_ss(-1.f));

        // Produces Euclidean bivector
        tmp = _mm_sub_ps(tmp, tmp2);

        // Use tmp2 to store the ideal bivector

        // (_, a3*b2, a3*b1, a3*b0)
        tmp2 = _mm_mul_ps(
            KLN_SWIZZLE(lhs, 3, 3, 3, 3), KLN_SWIZZLE(rhs, 0, 1, 2, 3));

        // Subtract (_, a2*b3, a1*b3, a0*b3)
        tmp2 = _mm_sub_ps(tmp2,
                          _mm_mul_ps(KLN_SWIZZLE(lhs, 0, 1, 2, 3),
                                     KLN_SWIZZLE(rhs, 3, 3, 3, 3)));
        // Zero the lowest component
        tmp2 = _mm_mul_ss(tmp2, _mm_setzero_ps());

        return {tmp, tmp2};
    }

    // p0: (e3, e2, e1, e0)
    // p1: (1, e12, e31, e23)
    // Returns a p0 and p3
    // p3: (e123, e021, e013, e032)
    // 20 instructions
    // - 8 shuffles
    // - 2 blends
    // - 6 muls
    // - 2 adds
    // - 2 sets
    inline p0p3 KLN_VEC_CALL gp01(__m128 const& lhs, __m128 const& rhs) noexcept
    {
        // (a3*e0 + a2*e1 + a1*e2 + a0*e3) * (b0 + b1*e12 + b2*e31 + b3*e23) =
        //
        //      (a2*b3 + a0*b1 + a1*b2)*e123
        //    + (a2*b0 + a0*b2 - a1*b1)*e1
        //    + (a1*b0 + a2*b1 - a0*b3)*e2
        //    + (a0*b0 + a1*b3 - a2*b2)*e3
        //    + (a3*b0)*e0
        //    + (-a3*b1)*e021
        //    + (-a3*b2)*e013
        //    + (-a3*b3)*e032

        // The ordering above matches operations across lanes for maximum
        // occupancy. The results need two final blends to produce the desired
        // layout. The vector requires a final shuffle before being returned.

        // (a2*b3, a2*b0, a1*b0, a0*b0)
        __m128 tmp = _mm_mul_ps(
            KLN_SWIZZLE(lhs, 0, 1, 2, 2), KLN_SWIZZLE(rhs, 0, 0, 0, 3));

        // Add (a0*b1, a0*b2, a2*b1, a1*b3)
        tmp = _mm_add_ps(tmp,
                         _mm_mul_ps(KLN_SWIZZLE(lhs, 1, 2, 0, 0),
                                    KLN_SWIZZLE(rhs, 3, 1, 2, 1)));

        // (a1*b2, a1*b1, a0*b3, a2*b2)
        __m128 tmp2 = _mm_mul_ps(
            KLN_SWIZZLE(lhs, 2, 0, 1, 1), KLN_SWIZZLE(rhs, 2, 3, 1, 2));
        tmp2 = _mm_mul_ss(tmp2, _mm_set_ss(-1.f));

        // Produces (e123, e1, e2, e3)
        tmp = _mm_sub_ps(tmp, tmp2);

        // (a3*b0, a3*b1, a3*b2, a3*b3)
        tmp2 = _mm_mul_ps(KLN_SWIZZLE(lhs, 3, 3, 3, 3), rhs);
        // (e0, e021, e013, e032)
        tmp2 = _mm_mul_ps(tmp2, _mm_set_ps(-1.f, -1.f, -1.f, 1.f));

        return {KLN_SWIZZLE(_mm_blend_ps(tmp, tmp2, 0b1), 0, 1, 2, 3),
                _mm_blend_ps(tmp, tmp2, 0b1110)};
    }

    inline p0p3 KLN_VEC_CALL gp10(__m128 const& lhs, __m128 const& rhs) noexcept
    {
        // (a0 + a1*e12 + a2*e31 + a3*e23) * (b3*e0 + b2*e1 + b1*e2 + b0*e3) =
        //
        //      (a3*b2 + a1*b0 + a2*b1)*e123
        //    + (a0*b2 + a1*b1 - a2*b0)*e1
        //    + (a0*b1 + a3*b0 - a1*b2)*e2
        //    + (a0*b0 + a2*b2 - a3*b1)*e3
        //    + (a0*b3)*e0
        //    + (-a1*b3)*e021
        //    + (-a2*b3)*e013
        //    + (-a3*b3)*e032

        __m128 tmp = _mm_mul_ps(
            KLN_SWIZZLE(rhs, 0, 1, 2, 2), KLN_SWIZZLE(lhs, 0, 0, 0, 3));
        tmp = _mm_add_ps(tmp,
                         _mm_mul_ps(KLN_SWIZZLE(lhs, 2, 3, 1, 1),
                                    KLN_SWIZZLE(rhs, 2, 0, 1, 0)));

        __m128 tmp2 = _mm_mul_ps(
            KLN_SWIZZLE(lhs, 3, 1, 2, 2), KLN_SWIZZLE(rhs, 1, 2, 0, 1));
        tmp2 = _mm_mul_ss(tmp2, _mm_set_ss(-1.f));

        // Produces (e123, e1, e2, e3)
        tmp = _mm_sub_ps(tmp, tmp2);

        tmp2 = _mm_mul_ps(lhs, KLN_SWIZZLE(rhs, 3, 3, 3, 3));
        // (e0, e021, e013, e032)
        tmp2 = _mm_mul_ps(tmp2, _mm_set_ps(-1.f, -1.f, -1.f, 1.f));

        return {KLN_SWIZZLE(_mm_blend_ps(tmp, tmp2, 0b1), 0, 1, 2, 3),
                _mm_blend_ps(tmp, tmp2, 0b1110)};
    }

    // p0: (e3, e2, e1, e0)
    // p2: (e0123, e01, e02, e03)
    // Returns a p0 and p3
    // p3: (e123, e021, e013, e032)
    inline p0p3 KLN_VEC_CALL gp02(__m128 const& lhs, __m128 const& rhs) noexcept
    {
        // (a3*e0 + a2*e1 + a1*e2 + a0*e3) *
        //   (b0*e0123 + b1*e01 + b2*e02 + b3*e03) =
        //
        //      (-a2*b1 - a1*b2 - a0*b3)*e0
        //    + (a0*b0 + a2*b2 - a1*b1)*e021
        //    + (a1*b0 + a0*b1 - a2*b3)*e013
        //    + (a2*b0 + a1*b3 - a0*b2)*e032

        // (a2*b1, a0*b0, a1*b0, a2*b0)
        __m128 tmp = _mm_mul_ps(
            KLN_SWIZZLE(lhs, 2, 1, 0, 2), KLN_SWIZZLE(rhs, 0, 0, 0, 1));

        // Add (a1*b2, a2*b2, a0*b1, a1*b3)
        tmp = _mm_add_ps(tmp,
                         _mm_mul_ps(KLN_SWIZZLE(lhs, 1, 0, 2, 1),
                                    KLN_SWIZZLE(rhs, 3, 1, 2, 2)));

        // Negate lowest component
        tmp = _mm_mul_ss(tmp, _mm_set_ss(-1.f));

        // Subtract (a0*b3, a1*b2, a2*b3, a0*b2)
        tmp = _mm_sub_ps(tmp,
                         _mm_mul_ps(KLN_SWIZZLE(lhs, 0, 2, 1, 0),
                                    KLN_SWIZZLE(rhs, 2, 3, 1, 3)));

        return {// Move e0 the last component and zero other components
                KLN_SWIZZLE(_mm_mul_ps(tmp, _mm_set_ss(1.f)), 0, 1, 2, 3),
                // Zero pseudoscalar component
                _mm_mul_ss(tmp, _mm_set_ss(0.f))};
    }

    inline p0p3 KLN_VEC_CALL gp20(__m128 const& lhs, __m128 const& rhs) noexcept
    {
        // (a0*e0123 + a1*e01 + a2*e02 + a3*e03) =
        //   (b3*e0 + b2*e1 + b1*e2 + b0*e3) *
        //
        //      (b2*a1 + b1*a2 + b0*a3)*e0
        //    + (b0*a0 + b2*a2 - b1*a1)*e021
        //    + (b1*a0 + b0*a1 - b2*a3)*e013
        //    + (b2*a0 + b1*a3 - b0*a2)*e032

        __m128 tmp = _mm_mul_ps(
            KLN_SWIZZLE(rhs, 2, 1, 0, 2), KLN_SWIZZLE(lhs, 0, 0, 0, 1));

        tmp = _mm_add_ps(tmp,
                         _mm_mul_ps(KLN_SWIZZLE(rhs, 1, 0, 2, 1),
                                    KLN_SWIZZLE(lhs, 3, 1, 2, 2)));

        tmp = _mm_sub_ps(tmp,
                         _mm_mul_ss(_mm_mul_ps(KLN_SWIZZLE(rhs, 0, 2, 1, 0),
                                               KLN_SWIZZLE(lhs, 2, 3, 1, 3)),
                                    _mm_set_ss(-1.f)));

        return {// Move e0 the last component and zero other components
                KLN_SWIZZLE(_mm_mul_ps(tmp, _mm_set_ss(1.f)), 0, 1, 2, 3),
                // Zero pseudoscalar component
                _mm_mul_ss(tmp, _mm_set_ss(0.f))};
    }

    // p0: (e3, e2, e1, e0)
    // p3: (e123, e021, e013, e032)
    // Returns p1 and p2 packed in a struct
    // p1: (1, e12, e31, e23)
    // p2: (e0123, e01, e02, e03)
    // 19 instructions:
    // - 8 shuffles
    // - 6 muls
    // - 3 adds
    // - 2 sets
    inline p1p2 KLN_VEC_CALL gp03(__m128 const& lhs, __m128 const& rhs) noexcept
    {
        // (a3*e0 + a2*e1 + a1*e2 + a0*e3) *
        //   (b0*e123 + b1*e021 + b2*e013 + b3*e032) =
        //
        //       (a0*b0)*e12
        //     + (a1*b0)*e31
        //     + (a2*b0)*e23
        //     + (a3*b0 + a0*b1 + a1*b2 + a2*b3)*e0123
        //     + (a0*b2 - a1*b1)*e01
        //     + (a2*b1 - a0*b3)*e02
        //     + (a1*b3 - a2*b2)*e03

        // (a3*b0, a0*b2, a2*b1, a1*b3)
        __m128 tmp = _mm_mul_ps(
            KLN_SWIZZLE(lhs, 1, 2, 0, 3), KLN_SWIZZLE(rhs, 3, 1, 2, 0));

        // (-a0*b1, a1*b1, a0*b3, a2*b2)
        __m128 tmp2 = _mm_mul_ps(
            KLN_SWIZZLE(lhs, 2, 0, 1, 0), KLN_SWIZZLE(rhs, 2, 3, 1, 1));
        tmp2 = _mm_mul_ss(tmp2, _mm_set_ss(-1.f));

        tmp = _mm_sub_ps(tmp, tmp2);
        // Still need to compute a1*b2 + a2*b3 to add to the lowest component of
        // tmp. Alternatively, we could have left the lane open and computed a
        // dot product separately.

        // (a1*b2, a0*b0, a1*b0, a2*b0)
        tmp2 = _mm_mul_ps(
            KLN_SWIZZLE(lhs, 2, 1, 0, 1), KLN_SWIZZLE(rhs, 0, 0, 0, 2));

        // Add a1*b2 to the lowest component of p2
        tmp = _mm_add_ss(tmp, tmp2);
        // Add a2*b3 to the lowest component of p2
        tmp = _mm_add_ss(tmp,
                         _mm_mul_ss(KLN_SWIZZLE(lhs, 0, 0, 0, 2),
                                    KLN_SWIZZLE(rhs, 0, 0, 0, 3)));
        return {// Zero the lowest component which held a portion of the pss
                _mm_mul_ss(tmp2, _mm_setzero_ps()),
                tmp};
    }

    inline p1p2 KLN_VEC_CALL gp30(__m128 const& lhs, __m128 const& rhs) noexcept
    {
        // (a0*e123 + a1*e021 + a2*e013 + a3*e032) =
        //   (b3*e0 + b2*e1 + b1*e2 + b0*e3) *
        //
        //       (b0*a0)*e12
        //     + (b1*a0)*e31
        //     + (b2*a0)*e23
        //     + (-b3*a0 - b0*a1 - b1*a2 - b2*a3)*e0123
        //     + (b0*a2 - b1*a1)*e01
        //     + (b2*a1 - b0*a3)*e02
        //     + (b1*a3 - b2*a2)*e03

        __m128 tmp = _mm_mul_ps(
            KLN_SWIZZLE(rhs, 1, 2, 0, 3), KLN_SWIZZLE(lhs, 3, 1, 2, 0));
        tmp = _mm_mul_ss(tmp, _mm_set_ss(-1.f));

        __m128 tmp2 = _mm_mul_ps(
            KLN_SWIZZLE(rhs, 2, 0, 1, 0), KLN_SWIZZLE(lhs, 2, 3, 1, 1));

        tmp = _mm_sub_ps(tmp, tmp2);

        tmp2 = _mm_mul_ps(
            KLN_SWIZZLE(rhs, 2, 1, 0, 1), KLN_SWIZZLE(lhs, 0, 0, 0, 2));

        tmp = _mm_sub_ss(tmp, tmp2);
        tmp = _mm_sub_ss(tmp,
                         _mm_mul_ss(KLN_SWIZZLE(rhs, 0, 0, 0, 2),
                                    KLN_SWIZZLE(lhs, 0, 0, 0, 3)));
        return {// Zero the lowest component which held a portion of the pss
                _mm_mul_ss(tmp2, _mm_setzero_ps()),
                tmp};
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

        // TODO: Consider using an xor here which has a latency of a
        // single cycle instead of 4 which may stall a later dependency
        // chain
        // mul CPI: .5, latency: 3-5
        // xor CPI: 1, latency: 1
        tmp2 = _mm_mul_ss(tmp2, _mm_set_ss(-1.f));

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

        tmp2 = _mm_mul_ss(tmp2, _mm_set_ss(-1.f));

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

        tmp2 = _mm_mul_ss(tmp2, _mm_set_ss(-1.f));

        return _mm_sub_ps(tmp, tmp2);
    }

    // p1: (1, e12, e31, e23)
    // p3: (e123, e021, e013, e032)
    // Returns p0 and p3
    // p0: (e3, e2, e1, e0)
    // p3: (e123, e021, e013, e032)
    inline p0p3 KLN_VEC_CALL gp13(__m128 const& lhs, __m128 const& rhs) noexcept
    {
        // (a0 + a1*e12 + a2*e31 + a3*e23) *
        //   (b0*e123 + b1*e021 + b2*e013 + b3*e032) =
        //
        //      (a1*b1 + a2*b2 + a3*b3)*e0
        //    + (a0*b1 + a2*b3 - a3*b2)*e021
        //    + (a0*b2 + a3*b1 - a1*b3)*e013
        //    + (a0*b3 + a1*b2 - a2*b1)*e032
        //    + (a0*b0)*e123
        //    + (-a1*b0)*e3
        //    + (-a2*b0)*e2
        //    + (-a3*b0)*e1

        // As with other partition combinations, we exchange two components to
        // increase lane occupancy and perform two blends to read the results at
        // the end.

        // (a1*b1, a0*b1, a0*b2, a0*b3)
        __m128 tmp = _mm_mul_ps(
            KLN_SWIZZLE(lhs, 0, 0, 0, 1), KLN_SWIZZLE(rhs, 3, 2, 1, 1));

        // Add (a2*b2, a2*b3, a3*b1, a1*b2)
        tmp = _mm_add_ps(tmp,
                         _mm_mul_ps(KLN_SWIZZLE(lhs, 1, 3, 2, 2),
                                    KLN_SWIZZLE(rhs, 2, 1, 3, 2)));

        // (a3*b3, a3*b2, a1*b3, a2*b1)
        __m128 tmp2 = _mm_mul_ps(
            KLN_SWIZZLE(lhs, 2, 1, 3, 3), KLN_SWIZZLE(rhs, 1, 3, 2, 3));
        tmp2 = _mm_mul_ss(tmp2, _mm_set_ss(-1.f));

        // This now holds (e0, e021, e013, e032)
        tmp = _mm_sub_ps(tmp, tmp2);

        // (a0*b0, a1*b0, a2*b0, a3*b0)
        tmp2 = _mm_mul_ps(lhs, KLN_SWIZZLE(rhs, 0, 0, 0, 0));
        // Negate 3 high components to store (e123, e3, e2, e1)
        tmp2 = _mm_mul_ps(tmp2, _mm_set_ps(-1.f, -1.f, -1.f, 1.f));

        return {// (e0, e3, e2, e1) -> (e3, e2, e1, e0)
                KLN_SWIZZLE(_mm_blend_ps(tmp, tmp2, 0b1110), 0, 3, 2, 1),
                _mm_blend_ps(tmp, tmp2, 0b1)};
    }

    inline p0p3 KLN_VEC_CALL gp31(__m128 const& lhs, __m128 const& rhs) noexcept
    {
        // (a0*e123 + a1*e021 + a2*e013 + a3*e032) =
        //   (b0 + b1*e12 + b2*e31 + b3*e23) *
        //
        //      (b1*a1 + b2*a2 + b3*a3)*e0
        //    + (b0*a1 - b2*a3 + b3*a2)*e021
        //    + (b0*a2 - b3*a1 + b1*a3)*e013
        //    + (b0*a3 - b1*a2 + b2*a1)*e032
        //    + (b0*a0)*e123
        //    + (-b1*a0)*e3
        //    + (-b2*a0)*e2
        //    + (-b3*a0)*e1

        __m128 tmp = _mm_mul_ps(
            KLN_SWIZZLE(rhs, 0, 0, 0, 1), KLN_SWIZZLE(lhs, 3, 2, 1, 1));

        tmp = _mm_add_ps(tmp,
                         _mm_mul_ps(KLN_SWIZZLE(lhs, 1, 3, 2, 3),
                                    KLN_SWIZZLE(rhs, 2, 1, 3, 3)));

        __m128 tmp2 = _mm_mul_ps(
            KLN_SWIZZLE(lhs, 2, 1, 3, 2), KLN_SWIZZLE(rhs, 1, 3, 2, 2));
        tmp2 = _mm_mul_ss(tmp2, _mm_set_ss(-1.f));

        // This now holds (e0, e021, e013, e032)
        tmp = _mm_sub_ps(tmp, tmp2);

        tmp2 = _mm_mul_ps(rhs, KLN_SWIZZLE(lhs, 0, 0, 0, 0));
        tmp2 = _mm_mul_ps(tmp2, _mm_set_ps(-1.f, -1.f, -1.f, 1.f));

        return {// (e0, e3, e2, e1) -> (e3, e2, e1, e0)
                KLN_SWIZZLE(_mm_blend_ps(tmp, tmp2, 0b1110), 0, 3, 2, 1),
                _mm_blend_ps(tmp, tmp2, 0b1)};
    }

    // p2: (e0123, e01, e02, e03)
    // p3: (e123, e021, e013, e032)
    // Returns p0 and p3
    // p0: (e3, e2, e1, e0)
    // Note that this specific product is somewhat awkward as e1, e2, and e3 are
    // unused
    inline p0p3 KLN_VEC_CALL gp23(__m128 const& lhs, __m128 const& rhs) noexcept
    {
        // (a0*e0123 + a1*e01 + a2*e02 + a3*e03) *
        //   (b0*e123 + b1*e021 + b2*e013 + b3*e032) =
        //
        //      (-a0*b0)*e0
        //    + (-a3*b0)*e021
        //    + (-a2*b0)*e013
        //    + (-a1*b0)*e032

        __m128 tmp = _mm_mul_ps(
            KLN_SWIZZLE(lhs, 1, 2, 3, 0), KLN_SWIZZLE(rhs, 0, 0, 0, 0));
        // Negate tmp
        tmp = _mm_xor_ps(tmp, _mm_set1_ps(-0.f));
        return {// Mask everything but e0 and move it to the MSB
                KLN_SWIZZLE(_mm_mul_ps(tmp, _mm_set_ss(1.f)), 0, 1, 2, 3),

                // Mask the e0 component
                _mm_mul_ss(tmp, _mm_setzero_ps())};
    }

    inline p0p3 KLN_VEC_CALL gp32(__m128 const& lhs, __m128 const& rhs) noexcept
    {
        // (a0*e123 + a1*e021 + a2*e013 + a3*e032) *
        //   (b0*e0123 + b1*e01 + b2*e02 + b3*e03) =
        //
        //      (b0*a0)*e0
        //    + (b3*a0)*e021
        //    + (b2*a0)*e013
        //    + (b1*a0)*e032

        __m128 tmp = _mm_mul_ps(
            KLN_SWIZZLE(rhs, 1, 2, 3, 0), KLN_SWIZZLE(lhs, 0, 0, 0, 0));
        return {// Mask everything but e0 and move it to the MSB
                KLN_SWIZZLE(_mm_mul_ps(tmp, _mm_set_ss(1.f)), 0, 1, 2, 3),

                // Mask the e0 component
                _mm_mul_ss(tmp, _mm_setzero_ps())};
    }

    // p3: (e123, e021, e013, e032)
    // Returns p1 and p2
    // p1: (1, e12, e31, e23)
    // p2: (e0123, e01, e02, e03)
    inline p1p2 KLN_VEC_CALL gp33(__m128 const& lhs, __m128 const& rhs) noexcept
    {
        // (a0*e123 + a1*e021 + a2*e013 + a3*e032) =
        //   (b0*e123 + b1*e021 + b2*e013 + b3*e032) =
        //
        //      (-a0*b0)
        //    + (-a0*b1 + a1*b0)*e03
        //    + (-a0*b2 + a2*b0)*e02
        //    + (-a0*b3 + a3*b0)*e01

        // (a0*b0, a0*b1, a0*b2, a0*b3)
        __m128 tmp = _mm_mul_ps(KLN_SWIZZLE(lhs, 0, 0, 0, 0), rhs);

        // (-2*a0*b0, -a0*b1, -a0*b2, -a0*b3)
        tmp = _mm_mul_ps(tmp, _mm_set_ps(-1.f, -1.f, -1.f, -2.f));

        // (1, e03, e02, e01)
        tmp = _mm_add_ps(tmp, _mm_mul_ps(lhs, KLN_SWIZZLE(rhs, 0, 0, 0, 0)));

        return {// Mask every component but the scalar component
                _mm_mul_ps(tmp, _mm_set_ss(1.f)),
                // Mask the scalar component
                KLN_SWIZZLE(_mm_mul_ss(tmp, _mm_setzero_ps()), 1, 2, 3, 0)};
    }
} // namespace detail
} // namespace kln