#include <mc_ruler.h>
#include <rtm/quatf.h>
#include <rtm/qvvf.h>

rtm::quatf rotor_composition(rtm::quatf const& a, rtm::quatf const& b)
{
    MC_MEASURE_BEGIN(rotor_composition);
    return rtm::quat_mul(a, b);
    MC_MEASURE_END();
}