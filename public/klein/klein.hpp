// File: klein.hpp
// Include this header to gain access to all the primary library facilities:
// 1. Representations of points, lines, planes, directions, rotors, translators,
//    and motors as multivectors
// 2. SSE-optimized operations between all the above

#pragma once

#include "detail/klein_entity.hpp"

namespace kln
{
// In projective geometry, planes are the fundamental element through which all
// other entities are constructed. Lines are the meet of two planes, and points
// are the meet of three planes (equivalently, a line and a plane).
//
// d*e_0 + a*e_1 + b*e_2 + c*e_3
struct plane final : public entity<0b1>
{
    plane() = default;

    // The constructor performs the rearrangement so the plane can be specified
    // in the familiar form: ax + by + cz + d
    plane(float a, float b, float c, float d) noexcept
    {
        parts[0].reg = _mm_set_ps(d, a, b, c);
    }

    float x() const noexcept
    {
        return parts[0].data[2];
    }

    float y() const noexcept
    {
        return parts[0].data[1];
    }

    float z() const noexcept
    {
        return parts[0].data[0];
    }

    float d() const noexcept
    {
        return parts[0].data[3];
    }
};

// Euclidean line: d*e_12 + e*e_31 + f*e_23
struct line final : public entity<0b10>
{
    line()
    {
        // Unlike other entities, the 0th component of this partition must be
        // exactly 0
        parts[0].data[0] = 0.0f;
    }

    line(float d, float e, float f) noexcept
    {
        parts[0].reg = _mm_set_ps(f, e, d, 0.f);
    }
};

// Ideal line: a*e_01 + b*e_02 + c*e_03
struct ideal_line final : public entity<0b100>
{
    ideal_line()
    {
        parts[0].data[0] = 0.0f;
    }

    ideal_line(float a, float b, float c) noexcept
    {
        parts[0].reg = _mm_set_ps(c, b, a, 0.f);
    }
};

// A general bivector is the sum of a Euclidean line and an ideal line
// p1: (1, e12, e31, e23)
// p2: (e0123, e01, e02, e03)
struct bivector final : public entity<0b110>
{
    bivector()
    {
        parts[0].data[0] = 0.0f;
        parts[1].data[0] = 0.0f;
    }

    bivector(float a, float b, float c, float d, float e, float f) noexcept
    {
        parts[0].reg = _mm_set_ps(f, e, d, 0.f);
        // Partition with degenerate components ordered after the first
        parts[1].reg = _mm_set_ps(c, b, a, 0.f);
    }

    bivector(entity<0b110> const& e)
        : entity{e}
    {}

    float operator[](size_t i) const noexcept
    {
        return reinterpret_cast<float const*>(this)[i];
    }
};

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

// Ideal points will have a 0 for the homogeneous coordinate
// x*e_032 + y*e_013 + z*e_021
struct direction final : public entity<0b1000>
{
    direction() = default;
    direction(float x, float y, float z) noexcept
    {
        parts[0].reg = _mm_set_ps(x, y, z, 0.f);
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

    float y() const noexcept
    {
        return parts[0].data[2];
    }

    float z() const noexcept
    {
        return parts[0].data[1];
    }
};

struct motor final : public entity<0b110>
{
    motor() = default;
    motor(float a, float b, float c, float d, float e, float f, float g) noexcept
    {
        // TODO: optimize initialization
        parts[0].reg = _mm_set_ps(d, c, b, a);
        parts[1].reg = _mm_set_ps(g, f, e, 0.f);
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
};
} // namespace kln

#undef KLN_SWIZZLE
#undef KLN_VEC_CALL