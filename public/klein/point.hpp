#pragma once

#include "detail/sse.hpp"

namespace kln
{
/// \defgroup point Points
///
/// A point is represented as the multivector
/// $x\mathbf{e}_{032} + y\mathbf{e}_{013} + z\mathbf{e}_{021} +
/// \mathbf{e}_{123}$. The point has a trivector representation because it is
/// the fixed point of 3 planar reflections (each of which is a grade-1
/// multivector). In practice, the coordinate mapping can be thought of as an
/// implementation detail.

/// \addtogroup point
/// @{
class point final
{
public:
    point() noexcept = default;

    point(__m128 xmm) noexcept
        : p3_{xmm}
    {}

    /// Component-wise constructor (homogeneous coordinate is automatically
    /// initialized to 1)
    point(float x, float y, float z) noexcept
        : p3_{_mm_set_ps(z, y, x, 1.f)}
    {}

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
        p3_ = _mm_loadu_ps(data);
    }

    /// Store m128 contents into an array of 4 floats
    void store(float* data) const noexcept
    {
        _mm_store_ps(data, p3_);
    }

    /// Normalize this point (division is done via rcpps with an additional
    /// Newton-Raphson refinement).
    void normalize() noexcept
    {
        __m128 tmp = detail::rcp_nr1(KLN_SWIZZLE(p3_, 0, 0, 0, 0));
        p3_        = _mm_mul_ps(p3_, tmp);
    }

    /// Return a normalized copy of this point.
    [[nodiscard]] point normalized() const noexcept
    {
        point out = *this;
        out.normalize();
        return out;
    }

    void invert() noexcept
    {
        __m128 inv_norm = detail::rcp_nr1(KLN_SWIZZLE(p3_, 0, 0, 0, 0));
        p3_             = _mm_mul_ps(inv_norm, p3_);
        p3_             = _mm_mul_ps(inv_norm, p3_);
    }

    [[nodiscard]] point inverse() const noexcept
    {
        point out = *this;
        out.invert();
        return out;
    }

    [[nodiscard]] float x() const noexcept
    {
        float out[4];
        _mm_store_ps(out, p3_);
        return out[1];
    }

    [[nodiscard]] float e032() const noexcept
    {
        return x();
    }

    [[nodiscard]] float y() const noexcept
    {
        float out[4];
        _mm_store_ps(out, p3_);
        return out[2];
    }

    [[nodiscard]] float e013() const noexcept
    {
        return y();
    }

    [[nodiscard]] float z() const noexcept
    {
        float out[4];
        _mm_store_ps(out, p3_);
        return out[3];
    }

    [[nodiscard]] float e021() const noexcept
    {
        return z();
    }

    /// The homogeneous coordinate `w` is exactly $1$ when normalized.
    [[nodiscard]] float w() const noexcept
    {
        float out;
        _mm_store_ss(&out, p3_);
        return out;
    }

    [[nodiscard]] float e123() const noexcept
    {
        return w();
    }

    /// Point addition
    point& KLN_VEC_CALL operator+=(point b) noexcept
    {
        p3_ = _mm_add_ps(p3_, b.p3_);
        return *this;
    }

    /// Point subtraction
    point& KLN_VEC_CALL operator-=(point b) noexcept
    {
        p3_ = _mm_sub_ps(p3_, b.p3_);
        return *this;
    }

    /// Point uniform scale
    point& operator*=(float s) noexcept
    {
        p3_ = _mm_mul_ps(p3_, _mm_set1_ps(s));
        return *this;
    }

    /// Point uniform scale
    point& operator*=(int s) noexcept
    {
        p3_ = _mm_mul_ps(p3_, _mm_set1_ps(static_cast<float>(s)));
        return *this;
    }

    /// Point uniform inverse scale
    point& operator/=(float s) noexcept
    {
        p3_ = _mm_mul_ps(p3_, detail::rcp_nr1(_mm_set1_ps(s)));
        return *this;
    }

    /// Point uniform inverse scale
    point& operator/=(int s) noexcept
    {
        p3_ = _mm_mul_ps(
            p3_, detail::rcp_nr1(_mm_set1_ps(static_cast<float>(s))));
        return *this;
    }

    __m128 p3_;
};

/// Point addition
[[nodiscard]] inline point KLN_VEC_CALL operator+(point a, point b) noexcept
{
    point c;
    c.p3_ = _mm_add_ps(a.p3_, b.p3_);
    return c;
}

/// Point subtraction
[[nodiscard]] inline point KLN_VEC_CALL operator-(point a, point b) noexcept
{
    point c;
    c.p3_ = _mm_sub_ps(a.p3_, b.p3_);
    return c;
}

/// Point uniform scale
[[nodiscard]] inline point KLN_VEC_CALL operator*(point p, float s) noexcept
{
    point c;
    c.p3_ = _mm_mul_ps(p.p3_, _mm_set1_ps(s));
    return c;
}

/// Point uniform scale
[[nodiscard]] inline point KLN_VEC_CALL operator*(float s, point p) noexcept
{
    return p * s;
}

/// Point uniform scale
[[nodiscard]] inline point KLN_VEC_CALL operator*(point p, int s) noexcept
{
    return p * static_cast<float>(s);
}

/// Point uniform scale
[[nodiscard]] inline point KLN_VEC_CALL operator*(int s, point p) noexcept
{
    return p * static_cast<float>(s);
}

/// Point uniform inverse scale
[[nodiscard]] inline point KLN_VEC_CALL operator/(point p, float s) noexcept
{
    point c;
    c.p3_ = _mm_mul_ps(p.p3_, detail::rcp_nr1(_mm_set1_ps(s)));
    return c;
}

/// Point uniform inverse scale
[[nodiscard]] inline point KLN_VEC_CALL operator/(point p, int s) noexcept
{
    return p / static_cast<float>(s);
}

/// Unary minus (leaves homogeneous coordinate untouched)
[[nodiscard]] inline point KLN_VEC_CALL operator-(point p) noexcept
{
    return {_mm_xor_ps(p.p3_, _mm_set_ps(-0.f, -0.f, -0.f, 0.f))};
}

/// Reversion operator
[[nodiscard]] inline point KLN_VEC_CALL operator~(point p) noexcept
{
    __m128 flip = _mm_set1_ps(-0.f);
    return {_mm_xor_ps(p.p3_, flip)};
}

/// The origin is a convenience type that occupies no memory but is castable to
/// a point entity. Several operations like conjugation of the origin by a motor
/// is optimized.
struct origin
{
    /// On its own, the origin occupies no memory, but it can be casted as an
    /// entity at any point, at which point it is represented as
    /// $\mathbf{e}_{123}$.
    operator point() const noexcept
    {
        point out;
        out.p3_ = _mm_set_ss(1.f);
        return out;
    }
};
} // namespace kln
/// @}
