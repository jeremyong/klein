#pragma once

#include "detail/sse.hpp"
#include <cmath>

namespace kln
{
/// \defgroup lines Lines
/// Klein provides three line classes: "line", "branch", and "ideal_line". The
/// line class represents a full six-coordinate bivector. The branch contains
/// three non-degenerate components (aka, a line through the origin). The ideal
/// line represents the line at infinity. When the line is created as a meet
/// of two planes or join of two points (or carefully selected Plücker
/// coordinates), it will be a Euclidean line (factorizable as the meet of two
/// vectors).

/// \addtogroup lines
/// @{

/// An ideal line represents a line at infinity and corresponds to the
/// multivector:
///
/// $$a\mathbf{e}_{01} + b\mathbf{e}_{02} + c\mathbf{e}_{03}$$
/// \ingroup lines
class ideal_line final
{
public:
    ideal_line() noexcept = default;

    ideal_line(float a, float b, float c) noexcept
        : p2_{_mm_set_ps(c, b, a, 0.f)}
    {}

    ideal_line(__m128 xmm) noexcept
        : p2_{xmm}
    {}

    [[nodiscard]] float squared_ideal_norm() noexcept
    {
        float out;
        __m128 dp = detail::hi_dp(p2_, p2_);
        _mm_store_ss(&out, dp);
        return out;
    }

    [[nodiscard]] float ideal_norm() noexcept
    {
        return std::sqrt(squared_ideal_norm());
    }

    /// Ideal line addition
    ideal_line& KLN_VEC_CALL operator+=(ideal_line b) noexcept
    {
        p2_ = _mm_add_ps(p2_, b.p2_);
        return *this;
    }

    /// Ideal line subtraction
    ideal_line& KLN_VEC_CALL operator-=(ideal_line b) noexcept
    {
        p2_ = _mm_sub_ps(p2_, b.p2_);
        return *this;
    }

    /// Ideal line uniform scale
    ideal_line& operator*=(float s) noexcept
    {
        p2_ = _mm_mul_ps(p2_, _mm_set1_ps(s));
        return *this;
    }

    /// Ideal line uniform scale
    ideal_line& operator*=(int s) noexcept
    {
        p2_ = _mm_mul_ps(p2_, _mm_set1_ps(static_cast<float>(s)));
        return *this;
    }

    /// Ideal line uniform inverse scale
    ideal_line& operator/=(float s) noexcept
    {
        p2_ = _mm_mul_ps(p2_, detail::rcp_nr1(_mm_set1_ps(s)));
        return *this;
    }

    /// Ideal line uniform inverse scale
    ideal_line& operator/=(int s) noexcept
    {
        p2_ = _mm_mul_ps(
            p2_, detail::rcp_nr1(_mm_set1_ps(static_cast<float>(s))));
        return *this;
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

/// Ideal line addition
[[nodiscard]] inline ideal_line KLN_VEC_CALL operator+(ideal_line a,
                                                       ideal_line b) noexcept
{
    ideal_line c;
    c.p2_ = _mm_add_ps(a.p2_, b.p2_);
    return c;
}

/// Ideal line subtraction
[[nodiscard]] inline ideal_line KLN_VEC_CALL operator-(ideal_line a,
                                                       ideal_line b) noexcept
{
    ideal_line c;
    c.p2_ = _mm_sub_ps(a.p2_, b.p2_);
    return c;
}

/// Ideal line uniform scale
[[nodiscard]] inline ideal_line KLN_VEC_CALL operator*(ideal_line l,
                                                       float s) noexcept
{
    ideal_line c;
    c.p2_ = _mm_mul_ps(l.p2_, _mm_set1_ps(s));
    return c;
}

/// Ideal line uniform scale
[[nodiscard]] inline ideal_line KLN_VEC_CALL operator*(ideal_line l, int s) noexcept
{
    ideal_line c;
    c.p2_ = _mm_mul_ps(l.p2_, _mm_set1_ps(static_cast<float>(s)));
    return c;
}

/// Ideal line uniform scale
[[nodiscard]] inline ideal_line KLN_VEC_CALL operator*(float s,
                                                       ideal_line l) noexcept
{
    return l * s;
}

/// Ideal line uniform scale
[[nodiscard]] inline ideal_line KLN_VEC_CALL operator*(int s, ideal_line l) noexcept
{
    return l * static_cast<float>(s);
}

/// Ideal line uniform inverse scale
[[nodiscard]] inline ideal_line KLN_VEC_CALL operator/(ideal_line l,
                                                       float s) noexcept
{
    ideal_line c;
    c.p2_ = _mm_mul_ps(l.p2_, detail::rcp_nr1(_mm_set1_ps(s)));
    return c;
}

[[nodiscard]] inline ideal_line KLN_VEC_CALL operator/(ideal_line l, int s) noexcept
{
    return l / static_cast<float>(s);
}

/// Unary minus
[[nodiscard]] inline ideal_line KLN_VEC_CALL operator-(ideal_line l) noexcept
{
    return {_mm_xor_ps(l.p2_, _mm_set1_ps(-0.f))};
}

/// Reversion operator
[[nodiscard]] inline ideal_line KLN_VEC_CALL operator~(ideal_line l) noexcept
{
    __m128 flip = _mm_set_ps(-0.f, -0.f, -0.f, 0.f);
    return {_mm_xor_ps(l.p2_, flip)};
}

/// The `branch` both a line through the origin and also the principal branch of
/// the logarithm of a rotor.
///
/// The rotor branch will be most commonly constructed by taking the
/// logarithm of a normalized rotor. The branch may then be linearily scaled
/// to adjust the "strength" of the rotor, and subsequently re-exponentiated
/// to create the adjusted rotor.
///
/// !!! example
///
///     Suppose we have a rotor $r$ and we wish to produce a rotor
///     $\sqrt[4]{r}$ which performs a quarter of the rotation produced by
///     $r$. We can construct it like so:
///
///     ```c++
///         kln::branch b = r.log();
///         kln::rotor r_4 = (0.25f * b).exp();
///     ```
///
/// !!! note
///
///     The branch of a rotor is technically a `line`, but because there are
///     no translational components, the branch is given its own type for
///     efficiency.
/// \ingroup lines
class branch final
{
public:
    branch() = default;

    /// Construct the branch as the following multivector:
    ///
    /// $$a \mathbf{e}_{23} + b\mathbf{e}_{31} + c\mathbf{e}_{12}$$
    ///
    /// To convince yourself this is a line through the origin, remember that
    /// such a line can be generated using the geometric product of two planes
    /// through the origin.
    branch(float a, float b, float c) noexcept
        : p1_{_mm_set_ps(c, b, a, 0.f)}
    {}

    branch(__m128 xmm) noexcept
        : p1_{xmm}
    {}

    /// If a line is constructed as the regressive product (join) of
    /// two points, the squared norm provided here is the squared
    /// distance between the two points (provided the points are
    /// normalized). Returns $d^2 + e^2 + f^2$.
    [[nodiscard]] float squared_norm() noexcept
    {
        float out;
        __m128 dp = detail::hi_dp(p1_, p1_);
        _mm_store_ss(&out, dp);
        return out;
    }

    /// Returns the square root of the quantity produced by `squared_norm`.
    [[nodiscard]] float norm() noexcept
    {
        return std::sqrt(squared_norm());
    }

    void normalize() noexcept
    {
        __m128 inv_norm = detail::rsqrt_nr1(detail::hi_dp_bc(p1_, p1_));
        p1_             = _mm_mul_ps(p1_, inv_norm);
    }

    [[nodiscard]] branch normalized() const noexcept
    {
        branch out = *this;
        out.normalize();
        return out;
    }

    void invert() noexcept
    {
        __m128 inv_norm = detail::rsqrt_nr1(detail::hi_dp_bc(p1_, p1_));
        p1_             = _mm_mul_ps(p1_, inv_norm);
        p1_             = _mm_mul_ps(p1_, inv_norm);
        p1_             = _mm_xor_ps(_mm_set_ps(-0.f, -0.f, -0.f, 0.f), p1_);
    }

    [[nodiscard]] branch inverse() const noexcept
    {
        branch out = *this;
        out.invert();
        return out;
    }

    /// Branch addition
    branch& KLN_VEC_CALL operator+=(branch b) noexcept
    {
        p1_ = _mm_add_ps(p1_, b.p1_);
        return *this;
    }

    /// Branch subtraction
    branch& KLN_VEC_CALL operator-=(branch b) noexcept
    {
        p1_ = _mm_sub_ps(p1_, b.p1_);
        return *this;
    }

    /// Branch uniform scale
    branch& operator*=(float s) noexcept
    {
        p1_ = _mm_mul_ps(p1_, _mm_set1_ps(s));
        return *this;
    }

    /// Branch uniform scale
    branch& operator*=(int s) noexcept
    {
        p1_ = _mm_mul_ps(p1_, _mm_set1_ps(static_cast<float>(s)));
        return *this;
    }

    /// Branch uniform inverse scale
    branch& operator/=(float s) noexcept
    {
        p1_ = _mm_mul_ps(p1_, detail::rcp_nr1(_mm_set1_ps(s)));
        return *this;
    }

    /// Branch uniform inverse scale
    branch& operator/=(int s) noexcept
    {
        p1_ = _mm_mul_ps(
            p1_, detail::rcp_nr1(_mm_set1_ps(static_cast<float>(s))));
        return *this;
    }

    /// Store m128 contents into an array of 4 floats
    void store(float* buf) const noexcept
    {
        _mm_store_ps(buf, p1_);
    }

    [[nodiscard]] float e12() const noexcept
    {
        float out[4];
        _mm_store_ps(out, p1_);
        return out[3];
    }

    [[nodiscard]] float e21() const noexcept
    {
        return -e12();
    }

    [[nodiscard]] float z() const noexcept
    {
        return e12();
    }

    [[nodiscard]] float e31() const noexcept
    {
        float out[4];
        _mm_store_ps(out, p1_);
        return out[2];
    }

    [[nodiscard]] float e13() const noexcept
    {
        return -e31();
    }

    [[nodiscard]] float y() const noexcept
    {
        return e31();
    }

    [[nodiscard]] float e23() const noexcept
    {
        float out[4];
        _mm_store_ps(out, p1_);
        return out[1];
    }

    [[nodiscard]] float e32() const noexcept
    {
        return -e23();
    }

    [[nodiscard]] float x() const noexcept
    {
        return e23();
    }

    __m128 p1_;
};

/// Branch addition
[[nodiscard]] inline branch KLN_VEC_CALL operator+(branch a, branch b) noexcept
{
    branch c;
    c.p1_ = _mm_add_ps(a.p1_, b.p1_);
    return c;
}

/// Branch subtraction
[[nodiscard]] inline branch KLN_VEC_CALL operator-(branch a, branch b) noexcept
{
    branch c;
    c.p1_ = _mm_sub_ps(a.p1_, b.p1_);
    return c;
}

/// Branch uniform scale
[[nodiscard]] inline branch KLN_VEC_CALL operator*(branch b, float s) noexcept
{
    branch c;
    c.p1_ = _mm_mul_ps(b.p1_, _mm_set1_ps(s));
    return c;
}

/// Branch uniform scale
[[nodiscard]] inline branch KLN_VEC_CALL operator*(branch b, int s) noexcept
{
    return b * static_cast<float>(s);
}

/// Branch uniform scale
[[nodiscard]] inline branch KLN_VEC_CALL operator*(float s, branch b) noexcept
{
    return b * s;
}

/// Branch uniform scale
[[nodiscard]] inline branch KLN_VEC_CALL operator*(int s, branch b) noexcept
{
    return b * static_cast<float>(s);
}

/// Branch uniform inverse scale
[[nodiscard]] inline branch KLN_VEC_CALL operator/(branch b, float s) noexcept
{
    branch c;
    c.p1_ = _mm_mul_ps(b.p1_, detail::rcp_nr1(_mm_set1_ps(s)));
    return c;
}

/// Branch uniform inverse scale
[[nodiscard]] inline branch KLN_VEC_CALL operator/(branch b, int s) noexcept
{
    return b / static_cast<float>(s);
}

/// Unary minus
[[nodiscard]] inline branch KLN_VEC_CALL operator-(branch b) noexcept
{
    return {_mm_xor_ps(b.p1_, _mm_set1_ps(-0.f))};
}

/// Reversion operator
[[nodiscard]] inline branch KLN_VEC_CALL operator~(branch b) noexcept
{
    __m128 flip = _mm_set_ps(-0.f, -0.f, -0.f, 0.f);
    return {_mm_xor_ps(b.p1_, flip)};
}

// p1: (1, e12, e31, e23)
// p2: (e0123, e01, e02, e03)

/// A general line in $\PGA$ is given as a 6-coordinate bivector with a direct
/// correspondence to Plücker coordinates. All lines can be exponentiated using
/// the `exp` method to generate a motor.
///
/// \ingroup lines
class line final
{
public:
    line() noexcept = default;

    /// A line is specifed by 6 coordinates which correspond to the line's
    /// [Plücker
    /// coordinates](https://en.wikipedia.org/wiki/Pl%C3%BCcker_coordinates).
    /// The coordinates specified in this way correspond to the following
    /// multivector:
    ///
    /// $$a\mathbf{e}_{01} + b\mathbf{e}_{02} + c\mathbf{e}_{03} +\
    /// d\mathbf{e}_{23} + e\mathbf{e}_{31} + f\mathbf{e}_{12}$$
    line(float a, float b, float c, float d, float e, float f) noexcept
        : p1_{_mm_set_ps(f, e, d, 0.f)}
        , p2_{_mm_set_ps(c, b, a, 0.f)}
    {}

    line(__m128 xmm1, __m128 xmm2) noexcept
        : p1_{xmm1}
        , p2_{xmm2}
    {}

    line(ideal_line other) noexcept
        : p1_{_mm_setzero_ps()}
        , p2_{other.p2_}
    {}

    line(branch other) noexcept
        : p1_{other.p1_}
        , p2_{_mm_setzero_ps()}
    {}

    /// Returns the square root of the quantity produced by
    /// `squared_norm`.
    [[nodiscard]] float norm() noexcept
    {
        return std::sqrt(squared_norm());
    }

    /// If a line is constructed as the regressive product (join) of
    /// two points, the squared norm provided here is the squared
    /// distance between the two points (provided the points are
    /// normalized). Returns $d^2 + e^2 + f^2$.
    [[nodiscard]] float squared_norm() noexcept
    {
        float out;
        __m128 dp = detail::hi_dp(p1_, p1_);
        _mm_store_ss(&out, dp);
        return out;
    }

    /// Normalize a line such that $\ell^2 = -1$.
    void normalize() noexcept
    {
        // l = b + c where b is p1 and c is p2
        // l * ~l = |b|^2 - 2(b1 c1 + b2 c2 + b3 c3)e0123
        //
        // sqrt(l*~l) = |b| - (b1 c1 + b2 c2 + b3 c3)/|b| e0123
        //
        // 1/sqrt(l*~l) = 1/|b| + (b1 c1 + b2 c2 + b3 c3)/|b|^3 e0123
        //              = s + t e0123
        __m128 b2 = detail::hi_dp_bc(p1_, p1_);
        __m128 s  = detail::rsqrt_nr1(b2);
        __m128 bc = detail::hi_dp_bc(p1_, p2_);
        __m128 t  = _mm_mul_ps(_mm_mul_ps(bc, detail::rcp_nr1(b2)), s);

        // p1 * (s + t e0123) = s * p1 - t p1_perp
        __m128 tmp = _mm_mul_ps(p2_, s);
        p2_        = _mm_sub_ps(tmp, _mm_mul_ps(p1_, t));
        p1_        = _mm_mul_ps(p1_, s);
    }

    /// Return a normalized copy of this line
    [[nodiscard]] line normalized() const noexcept
    {
        line out = *this;
        out.normalize();
        return out;
    }

    void invert() noexcept
    {
        // s, t computed as in the normalization
        __m128 b2     = detail::hi_dp_bc(p1_, p1_);
        __m128 s      = detail::rsqrt_nr1(b2);
        __m128 bc     = detail::hi_dp_bc(p1_, p2_);
        __m128 b2_inv = detail::rcp_nr1(b2);
        __m128 t      = _mm_mul_ps(_mm_mul_ps(bc, b2_inv), s);
        __m128 neg    = _mm_set_ps(-0.f, -0.f, -0.f, 0.f);

        // p1 * (s + t e0123)^2 = (s * p1 - t p1_perp) * (s + t e0123)
        // = s^2 p1 - s t p1_perp - s t p1_perp
        // = s^2 p1 - 2 s t p1_perp
        // p2 * (s + t e0123)^2 = s^2 p2
        // NOTE: s^2 = b2_inv
        __m128 st = _mm_mul_ps(s, t);
        st        = _mm_mul_ps(p1_, st);
        p2_       = _mm_sub_ps(_mm_mul_ps(p2_, b2_inv), _mm_add_ps(st, st));
        p2_       = _mm_xor_ps(p2_, neg);

        p1_ = _mm_xor_ps(_mm_mul_ps(p1_, b2_inv), neg);
    }

    [[nodiscard]] line inverse() const noexcept
    {
        line out = *this;
        out.invert();
        return out;
    }

    /// Bitwise comparison
    [[nodiscard]] bool KLN_VEC_CALL operator==(line other) const noexcept
    {
        __m128 p1_eq = _mm_cmpeq_ps(p1_, other.p1_);
        __m128 p2_eq = _mm_cmpeq_ps(p2_, other.p2_);
        __m128 eq    = _mm_and_ps(p1_eq, p2_eq);
        return _mm_movemask_ps(eq) == 0xf;
    }

    [[nodiscard]] bool KLN_VEC_CALL approx_eq(line other,
                                              float epsilon) const noexcept
    {
        __m128 eps = _mm_set1_ps(epsilon);
        __m128 neg = _mm_set1_ps(-0.f);
        __m128 cmp1
            = _mm_cmplt_ps(_mm_andnot_ps(neg, _mm_sub_ps(p1_, other.p1_)), eps);
        __m128 cmp2
            = _mm_cmplt_ps(_mm_andnot_ps(neg, _mm_sub_ps(p2_, other.p2_)), eps);
        __m128 cmp = _mm_and_ps(cmp1, cmp2);
        return _mm_movemask_ps(cmp) == 0xf;
    }

    /// Line addition
    line& KLN_VEC_CALL operator+=(line b) noexcept
    {
        p1_ = _mm_add_ps(p1_, b.p1_);
        p2_ = _mm_add_ps(p2_, b.p2_);
        return *this;
    }

    /// Line subtraction
    line& KLN_VEC_CALL operator-=(line b) noexcept
    {
        p1_ = _mm_sub_ps(p1_, b.p1_);
        p2_ = _mm_sub_ps(p2_, b.p2_);
        return *this;
    }

    /// Line uniform scale
    line& operator*=(float s) noexcept
    {
        __m128 vs = _mm_set1_ps(s);
        p1_       = _mm_mul_ps(p1_, vs);
        p2_       = _mm_mul_ps(p2_, vs);
        return *this;
    }

    /// Line uniform scale
    line& operator*=(int s) noexcept
    {
        __m128 vs = _mm_set1_ps(static_cast<float>(s));
        p1_       = _mm_mul_ps(p1_, vs);
        p2_       = _mm_mul_ps(p2_, vs);
        return *this;
    }

    /// Line uniform inverse scale
    line& operator/=(float s) noexcept
    {
        __m128 vs = detail::rcp_nr1(_mm_set1_ps(s));
        p1_       = _mm_mul_ps(p1_, vs);
        p2_       = _mm_mul_ps(p2_, vs);
        return *this;
    }

    /// Line uniform inverse scale
    line& operator/=(int s) noexcept
    {
        __m128 vs = detail::rcp_nr1(_mm_set1_ps(static_cast<float>(s)));
        p1_       = _mm_mul_ps(p1_, vs);
        p2_       = _mm_mul_ps(p2_, vs);
        return *this;
    }

    [[nodiscard]] float e12() const noexcept
    {
        float out[4];
        _mm_store_ps(out, p1_);
        return out[3];
    }

    [[nodiscard]] float e21() const noexcept
    {
        return -e12();
    }

    [[nodiscard]] float e31() const noexcept
    {
        float out[4];
        _mm_store_ps(out, p1_);
        return out[2];
    }

    [[nodiscard]] float e13() const noexcept
    {
        return -e31();
    }

    [[nodiscard]] float e23() const noexcept
    {
        float out[4];
        _mm_store_ps(out, p1_);
        return out[1];
    }

    [[nodiscard]] float e32() const noexcept
    {
        return -e23();
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

    __m128 p1_;
    __m128 p2_;
};

/// Line addition
[[nodiscard]] inline line KLN_VEC_CALL operator+(line a, line b) noexcept
{
    line c;
    c.p1_ = _mm_add_ps(a.p1_, b.p1_);
    c.p2_ = _mm_add_ps(a.p2_, b.p2_);
    return c;
}

/// Line subtraction
[[nodiscard]] inline line KLN_VEC_CALL operator-(line a, line b) noexcept
{
    line c;
    c.p1_ = _mm_sub_ps(a.p1_, b.p1_);
    c.p2_ = _mm_sub_ps(a.p2_, b.p2_);
    return c;
}

/// Line uniform scale
[[nodiscard]] inline line KLN_VEC_CALL operator*(line l, float s) noexcept
{
    line c;
    __m128 vs = _mm_set1_ps(s);
    c.p1_     = _mm_mul_ps(l.p1_, vs);
    c.p2_     = _mm_mul_ps(l.p2_, vs);
    return c;
}

/// Line uniform scale
[[nodiscard]] inline line KLN_VEC_CALL operator*(line l, int s) noexcept
{
    return l * static_cast<float>(s);
}

/// Line uniform scale
[[nodiscard]] inline line KLN_VEC_CALL operator*(float s, line l) noexcept
{
    return l * s;
}

/// Line uniform scale
[[nodiscard]] inline line KLN_VEC_CALL operator*(int s, line l) noexcept
{
    return l * static_cast<float>(s);
}

/// Line uniform inverse scale
[[nodiscard]] inline line KLN_VEC_CALL operator/(line r, float s) noexcept
{
    line c;
    __m128 vs = detail::rcp_nr1(_mm_set1_ps(static_cast<float>(s)));
    c.p1_     = _mm_mul_ps(r.p1_, vs);
    c.p2_     = _mm_mul_ps(r.p2_, vs);
    return c;
}

/// Line uniform inverse scale
[[nodiscard]] inline line KLN_VEC_CALL operator/(line r, int s) noexcept
{
    return r / static_cast<float>(s);
}

/// Unary minus
[[nodiscard]] inline line KLN_VEC_CALL operator-(line l) noexcept
{
    __m128 flip = _mm_set1_ps(-0.f);
    return {_mm_xor_ps(l.p1_, flip), _mm_xor_ps(l.p2_, flip)};
}

/// Reversion operator
[[nodiscard]] inline line KLN_VEC_CALL operator~(line l) noexcept
{
    __m128 flip = _mm_set_ps(-0.f, -0.f, -0.f, 0.f);
    return {_mm_xor_ps(l.p1_, flip), _mm_xor_ps(l.p2_, flip)};
}
} // namespace kln
/// @}
