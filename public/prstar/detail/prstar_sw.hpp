// File: prstar_sw.hpp
// Purpose: Define functions of the form swAB where A and B are partition
// indices. Each function so-defined computes the sandwich operator using vector
// intrinsics. The partition index determines which basis elements are present
// in each XMM component of the operand.
//
// Notes:
// 1. The first argument is always the TARGET which is the multivector to apply
//    the sandwich operator to.
// 2. The second operator MAY be a bivector or motor (sandwiching with
//    a point or vector isn't supported at this time).
// 3. For efficiency, the sandwich operator is NOT implemented in terms of two
//    geometric products and a reversion. The result is nevertheless equivalent.

#pragma once

#include "prstar_sse.hpp"

namespace prs
{
inline namespace detail
{
    // Partition memory layouts
    //     LSB --> MSB
    // p0: (e3, e2, e1, e0)
    // p1: (1, e12, e31, e23)
    // p2: (e0123, e01, e02, e03)
    // p3: (e123, e021, e013, e032)

    // Apply a rotor to a plane
    // b * a * rev(b)
    inline auto sw01(__m128 const& a, __m128 const& b) noexcept
    {
        // (b0 + b1*e12 + b2*e31 + b3*e23) * (a3*e0 + a2*e1 + a1*e2 + a0*e3)
        //   * (b0 - b1*e12 - b2*e31 - b3*e23) =
        //
        // (b0*a3*b0)*e0
        // + (b0*a2*b0 + b0*a1*b1 - b0*a0*b2)*e1
        // + (-b0*a2*b1 + b0*a1*b0 + b0*a0*b3)*e2
        // + (b0*a2*b2 - b0*a1*b3 + b0*a0*b0)*e3
        // + (-b0*a2*b3 - b0*a1*b2 - b0*a0*b1)*e123
        // + (b0*a3*b1)*e021
        // + (b0*a3*b2)*e031
        // + (b0*a3*b3)*e032
    }
} // namespace detail
} // namespace prs