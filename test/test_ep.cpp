#include <doctest/doctest.h>

#include <klein/klein.hpp>

using namespace kln;

TEST_CASE("multivector-ep")
{
    SUBCASE("plane^plane")
    {
        // d*e_0 + a*e_1 + b*e_2 + c*e_3
        plane p1{1.f, 2.f, 3.f, 4.f};
        plane p2{2.f, 3.f, -1.f, -2.f};
        line p12 = p1 ^ p2;
        CHECK_EQ(p12.e01(), 10.f);
        CHECK_EQ(p12.e02(), 16.f);
        CHECK_EQ(p12.e03(), 2.f);
        CHECK_EQ(p12.e12(), -1.f);
        CHECK_EQ(p12.e31(), 7.f);
        CHECK_EQ(p12.e23(), -11.f);
    }

    SUBCASE("plane^line")
    {
        // d*e_0 + a*e_1 + b*e_2 + c*e_3
        plane p1{1.f, 2.f, 3.f, 4.f};

        // a*e01 + b*e02 + c*e03 + d*e23 + e*e31 + f*e12
        line l1{0.f, 0.f, 1.f, 4.f, 1.f, -2.f};

        point p1l1 = p1 ^ l1;
        CHECK_EQ(p1l1.e021(), 8.f);
        CHECK_EQ(p1l1.e013(), -5.f);
        CHECK_EQ(p1l1.e032(), -14.f);
        CHECK_EQ(p1l1.e123(), 0.f);
    }

    SUBCASE("plane^ideal-line")
    {
        // d*e_0 + a*e_1 + b*e_2 + c*e_3
        plane p1{1.f, 2.f, 3.f, 4.f};

        // a*e01 + b*e02 + c*e03
        ideal_line l1{-2.f, 1.f, 4.f};

        point p1l1 = p1 ^ l1;
        CHECK_EQ(p1l1.e021(), 5.f);
        CHECK_EQ(p1l1.e013(), -10.f);
        CHECK_EQ(p1l1.e032(), 5.f);
        CHECK_EQ(p1l1.e123(), 0.f);
    }

    SUBCASE("plane^point")
    {
        // d*e_0 + a*e_1 + b*e_2 + c*e_3
        plane p1{1.f, 2.f, 3.f, 4.f};
        // x*e_032 + y*e_013 + z*e_021 + e_123
        point p2{-2.f, 1.f, 4.f};

        dual p1p2 = p1 ^ p2;
        CHECK_EQ(p1p2.scalar(), 0.f);
        CHECK_EQ(p1p2.e0123(), 16.f);
    }

    SUBCASE("line^plane")
    {
        // d*e_0 + a*e_1 + b*e_2 + c*e_3
        plane p1{1.f, 2.f, 3.f, 4.f};

        // a*e01 + b*e01 + c*e02 + d*e23 + e*e31 + f*e12
        line l1{0.f, 0.f, 1.f, 4.f, 1.f, -2.f};

        point p1l1 = l1 ^ p1;
        CHECK_EQ(p1l1.e021(), 8.f);
        CHECK_EQ(p1l1.e013(), -5.f);
        CHECK_EQ(p1l1.e032(), -14.f);
        CHECK_EQ(p1l1.e123(), 0.f);
    }

    SUBCASE("line^line")
    {
        // a*e01 + b*e01 + c*e02 + d*e23 + e*e31 + f*e12
        line l1{1.f, 0.f, 0.f, 3.f, 2.f, 1.f};
        line l2{0.f, 1.f, 0.f, 4.f, 1.f, -2.f};

        dual l1l2 = l1 ^ l2;
        CHECK_EQ(l1l2.e0123(), 6.f);
    }

    SUBCASE("line^ideal-line")
    {
        // a*e01 + b*e01 + c*e02 + d*e23 + e*e31 + f*e12
        line l1{0.f, 0.f, 1.f, 3.f, 2.f, 1.f};
        // a*e01 + b*e02 + c*e03
        ideal_line l2{-2.f, 1.f, 4.f};

        dual l1l2 = l1 ^ l2;
        CHECK_EQ(l1l2.e0123(), 0.f);
        CHECK_EQ(l1l2.scalar(), 0.f);
    }

    SUBCASE("ideal-line^plane")
    {
        // d*e_0 + a*e_1 + b*e_2 + c*e_3
        plane p1{1.f, 2.f, 3.f, 4.f};

        // a*e01 + b*e02 + c*e03
        ideal_line l1{-2.f, 1.f, 4.f};

        point p1l1 = l1 ^ p1;
        CHECK_EQ(p1l1.e021(), 5.f);
        CHECK_EQ(p1l1.e013(), -10.f);
        CHECK_EQ(p1l1.e032(), 5.f);
        CHECK_EQ(p1l1.e123(), 0.f);
    }

    SUBCASE("point^plane")
    {
        // x*e_032 + y*e_013 + z*e_021 + e_123
        point p1{-2.f, 1.f, 4.f};
        // d*e_0 + a*e_1 + b*e_2 + c*e_3
        plane p2{1.f, 2.f, 3.f, 4.f};

        dual p1p2 = p1 ^ p2;
        CHECK_EQ(p1p2.e0123(), -16.f);
    }
}