// File: x86_sse.hpp
// Purpose: Provide convenience macros and utilities for invoking x86 SSE
// intrinsics
#pragma once

#ifdef KLEIN_SSE_4_1
#    include <smmintrin.h>
#else
#    include <tmmintrin.h>
#endif

// Little-endian XMM register swizzle
//
// KLN_SWIZZLE(reg, 3, 2, 1, 0) is the identity.
//
// This is undef-ed at the bottom of klein.hpp so as not to
// pollute the macro namespace
#ifndef KLN_SWIZZLE
#    define KLN_SWIZZLE(reg, x, y, z, w) \
        _mm_shuffle_ps((reg), (reg), _MM_SHUFFLE(x, y, z, w))
#endif

#ifndef KLN_VEC_CALL
#    ifdef _MSC_VER
// Microsoft Compiler
#        define KLN_VEC_CALL __vectorcall
#    else
// GCC or Clang compiler (sse register passing is on by default)
#        define KLN_VEC_CALL
#    endif
#endif

#ifndef KLN_INLINE
#    ifdef _MSC_VER
#        define KLN_INLINE __forceinline
#    else
#        define KLN_INLINE inline __attribute__((always_inline))
#    endif
#endif

namespace kln
{
namespace detail
{
#ifdef KLEIN_SSE_4_1
    KLN_INLINE __m128 KLN_VEC_CALL hi_dp(__m128 const& a, __m128 const& b) noexcept
    {
        return _mm_dp_ps(a, b, 0b11100001);
    }

    KLN_INLINE __m128 KLN_VEC_CALL hi_dp_bc(__m128 const& a,
                                            __m128 const& b) noexcept
    {
        return _mm_dp_ps(a, b, 0b11101111);
    }

    KLN_INLINE __m128 KLN_VEC_CALL dp(__m128 const& a, __m128 const& b) noexcept
    {
        return _mm_dp_ps(a, b, 0b11110001);
    }

    KLN_INLINE __m128 KLN_VEC_CALL dp_bc(__m128 const& a, __m128 const& b) noexcept
    {
        return _mm_dp_ps(a, b, 0xff);
    }

    KLN_INLINE void KLN_VEC_CALL exchange_ss(__m128 const& a,
                                             __m128 const& b,
                                             __m128& a_out,
                                             __m128& b_out) noexcept
    {
        a_out = _mm_blend_ps(a, b, 1);
        b_out = _mm_blend_ps(b, a, 1);
    }
#else
    // Equivalent to _mm_dp_ps(a, b, 0b11100001);
    KLN_INLINE __m128 KLN_VEC_CALL hi_dp(__m128 const& a, __m128 const& b) noexcept
    {
        // Multiply across and mask low component
        __m128 out = _mm_castsi128_ps(
            _mm_bsrli_si128(_mm_castps_si128(_mm_mul_ps(a, b)), 4));
        __m128 hi = _mm_movehdup_ps(out);
        // (a1 b1, a2 b2, a3 b3, 0) + (a2 b2, a2 b2, 0, 0)
        // = (a1 b1 + a2 b2, _, a3 b3, 0)
        out = _mm_add_ps(hi, out);
        out = _mm_add_ss(out, _mm_movehl_ps(hi, out));
        return _mm_and_ps(out, _mm_castsi128_ps(_mm_set_epi32(0, 0, 0, -1)));
    }

    KLN_INLINE __m128 KLN_VEC_CALL hi_dp_bc(__m128 const& a,
                                            __m128 const& b) noexcept
    {
        // Multiply across and mask low component
        __m128 out = _mm_castsi128_ps(
            _mm_bsrli_si128(_mm_castps_si128(_mm_mul_ps(a, b)), 4));
        __m128 hi = _mm_movehdup_ps(out);
        // (a1 b1, a2 b2, a3 b3, 0) + (a2 b2, a2 b2, 0, 0)
        // = (a1 b1 + a2 b2, _, a3 b3, 0)
        out = _mm_add_ps(hi, out);
        out = _mm_add_ss(out, _mm_movehl_ps(hi, out));
        return KLN_SWIZZLE(out, 0, 0, 0, 0);
    }

    KLN_INLINE __m128 KLN_VEC_CALL dp(__m128 const& a, __m128 const& b) noexcept
    {
        // Multiply across and shift right (shifting in zeros)
        __m128 out = _mm_mul_ps(a, b);
        __m128 hi  = _mm_movehdup_ps(out);
        // (a1 b1, a2 b2, a3 b3, 0) + (a2 b2, a2 b2, 0, 0)
        // = (a1 b1 + a2 b2, _, a3 b3, 0)
        out = _mm_add_ps(hi, out);
        out = _mm_add_ss(out, _mm_movehl_ps(hi, out));
        return _mm_and_ps(out, _mm_castsi128_ps(_mm_set_epi32(0, 0, 0, -1)));
    }

    KLN_INLINE __m128 KLN_VEC_CALL dp_bc(__m128 const& a, __m128 const& b) noexcept
    {
        // Multiply across and shift right (shifting in zeros)
        __m128 out = _mm_mul_ps(a, b);
        __m128 hi  = _mm_movehdup_ps(out);
        // (a1 b1, a2 b2, a3 b3, 0) + (a2 b2, a2 b2, 0, 0)
        // = (a1 b1 + a2 b2, _, a3 b3, 0)
        out = _mm_add_ps(hi, out);
        out = _mm_add_ss(out, _mm_movehl_ps(hi, out));
        return KLN_SWIZZLE(out, 0, 0, 0, 0);
    }

    KLN_INLINE void KLN_VEC_CALL exchange_ss(__m128 const& a,
                                             __m128 const& b,
                                             __m128& a_out,
                                             __m128& b_out) noexcept
    {
        a_out = _mm_xor_ps(
            _mm_and_ps(a, _mm_castsi128_ps(_mm_set_epi32(-1, -1, -1, 0))),
            _mm_and_ps(b, _mm_castsi128_ps(_mm_set_epi32(0, 0, 0, -1))));
        b_out = _mm_xor_ps(
            _mm_and_ps(b, _mm_castsi128_ps(_mm_set_epi32(-1, -1, -1, 0))),
            _mm_and_ps(a, _mm_castsi128_ps(_mm_set_epi32(0, 0, 0, -1))));
    }
#endif
} // namespace detail
} // namespace kln