#pragma once

#include "detail/entity.hpp"

namespace kln
{
// x*e_032 + y*e_013 + z*e_021 + e_123
struct point final : public entity<0b1000>
{
    point() = default;

    point(float x, float y, float z) noexcept
    {
        parts[0].reg = _mm_set_ps(x, y, z, 1.f);
    }

    point(entity<0b1000> const& e)
        : entity{e}
    {}

    float x() const noexcept
    {
        return parts[0].data[3];
    }

    float& x() noexcept
    {
        return parts[0].data[3];
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
        return parts[0].data[1];
    }

    float& z() noexcept
    {
        return parts[0].data[1];
    }

    // Unity when normalized
    float w() const noexcept
    {
        return parts[0].data[0];
    }

    float& w() noexcept
    {
        return parts[0].data[0];
    }

    void normalize() noexcept
    {
        // Fast reciprocal operation to divide by w. The maximum relative error
        // for the rcp approximation is 1.5*2^-12 (~.00036621)
        __m128 tmp   = _mm_rcp_ps(KLN_SWIZZLE(parts[0].reg, 0, 0, 0, 0));
        parts[0].reg = _mm_mul_ps(parts[0].reg, tmp);
    }
};

// The origin is a convenience type that occupies no memory but is castable to a
// point entity
struct origin
{
    operator entity<0b1000>() const noexcept
    {
        entity<0b1000> out;
        out.p3() = _mm_set_ss(1.f);
        return out;
    }
};
}