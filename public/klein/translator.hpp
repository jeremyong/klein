#pragma once

#include "detail/matrix.hpp"
#include "entity.hpp"
#include "mat4x4.hpp"
#include "plane.hpp"
#include "point.hpp"

namespace kln
{
/// A translator represents a rigid-body displacement along a normalized axis.
/// To apply the translator to a supported entity, the call operator is
/// available.
///
/// !!! example
///
///     ```c++
///         // Initialize a point at (1, 3, 2)
///         kln::point p{1.f, 3.f, 2.f};
///
///         // Create a normalized translator representing a 4-unit
///         // displacement along the xz-axis.
///         kln::translator r{4.f, 1.f, 0.f, 1.f};
///
///         // Displace our point using the created translator
///         kln::point translated = r(p);
///     ```
///     We can translate lines and planes as well using the translator's call
///     operator.
///
/// Translators can be multiplied to one another with the `*` operator to create
/// a new translator equivalent to the application of each factor.
///
/// !!! example
///
///     ```c++
///         // Suppose we have 3 translators t1, t2, and t3
///
///         // The translator t created here represents the combined action of
///         // t1, t2, and t3.
///         kln::translator t = t3 * t2 * t1;
///     ```
///
/// The same `*` operator can be used to compose the translator's action with
/// other rotors and motors.
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

    translator(entity<0b110> const& other)
        : entity{other}
    {}

    /// Fast load operation for packed data that is already normalized. The
    /// argument `data` should point to a set of 4 float values with layout
    /// `(0.f, a, b, c)` corresponding to the multivector $a\mathbf{e}_{01} +
    /// b\mathbf{e}_{02} + c\mathbf{e}_{03}$.
    ///
    /// !!! danger
    ///
    ///     The translator data loaded this way *must* be normalized. That is,
    ///     the quantity $-\sqrt{a^2 + b^2 + c^2}$ must be half the desired
    ///     displacement.
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

    /// Conjugates a line $\ell$ with this translator and returns the result
    /// $t\ell\widetilde{t}$.
    line KLN_VEC_CALL operator()(line const& l) const noexcept
    {
        line out;
        swL2(l.p1(), l.p2(), p2(), &out.p1());
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