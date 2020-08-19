/// File: util.hpp
/// Description: Collection of various helper routines and constants

#pragma once

#include <cmath>
#include <cstdint>

#include "detail/sse.hpp"
#include "projection.hpp"

#ifdef _MSC_VER
#    include <intrin.h>
#endif

namespace kln
{
template <typename T>
constexpr T pi_v = 3.141592653589793238462643383279502884L;

constexpr float pi = pi_v<float>;

template <typename T>
constexpr T pi_2_v = 1.570796326794896619231321691639751442L;

constexpr float pi_2 = pi_2_v<float>;

template <typename T>
constexpr T pi_4_v = 0.785398163397448309615660845819875721L;

constexpr float pi_4 = pi_4_v<float>;

/// tau = 2 * pi
template <typename T>
constexpr T tau_v = 6.28318530717958647692528676655900577L;

constexpr float tau = tau_v<float>;

template <typename T>
constexpr T e_v = 2.718281828459045235360287471352662498L;

constexpr float e = e_v<float>;

template <typename T>
constexpr T sqrt2_v = 1.414213562373095048801688724209698079L;

constexpr float sqrt2 = sqrt2_v<float>;

/// sqrt(2) / 2 = 1 / sqrt(2)
template <typename T>
constexpr T sqrt2_2_v = 0.707106781186547524400844362104849039L;

constexpr float sqrt2_2 = sqrt2_2_v<float>;

/// Augment built-in log2 function with platform intrinsic for integral log2
template <typename T>
[[nodiscard]] KLN_INLINE T log2(T in) noexcept
{
    return std::log2(in);
}

/// Specialized log2 for a 4 byte unsigned integer. Note that log2(0) is UB.
template <>
[[nodiscard]] KLN_INLINE uint32_t log2(uint32_t in) noexcept
{
#ifdef _MSC_VER
    return 31 - __lzcnt(in);
#else
    return 31 - __builtin_clz(in);
#endif
}

template <>
[[nodiscard]] KLN_INLINE uint64_t log2(uint64_t in) noexcept
{
#ifdef _MSC_VER
    return 63 - __lzcnt64(in);
#else
    return 63 - __builtin_clzl(in);
#endif
}
} // namespace kln