#pragma once

#include "detail/exp_log.hpp"
#include "detail/matrix.hpp"
#include "entity.hpp"
#include "mat4x4.hpp"
#include "plane.hpp"
#include "point.hpp"

namespace kln
{
struct motor final : public entity<0b110>
{
    motor() = default;

    // Direct initialization from components. A more common way of creating a
    // motor is to take a product between a rotor and a translator.
    motor(float a, float b, float c, float d, float e, float f, float g, float h) noexcept
    {
        // TODO: optimize initialization
        parts[0].reg = _mm_set_ps(d, c, b, a);
        parts[1].reg = _mm_set_ps(g, f, e, h);
    }

    motor(entity<0b110> const& e) noexcept
        : entity{e}
    {}

    // Aligned and unaligned loads incur the same amount of latency and have
    // identical throughput on most modern processors
    void load(float* in) noexcept
    {
        parts[0].reg = _mm_loadu_ps(in);
        parts[1].reg = _mm_loadu_ps(in + 4);
    }

    // When normalized, the motor times its reverse should equal 1
    void normalize() noexcept
    {
        // m = b + c where b is p1 and c is p2
        //
        // m * ~m = |b|^2 + 2(b0 c0 - b1 c3 - b2 c2 - b3 c1)e0123
        //
        // The square root is given as:
        // |b| + (b0 c0 - b1 c3 - b2 c2 - b3 c1)/|b| e0123
        //
        // The inverse of this is given by:
        // 1/|b| + (-b0 c0 + b1 c3 + b2 c2 + b3 c1)/|b|^2 e0123 = s + t e0123
        //
        // Multiplying our original motor by this inverse will give us a
        // normalized motor.
        __m128 b2     = _mm_dp_ps(p1(), p1(), 0xff);
        __m128 b_norm = _mm_sqrt_ps(b2);
        __m128 s      = _mm_rcp_ps(b_norm);
        __m128 bc     = _mm_dp_ps(_mm_mul_ss(p1(), _mm_set_ss(-1.f)),
                              KLN_SWIZZLE(p2(), 1, 2, 3, 0),
                              0xff);
        __m128 t      = _mm_mul_ps(_mm_mul_ps(bc, _mm_rcp_ps(b2)), s);

        // (s + t e0123) * motor =
        //
        // s b0 +
        // s b1 e12 +
        // s b2 e31 +
        // s b3 e23 +
        // (s c0 + t b0) e0123 +
        // (s c1 - t b3) e01 +
        // (s c2 - t b2) e02 +
        // (s c3 - t b1) e03

        __m128 tmp = _mm_mul_ps(p2(), s);
        p2()       = _mm_sub_ps(tmp,
                          _mm_mul_ss(_mm_mul_ps(KLN_SWIZZLE(p1(), 1, 2, 3, 0), t),
                                     _mm_set_ss(-1.f)));
        p1()       = _mm_mul_ps(p1(), s);
    }

    [[nodiscard]] mat4x4 as_matrix() const noexcept
    {
        mat4x4 out;
        mat4x4_12<true>(parts[0].reg, &parts[1].reg, out.cols);
        return out;
    }

    // Takes the principal branch of the logarithm of the motor, returning a
    // bivector.
    [[nodiscard]] entity<0b110> log() const noexcept
    {
        entity<0b110> out;
        detail::log(p1(), p2(), out.p1(), out.p2());
        return out;
    }

    plane KLN_VEC_CALL operator()(plane const& p) const noexcept
    {
        plane out;
        sw012<false, true>(&p.p0(), parts[0].reg, &parts[1].reg, &out.p0());
        return out;
    }

    point KLN_VEC_CALL operator()(point const& p) const noexcept
    {
        point out;
        sw312<false, true>(&p.p3(), parts[0].reg, &parts[1].reg, &out.p3());
        return out;
    }

    point KLN_VEC_CALL operator()(origin) const noexcept
    {
        point out;
        out.p3() = swo12(parts[0].reg, parts[1].reg);
        return out;
    }
};
} // namespace kln