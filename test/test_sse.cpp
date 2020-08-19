#include <doctest/doctest.h>

#include <klein/klein.hpp>

using namespace kln;

TEST_CASE("rcp_nr1")
{
    __m128 a = _mm_set_ps(4.f, 3.f, 2.f, 1.f);

    __m128 b = detail::rcp_nr1(a);
    float buf[4];
    _mm_store_ps(buf, b);

    CHECK_EQ(buf[0], doctest::Approx(1.f));
    CHECK_EQ(buf[1], doctest::Approx(0.5f));
    CHECK_EQ(buf[2], doctest::Approx(1.f / 3.f));
    CHECK_EQ(buf[3], doctest::Approx(0.25f));
}