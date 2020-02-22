#pragma once

#include "detail/exterior_product.hpp"
#include "detail/geometric_product.hpp"
#include "detail/inner_product.hpp"
#include "detail/sandwich.hpp"
#include <cstdint>
#include <type_traits>

namespace kln
{
/// The full $\mathbf{P}(\mathbb{R}^*_{3, 0, 1})$ graded-algebra requires 16
/// floats to represent a general multivector. However, it is very common to
/// perform computation on either the odd or even subalgebras. For example,
/// motor composition lives entirely within the even subalgebra, while entities
/// such as planes, and points exist in the odd subalgebra.
///
/// The `entity` struct is the base class for all geometric entities in Klein
/// and encapsulates their multivector representations. The `plane`, `line`, and
/// `point` class are some examples of geometric entities. Geometric *actions*
/// such as the `rotor`, `translator`, and `motor` also have multivector
/// representations and are implemented as `entity` subclasses as well. Note
/// that while inheritance is used, there _is no virtual dispatch_ occurring at
/// any point. Inheritance is used here strictly because all the entities above
/// have the same underlying representation, and all operations implemented here
/// are valid for each one.
///
/// To compute PGA elements using SSE, we partition the basis into four
/// partitions corresponding to the following scheme:
///
/// ```
///     LSB --> MSB
/// p0: (e_0, e_1, e_2, e_3)
/// p1: (1, e_23, e_31, e_12)
/// p2: (e_0123, e_01, e_02, e_03)
/// p3: (e_123, e_032, e_013, e_021)
/// ```
///
/// The scalar and pseudoscalar are packed in partitions $p_1$ and $p_2$ along
/// with the 6 bivector elements. The scheme groups, for the most part, elements
/// of similar grade and the presence of the degenerate generator. When
/// non-uniformity exists within a partition (mixed degenerate and
/// non-degenerate components, or mixed grade), the "exception" is housed in the
/// first component so that the same swizzle masks can be used.
///
/// All partitions contain 4 packed single-precision floating point values.
/// An entity's memory layout is specified based on which partitions are
/// present. The least significant bit in the mask corresponds to the presence
/// of P0, and the 4th least significant bit corresponds to the presence of P3.
///
/// !!! danger
///
///     For performance, the single-element accessors such as `e0`
///     should be used sparingly or coalesced together in code so that the
///     entity data remains in packed SSE registers for as long as possible
///     without any dependent load.
///
/// @tparam PMask The `PMask` template parameter is a bitmask corresponding to
/// the partitions present in the entity. The size of the entity will be
/// `popcnt(PMask) * 4 * sizeof(float)` since each partition contains 4 floats.
template <uint8_t PMask /* Partition Mask */>
struct entity
{
    template <uint8_t P>
    friend struct entity;

    constexpr static uint8_t partition_count
        = (PMask & 1) + ((PMask >> 1) & 0b1) + ((PMask >> 2) & 1)
          + ((PMask >> 3) & 1);
    constexpr static uint8_t partition_offsets[4]
        = {0,
           (PMask & 1),
           (PMask & 1) + ((PMask >> 1) & 1),
           (PMask & 1) + ((PMask >> 1) & 1) + ((PMask >> 2) & 1)};
    constexpr static uint8_t partition_mask = PMask;

    /// Default constructor. The contents of the entity are left uninitialized.
    entity()
    {}

    /// Copy constructor.
    entity(entity const& other)
    {
        for (uint8_t i = 0; i != partition_count; ++i)
        {
            parts[i].reg = other.parts[i].reg;
        }
    }

    /// Addition.
    ///
    /// Returns the sum of this entity and another. The
    /// partition mask of the result will be the union of the two addends.
    template <uint8_t P>
    constexpr auto operator+(entity<P> const& other) const noexcept
    {
        return add_sub<true>(other);
    }

    template <uint8_t P>
    constexpr entity& operator+=(entity<P> const& other) noexcept
    {
        add_sub<true>(other);
        return *this;
    }

    /// Subtraction.
    ///
    /// Returns the difference of this entity and another.
    /// The partition mask of the result will be the union of the two operands.
    template <uint8_t P>
    constexpr auto operator-(entity<P> const& other) const noexcept
    {
        return add_sub<false>(other);
    }

    template <uint8_t P>
    constexpr entity& operator-=(entity<P> const& other) noexcept
    {
        add_sub<false>(other);
        return *this;
    }

    /// Scale the multivector by a scalar constant in-place.
    entity& operator*=(float scalar) noexcept
    {
        __m128 s = _mm_set1_ps(scalar);

        if constexpr (PMask & 0b1)
        {
            p0() = _mm_mul_ps(p0(), s);
        }
        if constexpr (PMask & 0b10)
        {
            p1() = _mm_mul_ps(p1(), s);
        }
        if constexpr (PMask & 0b100)
        {
            p2() = _mm_mul_ps(p2(), s);
        }
        if constexpr (PMask & 0b1000)
        {
            p3() = _mm_mul_ps(p3(), s);
        }

        return *this;
    }

    /// Scale the multivector by a scalar constant and return the result.
    [[nodiscard]] entity operator*(float scalar) const noexcept
    {
        entity out;
        __m128 s = _mm_set1_ps(scalar);

        if constexpr ((PMask & 0b1) > 0)
        {
            out.p0() = _mm_mul_ps(p0(), s);
        }
        if constexpr ((PMask & 0b10) > 0)
        {
            out.p1() = _mm_mul_ps(p1(), s);
        }
        if constexpr ((PMask & 0b100) > 0)
        {
            out.p2() = _mm_mul_ps(p2(), s);
        }
        if constexpr ((PMask & 0b1000) > 0)
        {
            out.p3() = _mm_mul_ps(p3(), s);
        }

        return out;
    }

    /// Divide the multivector by a scalar constant in-place.
    entity& operator/=(float s) noexcept
    {
        return operator*=(1.f / s);
    }

    /// Divide the multivector by a scalar constant and return the result.
    [[nodiscard]] entity operator/(float s) const noexcept
    {
        return operator*(1.f / s);
    }

    /// Reversion operator
    ///
    /// Given a basis element $e_S$, the reverse
    /// is given as $\mathbf{e}_{\widetilde{S}}$ where the sequence
    /// $\widetilde{S}$ is the reverse of the indices in $S$. For a given basis
    /// element, $e_S\widetilde{e}_S = 1$. The operator extends linearly to
    /// general multivectors.
    ///
    /// Ex: The reverse of $\mathbf{e}_{12} + 3\mathbf{e}_{021}$ is
    /// $\mathbf{e}_{21} + 3\mathbf{e}_{120}$. Signs will be flipped to
    /// reexpress the result in the cyclic basis as
    /// $-\mathbf{e}_{12} - 3\mathbf{e}_{021}$.
    constexpr entity operator~() const noexcept
    {
        entity out = *this;

        if constexpr ((PMask & 0b10) > 0)
        {
            out.p1() = _mm_xor_ps(p1(), _mm_set_ps(-0.f, -0.f, -0.f, 0.f));
        }
        if constexpr ((PMask & 0b100) > 0)
        {
            out.p2() = _mm_xor_ps(p2(), _mm_set_ps(-0.f, -0.f, -0.f, 0.f));
        }
        if constexpr ((PMask & 0b1000) > 0)
        {
            out.p3() = _mm_xor_ps(p3(), _mm_set1_ps(-0.f));
        }

        return out;
    }

    /// Symmetric Inner Product
    ///
    /// The symmetric inner product takes two arguments and contracts the lower
    /// graded element to the greater graded element. If lower graded element
    /// spans an index that is not contained in the higher graded element, the
    /// result is annihilated. Otherwise, the result is the part of the higher
    /// graded element "most unlike" the lower graded element. Thus, the
    /// symmetric inner product can be thought of as a bidirectional contraction
    /// operator.
    ///
    /// There is some merit in providing both a left and right contraction
    /// operator for explicitness. However, when using Klein, it's generally
    /// clear what the interpretation of the symmetric inner product is with
    /// respect to the projection on various entities.
    template <uint8_t PMask2>
    auto operator|(entity<PMask2> const& rhs) const noexcept
    {
        __m128 p0_ = _mm_set1_ps(0.f); // (e0, e1, e2, e3)
        __m128 p1_ = _mm_set1_ps(0.f); // (1, e23, e31, e12)
        __m128 p2_ = _mm_set1_ps(0.f); // (e0123, e01, e02, e03)
        __m128 p3_ = _mm_set1_ps(0.f); // (e123, e032, e013, e021)

        if constexpr ((PMask & 1) > 0)
        {
            if constexpr ((PMask2 & 1) > 0)
            {
                dot00(p0(), rhs.p0(), p1_);
            }
            if constexpr ((PMask2 & 0b10) > 0)
            {
                dot01<false>(p0(), rhs.p1(), p0_);
            }
            if constexpr ((PMask2 & 0b100) > 0)
            {
                __m128 p0_tmp;
                dot02<false>(p0(), rhs.p2(), p0_tmp, p3_);
                if constexpr ((PMask2 & 0b10) > 0)
                {
                    p0_ = _mm_add_ps(p0_tmp, p0_);
                }
                else
                {
                    p0_ = p0_tmp;
                }
            }
            if constexpr ((PMask2 & 0b1000) > 0)
            {
                __m128 p1_tmp;
                dot03(p0(), rhs.p3(), p1_tmp, p2_);
                if constexpr ((PMask2 & 0b1) > 0)
                {
                    p1_ = _mm_add_ps(p1_tmp, p1_);
                }
                else
                {
                    p1_ = p1_tmp;
                }
            }
        }

        if constexpr ((PMask & 0b10) > 0)
        {
            if constexpr ((PMask2 & 0b1) > 0)
            {
                __m128 p0_tmp;
                dot01<true>(rhs.p0(), p1(), p0_tmp);
                if constexpr ((PMask & 0b1) && (PMask2 & 0b110))
                {
                    p0_ = _mm_add_ps(p0_tmp, p0_);
                }
                else
                {
                    p0_ = p0_tmp;
                }
            }
            if constexpr ((PMask2 & 0b10) > 0)
            {
                __m128 p1_tmp;
                dot11(p1(), rhs.p1(), p1_tmp);
                if constexpr ((PMask & 0b1) && (PMask2 & 0b1001))
                {
                    p1_ = _mm_add_ps(p1_, p1_tmp);
                }
                else
                {
                    p1_ = p1_tmp;
                }
            }
            if constexpr ((PMask2 & 0b100) > 0)
            {
                __m128 p2_tmp;
                dot12(p1(), rhs.p2(), p2_tmp);
                if constexpr ((PMask & 1) && (PMask2 & 0b1000))
                {
                    p2_ = _mm_add_ps(p2_, p2_tmp);
                }
                else
                {
                    p2_ = p2_tmp;
                }
            }
            if constexpr ((PMask2 & 0b1000) > 0)
            {
                __m128 p0_tmp;
                dot13(p1(), rhs.p3(), p0_tmp);
                if constexpr (((PMask & 0b1) && (PMask2 & 0b110))
                              || (PMask2 & 0b1))
                {
                    p0_ = _mm_add_ps(p0_, p0_tmp);
                }
                else
                {
                    p0_ = p0_tmp;
                }
            }
        }

        if constexpr ((PMask & 0b100) > 0)
        {
            if constexpr ((PMask2 & 0b1) > 0)
            {
                __m128 p0_tmp;
                __m128 p3_tmp;
                dot02<true>(rhs.p0(), p2(), p0_tmp, p3_tmp);
                if constexpr (((PMask & 0b1) && (PMask2 & 0b110))
                              || ((PMask & 0b10) && (PMask2 & 0b1001)))
                {
                    p0_ = _mm_add_ps(p0_, p0_tmp);
                }
                else
                {
                    p0_ = p0_tmp;
                }
                if constexpr ((PMask & 1) && (PMask2 & 0b100))
                {
                    p3_ = _mm_add_ps(p3_, p3_tmp);
                }
                else
                {
                    p3_ = p3_tmp;
                }
            }
            if constexpr ((PMask2 & 0b10) > 0)
            {
                __m128 p2_tmp;
                dot12(rhs.p1(), p2(), p2_tmp);
                if constexpr ((PMask & 0b10) && (PMask2 & 0b100))
                {
                    p2_ = _mm_add_ps(p2_, p2_tmp);
                }
                else
                {
                    p2_ = p2_tmp;
                }
            }
            if constexpr ((PMask2 & 0b1000) > 0)
            {
                __m128 p0_tmp;
                dot23(p2(), rhs.p3(), p0_tmp);
                if constexpr (((PMask & 0b1) && (PMask2 & 0b110))
                              || ((PMask & 0b10) && (PMask2 & 0b1001))
                              || (PMask2 & 0b1))
                {
                    p0_ = _mm_sub_ps(p0_, p0_tmp);
                }
                else
                {
                    p0_ = _mm_xor_ps(_mm_set_ss(-0.f), p0_tmp);
                }
            }
        }

        if constexpr ((PMask & 0b1000) > 0)
        {
            if constexpr ((PMask2 & 0b1) > 0)
            {
                __m128 p1_tmp;
                __m128 p2_tmp;
                dot03(rhs.p0(), p3(), p1_tmp, p2_tmp);
                if constexpr (((PMask & 1) && (PMask2 & 0b1001))
                              || ((PMask & 0b10) && (PMask2 & 0b10)))
                {
                    p1_ = _mm_add_ps(p1_, p1_tmp);
                }
                else
                {
                    p1_ = p1_tmp;
                }
                if constexpr (((PMask & 0b1) && (PMask2 & 0b1000))
                              || ((PMask & 0b10) && (PMask2 & 0b100))
                              || ((PMask & 0b100) && (PMask2 & 0b10)))
                {
                    p2_ = _mm_add_ps(p2_, p2_tmp);
                }
                else
                {
                    p2_ = p2_tmp;
                }
            }
            if constexpr ((PMask2 & 0b10) > 0)
            {
                __m128 p0_tmp;
                dot13(rhs.p1(), p3(), p0_tmp);
                if constexpr (((PMask & 0b1) && (PMask2 & 0b110))
                              || ((PMask & 0b10) && (PMask2 & 0b1001))
                              || ((PMask & 0b100) & (PMask2 & 0b1001)))
                {
                    p0_ = _mm_add_ps(p0_, p0_tmp);
                }
                else
                {
                    p0_ = p0_tmp;
                }
            }
            if constexpr ((PMask2 & 0b100) > 0)
            {
                __m128 p0_tmp;
                dot23(rhs.p2(), p3(), p0_tmp);
                if constexpr (((PMask & 0b1) && (PMask2 & 0b110))
                              || ((PMask & 0b10) && (PMask2 & 0b1001))
                              || ((PMask & 0b100) & (PMask2 & 0b1001))
                              || (PMask2 & 0b10))
                {
                    p0_ = _mm_add_ps(p0_, p0_tmp);
                }
                else
                {
                    p0_ = p0_tmp;
                }
            }
            if constexpr ((PMask2 & 0b1000) > 0)
            {
                __m128 p1_tmp;
                dot33(p3(), rhs.p3(), p1_tmp);
                if constexpr (((PMask & 0b1) && (PMask2 & 1001))
                              || ((PMask & 0b10) && (PMask2 & 0b10))
                              || (PMask2 & 0b1))
                {
                    p1_ = _mm_add_ps(p1_, p1_tmp);
                }
                else
                {
                    p1_ = p1_tmp;
                }
            }
        }

        constexpr bool p0_set = ((PMask & 0b1) && (PMask2 & 0b110))
                                || ((PMask & 0b10) && (PMask2 & 0b1001))
                                || ((PMask & 0b100) && (PMask2 & 0b1001))
                                || ((PMask & 0b1000) && (PMask2 & 0b110));
        constexpr bool p1_set = ((PMask & 0b1) && (PMask2 & 0b1001))
                                || (PMask & PMask2 & 0b10)
                                || ((PMask & 0b1000) && (PMask2 & 1001));
        constexpr bool p2_set = ((PMask & 0b1) && (PMask2 & 0b1000))
                                || ((PMask & 0b10) && (PMask2 & 0b100))
                                || ((PMask & 0b100) && (PMask2 & 0b10))
                                || ((PMask & 0b1000) && (PMask2 & 0b1));
        constexpr bool p3_set = ((PMask & 0b1) && (PMask2 & 0b100))
                                || ((PMask & 0b100) && (PMask2 & 0b1));

        constexpr uint8_t out_mask
            = (p3_set << 3) | (p2_set << 2) | (p1_set << 1) | p0_set;

        entity<out_mask> out;
        if constexpr (p0_set)
        {
            out.p0() = p0_;
        }
        if constexpr (p1_set)
        {
            out.p1() = p1_;
        }
        if constexpr (p2_set)
        {
            out.p2() = p2_;
        }
        if constexpr (p3_set)
        {
            out.p3() = p3_;
        }
        return out;
    }

    /// Exterior Product
    ///
    /// The exterior product between two basis elements extinguishes if the two
    /// operands share any common index. Otherwise, the element produced is
    /// equivalent to the union of the subspaces. A sign flip is introduced if
    /// the concatenation of the element indices is an odd permutation of the
    /// cyclic basis representation.
    ///
    /// The exterior product extends to general multivectors by linearity.
    ///
    /// Ex: The exterior product $e_1 \wedge \mathbf{e}_{32}$ is
    /// $-\mathbf{e}_{123}$.
    template <uint8_t PMask2>
    auto operator^(entity<PMask2> const& rhs) const noexcept
    {
        __m128 p0_ = _mm_set1_ps(0.f); // (e0, e1, e2, e3)
        __m128 p1_ = _mm_set1_ps(0.f); // (1, e23, e31, e12)
        __m128 p2_ = _mm_set1_ps(0.f); // (e0123, e01, e02, e03)
        __m128 p3_ = _mm_set1_ps(0.f); // (e123, e032, e013, e021)

        if constexpr ((PMask & 1) > 0)
        {
            if constexpr ((PMask2 & 1) > 0)
            {
                ext00(p0(), rhs.p0(), p1_, p2_);
            }
            if constexpr ((PMask2 & 0b10) > 0)
            {
                __m128 tmp;
                ext01(p0(), rhs.p1(), tmp, p3_);
                p0_ = _mm_add_ps(tmp, p0_);
            }
            if constexpr ((PMask2 & 0b100) > 0)
            {
                __m128 tmp;
                ext02(p0(), rhs.p2(), tmp);
                p3_ = _mm_add_ps(tmp, p3_);
            }
            if constexpr ((PMask2 & 0b1000) > 0)
            {
                __m128 tmp;
                ext03<false>(p0(), rhs.p3(), tmp);
                p2_ = _mm_add_ps(tmp, p2_);
            }
        }

        if constexpr ((PMask & 0b10) > 0)
        {
            if constexpr ((PMask2 & 1) > 0)
            {
                __m128 tmp1;
                __m128 tmp2;
                ext01(rhs.p0(), p1(), tmp1, tmp2);
                p0_ = _mm_add_ps(tmp1, p0_);
                p3_ = _mm_add_ps(tmp2, p3_);
            }
            if constexpr ((PMask2 & 0b10) > 0)
            {
                __m128 tmp;
                ext11(p1(), rhs.p1(), tmp);
                p1_ = _mm_add_ps(p1_, tmp);
            }
            if constexpr ((PMask2 & 0b100) > 0)
            {
                __m128 tmp;
                ext12(p1(), rhs.p2(), tmp);
                p2_ = _mm_add_ps(p2_, tmp);
            }
            if constexpr ((PMask2 & 0b1000) > 0)
            {
                __m128 tmp;
                ext13(p1(), rhs.p3(), tmp);
                p3_ = _mm_add_ps(tmp, p3_);
            }
        }

        if constexpr ((PMask & 0b100) > 0)
        {
            if constexpr ((PMask2 & 1) > 0)
            {
                __m128 tmp;
                ext02(rhs.p0(), p2(), tmp);
                p3_ = _mm_add_ps(tmp, p3_);
            }
            if constexpr ((PMask2 & 0b10) > 0)
            {
                __m128 tmp;
                ext12(rhs.p1(), p2(), tmp);
                p2_ = _mm_add_ps(p2_, tmp);
            }
        }

        if constexpr ((PMask & 0b1000) > 0)
        {
            if constexpr ((PMask2 & 1) > 0)
            {
                __m128 tmp;
                ext03<true>(rhs.p0(), p2(), tmp);
                p2_ = _mm_add_ps(tmp, p2_);
            }
            if constexpr ((PMask2 & 0b10) > 0)
            {
                __m128 tmp;
                ext13(rhs.p1(), p3(), tmp);
                p3_ = _mm_add_ps(tmp, p3_);
            }
        }

        constexpr bool p0_set = ((PMask & 0b10) && (PMask2 & 1))
                                || ((PMask & 1) && (PMask2 & 0b10));
        constexpr bool p1_set = ((PMask & PMask2 & 1) || (PMask & PMask2 & 0b10));
        constexpr bool p2_set = (PMask & PMask2 & 1)
                                || ((PMask & 1000) && (PMask2 & 1))
                                || ((PMask & 1) && (PMask2 & 0b1000))
                                || ((PMask & 0b100) && (PMask2 & 0b10))
                                || ((PMask & 0b10) && (PMask2 & 0b100));
        constexpr bool p3_set = ((PMask & 1) && (PMask2 & 0b110))
                                || ((PMask & 0b110) && (PMask2 & 1))
                                || ((PMask & 0b1000) && (PMask2 & 0b10))
                                || ((PMask & 0b10) && (PMask2 & 0b1000));

        constexpr uint8_t out_mask
            = (p3_set << 3) | (p2_set << 2) | (p1_set << 1) | p0_set;

        entity<out_mask> out;
        if constexpr (p0_set)
        {
            out.p0() = p0_;
        }
        if constexpr (p1_set)
        {
            out.p1() = p1_;
        }
        if constexpr (p2_set)
        {
            out.p2() = p2_;
        }
        if constexpr (p3_set)
        {
            out.p3() = p3_;
        }
        return out;
    }

    /// Poincaré Dual
    ///
    /// The Poincaré Dual of an element is the "subspace complement" of the
    /// argument with respect to the pseudoscalar in the exterior algebra. In
    /// practice, it is a relabeling of the coordinates to their
    /// dual-coordinates and is used most often to implement a "join" operation
    /// in terms of the exterior product of the duals of each operand.
    ///
    /// Ex: The dual of the point $\mathbf{e}_{123} + 3\mathbf{e}_{013} -
    /// 2\mathbf{e}_{021}$ (the point at
    /// $(0, 3, -2)$) is the plane $e_0 + 3e_2 - 2e_3$.
    constexpr auto operator!() const noexcept
    {
        // p0 -> p3
        // p1 -> p2
        // p2 -> p1
        // p3 -> p0
        constexpr uint8_t dual_mask = ((PMask & 1) << 3) | ((PMask & 0b10) << 1)
                                      | ((PMask & 0b100) >> 1)
                                      | ((PMask & 0b1000) >> 3);
        entity<dual_mask> out;

        if constexpr ((PMask & 1) > 0)
        {
            out.p3() = p0();
        }

        if constexpr ((PMask & 0b10) > 0)
        {
            out.p2() = p1();
        }

        if constexpr ((PMask & 0b100) > 0)
        {
            out.p1() = p2();
        }

        if constexpr ((PMask & 0b1000) > 0)
        {
            out.p0() = p3();
        }

        return out;
    }

    /// Regressive Product
    ///
    /// The regressive product is implemented in terms of the exterior product.
    /// Given multivectors $\mathbf{a}$ and $\mathbf{b}$, the regressive product
    /// $\mathbf{a}\vee\mathbf{b}$ is equivalent to
    /// $J(J(\mathbf{a})\wedge J(\mathbf{b}))$. Thus, both meets and joins
    /// reside in the same algebraic structure.
    template <uint8_t PMask2>
    constexpr auto operator&(entity<PMask2> const& rhs) const noexcept
    {
        // Because of our choice of the cyclic basis, the dual map can be
        // computed in terms of the exterior product with casting the lhs and
        // rhs entities to their duals.

        return !(!(*this) ^ !rhs);
    }

    /// Geometric Product
    ///
    /// The geometric product extends the exterior product with a notion of a
    /// metric. When the subspace intersection of the operands of two basis
    /// elements is non-zero, instead of the product extinguishing, the grade
    /// collapses and a scalar weight is included in the final result according
    /// to the metric. The geometric product can be used to build rotations, and
    /// by extension, rotations and translations in projective space.
    template <uint8_t PMask2>
    auto operator*(entity<PMask2> const& rhs) const noexcept
    {
        // (Keeping e0 away from the least significant slot is an optimization
        // which allows us to avoid a shuffle in certain circumstances)

        __m128 p0_ = _mm_set1_ps(0.f); // (e0, e1, e2, e3)
        __m128 p1_ = _mm_set1_ps(0.f); // (1, e23, e31, e12)
        __m128 p2_ = _mm_set1_ps(0.f); // (e0123, e01, e02, e03)
        __m128 p3_ = _mm_set1_ps(0.f); // (e123, e032, e013, e021)

        if constexpr ((PMask & 1) > 0)
        {
            if constexpr ((PMask2 & 1) > 0)
            {
                gp00(p0(), rhs.p0(), p1_, p2_);
            }
            if constexpr ((PMask2 & 0b10) > 0)
            {
                gp01<false>(p0(), rhs.p1(), p0_, p3_);
            }
            if constexpr ((PMask2 & 0b100) > 0)
            {
                __m128 p0_tmp;
                __m128 p3_tmp;
                gp02<false>(p0(), rhs.p2(), p0_tmp, p3_tmp);
                if constexpr ((PMask2 & 0b10))
                {
                    p0_ = _mm_add_ps(p0_, p0_tmp);
                }
                else
                {
                    p0_ = p0_tmp;
                }
                if constexpr ((PMask2 & 0b10) > 0)
                {
                    p3_ = _mm_add_ps(p3_, p3_tmp);
                }
                else
                {
                    p3_ = p3_tmp;
                }
            }
            if constexpr ((PMask2 & 0b1000) > 0)
            {
                __m128 p1_tmp;
                __m128 p2_tmp;
                gp03<false>(p0(), rhs.p3(), p1_tmp, p2_tmp);
                if constexpr ((PMask2 & 1) > 0)
                {
                    p1_ = _mm_add_ps(p1_, p1_tmp);
                    p2_ = _mm_add_ps(p2_, p2_tmp);
                }
                else
                {
                    p1_ = p1_tmp;
                    p2_ = p2_tmp;
                }
            }
        }

        if constexpr ((PMask & 0b10) > 0)
        {
            if constexpr ((PMask2 & 1) > 0)
            {
                __m128 p0_tmp;
                __m128 p3_tmp;
                gp01<true>(rhs.p0(), p1(), p0_tmp, p3_tmp);
                if constexpr ((PMask & 1) && (PMask2 & 0b110))
                {
                    p0_ = _mm_add_ps(p0_, p0_tmp);
                    p3_ = _mm_add_ps(p3_, p3_tmp);
                }
                else
                {
                    p0_ = p0_tmp;
                    p3_ = p3_tmp;
                }
            }
            if constexpr ((PMask2 & 0b10) > 0)
            {
                __m128 p1_tmp;
                gp11(p1(), rhs.p1(), p1_tmp);
                if constexpr ((PMask & 1) && (PMask2 & 0b1001))
                {
                    p1_ = _mm_add_ps(p1_, p1_tmp);
                }
                else
                {
                    p1_ = p1_tmp;
                }
            }
            if constexpr ((PMask2 & 0b100) > 0)
            {
                __m128 p2_tmp;
                gp12<false>(p1(), rhs.p2(), p2_tmp);
                if constexpr ((PMask & 1) && (PMask2 & 0b1001))
                {
                    p2_ = _mm_add_ps(p2_, p2_tmp);
                }
                else
                {
                    p2_ = p2_tmp;
                }
            }
            if constexpr ((PMask2 & 0b1000) > 0)
            {
                __m128 p0_tmp;
                __m128 p3_tmp;
                gp13<false>(p1(), rhs.p3(), p0_tmp, p3_tmp);
                if constexpr (((PMask & 1) && (PMask2 & 0b110)) || (PMask2 & 0b1))
                {
                    p0_ = _mm_add_ps(p0_, p0_tmp);
                    p3_ = _mm_add_ps(p3_, p3_tmp);
                }
                else
                {
                    p0_ = p0_tmp;
                    p3_ = p3_tmp;
                }
            }
        }

        if constexpr ((PMask & 0b100) > 0)
        {
            if constexpr ((PMask2 & 1) > 0)
            {
                __m128 p0_tmp;
                __m128 p3_tmp;
                gp02<true>(rhs.p0(), p2(), p0_tmp, p3_tmp);
                if constexpr (((PMask & 1) && (PMask2 & 0b110))
                              || ((PMask & 0b10) && (PMask2 & 0b1001)))
                {
                    p0_ = _mm_add_ps(p0_, p0_tmp);
                    p3_ = _mm_add_ps(p3_, p3_tmp);
                }
                else
                {
                    p0_ = p0_tmp;
                    p3_ = p3_tmp;
                }
            }
            if constexpr ((PMask2 & 0b10) > 0)
            {
                __m128 p2_tmp;
                gp12<true>(p2(), rhs.p1(), p2_tmp);
                if constexpr (((PMask & 1) && (PMask2 & 0b1001))
                              || ((PMask & 0b10) && (PMask2 & 0b100)))
                {
                    p2_ = _mm_add_ps(p2_, p2_tmp);
                }
                else
                {
                    p2_ = p2_tmp;
                }
            }
            if constexpr ((PMask2 & 0b1000) > 0)
            {
                __m128 p0_tmp;
                __m128 p3_tmp;
                gp23<false>(p2(), rhs.p3(), p0_tmp, p3_tmp);
                if constexpr (((PMask & 1) && (PMask2 & 0b110))
                              || ((PMask & 0b10) && (PMask2 & 0b1001))
                              || (PMask2 & 0b1))
                {
                    p0_ = _mm_add_ps(p0_, p0_tmp);
                    p3_ = _mm_add_ps(p3_, p3_tmp);
                }
                else
                {
                    p0_ = p0_tmp;
                    p3_ = p3_tmp;
                }
            }
        }

        if constexpr ((PMask & 0b1000) > 0)
        {
            if constexpr ((PMask2 & 1) > 0)
            {
                __m128 p1_tmp;
                __m128 p2_tmp;
                gp03<true>(rhs.p0(), p3(), p1_tmp, p2_tmp);
                if constexpr (((PMask & 1) && (PMask2 & 0b1001))
                              || (PMask & PMask2 & 0b10))
                {
                    p1_ = _mm_add_ps(p1_, p1_tmp);
                }
                else
                {
                    p1_ = p1_tmp;
                }
                if constexpr (((PMask & 1) && (PMask2 & 0b1001))
                              || ((PMask & 0b10) && (PMask2 & 0b100))
                              || ((PMask & 0b100) && (PMask2 & 0b10)))
                {
                    p2_ = _mm_add_ps(p2_, p2_tmp);
                }
                else
                {
                    p2_ = p2_tmp;
                }
            }
            if constexpr ((PMask2 & 0b10) > 0)
            {
                __m128 p0_tmp;
                __m128 p3_tmp;
                gp13<true>(rhs.p1(), p3(), p0_tmp, p3_tmp);
                if constexpr (((PMask & 1) && (PMask2 & 0b110))
                              || ((PMask & 0b10) && (PMask2 & 0b1001))
                              || ((PMask & 0b100) && (PMask2 & 0b1001)))
                {
                    p0_ = _mm_add_ps(p0_, p0_tmp);
                    p3_ = _mm_add_ps(p3_, p3_tmp);
                }
                else
                {
                    p0_ = p0_tmp;
                    p3_ = p3_tmp;
                }
            }
            if constexpr ((PMask2 & 0b100) > 0)
            {
                __m128 p0_tmp;
                __m128 p3_tmp;
                gp23<true>(rhs.p2(), p3(), p0_tmp, p3_tmp);
                if constexpr (((PMask & 1) && (PMask2 & 0b110))
                              || ((PMask & 0b10) && (PMask2 & 0b1001))
                              || ((PMask & 0b100) && (PMask2 & 0b1001))
                              || (PMask2 & 0b10))
                {
                    p0_ = _mm_add_ps(p0_, p0_tmp);
                    p3_ = _mm_add_ps(p3_, p3_tmp);
                }
                else
                {
                    p0_ = p0_tmp;
                    p3_ = p3_tmp;
                }
            }
            if constexpr ((PMask2 & 0b1000) > 0)
            {
                __m128 p1_tmp;
                __m128 p2_tmp;
                gp33(p3(), rhs.p3(), p1_tmp, p2_tmp);
                if constexpr (((PMask & 1) && (PMask2 & 0b1001))
                              || (PMask & PMask2 & 0b10) || (PMask2 & 1))
                {
                    p1_ = _mm_add_ps(p1_, p1_tmp);
                }
                else
                {
                    p1_ = p1_tmp;
                }
                if constexpr (((PMask & 1) && (PMask2 & 0b1001))
                              || ((PMask & 0b10) && (PMask2 & 0b100))
                              || ((PMask & 0b100) && (PMask2 & 0b10))
                              || (PMask2 & 1))
                {
                    p2_ = _mm_add_ps(p2_, p2_tmp);
                }
                else
                {
                    p2_ = p2_tmp;
                }
            }
        }

        constexpr bool p0_set = ((PMask & 1) && (PMask2 & 0b110))
                                || ((PMask & 0b110) && (PMask2 & 1))
                                || ((PMask & 0b10) && (PMask2 & 0b1000))
                                || ((PMask & 0b1000) && (PMask2 & 0b10));
        constexpr bool p1_set = ((PMask & 1001) && (PMask2 & 0b1001))
                                || ((PMask & 0b10) && (PMask2 & 0b10));
        constexpr bool p2_set = ((PMask & 1001) && (PMask2 & 0b1001))
                                || ((PMask & 0b10) && (PMask2 & 0b100))
                                || ((PMask & 0b100) && (PMask2 & 0b10));
        constexpr bool p3_set = ((PMask & 0b110) && (PMask2 & 0b1001))
                                || ((PMask & 0b1001) && (PMask2 & 0b110));
        constexpr uint8_t out_mask
            = (p3_set << 3) | (p2_set << 2) | (p1_set << 1) | p0_set;

        entity<out_mask> out;
        if constexpr (p0_set)
        {
            out.p0() = p0_;
        }
        if constexpr (p1_set)
        {
            out.p1() = p1_;
        }
        if constexpr (p2_set)
        {
            out.p2() = p2_;
        }
        if constexpr (p3_set)
        {
            out.p3() = p3_;
        }
        return out;
    }

    // NOTE: The accessors below are read-only and NOT intended for frequent
    // use. Accessing individual XMM components is an antipattern. They are
    // provided here as a convenience for testing and debugging.

    // p0: (e0, e1, e2, e3)
    // p1: (1, e23, e31, e12)
    // p2: (e0123, e01, e02, e03)
    // p3: (e123, e032, e013, e021)
    constexpr float scalar() const noexcept
    {
        if constexpr ((PMask & 0b10) > 0)
        {
            return parts[partition_offsets[1]].data[0];
        }
        else
        {
            return 0.f;
        }
    }

    constexpr float e0() const noexcept
    {
        if constexpr ((PMask & 1) > 0)
        {
            return parts[partition_offsets[0]].data[0];
        }
        else
        {
            return 0.f;
        }
    }

    constexpr float e1() const noexcept
    {
        if constexpr ((PMask & 1) > 0)
        {
            return parts[partition_offsets[0]].data[1];
        }
        else
        {
            return 0.f;
        }
    }

    constexpr float e2() const noexcept
    {
        if constexpr ((PMask & 1) > 0)
        {
            return parts[partition_offsets[0]].data[2];
        }
        else
        {
            return 0.f;
        }
    }

    constexpr float e3() const noexcept
    {
        if constexpr ((PMask & 1) > 0)
        {
            return parts[partition_offsets[0]].data[3];
        }
        else
        {
            return 0.f;
        }
    }

    constexpr float e12() const noexcept
    {
        if constexpr ((PMask & 0b10) > 0)
        {
            return parts[partition_offsets[1]].data[3];
        }
        else
        {
            return 0.f;
        }
    }

    constexpr float e21() const noexcept
    {
        if constexpr ((PMask & 0b10) > 0)
        {
            return -parts[partition_offsets[1]].data[3];
        }
        else
        {
            return 0.f;
        }
    }

    constexpr float e31() const noexcept
    {
        if constexpr ((PMask & 0b10) > 0)
        {
            return parts[partition_offsets[1]].data[2];
        }
        else
        {
            return 0.f;
        }
    }

    constexpr float e13() const noexcept
    {
        if constexpr ((PMask & 0b10) > 0)
        {
            return -parts[partition_offsets[1]].data[2];
        }
        else
        {
            return 0.f;
        }
    }

    constexpr float e23() const noexcept
    {
        if constexpr ((PMask & 0b10) > 0)
        {
            return parts[partition_offsets[1]].data[1];
        }
        else
        {
            return 0.f;
        }
    }

    constexpr float e32() const noexcept
    {
        if constexpr ((PMask & 0b10) > 0)
        {
            return -parts[partition_offsets[1]].data[1];
        }
        else
        {
            return 0.f;
        }
    }

    constexpr float e01() const noexcept
    {
        if constexpr ((PMask & 0b100) > 0)
        {
            return parts[partition_offsets[2]].data[1];
        }
        else
        {
            return 0.f;
        }
    }

    constexpr float e10() const noexcept
    {
        if constexpr ((PMask & 0b100) > 0)
        {
            return -parts[partition_offsets[2]].data[1];
        }
        else
        {
            return 0.f;
        }
    }

    constexpr float e02() const noexcept
    {
        if constexpr ((PMask & 0b100) > 0)
        {
            return parts[partition_offsets[2]].data[2];
        }
        else
        {
            return 0.f;
        }
    }

    constexpr float e20() const noexcept
    {
        if constexpr ((PMask & 0b100) > 0)
        {
            return -parts[partition_offsets[2]].data[2];
        }
        else
        {
            return 0.f;
        }
    }

    constexpr float e03() const noexcept
    {
        if constexpr ((PMask & 0b100) > 0)
        {
            return parts[partition_offsets[2]].data[3];
        }
        else
        {
            return 0.f;
        }
    }

    constexpr float e30() const noexcept
    {
        if constexpr ((PMask & 0b100) > 0)
        {
            return -parts[partition_offsets[2]].data[3];
        }
        else
        {
            return 0.f;
        }
    }

    constexpr float e123() const noexcept
    {
        if constexpr ((PMask & 0b1000) > 0)
        {
            return parts[partition_offsets[3]].data[0];
        }
        else
        {
            return 0.f;
        }
    }

    constexpr float e021() const noexcept
    {
        if constexpr ((PMask & 0b1000) > 0)
        {
            return parts[partition_offsets[3]].data[3];
        }
        else
        {
            return 0.f;
        }
    }

    constexpr float e013() const noexcept
    {
        if constexpr ((PMask & 0b1000) > 0)
        {
            return parts[partition_offsets[3]].data[2];
        }
        else
        {
            return 0.f;
        }
    }

    constexpr float e032() const noexcept
    {
        if constexpr ((PMask & 0b1000) > 0)
        {
            return parts[partition_offsets[3]].data[1];
        }
        else
        {
            return 0.f;
        }
    }

    constexpr float e0123() const noexcept
    {
        if constexpr ((PMask & 0b100) > 0)
        {
            return parts[partition_offsets[2]].data[0];
        }
        else
        {
            return 0.f;
        }
    }

    constexpr __m128 const& p0() const noexcept
    {
        return parts[partition_offsets[0]].reg;
    }

    constexpr __m128 const& p1() const noexcept
    {
        return parts[partition_offsets[1]].reg;
    }

    constexpr __m128 const& p2() const noexcept
    {
        return parts[partition_offsets[2]].reg;
    }

    constexpr __m128 const& p3() const noexcept
    {
        return parts[partition_offsets[3]].reg;
    }

    constexpr float const* p0f() const noexcept
    {
        return parts[partition_offsets[0]].data;
    }

    constexpr float const* p1f() const noexcept
    {
        return parts[partition_offsets[1]].data;
    }

    constexpr float const* p2f() const noexcept
    {
        return parts[partition_offsets[2]].data;
    }

    constexpr float const* p3f() const noexcept
    {
        return parts[partition_offsets[3]].data;
    }

    constexpr __m128& p0() noexcept
    {
        return parts[partition_offsets[0]].reg;
    }

    constexpr __m128& p1() noexcept
    {
        return parts[partition_offsets[1]].reg;
    }

    constexpr __m128& p2() noexcept
    {
        return parts[partition_offsets[2]].reg;
    }

    constexpr __m128& p3() noexcept
    {
        return parts[partition_offsets[3]].reg;
    }

protected:
    union alignas(16) partition
    {
        float data[4];
        __m128 reg;
    };

    partition parts[partition_count];

private:
    template <bool Add, uint8_t PMask2>
    constexpr auto add_sub(entity<PMask2> const& other) const noexcept
    {
        constexpr uint8_t pmask = PMask | PMask2;
        kln::entity<pmask> out;

        uint8_t offset     = 0;
        uint8_t lhs_offset = 0;
        uint8_t rhs_offset = 0;
        for (uint8_t m = 1; m != 0b10000; m <<= 1)
        {
            if (PMask & m)
            {
                if (PMask2 & m)
                {
                    if constexpr (Add)
                    {
                        out.parts[offset++].reg
                            = _mm_add_ps(parts[lhs_offset++].reg,
                                         other.parts[rhs_offset++].reg);
                    }
                    else
                    {
                        out.parts[offset++].reg
                            = _mm_sub_ps(parts[lhs_offset++].reg,
                                         other.parts[rhs_offset++].reg);
                    }
                }
                else
                {
                    out.parts[offset++].reg = parts[lhs_offset++].reg;
                }
            }
            else
            {
                if (PMask2 & m)
                {
                    if constexpr (Add)
                    {
                        out.parts[offset++].reg = other.parts[rhs_offset++].reg;
                    }
                    else
                    {
                        out.parts[offset++].reg = _mm_xor_ps(
                            other.parts[rhs_offset++].reg, _mm_set1_ps(-0.0));
                    }
                }
            }
        }

        return out;
    }

    // If this is a mutable rvalue or non-const, we can add other in-place and
    // save some register allocation assuming the partition mask stays the same.
    template <bool Add, uint8_t PMask2>
    constexpr auto add_sub(entity<PMask2> const& other) noexcept
    {
        constexpr uint8_t pmask = PMask | PMask2;
        if constexpr (pmask == PMask)
        {
            uint8_t offset     = 0;
            uint8_t rhs_offset = 0;
            for (uint8_t m = 1; m != 0b10000; m <<= 1)
            {
                if (PMask2 & m)
                {
                    if constexpr (Add)
                    {
                        parts[offset].reg = _mm_add_ps(
                            parts[offset].reg, other.parts[rhs_offset++].reg);
                    }
                    else
                    {
                        parts[offset].reg = _mm_sub_ps(
                            parts[offset].reg, other.parts[rhs_offset++].reg);
                    }
                    ++offset;
                }
            }

            return *this;
        }
        else
        {
            kln::entity<pmask> out;
            out = static_cast<entity const&>(*this).add_sub<Add>(other);
            return out;
        }
    }
};
} // namespace kln