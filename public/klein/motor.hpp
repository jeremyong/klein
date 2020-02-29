#pragma once

#include "detail/exp_log.hpp"
#include "detail/matrix.hpp"
#include "entity.hpp"
#include "mat3x4.hpp"
#include "mat4x4.hpp"
#include "plane.hpp"
#include "point.hpp"

namespace kln
{
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
///         rotor r{M_PI * 0.5f, 0.f, 0.f, 1.f};
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
struct motor final : public entity<0b110>
{
    motor() = default;

    /// Direct initialization from components. A more common way of creating a
    /// motor is to take a product between a rotor and a translator.
    /// The arguments coorespond to the multivector
    /// $a + b\mathbf{e}_{23} + c\mathbf{e}_{31} + d\mathbf{e}_{12} +\
    /// e\mathbf{e}_{01} + f\mathbf{e}_{02} + g\mathbf{e}_{03} +\
    /// h\mathbf{e}_{0123}$.
    motor(float a, float b, float c, float d, float e, float f, float g, float h) noexcept
    {
        parts[0].reg = _mm_set_ps(d, c, b, a);
        parts[1].reg = _mm_set_ps(g, f, e, h);
    }

    motor(entity<0b110> const& e) noexcept
        : entity{e}
    {}

    /// Load motor data using two unaligned loads. This routine does *not*
    /// assume the data passed in this way is normalized.
    void load(float* in) noexcept
    {
        // Aligned and unaligned loads incur the same amount of latency and have
        // identical throughput on most modern processors
        parts[0].reg = _mm_loadu_ps(in);
        parts[1].reg = _mm_loadu_ps(in + 4);
    }

    /// Normalizes this motor $m$ such that $m\widetilde{m} = 1$.
    ///
    /// !!! tip
    ///
    ///     Normalization here is done using the `rsqrtps`
    ///     instruction with a maximum relative error of $1.5\times 2^{-12}$.
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
        // 1/|b| + (-b0 c0 + b1 c1 + b2 c2 + b3 c3)/|b|^2 e0123 = s + t e0123
        //
        // Multiplying our original motor by this inverse will give us a
        // normalized motor.
        __m128 b2 = _mm_dp_ps(p1(), p1(), 0xff);
        __m128 s  = _mm_rsqrt_ps(b2);
        __m128 bc = _mm_dp_ps(_mm_mul_ss(p1(), _mm_set_ss(-1.f)), p2(), 0xff);
        __m128 t  = _mm_mul_ps(_mm_mul_ps(bc, _mm_rcp_ps(b2)), s);

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

        __m128 tmp = _mm_mul_ps(p2(), s);
        p2() = _mm_sub_ps(tmp, _mm_mul_ss(_mm_mul_ps(p1(), t), _mm_set_ss(-1.f)));
        p1() = _mm_mul_ps(p1(), s);
    }

    /// Convert this motor to a 3x4 column-major matrix representing this
    /// motor's action as a linear transformation. The motor must be normalized
    /// for this conversion to produce well-defined results, but is more
    /// efficient than a 4x4 matrix conversion.
    [[nodiscard]] mat3x4 as_mat3x4() const noexcept
    {
        mat3x4 out;
        mat4x4_12<true, true>(parts[0].reg, &parts[1].reg, out.cols);
        return out;
    }

    /// Convert this motor to a 4x4 column-major matrix representing this
    /// motor's action as a linear transformation.
    [[nodiscard]] mat4x4 as_mat4x4() const noexcept
    {
        mat4x4 out;
        mat4x4_12<true>(parts[0].reg, &parts[1].reg, out.cols);
        return out;
    }

    /// Takes the principal branch of the logarithm of the motor, returning a
    /// bivector. Exponentiation of that bivector without any changes produces
    /// this motor again. Scaling that bivector by $\frac{1}{n}$,
    /// re-exponentiating, and taking the result to the $n$th power will also
    /// produce this motor again.
    [[nodiscard]] entity<0b110> log() const noexcept
    {
        entity<0b110> out;
        detail::log(p1(), p2(), out.p1(), out.p2());
        return out;
    }

    /// Conjugates a plane $p$ with this motor and returns the result
    /// $mp\widetilde{m}$.
    [[nodiscard]] plane KLN_VEC_CALL operator()(plane const& p) const noexcept
    {
        plane out;
        sw012<false, true>(&p.p0(), parts[0].reg, &parts[1].reg, &out.p0());
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
    void KLN_VEC_CALL operator()(plane* in, plane* out, size_t count) const
        noexcept
    {
        sw012<true, true>(
            &in->p0(), parts[0].reg, &parts[1].reg, &out->p0(), count);
    }

    /// Conjugates a line $\ell$ with this motor and returns the result
    /// $m\ell \widetilde{m}$.
    [[nodiscard]] line KLN_VEC_CALL operator()(line const& l) const noexcept
    {
        line out;
        swMM<false, true>(&l.p1(), p1(), &p2(), &out.p1());
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
        swMM<true, true>(
            &in->p1(), parts[0].reg, &parts[1].reg, &out->p1(), count);
    }

    /// Conjugates a point $p$ with this motor and returns the result
    /// $mp\widetilde{m}$.
    [[nodiscard]] point KLN_VEC_CALL operator()(point const& p) const noexcept
    {
        point out;
        sw312<false, true>(&p.p3(), parts[0].reg, &parts[1].reg, &out.p3());
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
    void KLN_VEC_CALL operator()(point* in, point* out, size_t count) const
        noexcept
    {
        sw312<true, true>(
            &in->p3(), parts[0].reg, &parts[1].reg, &out->p3(), count);
    }

    /// Conjugates the origin $O$ with this motor and returns the result
    /// $mO\widetilde{m}$.
    [[nodiscard]] point KLN_VEC_CALL operator()(origin) const noexcept
    {
        point out;
        out.p3() = swo12(parts[0].reg, parts[1].reg);
        return out;
    }

    /// Conjugates a direction $d$ with this motor and returns the result
    /// $md\widetilde{m}$.
    ///
    /// The cost of this operation is the same as the application of a rotor due
    /// to the translational invariance of directions (points at infinity).
    direction KLN_VEC_CALL operator()(direction const& d) const noexcept
    {
        direction out;
        sw312<false, false>(&d.p3(), parts[0].reg, nullptr, &out.p3());
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
    void KLN_VEC_CALL operator()(direction* in, direction* out, size_t count) const
        noexcept
    {
        sw312<true, false>(&in->p3(), parts[0].reg, nullptr, &out->p3(), count);
    }
};
} // namespace kln