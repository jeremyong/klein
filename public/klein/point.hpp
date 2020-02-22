#pragma once

#include "entity.hpp"

namespace kln
{
/// A point is represented as the multivector
/// $x\mathbf{e}_{032} + y\mathbf{e}_{013} + z\mathbf{e}_{021} +
/// \mathbf{e}_{123}$. The point has a trivector representation because it is
/// the fixed point of 3 planar reflections (each of which is a grade-1
/// multivector). In practice, the coordinate mapping can be thought of as an
/// implementation detail.
struct point final : public entity<0b1000>
{
    /// Default constructor leaves memory uninitialized.
    point() = default;

    /// Component-wise constructor (homogeneous coordinate is automatically
    /// initialized to 1)
    point(float x, float y, float z) noexcept
    {
        parts[0].reg = _mm_set_ps(z, y, x, 1.f);
    }

    point(entity<0b1000> const& e) noexcept
        : entity{e}
    {}

    /// A point projected onto a line will have an extinguished partition-0,
    /// which necessitates this explicit cast when it is known to be safe.
    explicit point(entity<0b1001> const& e) noexcept
    {
        p3() = e.p3();
    }

    /// Fast load from a pointer to an array of four floats with layout
    /// `(w, x, y, z)` where `w` occupies the lowest address in memory.
    ///
    /// !!! tip
    ///
    ///     This load operation is more efficient that modifying individual
    ///     components back-to-back.
    ///
    /// !!! danger
    ///
    ///     Unlike the component-wise constructor, the load here requires the
    ///     homogeneous coordinate `w` to be supplied as well in the lowest
    ///     address pointed to by `data`.
    void load(float* data) noexcept
    {
        parts[0].reg = _mm_loadu_ps(data);
    }

    float x() const noexcept
    {
        return parts[0].data[1];
    }

    float& x() noexcept
    {
        return parts[0].data[1];
    }

    float y() const noexcept
    {
        return parts[0].data[2];
    }

    float& y() noexcept
    {
        return parts[0].data[2];
    }

    float z() const noexcept
    {
        return parts[0].data[3];
    }

    float& z() noexcept
    {
        return parts[0].data[3];
    }

    /// The homogeneous coordinate `w` is exactly $1$ when normalized.
    float w() const noexcept
    {
        return parts[0].data[0];
    }

    float& w() noexcept
    {
        return parts[0].data[0];
    }

    /// Normalize this point
    ///
    /// !!! tip
    ///
    ///     Point normalization divides the coordinates by the homogeneous
    ///     coordinate `w`. This is done using the `rcpps` instruction with a
    ///     maximum relative error of $1.5\times 2^{-12}$.
    void normalize() noexcept
    {
        // Fast reciprocal operation to divide by w. The maximum relative error
        // for the rcp approximation is 1.5*2^-12 (~.00036621)
        __m128 tmp   = _mm_rcp_ps(KLN_SWIZZLE(parts[0].reg, 0, 0, 0, 0));
        parts[0].reg = _mm_mul_ps(parts[0].reg, tmp);
    }
};

/// The origin is a convenience type that occupies no memory but is castable to
/// a point entity. Several operations like conjugation of the origin by a motor
/// is optimized.
struct origin
{
    /// On its own, the origin occupies no memory, but it can be casted as an
    /// entity at any point, at which point it is represented as
    /// $\mathbf{e}_{123}$.
    operator entity<0b1000>() const noexcept
    {
        entity<0b1000> out;
        out.p3() = _mm_set_ss(1.f);
        return out;
    }
};
} // namespace kln