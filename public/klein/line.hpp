#pragma once

#include "detail/exp_log.hpp"
#include "entity.hpp"

namespace kln
{
/// An ideal line represents a line at infinity and corresponds to the
/// multivector:
///
/// $$a\mathbf{e}_{01} + b\mathbf{e}_{02} + c\mathbf{e}_{03}$$
struct ideal_line final : public entity<0b100>
{
    ideal_line() = default;

    ideal_line(float a, float b, float c) noexcept
    {
        parts[0].reg = _mm_set_ps(c, b, a, 0.f);
    }

    ideal_line(entity const& other) noexcept
        : entity{other}
    {}

    ideal_line(entity&& other) noexcept
        : entity{std::move(other)}
    {}

    /// Exponentiate this ideal line to produce a translation. An
    /// `entity<0b100>` is returned instead to avoid a cyclic dependency, but
    /// this can be implicitly casted to a `translator`.
    ///
    /// The exponential of an ideal line
    /// $a \mathbf{e}_{01} + b\mathbf{e}_{02} + c\mathbf{e}_{03}$ is given as:
    ///
    /// $$\exp{\left[a\ee_{01} + b\ee_{02} + c\ee_{03}\right]} = 1 +\
    /// a\ee_{01} + b\ee_{02} + c\ee_{03}$$
    ///
    /// If this line is aliasing a portion of an existing translator, the
    /// original translator can be used directly.
    [[nodiscard]] entity<0b110> exp() const& noexcept
    {
        entity<0b110> out;
        out.p1() = _mm_set_ss(1.f);
        out.p2() = p2();
        return out;
    }
};

/// The `branch` both a line through the origin and also the principal branch of
/// the logarithm of a rotor.
///
/// The rotor branch will be most commonly constructed by taking the
/// logarithm of a normalized rotor. The branch may then be linearily scaled
/// to adjust the "strength" of the rotor, and subsequently re-exponentiated
/// to create the adjusted rotor.
///
/// !!! example
///
///     Suppose we have a rotor $r$ and we wish to produce a rotor
///     $\sqrt[4]{r}$ which performs a quarter of the rotation produced by
///     $r$. We can construct it like so:
///
///     ```c++
///         kln::branch b = r.log();
///         kln::rotor r_4 = (0.25f * b).exp();
///     ```
///
/// !!! note
///
///     The branch of a rotor is technically a `line`, but because there are
///     no translational components, the branch is given its own type for
///     efficiency.
struct branch final : public entity<0b10>
{
    branch() = default;

    /// Construct the branch as the following multivector:
    ///
    /// $$a \mathbf{e}_{23} + b\mathbf{e}_{31} + c\mathbf{e}_{23}$$
    ///
    /// To convince yourself this is a line through the origin, remember that
    /// such a line can be generated using the geometric product of two planes
    /// through the origin.
    branch(float a, float b, float c) noexcept
    {
        parts[0].reg = _mm_set_ps(c, b, a, 0.f);
    }

    branch(entity const& other) noexcept
        : entity{other}
    {}

    branch(entity&& other) noexcept
        : entity{std::move(other)}
    {}

    /// Exponentiate this branch to produce a rotor. To avoid a circular
    /// dependency, an `entity<0b10>` is returned but this can be implicitly
    /// cast to a rotor.
    [[nodiscard]] entity exp() const noexcept
    {
        // Compute the rotor angle
        float ang;
        _mm_store_ss(&ang, _mm_sqrt_ps(_mm_dp_ps(p1(), p1(), 0b11100001)));
        float cos_ang = std::cos(ang);
        float sin_ang = std::sin(ang) / ang;

        entity out;
        out.p1() = _mm_mul_ps(_mm_set1_ps(sin_ang), p1());
        out.p1() = _mm_add_ps(out.p1(), _mm_set_ss(cos_ang));
        return out;
    }
};

// p1: (1, e12, e31, e23)
// p2: (e0123, e01, e02, e03)

/// A general line in $\PGA$ is given as a 6-coordinate bivector with a direct
/// correspondence to Plücker coordinates. All lines can be exponentiated using
/// the `exp` method to generate a motor.
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

    line(entity<0b110> const& e) noexcept
        : entity{e}
    {}

    line(entity<0b100> const& e) noexcept
    {
        p2() = e.p2();
    }

    line(entity<0b10> const& e) noexcept
    {
        p1() = e.p1();
    }

    /// If a line is constructed as the regressive product (join) of two points,
    /// the squared norm provided here is the squared distance between the two
    /// points (provided the points are normalized). Returns $d^2 + e^2 + f^2$.
    float squared_norm() noexcept
    {
        float out;
        __m128 dp = _mm_dp_ps(p1(), p1(), 0b11100001);
        _mm_store_ss(&out, dp);
        return out;
    }

    /// Returns the square root of the quantity produced by `squared_norm`.
    float norm() noexcept
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