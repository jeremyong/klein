#pragma once

#include <iostream>
#include <map>

class mon
{
public:
    // Map from variable to degree
    // A map is used here so that traversal order is deterministic
    std::map<std::string, int> factors;

    mon& operator*=(mon const& other) noexcept;

    // Multiply the monomial by a named variable with degree
    mon& push(std::string var, int deg = 1) noexcept;

    int degree() const noexcept;
};

mon operator*(mon const& lhs, mon const& rhs) noexcept;

namespace std
{
template <>
struct hash<mon>
{
    size_t operator()(mon const& in) const noexcept
    {
        size_t out = 0;
        size_t k;
        if constexpr (sizeof(void*) == 8)
        {
            k = 0x517cc1b727220a95;
        }
        else
        {
            k = 0x9e3779b9;
        }

        for (auto&& [var, deg] : in.factors)
        {
            out ^= std::hash<std::string>{}(var) + k + (out >> 2) + (out << 6);
            out ^= std::hash<int>{}(deg) + k + (out >> 2) + (out << 6);
        }
        return out;
    }
};
} // namespace std

bool operator==(mon const& lhs, mon const& rhs) noexcept;
bool operator<(mon const& lhs, mon const& rhs) noexcept;

class poly
{
public:
    // Map from monomial to scalar coefficient
    std::map<mon, float> terms;

    poly& push(mon const& m, float f = 1.f) noexcept;
    poly& operator+=(poly const& other) noexcept;
    poly& operator*=(poly const& other) noexcept;
    poly operator-() const& noexcept;
    poly& operator-() && noexcept;
};

poly operator+(poly const& lhs, poly const& rhs) noexcept;
poly operator*(poly const& lhs, poly const& rhs) noexcept;
std::ostream& operator<<(std::ostream& os, poly const& p) noexcept;