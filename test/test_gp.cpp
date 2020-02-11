#include <doctest/doctest.h>

#include <prstar/prstar.hpp>

using namespace prs;

TEST_CASE("multivector-gp")
{
    SUBCASE("plane*plane")
    {
        // d*e_0 + a*e_1 + b*e_2 + c*e_3
        plane p1{1.f, 2.f, 3.f, 4.f};
        plane p2{2.f, 3.f, -1.f, -2.f};
        bivector p12 = p1 * p2;
        CHECK_EQ(p12[0], 5.f);
        CHECK_EQ(p12[1], -1.f);
        CHECK_EQ(p12[2], 7.f);
        CHECK_EQ(p12[3], -11.f);
        CHECK_EQ(p12[4], 0.f);
        CHECK_EQ(p12[5], 10.f);
        CHECK_EQ(p12[6], 16.f);
        CHECK_EQ(p12[7], 2.f);
    }

    SUBCASE("plane*line")
    {
        // d*e_0 + a*e_1 + b*e_2 + c*e_3
        plane p1{1.f, 2.f, 3.f, 4.f};

        // d*e12 + e*e31 + f*e23
        line l1{-2.f, 1.f, 4.f};

        // Creates a vector/trivector union
        entity<0b1001> p1l1 = p1 * l1;
        CHECK_EQ(p1l1.e1(), 7.f);
        CHECK_EQ(p1l1.e2(), -14.f);
        CHECK_EQ(p1l1.e3(), 7.f);
        CHECK_EQ(p1l1.e0(), 0.f);
        CHECK_EQ(p1l1.e021(), 8.f);
        CHECK_EQ(p1l1.e013(), -4.f);
        CHECK_EQ(p1l1.e032(), -16.f);
        CHECK_EQ(p1l1.e123(), 0.f);
    }

    SUBCASE("plane*ideal-line")
    {
        // d*e_0 + a*e_1 + b*e_2 + c*e_3
        plane p1{1.f, 2.f, 3.f, 4.f};

        // a*e01 + b*e02 + c*e03
        ideal_line l1{-2.f, 1.f, 4.f};

        // Creates a vector/trivector union
        entity<0b1001> p1l1 = p1 * l1;
        CHECK_EQ(p1l1.e1(), 0.f);
        CHECK_EQ(p1l1.e2(), 0.f);
        CHECK_EQ(p1l1.e3(), 0.f);
        CHECK_EQ(p1l1.e0(), -12.f);
        CHECK_EQ(p1l1.e021(), 5.f);
        CHECK_EQ(p1l1.e013(), -10.f);
        CHECK_EQ(p1l1.e032(), 5.f);
        CHECK_EQ(p1l1.e123(), 0.f);
    }

    SUBCASE("plane*point")
    {
        // d*e_0 + a*e_1 + b*e_2 + c*e_3
        plane p1{1.f, 2.f, 3.f, 4.f};
        // x*e_032 + y*e_013 + z*e_021 + e_123
        point p2{-2.f, 1.f, 4.f};

        entity<0b110> p1p2 = p1 * p2;
        CHECK_EQ(p1p2.scalar(), 0.f);
        CHECK_EQ(p1p2.e01(), -5.f);
        CHECK_EQ(p1p2.e02(), 10.f);
        CHECK_EQ(p1p2.e03(), -5.f);
        CHECK_EQ(p1p2.e12(), 3.f);
        CHECK_EQ(p1p2.e31(), 2.f);
        CHECK_EQ(p1p2.e23(), 1.f);
        CHECK_EQ(p1p2.e0123(), 16.f);
    }

    SUBCASE("line*plane")
    {
        // d*e_0 + a*e_1 + b*e_2 + c*e_3
        plane p1{1.f, 2.f, 3.f, 4.f};

        // d*e12 + e*e31 + f*e23
        line l1{-2.f, 1.f, 4.f};

        // Creates a vector/trivector union
        entity<0b1001> p1l1 = l1 * p1;
        CHECK_EQ(p1l1.e1(), -7.f);
        CHECK_EQ(p1l1.e2(), 14.f);
        CHECK_EQ(p1l1.e3(), -7.f);
        CHECK_EQ(p1l1.e0(), 0.f);
        CHECK_EQ(p1l1.e021(), 8.f);
        CHECK_EQ(p1l1.e013(), -4.f);
        CHECK_EQ(p1l1.e032(), -16.f);
        CHECK_EQ(p1l1.e123(), 0.f);
    }

    SUBCASE("line*line")
    {
        // d*e12 + e*e31 + f*e23
        line l1{1.f, 2.f, 3.f};
        line l2{-2.f, 1.f, 4.f};

        entity<0b10> l1l2 = l1 * l2;
        CHECK_EQ(l1l2.scalar(), -12.f);
        CHECK_EQ(l1l2.e12(), 5.f);
        CHECK_EQ(l1l2.e31(), -10.f);
        CHECK_EQ(l1l2.e23(), 5.f);
    }

    SUBCASE("line*ideal-line")
    {
        // d*e12 + e*e31 + f*e23
        line l1{1.f, 2.f, 3.f};
        // a*e01 + b*e02 + c*e03
        ideal_line l2{-2.f, 1.f, 4.f};

        entity<0b100> l1l2 = l1 * l2;
        CHECK_EQ(l1l2.e0123(), 0.f);
        CHECK_EQ(l1l2.e01(), -7.f);
        CHECK_EQ(l1l2.e02(), 14.f);
        CHECK_EQ(l1l2.e03(), -7.f);
    }

    SUBCASE("line*point")
    {
        // d*e12 + e*e31 + f*e23
        line l1{1.f, 2.f, 3.f};
        // x*e_032 + y*e_013 + z*e_021 + e_123
        point p2{-2.f, 1.f, 4.f};

        entity<0b1001> l1p2 = l1 * p2;
        CHECK_EQ(l1p2.e1(), -3.f);
        CHECK_EQ(l1p2.e2(), -2.f);
        CHECK_EQ(l1p2.e3(), -1.f);
        CHECK_EQ(l1p2.e0(), 0.f);
        CHECK_EQ(l1p2.e021(), -7.f);
        CHECK_EQ(l1p2.e013(), 14.f);
        CHECK_EQ(l1p2.e032(), -7.f);
        CHECK_EQ(l1p2.e123(), 0.f);
    }

    SUBCASE("ideal-line*plane")
    {
        // d*e_0 + a*e_1 + b*e_2 + c*e_3
        plane p1{1.f, 2.f, 3.f, 4.f};

        // a*e01 + b*e02 + c*e03
        ideal_line l1{-2.f, 1.f, 4.f};

        // Creates a vector/trivector union
        entity<0b1001> p1l1 = l1 * p1;
        CHECK_EQ(p1l1.e1(), 0.f);
        CHECK_EQ(p1l1.e2(), 0.f);
        CHECK_EQ(p1l1.e3(), 0.f);
        CHECK_EQ(p1l1.e0(), 12.f);
        CHECK_EQ(p1l1.e021(), 5.f);
        CHECK_EQ(p1l1.e013(), -10.f);
        CHECK_EQ(p1l1.e032(), 5.f);
        CHECK_EQ(p1l1.e123(), 0.f);
    }

    SUBCASE("ideal-line*line")
    {
        // d*e12 + e*e31 + f*e23
        line l1{1.f, 2.f, 3.f};
        // a*e01 + b*e02 + c*e03
        ideal_line l2{-2.f, 1.f, 4.f};

        entity<0b100> l1l2 = l2 * l1;
        CHECK_EQ(l1l2.e0123(), 0.f);
        CHECK_EQ(l1l2.e01(), 7.f);
        CHECK_EQ(l1l2.e02(), -14.f);
        CHECK_EQ(l1l2.e03(), 7.f);
    }

    SUBCASE("ideal-line*ideal-line")
    {
        // a*e01 + b*e02 + c*e03
        ideal_line l1{1.f, 2.f, 3.f};
        // a*e01 + b*e02 + c*e03
        ideal_line l2{-2.f, 1.f, 4.f};

        // Compiled out to exactly 0
        entity<0b0> l1l2 = l2 * l1;
    }

    SUBCASE("ideal-line*point")
    {
        // a*e01 + b*e02 + c*e03
        ideal_line l1{1.f, 2.f, 3.f};
        // x*e_032 + y*e_013 + z*e_021 + e_123
        point p2{-2.f, 1.f, 4.f};

        entity<0b1000> l1p2 = l1 * p2;
        CHECK_EQ(l1p2.e123(), 0.f);
        CHECK_EQ(l1p2.e021(), -3.f);
        CHECK_EQ(l1p2.e013(), -2.f);
        CHECK_EQ(l1p2.e032(), -1.f);
    }

    SUBCASE("point*plane")
    {
        // x*e_032 + y*e_013 + z*e_021 + e_123
        point p1{-2.f, 1.f, 4.f};
        // d*e_0 + a*e_1 + b*e_2 + c*e_3
        plane p2{1.f, 2.f, 3.f, 4.f};

        entity<0b110> p1p2 = p1 * p2;
        CHECK_EQ(p1p2.scalar(), 0.f);
        CHECK_EQ(p1p2.e01(), -5.f);
        CHECK_EQ(p1p2.e02(), 10.f);
        CHECK_EQ(p1p2.e03(), -5.f);
        CHECK_EQ(p1p2.e12(), 3.f);
        CHECK_EQ(p1p2.e31(), 2.f);
        CHECK_EQ(p1p2.e23(), 1.f);
        CHECK_EQ(p1p2.e0123(), -16.f);
    }

    SUBCASE("point*line")
    {
        // d*e12 + e*e31 + f*e23
        line l1{1.f, 2.f, 3.f};
        // x*e_032 + y*e_013 + z*e_021 + e_123
        point p2{-2.f, 1.f, 4.f};

        entity<0b1001> l1p2 = p2 * l1;
        CHECK_EQ(l1p2.e1(), -3.f);
        CHECK_EQ(l1p2.e2(), -2.f);
        CHECK_EQ(l1p2.e3(), -1.f);
        CHECK_EQ(l1p2.e0(), 0.f);
        CHECK_EQ(l1p2.e021(), 7.f);
        CHECK_EQ(l1p2.e013(), -14.f);
        CHECK_EQ(l1p2.e032(), 7.f);
        CHECK_EQ(l1p2.e123(), 0.f);
    }

    SUBCASE("point*ideal-line")
    {
        // a*e01 + b*e02 + c*e03
        ideal_line l1{1.f, 2.f, 3.f};
        // x*e_032 + y*e_013 + z*e_021 + e_123
        point p2{-2.f, 1.f, 4.f};

        entity<0b1000> l1p2 = p2 * l1;
        CHECK_EQ(l1p2.e123(), 0.f);
        CHECK_EQ(l1p2.e021(), 3.f);
        CHECK_EQ(l1p2.e013(), 2.f);
        CHECK_EQ(l1p2.e032(), 1.f);
    }

    SUBCASE("point*point")
    {
        // x*e_032 + y*e_013 + z*e_021 + e_123
        point p1{1.f, 2.f, 3.f};
        point p2{-2.f, 1.f, 4.f};

        entity<0b110> p1p2 = p1 * p2;
        CHECK_EQ(p1p2.scalar(), -1.f);
        CHECK_EQ(p1p2.e12(), 0.f);
        CHECK_EQ(p1p2.e31(), 0.f);
        CHECK_EQ(p1p2.e23(), 0.f);
        CHECK_EQ(p1p2.e0123(), 0.f);
        CHECK_EQ(p1p2.e01(), 3.f);
        CHECK_EQ(p1p2.e02(), 1.f);
        CHECK_EQ(p1p2.e03(), -1.f);
    }
}

TEST_CASE("simd-sandwich")
{
    __m128 a = _mm_set_ps(4.f, 3.f, 2.f, 1.f);
    __m128 b = _mm_set_ps(-1.f, -2.f, -3.f, -4.f);
    float ab[4];
    _mm_store_ps(ab, detail::sw02(a, b));

    CHECK_EQ(ab[0], 1.f);
    CHECK_EQ(ab[1], 2.f);
    CHECK_EQ(ab[2], 3.f);
    CHECK_EQ(ab[3], -24.f);
}