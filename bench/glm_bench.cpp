#include <benchmark/benchmark.h>
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

static void BM_quat_composition(benchmark::State& state)
{
    glm::quat q1;
    glm::quat q2;
    while (state.KeepRunning())
    {
        benchmark::DoNotOptimize(q1 * q2);
    }
}
BENCHMARK(BM_quat_composition);

static void BM_quat_application(benchmark::State& state)
{
    glm::quat q;
    glm::vec4 p;
    while (state.KeepRunning())
    {
        auto m = glm::toMat4(q);
        benchmark::DoNotOptimize(m * p);
    }
}
BENCHMARK(BM_quat_application);

static void BM_quat_matrix_conversion(benchmark::State& state)
{
    glm::quat q;
    while (state.KeepRunning())
    {
        benchmark::DoNotOptimize(glm::toMat4(q));
    }
}
BENCHMARK(BM_quat_matrix_conversion);

static void BM_dual_quat_composition(benchmark::State& state)
{
    glm::dualquat dq1{
        glm::quat{1.f, 2.f, 3.f, 4.f}, glm::quat{1.f, 2.f, 3.f, 4.f}};
    glm::dualquat dq2{
        glm::quat{1.f, 2.f, 3.f, 4.f}, glm::quat{1.f, 2.f, 3.f, 4.f}};
    while (state.KeepRunning())
    {
        benchmark::DoNotOptimize(dq1 * dq2);
    }
}
BENCHMARK(BM_dual_quat_composition);

static void BM_dual_quat_application(benchmark::State& state)
{
    glm::dualquat dq{
        glm::quat{1.f, 2.f, 3.f, 4.f}, glm::quat{1.f, 2.f, 3.f, 4.f}};
    glm::vec4 p;
    while (state.KeepRunning())
    {
        auto m = glm::mat3x4_cast(dq);
        benchmark::DoNotOptimize(m * p);
    }
}
BENCHMARK(BM_dual_quat_application);

static void BM_dual_quat_matrix_conversion(benchmark::State& state)
{
    glm::dualquat dq{glm::quat{}, glm::quat{}};
    while (state.KeepRunning())
    {
        benchmark::DoNotOptimize(glm::mat3x4_cast(dq));
    }
}
BENCHMARK(BM_dual_quat_matrix_conversion);

BENCHMARK_MAIN();