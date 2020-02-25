#include <glm/ext/quaternion_float.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/dual_quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

// Run to generate llvm analysis
// clang++ glm_bench.cpp -std=c++17 -O2 -I../public -src/includes -msse4.2
// -march=native -S -o - | llvm-mca -mcpu=btver2 | xclip

// glm::quat rotor_composition(glm::quat const& a, glm::quat const& b)
// {
//     return a * b;
// }

glm::vec4 motor_application(glm::dualquat const& a, glm::vec4 const& b)
{
    return glm::mat3x4_cast(a) * b;
}