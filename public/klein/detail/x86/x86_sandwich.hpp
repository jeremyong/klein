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

    // Reflect a plane through another plane
    // b * a * b
    KLN_INLINE void KLN_VEC_CALL sw00(__m128 a, __m128 b, __m128& p0_out)
    {
        // (2a0(a2 b2 + a3 b3 + a1 b1) - b0(a1^2 + a2^2 + a3^2)) e0 +
        // (2a1(a2 b2 + a3 b3)         + b1(a1^2 - a2^2 - a3^2)) e1 +
        // (2a2(a3 b3 + a1 b1)         + b2(a2^2 - a3^2 - a1^2)) e2 +
        // (2a3(a1 b1 + a2 b2)         + b3(a3^2 - a1^2 - a2^2)) e3

        __m128 a_zzwy = KLN_SWIZZLE(a, 1, 3, 2, 2);
        __m128 a_wwyz = KLN_SWIZZLE(a, 2, 1, 3, 3);

        // Left block
        __m128 tmp = _mm_mul_ps(a_zzwy, KLN_SWIZZLE(b, 1, 3, 2, 2));
        tmp = _mm_add_ps(tmp, _mm_mul_ps(a_wwyz, KLN_SWIZZLE(b, 2, 1, 3, 3)));

        __m128 a1 = _mm_movehdup_ps(a);
        __m128 b1 = _mm_movehdup_ps(b);
        tmp       = _mm_add_ss(tmp, _mm_mul_ss(a1, b1));
        tmp       = _mm_mul_ps(tmp, _mm_add_ps(a, a));

        // Right block
        __m128 a_yyzw = KLN_SWIZZLE(a, 3, 2, 1, 1);
        __m128 tmp2 = _mm_xor_ps(_mm_mul_ps(a_yyzw, a_yyzw), _mm_set_ss(-0.f));
        tmp2        = _mm_sub_ps(tmp2, _mm_mul_ps(a_zzwy, a_zzwy));
        tmp2        = _mm_sub_ps(tmp2, _mm_mul_ps(a_wwyz, a_wwyz));
        tmp2        = _mm_mul_ps(tmp2, b);

        p0_out = _mm_add_ps(tmp, tmp2);
    }

    KLN_INLINE void KLN_VEC_CALL sw10(__m128 a,
                                      __m128 b,
                                      __m128& KLN_RESTRICT p1,
                                      __m128& KLN_RESTRICT p2)
    {
        //                       b0(a1^2 + a2^2 + a3^2) +
        // (2a3(a1 b1 + a2 b2) + b3(a3^2 - a1^2 - a2^2)) e12 +
        // (2a1(a2 b2 + a3 b3) + b1(a1^2 - a2^2 - a3^2)) e23 +
        // (2a2(a3 b3 + a1 b1) + b2(a2^2 - a3^2 - a1^2)) e31 +
        //
        // 2a0(a1 b2 - a2 b1) e03
        // 2a0(a2 b3 - a3 b2) e01 +
        // 2a0(a3 b1 - a1 b3) e02 +

        __m128 a_zyzw = KLN_SWIZZLE(a, 3, 2, 1, 2);
        __m128 a_ywyz = KLN_SWIZZLE(a, 2, 1, 3, 1);
        __m128 a_wzwy = KLN_SWIZZLE(a, 1, 3, 2, 3);

        __m128 b_xzwy = KLN_SWIZZLE(b, 1, 3, 2, 0);

        __m128 two_zero = _mm_set_ps(2.f, 2.f, 2.f, 0.f);
        p1              = _mm_mul_ps(a, b);
        p1              = _mm_add_ps(p1, _mm_mul_ps(a_wzwy, b_xzwy));
        p1              = _mm_mul_ps(p1, _mm_mul_ps(a_ywyz, two_zero));

        __m128 tmp = _mm_mul_ps(a_zyzw, a_zyzw);
        tmp        = _mm_add_ps(tmp, _mm_mul_ps(a_wzwy, a_wzwy));
        tmp        = _mm_xor_ps(tmp, _mm_set_ss(-0.f));
        tmp        = _mm_sub_ps(_mm_mul_ps(a_ywyz, a_ywyz), tmp);
        tmp        = _mm_mul_ps(KLN_SWIZZLE(b, 2, 1, 3, 0), tmp);

        p1 = KLN_SWIZZLE(_mm_add_ps(p1, tmp), 1, 3, 2, 0);

        p2 = _mm_mul_ps(a_zyzw, b_xzwy);
        p2 = _mm_sub_ps(p2, _mm_mul_ps(a_wzwy, b));
        p2 = _mm_mul_ps(p2, _mm_mul_ps(KLN_SWIZZLE(a, 0, 0, 0, 0), two_zero));
        p2 = KLN_SWIZZLE(p2, 1, 3, 2, 0);
    }

    KLN_INLINE void KLN_VEC_CALL sw20(__m128 a, __m128 b, __m128& p2)
    {
        //                       -b0(a1^2 + a2^2 + a3^2) e0123 +
        // (-2a3(a1 b1 + a2 b2) + b3(a1^2 + a2^2 - a3^2)) e03
        // (-2a1(a2 b2 + a3 b3) + b1(a2^2 + a3^2 - a1^2)) e01 +
        // (-2a2(a3 b3 + a1 b1) + b2(a3^2 + a1^2 - a2^2)) e02 +

        __m128 a_zzwy = KLN_SWIZZLE(a, 1, 3, 2, 2);
        __m128 a_wwyz = KLN_SWIZZLE(a, 2, 1, 3, 3);

        p2 = _mm_mul_ps(a, b);
        p2 = _mm_add_ps(p2, _mm_mul_ps(a_zzwy, KLN_SWIZZLE(b, 1, 3, 2, 0)));
        p2 = _mm_mul_ps(
            p2, _mm_mul_ps(a_wwyz, _mm_set_ps(-2.f, -2.f, -2.f, 0.f)));

        __m128 a_yyzw = KLN_SWIZZLE(a, 3, 2, 1, 1);
        __m128 tmp    = _mm_mul_ps(a_yyzw, a_yyzw);
        tmp           = _mm_xor_ps(
            _mm_set_ss(-0.f), _mm_add_ps(tmp, _mm_mul_ps(a_zzwy, a_zzwy)));
        tmp = _mm_sub_ps(tmp, _mm_mul_ps(a_wwyz, a_wwyz));
        p2  = _mm_add_ps(p2, _mm_mul_ps(tmp, KLN_SWIZZLE(b, 2, 1, 3, 0)));
        p2  = KLN_SWIZZLE(p2, 1, 3, 2, 0);
    }

    KLN_INLINE void KLN_VEC_CALL sw30(__m128 a, __m128 b, __m128& p3_out)
    {
        //                                b0(a1^2 + a2^2 + a3^2)  e123 +
        // (-2a1(a0 b0 + a3 b3 + a2 b2) + b1(a2^2 + a3^2 - a1^2)) e032 +
        // (-2a2(a0 b0 + a1 b1 + a3 b3) + b2(a3^2 + a1^2 - a2^2)) e013 +
        // (-2a3(a0 b0 + a2 b2 + a1 b1) + b3(a1^2 + a2^2 - a3^2)) e021

        __m128 a_zwyz = KLN_SWIZZLE(a, 2, 1, 3, 2);
        __m128 a_yzwy = KLN_SWIZZLE(a, 1, 3, 2, 1);

        p3_out
            = _mm_mul_ps(KLN_SWIZZLE(a, 0, 0, 0, 0), KLN_SWIZZLE(b, 0, 0, 0, 0));
        p3_out
            = _mm_add_ps(p3_out, _mm_mul_ps(a_zwyz, KLN_SWIZZLE(b, 2, 1, 3, 0)));
        p3_out
            = _mm_add_ps(p3_out, _mm_mul_ps(a_yzwy, KLN_SWIZZLE(b, 1, 3, 2, 0)));
        p3_out = _mm_mul_ps(
            p3_out, _mm_mul_ps(a, _mm_set_ps(-2.f, -2.f, -2.f, 0.f)));

        __m128 tmp    = _mm_mul_ps(a_yzwy, a_yzwy);
        tmp           = _mm_add_ps(tmp, _mm_mul_ps(a_zwyz, a_zwyz));
        __m128 a_wyzw = KLN_SWIZZLE(a, 3, 2, 1, 3);
        tmp           = _mm_sub_ps(
            tmp, _mm_xor_ps(_mm_mul_ps(a_wyzw, a_wyzw), _mm_set_ss(-0.f)));

        p3_out = _mm_add_ps(p3_out, _mm_mul_ps(b, tmp));
    }

    // Apply a translator to a plane.
    // Assumes e0123 component of p2 is exactly 0
    // p0: (e0, e1, e2, e3)
    // p2: (e0123, e01, e02, e03)
    // b * a * ~b
    // The low component of p2 is expected to be the scalar component instead
    KLN_INLINE __m128 KLN_VEC_CALL sw02(__m128 a, __m128 b)
    {
        // (a0 b0^2 + 2a1 b0 b1 + 2a2 b0 b2 + 2a3 b0 b3) e0 +
        // (a1 b0^2) e1 +
        // (a2 b0^2) e2 +
        // (a3 b0^2) e3
        //
        // Because the plane is projectively equivalent on multiplication by a
        // scalar, we can divide the result through by b0^2
        //
        // (a0 + 2a1 b1 / b0 + 2a2 b2 / b0 + 2a3 b3 / b0) e0 +
        // a1 e1 +
        // a2 e2 +
        // a3 e3
        //
        // The additive term clearly contains a dot product between the plane's
        // normal and the translation axis, demonstrating that the plane
        // "doesn't care" about translations along its span. More precisely, the
        // plane translates by the projection of the translator on the plane's
        // normal.

        // a1*b1 + a2*b2 + a3*b3 stored in the low component of tmp
        __m128 tmp = hi_dp(a, b);

        __m128 inv_b = rcp_nr1(b);
        // 2 / b0
        inv_b = _mm_add_ss(inv_b, inv_b);
        inv_b = _mm_and_ps(inv_b, _mm_castsi128_ps(_mm_set_epi32(0, 0, 0, -1)));
        tmp   = _mm_mul_ss(tmp, inv_b);

        // Add to the plane
        return _mm_add_ps(a, tmp);
    }

    // Apply a translator to a line
    // a := p1 input
    // d := p2 input
    // c := p2 translator
    // out points to the start address of a line (p1, p2)
    KLN_INLINE void KLN_VEC_CALL swL2(__m128 a, __m128 d, __m128 c, __m128* out)
    {
        // a0 +
        // a1 e23 +
        // a2 e31 +
        // a3 e12 +
        //
        // (2a0 c0 + d0) e0123 +
        // (2(a2 c3 - a3 c2 - a1 c0) + d1) e01 +
        // (2(a3 c1 - a1 c3 - a2 c0) + d2) e02 +
        // (2(a1 c2 - a2 c1 - a3 c0) + d3) e03

        __m128& p1_out = *out;
        __m128& p2_out = *(out + 1);

        p1_out = a;

        p2_out
            = _mm_mul_ps(KLN_SWIZZLE(a, 1, 3, 2, 0), KLN_SWIZZLE(c, 2, 1, 3, 0));

        // Add and subtract the same quantity in the low component to produce a
        // cancellation
        p2_out = _mm_sub_ps(
            p2_out,
            _mm_mul_ps(KLN_SWIZZLE(a, 2, 1, 3, 0), KLN_SWIZZLE(c, 1, 3, 2, 0)));
        p2_out = _mm_sub_ps(p2_out,
                            _mm_xor_ps(_mm_mul_ps(a, KLN_SWIZZLE(c, 0, 0, 0, 0)),
                                       _mm_set_ss(-0.f)));
        p2_out = _mm_add_ps(p2_out, p2_out);
        p2_out = _mm_add_ps(p2_out, d);
    }

    // Apply a translator to a point.
    // Assumes e0123 component of p2 is exactly 0
    // p2: (e0123, e01, e02, e03)
    // p3: (e123, e032, e013, e021)
    // b * a * ~b
    KLN_INLINE __m128 KLN_VEC_CALL sw32(__m128 a, __m128 b) noexcept
    {
        // a0 e123 +
        // (a1 - 2 a0 b1) e032 +
        // (a2 - 2 a0 b2) e013 +
        // (a3 - 2 a0 b3) e021

        __m128 tmp = _mm_mul_ps(KLN_SWIZZLE(a, 0, 0, 0, 0), b);
        tmp        = _mm_mul_ps(_mm_set_ps(-2.f, -2.f, -2.f, 0.f), tmp);
        tmp        = _mm_add_ps(a, tmp);
        return tmp;
    }

#if __cplusplus >= 201703L
    // Apply a motor to a motor (works on lines as well)
    // in points to the start of an array of motor inputs (alternating p1 and
    // p2) out points to the start of an array of motor outputs (alternating p1
    // and p2)
    //
    // Note: in and out are permitted to alias iff a == out.
    template <bool Variadic, bool Translate, bool InputP2>
    KLN_INLINE void KLN_VEC_CALL swMM(__m128 const* KLN_RESTRICT in,
                                      __m128 const& KLN_RESTRICT b,
                                      [[maybe_unused]] __m128 const* KLN_RESTRICT c,
                                      __m128* out,
                                      size_t count = 0) noexcept
    {
        // p1 block
        // a0(b0^2 + b1^2 + b2^2 + b3^2) +
        // (a1(b1^2 + b0^2 - b3^2 - b2^2) +
        //     2a2(b0 b3 + b1 b2) + 2a3(b1 b3 - b0 b2)) e23 +
        // (a2(b2^2 + b0^2 - b1^2 - b3^2) +
        //     2a3(b0 b1 + b2 b3) + 2a1(b2 b1 - b0 b3)) e31
        // (a3(b3^2 + b0^2 - b2^2 - b1^2) +
        //     2a1(b0 b2 + b3 b1) + 2a2(b3 b2 - b0 b1)) e12 +

        __m128 b_xwyz   = KLN_SWIZZLE(b, 2, 1, 3, 0);
        __m128 b_xzwy   = KLN_SWIZZLE(b, 1, 3, 2, 0);
        __m128 b_yxxx   = KLN_SWIZZLE(b, 0, 0, 0, 1);
        __m128 b_yxxx_2 = _mm_mul_ps(b_yxxx, b_yxxx);

        __m128 tmp   = _mm_mul_ps(b, b);
        tmp          = _mm_add_ps(tmp, b_yxxx_2);
        __m128 b_tmp = KLN_SWIZZLE(b, 2, 1, 3, 2);
        __m128 tmp2  = _mm_mul_ps(b_tmp, b_tmp);
        b_tmp        = KLN_SWIZZLE(b, 1, 3, 2, 3);
        tmp2         = _mm_add_ps(tmp2, _mm_mul_ps(b_tmp, b_tmp));
        tmp          = _mm_sub_ps(tmp, _mm_xor_ps(tmp2, _mm_set_ss(-0.f)));
        // tmp needs to be scaled by a and set to p1_out

        __m128 b_xxxx = KLN_SWIZZLE(b, 0, 0, 0, 0);
        __m128 scale  = _mm_set_ps(2.f, 2.f, 2.f, 0.f);
        tmp2          = _mm_mul_ps(b_xxxx, b_xwyz);
        tmp2          = _mm_add_ps(tmp2, _mm_mul_ps(b, b_xzwy));
        tmp2          = _mm_mul_ps(tmp2, scale);
        // tmp2 needs to be scaled by (a0, a2, a3, a1) and added to p1_out

        __m128 tmp3 = _mm_mul_ps(b, b_xwyz);
        tmp3        = _mm_sub_ps(tmp3, _mm_mul_ps(b_xxxx, b_xzwy));
        tmp3        = _mm_mul_ps(tmp3, scale);
        // tmp3 needs to be scaled by (a0, a3, a1, a2) and added to p1_out

        // p2 block
        // (d coefficients are the components of the input line p2)
        // (2a0(b0 c0 - b1 c1 - b2 c2 - b3 c3) +
        //  d0(b1^2 + b0^2 + b2^2 + b3^2)) e0123 +
        //
        // (2a1(b1 c1 - b0 c0 - b3 c3 - b2 c2) +
        //  2a3(b1 c3 + b2 c0 + b3 c1 - b0 c2) +
        //  2a2(b1 c2 + b0 c3 + b2 c1 - b3 c0) +
        //  2d2(b0 b3 + b2 b1) +
        //  2d3(b1 b3 - b0 b2) +
        //  d1(b0^2 + b1^2 - b3^2 - b2^2)) e01 +
        //
        // (2a2(b2 c2 - b0 c0 - b3 c3 - b1 c1) +
        //  2a1(b2 c1 + b3 c0 + b1 c2 - b0 c3) +
        //  2a3(b2 c3 + b0 c1 + b3 c2 - b1 c0) +
        //  2d3(b0 b1 + b3 b2) +
        //  2d1(b2 b1 - b0 b3) +
        //  d2(b0^2 + b2^2 - b1^2 - b3^2)) e02 +
        //
        // (2a3(b3 c3 - b0 c0 - b1 c1 - b2 c2) +
        //  2a2(b3 c2 + b1 c0 + b2 c3 - b0 c1) +
        //  2a1(b3 c1 + b0 c2 + b1 c3 - b2 c0) +
        //  2d1(b0 b2 + b1 b3) +
        //  2d2(b3 b2 - b0 b1) +
        //  d3(b0^2 + b3^2 - b2^2 - b1^2)) e03

        // Rotation

        // tmp scaled by d and added to p2
        // tmp2 scaled by (d0, d2, d3, d1) and added to p2
        // tmp3 scaled by (d0, d3, d1, d2) and added to p2

        // Translation
        [[maybe_unused]] __m128 tmp4; // scaled by a and added to p2
        [[maybe_unused]] __m128 tmp5; // scaled by (a0, a3, a1, a2), added to p2
        [[maybe_unused]] __m128 tmp6; // scaled by (a0, a2, a3, a1), added to p2

        if constexpr (Translate)
        {
            __m128 czero  = KLN_SWIZZLE(*c, 0, 0, 0, 0);
            __m128 c_xzwy = KLN_SWIZZLE(*c, 1, 3, 2, 0);
            __m128 c_xwyz = KLN_SWIZZLE(*c, 2, 1, 3, 0);

            tmp4 = _mm_mul_ps(b, *c);
            tmp4 = _mm_sub_ps(
                tmp4, _mm_mul_ps(b_yxxx, KLN_SWIZZLE(*c, 0, 0, 0, 1)));
            tmp4 = _mm_sub_ps(tmp4,
                              _mm_mul_ps(KLN_SWIZZLE(b, 1, 3, 3, 2),
                                         KLN_SWIZZLE(*c, 1, 3, 3, 2)));
            tmp4 = _mm_sub_ps(tmp4,
                              _mm_mul_ps(KLN_SWIZZLE(b, 2, 1, 2, 3),
                                         KLN_SWIZZLE(*c, 2, 1, 2, 3)));
            tmp4 = _mm_add_ps(tmp4, tmp4);

            tmp5 = _mm_mul_ps(b, c_xwyz);
            tmp5 = _mm_add_ps(tmp5, _mm_mul_ps(b_xzwy, czero));
            tmp5 = _mm_add_ps(tmp5, _mm_mul_ps(b_xwyz, *c));
            tmp5 = _mm_sub_ps(tmp5, _mm_mul_ps(b_xxxx, c_xzwy));
            tmp5 = _mm_mul_ps(tmp5, scale);

            tmp6 = _mm_mul_ps(b, c_xzwy);
            tmp6 = _mm_add_ps(tmp6, _mm_mul_ps(b_xxxx, c_xwyz));
            tmp6 = _mm_add_ps(tmp6, _mm_mul_ps(b_xzwy, *c));
            tmp6 = _mm_sub_ps(tmp6, _mm_mul_ps(b_xwyz, czero));
            tmp6 = _mm_mul_ps(tmp6, scale);
        }

        size_t limit            = Variadic ? count : 1;
        constexpr size_t stride = InputP2 ? 2 : 1;
        for (size_t i = 0; i != limit; ++i)
        {
            __m128 const& p1_in = in[stride * i]; // a
            __m128 p1_in_xzwy   = KLN_SWIZZLE(p1_in, 1, 3, 2, 0);
            __m128 p1_in_xwyz   = KLN_SWIZZLE(p1_in, 2, 1, 3, 0);

            __m128& p1_out = out[stride * i];

            p1_out = _mm_mul_ps(tmp, p1_in);
            p1_out = _mm_add_ps(p1_out, _mm_mul_ps(tmp2, p1_in_xzwy));
            p1_out = _mm_add_ps(p1_out, _mm_mul_ps(tmp3, p1_in_xwyz));

            if constexpr (InputP2)
            {
                __m128 const& p2_in = in[2 * i + 1]; // d
                __m128& p2_out      = out[2 * i + 1];
                p2_out              = _mm_mul_ps(tmp, p2_in);
                p2_out              = _mm_add_ps(
                    p2_out, _mm_mul_ps(tmp2, KLN_SWIZZLE(p2_in, 1, 3, 2, 0)));
                p2_out = _mm_add_ps(
                    p2_out, _mm_mul_ps(tmp3, KLN_SWIZZLE(p2_in, 2, 1, 3, 0)));
            }

            // If what is being applied is a rotor, the non-directional
            // components of the line are left untouched
            if constexpr (Translate)
            {
                __m128& p2_out = out[2 * i + 1];
                p2_out         = _mm_add_ps(p2_out, _mm_mul_ps(tmp4, p1_in));
                p2_out = _mm_add_ps(p2_out, _mm_mul_ps(tmp5, p1_in_xwyz));
                p2_out = _mm_add_ps(p2_out, _mm_mul_ps(tmp6, p1_in_xzwy));
            }
        }
    }

    // Apply a motor to a plane
    // a := p0
    // b := p1
    // c := p2
    // If Translate is false, c is ignored (rotor application).
    // If Variadic is true, a and out must point to a contiguous block of memory
    // equivalent to __m128[count]
    template <bool Variadic = false, bool Translate = true>
    KLN_INLINE void KLN_VEC_CALL sw012(__m128 const* KLN_RESTRICT a,
                                       __m128 b,
                                       [[maybe_unused]] __m128 const* KLN_RESTRICT c,
                                       __m128* out,
                                       size_t count = 0) noexcept
    {
        // LSB
        //
        // (2a3(b0 c3 + b1 c2 + b3 c0 - b2 c1) +
        //  2a2(b0 c2 + b3 c1 + b2 c0 - b1 c3) +
        //  2a1(b0 c1 + b2 c3 + b1 c0 - b3 c2) +
        //  a0 (b2^2 + b1^2 + b0^2 + b3^2)) e0 +
        //
        // (2a2(b0 b3 + b2 b1) +
        //  2a3(b1 b3 - b0 b2) +
        //  a1 (b0^2 + b1^2 - b3^2 - b2^2)) e1 +
        //
        // (2a3(b0 b1 + b3 b2) +
        //  2a1(b2 b1 - b0 b3) +
        //  a2 (b0^2 + b2^2 - b1^2 - b3^2)) e2 +
        //
        // (2a1(b0 b2 + b1 b3) +
        //  2a2(b3 b2 - b0 b1) +
        //  a3 (b0^2 + b3^2 - b2^2 - b1^2)) e3
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
        __m128 dc_scale = _mm_set_ps(2.f, 2.f, 2.f, 1.f);
        __m128 b_xwyz   = KLN_SWIZZLE(b, 2, 1, 3, 0);
        __m128 b_xzwy   = KLN_SWIZZLE(b, 1, 3, 2, 0);
        __m128 b_xxxx   = KLN_SWIZZLE(b, 0, 0, 0, 0);

        __m128 tmp1
            = _mm_mul_ps(KLN_SWIZZLE(b, 0, 0, 0, 2), KLN_SWIZZLE(b, 2, 1, 3, 2));
        tmp1 = _mm_add_ps(
            tmp1,
            _mm_mul_ps(KLN_SWIZZLE(b, 1, 3, 2, 1), KLN_SWIZZLE(b, 3, 2, 1, 1)));
        // Scale later with (a0, a2, a3, a1)
        tmp1 = _mm_mul_ps(tmp1, dc_scale);

        __m128 tmp2 = _mm_mul_ps(b, b_xwyz);

        tmp2 = _mm_sub_ps(tmp2,
                          _mm_xor_ps(_mm_set_ss(-0.f),
                                     _mm_mul_ps(KLN_SWIZZLE(b, 0, 0, 0, 3),
                                                KLN_SWIZZLE(b, 1, 3, 2, 3))));
        // Scale later with (a0, a3, a1, a2)
        tmp2 = _mm_mul_ps(tmp2, dc_scale);

        // Alternately add and subtract to improve low component stability
        __m128 tmp3 = _mm_mul_ps(b, b);
        tmp3        = _mm_sub_ps(tmp3, _mm_mul_ps(b_xwyz, b_xwyz));
        tmp3        = _mm_add_ps(tmp3, _mm_mul_ps(b_xxxx, b_xxxx));
        tmp3        = _mm_sub_ps(tmp3, _mm_mul_ps(b_xzwy, b_xzwy));
        // Scale later with a

        // Compute
        // 0 * _ +
        // 2a1(b0 c1 + b2 c3 + b1 c0 - b3 c2) +
        // 2a2(b0 c2 + b3 c1 + b2 c0 - b1 c3) +
        // 2a3(b0 c3 + b1 c2 + b3 c0 - b2 c1)
        // by decomposing into four vectors, factoring out the a components

        [[maybe_unused]] __m128 tmp4;
        if constexpr (Translate)
        {
            tmp4 = _mm_mul_ps(b_xxxx, *c);
            tmp4 = _mm_add_ps(
                tmp4, _mm_mul_ps(b_xzwy, KLN_SWIZZLE(*c, 2, 1, 3, 0)));
            tmp4 = _mm_add_ps(tmp4, _mm_mul_ps(b, KLN_SWIZZLE(*c, 0, 0, 0, 0)));

            // NOTE: The high component of tmp4 is meaningless here
            tmp4 = _mm_sub_ps(
                tmp4, _mm_mul_ps(b_xwyz, KLN_SWIZZLE(*c, 1, 3, 2, 0)));
            tmp4 = _mm_mul_ps(tmp4, dc_scale);
        }

        // The temporaries (tmp1, tmp2, tmp3, tmp4) strictly only have a
        // dependence on b and c.

        size_t limit = Variadic ? count : 1;
        for (size_t i = 0; i != limit; ++i)
        {
            // Compute the lower block for components e1, e2, and e3
            __m128& p = out[i];
            p         = _mm_mul_ps(tmp1, KLN_SWIZZLE(a[i], 1, 3, 2, 0));
            p = _mm_add_ps(p, _mm_mul_ps(tmp2, KLN_SWIZZLE(a[i], 2, 1, 3, 0)));
            p = _mm_add_ps(p, _mm_mul_ps(tmp3, a[i]));

            if constexpr (Translate)
            {
                __m128 tmp5 = hi_dp(tmp4, a[i]);
                p           = _mm_add_ps(p, tmp5);
            }
        }
    }

    // Apply a motor to a point
    template <bool Variadic, bool Translate>
    KLN_INLINE void KLN_VEC_CALL sw312(__m128 const* KLN_RESTRICT a,
                                       __m128 b,
                                       [[maybe_unused]] __m128 const* KLN_RESTRICT c,
                                       __m128* out,
                                       size_t count = 0) noexcept
    {
        // LSB
        // a0(b1^2 + b0^2 + b2^2 + b3^2) e123 +
        //
        // (2a0(b2 c3 - b0 c1 - b3 c2 - b1 c0) +
        //  2a3(b1 b3 - b0 b2) +
        //  2a2(b0 b3 +  b2 b1) +
        //  a1(b0^2 + b1^2 - b3^2 - b2^2)) e032
        //
        // (2a0(b3 c1 - b0 c2 - b1 c3 - b2 c0) +
        //  2a1(b2 b1 - b0 b3) +
        //  2a3(b0 b1 + b3 b2) +
        //  a2(b0^2 + b2^2 - b1^2 - b3^2)) e013 +
        //
        // (2a0(b1 c2 - b0 c3 - b2 c1 - b3 c0) +
        //  2a2(b3 b2 - b0 b1) +
        //  2a1(b0 b2 + b1 b3) +
        //  a3(b0^2 + b3^2 - b2^2 - b1^2)) e021 +
        // MSB
        //
        // Sanity check: For c1 = c2 = c3 = 0, the computation becomes
        // indistinguishable from a rotor application and the homogeneous
        // coordinate a0 does not participate. As an additional sanity check,
        // note that for a normalized rotor and homogenous point, the e123
        // component will remain unity.

        __m128 two    = _mm_set_ps(2.f, 2.f, 2.f, 0.f);
        __m128 b_xxxx = KLN_SWIZZLE(b, 0, 0, 0, 0);
        __m128 b_xwyz = KLN_SWIZZLE(b, 2, 1, 3, 0);
        __m128 b_xzwy = KLN_SWIZZLE(b, 1, 3, 2, 0);

        __m128 tmp1 = _mm_mul_ps(b, b_xwyz);
        tmp1        = _mm_sub_ps(tmp1, _mm_mul_ps(b_xxxx, b_xzwy));
        tmp1        = _mm_mul_ps(tmp1, two);
        // tmp1 needs to be scaled by (_, a3, a1, a2)

        __m128 tmp2 = _mm_mul_ps(b_xxxx, b_xwyz);
        tmp2        = _mm_add_ps(tmp2, _mm_mul_ps(b_xzwy, b));
        tmp2        = _mm_mul_ps(tmp2, two);
        // tmp2 needs to be scaled by (_, a2, a3, a1)

        __m128 tmp3  = _mm_mul_ps(b, b);
        __m128 b_tmp = KLN_SWIZZLE(b, 0, 0, 0, 1);
        tmp3         = _mm_add_ps(tmp3, _mm_mul_ps(b_tmp, b_tmp));
        b_tmp        = KLN_SWIZZLE(b, 2, 1, 3, 2);
        __m128 tmp4  = _mm_mul_ps(b_tmp, b_tmp);
        b_tmp        = KLN_SWIZZLE(b, 1, 3, 2, 3);
        tmp4         = _mm_add_ps(tmp4, _mm_mul_ps(b_tmp, b_tmp));
        tmp3         = _mm_sub_ps(tmp3, _mm_xor_ps(tmp4, _mm_set_ss(-0.f)));
        // tmp3 needs to be scaled by (a0, a1, a2, a3)

        if constexpr (Translate)
        {
            tmp4 = _mm_mul_ps(b_xzwy, KLN_SWIZZLE(*c, 2, 1, 3, 0));
            tmp4 = _mm_sub_ps(tmp4, _mm_mul_ps(b_xxxx, *c));
            tmp4 = _mm_sub_ps(
                tmp4, _mm_mul_ps(b_xwyz, KLN_SWIZZLE(*c, 1, 3, 2, 0)));
            tmp4 = _mm_sub_ps(tmp4, _mm_mul_ps(b, KLN_SWIZZLE(*c, 0, 0, 0, 0)));

            // Mask low component and scale other components by 2
            tmp4 = _mm_mul_ps(tmp4, two);
            // tmp4 needs to be scaled by (_, a0, a0, a0)
        }

        size_t limit = Variadic ? count : 1;
        for (size_t i = 0; i != limit; ++i)
        {
            __m128& p = out[i];
            p         = _mm_mul_ps(tmp1, KLN_SWIZZLE(a[i], 2, 1, 3, 0));
            p = _mm_add_ps(p, _mm_mul_ps(tmp2, KLN_SWIZZLE(a[i], 1, 3, 2, 0)));
            p = _mm_add_ps(p, _mm_mul_ps(tmp3, a[i]));

            if constexpr (Translate)
            {
                p = _mm_add_ps(
                    p, _mm_mul_ps(tmp4, KLN_SWIZZLE(a[i], 0, 0, 0, 0)));
            }
        }
    }
#else
// Use header that avoids `if constexpr` usage
#    include "x86_sandwich_cxx11.inl"
#endif

    // Conjugate origin with motor. Unlike other operations the motor MUST be
    // normalized prior to usage b is the rotor component (p1) c is the
    // translator component (p2)
    KLN_INLINE __m128 swo12(__m128 b, __m128 c)
    {
        //  (b0^2 + b1^2 + b2^2 + b3^2) e123 +
        // 2(b2 c3 - b1 c0 - b0 c1 - b3 c2) e032 +
        // 2(b3 c1 - b2 c0 - b0 c2 - b1 c3) e013 +
        // 2(b1 c2 - b3 c0 - b0 c3 - b2 c1) e021

        __m128 tmp = _mm_mul_ps(b, KLN_SWIZZLE(c, 0, 0, 0, 0));
        tmp        = _mm_add_ps(tmp, _mm_mul_ps(KLN_SWIZZLE(b, 0, 0, 0, 0), c));
        tmp        = _mm_add_ps(
            tmp,
            _mm_mul_ps(KLN_SWIZZLE(b, 2, 1, 3, 0), KLN_SWIZZLE(c, 1, 3, 2, 0)));
        tmp = _mm_sub_ps(
            _mm_mul_ps(KLN_SWIZZLE(b, 1, 3, 2, 0), KLN_SWIZZLE(c, 2, 1, 3, 0)),
            tmp);
        tmp = _mm_mul_ps(tmp, _mm_set_ps(2.f, 2.f, 2.f, 0.f));

        // b0^2 + b1^2 + b2^2 + b3^2 assumed to equal 1
        // Set the low component to unity
        return _mm_add_ps(tmp, _mm_set_ss(1.f));
    }
} // namespace detail
} // namespace kln