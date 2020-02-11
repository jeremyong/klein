// File: prstar_sw.hpp
// Purpose: Define functions of the form swAB where A and B are partition
// indices. Each function so-defined computes the sandwich operator using vector
// intrinsics. The partition index determines which basis elements are present
// in each XMM component of the operand.
//
// Notes:
// 1. The first argument is always the TARGET which is the multivector to apply
//    the sandwich operator to.
// 2. The second operator MAY be a bivector or motor (sandwiching with
//    a point or vector isn't supported at this time).
// 3. For efficiency, the sandwich operator is NOT implemented in terms of two
//    geometric products and a reversion. The result is nevertheless equivalent.

#pragma once

#include "prstar_sse.hpp"

namespace prs
{
inline namespace detail
{
    // Partition memory layouts
    //     LSB --> MSB
    // p0: (e3, e2, e1, e0)
    // p1: (1, e12, e31, e23)
    // p2: (e0123, e01, e02, e03)
    // p3: (e123, e021, e013, e032)

    // Apply a rotor to a plane. Assumes the rotor is normalized
    // b * a * ~b
    inline auto PRS_VEC_CALL sw01(__m128 const& a, __m128 const& b) noexcept
    {
        // (b0 + b1*e12 + b2*e31 + b3*e23) * (a3*e0 + a2*e1 + a1*e2 + a0*e3)
        //   * (b0 - b1*e12 - b2*e31 - b3*e23) =
        //
        // a3*(b0^2 + b1^2 + b2^2 + b3^2)*e0 +
        //
        // (2*(-a0*b0*b2 + a0*b1*b3 + a1*b0*b1 + a1*b2*b3)
        //  + a2*(b0^2 + b3^2 - b1^2 - b2^2))*e1 +
        //
        // (2*(-a2*b0*b1 + a0*b0*b3 + a0*b1*b2 + a2*b2*b3)
        //  + a1*(b0^2 + b2^2 - b1^2 - b3^2))*e2 +
        //
        // (2*(-a1*b0*b3 + a1*b1*b2 + a2*b0*b2 + a2*b1*b3)
        //  + a0*(b0^2 + b1^2 - b2^2 - b3^2))*e3 +
        //
        // The twelve cubic terms can be done with 9 SSE muls and some
        // swizzling. To accommodate this, the 3 negative terms are accumulated
        // in the upper portion of the register and swizzled
    }

    // Apply a translator to a plane.
    // Assumes e0123 component of p2 is exactly 0
    // p0: (e3, e2, e1, e0)
    // p2: (e0123, e01, e02, e03)
    // b * a * ~b
    inline auto PRS_VEC_CALL sw02(__m128 const& a, __m128 const& b)
    {
        // (1 + b1*e01 + b2*e02 + b3*e03) *
        //   (a3*e0 + a2*e1 + a1*e2 + a0*e3) *
        //   (1 - b1*e01 - b2*e02 - b3*e03) =
        //
        // (a3 + 2*a0*b3 + 2*a1*b2 + 2*a2*b1)*e0 + a2*e1 + a1*e2 + a0*e3

        // a0*b3 + a1*b2 + a2*b1 stored in the high component of tmp
        __m128 tmp = _mm_dp_ps(a, PRS_SWIZZLE(b, 0, 1, 2, 3), 0b01111000);

        // Scale by 2
        tmp = _mm_mul_ps(tmp, _mm_set1_ps(2.f));

        // Add to the plane
        return _mm_add_ps(a, tmp);
    }

    // Apply a motor to a plane
    inline auto PRS_VEC_CALL sw012(__m128 const& a,
                                   __m128 const& b,
                                   __m128 const& c)
    {
        // (2a0 b0 c3 + -2a0 b2 c1 + 2a0 b3 c2 + 2a1 b0 c2 + 2a1 b1 c1 +
        //  -2a1 b3 c3 + 2a2 b0 c1 + -2a2 b1 c2 + 2a2 b2 c3 +
        //  a3 (b0^2 + b1^2 + b2^2 + b3^2)) e0 +
        //
        // (-2a0 b0 b2 + 2a0 b1 b3 + 2a1 b0 b1 + 2a1 b2 b3 +
        //  a2 (b0^2 - b1^2 - b2^2 + b3^2)) e1 +
        //
        // (2a0 b0 b3 + 2a0 b1 b2 - 2a2 b0 b1 + 2a2 b2 b3 +
        //  a1 (b0^2 - b1^2 + b2^2 - b3^2)) e2 +
        //
        // (-2a1 b0 b3 + 2a1 b1 b2 + 2a2 b0 b2 + 2a2 b1 b3 +
        // a0 (b0^2 + b1^2 - b2^2 - b3^2)) e3
        //
        // Note the similarity between the results here and the rotor and
        // translator applied to the plane. The e1, e2, and e3 components do not
        // participate in the translation and are identical to the result after
        // the rotor was applied to the plane. The e0 component is displaced
        // similarly to the manner in which it is displaced after application of
        // a translator.
    }

    // Apply a rotor to a point.
    inline auto PRS_VEC_CALL sw31(__m128 const& a, __m128 const& b) noexcept
    {
        // (b0 + b1*e12 + b2*e31 + b3*e23) *
        //   (a0*e123 + a1*e021 + a2*e013 + a3*e032) *
        //   (b0 - b1*e12 - b2*e31 - b3*e23) =
        //
        // a0*(b0^2 + b1^2 + b2^2 + b3^2)*e123 +
        //
        // (2*(-a2*b0*b3 + a2*b1*b2 + a3*b0*b2 + a3*b1*b3)
        //  + a1*(b0^2 + b1^2 - b2^2 - b3^2))*e021 +
        //
        // (2*(-a3*b0*b1 + a1*b0*b3 + a1*b1*b2 + a3*b2*b3)
        //  + a2*(b0^2 + b2^2 - b1^2 - b3^2))*e013 +
        //
        // (2*(-a1*b0*b2 + a1*b1*b3 + a2*b0*b1 + a2*b2*b3)
        //  + a3*(b0^2 + b3^2 - b1^2 - b2^2))*e032
    }

    // Apply a translator to a point.
    // Assumes e0123 component of p2 is exactly 0
    // p2: (e0123, e01, e02, e03)
    // p3: (e123, e021, e013, e032)
    // b * a * ~b
    inline auto PRS_VEC_CALL sw32(__m128 const& a, __m128 const& b) noexcept
    {
        // (1 + b1*e01 + b2*e02 + b3*e03) *
        //   (a0*e123 + a1*e021 + a2*e013 + a3*e032) *
        //   (1 - b1*e01 - b2*e02 - b3*e03) =
        //
        // a0*1e123
        // + (a1 - 2*a0*b3)*e021
        // + (a2 - 2*a0*b2)*e013
        // + (a3 - 2*a0*b1)*e023

        // (_, a0*b3, a0*b2, a0*b1)
        __m128 tmp
            = _mm_mul_ps(PRS_SWIZZLE(a, 0, 0, 0, 0), PRS_SWIZZLE(b, 1, 2, 3, 0));
        tmp = _mm_mul_ps(_mm_set1_ps(-2.f), tmp);
        // Mask low component
        tmp = _mm_mul_ps(_mm_set_ps(1.f, 1.f, 1.f, 0.f), tmp);
        tmp = _mm_sub_ps(a, tmp);
        return tmp;
    }

    // Apply a motor to a point
    inline auto PRS_VEC_CALL sw312(__m128 const& a,
                                   __m128 const& b,
                                   __m128 const& c) noexcept
    {
        // (2a0(-b0 c3 - b2 c1 + b3 c2) +
        //  2a2(-b0 b3 + b1 b2) +
        //  2a3(b0 b2 + b1 b3) +
        //  a1(b0^2 + b1^2 - b2^2 - b3^2)) e021 +
        //
        // (2a0(-b0 c2 + b1 c1 - b3 c3) +
        //  2a1(b0 b3 + b1 b2) +
        //  2a3(-b0 b1 + b2 b3) +
        //  a2(b0^2 - b1^2 + b2^2 - b3^2)) e013 +
        //
        // (2a0(-b0 c1 - b1 c2 + b2 c3) +
        //  2a1(-b0 b2 + b1 b3) +
        //  2a2(b0 b1 +  b2 b3) +
        //  a3(-b0^2 + b1^2 + b2^2 - b3^2)) e023 +
        //
        // a0(b0^2 + b1^2 + b2^2 + b3^2) e123
        //
        // Sanity check: For c1 = c2 = c3 = 0, the computation becomes
        // indistinguishable from a rotor application and the homogeneous
        // coordinate a0 does not participate.
    }
} // namespace detail
} // namespace prs