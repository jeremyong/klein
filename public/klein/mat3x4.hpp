#pragma once

#include "detail/sse.hpp"

namespace kln
{
/// 3x4 column-major matrix (used for converting rotors/motors to matrix form to
/// upload to shaders). Note that the storage requirement is identical to a
/// column major mat4x4 due to the SIMD representation.
struct mat3x4
{
    union
    {
        __m128 cols[4];
        float data[16];
    };

    /// Apply the linear transformation represented by this matrix to a point
    /// packed with the layout (x, y, z, 1.f)
    __m128 KLN_VEC_CALL operator()(__m128 const& xyzw) const noexcept
    {
        __m128 out = _mm_mul_ps(cols[0], KLN_SWIZZLE(xyzw, 0, 0, 0, 0));
        out = _mm_add_ps(out, _mm_mul_ps(cols[1], KLN_SWIZZLE(xyzw, 1, 1, 1, 1)));
        out = _mm_add_ps(out, _mm_mul_ps(cols[2], KLN_SWIZZLE(xyzw, 2, 2, 2, 2)));
        out = _mm_add_ps(out, _mm_mul_ps(cols[3], KLN_SWIZZLE(xyzw, 3, 3, 3, 3)));
        return out;
    }

    // TODO: provide a transpose function
};
} // namespace kln