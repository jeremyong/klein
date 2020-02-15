#pragma once

#include "detail/entity.hpp"
#include "detail/matrix.hpp"
#include "mat4x4.hpp"
#include "plane.hpp"
#include "point.hpp"

namespace kln
{
struct translator final : public entity<0b110>
{
    translator() = default;
    translator(float delta, float x, float y, float z)
    {
        float norm     = std::sqrt(x * x + y * y + z * z);
        float inv_norm = 1.f / norm;

        // This register is used somewhat awkardly to hold the scalar 1.
        parts[0].reg = _mm_set_ps(0.f, 0.f, 0.f, 1.f);
        float half_d = -0.5f * delta;
        parts[1].reg = _mm_mul_ps(_mm_set1_ps(half_d), _mm_set_ps(z, y, x, 0.f));
        parts[1].reg = _mm_mul_ps(
            parts[1].reg, _mm_set_ps(inv_norm, inv_norm, inv_norm, 0.f));
    }

    plane KLN_VEC_CALL operator()(plane const& p) const noexcept
    {
        plane out;
        out.p0() = sw02(p.p0(), parts[1].reg);
        return out;
    }

    point KLN_VEC_CALL operator()(point const& p) const noexcept
    {
        point out;
        out.p3() = sw32(p.p3(), parts[1].reg);
        return out;
    }
};
} // namespace kln