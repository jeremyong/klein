#pragma once

#include "entity.hpp"
#include "line.hpp"
#include "point.hpp"

namespace kln
{
/// In projective geometry, planes are the fundamental element through which all
/// other entities are constructed. Lines are the meet of two planes, and points
/// are the meet of three planes (equivalently, a line and a plane).
///
/// The plane multivector in PGA looks like
/// $d\mathbf{e}_0 + a\mathbf{e}_1 + b\mathbf{e}_2 + c\mathbf{e}_3$. Points
/// that reside on the plane satisfy the familiar equation
/// $d + ax + by + cz = 0$.
struct plane final : public entity<0b1>
{
    /// The default constructor leaves memory uninitialized
    plane() = default;

    /// The constructor performs the rearrangement so the plane can be specified
    /// in the familiar form: ax + by + cz + d
    plane(float a, float b, float c, float d) noexcept
    {
        parts[0].reg = _mm_set_ps(c, b, a, d);
    }

    /// Data should point to four floats with memory layout `(d, a, b, c)` where
    /// `d` occupies the lowest address in memory.
    explicit plane(float* data) noexcept
    {
        parts[0].reg = _mm_loadu_ps(data);
    }

    /// Line to plane cast.
    ///
    /// !!! danger
    ///
    ///     When constructing a plane with points using the regressive product,
    ///     data leaks into the 3rd partition so this explicit constructor is
    ///     made available. For example, if you had three `point` entities `p1`,
    ///     `p2`, and `p3`, the plane containing all three points could be
    ///     constructed via `plane p{p1 & p2 & p3}`.
    ///
    ///     If the third partition contains data, this cast will *truncate* that
    ///     data so this constructor should only be used when the caller *knows*
    ///     that the entity passed as the argument is a plane.
    explicit plane(entity<0b1001> const& other) noexcept
    {
        parts[0].reg = other.p0();
    }

    /// Unaligned load of data. The `data` argument should point to 4 floats
    /// corresponding to the
    /// `(d, a, b, c)` components of the plane multivector where `d` occupies
    /// the lowest address in memory.
    ///
    /// !!! tip
    ///
    ///     This is a faster mechanism for setting data compared to setting
    ///     components one at a time.
    void load(float* data) noexcept
    {
        parts[0].reg = _mm_loadu_ps(data);
    }

    /// Normalize this plane $p$ such that $p \cdot p = 1$.
    ///
    /// In order to compute the cosine of the angle between planes via the
    /// inner product operator `|`, the planes must be normalized. Producing a
    /// normalized rotor between two planes with the geometric product `*` also
    /// requires that the planes are normalized.
    void normalize() noexcept
    {
        __m128 inv_norm
            = _mm_rcp_ps(_mm_sqrt_ps(_mm_dp_ps(p0(), p0(), 0b11101111)));
        inv_norm = _mm_blend_ps(inv_norm, _mm_set_ss(1.f), 1);
        p0()     = _mm_mul_ps(inv_norm, p0());
    }

    /// Reflect another plane $p_2$ through this plane $p_1$. The operation
    /// performed via this call operator is an optimized routine equivalent to
    /// the expression $p_1 p_2 p_1$.
    [[nodiscard]] plane KLN_VEC_CALL operator()(plane const& p) const noexcept
    {
        plane out;
        sw00(p0(), p.p0(), out.p0());
        return out;
    }

    /// Reflect line $\ell$ through this plane $p$. The operation
    /// performed via this call operator is an optimized routine equivalent to
    /// the expression $p \ell p$.
    [[nodiscard]] line KLN_VEC_CALL operator()(line const& l) const noexcept
    {
        line out;
        sw10(p0(), l.p1(), out.p1(), out.p2());
        __m128 p2_tmp;
        sw20(p0(), l.p2(), p2_tmp);
        out.p2() = _mm_add_ps(out.p2(), p2_tmp);
        return out;
    }

    /// Reflect the point $P$ through this plane $p$. The operation
    /// performed via this call operator is an optimized routine equivalent to
    /// the expression $p P p$.
    [[nodiscard]] point KLN_VEC_CALL operator()(point const& p) const noexcept
    {
        point out;
        sw30(p0(), p.p3(), out.p3());
        return out;
    }

    [[nodiscard]] float x() const noexcept
    {
        return parts[0].data[1];
    }

    [[nodiscard]] float& x() noexcept
    {
        return parts[0].data[1];
    }

    [[nodiscard]] float y() const noexcept
    {
        return parts[0].data[2];
    }

    [[nodiscard]] float& y() noexcept
    {
        return parts[0].data[2];
    }

    [[nodiscard]] float z() const noexcept
    {
        return parts[0].data[3];
    }

    [[nodiscard]] float& z() noexcept
    {
        return parts[0].data[3];
    }

    [[nodiscard]] float d() const noexcept
    {
        return parts[0].data[0];
    }

    [[nodiscard]] float& d() noexcept
    {
        return parts[0].data[0];
    }
};
} // namespace kln