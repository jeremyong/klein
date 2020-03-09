#pragma once

#include "detail/sse.hpp"

#ifdef KLEIN_VALIDATE
#    include <cassert>
#endif

namespace kln
{
/// \defgroup dir Directions
/// Directions in $\mathbf{P}(\mathbb{R}^3_{3, 0, 1})$ are represented using
/// points at infinity (homogeneous coordinate 0). Having a homogeneous
/// coordinate of zero ensures that directions are translation-invariant.

/// \addtogroup dir
/// @{
class direction final
{
public:
    direction() noexcept = default;

    /// Create a normalized direction
    direction(float x, float y, float z) noexcept
        : p3_{_mm_set_ps(z, y, x, 0.f)}
    {
        normalize();
    }

    direction(__m128 p3) noexcept
        : p3_{p3}
    {}

    /// Data should point to four floats with memory layout `(0.f, x, y, z)`
    /// where the zero occupies the lowest address in memory.
    explicit direction(float* data) noexcept
    {
#ifdef KLEIN_VALIDATE
        assert(data[0] == 0.f
            && "Homogeneous coordinate of point data used to initialize a"
               "direction must be exactly zero");
#endif
        p3_ = _mm_loadu_ps(data);
    }

    [[nodiscard]] float x() const noexcept
    {
        float out[4];
        _mm_store_ps(out, p3_);
        return out[1];
    }

    [[nodiscard]] float y() const noexcept
    {
        float out[4];
        _mm_store_ps(out, p3_);
        return out[2];
    }

    [[nodiscard]] float z() const noexcept
    {
        float out[4];
        _mm_store_ps(out, p3_);
        return out[3];
    }

    /// Normalize this direction by dividing all components by the
    /// magnitude (by default, `rsqrtps` is used with a single Newton-Raphson
    /// refinement iteration)
    void normalize() noexcept
    {
        __m128 tmp = detail::rsqrt_nr1(detail::hi_dp_bc(p3_, p3_));
        p3_        = _mm_mul_ps(p3_, tmp);
    }

    /// Return a normalized copy of this direction
    direction normalized() const noexcept
    {
        direction out = *this;
        out.normalize();
        return out;
    }

    /// Direction addition
    direction& KLN_VEC_CALL operator+=(direction b) noexcept
    {
        p3_ = _mm_add_ps(p3_, b.p3_);
        return *this;
    }

    /// Direction subtraction
    direction& KLN_VEC_CALL operator-=(direction b) noexcept
    {
        p3_ = _mm_sub_ps(p3_, b.p3_);
        return *this;
    }

    /// Direction uniform scale
    direction& operator*=(float s) noexcept
    {
        p3_ = _mm_mul_ps(p3_, _mm_set1_ps(s));
        return *this;
    }

    /// Direction uniform scale
    direction& operator*=(int s) noexcept
    {
        p3_ = _mm_mul_ps(p3_, _mm_set1_ps(static_cast<float>(s)));
        return *this;
    }

    /// Direction uniform inverse scale
    direction& operator/=(float s) noexcept
    {
        p3_ = _mm_mul_ps(p3_, detail::rcp_nr1(_mm_set1_ps(s)));
        return *this;
    }

    /// Direction uniform inverse scale
    direction& operator/=(int s) noexcept
    {
        p3_ = _mm_mul_ps(
            p3_, detail::rcp_nr1(_mm_set1_ps(static_cast<float>(s))));
        return *this;
    }

    __m128 p3_;
};

/// Direction addition
[[nodiscard]] inline direction KLN_VEC_CALL operator+(direction a,
                                                      direction b) noexcept
{
    direction c;
    c.p3_ = _mm_add_ps(a.p3_, b.p3_);
    return c;
}

/// Direction subtraction
[[nodiscard]] inline direction KLN_VEC_CALL operator-(direction a,
                                                      direction b) noexcept
{
    direction c;
    c.p3_ = _mm_sub_ps(a.p3_, b.p3_);
    return c;
}

/// Direction uniform scale
[[nodiscard]] inline direction KLN_VEC_CALL operator*(direction d, float s) noexcept
{
    direction c;
    c.p3_ = _mm_mul_ps(d.p3_, _mm_set1_ps(s));
    return c;
}

/// Direction uniform scale
[[nodiscard]] inline direction KLN_VEC_CALL operator*(float s, direction d) noexcept
{
    return d * s;
}

/// Direction uniform scale
[[nodiscard]] inline direction KLN_VEC_CALL operator*(direction d, int s) noexcept
{
    return d * static_cast<float>(s);
}

/// Direction uniform scale
[[nodiscard]] inline direction KLN_VEC_CALL operator*(int s, direction d) noexcept
{
    return d * static_cast<float>(s);
}

/// Direction uniform inverse scale
[[nodiscard]] inline direction KLN_VEC_CALL operator/(direction d, float s) noexcept
{
    direction c;
    c.p3_ = _mm_mul_ps(d.p3_, detail::rcp_nr1(_mm_set1_ps(s)));
    return c;
}

/// Direction uniform inverse scale
[[nodiscard]] inline direction KLN_VEC_CALL operator/(direction d, int s) noexcept
{
    return d / static_cast<float>(s);
}

/// Unary minus
[[nodiscard]] inline direction operator-(direction d) noexcept
{
    return {_mm_xor_ps(d.p3_, _mm_set1_ps(-0.f))};
}
} // namespace kln
  /// @}