#include <doctest/doctest.h>

#include <klein/klein.hpp>

using namespace kln;

TEST_CASE("multivector-gp")
{
    SUBCASE("plane*plane")
    {
        // d*e_0 + a*e_1 + b*e_2 + c*e_3
        plane p1{1.f, 2.f, 3.f, 4.f};
        plane p2{2.f, 3.f, -1.f, -2.f};
        motor p12 = p1 * p2;
        CHECK_EQ(p12.scalar(), 5.f);
        CHECK_EQ(p12.e12(), -1.f);
        CHECK_EQ(p12.e31(), 7.f);
        CHECK_EQ(p12.e23(), -11.f);
        CHECK_EQ(p12.e01(), 10.f);
        CHECK_EQ(p12.e02(), 16.f);
        CHECK_EQ(p12.e03(), 2.f);
        CHECK_EQ(p12.e0123(), 0.f);

        plane p3 = sqrt(p1 / p2)(p2);
        CHECK_EQ(p3.approx_eq(p1, 0.001f), true);

        p1.normalize();
        motor m = p1 * p1;
        CHECK_EQ(m.scalar(), doctest::Approx(1.f));
    }

    SUBCASE("plane/plane")
    {
        plane p1{1.f, 2.f, 3.f, 4.f};
        motor m = p1 / p1;
        CHECK_EQ(m.scalar(), doctest::Approx(1.f));
        CHECK_EQ(m.e12(), 0.f);
        CHECK_EQ(m.e31(), 0.f);
        CHECK_EQ(m.e23(), 0.f);
        CHECK_EQ(m.e01(), 0.f);
        CHECK_EQ(m.e02(), 0.f);
        CHECK_EQ(m.e03(), 0.f);
        CHECK_EQ(m.e0123(), 0.f);
    }

    SUBCASE("plane*point")
    {
        // d*e_0 + a*e_1 + b*e_2 + c*e_3
        plane p1{1.f, 2.f, 3.f, 4.f};
        // x*e_032 + y*e_013 + z*e_021 + e_123
        point p2{-2.f, 1.f, 4.f};

        motor p1p2 = p1 * p2;
        CHECK_EQ(p1p2.scalar(), 0.f);
        CHECK_EQ(p1p2.e01(), -5.f);
        CHECK_EQ(p1p2.e02(), 10.f);
        CHECK_EQ(p1p2.e03(), -5.f);
        CHECK_EQ(p1p2.e12(), 3.f);
        CHECK_EQ(p1p2.e31(), 2.f);
        CHECK_EQ(p1p2.e23(), 1.f);
        CHECK_EQ(p1p2.e0123(), 16.f);
    }

    SUBCASE("line-normalization")
    {
        line l{1.f, 2.f, 3.f, 3.f, 2.f, 1.f};
        l.normalize();
        motor m = l * ~l;
        CHECK_EQ(m.scalar(), doctest::Approx(1.f));
        CHECK_EQ(m.e23(), doctest::Approx(0.f));
        CHECK_EQ(m.e31(), doctest::Approx(0.f));
        CHECK_EQ(m.e12(), doctest::Approx(0.f));
        CHECK_EQ(m.e01(), doctest::Approx(0.f));
        CHECK_EQ(m.e02(), doctest::Approx(0.f));
        CHECK_EQ(m.e03(), doctest::Approx(0.f));
        CHECK_EQ(m.e0123(), doctest::Approx(0.f));
    }

    SUBCASE("branch*branch")
    {
        branch b1{2.f, 1.f, 3.f};
        branch b2{1.f, -2.f, -3.f};
        rotor r = b2 * b1;
        CHECK_EQ(r.scalar(), 9.f);
        CHECK_EQ(r.e23(), 3.f);
        CHECK_EQ(r.e31(), 9.f);
        CHECK_EQ(r.e12(), -5.f);

        b1.normalize();
        b2.normalize();
        branch b3 = ~sqrt(b2 * b1)(b1);
        CHECK_EQ(b3.x(), doctest::Approx(b2.x()));
        CHECK_EQ(b3.y(), doctest::Approx(b2.y()));
        CHECK_EQ(b3.z(), doctest::Approx(b2.z()));
    }

    SUBCASE("branch/branch")
    {
        branch b{2.f, 1.f, 3.f};
        rotor r = b / b;
        CHECK_EQ(r.scalar(), doctest::Approx(1.f));
        CHECK_EQ(r.e23(), 0.f);
        CHECK_EQ(r.e31(), 0.f);
        CHECK_EQ(r.e12(), 0.f);
    }

    SUBCASE("line*line")
    {
        // a*e01 + b*e02 + c*e03 + d*e23 + e*e31 + f*e12
        line l1{1.f, 0.f, 0.f, 3.f, 2.f, 1.f};
        line l2{0.f, 1.f, 0.f, 4.f, 1.f, -2.f};

        motor l1l2 = l1 * l2;
        CHECK_EQ(l1l2.scalar(), -12.f);
        CHECK_EQ(l1l2.e12(), 5.f);
        CHECK_EQ(l1l2.e31(), -10.f);
        CHECK_EQ(l1l2.e23(), 5.f);
        CHECK_EQ(l1l2.e01(), 1.f);
        CHECK_EQ(l1l2.e02(), -2.f);
        CHECK_EQ(l1l2.e03(), -4.f);
        CHECK_EQ(l1l2.e0123(), 6.f);

        l1.normalize();
        l2.normalize();
        line l3 = sqrt(l1 * l2)(l2);
        CHECK_EQ(l3.approx_eq(-l1, 0.001f), true);
    }

    SUBCASE("line/line")
    {
        line l{1.f, -2.f, 2.f, -3.f, 3.f, -4.f};
        motor m = l / l;
        CHECK_EQ(m.scalar(), doctest::Approx(1.f));
        CHECK_EQ(m.e12(), 0.f);
        CHECK_EQ(m.e31(), 0.f);
        CHECK_EQ(m.e23(), 0.f);
        CHECK_EQ(m.e01(), doctest::Approx(0.f));
        CHECK_EQ(m.e02(), doctest::Approx(0.f));
        CHECK_EQ(m.e03(), doctest::Approx(0.f));
        CHECK_EQ(m.e0123(), doctest::Approx(0.f));
    }

    SUBCASE("point*plane")
    {
        // x*e_032 + y*e_013 + z*e_021 + e_123
        point p1{-2.f, 1.f, 4.f};
        // d*e_0 + a*e_1 + b*e_2 + c*e_3
        plane p2{1.f, 2.f, 3.f, 4.f};

        motor p1p2 = p1 * p2;
        CHECK_EQ(p1p2.scalar(), 0.f);
        CHECK_EQ(p1p2.e01(), -5.f);
        CHECK_EQ(p1p2.e02(), 10.f);
        CHECK_EQ(p1p2.e03(), -5.f);
        CHECK_EQ(p1p2.e12(), 3.f);
        CHECK_EQ(p1p2.e31(), 2.f);
        CHECK_EQ(p1p2.e23(), 1.f);
        CHECK_EQ(p1p2.e0123(), -16.f);
    }

    SUBCASE("point*point")
    {
        // x*e_032 + y*e_013 + z*e_021 + e_123
        point p1{1.f, 2.f, 3.f};
        point p2{-2.f, 1.f, 4.f};

        translator p1p2 = p1 * p2;
        CHECK_EQ(p1p2.e01(), doctest::Approx(-3.f));
        CHECK_EQ(p1p2.e02(), doctest::Approx(-1.f));
        CHECK_EQ(p1p2.e03(), doctest::Approx(1.f));

        point p3 = sqrt(p1p2)(p2);
        CHECK_EQ(p3.x(), doctest::Approx(1.f));
        CHECK_EQ(p3.y(), doctest::Approx(2.f));
        CHECK_EQ(p3.z(), doctest::Approx(3.f));
    }

    SUBCASE("point/point")
    {
        point p1{1.f, 2.f, 3.f};
        translator t = p1 / p1;
        CHECK_EQ(t.e01(), 0.f);
        CHECK_EQ(t.e02(), 0.f);
        CHECK_EQ(t.e03(), 0.f);
    }

    SUBCASE("translator/translator")
    {
        translator t1{3.f, 1.f, -2.f, 3.f};
        translator t2 = t1 / t1;
        CHECK_EQ(t2.e01(), 0.f);
        CHECK_EQ(t2.e02(), 0.f);
        CHECK_EQ(t2.e03(), 0.f);
    }

    SUBCASE("rotor*translator")
    {
        rotor r;
        r.p1_ = _mm_set_ps(1.f, 0, 0, 1.f);
        translator t;
        t.p2_   = _mm_set_ps(1.f, 0, 0, 0.f);
        motor m = r * t;
        CHECK_EQ(m.scalar(), 1.f);
        CHECK_EQ(m.e01(), 0.f);
        CHECK_EQ(m.e02(), 0.f);
        CHECK_EQ(m.e03(), 1.f);
        CHECK_EQ(m.e23(), 0.f);
        CHECK_EQ(m.e31(), 0.f);
        CHECK_EQ(m.e12(), 1.f);
        CHECK_EQ(m.e0123(), 1.f);
    }

    SUBCASE("translator*rotor")
    {
        rotor r;
        r.p1_ = _mm_set_ps(1.f, 0, 0, 1.f);
        translator t;
        t.p2_   = _mm_set_ps(1.f, 0, 0, 0.f);
        motor m = t * r;
        CHECK_EQ(m.scalar(), 1.f);
        CHECK_EQ(m.e01(), 0.f);
        CHECK_EQ(m.e02(), 0.f);
        CHECK_EQ(m.e03(), 1.f);
        CHECK_EQ(m.e23(), 0.f);
        CHECK_EQ(m.e31(), 0.f);
        CHECK_EQ(m.e12(), 1.f);
        CHECK_EQ(m.e0123(), 1.f);
    }

    SUBCASE("motor*rotor")
    {
        rotor r1;
        r1.p1_ = _mm_set_ps(1.f, 2.f, 3.f, 4.f);
        translator t;
        t.p2_ = _mm_set_ps(3.f, -2.f, 1.f, -3.f);
        rotor r2;
        r2.p1_   = _mm_set_ps(-4.f, 2.f, -3.f, 1.f);
        motor m1 = (t * r1) * r2;
        motor m2 = t * (r1 * r2);
        CHECK_EQ(m1, m2);
    }

    SUBCASE("rotor*motor")
    {
        rotor r1;
        r1.p1_ = _mm_set_ps(1.f, 2.f, 3.f, 4.f);
        translator t;
        t.p2_ = _mm_set_ps(3.f, -2.f, 1.f, -3.f);
        rotor r2;
        r2.p1_   = _mm_set_ps(-4.f, 2.f, -3.f, 1.f);
        motor m1 = r2 * (r1 * t);
        motor m2 = (r2 * r1) * t;
        CHECK_EQ(m1, m2);
    }

    SUBCASE("motor*translator")
    {
        rotor r;
        r.p1_ = _mm_set_ps(1.f, 2.f, 3.f, 4.f);
        translator t1;
        t1.p2_ = _mm_set_ps(3.f, -2.f, 1.f, -3.f);
        translator t2;
        t2.p2_   = _mm_set_ps(-4.f, 2.f, -3.f, 1.f);
        motor m1 = (r * t1) * t2;
        motor m2 = r * (t1 * t2);
        CHECK_EQ(m1, m2);
    }

    SUBCASE("translator*motor")
    {
        rotor r;
        r.p1_ = _mm_set_ps(1.f, 2.f, 3.f, 4.f);
        translator t1;
        t1.p2_ = _mm_set_ps(3.f, -2.f, 1.f, -3.f);
        translator t2;
        t2.p2_   = _mm_set_ps(-4.f, 2.f, -3.f, 1.f);
        motor m1 = t2 * (r * t1);
        motor m2 = (t2 * r) * t1;
        CHECK_EQ(m1, m2);
    }

    SUBCASE("motor*motor")
    {
        motor m1{2, 3, 4, 5, 6, 7, 8, 9};
        motor m2{6, 7, 8, 9, 10, 11, 12, 13};
        motor m3 = m1 * m2;
        CHECK_EQ(m3.scalar(), -86.f);
        CHECK_EQ(m3.e23(), 36.f);
        CHECK_EQ(m3.e31(), 32.f);
        CHECK_EQ(m3.e12(), 52.f);
        CHECK_EQ(m3.e01(), -38.f);
        CHECK_EQ(m3.e02(), -76.f);
        CHECK_EQ(m3.e03(), -66.f);
        CHECK_EQ(m3.e0123(), 384.f);
    }

    SUBCASE("motor/motor")
    {
        motor m1{2, 3, 4, 5, 6, 7, 8, 9};
        motor m2 = m1 / m1;
        CHECK_EQ(m2.scalar(), doctest::Approx(1.f));
        CHECK_EQ(m2.e23(), 0.f);
        CHECK_EQ(m2.e31(), 0.f);
        CHECK_EQ(m2.e12(), 0.f);
        CHECK_EQ(m2.e01(), 0.f);
        CHECK_EQ(m2.e02(), doctest::Approx(0.f));
        CHECK_EQ(m2.e03(), doctest::Approx(0.f));
        CHECK_EQ(m2.e0123(), doctest::Approx(0.f));
    }
}