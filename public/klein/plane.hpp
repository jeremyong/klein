#pragma once

#include "detail/entity.hpp"

namespace kln
{
// In projective geometry, planes are the fundamental element through which all
// other entities are constructed. Lines are the meet of two planes, and points
// are the meet of three planes (equivalently, a line and a plane).
//
// d*e_0 + a*e_1 + b*e_2 + c*e_3
struct plane final : public entity<0b1>
{
    plane() = default;

    // The constructor performs the rearrangement so the plane can be specified
    // in the familiar form: ax + by + cz + d
    plane(float a, float b, float c, float d) noexcept
    {
        parts[0].reg = _mm_set_ps(c, b, a, d);
    }

    // Data should point to four floats with memory layout (d, a, b, c)
    plane(float* data) noexcept
    {
        parts[0].reg = _mm_loadu_ps(data);
    }

    // When constructing a plane with points using the regressive product, data
    // leaks into the 3rd partition so this explicit constructor is made
    // available
    explicit plane(entity<0b1001> const& other) noexcept
    {
        parts[0].reg = other.p0();
    }

    float x() const noexcept
    {
        return parts[0].data[1];
    }

    float y() const noexcept
    {
        return parts[0].data[2];
    }

    float z() const noexcept
    {
        return parts[0].data[3];
    }

    float d() const noexcept
    {
        return parts[0].data[0];
    }
};
} // namespace kln