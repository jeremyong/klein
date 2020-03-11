#include <doctest/doctest.h>

#include <klein/klein.hpp>

TEST_CASE("log2")
{
    int x = 12;
    CHECK_EQ(kln::log2(8), 3);
    CHECK_EQ(kln::log2(9), 3);
    CHECK_EQ(kln::log2(x), 3);
    uint64_t y = 1ull << 34;
    CHECK_EQ(kln::log2(y), 34);
    CHECK_EQ(kln::log2((1ull << 34) | (1 << 12)), 34);
}