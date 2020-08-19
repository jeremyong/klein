#include "ga.hpp"

#include <cassert>
#include <immintrin.h>

uint32_t popcnt(uint32_t i)
{
    return _mm_popcnt_u32(i);
}

algebra::algebra(uint32_t p, uint32_t q, uint32_t r)
    : p_{p}
    , q_{q}
    , r_{r}
    , dim_{p + q + r}
{
    assert(dim_ < 32
           && "Exceeded maximum metric size that can fit in a 32-bit integer");
}

bool algebra::operator==(algebra const& other) const noexcept
{
    return p_ == other.p_ && q_ == other.q_ && r_ == other.r_;
}

int32_t algebra::mul(uint32_t lhs, uint32_t rhs) const noexcept
{
    if (lhs == 0 && rhs == 0)
    {
        return 1;
    }
    else if (lhs == 0)
    {
        return rhs + 1;
    }
    else if (rhs == 0)
    {
        return lhs + 1;
    }

    int factor = 1;

    for (uint32_t i = 0; i != dim_; ++i)
    {
        uint8_t index = dim_ - i - 1;
        uint8_t bit   = 1 << index;
        bool lhs_e    = (lhs & bit) > 0;
        bool rhs_e    = (rhs & bit) > 0;

        if (lhs_e)
        {
            if ((popcnt(rhs & (bit - 1)) & 1) > 0)
            {
                factor = -factor;
            }

            if (rhs_e)
            {
                // Metric contraction
                if (r_ > 0 && index < r_)
                {
                    // Degenerate
                    return 0;
                }
                else if (index >= p_ + r_)
                {
                    factor = -factor;
                }
            }
        }
    }

    return factor * ((lhs ^ rhs) + 1);
}

int32_t algebra::ext(uint32_t lhs, uint32_t rhs) const noexcept
{
    if ((lhs & rhs) > 0)
    {
        return 0;
    }

    int factor = 1;

    // The lhs and rhs need to be interleaved and swaps counted
    for (uint32_t i = 0; i != dim_; ++i)
    {
        if ((rhs & (1 << i)) > 0)
        {
            int swaps = popcnt(lhs & ~((1 << (i + 1)) - 1));
            if (swaps & 1)
            {
                factor = -factor;
            }
        }
    }

    return factor * ((lhs | rhs) + 1);
}

int32_t algebra::dual(uint32_t in) const noexcept
{
    // NOTE: for now, this operator is specialized for P(R*_{3, 0, 1})
    assert(p_ == 3);
    assert(q_ == 0);
    assert(r_ == 1);

    // The dual-coordinate map J maps elements e_S to their right complement E^T
    // where ST is an even permutation of {0123}. Exceptions are made for the
    // trivector complements since their complements do not have indices that
    // can be swapped. For these cases, a minus sign is introduced since the
    // resulting permutation will be odd.
    switch (in)
    {
    case 0:
        return 0b1111 + 1;
    case 1:
        return 0b1110 + 1;
    case 0b10:
        return -(0b1101 + 1);
    case 0b100:
        return 0b1011 + 1;
    case 0b1000:
        return -(0b111 + 1);
    case 0b11:
        return 0b1100 + 1;
    case 0b101:
        return -(0b1010 + 1);
    case 0b1001:
        return 0b110 + 1;
    case 0b110:
        return 0b1001 + 1;
    case 0b1010:
        return -(0b101 + 1);
    case 0b1100:
        return 0b11 + 1;
    case 0b111:
        return -(0b1000 + 1);
    case 0b1011:
        return 0b100 + 1;
    case 0b1101:
        return -(0b10 + 1);
    case 0b1110:
        return 0b1 + 1;
    case 0b1111:
    default:
        return 1;
    }
}

int32_t algebra::reg(uint32_t lhs, uint32_t rhs) const noexcept
{
    int32_t lhs_j = dual(lhs);
    int32_t rhs_j = dual(rhs);

    int factor = lhs_j < 0 ? -1 : 1;
    if (rhs_j < 0)
    {
        factor *= -1;
    }

    int32_t ext_j = ext(std::abs(lhs_j) - 1, std::abs(rhs_j) - 1);
    if (ext_j < 0)
    {
        factor *= -1;
    }
    else if (ext_j == 0)
    {
        return 0;
    }

    int32_t result = dual(std::abs(ext_j) - 1);
    return factor * result;
}

// The inner product contracts indices between the LHS and RHS producing an
// element that is "most unlike" the lower-graded element.
int32_t algebra::dot(uint32_t lhs, uint32_t rhs) const noexcept
{
    if (lhs == 0 || rhs == 0)
    {
        return 0;
    }

    // Reuse the existing geometric product to compute the inner product
    int32_t g = mul(lhs, rhs);
    if (g == 0)
    {
        return 0;
    }

    int32_t target
        = std::abs(static_cast<int>(popcnt(lhs)) - static_cast<int>(popcnt(rhs)));

    // If the target grade doesn't match the grade difference, we know that a
    // full contraction could not be performed in one direction or the other.
    if (static_cast<int>(popcnt(std::abs(g) - 1)) == target)
    {
        return g;
    }

    return 0;
}

bool algebra::rev(uint32_t in) const noexcept
{
    uint32_t bits = popcnt(in);
    return (bits & 0b10) > 0;
}

mv::mv(algebra const& a) noexcept
    : algebra_{&a}
{}

mv& mv::push(uint32_t e, poly const& p) noexcept
{
    auto it = terms.find(e);
    if (it == terms.end())
    {
        terms.emplace(e, p);
    }
    else
    {
        it->second += p;

        if (it->second.terms.empty())
        {
            terms.erase(it);
        }
    }

    return *this;
}

mv mv::operator-() const& noexcept
{
    mv out{*this};
    for (auto& [e, p] : out.terms)
    {
        p = -p;
    }
    return out;
}

mv& mv::operator-() && noexcept
{
    for (auto& [e, p] : terms)
    {
        p = -p;
    }
    return *this;
}

mv mv::operator~() const& noexcept
{
    mv out{*this};
    for (auto& [e, p] : out.terms)
    {
        if (algebra_->rev(e))
        {
            p = -p;
        }
    }
    return out;
}

mv& mv::operator~() && noexcept
{
    for (auto& [e, p] : terms)
    {
        if (algebra_->rev(e))
        {
            p = -p;
        }
    }
    return *this;
}

mv& mv::operator+=(mv const& other) noexcept
{
    for (auto&& [e, p] : other.terms)
    {
        push(e, p);
    }

    return *this;
}

mv& mv::operator-=(mv const& other) noexcept
{
    for (auto&& [e, p] : other.terms)
    {
        push(e, -p);
    }

    return *this;
}

mv operator+(mv const& lhs, mv const& rhs) noexcept
{
    mv out{lhs};
    out += rhs;
    return out;
}

mv& mv::operator*=(mv const& other) noexcept
{
    mv result = *this * other;
    std::swap(terms, result.terms);
    return *this;
}

mv operator*(mv const& lhs, mv const& rhs) noexcept
{
    mv out{*lhs.algebra_};

    for (auto&& [e1, p1] : lhs.terms)
    {
        for (auto&& [e2, p2] : rhs.terms)
        {
            int32_t result = lhs.algebra_->mul(e1, e2);
            if (result != 0)
            {
                uint32_t e = std::abs(result) - 1;
                auto it    = out.terms.find(e);

                poly p12 = p1 * p2;

                if (it == out.terms.end())
                {
                    it = out.terms.emplace(e, poly{}).first;
                }

                if (result < 0)
                {
                    it->second += -p12;
                }
                else
                {
                    it->second += p12;
                }
            }
        }
    }

    return out.prune();
}

mv& mv::operator^=(mv const& other) noexcept
{
    mv result = *this ^ other;
    std::swap(terms, result.terms);
    return *this;
}

mv operator^(mv const& lhs, mv const& rhs) noexcept
{
    mv out{*lhs.algebra_};

    for (auto&& [e1, p1] : lhs.terms)
    {
        for (auto&& [e2, p2] : rhs.terms)
        {
            int32_t result = lhs.algebra_->ext(e1, e2);
            if (result != 0)
            {
                uint32_t e = std::abs(result) - 1;
                auto it    = out.terms.find(e);

                poly p12 = p1 * p2;

                if (it == out.terms.end())
                {
                    it = out.terms.emplace(e, poly{}).first;
                }

                if (result < 0)
                {
                    it->second += -p12;
                }
                else
                {
                    it->second += p12;
                }
            }
        }
    }

    return out.prune();
}

mv& mv::operator&=(mv const& other) noexcept
{
    mv result = *this & other;
    std::swap(terms, result.terms);
    return *this;
}

mv operator&(mv const& lhs, mv const& rhs) noexcept
{
    mv out{*lhs.algebra_};

    for (auto&& [e1, p1] : lhs.terms)
    {
        for (auto&& [e2, p2] : rhs.terms)
        {
            int32_t result = lhs.algebra_->reg(e1, e2);
            if (result != 0)
            {
                uint32_t e = std::abs(result) - 1;
                auto it    = out.terms.find(e);

                poly p12 = p1 * p2;

                if (it == out.terms.end())
                {
                    it = out.terms.emplace(e, poly{}).first;
                }

                if (result < 0)
                {
                    it->second += -p12;
                }
                else
                {
                    it->second += p12;
                }
            }
        }
    }

    return out.prune();
}

mv& mv::operator|=(mv const& other) noexcept
{
    mv result = *this | other;
    std::swap(terms, result.terms);
    return *this;
}

mv operator|(mv const& lhs, mv const& rhs) noexcept
{
    mv out{*lhs.algebra_};

    for (auto&& [e1, p1] : lhs.terms)
    {
        for (auto&& [e2, p2] : rhs.terms)
        {
            int32_t result = lhs.algebra_->dot(e1, e2);
            if (result != 0)
            {
                uint32_t e = std::abs(result) - 1;
                auto it    = out.terms.find(e);

                poly p12 = p1 * p2;

                if (it == out.terms.end())
                {
                    it = out.terms.emplace(e, poly{}).first;
                }

                if (result < 0)
                {
                    it->second += -p12;
                }
                else
                {
                    it->second += p12;
                }
            }
        }
    }

    return out.prune();
}

mv& mv::prune()
{
    // Remove empty terms
    for (auto it = terms.begin(); it != terms.end();)
    {
        if (it->second.terms.empty())
        {
            it = terms.erase(it);
        }
        else
        {
            ++it;
        }
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os,
                         std::map<uint32_t, poly>::const_iterator const& it) noexcept
{
    os << it->second;

    if (it->first == 0)
    {
        return os;
    }

    os << " e";

    for (size_t i = 0; i != 9; ++i)
    {
        if ((it->first & (1 << i)) > 0)
        {
            os << i;
        }
    }

    return os;
}

std::ostream& operator<<(std::ostream& os, mv const& m) noexcept
{
    if (m.terms.empty())
    {
        os << '0';
        return os;
    }

    auto it = m.terms.cbegin();
    os << it;
    ++it;

    for (; it != m.terms.cend(); ++it)
    {
        os << " + " << it;
    }

    return os;
}