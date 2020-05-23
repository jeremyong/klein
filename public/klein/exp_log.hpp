#pragma once

#include "line.hpp"
#include "motor.hpp"
#include "rotor.hpp"
#include "translator.hpp"

#include "detail/exp_log.hpp"

namespace kln
{
/// \defgroup exp_log Exponential and Logarithm
/// @{
///
/// The group of rotations, translations, and screws (combined rotatation and
/// translation) is _nonlinear_. This means, given say, a rotor $\mathbf{r}$,
/// the rotor
/// $\frac{\mathbf{r}}{2}$ _does not_ correspond to half the rotation.
/// Similarly, for a motor $\mathbf{m}$, the motor $n \mathbf{m}$ is not $n$
/// applications of the motor $\mathbf{m}$. One way we could achieve this is
/// through exponentiation; for example, the motor $\mathbf{m}^3$ will perform
/// the screw action of $\mathbf{m}$ three times. However, repeated
/// multiplication in this fashion lacks both efficiency and numerical
/// stability.
///
/// The solution is to take the logarithm of the action which maps the action to
/// a linear space. Using `log(A)` where `A` is one of `rotor`,
/// `translator`, or `motor`, we can apply linear scaling to `log(A)`,
/// and then re-exponentiate the result. Using this technique, `exp(n * log(A))`
/// is equivalent to $\mathbf{A}^n$.

/// Takes the principal branch of the logarithm of the motor, returning a
/// bivector. Exponentiation of that bivector without any changes produces
/// this motor again. Scaling that bivector by $\frac{1}{n}$,
/// re-exponentiating, and taking the result to the $n$th power will also
/// produce this motor again. The logarithm presumes that the motor is
/// normalized.
[[nodiscard]] inline line KLN_VEC_CALL log(motor m) noexcept
{
    line out;
    detail::log(m.p1_, m.p2_, out.p1_, out.p2_);
    return out;
}

/// Exponentiate a line to produce a motor that posesses this line
/// as its axis. This routine will be used most often when this line is
/// produced as the logarithm of an existing rotor, then scaled to subdivide
/// or accelerate the motor's action. The line need not be a _simple bivector_
/// for the operation to be well-defined.
[[nodiscard]] inline motor KLN_VEC_CALL exp(line l) noexcept
{
    motor out;
    detail::exp(l.p1_, l.p2_, out.p1_, out.p2_);
    return out;
}

/// Compute the logarithm of the translator, producing an ideal line axis.
/// In practice, the logarithm of a translator is simply the ideal partition
/// (without the scalar $1$).
[[nodiscard]] inline ideal_line KLN_VEC_CALL log(translator t) noexcept
{
    ideal_line out;
    out.p2_ = t.p2_;
    return out;
}

/// Exponentiate an ideal line to produce a translation.
///
/// The exponential of an ideal line
/// $a \mathbf{e}_{01} + b\mathbf{e}_{02} + c\mathbf{e}_{03}$ is given as:
///
/// $$\exp{\left[a\ee_{01} + b\ee_{02} + c\ee_{03}\right]} = 1 +\
/// a\ee_{01} + b\ee_{02} + c\ee_{03}$$
[[nodiscard]] inline translator KLN_VEC_CALL exp(ideal_line il) noexcept
{
    translator out;
    out.p2_ = il.p2_;
    return out;
}

/// Returns the principal branch of this rotor's logarithm. Invoking
/// `exp` on the returned `kln::branch` maps back to this rotor.
///
/// Given a rotor $\cos\alpha + \sin\alpha\left[a\ee_{23} + b\ee_{31} +\
/// c\ee_{23}\right]$, the log is computed as simply
/// $\alpha\left[a\ee_{23} + b\ee_{31} + c\ee_{23}\right]$.
/// This map is only well-defined if the
/// rotor is normalized such that $a^2 + b^2 + c^2 = 1$.
[[nodiscard]] inline branch KLN_VEC_CALL log(rotor r) noexcept
{
    float cos_ang;
    _mm_store_ss(&cos_ang, r.p1_);
    float ang     = std::acos(cos_ang);
    float sin_ang = std::sin(ang);

    branch out;
    out.p1_ = _mm_mul_ps(r.p1_, detail::rcp_nr1(_mm_set1_ps(sin_ang)));
    out.p1_ = _mm_mul_ps(out.p1_, _mm_set1_ps(ang));
#ifdef KLEIN_SSE_4_1
    out.p1_ = _mm_blend_ps(out.p1_, _mm_setzero_ps(), 1);
#else
    out.p1_ = _mm_and_ps(out.p1_, _mm_castsi128_ps(_mm_set_epi32(-1, -1, -1, 0)));
#endif
    return out;
}

/// Exponentiate a branch to produce a rotor.
[[nodiscard]] inline rotor KLN_VEC_CALL exp(branch b) noexcept
{
    // Compute the rotor angle
    float ang;
    _mm_store_ss(&ang, detail::sqrt_nr1(detail::hi_dp(b.p1_, b.p1_)));
    float cos_ang = std::cos(ang);
    float sin_ang = std::sin(ang) / ang;

    rotor out;
    out.p1_ = _mm_mul_ps(_mm_set1_ps(sin_ang), b.p1_);
    out.p1_ = _mm_add_ps(out.p1_, _mm_set_ps(0.f, 0.f, 0.f, cos_ang));
    return out;
}

/// Compute the square root of the provided rotor $r$.
[[nodiscard]] inline rotor KLN_VEC_CALL sqrt(rotor r) noexcept
{
    r.p1_ = _mm_add_ss(r.p1_, _mm_set_ss(1.f));
    r.normalize();
    return r;
}

[[nodiscard]] inline rotor KLN_VEC_CALL sqrt(branch b) noexcept
{
    rotor r;
    r.p1_ = _mm_add_ss(b.p1_, _mm_set_ss(1.f));
    r.normalize();
    return r;
}

/// Compute the square root of the provided translator $t$.
[[nodiscard]] inline translator KLN_VEC_CALL sqrt(translator t) noexcept
{
    t *= 0.5f;
    return t;
}

/// Compute the square root of the provided motor $m$.
[[nodiscard]] inline motor KLN_VEC_CALL sqrt(motor m) noexcept
{
    m.p1_ = _mm_add_ss(m.p1_, _mm_set_ss(1.f));
    m.normalize();
    return m;
}
/// @}
} // namespace kln
