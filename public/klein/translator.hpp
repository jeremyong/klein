#pragma once

#include "detail/matrix.hpp"
#include "entity.hpp"
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
        parts[0].reg = _mm_set_ss(1.f);
        float half_d = -0.5f * delta;
        parts[1].reg = _mm_mul_ps(_mm_set1_ps(half_d), _mm_set_ps(z, y, x, 0.f));
        parts[1].reg = _mm_mul_ps(
            parts[1].reg, _mm_set_ps(inv_norm, inv_norm, inv_norm, 0.f));
    }

    /// Fast load operation for packed data that is already normalized. The
    /// argument `data` should point to a set of 4 float values with layout
    /// `(0.f, a, b, c)` corresponding to the multivector $a\mathbf{e}_{01} +
    /// b\mathbf{e}_{02} + c\mathbf{e}_{03}$.
    ///
    /// !!! danger
    ///
    ///     The rotor data loaded this way *must* be normalized. That is, the
    ///     quantity $a^2 + b^2 + c^2$ must be 1.
    void load_normalized(float* data) noexcept
    {
        parts[0].reg = _mm_set_ss(1.f);
        parts[1].reg = _mm_loadu_ps(data);
    }

    /// Conjugates a plane $p$ with this translator and returns the result
    /// $tp\widetilde{t}$.
    plane KLN_VEC_CALL operator()(plane const& p) const noexcept
    {
        plane out;
        out.p0() = sw02(p.p0(), _mm_blend_ps(parts[1].reg, parts[0].reg, 1));
        return out;
    }

    /// Conjugates a point $p$ with this translator and returns the result
    /// $tp\widetilde{t}$.
    point KLN_VEC_CALL operator()(point const& p) const noexcept
    {
        point out;
        out.p3() = sw32(p.p3(), parts[1].reg);
        return out;
    }
};
} // namespace kln