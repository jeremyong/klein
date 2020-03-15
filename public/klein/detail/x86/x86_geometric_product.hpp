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
    KLN_INLINE void KLN_VEC_CALL gp00(__m128 a,
                                      __m128 b,
                                      __m128& KLN_RESTRICT p1_out,
                                      __m128& KLN_RESTRICT p2_out) noexcept
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
    // p3: (e123, e032, e013, e021)
    // p1: (1, e12, e31, e23)
    // p2: (e0123, e01, e02, e03)
    template <bool Flip>
    KLN_INLINE void KLN_VEC_CALL gp03(__m128 a,
                                      __m128 b,
                                      __m128& KLN_RESTRICT p1,
                                      __m128& KLN_RESTRICT p2) noexcept
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

        p1 = _mm_mul_ps(a, KLN_SWIZZLE(b, 0, 0, 0, 0));
#ifdef KLEIN_SSE_4_1
        p1 = _mm_blend_ps(p1, _mm_setzero_ps(), 1);
#else
        p1 = _mm_and_ps(p1, _mm_castsi128_ps(_mm_set_epi32(-1, -1, -1, 0)));
#endif

        // (_, a3 b2, a1 b3, a2 b1)
        p2 = _mm_mul_ps(KLN_SWIZZLE(a, 2, 1, 3, 0), KLN_SWIZZLE(b, 1, 3, 2, 0));
        p2 = _mm_sub_ps(
            p2,
            _mm_mul_ps(KLN_SWIZZLE(a, 1, 3, 2, 0), KLN_SWIZZLE(b, 2, 1, 3, 0)));

        // Compute a0 b0 + a1 b1 + a2 b2 + a3 b3 and store it in the low
        // component
        __m128 tmp = dp(a, b);

        tmp = _mm_xor_ps(tmp, _mm_set_ss(-0.f));

        p2 = _mm_add_ps(p2, tmp);
    }

    template <>
    KLN_INLINE void KLN_VEC_CALL gp03<false>(__m128 a,
                                             __m128 b,
                                             __m128& KLN_RESTRICT p1,
                                             __m128& KLN_RESTRICT p2) noexcept
    {
        p1 = _mm_mul_ps(a, KLN_SWIZZLE(b, 0, 0, 0, 0));
#ifdef KLEIN_SSE_4_1
        p1 = _mm_blend_ps(p1, _mm_setzero_ps(), 1);
#else
        p1 = _mm_and_ps(p1, _mm_castsi128_ps(_mm_set_epi32(-1, -1, -1, 0)));
#endif

        // (_, a3 b2, a1 b3, a2 b1)
        p2 = _mm_mul_ps(KLN_SWIZZLE(a, 2, 1, 3, 0), KLN_SWIZZLE(b, 1, 3, 2, 0));
        p2 = _mm_sub_ps(
            p2,
            _mm_mul_ps(KLN_SWIZZLE(a, 1, 3, 2, 0), KLN_SWIZZLE(b, 2, 1, 3, 0)));

        // Compute a0 b0 + a1 b1 + a2 b2 + a3 b3 and store it in the low
        // component
        __m128 tmp = dp(a, b);
        p2         = _mm_add_ps(p2, tmp);
    }

    // p1: (1, e23, e31, e12)
    KLN_INLINE void KLN_VEC_CALL gp11(__m128 a, __m128 b, __m128& p1_out) noexcept
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
        __m128 tmp1
            = _mm_mul_ps(KLN_SWIZZLE(a, 3, 2, 1, 2), KLN_SWIZZLE(b, 0, 0, 0, 2));

        __m128 tmp2
            = _mm_mul_ps(KLN_SWIZZLE(a, 2, 1, 3, 3), KLN_SWIZZLE(b, 1, 3, 2, 3));

        __m128 tmp = _mm_xor_ps(_mm_add_ps(tmp1, tmp2), _mm_set_ss(-0.f));

        p1_out = _mm_add_ps(p1_out, tmp);
    }

    // p3: (e123, e021, e013, e032)
    // p2: (e0123, e01, e02, e03)
    KLN_INLINE void KLN_VEC_CALL gp33(__m128 a, __m128 b, __m128& p2) noexcept
    {
        // (-a0 b0) +
        // (-a0 b1 + a1 b0) e01 +
        // (-a0 b2 + a2 b0) e02 +
        // (-a0 b3 + a3 b0) e03
        //
        // Produce a translator by dividing all terms by a0 b0

        __m128 tmp = _mm_mul_ps(KLN_SWIZZLE(a, 0, 0, 0, 0), b);
        tmp        = _mm_mul_ps(tmp, _mm_set_ps(-1.f, -1.f, -1.f, -2.f));
        tmp        = _mm_add_ps(tmp, _mm_mul_ps(a, KLN_SWIZZLE(b, 0, 0, 0, 0)));

        // (0, 1, 2, 3) -> (0, 0, 2, 2)
        __m128 ss = _mm_moveldup_ps(tmp);
        ss        = _mm_movelh_ps(ss, ss);
        tmp       = _mm_mul_ps(tmp, detail::rcp_nr1(ss));

#ifdef KLEIN_SSE_4_1
        p2 = _mm_blend_ps(tmp, _mm_setzero_ps(), 1);
#else
        p2 = _mm_and_ps(tmp, _mm_castsi128_ps(_mm_set_epi32(-1, -1, -1, 0)));
#endif
    }

    KLN_INLINE void KLN_VEC_CALL gpDL(float u,
                                      float v,
                                      __m128 b,
                                      __m128 c,
                                      __m128& KLN_RESTRICT p1,
                                      __m128& KLN_RESTRICT p2) noexcept
    {
        // b1 u e23 +
        // b2 u e31 +
        // b3 u e12 +
        // (-b1 v + c1 u) e01 +
        // (-b2 v + c2 u) e02 +
        // (-b3 v + c3 u) e03
        __m128 u_vec = _mm_set1_ps(u);
        __m128 v_vec = _mm_set1_ps(v);
        p1           = _mm_mul_ps(u_vec, b);
        p2           = _mm_mul_ps(c, u_vec);
        p2           = _mm_sub_ps(p2, _mm_mul_ps(b, v_vec));
    }

    template <bool Flip>
    KLN_INLINE void KLN_VEC_CALL gpRT(__m128 a, __m128 b, __m128& p2)
    {
        // (a1 b1 + a2 b2 + a3 b3) e0123 +
        // (a0 b1 + a2 b3 - a3 b2) e01 +
        // (a0 b2 + a3 b1 - a1 b3) e02 +
        // (a0 b3 + a1 b2 - a2 b1) e03

        p2 = _mm_mul_ps(KLN_SWIZZLE(a, 0, 0, 0, 1), KLN_SWIZZLE(b, 3, 2, 1, 1));
        p2 = _mm_add_ps(
            p2,
            _mm_mul_ps(KLN_SWIZZLE(a, 1, 3, 2, 2), KLN_SWIZZLE(b, 2, 1, 3, 2)));
        p2 = _mm_sub_ps(p2,
                        _mm_xor_ps(_mm_set_ss(-0.f),
                                   _mm_mul_ps(KLN_SWIZZLE(a, 2, 1, 3, 3),
                                              KLN_SWIZZLE(b, 1, 3, 2, 3))));
    }

    template <>
    KLN_INLINE void KLN_VEC_CALL gpRT<false>(__m128 a, __m128 b, __m128& p2)
    {
        // (a1 b1 + a2 b2 + a3 b3) e0123 +
        // (a0 b1 + a3 b2 - a2 b3) e01 +
        // (a0 b2 + a1 b3 - a3 b1) e02 +
        // (a0 b3 + a2 b1 - a1 b2) e03

        p2 = _mm_mul_ps(KLN_SWIZZLE(a, 0, 0, 0, 1), KLN_SWIZZLE(b, 3, 2, 1, 1));
        p2 = _mm_add_ps(
            p2,
            _mm_mul_ps(KLN_SWIZZLE(a, 2, 1, 3, 2), KLN_SWIZZLE(b, 1, 3, 2, 2)));
        p2 = _mm_sub_ps(p2,
                        _mm_xor_ps(_mm_set_ss(-0.f),
                                   _mm_mul_ps(KLN_SWIZZLE(a, 1, 3, 2, 3),
                                              KLN_SWIZZLE(b, 2, 1, 3, 3))));
    }

    template <bool Flip>
    KLN_INLINE void KLN_VEC_CALL gp12(__m128 a, __m128 b, __m128& p2) noexcept
    {
        gpRT<Flip>(a, b, p2);
        p2 = _mm_sub_ps(p2,
                        _mm_xor_ps(_mm_set_ss(-0.f),
                                   _mm_mul_ps(a, KLN_SWIZZLE(b, 0, 0, 0, 0))));
    }

    // Optimized line * line operation
    KLN_INLINE void KLN_VEC_CALL gpLL(__m128 const& KLN_RESTRICT l1,
                                      __m128 const& KLN_RESTRICT l2,
                                      __m128* KLN_RESTRICT out) noexcept
    {
        // (-a1 b1 - a3 b3 - a2 b2) +
        // (a2 b1 - a1 b2) e12 +
        // (a1 b3 - a3 b1) e31 +
        // (a3 b2 - a2 b3) e23 +
        // (a1 c1 + a3 c3 + a2 c2 + b1 d1 + b3 d3 + b2 d2) e0123
        // (a3 c2 - a2 c3         + b2 d3 - b3 d2) e01 +
        // (a1 c3 - a3 c1         + b3 d1 - b1 d3) e02 +
        // (a2 c1 - a1 c2         + b1 d2 - b2 d1) e03 +
        __m128 const& a = l1;
        __m128 const& d = *(&l1 + 1);
        __m128 const& b = l2;
        __m128 const& c = *(&l2 + 1);

        __m128 flip = _mm_set_ss(-0.f);

        __m128& p1 = *out;
        __m128& p2 = *(out + 1);

        p1 = _mm_mul_ps(KLN_SWIZZLE(a, 3, 1, 2, 1), KLN_SWIZZLE(b, 2, 3, 1, 1));
        p1 = _mm_xor_ps(p1, flip);
        p1 = _mm_sub_ps(
            p1,
            _mm_mul_ps(KLN_SWIZZLE(a, 2, 3, 1, 3), KLN_SWIZZLE(b, 3, 1, 2, 3)));
        __m128 a2 = _mm_unpackhi_ps(a, a);
        __m128 b2 = _mm_unpackhi_ps(b, b);
        p1        = _mm_sub_ss(p1, _mm_mul_ss(a2, b2));

        p2 = _mm_mul_ps(KLN_SWIZZLE(a, 2, 1, 3, 1), KLN_SWIZZLE(c, 1, 3, 2, 1));
        p2 = _mm_sub_ps(p2,
                        _mm_xor_ps(flip,
                                   _mm_mul_ps(KLN_SWIZZLE(a, 1, 3, 2, 3),
                                              KLN_SWIZZLE(c, 2, 1, 3, 3))));
        p2 = _mm_add_ps(
            p2,
            _mm_mul_ps(KLN_SWIZZLE(b, 1, 3, 2, 1), KLN_SWIZZLE(d, 2, 1, 3, 1)));
        p2        = _mm_sub_ps(p2,
                        _mm_xor_ps(flip,
                                   _mm_mul_ps(KLN_SWIZZLE(b, 2, 1, 3, 3),
                                              KLN_SWIZZLE(d, 1, 3, 2, 3))));
        __m128 c2 = _mm_unpackhi_ps(c, c);
        __m128 d2 = _mm_unpackhi_ps(d, d);
        p2        = _mm_add_ss(p2, _mm_mul_ss(a2, c2));
        p2        = _mm_add_ss(p2, _mm_mul_ss(b2, d2));
    }

    // Optimized motor * motor operation
    KLN_INLINE void KLN_VEC_CALL gpMM(__m128 const& KLN_RESTRICT m1,
                                      __m128 const& KLN_RESTRICT m2,
                                      __m128* KLN_RESTRICT out) noexcept
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
        __m128 const& a = m1;
        __m128 const& b = *(&m1 + 1);
        __m128 const& c = m2;
        __m128 const& d = *(&m2 + 1);

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