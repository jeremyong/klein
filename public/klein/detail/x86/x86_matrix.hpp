// File: x86_matrix.hpp
// Purpose: Provide conversion routines from rotors, motors, and translators to
// matrices
//
// Notes:
// The preferred layout is a column-major layout as mat-mat and mat-vec
// multiplication is more naturally implemented when defined this way.

#pragma once

#include "x86_sse.hpp"

namespace kln
{
// Partition memory layouts
//     LSB --> MSB
// p0: (e0, e1, e2, e3)
// p1: (1, e23, e31, e12)
// p2: (e0123, e01, e02, e03)
// p3: (e123, e032, e013, e021)

#if __cplusplus >= 201703L
// Convert a motor to a column-major 4x4
template <bool Translate, bool Normalized>
KLN_INLINE void KLN_VEC_CALL mat4x4_12(__m128 b,
                                       [[maybe_unused]] __m128 const* c,
                                       __m128* out) noexcept
{
    // The derivation of this conversion follows directly from the general
    // expansion of conjugating a point with a motor. See sw312 in
    // klein_sw.hpp for details.
    //
    // LSB
    // (2a0(b2 c3 - b0 c1 - b3 c2 - b1 c0) +
    //  2a3(b1 b3 - b0 b2) +
    //  2a2(b0 b3 + b2 b1) +
    //  a1(b0^2 + b1^2 - b3^2 - b2^2)) e032 // x-coordinate
    //
    // (2a0(b3 c1 - b0 c2 - b1 c3 - b2 c0) +
    //  2a1(b2 b1 - b0 b3) +
    //  2a3(b0 b1 + b3 b2) +
    //  a2(b0^2 + b2^2 - b1^2 - b3^2)) e013 + // y-coordinate
    //
    // (2a0(b1 c2 - b0 c3 - b2 c1 - b3 c0) +
    //  2a2(b3 b2 - b0 b1) +
    //  2a1(b0 b2 + b1 b3) +
    //  a3(b0^2 + b3^2 - b2^2 - b1^2)) e021 + // z-coordinate
    //
    // a0(b0^2 + b1^2 + b2^2 + b3^2) e123 // w-coordinate
    // MSB

    // Store a number of scalar temporaries needed later
    float buf[4];
    _mm_storeu_ps(buf, _mm_mul_ps(b, b));
    float b0_2 = buf[0];
    float b1_2 = buf[1];
    float b2_2 = buf[2];
    float b3_2 = buf[3];

    // The first column of the matrix we need to produce contains the scale
    // factors of the x-coordinate (a1). This can be read off as:
    //
    // b0^2 + b1^2 - b3^2 - b2^2
    // 2(b1 b2 - b3 b0)
    // 2(b2 b0 + b1 b3)
    // 0
    __m128& c0 = out[0];
    c0         = _mm_mul_ps(b, KLN_SWIZZLE(b, 0, 0, 2, 0));
    __m128 tmp
        = _mm_mul_ps(KLN_SWIZZLE(b, 0, 1, 3, 1), KLN_SWIZZLE(b, 0, 3, 0, 1));
    tmp = _mm_xor_ps(_mm_set_ps(0.f, 0.f, -0.f, 0.f), tmp);
    c0  = _mm_mul_ps(_mm_set_ps(0.f, 2.f, 2.f, 1.f), _mm_add_ps(c0, tmp));
    c0  = _mm_sub_ps(c0, _mm_set_ss(b3_2 + b2_2));

    // We can perform the same exercise for y (a2) (the second column):
    //
    // 2(b0 b3 + b2 b1)
    // (-b1^2 - b3^2 + b0^2 + b2^2)
    // 2(b2 b3 - b0 b1)
    // 0
    __m128& c1 = out[1];
    c1         = _mm_mul_ps(b, KLN_SWIZZLE(b, 0, 3, 1, 3));
    tmp = _mm_mul_ps(KLN_SWIZZLE(b, 0, 0, 3, 2), KLN_SWIZZLE(b, 0, 1, 3, 1));
    tmp = _mm_xor_ps(_mm_set_ps(0.f, -0.f, 0.f, 0.f), tmp);
    c1  = _mm_mul_ps(_mm_set_ps(0.f, 2.f, -1.f, 2.f), _mm_add_ps(c1, tmp));
    c1  = _mm_add_ps(c1, _mm_set_ps(0.f, 0.f, b0_2 + b2_2, 0.f));

    // z (a3)
    //
    // 2(-b0 b2 + b1 b3)
    // 2(b1 b0 + b2 b3)
    // (-b2^2 + b0^2 + b3^2 - b1^2)
    // 0
    __m128& c2 = out[2];
    c2         = _mm_xor_ps(_mm_set_ps(0.f, -0.f, 0.f, -0.f),
                    _mm_mul_ps(b, KLN_SWIZZLE(b, 0, 2, 0, 2)));
    c2         = _mm_add_ps(
        c2, _mm_mul_ps(KLN_SWIZZLE(b, 0, 0, 2, 1), KLN_SWIZZLE(b, 0, 0, 3, 3)));
    c2 = _mm_mul_ps(c2, _mm_set_ps(0.f, 1.f, 2.f, 2.f));
    c2 = _mm_add_ps(c2, _mm_set_ps(0.f, b3_2 - b1_2, 0.f, 0.f));

    // And finally w (a0)
    //
    // 2(b2 c3 - b0 c1 - b3 c2 - b1 c0)
    // 2(b3 c1 - b1 c3 - b0 c2 - b2 c0)
    // 2(b1 c2 - b2 c1 - b0 c3 - b3 c0)
    // b0^2 + b1^2 + b2^2 + b3^2
    __m128& c3 = out[3];
    if constexpr (Translate)
    {
        c3 = _mm_mul_ps(b, KLN_SWIZZLE(*c, 0, 1, 3, 1));
        c3 = _mm_add_ps(
            c3,
            _mm_mul_ps(KLN_SWIZZLE(b, 0, 0, 0, 3), KLN_SWIZZLE(*c, 0, 3, 2, 2)));
        c3 = _mm_add_ps(
            c3,
            _mm_mul_ps(KLN_SWIZZLE(b, 0, 3, 2, 1), KLN_SWIZZLE(*c, 0, 0, 0, 0)));
        tmp = _mm_mul_ps(KLN_SWIZZLE(b, 0, 1, 3, 2), KLN_SWIZZLE(*c, 0, 2, 1, 3));
        c3 = _mm_mul_ps(_mm_set_ps(0.f, 2.f, 2.f, 2.f), _mm_sub_ps(tmp, c3));
    }
    if constexpr (Normalized)
    {
#    ifdef KLEIN_SSE_4_1
        c3 = _mm_blend_ps(c3, _mm_set_ps(1.f, 0.f, 0.f, 0.f), 0b1000);
#    else
        c3 = _mm_add_ps(c3, _mm_set_ps(1.f, 0.f, 0.f, 0.f));
#    endif
    }
    else
    {
#    ifdef KLEIN_SSE_4_1
        c3 = _mm_blend_ps(
            c3, _mm_set_ps(b0_2 + b1_2 + b2_2 + b3_2, 0.f, 0.f, 0.f), 0b1000);
#    else
        c3 = _mm_add_ps(c3, _mm_set_ps(b0_2 + b1_2 + b2_2 + b3_2, 0.f, 0.f, 0.f));
#    endif
    }
}
#else
#    include "x86_matrix_cxx11.inl"
#endif
} // namespace kln