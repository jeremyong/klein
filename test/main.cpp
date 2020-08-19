#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <klein/klein.hpp>

// Cheat sheet
// TEST_SUITE_BEGIN defines the start of a scope of tests grouped under a suite
// TEST_SUITE_END ends the test suite scope
// TEST_CASE defines a test case and takes a string name
//   After the test name, the * operator can be used to add decorators
//     - skip(bool = true)
//     - may_fail(bool = true)
//     - should_fail(bool = true)
//     - expected_failures(int)
//     - timeout(double)
//     - description("text")
// TEST_CASE_TEMPLATE takes a comma separated list of types after the test name
// and type parameter name SUBCASE defines a sub-test case within the scope of a
// test case

// CHECK checks a condition
// REQUIRE checks a condition and stops the test if the condition fails
// REQUIRE_FALSE ensures that a condition fails
// For most asserts though, use
// [REQUIRE|CHECK|WARN]_[EQ|NE|GT|LT|GE|LE|UNARY|UNARY_FALSE] as these compile
// faster.

// For floating point comparison, there is the handy helper `doctest::Approx(2,
// 1)` which when compared to another float, checks the comparison to within a
// percentage-based tolerance. You can specify the tolerance using
// `doctest::Approx::epsilon(float percentage)`.

// Command-line
// -ltc list-test-cases
// -lts list-test-suites
// -tc <filters> (comma separated test cases)
// -tce negated -tc
// -ts <filters> (comma separated test suites)
// -tse negated -ts
// -rs <seed> randomizes test order
// -d time each test and print duration

using namespace kln;

TEST_CASE("multivector-sum")
{
    SUBCASE("points")
    {
        point p1{1.f, 2.f, 3.f};
        point p2{2.f, 3.f, -1.f};
        point p3 = p1 + p2;
        CHECK_EQ(p3.x(), 1.f + 2.f);
        CHECK_EQ(p3.y(), 2.f + 3.f);
        CHECK_EQ(p3.z(), 3.f + -1.f);

        point p4 = p1 - p2;
        CHECK_EQ(p4.x(), 1.f - 2.f);
        CHECK_EQ(p4.y(), 2.f - 3.f);
        CHECK_EQ(p4.z(), 3.f - -1.f);

        // Adding rvalue to lvalue
        point p5 = point{1.f, 2.f, 3.f} + p2;
        CHECK_EQ(p5.x(), 1.f + 2.f);
        CHECK_EQ(p5.y(), 2.f + 3.f);
        CHECK_EQ(p5.z(), 3.f + -1.f);

        // Adding rvalue to rvalue
        point p6 = point{1.f, 2.f, 3.f} + point{2.f, 3.f, -1.f};
        CHECK_EQ(p6.x(), 1.f + 2.f);
        CHECK_EQ(p6.y(), 2.f + 3.f);
        CHECK_EQ(p6.z(), 3.f + -1.f);
    }

    SUBCASE("planes")
    {
        plane p{1.f, 3.f, 4.f, -5.f};
        float p_norm = p | p;
        CHECK_NE(p_norm, 1.f);
        p.normalize();
        p_norm = p | p;
        CHECK_EQ(p_norm, doctest::Approx(1.f));
    }
}

TEST_CASE("rotor-constrain")
{
    rotor r1{1, 2, 3, 4};
    rotor r2 = r1.constrained();
    CHECK_EQ(r1, r2);

    r1 = -r1;
    r2 = r1.constrained();
    CHECK_EQ(r1, -r2);
}

TEST_CASE("motor-constrain")
{
    motor m1{1, 2, 3, 4, 5, 6, 7, 8};
    motor m2 = m1.constrained();
    CHECK_EQ(m1, m2);

    m1 = -m1;
    m2 = m1.constrained();
    CHECK_EQ(m1, -m2);
}