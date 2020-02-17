#pragma once

#include "entity.hpp"
#include "detail/matrix.hpp"
#include "line.hpp"
#include "mat4x4.hpp"
#include "plane.hpp"
#include "point.hpp"
#include <cmath>

namespace kln
{
struct rotor final : public entity<0b10>
{
    rotor() = default;
    // Convenience constructor. Computes transcendentals and normalizes rotation
    // axis.
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

    void normalize() noexcept
    {
        // A rotor is normalized if r * ~r is unity.
        __m128 inv_norm = _mm_rcp_ps(_mm_sqrt_ps(_mm_dp_ps(p1(), p1(), 0xff)));
        p1()            = _mm_mul_ps(p1(), inv_norm);
    }

    plane KLN_VEC_CALL operator()(plane const& p) const noexcept
    {
        plane out;
        sw012<false, false>(&p.p0(), parts[0].reg, nullptr, &out.p0());
        return out;
    }

    point KLN_VEC_CALL operator()(point const& p) const noexcept
    {
        point out;
        sw312<false, false>(&p.p3(), parts[0].reg, nullptr, &out.p3());
        return out;
    }

    mat4x4 as_matrix() const noexcept
    {
        mat4x4 out;
        mat4x4_12<false>(parts[0].reg, nullptr, out.cols);
        return out;
    }
};
} // namespace kln