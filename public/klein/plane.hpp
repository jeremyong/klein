#pragma once

#include "entity.hpp"

namespace kln
{
/// In projective geometry, planes are the fundamental element through which all
/// other entities are constructed. Lines are the meet of two planes, and points
/// are the meet of three planes (equivalently, a line and a plane).
///
/// The plane multivector in PGA looks like
/// $d\mathbf{e}_0 + a\mathbf{e}_1 + b\mathbf{e}_2 + c\mathbf{e}_3$. Points
/// that reside on the plane satisfy the familiar equation
/// $d + ax + by + cz = 0$.
struct plane final : public entity<0b1>
{
    /// The default constructor leaves memory uninitialized
    plane() = default;

    /// The constructor performs the rearrangement so the plane can be specified
    /// in the familiar form: ax + by + cz + d
    plane(float a, float b, float c, float d) noexcept
    {
        parts[0].reg = _mm_set_ps(c, b, a, d);
    }

    /// Data should point to four floats with memory layout `(d, a, b, c)` where
    /// `d` occupies the lowest address in memory.
    plane(float* data) noexcept
    {
        parts[0].reg = _mm_loadu_ps(data);
    }

    /// Line to plane cast.
    ///
    /// !!! danger
    ///
    ///     When constructing a plane with points using the regressive product,
    ///     data leaks into the 3rd partition so this explicit constructor is
    ///     made available. For example, if you had three `point` entities `p1`,
    ///     `p2`, and `p3`, the plane containing all three points could be
    ///     constructed via `plane p{p1 & p2 & p3}`.
    ///
    ///     If the third partition contains data, this cast will *truncate* that
    ///     data so this constructor should only be used when the caller *knows*
    ///     that the entity passed as the argument is a plane.
    explicit plane(entity<0b1001> const& other) noexcept
    {
        parts[0].reg = other.p0();
    }

    /// Unaligned load of data. The `data` argument should point to 4 floats
    /// corresponding to the
    /// `(d, a, b, c)` components of the plane multivector where `d` occupies
    /// the lowest address in memory.
    ///
    /// !!! tip
    ///
    ///     This is a faster mechanism for setting data compared to setting
    ///     components one at a time.
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

    float d() const noexcept
    {
        return parts[0].data[0];
    }

    float& d() noexcept
    {
        return parts[0].data[0];
    }
};
} // namespace kln