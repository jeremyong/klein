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
        parts[0].reg = _mm_set_ps(d, a, b, c);
    }

    float x() const noexcept
    {
        return parts[0].data[2];
    }

    float y() const noexcept
    {
        return parts[0].data[1];
    }

    float z() const noexcept
    {
        return parts[0].data[0];
    }

    float d() const noexcept
    {
        return parts[0].data[3];
    }
};
}