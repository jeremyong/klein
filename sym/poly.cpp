#include "poly.hpp"

mon& mon::push(std::string var, int deg) noexcept
{
    if (deg == 0)
    {
        return *this;
    }

    auto it = factors.find(var);
    if (it == factors.end())
    {
        factors.emplace(var, deg);
    }
    else
    {
        if (it->second + deg == 0)
        {
            factors.erase(it);
        }
        else
        {
            it->second += deg;
        }
    }

    return *this;
}

int mon::degree() const noexcept
{
    int out = 0;
    for (auto&& [v, d] : factors)
    {
        out += d;
    }
    return out;
}

bool operator==(mon const& lhs, mon const& rhs) noexcept
{
    if (lhs.factors.size() != rhs.factors.size())
    {
        return false;
    }

    auto lhs_it = lhs.factors.begin();
    auto rhs_it = rhs.factors.begin();

    while (lhs_it != lhs.factors.end() && rhs_it != rhs.factors.end())
    {
        if (lhs_it->first != rhs_it->first)
        {
            return false;
        }

        if (lhs_it->second != rhs_it->second)
        {
            return false;
        }
        ++lhs_it;
        ++rhs_it;
    }
    return true;
}

// Graded lexical comparison (grlex)
bool operator<(mon const& lhs, mon const& rhs) noexcept
{
    int lhs_d = lhs.degree();
    int rhs_d = rhs.degree();
    if (lhs_d < rhs_d)
    {
        return true;
    }
    else if (lhs_d > rhs_d)
    {
        return false;
    }

    auto lhs_it = lhs.factors.begin();
    auto rhs_it = rhs.factors.begin();

    while (lhs_it != lhs.factors.end() || rhs_it != rhs.factors.end())
    {
        if (lhs_it == lhs.factors.end())
        {
            return true;
        }
        else if (rhs_it == rhs.factors.end())
        {
            return false;
        }
        else if (lhs_it->first < rhs_it->first)
        {
            return true;
        }
        else if (rhs_it->first < lhs_it->first)
        {
            return false;
        }
        else if (lhs_it->second < rhs_it->second)
        {
            return true;
        }
        else if (lhs_it->second > rhs_it->second)
        {
            return false;
        }
        ++lhs_it;
        ++rhs_it;
    }

    // Unreachable
    return false;
}

mon& mon::operator*=(mon const& other) noexcept
{
    for (auto&& [v, d] : other.factors)
    {
        auto it = factors.find(v);

        if (it == factors.end())
        {
            factors.emplace(v, d);
        }
        else
        {
            if (it->second + d == 0)
            {
                factors.erase(it);
            }
            else
            {
                it->second += d;
            }
        }
    }

    return *this;
}

mon operator*(mon const& lhs, mon const& rhs) noexcept
{
    mon out = lhs;
    out *= rhs;
    return out;
}

poly& poly::push(mon const& m, float f) noexcept
{
    auto it = terms.find(m);
    if (it == terms.end())
    {
        terms.emplace(m, f);
    }
    else
    {
        if (it->second + f == 0.f)
        {
            terms.erase(it);
        }
        else
        {
            it->second += f;
        }
    }

    return *this;
}

poly poly::operator-() const& noexcept
{
    poly out = *this;
    for (auto& [m, f] : out.terms)
    {
        f *= -1;
    }
    return out;
}

poly& poly::operator-() && noexcept
{
    for (auto& [m, f] : terms)
    {
        f *= -1;
    }

    return *this;
}

poly& poly::operator+=(poly const& other) noexcept
{
    for (auto&& [m, f] : other.terms)
    {
        auto it = terms.find(m);
        if (it == terms.end())
        {
            terms.emplace(m, f);
        }
        else
        {
            if (it->second + f == 0.f)
            {
                terms.erase(it);
            }
            else
            {
                it->second += f;
            }
        }
    }
    return *this;
}

poly operator+(poly const& lhs, poly const& rhs) noexcept
{
    poly out = lhs;
    out += rhs;
    return out;
}

poly operator*(poly const& lhs, poly const& rhs) noexcept
{
    poly out;

    for (auto&& [m1, f1] : lhs.terms)
    {
        poly t;

        for (auto&& [m2, f2] : rhs.terms)
        {
            if (f1 * f2 != 0.f)
            {
                auto m = m1 * m2;
                t.terms[m] += f1 * f2;
            }
        }

        out += t;
    }

    return out;
}

poly& poly::operator*=(poly const& other) noexcept
{
    poly temp = *this * other;
    std::swap(terms, temp.terms);
    return *this;
}

std::ostream&
operator<<(std::ostream& os,
           std::map<std::string, int>::const_iterator const& it) noexcept
{
    if (it->second == 0)
    {
        return os;
    }

    os << it->first;
    if (it->second != 1)
    {
        os << '^' << it->second;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os,
                         std::map<mon, float>::const_iterator const& it) noexcept
{
    if (it->second == -1.f)
    {
        os << '-';
    }
    else if (it->second != 1.f)
    {
        os << it->second;
    }

    if (it->first.factors.empty())
    {
        return os;
    }

    auto factor = it->first.factors.cbegin();
    os << factor;
    ++factor;

    for (; factor != it->first.factors.cend(); ++factor)
    {
        os << ' ' << factor;
    }

    return os;
}

std::ostream& operator<<(std::ostream& os, poly const& p) noexcept
{
    if (p.terms.empty())
    {
        return os;
    }

    bool multi = p.terms.size() > 1;

    if (multi)
    {
        os << '(';
    }

    auto it = p.terms.cbegin();
    os << it;
    ++it;

    for (; it != p.terms.cend(); ++it)
    {
        os << " + " << it;
    }

    if (multi)
    {
        os << ')';
    }

    return os;
}
