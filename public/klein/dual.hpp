#pragma once

#include "detail/sse.hpp"

namespace kln
{
/// \defgroup dualn Dual Numbers
/// A dual number is a multivector of the form $p + q\mathbf{e}_{0123}$.

/// \addtogroup dualn
/// @{
class dual
{
public:
    float scalar() const noexcept
    {
        return p;
    }

    float e0123() const noexcept
    {
        return q;
    }

    dual& operator+=(dual b) noexcept
    {
        p += b.p;
        q += b.q;
        return *this;
    }

    dual& operator-=(dual b) noexcept
    {
        p -= b.p;
        q -= b.q;
        return *this;
    }

    dual& operator*=(float s) noexcept
    {
        p *= s;
        q *= s;
        return *this;
    }

    dual& operator/=(float s) noexcept
    {
        p /= s;
        q /= s;
        return *this;
    }

    float p;
    float q;
};

[[nodiscard]] inline dual KLN_VEC_CALL operator+(dual a, dual b) noexcept
{
    return {a.p + b.p, a.q + b.q};
}

[[nodiscard]] inline dual KLN_VEC_CALL operator-(dual a, dual b) noexcept
{
    return {a.p - b.p, a.q - b.q};
}

[[nodiscard]] inline dual KLN_VEC_CALL operator*(dual a, float s) noexcept
{
    return {a.p * s, a.q * s};
}

[[nodiscard]] inline dual KLN_VEC_CALL operator*(float s, dual a) noexcept
{
    return {a.p * s, a.q * s};
}

[[nodiscard]] inline dual KLN_VEC_CALL operator/(dual a, float s) noexcept
{
    return {a.p / s, a.q / s};
}

/// @}
} // namespace kln