#define _USE_MATH_DEFINES
#include <doctest/doctest.h>

#include <klein/klein.hpp>

using namespace kln;

TEST_CASE("measure-point-to-point")
{
    point p1{1.f, 0, 0};
    point p2{0.f, 1.f, 0};
    line l = p1 & p2;
    // Produce the squared distance between p1 and p2
    CHECK_EQ(l.squared_norm(), 2.f);
}

TEST_CASE("measure-point-to-plane")
{
    //    Plane p2
    //    /
    //   / \ line perpendicular to
    //  /   \ p2 through p1
    // 0------x--------->
    //        p1

    // (2, 0, 0)
    point p1{2.f, 0.f, 0.f};
    // Plane x + y = 0
    plane p2{1.f, -1.f, 0.f, 0.f};
    // Line through (2, 0, 0) perpendicular to the plane
    line l = p1 | p2;
    // Distance from point p1 to plane p2
    CHECK_EQ(l.squared_norm(), 2.f);
}