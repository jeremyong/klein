#include <glm/ext/quaternion_float.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/dual_quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <random>

static std::random_device r;
static std::minstd_rand lcg{r()};
static std::uniform_real_distribution<float> dist{-100.f, 100.f};

glm::quat random_quat()
{
    return {dist(lcg), dist(lcg), dist(lcg), dist(lcg)};
}

glm::vec4 random_point()
{
    return {dist(lcg), dist(lcg), dist(lcg), 1.f};
}

glm::dualquat random_dual_quat()
{
    return {{dist(lcg), dist(lcg), dist(lcg), dist(lcg)},
            {dist(lcg), dist(lcg), dist(lcg), dist(lcg)}};
}

int main(int argc, char** argv)
{
    // NOTE: All benchmarks from before were removed in favor of inspecting
    // assembly from the time being due to pathological measurement errors.
    // A new benchmark is underway that doesn't rely on `asm volatile` due to
    // compilers ignoring the directive.
    return 0;
}