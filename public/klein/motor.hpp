#pragma once

#include "detail/entity.hpp"
#include "detail/exp_log.hpp"
#include "detail/matrix.hpp"
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
    void load(float* in)
    {
        parts[0].reg = _mm_loadu_ps(in);
        parts[1].reg = _mm_loadu_ps(in + 4);
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