// File: sandwich.hpp
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

    // Apply a translator to a plane.
    // Assumes e0123 component of p2 is exactly 0
    // p0: (e3, e2, e1, e0)
    // p2: (e0123, e01, e02, e03)
    // b * a * ~b
    inline auto KLN_VEC_CALL sw02(__m128 const& a, __m128 const& b)
    {
        // (1 + b1*e01 + b2*e02 + b3*e03) *
        //   (a3*e0 + a2*e1 + a1*e2 + a0*e3) *
        //   (1 - b1*e01 - b2*e02 - b3*e03) =
        //
        // (a3 + 2*a0*b3 + 2*a1*b2 + 2*a2*b1)*e0 + a2*e1 + a1*e2 + a0*e3

        // a0*b3 + a1*b2 + a2*b1 stored in the high component of tmp
        __m128 tmp = _mm_dp_ps(a, KLN_SWIZZLE(b, 0, 1, 2, 3), 0b01111000);

        // Scale by 2
        tmp = _mm_mul_ps(tmp, _mm_set1_ps(2.f));

        // Add to the plane
        return _mm_add_ps(a, tmp);
    }

    // Apply a motor to a plane
    // a := p0
    // b := p1
    // c := p2
    // If Translate is false, c is ignored (rotor application).
    // If Variadic is true, a and out must point to a contiguous block of memory
    // equivalent to __m128[count]
    template <bool Variadic = false, bool Translate = true>
    inline void KLN_VEC_CALL sw012(__m128 const* a,
                                   __m128 const& b,
                                   __m128 const* c,
                                   __m128* out,
                                   size_t count = 0)
    {
        // LSB
        //
        // (2a2(b0 b2 + b1 b3) +
        //  2a1(b1 b2 - b0 b3) +
        //  a0 (b0^2 + b1^2 - b2^2 - b3^2)) e3 +
        //
        // (2a0(b0 b3 + b1 b2) +
        //  2a2(b2 b3 - b0 b1) +
        //  a1 (b0^2 + b2^2 - b1^2 - b3^2)) e2 +
        //
        // (2a1(b0 b1 + b2 b3) +
        //  2a0(b1 b3 - b0 b2) +
        //  a2 (b0^2 + b3^2 - b1^2 - b2^2)) e1 +
        //
        // (2a0(b0 c3 + b3 c2 + b1 c0 - b2 c1) +
        //  2a1(b0 c2 + b1 c1 + b2 c0 - b3 c3) +
        //  2a2(b0 c1 + b2 c3 + b3 c0 - b1 c2) +
        //  a3 (b0^2 + b1^2 + b2^2 + b3^2)) e0
        //
        // MSB
        //
        // Note the similarity between the results here and the rotor and
        // translator applied to the plane. The e1, e2, and e3 components do not
        // participate in the translation and are identical to the result after
        // the rotor was applied to the plane. The e0 component is displaced
        // similarly to the manner in which it is displaced after application of
        // a translator.

        // Double-cover scale
        __m128 dc_scale = _mm_set_ps(1.f, 2.f, 2.f, 2.f);

        // MSB is e0
        // LSB -> MSB
        // (b0 b2, b0 b3, b0 b1, b0^2)
        __m128 tmp1
            = _mm_mul_ps(KLN_SWIZZLE(b, 0, 0, 0, 0), KLN_SWIZZLE(b, 0, 1, 3, 2));

        // Add (b1 b3, b1 b2, b2 b3, b1^2)
        tmp1 = _mm_add_ps(
            tmp1,
            _mm_mul_ps(KLN_SWIZZLE(b, 1, 2, 1, 1), KLN_SWIZZLE(b, 1, 3, 2, 3)));

        tmp1 = _mm_mul_ps(tmp1, dc_scale);

        // (b1 b2, b2 b3, b1 b3, b2^2)
        __m128 tmp2
            = _mm_mul_ps(KLN_SWIZZLE(b, 2, 1, 2, 1), KLN_SWIZZLE(b, 2, 3, 3, 2));

        // Add (-b0 b3, -b0 b1, -b0 b2, b3^2)
        tmp2 = _mm_add_ps(tmp2,
                          _mm_mul_ps(_mm_set_ps(1.f, -1.f, -1.f, -1.f),
                                     _mm_mul_ps(KLN_SWIZZLE(b, 3, 0, 0, 3), b)));

        tmp2 = _mm_mul_ps(tmp2, dc_scale);

        __m128 b_tmp = KLN_SWIZZLE(b, 0, 0, 0, 0);

        // (b0^2, b0^2, b0^2, b0^2)
        __m128 tmp3 = _mm_mul_ps(b_tmp, b_tmp);

        b_tmp = KLN_SWIZZLE(b, 1, 3, 2, 1);

        // Add (b1^2, b2^2, b3^2, b1^2)
        tmp3 = _mm_add_ps(tmp3, _mm_mul_ps(b_tmp, b_tmp));

        b_tmp = KLN_SWIZZLE(b, 2, 1, 1, 2);

        // Sub (b2^2, b1^2, b1^2, b_2^2)
        tmp3 = _mm_sub_ps(tmp3, _mm_mul_ps(b_tmp, b_tmp));

        b_tmp = KLN_SWIZZLE(b, 3, 2, 3, 3);

        // Sub (b3^2, b3^2, b2^2, b3^2)
        tmp3 = _mm_sub_ps(tmp3, _mm_mul_ps(b_tmp, b_tmp));

        // Mask high component
        tmp3 = _mm_mul_ps(_mm_set_ps(0.f, 1.f, 1.f, 1.f), tmp3);

        // Compute
        // 2a0(b0 c3 + b3 c2 + b1 c0 - b2 c1) +
        // 2a1(b1 c1 + b0 c2 + b2 c0 - b3 c3) +
        // 2a2(b2 c3 + b0 c1 + b3 c0 - b1 c2) +
        // 0 * (_)
        // by decomposing into four vectors, factoring out the a components
        //
        // (b0 c3, b1 c1, b2 c3, b3 c0)
        // Swizzle c here so that we don't have to swizzle tmp4 in the inner
        // loop later
        __m128 tmp4 = Translate ? _mm_mul_ps(b, KLN_SWIZZLE(*c, 0, 3, 1, 3))
                                : _mm_set1_ps(0.f);

        if constexpr (Translate)
        {
            // Add (b3 c2, b0 c2, b0 c1, b0 c0)
            tmp4 = _mm_add_ps(tmp4,
                              _mm_mul_ps(KLN_SWIZZLE(b, 0, 0, 0, 3),
                                         KLN_SWIZZLE(*c, 0, 1, 2, 2)));

            // Add (b1 c0, b2 c0, b3 c0, b0 c0)
            tmp4 = _mm_add_ps(tmp4,
                              _mm_mul_ps(KLN_SWIZZLE(b, 0, 3, 2, 1),
                                         KLN_SWIZZLE(*c, 0, 0, 0, 0)));

            // Sub (b2 c1, b3 c3, b1 c2, b0 c0)
            // NOTE: The high component of tmp4 is meaningless here
            tmp4 = _mm_sub_ps(tmp4,
                              _mm_mul_ps(KLN_SWIZZLE(b, 0, 1, 3, 2),
                                         KLN_SWIZZLE(*c, 0, 2, 3, 1)));

            tmp4 = _mm_mul_ps(tmp4, dc_scale);
        }

        // The temporaries (tmp1, tmp2, tmp3, tmp4) strictly only have a
        // dependence on b and c.

        if constexpr (Variadic)
        {
            for (size_t i = 0; i != count; ++i)
            {
                // Compute the lower block for components e1, e2, and e3
                __m128& p = out[i];
                p         = _mm_mul_ps(tmp1, KLN_SWIZZLE(a[i], 3, 1, 0, 2));
                p         = _mm_add_ps(
                    p, _mm_mul_ps(tmp2, KLN_SWIZZLE(a[i], 3, 0, 2, 1)));
                p = _mm_add_ps(p, _mm_mul_ps(tmp3, a[i]));

                if constexpr (Translate)
                {
                    __m128 tmp5 = _mm_dp_ps(tmp4, a[i], 0b01111000);
                    p           = _mm_add_ps(p, tmp5);
                }
            }
        }
        else
        {
            // Compute the lower block for components e1, e2, and e3
            __m128& p = *out;
            p         = _mm_mul_ps(tmp1, KLN_SWIZZLE(*a, 3, 1, 0, 2));
            p = _mm_add_ps(p, _mm_mul_ps(tmp2, KLN_SWIZZLE(*a, 3, 0, 2, 1)));
            p = _mm_add_ps(p, _mm_mul_ps(tmp3, *a));

            if constexpr (Translate)
            {
                __m128 tmp5 = _mm_dp_ps(tmp4, *a, 0b01111000);
                p           = _mm_add_ps(p, tmp5);
            }
        }
    }

    // Apply a translator to a point.
    // Assumes e0123 component of p2 is exactly 0
    // p2: (e0123, e01, e02, e03)
    // p3: (e123, e021, e013, e032)
    // b * a * ~b
    inline auto KLN_VEC_CALL sw32(__m128 const& a, __m128 const& b) noexcept
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
            = _mm_mul_ps(KLN_SWIZZLE(a, 0, 0, 0, 0), KLN_SWIZZLE(b, 1, 2, 3, 0));
        tmp = _mm_mul_ps(_mm_set1_ps(-2.f), tmp);
        // Mask low component
        tmp = _mm_mul_ps(_mm_set_ps(1.f, 1.f, 1.f, 0.f), tmp);
        tmp = _mm_add_ps(a, tmp);
        return tmp;
    }

    // Apply a motor to a point
    template <bool Variadic = false, bool Translate = true>
    inline void KLN_VEC_CALL sw312(__m128 const* a,
                                   __m128 const& b,
                                   __m128 const* c,
                                   __m128* out,
                                   size_t count = 0) noexcept
    {
        // LSB
        // a0(b0^2 + b1^2 + b2^2 + b3^2) e123 +
        //
        // (2a0(b3 c2 - b0 c3 - b2 c1 - b1 c0) +
        //  2a2(b1 b2 - b0 b3) +
        //  2a3(b0 b2 + b1 b3) +
        //  a1(b0^2 + b1^2 - b2^2 - b3^2)) e021 +
        //
        // (2a0(b1 c1 - b0 c2 - b3 c3 - b2 c0) +
        //  2a3(b2 b3 - b0 b1) +
        //  2a1(b0 b3 + b1 b2) +
        //  a2(b0^2 + b2^2 - b1^2 - b3^2)) e013 +
        //
        // (2a0(b2 c3 - b0 c1 - b1 c2 - b3 c0) +
        //  2a1(b1 b3 - b0 b2) +
        //  2a2(b0 b1 +  b2 b3) +
        //  a3(b0^2 + b3^2 - b1^2 - b2^2)) e032
        // MSB
        //
        // Sanity check: For c1 = c2 = c3 = 0, the computation becomes
        // indistinguishable from a rotor application and the homogeneous
        // coordinate a0 does not participate. As an additional sanity check,
        // note that for a normalized rotor and homogenous point, the e123
        // component will remain unity.

        __m128 two = _mm_set_ps(2.f, 2.f, 2.f, 0.f);

        // (_, b1 b2, b2 b3, b1 b3)
        __m128 tmp1 = _mm_mul_ps(KLN_SWIZZLE(b, 1, 3, 2, 0), b);
        // Sub (_, b0 b3, b0 b1, b0 b2)
        tmp1 = _mm_sub_ps(
            tmp1,
            _mm_mul_ps(KLN_SWIZZLE(b, 0, 0, 0, 0), KLN_SWIZZLE(b, 2, 1, 3, 0)));
        tmp1 = _mm_mul_ps(tmp1, two);
        // tmp1 needs to be scaled by (_, a2, a3, a1)

        // (_, b0 b2, b0 b3, b0 b1)
        __m128 tmp2
            = _mm_mul_ps(KLN_SWIZZLE(b, 0, 0, 0, 0), KLN_SWIZZLE(b, 1, 3, 2, 0));
        // Add (_, b1 b3, b2 b1, b3 b2)
        tmp2 = _mm_add_ps(tmp2, _mm_mul_ps(KLN_SWIZZLE(b, 2, 1, 3, 0), b));
        tmp2 = _mm_mul_ps(tmp2, two);
        // tmp2 needs to be scaled by (_, a3, a1, a2)

        __m128 b_tmp = KLN_SWIZZLE(b, 0, 0, 0, 0);
        // (b0^2, b0^2, b0^2, b0^2)
        __m128 tmp3 = _mm_mul_ps(b_tmp, b_tmp);
        b_tmp       = KLN_SWIZZLE(b, 3, 2, 1, 1);
        // Add (b1^2, b1^2, b2^2, b3^2)
        tmp3        = _mm_add_ps(tmp3, _mm_mul_ps(b_tmp, b_tmp));
        b_tmp       = KLN_SWIZZLE(b, 1, 1, 2, 2);
        __m128 tmp4 = _mm_mul_ps(b_tmp, b_tmp);
        b_tmp       = KLN_SWIZZLE(b, 2, 3, 3, 3);
        tmp4        = _mm_mul_ps(_mm_set_ps(1.f, 1.f, 1.f, -1.f),
                          _mm_add_ps(tmp4, _mm_mul_ps(b_tmp, b_tmp)));
        // Sub (-b2^2 + b3^2, b2^2 + b3^2, b1^2 + b3^2, b1^2 + b2^2)
        tmp3 = _mm_sub_ps(tmp3, tmp4);
        // tmp3 needs to be scaled by (a0, a1, a2, a3)

        if constexpr (Translate)
        {
            // (_, b3 c2, b1 c1, b2 c3)
            tmp4 = _mm_mul_ps(
                KLN_SWIZZLE(b, 2, 1, 3, 0), KLN_SWIZZLE(*c, 3, 1, 2, 0));

            // Sub (_, b0 c3, b0 c2, b0 c1)
            tmp4 = _mm_sub_ps(tmp4,
                              _mm_mul_ps(KLN_SWIZZLE(b, 0, 0, 0, 0),
                                         KLN_SWIZZLE(*c, 1, 2, 3, 0)));
            // Sub (_, b2 c1, b3 c3, b1 c2)
            tmp4 = _mm_sub_ps(tmp4,
                              _mm_mul_ps(KLN_SWIZZLE(b, 1, 3, 2, 0),
                                         KLN_SWIZZLE(*c, 2, 3, 1, 0)));

            // Sub (_, b1 c0, b2 c0, b3 c0)
            tmp4 = _mm_sub_ps(tmp4, _mm_mul_ps(b, KLN_SWIZZLE(*c, 0, 0, 0, 0)));

            // Mask low component and scale other components by 2
            tmp4 = _mm_mul_ps(tmp4, two);
            // tmp4 needs to be scaled by (_, a0, a0, a0)
        }

        if constexpr (Variadic)
        {
            for (size_t i = 0; i != count; ++i)
            {
                __m128& p = out[i];
                p         = _mm_mul_ps(tmp1, KLN_SWIZZLE(a[i], 1, 3, 2, 0));
                p         = _mm_add_ps(
                    p, _mm_mul_ps(tmp2, KLN_SWIZZLE(a[i], 2, 1, 3, 0)));
                p = _mm_add_ps(p, _mm_mul_ps(tmp3, a[i]));

                if constexpr (Translate)
                {
                    p = _mm_add_ps(
                        p, _mm_mul_ps(tmp4, KLN_SWIZZLE(a[i], 0, 0, 0, 0)));
                }
            }
        }
        else
        {
            __m128& p = *out;
            p         = _mm_mul_ps(tmp1, KLN_SWIZZLE(*a, 1, 3, 2, 0));
            p = _mm_add_ps(p, _mm_mul_ps(tmp2, KLN_SWIZZLE(*a, 2, 1, 3, 0)));
            p = _mm_add_ps(p, _mm_mul_ps(tmp3, *a));

            if constexpr (Translate)
            {
                p = _mm_add_ps(p, _mm_mul_ps(tmp4, KLN_SWIZZLE(*a, 0, 0, 0, 0)));
            }
        }
    }

    // Conjugate origin with motor. Unlike other operations the motor MUST be
    // normalized prior to usage b is the rotor component (p1) c is the
    // translator component (p2)
    inline __m128 swo12(__m128 const& b, __m128 const& c)
    {
        // Rearranged to eliminate a b swizzle
        //  (b1^2 + b0^2 + b2^2 + b3^2) e123 +
        // 2(b3 c2 - b1 c0 - b0 c3 - b2 c1) e021 +
        // 2(b1 c1 - b2 c0 - b0 c2 - b3 c3) e013 +
        // 2(b2 c3 - b3 c0 - b0 c1 - b1 c2) e032
        //
        // To eliminate a lot of unnecessary swizzling, the motor is expected to
        // be normalized such that (b0^2 + b1^2 + b2^2 + b3^2) = 1

        // (_, b1 c0, b2 c0, b3 c0)
        __m128 tmp = _mm_mul_ps(b, KLN_SWIZZLE(c, 0, 0, 0, 0));

        // Add (_, b0 c3, b0 c2, b0 c1)
        tmp = _mm_add_ps(
            tmp,
            _mm_mul_ps(KLN_SWIZZLE(b, 0, 0, 0, 0), KLN_SWIZZLE(c, 1, 2, 3, 0)));

        // Add (_, b2 c1, b3 c3, b1 c2)
        tmp = _mm_add_ps(
            tmp,
            _mm_mul_ps(KLN_SWIZZLE(b, 1, 3, 2, 0), KLN_SWIZZLE(c, 1, 3, 2, 0)));

        // Sub from (_, b3 c2, b1 c1, b2 c3)
        tmp = _mm_sub_ps(
            _mm_mul_ps(KLN_SWIZZLE(b, 2, 1, 3, 0), KLN_SWIZZLE(c, 3, 1, 2, 0)),
            tmp);

        tmp = _mm_mul_ps(tmp, _mm_set_ps(2.f, 2.f, 2.f, 0.f));

        // Set the low component to unity
        return _mm_add_ps(tmp, _mm_set_ss(1.f));
    }
} // namespace detail
} // namespace kln