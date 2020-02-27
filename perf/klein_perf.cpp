#include <klein/klein.hpp>
#include <mc_ruler.h>

kln::rotor rotor_composition(kln::rotor const& a, kln::rotor const& b)
{
    MC_MEASURE_BEGIN(rotor_composition);
    return a * b;
    MC_MEASURE_END();
}

kln::point motor_application(kln::motor const& m, kln::point const& p)
{
    MC_MEASURE_BEGIN(motor_application);
    return m(p);
    MC_MEASURE_END();
}