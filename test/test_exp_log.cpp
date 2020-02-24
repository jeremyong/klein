#define _USE_MATH_DEFINES
#include <doctest/doctest.h>

#include <klein/klein.hpp>

using namespace kln;

TEST_CASE("rotor-exp-log")
{
    rotor r{M_PI * 0.5f, 0.3f, -3.f, 1.f};
    rotor::branch b = r.log();
    rotor r2        = b.exp();

    CHECK_EQ(r2.scalar(), doctest::Approx(r.scalar()).epsilon(0.001));
    CHECK_EQ(r2.e12(), doctest::Approx(r.e12()).epsilon(0.001));
    CHECK_EQ(r2.e32(), doctest::Approx(r.e32()).epsilon(0.001));
    CHECK_EQ(r2.e23(), doctest::Approx(r.e23()).epsilon(0.001));
}

TEST_CASE("motor-exp-log")
{
    // Construct a motor from a translator and rotor
    rotor r{M_PI * 0.5f, 0.3f, -3.f, 1.f};
    translator t{12.f, -2.f, 0.4f, 1.f};
    motor m1 = r * t;
    line l   = m1.log();
    motor m2 = l.exp();
    // Check accuracy to within 1%
    CHECK_EQ(m1.scalar(), doctest::Approx(m2.scalar()).epsilon(0.01));
    CHECK_EQ(m1.e12(), doctest::Approx(m2.e12()).epsilon(0.01));
    CHECK_EQ(m1.e32(), doctest::Approx(m2.e32()).epsilon(0.01));
    CHECK_EQ(m1.e23(), doctest::Approx(m2.e23()).epsilon(0.01));
    CHECK_EQ(m1.e01(), doctest::Approx(m2.e01()).epsilon(0.01));
    CHECK_EQ(m1.e02(), doctest::Approx(m2.e02()).epsilon(0.01));
    CHECK_EQ(m1.e03(), doctest::Approx(m2.e03()).epsilon(0.01));
    CHECK_EQ(m1.e0123(), doctest::Approx(m2.e0123()).epsilon(0.01));
}

TEST_CASE("motor-slerp")
{
    // Construct a motor from a translator and rotor
    rotor r{M_PI * 0.5f, 0.3f, -3.f, 1.f};
    translator t{12.f, -2.f, 0.4f, 1.f};
    motor m1 = r * t;
    line l   = m1.log();
    // Divide the motor action into three equal steps
    line step    = l / 3;
    motor m_step = step.exp();
    motor m2     = m_step * m_step * m_step;
    CHECK_EQ(m1.scalar(), doctest::Approx(m2.scalar()).epsilon(0.01));
    CHECK_EQ(m1.e12(), doctest::Approx(m2.e12()).epsilon(0.01));
    CHECK_EQ(m1.e32(), doctest::Approx(m2.e32()).epsilon(0.01));
    CHECK_EQ(m1.e23(), doctest::Approx(m2.e23()).epsilon(0.01));
    CHECK_EQ(m1.e01(), doctest::Approx(m2.e01()).epsilon(0.01));
    CHECK_EQ(m1.e02(), doctest::Approx(m2.e02()).epsilon(0.01));
    CHECK_EQ(m1.e03(), doctest::Approx(m2.e03()).epsilon(0.01));
    CHECK_EQ(m1.e0123(), doctest::Approx(m2.e0123()).epsilon(0.01));
}

TEST_CASE("motor-blend")
{
    rotor r1{M_PI * 0.5f, 0, 0, 1.f};
    translator t1{1.f, 0.f, 0.f, 1.f};
    motor m1 = r1 * t1;

    rotor r2{M_PI * 0.5f, 0.3f, -3.f, 1.f};
    translator t2{12.f, -2.f, 0.4f, 1.f};
    motor m2 = r2 * t2;

    motor motion     = m2 * ~m1;
    line step        = motion.log() / 4.f;
    motor motor_step = step.exp();

    // Applying motor_step 0 times to m1 is m1.
    // Applying motor_step 4 times to m1 is m2 * ~m1;
    motor result = motor_step * motor_step * motor_step * motor_step * m1;
    CHECK_EQ(result.scalar(), doctest::Approx(m2.scalar()).epsilon(0.01));
    CHECK_EQ(result.e12(), doctest::Approx(m2.e12()).epsilon(0.01));
    CHECK_EQ(result.e32(), doctest::Approx(m2.e32()).epsilon(0.01));
    CHECK_EQ(result.e23(), doctest::Approx(m2.e23()).epsilon(0.01));
    CHECK_EQ(result.e01(), doctest::Approx(m2.e01()).epsilon(0.01));
    CHECK_EQ(result.e02(), doctest::Approx(m2.e02()).epsilon(0.01));
    CHECK_EQ(result.e03(), doctest::Approx(m2.e03()).epsilon(0.01));
    CHECK_EQ(result.e0123(), doctest::Approx(m2.e0123()).epsilon(0.01));
}