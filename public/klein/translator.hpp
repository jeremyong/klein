#pragma once

#include "detail/matrix.hpp"
#include "line.hpp"
#include "mat4x4.hpp"
#include "plane.hpp"
#include "point.hpp"

namespace kln
{
/// \defgroup translator Translators
///
/// A translator represents a rigid-body displacement along a normalized axis.
/// To apply the translator to a supported entity, the call operator is
/// available.
///
/// !!! example
///
///     ```c++
///         // Initialize a point at (1, 3, 2)
///         kln::point p{1.f, 3.f, 2.f};
///
///         // Create a normalized translator representing a 4-unit
///         // displacement along the xz-axis.
///         kln::translator r{4.f, 1.f, 0.f, 1.f};
///
///         // Displace our point using the created translator
///         kln::point translated = r(p);
///     ```
///     We can translate lines and planes as well using the translator's call
///     operator.
///
/// Translators can be multiplied to one another with the `*` operator to create
/// a new translator equivalent to the application of each factor.
///
/// !!! example
///
///     ```c++
///         // Suppose we have 3 translators t1, t2, and t3
///
///         // The translator t created here represents the combined action of
///         // t1, t2, and t3.
///         kln::translator t = t3 * t2 * t1;
///     ```
///
/// The same `*` operator can be used to compose the translator's action with
/// other rotors and motors.

/// \addtogroup translator
/// @{
class translator final
{
public:
    translator() noexcept = default;

    translator(float delta, float x, float y, float z) noexcept
    {
        float norm     = std::sqrt(x * x + y * y + z * z);
        float inv_norm = 1.f / norm;

        float half_d = -0.5f * delta;
        p2_ = _mm_mul_ps(_mm_set1_ps(half_d), _mm_set_ps(z, y, x, 0.f));
        p2_ = _mm_mul_ps(p2_, _mm_set_ps(inv_norm, inv_norm, inv_norm, 0.f));
    }

    /// Fast load operation for packed data that is already normalized. The
    /// argument `data` should point to a set of 4 float values with layout
    /// `(0.f, a, b, c)` corresponding to the multivector $a\mathbf{e}_{01} +
    /// b\mathbf{e}_{02} + c\mathbf{e}_{03}$.
    ///
    /// !!! danger
    ///
    ///     The translator data loaded this way *must* be normalized. That is,
    ///     the quantity $-\sqrt{a^2 + b^2 + c^2}$ must be half the desired
    ///     displacement.
    void load_normalized(float* data) noexcept
    {
        p2_ = _mm_loadu_ps(data);
    }

    void invert() noexcept
    {
        p2_ = _mm_xor_ps(_mm_set_ps(-0.f, -0.f, -0.f, 0.f), p2_);
    }

    [[nodiscard]] translator inverse() const noexcept
    {
        translator out = *this;
        out.invert();
        return out;
    }

    /// Conjugates a plane $p$ with this translator and returns the result
    /// $tp\widetilde{t}$.
    [[nodiscard]] plane KLN_VEC_CALL operator()(plane const& p) const noexcept
    {
        plane out;
#ifdef KLEIN_SSE_4_1
        __m128 tmp = _mm_blend_ps(p2_, _mm_set_ss(1.f), 1);
#else
        __m128 tmp = _mm_add_ps(p2_, _mm_set_ss(1.f));
#endif
        out.p0_ = detail::sw02(p.p0_, tmp);
        return out;
    }

    /// Conjugates a line $\ell$ with this translator and returns the result
    /// $t\ell\widetilde{t}$.
    [[nodiscard]] line KLN_VEC_CALL operator()(line const& l) const noexcept
    {
        line out;
        detail::swL2(l.p1_, l.p2_, p2_, &out.p1_);
        return out;
    }

    /// Conjugates a point $p$ with this translator and returns the result
    /// $tp\widetilde{t}$.
    [[nodiscard]] point KLN_VEC_CALL operator()(point const& p) const noexcept
    {
        point out;
        out.p3_ = detail::sw32(p.p3_, p2_);
        return out;
    }

    /// Translator addition
    translator& KLN_VEC_CALL operator+=(translator b) noexcept
    {
        p2_ = _mm_add_ps(p2_, b.p2_);
        return *this;
    }

    /// Translator subtraction
    translator& KLN_VEC_CALL operator-=(translator b) noexcept
    {
        p2_ = _mm_sub_ps(p2_, b.p2_);
        return *this;
    }

    /// Translator uniform scale
    translator& operator*=(float s) noexcept
    {
        p2_ = _mm_mul_ps(p2_, _mm_set1_ps(s));
        return *this;
    }

    /// Translator uniform scale
    translator& operator*=(int s) noexcept
    {
        p2_ = _mm_mul_ps(p2_, _mm_set1_ps(static_cast<float>(s)));
        return *this;
    }

    /// Translator uniform inverse scale
    translator& operator/=(float s) noexcept
    {
        p2_ = _mm_mul_ps(p2_, detail::rcp_nr1(_mm_set1_ps(s)));
        return *this;
    }

    /// Translator uniform inverse scale
    translator& operator/=(int s) noexcept
    {
        p2_ = _mm_mul_ps(
            p2_, detail::rcp_nr1(_mm_set1_ps(static_cast<float>(s))));
        return *this;
    }

    constexpr float scalar() const noexcept
    {
        return 1.f;
    }

    [[nodiscard]] float e01() const noexcept
    {
        float out[4];
        _mm_store_ps(out, p2_);
        return out[1];
    }

    [[nodiscard]] float e10() const noexcept
    {
        return -e01();
    }

    [[nodiscard]] float e02() const noexcept
    {
        float out[4];
        _mm_store_ps(out, p2_);
        return out[2];
    }

    [[nodiscard]] float e20() const noexcept
    {
        return -e02();
    }

    [[nodiscard]] float e03() const noexcept
    {
        float out[4];
        _mm_store_ps(out, p2_);
        return out[3];
    }

    [[nodiscard]] float e30() const noexcept
    {
        return -e03();
    }

    __m128 p2_;
};

/// Translator addition
[[nodiscard]] inline translator KLN_VEC_CALL operator+(translator a,
                                                       translator b) noexcept
{
    translator c;
    c.p2_ = _mm_add_ps(a.p2_, b.p2_);
    return c;
}

/// Translator subtraction
[[nodiscard]] inline translator KLN_VEC_CALL operator-(translator a,
                                                       translator b) noexcept
{
    translator c;
    c.p2_ = _mm_sub_ps(a.p2_, b.p2_);
    return c;
}

/// Translator uniform scale
[[nodiscard]] inline translator KLN_VEC_CALL operator*(translator t,
                                                       float s) noexcept
{
    translator c;
    c.p2_ = _mm_mul_ps(t.p2_, _mm_set1_ps(s));
    return c;
}

/// Translator uniform scale
[[nodiscard]] inline translator KLN_VEC_CALL operator*(translator t, int s) noexcept
{
    translator c;
    c.p2_ = _mm_mul_ps(t.p2_, _mm_set1_ps(static_cast<float>(s)));
    return c;
}

/// Translator uniform scale
[[nodiscard]] inline translator KLN_VEC_CALL operator*(float s,
                                                       translator t) noexcept
{
    return t * s;
}

/// Translator uniform scale
[[nodiscard]] inline translator KLN_VEC_CALL operator*(int s, translator t) noexcept
{
    return t * s;
}

/// Translator uniform inverse scale
[[nodiscard]] inline translator KLN_VEC_CALL operator/(translator t,
                                                       float s) noexcept
{
    translator c;
    c.p2_ = _mm_mul_ps(t.p2_, detail::rcp_nr1(_mm_set1_ps(s)));
    return c;
}

/// Translator uniform inverse scale
[[nodiscard]] inline translator KLN_VEC_CALL operator/(translator t, int s) noexcept
{
    return t / static_cast<float>(s);
}
} // namespace kln
/// @}
