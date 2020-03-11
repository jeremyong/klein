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
    // Plane x - y = 0
    plane p2{1.f, -1.f, 0.f, 0.f};
    p2.normalize();
    // Distance from point p1 to plane p2
    auto root_two = doctest::Approx(std::sqrt(2.f));
    CHECK_EQ(std::abs((p1 & p2).scalar()), root_two);
    CHECK_EQ(std::abs((p1 ^ p2).e0123()), root_two);
}

TEST_CASE("measure-point-to-line")
{
    line l{0, 1, 0, 1, 0, 0};
    point p{0, 1, 2};
    float distance = plane{l & p}.norm();
    CHECK_EQ(distance, doctest::Approx(std::sqrt(2.f)));
}