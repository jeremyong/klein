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

#ifndef KLN_RESTRICT
#    define KLN_RESTRICT __restrict
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
    // DP high components and caller ignores returned high components
    KLN_INLINE __m128 KLN_VEC_CALL hi_dp_ss(__m128 const& a,
                                            __m128 const& b) noexcept
    {
        // 0 1 2 3 -> 1 + 2 + 3, 0, 0, 0

        __m128 out = _mm_mul_ps(a, b);

        // 0 1 2 3 -> 1 1 3 3
        __m128 hi = _mm_movehdup_ps(out);

        // 0 1 2 3 + 1 1 3 3 -> (0 + 1, 1 + 1, 2 + 3, 3 + 3)
        __m128 sum = _mm_add_ps(hi, out);

        // unpacklo: 0 0 1 1
        out = _mm_add_ps(sum, _mm_unpacklo_ps(out, out));

        // (1 + 2 + 3, _, _, _)
        return _mm_movehl_ps(out, out);
    }

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
#else
    // Equivalent to _mm_dp_ps(a, b, 0b11100001);
    KLN_INLINE __m128 KLN_VEC_CALL hi_dp(__m128 const& a, __m128 const& b) noexcept
    {
        // 0 1 2 3 -> 1 + 2 + 3, 0, 0, 0

        __m128 out = _mm_mul_ps(a, b);

        // 0 1 2 3 -> 1 1 3 3
        __m128 hi = _mm_movehdup_ps(out);

        // 0 1 2 3 + 1 1 3 3 -> (0 + 1, 1 + 1, 2 + 3, 3 + 3)
        __m128 sum = _mm_add_ps(hi, out);

        // unpacklo: 0 0 1 1
        out = _mm_add_ps(sum, _mm_unpacklo_ps(out, out));

        // (1 + 2 + 3, _, _, _)
        out = _mm_movehl_ps(out, out);

        return _mm_and_ps(out, _mm_castsi128_ps(_mm_set_epi32(0, 0, 0, -1)));
    }

    KLN_INLINE __m128 KLN_VEC_CALL hi_dp_bc(__m128 const& a,
                                            __m128 const& b) noexcept
    {
        // Multiply across and mask low component
        __m128 out = _mm_mul_ps(a, b);

        // 0 1 2 3 -> 1 1 3 3
        __m128 hi = _mm_movehdup_ps(out);

        // 0 1 2 3 + 1 1 3 3 -> (0 + 1, 1 + 1, 2 + 3, 3 + 3)
        __m128 sum = _mm_add_ps(hi, out);

        // unpacklo: 0 0 1 1
        out = _mm_add_ps(sum, _mm_unpacklo_ps(out, out));

        return KLN_SWIZZLE(out, 2, 2, 2, 2);
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
#endif
} // namespace detail
} // namespace kln