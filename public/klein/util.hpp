/// File: util.hpp
/// Description: Collection of various helper routines and constants

#pragma once

#include <cmath>
#include <cstdint>

#include "detail/sse.hpp"
#include "projection.hpp"

namespace kln
{
template <typename T>
constexpr T pi_v = (T)3.141592653589793238462643383279502884L;

constexpr float pi = pi_v<float>;

template <typename T>
constexpr T pi_2_v = (T)1.570796326794896619231321691639751442L;

constexpr float pi_2 = pi_2_v<float>;

template <typename T>
constexpr T pi_4_v = (T)0.785398163397448309615660845819875721L;

constexpr float pi_4 = pi_4_v<float>;

/// tau = 2 * pi
template <typename T>
constexpr T tau_v = (T)6.28318530717958647692528676655900577L;

constexpr float tau = tau_v<float>;

template <typename T>
constexpr T e_v = (T)2.718281828459045235360287471352662498L;

constexpr float e = e_v<float>;

template <typename T>
constexpr T sqrt2_v = (T)1.414213562373095048801688724209698079L;

constexpr float sqrt2 = sqrt2_v<float>;

/// sqrt(2) / 2 = 1 / sqrt(2)
template <typename T>
constexpr T sqrt2_2_v = (T)0.707106781186547524400844362104849039L;

constexpr float sqrt2_2 = sqrt2_2_v<float>;
} // namespace kln