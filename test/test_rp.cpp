#include <doctest/doctest.h>

#include <klein/klein.hpp>

using namespace kln;

TEST_CASE("multivector-rp")
{
    SUBCASE("+z line")
    {
        point p1{0.f, 0.f, 0.f};
        point p2{0.f, 0.f, 1.f};
        line p12 = p1 & p2;
        CHECK_EQ(p12.e12(), 1.f);
    }

    SUBCASE("+y line")
    {
        point p1{0.f, -1.f, 0.f};
        point p2{0.f, 0.f, 0.f};
        line p12 = p1 & p2;
        CHECK_EQ(p12.e31(), 1.f);
    }

    SUBCASE("+x line")
    {
        point p1{-2.f, 0.f, 0.f};
        point p2{-1.f, 0.f, 0.f};
        line p12 = p1 & p2;
        CHECK_EQ(p12.e23(), 1.f);
    }

    SUBCASE("plane-construction")
    {
        point p1{1.f, 3.f, 2.f};
        point p2{-1.f, 5.f, 2.f};
        point p3{2.f, -1.f, -4.f};

        plane p123{p1 & p2 & p3};

        // Check that all 3 points lie on the plane
        CHECK_EQ(p123.e1() + p123.e2() * 3.f + p123.e3() * 2.f + p123.e0(), 0.f);
        CHECK_EQ(-p123.e1() + p123.e2() * 5.f + p123.e3() * 2.f + p123.e0(), 0.f);
        CHECK_EQ(p123.e1() * 2.f - p123.e2() - p123.e3() * 4.f + p123.e0(), 0.f);
    }
}