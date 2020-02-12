#pragma once

#include "poly.hpp"

#include <cstdint>
#include <iostream>

uint32_t popcnt(uint32_t i);

class algebra
{
public:
    // Positive dimensions, negative dimensions, degenerate dimensions
    // Note that in terms of basis labels, degenerate dimensions come first so
    // that the indexing doesn't vary with spatial dimension
    algebra(uint32_t p, uint32_t q, uint32_t r);

    // The sign of the result indicates if a sign flip is needed
    // Elements are encoded 1 + the bitfield to disambiguate 0.
    int32_t mul(uint32_t lhs, uint32_t rhs) const noexcept;

    // Return the parity of a reversion operator on a given element
    bool rev(uint32_t in) const noexcept;

    bool operator==(algebra const&) const noexcept;

private:
    uint32_t p_;
    uint32_t q_;
    uint32_t r_;
    uint32_t dim_;
};

struct elem_comp
{
    bool operator()(uint32_t lhs, uint32_t rhs) const noexcept
    {
        uint32_t lhs_pop = popcnt(lhs);
        uint32_t rhs_pop = popcnt(rhs);

        if (lhs_pop < rhs_pop)
        {
            return true;
        }
        else if (lhs_pop > rhs_pop)
        {
            return false;
        }
        else
        {
            return lhs < rhs;
        }
    }
};

class mv
{
public:
    mv() = default;
    mv(algebra const& a) noexcept;

    mv operator-() const& noexcept;
    mv& operator-() && noexcept;
    mv operator~() const& noexcept;
    mv& operator~() && noexcept;
    mv& operator*=(mv const& other) noexcept;
    mv& operator+=(mv const& other) noexcept;
    mv& operator-=(mv const& other) noexcept;

    mv& push(uint32_t e, poly const& p) noexcept;

    // Map from basis blade to polynomial
    std::map<uint32_t, poly, elem_comp> terms;

private:
    friend mv operator+(mv const& lhs, mv const& rhs) noexcept;
    friend mv operator*(mv const& lhs, mv const& rhs) noexcept;
    algebra const* algebra_ = nullptr;
};

mv operator+(mv const& lhs, mv const& rhs) noexcept;
mv operator*(mv const& lhs, mv const& rhs) noexcept;
std::ostream& operator<<(std::ostream& os, mv const& m) noexcept;