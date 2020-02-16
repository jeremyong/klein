#pragma once

#include "exterior_product.hpp"
#include "geometric_product.hpp"
#include "sandwich.hpp"
#include <cstdint>
#include <type_traits>

namespace kln
{
// The full P(R_{3, 0, 1}) graded-algebra requires 16 floats to represent a
// general multivector. However, it is very common to perform computation on
// either the odd or even subalgebras. For example, motor composition lives
// entirely within the even subalgebra, while entities such as planes, and
// points exist in the odd subalgebra.

// To compute PGA elements using SSE, we partition the basis into four
// partitions corresponding to the following scheme:
//
//     LSB --> MSB
// p0: (e3, e2, e1, e0)
// p1: (1, e12, e31, e23)
// p2: (e0123, e01, e02, e03)
// p3: (e123, e021, e013, e032)
//
// The scalar and pseudoscalar are packed in partitions p1 and p2 along with the
// 6 bivector elements. The scheme groups, for the most part, elements of
// similar grade and the presence of the degenerate generator. When
// non-uniformity exists within a partition (mixed degenerate and non-degenerate
// components, or mixed grade), the "exception" is housed in the first component
// so that the same swizzle masks can be used.

// All partitions contain 4 packed single-precision floating point values.
union alignas(16) partition
{
    float data[4];
    __m128 reg;
};

struct base_entity
{};

// An entity's memory layout is specified based on which partitions are present.
// The least significant bit in the mask corresponds to the presence of P0, and
// the 4th least significant bit corresponds to the presence of P3.
// This class is not intended to be used by the user directly.
template <uint8_t PMask /* Partition Mask */>
struct entity : public base_entity
{
    template <uint8_t P>
    friend class entity;

    constexpr static uint8_t partition_count
        = (PMask & 1) + ((PMask >> 1) & 0b1) + ((PMask >> 2) & 1)
          + ((PMask >> 3) & 1);
    constexpr static uint8_t partition_offsets[4]
        = {0,
           (PMask & 1),
           (PMask & 1) + ((PMask >> 1) & 1),
           (PMask & 1) + ((PMask >> 1) & 1) + ((PMask >> 2) & 1)};
    constexpr static uint8_t partition_mask = PMask;

    entity()
    {}

    entity(entity const& other)
    {
        for (uint8_t i = 0; i != partition_count; ++i)
        {
            parts[i].reg = other.parts[i].reg;
        }
    }

    template <uint8_t P>
    constexpr auto operator+(entity<P> const& other) const noexcept
    {
        return add_sub<true>(other);
    }

    template <uint8_t P>
    constexpr auto operator+(entity<P> const& other) noexcept
    {
        return add_sub<true>(other);
    }

    template <uint8_t P>
    constexpr auto operator-(entity<P> const& other) const noexcept
    {
        return add_sub<false>(other);
    }

    template <uint8_t P>
    constexpr auto operator-(entity<P> const& other) noexcept
    {
        return add_sub<false>(other);
    }

    // Scale
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

    [[nodiscard]] entity operator*(float scalar) const noexcept
    {
        entity out;
        __m128 s = _mm_set1_ps(scalar);

        if constexpr (PMask & 0b1)
        {
            out.p0() = _mm_mul_ps(p0(), s);
        }
        if constexpr (PMask & 0b10)
        {
            out.p1() = _mm_mul_ps(p1(), s);
        }
        if constexpr (PMask & 0b100)
        {
            out.p2() = _mm_mul_ps(p2(), s);
        }
        if constexpr (PMask & 0b1000)
        {
            out.p3() = _mm_mul_ps(p3(), s);
        }

        return out;
    }

    entity& operator/=(float s) noexcept
    {
        return operator*=(1.f / s);
    }

    [[nodiscard]] entity operator/(float s) const noexcept
    {
        return operator*(1.f / s);
    }

    // Reverse
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

    template <uint8_t PMask2>
    constexpr auto operator^(entity<PMask2> const& rhs) const noexcept
    {
        __m128 p0_ = _mm_set1_ps(0.f); // (e3, e2, e1, e0)
        __m128 p1_ = _mm_set1_ps(0.f); // (1, e12, e31, e23)
        __m128 p2_ = _mm_set1_ps(0.f); // (e0123, e01, e02, e03)
        __m128 p3_ = _mm_set1_ps(0.f); // (e123, e021, e013, e032)

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

    // Geometric Product
    template <uint8_t PMask2>
    constexpr auto operator*(entity<PMask2> const& rhs) const noexcept
    {
        // (Keeping e0 away from the least significant slot is an optimization
        // which allows us to avoid a shuffle in certain circumstances)

        __m128 p0_ = _mm_set1_ps(0.f); // (e3, e2, e1, e0)
        __m128 p1_ = _mm_set1_ps(0.f); // (1, e12, e31, e23)
        __m128 p2_ = _mm_set1_ps(0.f); // (e0123, e01, e02, e03)
        __m128 p3_ = _mm_set1_ps(0.f); // (e123, e021, e013, e032)

        if constexpr ((PMask & 1) > 0)
        {
            if constexpr ((PMask2 & 1) > 0)
            {
                p1p2 p1p2_ = gp00(p0(), rhs.p0());
                p1_        = p1p2_.p1;
                p2_        = p1p2_.p2;
            }
            if constexpr ((PMask2 & 0b10) > 0)
            {
                p0p3 p0p3_ = gp01(p0(), rhs.p1());
                p0_        = p0p3_.p0;
                p3_        = p0p3_.p3;
            }
            if constexpr ((PMask2 & 0b100) > 0)
            {
                p0p3 p0p3_ = gp02(p0(), rhs.p2());
                p0_        = _mm_add_ps(p0_, p0p3_.p0);
                p3_        = _mm_add_ps(p3_, p0p3_.p3);
            }
            if constexpr ((PMask2 & 0b1000) > 0)
            {
                p1p2 p1p2_ = gp03(p0(), rhs.p3());
                p1_        = _mm_add_ps(p1_, p1p2_.p1);
                p2_        = _mm_add_ps(p2_, p1p2_.p2);
            }
        }

        if constexpr ((PMask & 0b10) > 0)
        {
            if constexpr ((PMask2 & 1) > 0)
            {
                p0p3 p0p3_ = gp10(p1(), rhs.p0());
                p0_        = _mm_add_ps(p0_, p0p3_.p0);
                p3_        = _mm_add_ps(p3_, p0p3_.p3);
            }
            if constexpr ((PMask2 & 0b10) > 0)
            {
                p1_ = _mm_add_ps(p1_, gp11(p1(), rhs.p1()));
            }
            if constexpr ((PMask2 & 0b100) > 0)
            {
                p2_ = _mm_add_ps(p2_, gp12(p1(), rhs.p2()));
            }
            if constexpr ((PMask2 & 0b1000) > 0)
            {
                p0p3 p0p3_ = gp13(p1(), rhs.p3());
                p0_        = _mm_add_ps(p0_, p0p3_.p0);
                p3_        = _mm_add_ps(p3_, p0p3_.p3);
            }
        }

        if constexpr ((PMask & 0b100) > 0)
        {
            if constexpr ((PMask2 & 1) > 0)
            {
                p0p3 p0p3_ = gp20(p2(), rhs.p0());
                p0_        = _mm_add_ps(p0_, p0p3_.p0);
                p3_        = _mm_add_ps(p3_, p0p3_.p3);
            }
            if constexpr ((PMask2 & 0b10) > 0)
            {
                p2_ = _mm_add_ps(p2_, gp21(p2(), rhs.p1()));
            }
            if constexpr ((PMask2 & 0b1000) > 0)
            {
                p0p3 p0p3_ = gp23(p2(), rhs.p3());
                p0_        = _mm_add_ps(p0_, p0p3_.p0);
                p3_        = _mm_add_ps(p3_, p0p3_.p3);
            }
        }

        if constexpr ((PMask & 0b1000) > 0)
        {
            if constexpr ((PMask2 & 1) > 0)
            {
                p1p2 p1p2_ = gp30(p3(), rhs.p0());
                p1_        = _mm_add_ps(p1_, p1p2_.p1);
                p2_        = _mm_add_ps(p2_, p1p2_.p2);
            }
            if constexpr ((PMask2 & 0b10) > 0)
            {
                p0p3 p0p3_ = gp31(p3(), rhs.p1());
                p0_        = _mm_add_ps(p0_, p0p3_.p0);
                p3_        = _mm_add_ps(p3_, p0p3_.p3);
            }
            if constexpr ((PMask2 & 0b100) > 0)
            {
                p0p3 p0p3_ = gp32(p3(), rhs.p2());
                p0_        = _mm_add_ps(p0_, p0p3_.p0);
                p3_        = _mm_add_ps(p3_, p0p3_.p3);
            }
            if constexpr ((PMask2 & 0b1000) > 0)
            {
                p1p2 p1p2_ = gp33(p3(), rhs.p3());
                p1_        = _mm_add_ps(p1_, p1p2_.p1);
                p2_        = _mm_add_ps(p2_, p1p2_.p2);
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

    // p0: (e3, e2, e1, e0)
    // p1: (1, e12, e31, e23)
    // p2: (e0123, e01, e02, e03)
    // p3: (e123, e021, e013, e032)
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
            return parts[partition_offsets[0]].data[3];
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
            return parts[partition_offsets[0]].data[2];
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
            return parts[partition_offsets[0]].data[1];
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
            return parts[partition_offsets[0]].data[0];
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
            return parts[partition_offsets[1]].data[1];
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
            return -parts[partition_offsets[1]].data[1];
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
            return parts[partition_offsets[1]].data[3];
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
            return -parts[partition_offsets[1]].data[3];
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
            return parts[partition_offsets[3]].data[1];
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
            return parts[partition_offsets[3]].data[3];
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

    __m128 const& p0() const noexcept
    {
        return parts[partition_offsets[0]].reg;
    }

    __m128 const& p1() const noexcept
    {
        return parts[partition_offsets[1]].reg;
    }

    __m128 const& p2() const noexcept
    {
        return parts[partition_offsets[2]].reg;
    }

    __m128 const& p3() const noexcept
    {
        return parts[partition_offsets[3]].reg;
    }

    float const* p0f() const noexcept
    {
        return parts[partition_offsets[0]].data;
    }

    float const* p1f() const noexcept
    {
        return parts[partition_offsets[1]].data;
    }

    float const* p2f() const noexcept
    {
        return parts[partition_offsets[2]].data;
    }

    float const* p3f() const noexcept
    {
        return parts[partition_offsets[3]].data;
    }

    __m128& p0() noexcept
    {
        return parts[partition_offsets[0]].reg;
    }

    __m128& p1() noexcept
    {
        return parts[partition_offsets[1]].reg;
    }

    __m128& p2() noexcept
    {
        return parts[partition_offsets[2]].reg;
    }

    __m128& p3() noexcept
    {
        return parts[partition_offsets[3]].reg;
    }

protected:
    partition parts[partition_count];

private:
    template <bool Add, uint8_t PMask2>
    constexpr auto add_sub(entity<PMask2> const& other) const& noexcept
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

    // If this is a mutable rvalue, we can add other in-place and save some
    // register allocation assuming the partition mask stays the same.
    template <bool Add, uint8_t PMask2>
        constexpr auto add_sub(entity<PMask2> const& other) && noexcept
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