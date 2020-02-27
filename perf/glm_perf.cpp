#include <glm/ext/quaternion_float.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/dual_quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <mc_ruler.h>

glm::quat rotor_composition(glm::quat const& a, glm::quat const& b)
{
    MC_MEASURE_BEGIN(rotor_composition);
    return a * b;
    MC_MEASURE_END();
}

glm::vec4 motor_application(glm::dualquat const& a, glm::vec4 const& b)
{
    MC_MEASURE_BEGIN(motor_application);
    return glm::mat3x4_cast(a) * b;
    MC_MEASURE_END();
}