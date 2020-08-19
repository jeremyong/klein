#include <mc_ruler.h>
#include <rtm/quatf.h>
#include <rtm/qvvf.h>

rtm::quatf rotor_composition(rtm::quatf const& a, rtm::quatf const& b)
{
    MC_MEASURE_BEGIN(rotor_composition);
    auto out = rtm::quat_mul(a, b);
    MC_MEASURE_END();
    return out;
}

rtm::vector4f qvvf_application(rtm::qvvf const& a, rtm::vector4f const& b)
{
    MC_MEASURE_BEGIN(qvvf_application);
    auto out = rtm::qvv_mul_point3_no_scale(b, a);
    MC_MEASURE_END();
    return out;
}