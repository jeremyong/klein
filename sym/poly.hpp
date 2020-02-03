#pragma once

#include <unordered_map>

struct mon
{
    char const* name;
};

struct poly
{
    std::unordered_map<mon, int> terms;
};