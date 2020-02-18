#pragma once

#include "detail/matrix.hpp"
#include "entity.hpp"
#include "line.hpp"
#include "mat4x4.hpp"
#include "plane.hpp"
#include "point.hpp"
#include <cmath>

namespace kln
{
struct rotor final : public entity<0b10>
{
    /// Default constructor leaves memory uninitialized.
    rotor() = default;

    /// Convenience constructor. Computes transcendentals and normalizes
    /// rotation axis.
    rotor(float ang_rad, float x, float y, float z)
    {
        float norm     = std::sqrt(x * x + y * y + z * z);
        float inv_norm = -1.f / norm;

        float half = 0.5f * ang_rad;
        // Rely on compiler to coalesce these two assignments into a single
        // sincos call at instruction selection time
        float buf[4];
        buf[0]        = std::cos(half);
        float sin_ang = std::sin(half);
        float scale   = sin_ang * inv_norm;
        buf[1]        = z * scale;
        buf[2]        = y * scale;
        buf[3]        = x * scale;
        parts[0].reg  = _mm_loadu_ps(buf);
    }

    rotor(entity<0b10> const& other)
        : entity{other}
    {}

    /// Fast load operation for packed data that is already normalized. The
    /// argument `data` should point to a set of 4 float values with layout `(a,
    /// b, c, d)` corresponding to the multivector
    /// $a + b\mathbf{e}_{12} + c\mathbf{e}_{31} + d\mathbf{e}_{23}$.
    ///
    /// !!! danger
    ///
    ///     The rotor data loaded this way *must* be normalized. That is, the
    ///     rotor $r$ must satisfy $r\widetilde{r} = 1$.
    void load_normalized(float* data) noexcept
    {
        parts[0].reg = _mm_loadu_ps(data);
    }

    /// Normalize a rotor such that $\mathbf{r}\widetilde{\mathbf{r}} = 1$.
    void normalize() noexcept
    {
        // A rotor is normalized if r * ~r is unity.
        __m128 inv_norm = _mm_rcp_ps(_mm_sqrt_ps(_mm_dp_ps(p1(), p1(), 0xff)));
        p1()            = _mm_mul_ps(p1(), inv_norm);
    }

    /// Conjugates a plane $p$ with this rotor and returns the result
    /// $rp\widetilde{r}$.
    plane KLN_VEC_CALL operator()(plane const& p) const noexcept
    {
        plane out;
        sw012<false, false>(&p.p0(), parts[0].reg, nullptr, &out.p0());
        return out;
    }

    /// Conjugates a point $p$ with this rotor and returns the result
    /// $rp\widetilde{r}$.
    point KLN_VEC_CALL operator()(point const& p) const noexcept
    {
        point out;
        sw312<false, false>(&p.p3(), parts[0].reg, nullptr, &out.p3());
        return out;
    }

    /// Converts the rotor to a 4x4 column-major matrix.
    mat4x4 as_matrix() const noexcept
    {
        mat4x4 out;
        mat4x4_12<false>(parts[0].reg, nullptr, out.cols);
        return out;
    }
};
} // namespace kln