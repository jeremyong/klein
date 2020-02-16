#define _USE_MATH_DEFINES
#include <doctest/doctest.h>

#include <klein/klein.hpp>

using namespace kln;

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

TEST_CASE("rotor-point")
{
    rotor r{M_PI * 0.5f, 0, 0, 1.f};
    point p1{1, 0, 0};
    point p2 = r(p1);
    CHECK_EQ(p2.x(), 0.f);
    CHECK_EQ(p2.y(), doctest::Approx(1.f));
    CHECK_EQ(p2.z(), 0.f);
}

TEST_CASE("translator-point")
{
    translator t{1.f, 0.f, 0.f, 1.f};
    point p1{1, 0, 0};
    point p2 = t(p1);
    CHECK_EQ(p2.x(), 1.f);
    CHECK_EQ(p2.y(), 0.f);
    CHECK_EQ(p2.z(), 1.f);
}

TEST_CASE("construct-motor")
{
    rotor r{M_PI * 0.5f, 0, 0, 1.f};
    translator t{1.f, 0.f, 0.f, 1.f};
    motor m = r * t;
    point p1{1, 0, 0};
    point p2 = m(p1);
    CHECK_EQ(p2.x(), 0.f);
    CHECK_EQ(p2.y(), doctest::Approx(1.f));
    CHECK_EQ(p2.z(), doctest::Approx(1.f));
}

TEST_CASE("motor-plane")
{
    motor m{1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f};
    plane p1{3.f, 2.f, 1.f, -1.f};
    plane p2 = m(p1);
    CHECK_EQ(p2.x(), 78.f);
    CHECK_EQ(p2.y(), 60.f);
    CHECK_EQ(p2.z(), 54.f);
    CHECK_EQ(p2.d(), 358.f);
}

TEST_CASE("motor-point")
{
    motor m{1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f};
    point p1{-1.f, 1.f, 2.f};
    point p2 = m(p1);
    CHECK_EQ(p2.x(), -12.f);
    CHECK_EQ(p2.y(), -86.f);
    CHECK_EQ(p2.z(), -86.f);
    CHECK_EQ(p2.w(), 30.f);
}

TEST_CASE("motor-origin")
{
    rotor r{M_PI * 0.5f, 0, 0, 1.f};
    translator t{1.f, 0.f, 0.f, 1.f};
    motor m = r * t;
    point p = m(origin{});
    CHECK_EQ(p.x(), 0.f);
    CHECK_EQ(p.y(), 0.f);
    CHECK_EQ(p.z(), doctest::Approx(1.f));
}

TEST_CASE("motor-to-matrix")
{
    motor m{1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f};
    __m128 p1    = _mm_set_ps(1.f, 2.f, 1.f, -1.f);
    mat4x4 m_mat = m.as_matrix();
    __m128 p2    = m_mat(p1);
    float buf[4];
    _mm_storeu_ps(buf, p2);

    CHECK_EQ(buf[0], -12.f);
    CHECK_EQ(buf[1], -86.f);
    CHECK_EQ(buf[2], -86.f);
    CHECK_EQ(buf[3], 30.f);
}

TEST_CASE("normalize-motor")
{
    motor m{1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f};
    m.normalize();
    motor norm = m * ~m;
    CHECK_EQ(norm.scalar(), doctest::Approx(1.f).epsilon(0.001));
    CHECK_EQ(norm.e0123(), doctest::Approx(0.f).epsilon(0.001));
}

TEST_CASE("normalize-rotor")
{
    rotor r;
    r.p1() = _mm_set_ps(4.f, -3.f, 3.f, 28.f);
    r.normalize();
    rotor norm = r * ~r;
    CHECK_EQ(norm.scalar(), doctest::Approx(1.f).epsilon(0.001));
    CHECK_EQ(norm.e12(), doctest::Approx(0.f));
    CHECK_EQ(norm.e31(), doctest::Approx(0.f));
    CHECK_EQ(norm.e23(), doctest::Approx(0.f));
}