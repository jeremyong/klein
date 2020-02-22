#pragma once

#include "entity.hpp"

#ifdef KLEIN_VALIDATE
#    include <cassert>
#endif

namespace kln
{
/// Directions in $\mathbf{P}(\mathbb{R}^3_{3, 0, 1})$ are represented using
/// points at infinity (homogeneous coordinate 0). Having a homogeneous
/// coordinate of zero ensures that directions are translation-invariant.
struct direction final : public entity<0b1000>
{
    direction() = default;

    /// Create a normalized direction
    direction(float x, float y, float z) noexcept
    {
        parts[0].reg = _mm_set_ps(z, y, x, 0.f);
        normalize();
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

    /// Data should point to four floats with memory layout `(0.f, x, y, z)`
    /// where the zero occupies the lowest address in memory.
    explicit direction(float* data) noexcept
    {
#ifdef KLEIN_VALIDATE
        assert(data[0] == 0.f
            && "Homogeneous coordinate of point data used to initialize a"
               "direction must be exactly zero");
#endif
        parts[0].reg = _mm_loadu_ps(data);
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

    /// Normalize this direction by dividing all components by the square
    /// magnitude
    ///
    /// !!! tip
    ///
    ///     Direction normalization divides the coordinates by the quantity
    ///     x^2 + y^2 + z^2. This is done using the `rcpps` instruction with a
    ///     maximum relative error of $1.5\times 2^{-12}$.
    void normalize() noexcept
    {
        // Fast reciprocal operation to divide by a^2 + b^2 + c^2. The maximum
        // relative error for the rcp approximation is 1.5*2^-12 (~.00036621)
        __m128 tmp   = _mm_rcp_ps(_mm_dp_ps(p3(), p3(), 0b11101110));
        parts[0].reg = _mm_mul_ps(parts[0].reg, tmp);
    }
};
} // namespace kln