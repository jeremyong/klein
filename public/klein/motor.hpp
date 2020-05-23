#pragma once

#include "detail/exp_log.hpp"
#include "detail/geometric_product.hpp"
#include "detail/matrix.hpp"
#include "detail/sandwich.hpp"
#include "detail/sse.hpp"
#include "direction.hpp"
#include "line.hpp"
#include "mat3x4.hpp"
#include "mat4x4.hpp"
#include "plane.hpp"
#include "point.hpp"
#include "rotor.hpp"
#include "translator.hpp"

namespace kln
{
/// \defgroup motor Motors
///
/// A `motor` represents a kinematic motion in our algebra. From
/// [Chasles'
/// theorem](https://en.wikipedia.org/wiki/Chasles%27_theorem_(kinematics)), we
/// know that any rigid body displacement can be produced by a translation along
/// a line, followed or preceded by a rotation about an axis parallel to that
/// line. The motor algebra is isomorphic to the dual quaternions but exists
/// here in the same algebra as all the other geometric entities and actions at
/// our disposal. Operations such as composing a motor with a rotor or
/// translator are possible for example. The primary benefit to using a motor
/// over its corresponding matrix operation is twofold. First, you get the
/// benefit of numerical stability when composing multiple actions via the
/// geometric product (`*`). Second, because the motors constitute a continuous
/// group, they are amenable to smooth interpolation and differentiation.
///
/// !!! example
///
///     ```c++
///         // Create a rotor representing a pi/2 rotation about the z-axis
///         // Normalization is done automatically
///         rotor r{kln::pi * 0.5f, 0.f, 0.f, 1.f};
///
///         // Create a translator that represents a translation of 1 unit
///         // in the yz-direction. Normalization is done automatically.
///         translator t{1.f, 0.f, 1.f, 1.f};
///
///         // Create a motor that combines the action of the rotation and
///         // translation above.
///         motor m = r * t;
///
///         // Initialize a point at (1, 3, 2)
///         kln::point p1{1.f, 3.f, 2.f};
///
///         // Translate p1 and rotate it to create a new point p2
///         kln::point p2 = m(p1);
///     ```
///
/// Motors can be multiplied to one another with the `*` operator to create
/// a new motor equivalent to the application of each factor.
///
/// !!! example
///
///     ```c++
///         // Suppose we have 3 motors m1, m2, and m3
///
///         // The motor m created here represents the combined action of m1,
///         // m2, and m3.
///         kln::motor m = m3 * m2 * m1;
///     ```
///
/// The same `*` operator can be used to compose the motor's action with other
/// translators and rotors.
///
/// A demonstration of using the exponential and logarithmic map to blend
/// between two motors is provided in a test case
/// [here](https://github.com/jeremyong/Klein/blob/master/test/test_exp_log.cpp#L48).

/// \addtogroup motor
/// @{
/// \ingroup motor
class motor final
{
public:
    motor() noexcept = default;

    /// Direct initialization from components. A more common way of creating a
    /// motor is to take a product between a rotor and a translator.
    /// The arguments coorespond to the multivector
    /// $a + b\mathbf{e}_{23} + c\mathbf{e}_{31} + d\mathbf{e}_{12} +\
    /// e\mathbf{e}_{01} + f\mathbf{e}_{02} + g\mathbf{e}_{03} +\
    /// h\mathbf{e}_{0123}$.
    motor(float a, float b, float c, float d, float e, float f, float g, float h) noexcept
        : p1_{_mm_set_ps(d, c, b, a)}
        , p2_{_mm_set_ps(g, f, e, h)}
    {}

    /// Produce a screw motion rotating and translating by given amounts along a
    /// provided Euclidean axis.
    motor(float ang_rad, float d, line l) noexcept
    {
        line log_m;
        detail::gpDL(
            -ang_rad * 0.5f, d * 0.5f, l.p1_, l.p2_, log_m.p1_, log_m.p2_);
        detail::exp(log_m.p1_, log_m.p2_, p1_, p2_);
    }

    motor(__m128 p1, __m128 p2) noexcept
        : p1_{p1}
        , p2_{p2}
    {}

    explicit motor(rotor r) noexcept
        : p1_{r.p1_}
        , p2_{_mm_setzero_ps()}
    {}

    explicit motor(translator t) noexcept
        : p1_{_mm_set_ss(1.f)}
        , p2_{t.p2_}
    {}

    motor& KLN_VEC_CALL operator=(rotor r) noexcept
    {
        p1_ = r.p1_;
        p2_ = _mm_setzero_ps();
        return *this;
    }

    motor& KLN_VEC_CALL operator=(translator t) noexcept
    {
        p1_ = _mm_setzero_ps();
        p2_ = t.p2_;
        return *this;
    }

    /// Load motor data using two unaligned loads. This routine does *not*
    /// assume the data passed in this way is normalized.
    void load(float* in) noexcept
    {
        // Aligned and unaligned loads incur the same amount of latency and have
        // identical throughput on most modern processors
        p1_ = _mm_loadu_ps(in);
        p2_ = _mm_loadu_ps(in + 4);
    }

    /// Normalizes this motor $m$ such that $m\widetilde{m} = 1$.
    void normalize() noexcept
    {
        // m = b + c where b is p1 and c is p2
        //
        // m * ~m = |b|^2 + 2(b0 c0 - b1 c1 - b2 c2 - b3 c3)e0123
        //
        // The square root is given as:
        // |b| + (b0 c0 - b1 c1 - b2 c2 - b3 c3)/|b| e0123
        //
        // The inverse of this is given by:
        // 1/|b| + (-b0 c0 + b1 c1 + b2 c2 + b3 c3)/|b|^3 e0123 = s + t e0123
        //
        // Multiplying our original motor by this inverse will give us a
        // normalized motor.
        __m128 b2 = detail::dp_bc(p1_, p1_);
        __m128 s  = detail::rsqrt_nr1(b2);
        __m128 bc = detail::dp_bc(_mm_xor_ps(p1_, _mm_set_ss(-0.f)), p2_);
        __m128 t  = _mm_mul_ps(_mm_mul_ps(bc, detail::rcp_nr1(b2)), s);

        // (s + t e0123) * motor =
        //
        // s b0 +
        // s b1 e23 +
        // s b2 e31 +
        // s b3 e12 +
        // (s c0 + t b0) e0123 +
        // (s c1 - t b1) e01 +
        // (s c2 - t b2) e02 +
        // (s c3 - t b3) e03

        __m128 tmp = _mm_mul_ps(p2_, s);
        p2_ = _mm_sub_ps(tmp, _mm_xor_ps(_mm_mul_ps(p1_, t), _mm_set_ss(-0.f)));
        p1_ = _mm_mul_ps(p1_, s);
    }

    /// Return a normalized copy of this motor.
    [[nodiscard]] motor normalized() const noexcept
    {
        motor out = *this;
        out.normalize();
        return out;
    }

    void invert() noexcept
    {
        // s, t computed as in the normalization
        __m128 b2     = detail::dp_bc(p1_, p1_);
        __m128 s      = detail::rsqrt_nr1(b2);
        __m128 bc     = detail::dp_bc(_mm_xor_ps(p1_, _mm_set_ss(-0.f)), p2_);
        __m128 b2_inv = detail::rcp_nr1(b2);
        __m128 t      = _mm_mul_ps(_mm_mul_ps(bc, b2_inv), s);
        __m128 neg    = _mm_set_ps(-0.f, -0.f, -0.f, 0.f);

        // p1 * (s + t e0123)^2 = (s * p1 - t p1_perp) * (s + t e0123)
        // = s^2 p1 - s t p1_perp - s t p1_perp
        // = s^2 p1 - 2 s t p1_perp
        // (the scalar component above needs to be negated)
        // p2 * (s + t e0123)^2 = s^2 p2 NOTE: s^2 = b2_inv
        __m128 st = _mm_mul_ps(s, t);
        st        = _mm_mul_ps(p1_, st);
        p2_       = _mm_sub_ps(_mm_mul_ps(p2_, b2_inv),
                         _mm_xor_ps(_mm_add_ps(st, st), _mm_set_ss(-0.f)));
        p2_       = _mm_xor_ps(p2_, neg);

        p1_ = _mm_xor_ps(_mm_mul_ps(p1_, b2_inv), neg);
    }

    [[nodiscard]] motor inverse() const noexcept
    {
        motor out = *this;
        out.invert();
        return out;
    }

    /// Constrains the motor to traverse the shortest arc
    void constrain() noexcept
    {
        __m128 mask = KLN_SWIZZLE(_mm_and_ps(p1_, _mm_set_ss(-0.f)), 0, 0, 0, 0);
        p1_         = _mm_xor_ps(mask, p1_);
        p2_         = _mm_xor_ps(mask, p2_);
    }

    [[nodiscard]] motor constrained() const noexcept
    {
        motor out = *this;
        out.constrain();
        return out;
    }

    /// Bitwise comparison
    [[nodiscard]] bool KLN_VEC_CALL operator==(motor other) const noexcept
    {
        __m128 p1_eq = _mm_cmpeq_ps(p1_, other.p1_);
        __m128 p2_eq = _mm_cmpeq_ps(p2_, other.p2_);
        __m128 eq    = _mm_and_ps(p1_eq, p2_eq);
        return _mm_movemask_ps(eq) == 0xf;
    }

    [[nodiscard]] bool KLN_VEC_CALL approx_eq(motor other,
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

    /// Convert this motor to a 3x4 column-major matrix representing this
    /// motor's action as a linear transformation. The motor must be normalized
    /// for this conversion to produce well-defined results, but is more
    /// efficient than a 4x4 matrix conversion.
    [[nodiscard]] mat3x4 as_mat3x4() const noexcept
    {
        mat3x4 out;
        mat4x4_12<true, true>(p1_, &p2_, out.cols);
        return out;
    }

    /// Convert this motor to a 4x4 column-major matrix representing this
    /// motor's action as a linear transformation.
    [[nodiscard]] mat4x4 as_mat4x4() const noexcept
    {
        mat4x4 out;
        mat4x4_12<true, false>(p1_, &p2_, out.cols);
        return out;
    }

    /// Conjugates a plane $p$ with this motor and returns the result
    /// $mp\widetilde{m}$.
    [[nodiscard]] plane KLN_VEC_CALL operator()(plane const& p) const noexcept
    {
        plane out;
        detail::sw012<false, true>(&p.p0_, p1_, &p2_, &out.p0_);
        return out;
    }

    /// Conjugates an array of planes with this motor in the input array and
    /// stores the result in the output array. Aliasing is only permitted when
    /// `in == out` (in place motor application).
    ///
    /// !!! tip
    ///
    ///     When applying a motor to a list of tightly packed planes, this
    ///     routine will be *significantly faster* than applying the motor to
    ///     each plane individually.
    void KLN_VEC_CALL operator()(plane* in, plane* out, size_t count) const noexcept
    {
        detail::sw012<true, true>(&in->p0_, p1_, &p2_, &out->p0_, count);
    }

    /// Conjugates a line $\ell$ with this motor and returns the result
    /// $m\ell \widetilde{m}$.
    [[nodiscard]] line KLN_VEC_CALL operator()(line const& l) const noexcept
    {
        line out;
        detail::swMM<false, true, true>(&l.p1_, p1_, &p2_, &out.p1_);
        return out;
    }

    /// Conjugates an array of lines with this motor in the input array and
    /// stores the result in the output array. Aliasing is only permitted when
    /// `in == out` (in place motor application).
    ///
    /// !!! tip
    ///
    ///     When applying a motor to a list of tightly packed lines, this
    ///     routine will be *significantly faster* than applying the motor to
    ///     each line individually.
    void KLN_VEC_CALL operator()(line* in, line* out, size_t count) const noexcept
    {
        detail::swMM<true, true, true>(&in->p1_, p1_, &p2_, &out->p1_, count);
    }

    /// Conjugates a point $p$ with this motor and returns the result
    /// $mp\widetilde{m}$.
    [[nodiscard]] point KLN_VEC_CALL operator()(point const& p) const noexcept
    {
        point out;
        detail::sw312<false, true>(&p.p3_, p1_, &p2_, &out.p3_);
        return out;
    }

    /// Conjugates an array of points with this motor in the input array and
    /// stores the result in the output array. Aliasing is only permitted when
    /// `in == out` (in place motor application).
    ///
    /// !!! tip
    ///
    ///     When applying a motor to a list of tightly packed points, this
    ///     routine will be *significantly faster* than applying the motor to
    ///     each point individually.
    void KLN_VEC_CALL operator()(point* in, point* out, size_t count) const noexcept
    {
        detail::sw312<true, true>(&in->p3_, p1_, &p2_, &out->p3_, count);
    }

    /// Conjugates the origin $O$ with this motor and returns the result
    /// $mO\widetilde{m}$.
    [[nodiscard]] point KLN_VEC_CALL operator()(origin) const noexcept
    {
        point out;
        out.p3_ = detail::swo12(p1_, p2_);
        return out;
    }

    /// Conjugates a direction $d$ with this motor and returns the result
    /// $md\widetilde{m}$.
    ///
    /// The cost of this operation is the same as the application of a rotor due
    /// to the translational invariance of directions (points at infinity).
    [[nodiscard]] direction KLN_VEC_CALL operator()(direction const& d) const noexcept
    {
        direction out;
        detail::sw312<false, false>(&d.p3_, p1_, nullptr, &out.p3_);
        return out;
    }

    /// Conjugates an array of directions with this motor in the input array and
    /// stores the result in the output array. Aliasing is only permitted when
    /// `in == out` (in place motor application).
    ///
    /// The cost of this operation is the same as the application of a rotor due
    /// to the translational invariance of directions (points at infinity).
    ///
    /// !!! tip
    ///
    ///     When applying a motor to a list of tightly packed directions, this
    ///     routine will be *significantly faster* than applying the motor to
    ///     each direction individually.
    void KLN_VEC_CALL operator()(direction* in,
                                 direction* out,
                                 size_t count) const noexcept
    {
        detail::sw312<true, false>(&in->p3_, p1_, nullptr, &out->p3_, count);
    }

    /// Motor addition
    motor& KLN_VEC_CALL operator+=(motor b) noexcept
    {
        p1_ = _mm_add_ps(p1_, b.p1_);
        p2_ = _mm_add_ps(p2_, b.p2_);
        return *this;
    }

    /// Motor subtraction
    motor& KLN_VEC_CALL operator-=(motor b) noexcept
    {
        p1_ = _mm_sub_ps(p1_, b.p1_);
        p2_ = _mm_sub_ps(p2_, b.p2_);
        return *this;
    }

    /// Motor uniform scale
    motor& operator*=(float s) noexcept
    {
        __m128 vs = _mm_set1_ps(s);
        p1_       = _mm_mul_ps(p1_, vs);
        p2_       = _mm_mul_ps(p2_, vs);
        return *this;
    }

    /// Motor uniform scale
    motor& operator*=(int s) noexcept
    {
        __m128 vs = _mm_set1_ps(static_cast<float>(s));
        p1_       = _mm_mul_ps(p1_, vs);
        p2_       = _mm_mul_ps(p2_, vs);
        return *this;
    }

    /// Motor uniform inverse scale
    motor& operator/=(float s) noexcept
    {
        __m128 vs = detail::rcp_nr1(_mm_set1_ps(s));
        p1_       = _mm_mul_ps(p1_, vs);
        p2_       = _mm_mul_ps(p2_, vs);
        return *this;
    }

    /// Motor uniform inverse scale
    motor& operator/=(int s) noexcept
    {
        __m128 vs = detail::rcp_nr1(_mm_set1_ps(static_cast<float>(s)));
        p1_       = _mm_mul_ps(p1_, vs);
        p2_       = _mm_mul_ps(p2_, vs);
        return *this;
    }

    [[nodiscard]] float scalar() const noexcept
    {
        float out;
        _mm_store_ss(&out, p1_);
        return out;
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

    [[nodiscard]] float e0123() const noexcept
    {
        float out;
        _mm_store_ss(&out, p2_);
        return out;
    }

    __m128 p1_;
    __m128 p2_;
};

/// Motor addition
[[nodiscard]] inline motor KLN_VEC_CALL operator+(motor a, motor b) noexcept
{
    motor c;
    c.p1_ = _mm_add_ps(a.p1_, b.p1_);
    c.p2_ = _mm_add_ps(a.p2_, b.p2_);
    return c;
}

/// Motor subtraction
[[nodiscard]] inline motor KLN_VEC_CALL operator-(motor a, motor b) noexcept
{
    motor c;
    c.p1_ = _mm_sub_ps(a.p1_, b.p1_);
    c.p2_ = _mm_sub_ps(a.p2_, b.p2_);
    return c;
}

/// Motor uniform scale
[[nodiscard]] inline motor KLN_VEC_CALL operator*(motor l, float s) noexcept
{
    motor c;
    __m128 vs = _mm_set1_ps(s);
    c.p1_     = _mm_mul_ps(l.p1_, vs);
    c.p2_     = _mm_mul_ps(l.p2_, vs);
    return c;
}

/// Motor uniform scale
[[nodiscard]] inline motor KLN_VEC_CALL operator*(motor l, int s) noexcept
{
    return l * static_cast<float>(s);
}

/// Motor uniform scale
[[nodiscard]] inline motor KLN_VEC_CALL operator*(float s, motor l) noexcept
{
    return l * s;
}

/// Motor uniform scale
[[nodiscard]] inline motor KLN_VEC_CALL operator*(int s, motor l) noexcept
{
    return l * static_cast<float>(s);
}

/// Motor uniform inverse scale
[[nodiscard]] inline motor KLN_VEC_CALL operator/(motor r, float s) noexcept
{
    motor c;
    __m128 vs = detail::rcp_nr1(_mm_set1_ps(static_cast<float>(s)));
    c.p1_     = _mm_mul_ps(r.p1_, vs);
    c.p2_     = _mm_mul_ps(r.p2_, vs);
    return c;
}

/// Motor uniform inverse scale
[[nodiscard]] inline motor KLN_VEC_CALL operator/(motor r, int s) noexcept
{
    return r / static_cast<float>(s);
}

/// Unary minus
[[nodiscard]] inline motor KLN_VEC_CALL operator-(motor m) noexcept
{
    __m128 flip = _mm_set1_ps(-0.f);
    return {_mm_xor_ps(m.p1_, flip), _mm_xor_ps(m.p2_, flip)};
}

/// Reversion operator
[[nodiscard]] inline motor KLN_VEC_CALL operator~(motor m) noexcept
{
    __m128 flip = _mm_set_ps(-0.f, -0.f, -0.f, 0.f);
    return {_mm_xor_ps(m.p1_, flip), _mm_xor_ps(m.p2_, flip)};
}
} // namespace kln
  /// @}
