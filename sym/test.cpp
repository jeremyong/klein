#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "ga.hpp"
#include "parser.hpp"
#include "poly.hpp"

TEST_CASE("monomial-product")
{
    // a^2
    mon m1;
    m1.push("a", 2);

    // b / a
    mon m2;
    m2.push("a", -1).push("b", 1);

    // ab
    mon m3 = m1 * m2;

    CHECK_EQ(m3.factors["a"], 1);
    CHECK_EQ(m3.factors["b"], 1);
}

TEST_CASE("polynomial")
{
    mon a;
    a.push("a", 1);
    mon b;
    b.push("b", 1);

    mon a2 = a * a;
    mon b2 = b * b;

    // a + b
    poly p1;
    p1.push(a, 1.f);
    p1.push(b, 1.f);

    // a - b
    poly p2;
    p2.push(a, 1.f);
    p2.push(b, -1.f);

    // 1
    poly p_one;
    mon one;
    p_one.push(one, 1.f);

    // 2
    poly p_two;
    p_two.push(one, 2.f);

    SUBCASE("sum")
    {
        poly p3 = p1 + p2;
        CHECK_EQ(p3.terms.find(b), p3.terms.end());
        CHECK_EQ(p3.terms.find(a)->second, 2.f);
    }

    SUBCASE("sum-one")
    {
        poly p3 = p1 + p_one;
        CHECK_EQ(p3.terms.find(one)->second, 1.f);
        CHECK_EQ(p3.terms.find(a)->second, 1.f);
    }

    SUBCASE("sum-one-two")
    {
        poly p3 = p_one + p_two;
        CHECK_EQ(p3.terms.find(one)->second, 3.f);
    }

    SUBCASE("product")
    {
        poly p3 = p1 * p2;
        CHECK_EQ(p3.terms.find(a2)->second, 1.f);
        CHECK_EQ(p3.terms.find(b2)->second, -1.f);
    }
}

TEST_CASE("ga")
{
    algebra pga{3, 0, 1};

    poly p_a0;
    mon m_a0;
    m_a0.push("a0");
    p_a0.push(m_a0);

    poly p_a1;
    mon m_a1;
    m_a1.push("a1");
    p_a1.push(m_a1);

    poly p_b0;
    mon m_b0;
    m_b0.push("b0");
    p_b0.push(m_b0);

    poly p_b1;
    mon m_b1;
    m_b1.push("b1");
    p_b1.push(m_b1);

    // a_0 * e_0 + a_1 * e_1
    mv mv1{pga};
    mv1.push(0b1, p_a0);
    mv1.push(0b10, p_a1);

    // b_0 * e_0 + b_1 * e_1
    mv mv2{pga};
    mv2.push(0b1, p_b0);
    mv2.push(0b10, p_b1);

    mon m_a1_b1;
    m_a1_b1.push("a1");
    m_a1_b1.push("b1");

    mon m_a0_b1;
    m_a0_b1.push("a0");
    m_a0_b1.push("b1");

    mon m_a1_b0;
    m_a1_b0.push("a1");
    m_a1_b0.push("b0");

    SUBCASE("product")
    {
        // (a_0 * b_1 - a_1 * b_0) * e_10 + a_1 * b_1
        mv mv3 = mv1 * mv2;
        CHECK_EQ(mv3.terms.size(), 2);
        CHECK_NE(mv3.terms[0].terms.find(m_a1_b1), mv3.terms[0].terms.end());
        CHECK_EQ(mv3.terms[0].terms.find(m_a1_b1)->second, 1.f);
        CHECK_NE(mv3.terms[3].terms.find(m_a0_b1), mv3.terms[3].terms.end());
        CHECK_EQ(mv3.terms[3].terms.find(m_a0_b1)->second, 1.f);
        CHECK_NE(mv3.terms[3].terms.find(m_a1_b0), mv3.terms[3].terms.end());
        CHECK_EQ(mv3.terms[3].terms.find(m_a1_b0)->second, -1.f);
    }
}

TEST_CASE("parser")
{
    algebra pga{3, 0, 1};

    SUBCASE("add")
    {
        mv mv1 = parse("1 + 3 * 2", pga);
        CHECK_EQ(mv1.terms[0].terms.begin()->second, 7.f);

        mv1 = parse("(3e0 + 3e012) + (3e0 - 3e012)", pga);
        CHECK_EQ(mv1.terms[0b111].terms.size(), 0);
        CHECK_EQ(mv1.terms[0b1].terms.begin()->second, 6.f);
    }

    SUBCASE("sub")
    {
        mv mv1 = parse("1 - 3 - 2", pga);
        CHECK_EQ(mv1.terms[0].terms.begin()->second, -4.f);
    }

    SUBCASE("product")
    {
        mv mv1 = parse("2e012 * 2", pga);
        CHECK_EQ(mv1.terms[0b111].terms.begin()->second, 4.f);

        mv mv2 = parse("(e23 + 2e012) * (2 - 3e01)", pga);
        CHECK_EQ(mv2.terms[0b1100].terms.begin()->second, 2.f);
        CHECK_EQ(mv2.terms[0b111].terms.begin()->second, 4.f);
        CHECK_EQ(mv2.terms[0b1111].terms.begin()->second, -3.f);
    }

    SUBCASE("exterior-product")
    {
        mv mv1 = parse("(e3 + e2 + e1 + e0) ^ (e3 + 2e2 + 2e1 + 2e0)", pga);
        CHECK_EQ(mv1.terms[0b1001].terms.begin()->second, -1.f);
        CHECK_EQ(mv1.terms[0b1010].terms.begin()->second, -1.f);
        CHECK_EQ(mv1.terms[0b1100].terms.begin()->second, -1.f);
        CHECK_EQ(mv1.terms[0b110].terms.size(), 0.f);
        CHECK_EQ(mv1.terms[0b101].terms.size(), 0.f);
        CHECK_EQ(mv1.terms[0b11].terms.size(), 0.f);

        mv mv2
            = parse("(e3 + e2 + e1 + e0) ^ (e123 + 2e021 + 2e013 + 2e032)", pga);
        CHECK_EQ(mv2.terms[0b1111].terms.begin()->second, 7.f);
        CHECK_EQ(mv2.terms.size(), 1);
    }

    SUBCASE("regressive-product")
    {
        // Join the origin and the point (1, 0, 0) to generate the x-axis
        mv mv1 = parse("e123 & (e123 + e032)", pga);
        CHECK_EQ(mv1.terms.size(), 1);
        CHECK_EQ(mv1.terms[0b1100].terms.begin()->second, 1.f);
    }

    SUBCASE("inner-product")
    {
        // The inner product of two places is a scalar.
        mv mv1 = parse("(e0 + e1 + e2 + e3) | (e0 + e1 + e2 + e3)", pga);
        CHECK_EQ(mv1.terms.size(), 1);
        CHECK_EQ(mv1.terms[0].terms.begin()->second, 3.f);

        mv mv2
            = parse("(e0 + e1 + e2 + e3) | (2e0123 + 3e01 - 4e02 + 2e03)", pga);
        CHECK_EQ(mv2.terms.size(), 4);
        CHECK_EQ(mv2.terms[1].terms.begin()->second, -1.f);
        CHECK_EQ(mv2.terms[0b111].terms.begin()->second, -2.f);
        CHECK_EQ(mv2.terms[0b1011].terms.begin()->second, 2.f);
        CHECK_EQ(mv2.terms[0b1101].terms.begin()->second, -2.f);
    }

    SUBCASE("reverse")
    {
        mv mv1 = parse("~e02", pga);
        CHECK_EQ(mv1.terms[0b101].terms.begin()->second, -1.f);
    }

    SUBCASE("rotor")
    {
        mv mv1 = parse(
            "(2 + 3e12 + 4e31) * (5e0 + 7e1 + 11e2) * (2 - 3e12 - 4e31)", pga);
        CHECK_EQ(mv1.terms[1].terms.begin()->second, 145.f);
        CHECK_EQ(mv1.terms[0b10].terms.begin()->second, -15.f);
        CHECK_EQ(mv1.terms[0b100].terms.begin()->second, 37.f);
        CHECK_EQ(mv1.terms[0b1000].terms.begin()->second, 376.f);
    }
}