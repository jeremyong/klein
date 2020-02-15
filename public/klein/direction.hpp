#pragma once

#include "detail/entity.hpp"

namespace kln
{
// Ideal points will have a 0 for the homogeneous coordinate
// x*e_032 + y*e_013 + z*e_021
struct direction final : public entity<0b1000>
{
    direction() = default;
    direction(float x, float y, float z) noexcept
    {
        parts[0].reg = _mm_set_ps(x, y, z, 0.f);
    }

    // Provide conversion operator from parent class entity
    direction(entity<0b1000> const& e) noexcept
        : entity{e}
    {
#ifdef KLEIN_VALIDATE
        assert(parts[0].data[0] < 1e-7 && parts[0].data[0] > -1e-7
               && "Cannot initialize direction from non-ideal point");
#endif
    }

    constexpr float operator[](size_t i) const noexcept
    {
        return parts[0].data[3 - i];
    }

    constexpr float& operator[](size_t i) noexcept
    {
        return parts[0].data[3 - i];
    }

    float x() const noexcept
    {
        return parts[0].data[3];
    }

    float y() const noexcept
    {
        return parts[0].data[2];
    }

    float z() const noexcept
    {
        return parts[0].data[1];
    }
};
}