#include <rtm/quatf.h>
#include <rtm/qvvf.h>

// Run to generate llvm analysis
// clang++ rtm_bench.cpp -std=c++17 -O2 -I../public
// -I../build/_deps/rtm-src/includes -msse4.2 -march=native -S -o - | llvm-mca
// -mcpu=btver2 | xclip

/*
rtm::quatf rotor_composition(rtm::quatf const& a, rtm::quatf const& b)
{
    return rtm::quat_mul(a, b);
}
*/

// NOTE: Not an apples to apples comparison with a motor application because
// qvvf is decomposed into two simple bivectors (rotation/translation stored
// separately)
rtm::vector4f motor_application(rtm::qvvf const& a, rtm::vector4f const& b)
{
    return rtm::qvv_mul_point3(b, a);
}