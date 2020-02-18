#include <benchmark/benchmark.h>
#include <klein/klein.hpp>
#include <random>

static std::random_device r;
static std::minstd_rand lcg{r()};
static std::uniform_real_distribution<float> dist{-100.f, 100.f};

kln::rotor random_rotor()
{
    return {dist(lcg), dist(lcg), dist(lcg), dist(lcg)};
}

kln::motor random_motor()
{
    return {dist(lcg),
            dist(lcg),
            dist(lcg),
            dist(lcg),
            dist(lcg),
            dist(lcg),
            dist(lcg),
            dist(lcg)};
}

kln::point random_point()
{
    return {dist(lcg), dist(lcg), dist(lcg)};
}

static void BM_rotor_composition(benchmark::State& state)
{
    static kln::rotor r1{1.f, 2.f, 3.f, 4.f};
    static kln::rotor r2{-1.f, 1.f, 4.f, 2.f};
    while (state.KeepRunning())
    {
        benchmark::ClobberMemory();
        benchmark::DoNotOptimize(r1 * r2);
    }
}
BENCHMARK(BM_rotor_composition);

static void BM_rotor_application(benchmark::State& state)
{
    kln::rotor r{1.f, 2.f, 3.f, 4.f};
    kln::point p{1.f, 2.f, 3.f};
    while (state.KeepRunning())
    {
        benchmark::ClobberMemory();
        benchmark::DoNotOptimize(r(p));
    }
}
BENCHMARK(BM_rotor_application);

static void BM_rotor_matrix_conversion(benchmark::State& state)
{
    kln::rotor r{1.f, 2.f, 3.f, 4.f};
    while (state.KeepRunning())
    {
        benchmark::ClobberMemory();
        benchmark::DoNotOptimize(r.as_matrix());
    }
}
BENCHMARK(BM_rotor_matrix_conversion);

static void BM_motor_composition(benchmark::State& state)
{
    kln::motor m1{1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f};
    kln::motor m2{1.f, -2.f, 3.f, 3.f, 5.f, 1.f, 2.f, -8.f};
    while (state.KeepRunning())
    {
        benchmark::ClobberMemory();
        benchmark::DoNotOptimize(m1 * m2);
    }
}
BENCHMARK(BM_motor_composition);

static void BM_motor_application(benchmark::State& state)
{
    kln::motor m{1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f};
    kln::point p{1.f, 2.f, 3.f};
    while (state.KeepRunning())
    {
        benchmark::ClobberMemory();
        benchmark::DoNotOptimize(m(p));
    }
}
BENCHMARK(BM_motor_application);

static void BM_motor_matrix_conversion(benchmark::State& state)
{
    kln::motor m{1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f};
    while (state.KeepRunning())
    {
        benchmark::ClobberMemory();
        benchmark::DoNotOptimize(m.as_matrix());
    }
}
BENCHMARK(BM_motor_matrix_conversion);

BENCHMARK_MAIN();