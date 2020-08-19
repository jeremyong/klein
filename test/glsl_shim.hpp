#pragma once

#include <cstddef>
#include <cstdint>

constexpr uint8_t swizzle_index(char const& c)
{
    switch (c)
    {
    case 'x':
        return 0;
    case 'y':
        return 1;
    case 'z':
        return 2;
    case 'w':
        return 3;
    }
    return 0;
}

#define SWIZZLE(a, b, c, d)       \
    swizzle<swizzle_index(#a[0]), \
            swizzle_index(#b[0]), \
            swizzle_index(#c[0]), \
            swizzle_index(#d[0])> \
        a##b##c##d

#define SWIZZLE_3(a, b, c) \
    SWIZZLE(a, b, c, x);   \
    SWIZZLE(a, b, c, y);   \
    SWIZZLE(a, b, c, z);   \
    SWIZZLE(a, b, c, w);

#define SWIZZLE_2(a, b) \
    SWIZZLE_3(a, b, x); \
    SWIZZLE_3(a, b, y); \
    SWIZZLE_3(a, b, z); \
    SWIZZLE_3(a, b, w);

#define SWIZZLE_1(a) \
    SWIZZLE_2(a, x); \
    SWIZZLE_2(a, y); \
    SWIZZLE_2(a, z); \
    SWIZZLE_2(a, w);

#define SWIZZLES  \
    SWIZZLE_1(x); \
    SWIZZLE_1(y); \
    SWIZZLE_1(z); \
    SWIZZLE_1(w)

// Redefine various glsl types and keywords

#define in
#define out

struct vec4
{
    template <uint8_t a, uint8_t b, uint8_t c, uint8_t d>
    struct swizzle
    {
        constexpr operator vec4() const noexcept
        {
            float const* data = reinterpret_cast<float const*>(this);
            return {data[a], data[b], data[c], data[d]};
        }

        template <uint8_t e, uint8_t f, uint8_t g, uint8_t h>
        vec4 operator*(swizzle<e, f, g, h> const& other) const noexcept
        {
            return static_cast<vec4>(*this) * static_cast<vec4>(other);
        }

        vec4 operator*(vec4 const& other) const noexcept
        {
            return static_cast<vec4>(*this) * other;
        }
    };

    template <uint8_t i>
    struct component
    {
        operator float() const noexcept
        {
            return reinterpret_cast<float const*>(this)[i];
        }

        vec4 operator*(vec4 const& other) const noexcept
        {
            return other * static_cast<float>(*this);
        }

        float operator-() const noexcept
        {
            return -reinterpret_cast<float const*>(this)[i];
        }

        component& operator=(float other) noexcept
        {
            reinterpret_cast<float*>(this)[i] = other;
            return *this;
        }
    };

    union
    {
        float data[4];
        component<0> x;
        component<1> y;
        component<2> z;
        component<3> w;
        SWIZZLES;
    };

    vec4() = default;

    vec4(float a, float b, float c, float d) noexcept
        : data{a, b, c, d}
    {}

    vec4 operator*(float other) const noexcept
    {
        vec4 result;
        for (size_t i = 0; i != 4; ++i)
        {
            result.data[i] = data[i] * other;
        }
        return result;
    }

    vec4& operator*=(float other) noexcept
    {
        for (size_t i = 0; i != 4; ++i)
        {
            data[i] = data[i] * other;
        }
        return *this;
    }

    template <uint8_t j>
    vec4 operator*(component<j> const& other) const noexcept
    {
        vec4 result;
        for (size_t i = 0; i != 4; ++i)
        {
            result.data[i] = data[i] * static_cast<float>(other);
        }
        return result;
    }

    template <uint8_t j>
    vec4& operator*=(component<j> const& other) noexcept
    {
        for (size_t i = 0; i != 4; ++i)
        {
            data[i] = data[i] * static_cast<float>(other);
        }
        return *this;
    }

    vec4 operator+(const vec4& other) const noexcept
    {
        vec4 result;
        for (size_t i = 0; i != 4; ++i)
        {
            result.data[i] = data[i] + other.data[i];
        }
        return result;
    }

    vec4 operator*(const vec4& other) const noexcept
    {
        vec4 result;
        for (size_t i = 0; i != 4; ++i)
        {
            result.data[i] = data[i] * other.data[i];
        }
        return result;
    }

    vec4 operator-(const vec4& other) const noexcept
    {
        vec4 result;
        for (size_t i = 0; i != 4; ++i)
        {
            result.data[i] = data[i] - other.data[i];
        }
        return result;
    }

    vec4& operator+=(const vec4& other) noexcept
    {
        for (size_t i = 0; i != 4; ++i)
        {
            data[i] += other.data[i];
        }
        return *this;
    }

    vec4& operator*=(const vec4& other) noexcept
    {
        for (size_t i = 0; i != 4; ++i)
        {
            data[i] *= other.data[i];
        }
        return *this;
    }

    vec4& operator-=(const vec4& other) noexcept
    {
        for (size_t i = 0; i != 4; ++i)
        {
            data[i] -= other.data[i];
        }
        return *this;
    }
};

float dot(vec4 const& a, vec4 const& b)
{
    float result = 0;
    for (size_t i = 0; i != 4; ++i)
    {
        result += a.data[i] * b.data[i];
    }
    return result;
}