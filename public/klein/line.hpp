#pragma once

#include "detail/exp_log.hpp"
#include "entity.hpp"

namespace kln
{
// Ideal line: a*e_01 + b*e_02 + c*e_03
struct ideal_line final : public entity<0b100>
{
    ideal_line()
    {
        parts[0].data[0] = 0.0f;
    }

    ideal_line(float a, float b, float c) noexcept
    {
        parts[0].reg = _mm_set_ps(c, b, a, 0.f);
    }
};

// p1: (1, e12, e31, e23)
// p2: (e0123, e01, e02, e03)
struct line final : public entity<0b110>
{
    line()
    {
        parts[0].data[0] = 0.0f;
        parts[1].data[0] = 0.0f;
    }

    /// A line is specifed by 6 coordinates which correspond to the line's
    /// [Plücker
    /// coordinates](https://en.wikipedia.org/wiki/Pl%C3%BCcker_coordinates).
    /// The coordinates specified in this way correspond to the following
    /// multivector:
    ///
    /// $$a\mathbf{e}_{01} + b\mathbf{e}_{02} + c\mathbf{e}_{03} +\
    /// d\mathbf{e}_{23} + e\mathbf{e}_{31} + f\mathbf{e}_{12}$$
    line(float a, float b, float c, float d, float e, float f) noexcept
    {
        parts[0].reg = _mm_set_ps(f, e, d, 0.f);
        parts[1].reg = _mm_set_ps(c, b, a, 0.f);
    }

    line(entity<0b110> const& e)
        : entity{e}
    {}

    line(entity<0b100> const& e)
    {
        p2() = e.p2();
    }

    line(entity<0b10> const& e)
    {
        p1() = e.p1();
    }

    /// If a line is constructed as the regressive product (join) of two points,
    /// the squared norm provided here is the squared distance between the two
    /// points (provided the points are normalized). Returns $d^2 + e^2 + f^2$.
    float squared_norm()
    {
        float out;
        __m128 dp = _mm_dp_ps(p1(), p1(), 0b11100001);
        _mm_store_ss(&out, dp);
        return out;
    }

    /// Returns the square root of the quantity produced by `squared_norm`.
    float norm()
    {
        return std::sqrt(squared_norm());
    }

    /// Line exponentiation
    ///
    /// The line can be exponentiated to produce a motor that posesses this line
    /// as its axis. This routine will be used most often when this line is
    /// produced as the logarithm of an existing rotor, then scaled to subdivide
    /// or accelerate the motor's action.
    entity<0b110> exp() const noexcept
    {
        entity<0b110> out;
        detail::exp(p1(), p2(), out.p1(), out.p2());
        return out;
    }
};
} // namespace kln