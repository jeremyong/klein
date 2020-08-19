#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "glsl_shim.hpp"

#include <klein.glsl>

TEST_CASE("rr_mul")
{
    kln_rotor r1;
    r1.p1 = vec4(2, 3, 4, 5);

    kln_rotor r2;
    r2.p1 = vec4(6, 7, 8, 9);

    kln_rotor r3 = kln_mul(r1, r2);
    CHECK_EQ(r3.p1.x, -86.f);
    CHECK_EQ(r3.p1.y, 36.f);
    CHECK_EQ(r3.p1.z, 32.f);
    CHECK_EQ(r3.p1.w, 52.f);
}

TEST_CASE("mm_mul")
{
    kln_motor m1;
    m1.p1 = vec4(2, 3, 4, 5);
    m1.p2 = vec4(9, 6, 7, 8);

    kln_motor m2;
    m2.p1 = vec4(6, 7, 8, 9);
    m2.p2 = vec4(13, 10, 11, 12);

    kln_motor m3 = kln_mul(m1, m2);
    CHECK_EQ(m3.p1.x, -86.f);
    CHECK_EQ(m3.p1.y, 36.f);
    CHECK_EQ(m3.p1.z, 32.f);
    CHECK_EQ(m3.p1.w, 52.f);
    CHECK_EQ(m3.p2.x, 384.f);
    CHECK_EQ(m3.p2.y, -38.f);
    CHECK_EQ(m3.p2.z, -76.f);
    CHECK_EQ(m3.p2.w, -66.f);
}

TEST_CASE("rotor_plane")
{
    kln_rotor r;
    r.p1 = vec4(1, 4, -3, 2);
    kln_plane p1;
    p1.p0        = vec4(2, 3, 4, 5);
    kln_plane p2 = kln_apply(r, p1);
    CHECK_EQ(p2.p0.x, 60);
    CHECK_EQ(p2.p0.y, 42);
    CHECK_EQ(p2.p0.z, -144);
    CHECK_EQ(p2.p0.w, -150);
}

TEST_CASE("motor_plane")
{
    kln_motor m;
    m.p1 = vec4(1, 4, -3, 2);
    m.p2 = vec4(8, 5, 6, 7);
    kln_plane p1;
    p1.p0        = vec4(2, 3, 4, 5);
    kln_plane p2 = kln_apply(m, p1);
    CHECK_EQ(p2.p0.x, 416);
    CHECK_EQ(p2.p0.y, 42);
    CHECK_EQ(p2.p0.z, -144);
    CHECK_EQ(p2.p0.w, -150);
}

TEST_CASE("rotor_point")
{
    kln_rotor r;
    r.p1 = vec4(1, 4, -3, 2);
    kln_point p1;
    p1.p3        = vec4(2, 3, 4, 5);
    kln_point p2 = kln_apply(r, p1);
    CHECK_EQ(p2.p3.x, 60);
    CHECK_EQ(p2.p3.y, 42);
    CHECK_EQ(p2.p3.z, -144);
    CHECK_EQ(p2.p3.w, -150);
}

TEST_CASE("motor_point")
{
    kln_motor m;
    m.p1 = vec4(1, 4, -3, 2);
    m.p2 = vec4(8, 5, 6, 7);
    kln_point p1;
    p1.p3        = vec4(2, 3, 4, 5);
    kln_point p2 = kln_apply(m, p1);
    CHECK_EQ(p2.p3.x, 60);
    CHECK_EQ(p2.p3.y, -238);
    CHECK_EQ(p2.p3.z, -144);
    CHECK_EQ(p2.p3.w, -86);
}

TEST_CASE("motor_origin")
{
    kln_motor m;
    m.p1        = vec4(1, 4, -3, 2);
    m.p2        = vec4(8, 5, 6, 7);
    kln_point p = kln_apply(m);
    CHECK_EQ(p.p3.x, 1);
    CHECK_EQ(p.p3.y, -140);
    CHECK_EQ(p.p3.z, 0);
    CHECK_EQ(p.p3.w, 32);
}